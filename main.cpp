#include <iostream>
#include "include/Global.h"
#include "include/Graph.h"
using namespace std;
using namespace global;

FILE *fin,*fout;
Graph g;

void getData()
{
    fin=fopen("data/data9.csv","r");
    int u,v;
    while (~fscanf(fin,"%d,%d\n",&u,&v))
    {
        g.addedge(u,v);
        printf("%d %d\n",u,v);
    }
    
}


int main()
{
    getData();

    system("pause");
    return 0;
}
