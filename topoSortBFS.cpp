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
    vi indegree(n+1,0);
    for(int i=0;i<n;i++){
        for(auto x:adj[i]){
            indegree[x]++;
        }
    }

    queue<int> q;
    for(int i=0;i<n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    vi ans;
    while(!q.empty()){
        int node = q.front();
        q.pop();
        ans.pb(node);
        for(auto x:adj[node]){
            indegree[x]--;
            if(indegree[x]==0){
                q.push(x);
            }
        }
    }
    for(auto x:ans){
        cout<<x<<" ";
    }

    return 0;
}