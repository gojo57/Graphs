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

void dfs(vvi &adj, vi &vis, vi &order, int node){ //topological sort
    vis[node] = 1;
    for(auto it: adj[node]){
        if(!vis[it]){
            dfs(adj, vis, order, it);
        }
    }
    order.pb(node);
}

void dfs2(vvi &adj, vi &vis, int node){
    vis[node] = 1;
    cout<<node<<" ";
    for(auto it: adj[node]){
        if(!vis[it]){
            dfs2(adj, vis, it);
        }
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m; cin>>n>>m;
    vvi adj(n+1), revAdj(n+1);
    while(m--){
        int u, v; cin>>u>>v;
        adj[u].pb(v);
        revAdj[v].pb(u);
    }
    vi vis(n+1, 0), order;

    // Step 1: Topological Sort (store the vertices according to their dfs finishing time)
    for(int i = 0; i<n; i++){
        if(!vis[i]){
            dfs(adj, vis, order, i);
        }
    }

    // Step 2: Reverse the graph (already done in revAdj)

    // Step 3: Do dfs on the reversed graph in the order int the order vector
    vis.assign(n+1, 0);
    char component = 'A';
    for(int i = order.size()-1; i>=0; i--){
        int node = order[i];
        if(!vis[node]){
            cout<<"Component "<<component++<<": ";
            // This is a new component
            dfs2(revAdj, vis, node);
            cout<<endl;
        }
    }


    return 0;
}