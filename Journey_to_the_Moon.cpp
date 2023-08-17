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

int dfs(int u, vvi &adj, vi &vis){
    vis[u] = 1;
    int tot = 1;
    for(auto v: adj[u]){
        if(!vis[v]){
            tot += dfs(v, adj, vis);
        }
    }
    return tot;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, p; cin>>n>>p;
    vvi adj(n+1);
    vi vis(n+1, 0);
    for(int i=0;i<p;i++){
        int u, v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vi sz;
    for(int i = 0; i<n; i++){
        if(!vis[i]){
            sz.pb(dfs(i, adj, vis));
        }
    }
    int ans = 0, sum = 0;
    for(int i = 0; i<sz.size(); i++){
        ans += sum*sz[i];
        sum += sz[i];
    }
    cout<<ans<<endl;
    return 0;
}