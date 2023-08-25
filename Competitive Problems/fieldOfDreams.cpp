// Field of dreams

// --> A field is represented by a 2-D grid of size NxM
// --> Each cell in the grid is either a g cell or a d cell, where g denotes grass and d denotes dirt
// --> Two cells are said to be connected if they share an edge
// --> The grid is said to be connected if all the g cells can be traversed without passing through d cells. Otherwise, the grid is said to be disconnected.
// Write a program to find the minimum number of g cells that must be replaced by d cells such that grid is disconnected. If the grid is initially disconnected print 0.

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

string arr[401];
vvi adj(N);
map<pii, int> cd;
int cur = 0, one = 0, comp = 0, m, n;
vi vis(n+1, 0);

void add_edges(){
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            if(arr[i][j] == 'g'){
                if(i+1<n && arr[i+1][j] == 'g'){
                    adj[cd[{i, j}]].pb(cd[{i+1, j}]);
                }
                if(i && arr[i-1][j] == 'g'){
                    adj[cd[{i, j}]].pb(cd[{i-1, j}]);
                }
                if(j+1<m && arr[i][j+1] == 'g'){
                    adj[cd[{i, j}]].pb(cd[{i, j+1}]);
                }
                if(j && arr[i][j-1] == 'g'){
                    adj[cd[{i, j}]].pb(cd[{i, j-1}]);
                }
            }
        }
    }
    n = cur;
}

int disc[N], low[N], tme;
set<int> art_pts;
int timer;

void dfs(int node, int par = -1){
    disc[node] = low[node] = tme++;
    int no_child = 0;
    for(int child: adj[node]){
        if(!disc[child]){
            dfs(child, node);
            no_child++;
            low[node] = min(low[node], low[child]);
            // articulation point
            if(par!=0 && low[child] >= disc[node]){
                art_pts.insert(node);
            }
        }
        else if(child != par){
            // back edge or a cycle is found
            low[node] = min(low[node], disc[child]);
        }
    }
    // root node is an articulation point if it has more than 1 child, hence a separate case for the root node
    if(par == 0 && no_child > 1){
        art_pts.insert(node);
    }
    return;
}

void dfs2(int node){
    vis[node] = 1;
    for(int child: adj[node]){
        if(!vis[child]){
            dfs2(child);
        }
    }
}

void find_cutpoints(){
    for(int i=0; i<n; i++){
        if(!vis[i]){
            comp++;
            dfs2(i);
        }
    }
}

//****************************main****************************//
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin>>n>>m;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }

    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            if(arr[i][j] == 'g'){
                cd[{i, j}] = cur++;
            }
        }
    }
    add_edges();

    if(!n){
        cout<<0<<"\n";
    }
    else if(n==1){
        cout<<"1\n";
    }
    else if(n==2){
        if(adj[0].size()){
            cout<<"2\n";
        }
        else{
            cout<<"0\n";
        }
    }
    else{
        dfs(0);
        find_cutpoints();
        one = art_pts.size()>0;
        if(comp>1){
            cout<<"0\n";
        }
        else if(one==1){
            cout<<"1\n";
        }
        else{
            cout<<"2\n";
        }
    }

    return 0;
}
