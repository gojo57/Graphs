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

void bfs(int src, vector<int> &dist, vector<vector<int>> &adj)
{
    queue<int> q;

    for(auto v: adj)
    {
        int node = v[0];
        dist[node] = INT_MAX;
    }
    q.push(src);
    dist[src] = 0;

    while(!q.empty())
    {
        int node = q.front();
        q.pop();
        for(auto it: adj[node])
        {
            if(dist[it] == INT_MAX)
            {
                dist[it] = dist[node] + 1;
                q.push(it);
            }
        }
    }

    // print the distance of all nodes from src
    for(auto it: adj){
        int node = it[0];
        int d = dist[node];
        cout << "Node " << node << " is at distance " << d << " from src\n";
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vvi adj;
    vi dist(6, 0);
    adj.pb({1, 2});
    adj.pb({0, 2});
    adj.pb({1, 3});
    adj.pb({0, 2, 4});
    adj.pb({3, 5});
    adj.pb({4});
    bfs(0, dist, adj);
    return 0;
}