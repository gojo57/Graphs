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

bool dfs(int node, vvi &adj, vi &vis, vi &dfsVis){
    vis[node] = 1;
    dfsVis[node] = 1;
    for(auto it: adj[node]){
        if(!vis[it]){
            if(dfs(it, adj, vis, dfsVis)) return true;
        }
        else if(dfsVis[it]) return true;
    }
    dfsVis[node] = 0;
    return false;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m; cin>>n>>m;
    vvi adj(n+1);
    vi vis(n+1, 0), dfsVis(n+1, 0);
    for(int i=0; i<m; i++){
        int u, v; cin>>u>>v;
        adj[u].pb(v);
    }
    int cycle = 0;
    for(int i = 0; i<n; i++){
        if(!vis[i]){
            if(dfs(i, adj, vis, dfsVis)){
                cycle = 1;
                break;
            }
        }
    }
    if(cycle) cout<<"Cycle is present";
    else cout<<"Cycle is not present";

    return 0;
}