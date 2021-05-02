#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define M 5100
#define P pair<ll, ll>
const ll mod = 998244353;

/************ Sieve Primes ***********/
ll spf[M]; 

    #ifndef ONLINE_JUDGE
        freopen("out.dat","w",stdout); freopen("in.dat","r",stdin);
    #endif


void sieve() 
{
    spf[1] = 1; 
    for (ll i=2; i<M; i++) 
        spf[i] = i; 
    for (ll i=4; i<M; i+=2) 
        spf[i] = 2; 
  
    for (ll i=3; i*i<M; i++) 
    { 
        if (spf[i] == i) 
        { 
            for (ll j=i*i; j<M; j+=i) 
                if (spf[j]==j) 
                    spf[j] = i; 
        } 
    } 
} 

vector<ll> getFactorization(ll x) 
{ 
    vector<ll> ret; 
    while (x != 1) 
    { 
        ret.push_back(spf[x]); 
        x = x / spf[x]; 
    } 
    return ret; 
}

/************* DSU ************/
vector<ll> par;

ll find(ll u){
    if(par[u] == u){
        return u;
    }
    return par[u] = find(par[u]);
}

void merge(ll u, ll v){
    u = find(u), v = find(v);
    if(u != v){
        par[u] = v;
    }
}


/********** Pow, Inverse Mod, nCr *********/
ll power(ll x, ll n){
    if(n == 0) return 1;
    ll ans = power(x, n/2);
    ans = (ans*ans)%mod;
    if(n%2 == 1) ans = (ans*x)%mod;
    return ans;
}

ll modInverse(ll x) {
    return power(x, mod - 2); 
}

vector<ll> fact;

ll nCrMod(ll n, ll r) { 
    if (r == 0) 
        return 1;   
    return (fact[n] * modInverse(fact[r]) % mod * modInverse(fact[n - r]) % mod) % mod; 
}

int main(){

}

/***************** matrix exponentiation *****************/

vector< vector<ll> > multi(vector<vector<ll>> &a, vector<vector<ll>> &b){
    vector<vector<ll>> ans(a.size(), vector<ll>(b[0].size(), 0));
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < b[0].size(); j++){
            for(int k = 0; k < a[0].size(); k++){
                ans[i][j] = (ans[i][j] + (a[i][k]*b[k][j])%mod )%mod;
            }
        }
    }
    return ans;
}

vector<vector<ll>> expo(vector<vector<ll>> x, ll n){
    if(n == 0){
        vector< vector<ll>> ret(x.size(), vector<ll>(x.size(), 0));
        for(int i = 0; i < x.size(); i++){
            ret[i][i] = 1;
        }
        return ret;
    }
    vector<vector<ll>> ans = expo(x, n/2);
    ans = multi(ans, ans);
    if(n%2 == 1)
        ans = multi(ans, x);
    return ans;
}

void printMat(vector<vector<ll>> &mat){
    for(int i = 0; i < mat.size(); i++){
        for(int j = 0; j < mat[i].size(); j++){
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }
}

