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
const int N = 2e5+5;

//****************************dsu****************************//
class Graph{
    int n, *rank, *parent;
public:
    Graph(int n){
        this->n = n;
        rank = new int[n+1];
        parent = new int[n+1];
        for(int i=1;i<=n;i++){
            rank[i] = 1;
            parent[i] = i;
        }
    }
    int find(int x){
        if(parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    int union_set(int x, int y){
        int s1 = find(x);
        int s2 = find(y);
        int rtval = rank[s1] * rank[s2];
        parent[s1] = s2;
        rank[s2] += rank[s1];
        return rtval;
    }
    ~Graph(){
        delete [] rank;
        delete [] parent;
    }
};


//****************************main****************************//
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m; cin >> n >> m;
    vector<pair<int, pii>> adj;
    mii mp;
    for(int i = 0; i<n-1; i++){
        int u, v, w; cin >> u >> v >> w;
        adj.pb({w, {u, v}});
    }
    sort(all(adj));
    Graph g(n);
    for(int i = 0; i<n-1; i++){
        int u = adj[i].second.first;
        int v = adj[i].second.second;
        int w = adj[i].first;
        mp[w] += g.union_set(u, v);
    }
    int prev = 0;
    vpii v;
    for(auto i: mp){
        v.pb({i.first, i.second + prev});
        prev += i.second;
    }
    while(m--){
        int k; cin >> k;
        pii tmp = {k, LLONG_MAX};
        auto it = upper_bound(all(v), tmp);
        if(it == v.begin()){
            cout << 0 << " ";
        }
        else{
            it--;
            cout << it->second << " ";
        }
    }

    return 0;
}
