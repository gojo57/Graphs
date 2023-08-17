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

vvi adj(100005);
void bfs(int src, int n, int &ans){
    vi dist(n+1, INT_MAX);
    queue<int> q;
    q.push(src);
    dist[src] = 0;
    while(!q.empty()){
        int node = q.front();
        q.pop();
        for(auto nbr: adj[node]){
            if(dist[nbr]==INT_MAX){
                dist[nbr] = dist[node] + 1;
                q.push(nbr);
            }
            else if(dist[nbr]>=dist[node]){
                ans = min(ans, dist[nbr] + dist[node] + 1);
            }
        }
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m; cin>>n>>m;
    for(int i=0;i<m;i++){
        int u, v; cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    int ans = n+1;
    for(int i = 1; i<=n; i++){
        bfs(i, n, ans);
    }
    if(ans==n+1){
        cout<<"Np cycle in graph!\n";
    }
    else{
        cout<<"Shortest cycle has length: "<<ans<<"\n";
    }
    return 0;
}