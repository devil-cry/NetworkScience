#ifndef GLOBAL_H
#define GLOBAL_H

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
namespace global
{
    template<typename T>inline void read(T &x)
    {
        x=0;bool f=0;char ch=getchar();
        while(ch<'0'||ch>'9')(ch=='-')&&(f=1),ch=getchar();
        while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();f&&(x=-x);
    }
    template<typename T>inline void out(T x)
    {
        (x<0)&&(putchar('-'),x=-x);
        if(x>9)out(x/10);putchar(x%10+'0');
    }

    #define fi first
    #define se second
    #define pb push_back
    #define bug puts("Bug Here")
    #define all(x) (x).begin(),(x).end()
    typedef long long ll;
    typedef pair<int,int> pii;
    typedef pair<int,double> pid;
    //    ll mod=1e9+7;
    ll mod=998244353;

    // Start Here

    const int MAX_VERTEX_NUM=150;

};

#endif // GLOBAL_H
