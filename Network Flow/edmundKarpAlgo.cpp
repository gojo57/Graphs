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

bool bfs(vvi &residualGraph, int source, int sink, int n, vi &parent){
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    bool foundAugmentedPath = false;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v=0;v<n;v++){
            if(!visited[v] && residualGraph[u][v] > 0){
                q.push(v);
                parent[v] = u;
                visited[v] = true;
                if(v == sink){
                    foundAugmentedPath = true;
                    break;
                }
            }
        }
    }
    return foundAugmentedPath;
}

void printAugmentedPaths(vvi &augmentedPaths){
    for(auto path: augmentedPaths){
        for(auto edge: path){
            cout<<edge<<", ";
        }
        cout<<endl;
    }
}

int maxFlow(vvi &capacity, int source, int sink, int v){
    vvi residualGraph(v, vi(v, 0));
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            residualGraph[i][j] = capacity[i][j];
        }
    }
    vi parent(v, 0);
    vvi augmentedPaths;
    int maxFlow = 0;
    while(bfs(residualGraph, source, sink, v, parent)){
        vi currentAugmentedPath;
        int pathFlow = INT_MAX;
        int v = sink;
        while(v != source){
            currentAugmentedPath.pb(v);
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
            v = u;
        }
        currentAugmentedPath.pb(source);
        reverse(all(currentAugmentedPath)); 
        augmentedPaths.pb(currentAugmentedPath);
        maxFlow += pathFlow;

        v = sink;
        while(v != source){
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
            // capacity[u][v] -= pathFlow;
            // capacity[v][u] += pathFlow;
            v = u;
        }
    }
    printAugmentedPaths(augmentedPaths);
    return maxFlow;
}

//****************************main****************************//
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int v, e; cin>>v>>e;
    vvi capacity(v, vi(v, 0));
    for(int i=0;i<e;i++){
        int u, v, c; cin>>u>>v>>c;
        capacity[u][v] = c;
    }
    cout<<maxFlow(capacity, 0, 1, v)<<endl;
    return 0;
}
