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

bool dfs(int node, vector<int> adj[], vector<int> &vis, int parent, int color){
    vis[node] = color;
    for(auto it: adj[node]){
        if(vis[it]==0){
            if(dfs(it, adj, vis, node, 3-color)==false)
                return false;
        }
        else if(it!=parent && vis[it]==color)
            return false;
    }
    return true;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m; cin>>n>>m;
    vector<int> adj[n];
    vi vis(n, 0); // 0->not visited, 1-> visited, color 1, 2-> visited, color 2

    for(int i=0;i<m;i++){
        int u, v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    int color = 1;
    // bfs or dfs, by coloring the nodes at each step (current node has color 1, its neighbours have color 2, and so on)
    if(dfs(0, adj, vis, -1, color)){
        cout<<"Bipartite Graph\n";
    }
    else{
        cout<<"Not Bipartite Graph\n";
    }

    return 0;
}