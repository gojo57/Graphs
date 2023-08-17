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

    int test; cin>>test;
    while(test--)
    {
        int n; cin>>n;
        vi a(n);
        for(int i = 1; i<=n; i+=2){
            for(int j = i; j<=n; j*=2){
                cout<<j<<" ";
            }
        }
        cout<<"\n";
    }
    return 0;
}