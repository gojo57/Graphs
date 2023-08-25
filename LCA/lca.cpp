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

////****************************segtree//****************************//

int lazy[4*N+1];
int segTree[4*N+1];
int a[N] = {0};

void build(int v, int tl, int tr)
{
    if(tl==tr){
        segTree[v] = a[tl];
    }
    else{
        int tm = (tl+tr)/2;
        build(2*v,tl,tm);
        build(2*v+1,tm+1,tr);
        // segTree[v] = segTree[2*v] + segTree[2*v+1];
    }
}

void updateRangeLazy(int ss, int se, int l, int r, int inc, int node){  // O(logn)
    //First step - Never go down if you have lazy value at node, first resolve it
    if(lazy[node]!=0){
        segTree[node] = lazy[node];
        //if not a leaf node
        if(ss!=se){ // pass the lazy value to children
            lazy[2*node] = lazy[node];
            lazy[2*node+1] = lazy[node];
        }
        lazy[node] = 0;
    }

    //Out of bounds
    if(l>se || r<ss){
        return;
    }

    //Complete Overlap
    if(ss>=l && se<=r){
        segTree[node] = inc;
        //Pass the lazy value to children
        if(ss!=se){
            lazy[2*node] = inc;
            lazy[2*node+1] = inc;
        }
        return;
    }

    //Partial Overlap
    int mid = (ss+se)/2;
    updateRangeLazy(ss, mid, l, r, inc, 2*node);
    updateRangeLazy(mid+1, se, l, r, inc, 2*node+1);

    segTree[node] = segTree[2*node]+ segTree[2*node+1];
    return;
}

int queryLazy(int *tree, int ss, int se, int qs, int qe, int index){  // O(logn)
    //First step - Never go down if you have lazy value at node, first resolve it
    if(lazy[index]!=0){
        tree[index] = lazy[index];
        //if not a leaf node
        if(ss!=se){ // pass the lazy value to children
            lazy[2*index] = lazy[index];
            lazy[2*index+1] = lazy[index];
        }
        lazy[index] = 0;
    }

    //Complete Overlap
    if(ss>=qs && se<=qe){
        return tree[index];
    }

    //No Overlap
    if(qe<ss || qs>se){
        return INT_MAX;
    }

    //Partial Overlap
    int mid = (ss+se)/2;
    int left = queryLazy(tree, ss, mid, qs, qe, 2*index);
    int right = queryLazy(tree, mid+1, se, qs, qe, 2*index+1);

    return min(left, right); 
}

void printUpdatedArray(int node, int tl, int tr) {
    if(lazy[node]!=0){
        segTree[node] = lazy[node];
        //if not a leaf node
        if(tl!=tr){ // pass the lazy value to children
            lazy[2*node] = lazy[node];
            lazy[2*node+1] = lazy[node];
        }
        lazy[node] = 0;
    }
    if (tl == tr) {
        cout << segTree[node] << "\n";
    } else {
        int tm = (tl + tr) / 2;
        printUpdatedArray(node * 2, tl, tm);
        printUpdatedArray(node * 2 + 1, tm + 1, tr);
    }
}

//****************************dsu****************************//
class Graph{
    int n, *rank, *parent;
public:
    Graph(int n){
        this->n = n;
        rank = new int[n];
        parent = new int[n];
        for(int i=0;i<n;i++){
            rank[i] = 1;
            parent[i] = i;
        }
    }
    int find(int x){
        if(parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    void union_set(int x, int y){
        x = find(x);
        y = find(y);
        if(x != y){
            if(rank[x] < rank[y]) swap(x, y);
            parent[y] = x;
            rank[x] += rank[y];
        }
    }
    int connected_components(){
        int ans = 0;
        for(int i=0;i<n;i++){
            if(parent[i] == i) ans++;
        }
        return ans;
    }
    ~Graph(){
        delete [] rank;
        delete [] parent;
    }
};

const int M = 22;
int parent[N], dep[N], tin[N], tout[N], timer;
int Par[N][M]; // Par[i][j] = 2^j th parent of i

void dfs(int node, int par, vvi &graph){ // O(n)
    tin[node] = ++timer;
    parent[node] = par;
    for(auto child: graph[node]){
        if(child != par){
            dep[child] = dep[node] + 1;
            dfs(child, node, graph);
        }
    }
    tout[node] = timer;
    return;
}

int lca_brute(int u, int v){
    // if u is at a lower level than v, swap them
    if(dep[u] < dep[v]) swap(u, v);
    // always depth of u > depth of v
    int diff = dep[u] - dep[v];
    while(dep[u] > dep[v]){
        u = parent[u];
    }
    // now both are at same level
    while(u != v){
        u = parent[u];
        v = parent[v];
    }
    return u;
}

void cal_sparse_table(int node, int parent, vvi &graph){ // O(n)*M
    Par[node][0] = parent;
    for(int i=1;i<M;i++){
        Par[node][i] = Par[Par[node][i-1]][i-1];
    }
    for(auto child: graph[node]){
        if(child != parent){
            cal_sparse_table(child, node, graph);
        }
    }
}

int LCA_using_depth(int u, int v){  // O(logn) ~= O(M)
    if(u==v) return u;
    if(dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    for(int i=M-1;i>=0;i--){
        if(diff & (1<<i)){
            u = Par[u][i];
        }
    }
    // now both are at same level
    if(u == v) return u; // if v is ancestor of u
    for(int i=M-1;i>=0;i--){
        if(Par[u][i] != Par[v][i]){
            u = Par[u][i];
            v = Par[v][i];
        }
    }
    // now both are just below the lca
    return Par[u][0];
}

int LCA_using_tin_tout(int u, int v){  // O(1)
    // if u is ancestor of v
    if(tin[u] <= tin[v] && tout[u] >= tout[v]) return u;
    // if v is ancestor of u
    if(tin[v] <= tin[u] && tout[v] >= tout[u]) return v;
    for(int i=M-1;i>=0;i--){
        if(tin[Par[u][i]] > tin[v] || tout[Par[u][i]] < tout[v]){
            u = Par[u][i];
        }
    }
    return Par[u][0];
}

//****************************main****************************//
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vvi graph(N);
    int n; cin>>n;
    for(int i=0;i<n-1;i++){
        int u, v; cin>>u>>v;
        graph[u].pb(v);
        graph[v].pb(u);
    }
    // root as 1
    // for(int i = 1; i<=n; i++){
    //     cout<<i<<" "<<parent[i]<<" "<<dep[i]<<"\n";
    // }
    // cout<<lca_brute(9, 9)<<"\n";
    timer = 0;
    tin[0] = 0; // universal parent
    tout[0] = n+1; // universal parent
    dfs(1, 0, graph);
    cal_sparse_table(1, 0, graph);

    cout<<LCA_using_depth(9, 15)<<"\n";
    cout<<LCA_using_tin_tout(9, 15)<<"\n";

    return 0;
}
