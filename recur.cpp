#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define P pair<ll, ll>
const ll mod = 1000000007; //1000000007 998244353 

vector<ll> dp;



void solve(){
    dp = vector<ll>(100000);
    dp[2] = 1;
    dp[3] = 3;

}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("out.dat","w",stdout); freopen("in.dat","r",stdin);
    #endif
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll t = 1;
    // cin >> t;
    while(t--) 
        solve();
    return 0;
}