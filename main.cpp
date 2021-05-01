#include <iostream>
#include "include/Global.h"
#include "include/Graph.h"
using namespace std;
using namespace global;

FILE *fin,*fout;
Graph g,g0,g1,g2;

void getData()
{
    g.init();
    fin=fopen("data/data9.csv","r");
    int u,v;
    while (~fscanf(fin,"%d,%d\n",&u,&v))
    {
        g.addedge(u,v);
    }

}
void printGraphProperties(Graph& gt)
{
    fprintf(fout,"节点数 N :\t %d\n",gt.vertexNum);
    fprintf(fout,"边数 M :\t %d\n",gt.edgeNum);
    fprintf(fout,"平均度 <K> :\t %.6f\n",gt.getAverageDegree());
    fprintf(fout,"度分布 P(K) :\t ");
    vector<pii> ans=gt.getDegreeDistribution();
    for(auto x:ans){
        fprintf(fout,"(%d,%d)\t",x.first,x.second);
    }
    fprintf(fout,"\n");
    fprintf(fout,"余平均度 <Kn> :\t %.6f\n",gt.getExcessAverageDegree());
    fprintf(fout,"余度分布 Pn<K> :\t ");
    vector<pid> res=gt.getExcessDegreeDistribution();
    for(auto x:res){
        fprintf(fout,"(%d,%.6f) :\t",x.first,x.second);
    }
    fprintf(fout,"\n");
    fprintf(fout,"平均路径 L :\t %.6f\n",gt.getAveragePathLength());
    fprintf(fout,"聚类系数 C :\t %.6f\n",gt.getGlobalClusteringCoefficient());
}
void solve()
{
    fout=fopen("data/output.txt","w");
    fprintf(fout,"***********************");
    fprintf(fout,"原始图");
    fprintf(fout,"***********************\n");
    printGraphProperties(g);
    
    fprintf(fout,"***********************");
    fprintf(fout,"0阶零模型");
    fprintf(fout,"***********************\n");
    g0.init();
    g0.zeroOrderZeroModel(g);
    printGraphProperties(g0);

    fprintf(fout,"***********************");
    fprintf(fout,"1阶零模型");
    fprintf(fout,"***********************\n");
    g1.init();
    g1.firstOrderZeroModel(g);
    printGraphProperties(g1);

}

int main()
{
    getData();
    solve();

    system("pause");
    return 0;
}

