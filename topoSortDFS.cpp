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

void dfs(int node, vi &vis, stack<int> &s, vvi &adj){
    vis[node] = 1;
    for(auto it: adj[node]){
        if(!vis[it]){
            dfs(it, vis, s, adj);
        }
    }
    s.push(node);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m; cin>>n>>m;
    vvi adj(n+1);
    for(int i=0;i<m;i++){
        int u,v; cin>>u>>v;
        adj[u].pb(v);
    }
    vi vis(n+1,0);
    stack<int> s;   
    for(int i = 0; i < n; i++){
        if(!vis[i]){
            dfs(i, vis, s, adj);
        }
    }

    vi ans;
    while(!s.empty()){
        ans.pb(s.top());
        s.pop();
    }
    for(auto it: ans){
        cout<<it<<" ";
    }

    return 0;
}