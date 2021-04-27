#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Global.h"
using namespace std;
using namespace global;
class Graph
{
public:
    vector<int> edge[MAX_VERTEX_NUM];
    int degree[MAX_VERTEX_NUM];
    int vertexNum,edgeNum;
    int averageDegree;
    bool visNode[MAX_VERTEX_NUM];
    Graph()
    {
        for(int i=0;i<MAX_VERTEX_NUM;i++){
            edge[i].clear();
            degree[i]=0;
            visNode[i]=false;
        }
        vertexNum=edgeNum=0;
    }

    void addedge(int u,int v)
    {
        edge[u].push_back(v);
        edge[v].push_back(u);
        degree[u]++;
        degree[v]++;
        if(!visNode[u]){visNode[u]=true;vertexNum++;}
        if(!visNode[v]){visNode[v]=true;vertexNum++;}
        edgeNum++;
    }

    int getVertexNum()
    {
        return vertexNum;
    }

    int getEdgeNum()
    {
        return edgeNum;
    }

    double getAverageDegree()
    {
        double sumDegree=2.0*edgeNum;
        if(vertexNum==0){
            puts("ERROR IN getAverageDegree(): There is no vertex in graph!");
            return -1;
        }
        return sumDegree/vertexNum;
    }



};

#endif