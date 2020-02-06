#include<stdio.h>
#include<string.h>

char data[100],concatdata[117],src_crc[17],dest_crc[17],frame[120],divident[18];
char divisor[18]="10001000000100001",res[17]="0000000000000000";

void crc_cal(int node)       // function to calculate Cyclic Redundancy Check code
{
    int i,j;
    for(j=17;j<=strlen(concatdata);j++)
    {
        if(divident[0]=='1')                    // performing an ex-or operation
        {
            for(i=1;i<=16;i++)
                if(divident[i]!=divisor[i])
                    divident[i-1]='1';
                else
                    divident[i-1]='0';
        }
        else
        {
            for(i=1;i<=16;i++)
                divident[i-1]=divident[i];
        }
        if(node==0)
            divident[i-1]=concatdata[j];
        else
            divident[i-1]=frame[j];
    }
    divident[i]='\0';
    printf("\ncrc is %s\n",divident);
    if(node==0)
    {
        strcpy(src_crc,divident);
    }
    else
        strcpy(dest_crc,divident);
}
int main()
{
    int i;
    printf("\n At src node :\n Enter the msg to be sent :");
    gets(data);
    strcpy(concatdata,data);
    strcat(concatdata,"0000000000000000");   //   Message appended with 16  zeros
    for(i=0;i<=16;i++)
        divident[i]=concatdata[i];
    divident[i]='\0';
    crc_cal(0);
    printf("\ndata is:\t");
    puts(data);
    printf("\n The frame transmitted is :\t");
    printf("\n%s%s",data,src_crc);
    printf("\n\t\tSOURCE NODE TRANSMITTED THE FRAME---->");
    printf("\n\n\n\n\t\t\tAT DESTINATION NODE\nenter the recived frame:\t");
    gets(frame);
    for(i=0;i<=16;i++)
        divident[i]=frame[i];
    divident[i]='\0';
    crc_cal(1);
    if((strcmp(dest_crc,res))==0)
        printf("\nRecived frame is error free .\n ");
    else
        printf("\nRecived frame containes one or more error ");
    return 1;
}
