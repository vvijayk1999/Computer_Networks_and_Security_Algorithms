
#include<stdio.h>
struct rtable
{
    int dist[10],nextnode[10];
}table[10];
int cost[10][10],n;
void distVect()
{
    int count = 0,i,j,k;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        {
            table[i].dist[j] = cost[i][j];
            table[i].nextnode[j] = j;
        }
    
    do
    {
        count = 0;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                for(k=0;k<n;k++)
                {
                    if(table[i].dist[j] > cost[i][k] + table[k].dist[j])
                    {
                        table[i].dist[j] = table[i].dist[k] + table[k].dist[j];
                        table[i].nextnode[j] = k;
                        count ++;
                    }
                }
    }while(count!=0);
}
int main()
{
    int i,j;
    
    printf("Enter the number of vertices : ");
    scanf("%d",&n);
    printf("Enter the cost matrix : ");
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&cost[i][j]);
    distVect();
    
    printf("\n\n\nThe routing table is : \n\n");
    for(i=0;i<n;i++)
    {
        printf("\nRouting table for node %c : \n",i+65);
        printf("dest.\t\tnext node\t\tdistance\n");
        for(j=0;j<n;j++)
        {
            if(table[i].dist[j] >= 99)
                printf("%c\t\t-\t\tinfinite\n",j+65);
            else
                printf("%c\t\t%c\t\t%d\n",j+65,table[i].nextnode[j]+65,table[i].dist[j]);
        }
    }
    return 0;
}
