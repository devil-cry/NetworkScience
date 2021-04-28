#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <set>
#include "Global.h"
using namespace std;
using namespace global;
class Graph
{
public:
    vector<int> edge[MAX_VERTEX_NUM];
    int degree[MAX_VERTEX_NUM];
    int excessDegree[MAX_VERTEX_NUM];

    int vertexNum,edgeNum;
    int vertexNumInDegree[MAX_VERTEX_NUM];
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

    double getAverageDegree()
    {
        double sumDegree=2.0*edgeNum;
        if(vertexNum==0){
            puts("ERROR IN getAverageDegree(): There is no vertex in graph!");
            return -1;
        }
        return sumDegree/vertexNum;
    }

    vector<pii>& getDegreeDistribution()
    {
        vector<pii> v;
        set<int> s;
        map<int,int> mp;
        for(int i=0;i<MAX_VERTEX_NUM;i++)if(visNode[i]){
            if(s.find(degree[i])==s.end()){
                s.insert(degree[i]);
                mp[degree[i]]++;
            }
        }
        for(auto x:s){
            v.push_back(pii(x,mp[x]));
        }
        return v;
    }

    vector<pid>& getExcessAverageDegree()
    {
        vector<pid> v;
        set<int> s;
        map<int,double> mpSum;
        map<int,int> mpCnt;
        double sum;
        for(int i=0;i<MAX_VERTEX_NUM;i++)if(visNode[i]){
            if(s.find(degree[i])==s.end()){
                s.insert(degree[i]);
                mpSum[degree[i]]=0.0;
            }
            sum=0.0;
            for(auto v:edge[i]){
                sum+=1.0*degree[v];
            }
            mpSum[degree[i]]+=sum/edge[i].size();
            mpCnt[degree[i]]++;
        }
        for(auto x:s){
            v.push_back(pid(x,mpSum[x]/mpCnt[x]));
        }
        return v;
    }

    vector<pid>& getExcessDegreeDistribution()
    {
        vector<pid> v;
        set<int> s;
        
    }

};

#endif