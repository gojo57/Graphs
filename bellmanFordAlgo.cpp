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

template<typename T>
class Graph{
    map<T, list<pair<T, int>>> adjList;
public:
    void addEdge(T u, T v, int dist, bool bidir = true){
        adjList[u].pb({v, dist});
        if(bidir){
            adjList[v].pb({u, dist});
        }
    }

    void printAdjList(){
        for(auto node: adjList){
            cout<<node.first<<"->";
            for(auto child: node.second){
                cout<<"("<<child.first<<","<<child.second<<")";
            }
            cout<<endl;
        }
    }

    void bellmanFord(T src){
        map<T, int> dist;
        for(auto node: adjList){
            dist[node.first] = INT_MAX;
        }
        dist[src] = 0;
        for(int i = 0; i < adjList.size() - 1; i++){
            for(auto node: adjList){
                for(auto child: node.second){
                    if(dist[node.first] + child.second < dist[child.first]){
                        dist[child.first] = dist[node.first] + child.second;
                    }
                }
            }
        }
        for(auto node: adjList){
            for(auto child: node.second){
                if(dist[node.first] + child.second < dist[child.first]){
                    cout<<"Negative weight cycle detected"<<endl;
                    return;
                }
            }
        }
        for(auto node: dist){
            cout<<node.first<<" "<<node.second<<endl;
        }
    }
};

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Graph<int> g;
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 4);
    // g.addEdge(2, 3, -3);
    g.addEdge(3, 4, -2, 0);
    g.addEdge(1, 4, 7);
    g.bellmanFord(1);

    return 0;
}