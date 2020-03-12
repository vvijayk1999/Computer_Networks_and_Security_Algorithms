#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int gcd(long m, long n)
{
    if(n==0)return m;
    if(m<n)return gcd(n,m);
    return gcd(n,m%n);
}

int rsa(char *msg)
{
    long p=0,q=0,n=0,e=0,d=0,phi=0;
    long nummes[100]={0};
    long encrypt[100]={0};
    long decrypt[100]={0};
    long i=0,j=0,nofelem=0;
    int prime[1000]={0};
    while (p==q)
    {
        /* code */
        p=11;
        q=17;
    }
    printf("\nValues of p and q are %ld and %ld \n",p,q);
    n=p*q;
    phi = (p-1)*(q-1);
    for(i=2;i<phi;i++)
        if(gcd(i,phi)==1)
            break;
    e=i;
    for(i=2;i<phi;i++)
        if((e*i-1)%phi==0)
            break;
    d=i;
    for(i=0;i<strlen(msg);i++)
        nummes[i]=msg[i]-96;
    nofelem=strlen(msg);
    for(i=0;i<nofelem;i++)
    {
        encrypt[i]=1;
        for(j=0;j<e;j++)
            encrypt[i]=(encrypt[i]*nummes[i])%n;
    }
    printf("Encrypted message \n");
    for(i=0;i<nofelem;i++)
        printf("%ld",encrypt[i]);
    for(i=0;i<nofelem;i++)
    {
        decrypt[i]=1;
        for(j=0;j<d;j++)
            decrypt[i]=(decrypt[i]*encrypt[i])%n;
    }
    printf("\nDecrypted  message\n");
    for(i=0;i<nofelem;i++)
        printf("%c",(char)decrypt[i]+96);
    return 0;
}
int main()
{
    char msg[100]={0};
    printf("\nThis algorithm has been implemented for lower case letters only\n");
    printf("\nEnter the message : ");
    scanf("%s",msg);
    rsa(msg);
    return 0;   
}