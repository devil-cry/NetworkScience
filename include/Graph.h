#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <algorithm>
#include <random>
#include <ctime>
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
    int dis[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    

    void init()
    {
        for(int i=0;i<MAX_VERTEX_NUM;i++){
            edge[i].clear();
            degree[i]=0;
            visNode[i]=false;
        }
        memset(dis,0x3f3f3f3f,sizeof(dis));
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
        assert(vertexNum>0);
        double sumDegree=2.0*edgeNum;
        assert(vertexNum>0);
        return sumDegree/vertexNum;
    }

    vector<pii> getDegreeDistribution()
    {
        vector<pii> v;
        set<int> s;
        map<int,int> mp;
        for(int i=0;i<MAX_VERTEX_NUM;i++)if(visNode[i]){
            if(s.find(degree[i])==s.end()){
                s.insert(degree[i]);
            }
            mp[degree[i]]++;
        }
        for(auto x:s){
            v.push_back(pii(x,mp[x]));
        }
        return v;
    }

    double getExcessAverageDegree()
    {
        assert(vertexNum>0);
        double sum=0.0,tsum;
        for(int i=0;i<MAX_VERTEX_NUM;i++)if(visNode[i]){
            tsum=0.0;
            for(auto v:edge[i]){
                tsum+=1.0*degree[v];
            }
            tsum/=edge[i].size();
            sum+=tsum;
        }
        return sum/vertexNum;
    }

    vector<pid> getExcessDegreeDistribution()
    {
        vector<pid> v;
        set<int> s;
        int cnt=0;
        map<int,int> mp;
        for(int i=0;i<MAX_VERTEX_NUM;i++)if(visNode[i]){
            for(auto v:edge[i]){
                if(s.find(degree[v])==s.end()){
                    s.insert(degree[v]);
                }
                mp[degree[v]]++;
            }
            cnt+=edge[i].size();
        }
        for(auto x:s){
            v.push_back(pid(x,1.0*mp[x]/cnt));
        }
        return v;
    }

    void floyd()
    {
        for(int i=0;i<MAX_VERTEX_NUM;i++)if(visNode[i]){
            for(auto x:edge[i]){
                dis[i][x]=dis[x][i]=1;
            }
        }
        for(int k=0;k<MAX_VERTEX_NUM;k++)if(visNode[k]){
            for(int i=0;i<MAX_VERTEX_NUM;i++)if(visNode[i]){
                for(int j=0;j<MAX_VERTEX_NUM;j++)if(visNode[j]){
                    dis[i][j]=min(dis[i][j], dis[i][k]+dis[k][j]);
                }
            }
        }
    }

    double getAveragePathLength()
    {
        assert(vertexNum>1);

        floyd();
        int sum=0;
        for(int i=0;i<MAX_VERTEX_NUM;i++)if(visNode[i]){
            for(int j=i+1;j<MAX_VERTEX_NUM;j++)if(visNode[j]){
                sum+=dis[i][j];
            }
        }
        return 2.0*sum/(vertexNum*(vertexNum-1));
    }

    double getGlobalClusteringCoefficient()
    {
        assert(vertexNum>0);
        floyd();
        double sum=0.0;
        int tsum;
        for(int i=0;i<MAX_VERTEX_NUM;i++)if(visNode[i]){
            tsum=0;
            if(degree[i]<2) continue;
            for(int j=0;j<edge[i].size();j++)
                for(int k=j+1;k<edge[i].size();k++)
                    if(dis[edge[i][j]][edge[i][k]]==1)
                        tsum+=2;
            sum+=1.0*tsum/(degree[i]*(degree[i]-1));
        }
        return sum/vertexNum;
    }

    void zeroOrderZeroModel(const Graph& src)
    {
        vector<int> tempNode;
        for(int i=0;i<MAX_VERTEX_NUM;i++)if(src.visNode[i]){
            tempNode.push_back(i);
        }
        int u,v,p,q;
        for(int i=0;i<src.vertexNum;i++){
            q=getrand(0,src.vertexNum-1);
            while( q==i ){
                q=getrand(0,src.vertexNum-1);
            }
            addedge(tempNode[i],tempNode[q]);
        }
        for(int i=src.vertexNum;i<src.edgeNum;i++){
            p=getrand(0,src.vertexNum-1);
            q=getrand(0,src.vertexNum-1);
            addedge(tempNode[p],tempNode[q]);
        }
    }

    void firstOrderZeroModel(const Graph& src)
    {
        pii tempDegree[MAX_VERTEX_NUM];
        for(int i=0;i<MAX_VERTEX_NUM;i++)
            tempDegree[i]=pii(src.degree[i],i);
        sort(tempDegree,tempDegree+MAX_VERTEX_NUM);
        reverse(tempDegree,tempDegree+MAX_VERTEX_NUM);
        int l=0,r=MAX_VERTEX_NUM-1;
        while(r>=0&&tempDegree[r].first==0) r--;
        int p,q,u,v;
        srand( (unsigned)time(NULL) );
        while (l<=r)
        {
            p=getrand(l,r);
            if(tempDegree[p].first==0) break;
            u=tempDegree[p].second;
            tempDegree[p].first--;
            if(tempDegree[p].first==0){
                swap(tempDegree[p],tempDegree[r]);
                r--;
            }
            q=getrand(l,r);
            v=tempDegree[q].second;
            tempDegree[q].first--;
            if(tempDegree[q].first==0){
                swap(tempDegree[q],tempDegree[r]);
                r--;
            }
            addedge(u,v);
        }
    }

    void secondOrderZeroModel()
    {

    }

};

#endif