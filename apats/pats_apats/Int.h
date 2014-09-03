// Stephen Fulwider
// Special Int structure to hold ints longer than 32 bits and perform necessary bit operations
//  on extended Ints in an efficient manner

#ifndef Int_Type
#define Int_Type

#define ALL 0xffffffff

#define true 1
#define false 0


typedef struct
{
	unsigned int An;
	unsigned int *A;
} Int;

typedef int bool;


// make a new Int type with the appropriate amount of space
inline void make(Int* T,int n)
{
	assert(n>0);
	T->An=(n+31)>>5; // ceil (n/32)
	T->A=(unsigned int *)calloc(T->An,sizeof(unsigned int));
}

// T=0
inline void zero(const Int* T)
{
	unsigned int i,n=T->An;
	for (i=0; i<n; ++i)
		T->A[i]=0;
}

// turn bit n on
inline void set(const Int* T,unsigned int n)
{
	T->A[n>>5]|=(1U<<(n%32));
}

/*
// T==0?
inline bool isZero(const Int* T)
{
	unsigned int i,n=T->An;
	for (i=0; i<n; ++i)
		if (T->A[i]!=0)
			return false;
	return true;
}



// turn bit n off
inline void unset(const Int* T,unsigned int n)
{
	T->A[n>>5]&=~(1U<<(n%32));
}

// invert all bits of A
inline void invert(const Int* T)
{
	unsigned int i,n=T->An;
	for (i=0; i<n; ++i)
		T->A[i]=~(T->A[i]);
}

// T=rhs
inline void setInt(const Int* T,const Int* rhs)
{
	unsigned int i,n=T->An;
	for (i=0; i<n; ++i)
		T->A[i]=rhs->A[i];
}

// T&=rhs, one is set only if result is non-zero
inline void and(const Int* T,const Int* rhs,bool* one)
{
	unsigned int i,n=T->An;
	*one=false;
	for (i=0; i<n; ++i)
	{
		T->A[i]&=rhs->A[i];
		if ((T->A[i])>0)
			*one=true;
	}
}

// T=X&Y, one is set only if result is non-zero
inline void and3(const Int* T,const Int* X,const Int* Y,bool* one)
{
	unsigned int i,n=T->An;
	*one=false;
	for (i=0; i<n; ++i)
	{
		T->A[i]=(X->A[i])&(Y->A[i]);
		if ((T->A[i])>0)
			*one=true;
	}
}


// T|=rhs
inline void or(const Int* T,const Int* rhs)
{
	unsigned int i,n=T->An;
	for (i=0; i<n; ++i)
		T->A[i]|=rhs->A[i];
}

// T|=(X|Y)
inline void or3(const Int* T, const Int* X, const Int* Y)
{
	unsigned int i,n=T->An;
	for (i=0; i<n; ++i)
		T->A[i]|=X->A[i]|Y->A[i];
}

// T|=rhs
inline void xor(const Int* T,const Int* rhs)
{
	unsigned int i,n=T->An;
	for (i=0; i<n; ++i)
		T->A[i]^=rhs->A[i];
}

// T<<=1
inline void ls1(const Int* T)
{
	unsigned int i,j,n=T->An;
	for (i=0,j=n-1; i<n; ++i,--j)
	{
		T->A[j]<<=1;
		if (j>0 && (((T->A[j-1])&(1U<<31))>0))
			(T->A[j])|=1;
	}
}

// A|=(T<<1)
inline void ls1Or(const Int* A, const Int* prev)
{
	unsigned int i,j,n=A->An;
	for (i=0,j=n-1; i<n; ++i,--j)
	{
		A->A[j]|=((prev->A[j])<<1);
		if (j>0 && (((prev->A[j-1])&(1U<<31))>0))
			(A->A[j])|=1;
	}
}

// T=(T<<1)|S
inline void shiftOr(const Int* T,const Int* S)
{
	unsigned int i,j,n=T->An;
	for (i=0,j=n-1; i<n; ++i,--j)
	{
		T->A[j]<<=1;
		T->A[j]|=S->A[j];
		if (j>0 && (((T->A[j-1])&(1U<<31))>0))
			(T->A[j])|=1;
	}
}

// T=((T<<1)|S)&U
inline void shiftOrAnd(const Int* T,const Int* S,const Int* U)
{
	unsigned int i,j,n=T->An;
	for (i=0,j=n-1; i<n; ++i,--j)
	{
		T->A[j]<<=1;
		T->A[j]|=S->A[j];
		if (j>0 && (((T->A[j-1])&(1U<<31))>0))
			(T->A[j])|=1;
		T->A[j]&=U->A[j];
	}
}



// --T
//  !!! only call if T>0 !!!
inline void sub1(const Int* T)
{
	int j=0;
	for (; T->A[j]==0; ++j)
		T->A[j]=ALL;
	T->A[j]-=1;
}

// count trailing zeros
inline unsigned int ctz(const Int* T)
{
	unsigned int cnt=0,i,n=T->An;
	for (i=0; i<n; ++i)
	{
		if (T->A[i]==0) cnt+=32;
		else
		{
			cnt+=__builtin_ctz(T->A[i]);
			break;
		}
	}
	return cnt;
}
*/

#endif

