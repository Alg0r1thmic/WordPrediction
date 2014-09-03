// Stephen Fulwider
//  Extension of Baeza-Yates algorithm to handle approximate searching for multiple patterns

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "Int.h"

#define MAX_CHAR ((1<<7)-1)
#define MAX_PAT_LEN  100
#define MAX_LINE_LEN (1<<10)


FILE *in;

unsigned int Pn; // number of patterns
char **P;		// set of patterns
unsigned int n;  // sum of lengths of patterns

char T[MAX_LINE_LEN+1];  // line of text

unsigned int *N; // array for easy lookup of which pattern is found

unsigned int k; // maximum number of errors

Int *U[MAX_CHAR]; // character bit vectors
Int S,F; // start and end bit vectors
Int **M;   // columns of each matrix
Int Z,X; // used to find matches

//estructures meves
int hits[3000]; //hits pattern i
int size[3000]; //size pattern i
int discrete[10000]; //pos j -> pattern i


void print(const Int* T)
{
	unsigned int i,k;
	int at=0,idx=0;
	for (i=0; i<T->An; ++i)
	{
		for (k=0; k<32; ++k) // print backwards for ease of viewing
		{
			if (at<Pn && idx==strlen(P[at]))
			{
				++at;
				if (at==Pn) break;
				idx=0;
				fprintf(stderr," ");
			}
			++idx;
			fprintf(stderr,"%d",((T->A[i])&(1U<<k))>0);
		}
	}
	fprintf(stderr,"\n");
}

void readPatterns(char *file)
{
	unsigned int i,j,p,len;
	char pat[MAX_PAT_LEN+1]; // pattern
	
	in=fopen(file,"r");
			
	p=0; Pn=8; n=0; i=0;
	P=(char**)calloc(Pn,sizeof(char*));
	while (fgets(pat,MAX_PAT_LEN+1,in))
	{
		if (p==Pn)
		{
			Pn<<=1;
			P=(char**)realloc(P,Pn*sizeof(char*));
		}
		len=strlen(pat)-1;
		pat[len]='\0';
		if (len==0) continue;
		if (len<=k)
		{
			fprintf(stderr,"apats: size of pattern '%s' should be > #of errors %d (will match every line...)\n",pat,k);
			//continue;
		}
		size[i] = len;
		j=n;
		for (j=n; j<n+len; j++) discrete[j] = i;
		P[p]=(char*)calloc(len+1,sizeof(char));
		strcpy(P[p],pat);
		n+=len;
		++p; ++i;
	}
	Pn=p;
	fclose(in);
	
	/* print the patterns read
	fprintf(stderr,"Pn=%u\nPatterns:",Pn);
	for (i=0; i<Pn; ++i)
		fprintf(stderr," %s;",P[i]);
	fprintf(stderr,"\nn=%u\n\n",n);
	*/
}

void preProcess()
{
	unsigned int i,j,k;
	char c;
	
	for (i=0; i<MAX_CHAR; ++i)
	{
		U[i]=(Int*)calloc(1,sizeof(Int));
		make(U[i],n);
	}
	
	N=(unsigned int*)calloc(n,sizeof(unsigned int));
	
	make(&S,n); // start bit vector
	make(&F,n); // end bit vector
	
	for (i=0,j=0; i<Pn; ++i)
	{
		set(&S,j);
		for (k=0; k<strlen(P[i]); ++k,++j)
		{
			set(U[P[i][k]],j);
			N[j]=i;
		}
		set(&F,j-1);
	}
	
	/* print S,F, and U
	fprintf(stderr,"S: "); print(&S);
	fprintf(stderr,"F: "); print(&F);
	fprintf(stderr,"U\n");
	for (c=0; c<MAX_CHAR; ++c)
		if (!isZero(U[c]))
			fprintf(stderr,"%c: ",c), print(U[c]);
	fprintf(stderr,"\n");
	*/
}

void search(char *file)
{	
	char c;
	
	unsigned int i,j,t,l,tmp2,len;
	bool found;
	
	Int prev,tmp,SS;
	
	M=(Int**)calloc(k+1,sizeof(Int*)); // columns of matrix
	for (i=0; i<=k; ++i)
	{
		M[i]=(Int*)calloc(1,sizeof(Int));
		make(M[i],n);
	}
	make(&Z,n); // matches found
	make(&X,n); // location of match found
	
	make(&prev,n);
	make(&tmp,n);
	make(&SS,n);
	
	unsigned int An=M[0]->An;
	
	in=fopen(file,"r");

	clock_t start, end;
	double elapsed;
	
	start = clock();
	while (fgets(T,MAX_LINE_LEN+1,in))
	{
		found=false;
		for (i=0; i<=k; ++i)
			zero(M[i]);

		len=strlen(T);
		for (t=0; t<len; ++t)
		{
			c=T[t];
			for (i=0,j=An-1; i<An; ++i,--j)
			{
				prev.A[j]=M[0]->A[j];
				SS.A[j]=S.A[j];
				M[0]->A[j]=((M[0]->A[j])<<1)|(S.A[j]);
				if (j>0 && (((M[0]->A[j-1])&(1U<<31))>0))
					M[0]->A[j]|=1;
				M[0]->A[j]&=(U[c]->A[j]);
				
				for (l=1; l<=k; ++l)
				{
					tmp.A[j]=M[l]->A[j];
					SS.A[j]<<=1;
					if (j>0 && (((SS.A[j-1])&(1U<<31))>0))
						SS.A[j]|=1;
					
					M[l]->A[j]=0;
					if (l==1)
						M[l]->A[j]=S.A[j];
					M[l]->A[j]|=(M[l-1]->A[j])|(prev.A[j])|((prev.A[j])<<1)|((M[l-1]->A[j])<<1)|(SS.A[j]&U[c]->A[j]);
	
					if (j>0 && ((((prev.A[j-1])&(1U<<31))>0)||(((M[l-1]->A[j-1])&(1U<<31))>0)))
						M[l]->A[j]|=1;
					tmp2=((tmp.A[j])<<1)|(S.A[j]);
					if (j>0 && (((tmp.A[j-1])&(1U<<31))>0))
						tmp2|=1;
					M[l]->A[j]|=(tmp2&(U[c]->A[j]));
	
					prev.A[j]=tmp.A[j];
				}
				
				if (((M[k]->A[j])&(F.A[j]))>0)
				{
					found=true;
					break;
				}
			}
			
			if (found) // match found
			{
				printf("%s",T);
				break;
			}
		}
	}
	
	end = clock();
	elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
	
	fprintf(stderr,"Total Time: %.4lf\n",elapsed);
	
	
	fclose(in);
}

int main(int argc, char *argv[])
{	
	if (argc!=4)
	{
		fprintf(stderr,"Usage: ./apats k PATTERN_FILE TEXT_FILE\n");
		return 1;
	}
	
	k=atoi(argv[1]);
	readPatterns(argv[2]);
	preProcess();	
	search(argv[3]);
	
	return 0;
}

