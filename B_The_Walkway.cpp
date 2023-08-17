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
vector<int> a(200005);

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int test; cin>>test;
    while(test--)
    {
        int n, m, d; cin>>n>>m>>d;
        for(int i=1;i<=m;i++) cin>>a[i];
        a[0]=1;
		a[m+1]=n+1;
		int tot=0;
		for(int i=0;i<=m;i++){
			tot+=(a[i+1]-a[i]+d-1)/d;
		}
        int temp = -1, ans = 1;
        for(int i = 1; i<=m; i++){
            int dec = (a[i]-a[i-1]+d-1)/d + (a[i+1]-a[i]+d-1)/d - (a[i+1]-a[i-1]+d-1)/d;
            if(dec > temp){
                temp = dec;
                ans = 1;
            }
            else if(dec == temp){
                ans++;
            }
        }
        cout<<tot-temp<<" "<<ans<<"\n";
    }
    return 0;
}