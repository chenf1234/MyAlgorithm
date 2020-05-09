#include<iostream>
using namespace std;
#define INF 0x3f3f3f3f
int dis[200][200];
int n,m;
void Floyd(){
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(dis[i][k]!=INF&&dis[k][j]!=INF&&dis[i][k]+dis[k][j]<dis[i][j]){
                    dis[i][j]=dis[i][k]+dis[k][j];
                }
            }
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    printf("%d %d %d\n",dis[0],dis,&dis[0][0]);
    fill(&dis[0][0],&dis[0][0]+200*200,INF);
    for(int i=0;i<200;i++)dis[i][i]=0;
    for(int i=0;i<m;i++){
        int begin,next,cost;
        scanf("%d%d%d",&begin,&next,&cost);
        dis[begin][next]=cost;
    }
    Floyd();
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%-10d ",dis[i][j]);
        }
        printf("\n");
    }
}