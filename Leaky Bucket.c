#include<stdio.h>
#include<stdlib.h>
int trand(int a)
{	 
	int rn;
	rn=random()%10;
	rn=rn%a;
	if(rn==0)
	rn=1;
	return(rn);
}
int main()
{
	int i,packet[5],psz,bsz,pszrn=0,clk,ptime,orate;
	for(i=0;i<5;i++)
    	packet[i]=trand(6)*10;
	printf("\nEnter the o/p rate");
	scanf("%d",&orate);
	printf("Enter the bucket size");
	scanf("%d",&bsz);
	for(i=0;i<5;i++)
	{
		if((packet[i]+pszrn)>bsz)
			printf("\nIncoming packet size %d is greater than bucket size_reject",packet[i]);
		else
		{
			psz=packet[i];
			pszrn+=psz;
			printf("\nIncoming packet size is %d",psz);
			printf("\nNo. of packets waiting for transmission=%d",pszrn);
			ptime=trand(4)*10;
			printf("\nNext packet will come at %d",ptime);
			for(clk=0;clk<=ptime;clk++)
			{
				printf("\nTime left=%d\t\t",ptime-clk);
				sleep(1);
				if(pszrn)
				{
					if(pszrn==0)
						printf("\n Bucket is empty");
					else
					{
						if(pszrn>=orate)
							printf("%d Bytes are transmitted",orate);
						else
							printf("\n %d Bytes transmitted ",pszrn);
					}
					if(pszrn<=orate)
						pszrn=0;
					else
						pszrn-=orate;
					printf("\n Bytes remaining %d",pszrn);
				}
				else
					printf("\n Bytes remaining %d",pszrn);
			}
		}
	}
	return 0;
}
