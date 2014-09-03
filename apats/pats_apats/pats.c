// Stephen Fulwider
//  Extension of Baeza-Yates algorithm to handle exact searching for multiple patterns

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

Int *U[MAX_CHAR]; // character bit vectors
Int S,F; // start and end bit vectors
Int M;   // column of matrix
Int Z,X; // used to find matches


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
	unsigned int i,p,len;
	char pat[MAX_PAT_LEN+1]; // pattern
	
	in=fopen(file,"r");
			
	p=0; Pn=8; n=0;
	P=(char**)calloc(Pn,sizeof(char*));
	while (fgets(pat,MAX_PAT_LEN+1,in))
	{
		if (p==Pn)
		{
			Pn<<=1;
			P=(char**)realloc(P,Pn*sizeof(char*));
		}
		len=strlen(pat)-1;
		if (len==0) continue;
		P[p]=(char*)calloc(len+1,sizeof(char));
		pat[len]='\0';
		strcpy(P[p],pat);
		n+=len;
		++p;
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
	
	unsigned int i,j,t,len;
	bool found;
	
	make(&M,n);
	make(&Z,n); // matches found
	make(&X,n); // location of match found
	
	unsigned int An=M.An;
		
	in=fopen(file,"r");

	clock_t start, end;
	double elapsed;

	start = clock();
	while (fgets(T,MAX_LINE_LEN+1,in))
	{
		found=false;
		len=strlen(T);
		for (t=0; t<len; ++t)
		{
			c=T[t];
			for (i=0,j=An-1; i<An; ++i,--j)
			{
				M.A[j]=((M.A[j])<<1)|(S.A[j]);
				if (j>0 && (((M.A[j-1])&(1U<<31))>0))
					M.A[j]|=1;
				M.A[j]&=(U[c]->A[j]);
				
				if (((M.A[j])&(F.A[j]))>0)
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
	if (argc!=3)
	{
		fprintf(stderr,"Usage: ./pats PATTERN_FILE TEXT_FILE\n");
		return 1;
	}
	
	readPatterns(argv[1]);
	preProcess();	
	search(argv[2]);
	
	return 0;
}

