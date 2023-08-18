#include<bits/stdc++.h>
#define pb push_back
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define ones(x) __builtin_popcountll(x)
#define int long long
#define pii pair<int,int>
#define mii map<int,int>
#define vi vector<int>
#define vvi vector<vector<int>>
#define vpii vector<pair<int, int>>
using namespace std;
const int mod = 1e9+7;

vvi floydWarshall(vvi graph){
    int n = graph.size();
    vvi dist(n, vi(n, INT_MAX));
    for(int i = 0; i < n; i++){
        dist[i][i] = 0;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < graph[i].size(); j++){
            if(graph[i][j] != INT_MAX){
                dist[i][j] = graph[i][j];
            }
        }
    }
    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    return dist;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vvi graph = {
        {0, INT_MAX, -2, INT_MAX},
        {4, 0, 3, INT_MAX},
        {INT_MAX, INT_MAX, 0, 2},
        {INT_MAX, -1, INT_MAX, 0}
    };

    vvi dist = floydWarshall(graph);
    for(int i = 0; i < dist.size(); i++){
        for(int j = 0; j < dist[i].size(); j++){
            cout<<dist[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}