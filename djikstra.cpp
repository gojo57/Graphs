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

    void djikstra(T src){
        map<T, int> dist;
        for(auto node: adjList){
            dist[node.first] = INT_MAX;
        }
        set<pair<int, T>> s;
        dist[src] = 0;
        s.insert({0, src});
        while(!s.empty()){
            auto p = *(s.begin());
            T node = p.second;
            int nodeDist = p.first;
            s.erase(s.begin());
            for(auto child: adjList[node]){
                if(nodeDist + child.second < dist[child.first]){
                    auto f = s.find({dist[child.first], child.first});
                    if(f != s.end()){
                        s.erase(f);
                    }
                    dist[child.first] = nodeDist + child.second;
                    s.insert({dist[child.first], child.first});
                }
            }
        }
        for(auto node: dist){
            cout<<node.first<<" is located at distance of "<<node.second<<endl;
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
    g.addEdge(2, 3, 1);
    g.addEdge(3, 4, 2);
    g.addEdge(1, 4, 7);
    g.djikstra(1);

    return 0;
}