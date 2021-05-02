#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define P pair<ll, ll>
const ll mod = 1000000007; //1000000007 998244353 

ll n;
vector< vector<ll> > g;

void addEdge(ll u, ll v){
    g[u].push_back(v);
    g[v].push_back(u);
}

double genRandom(){
    return (double)rand() / RAND_MAX;
}

void genAlbertGraph(){
    addEdge(0, 1);

    for(int i = 2; i < n; i++){
        int totalDeg = 0;
        for(int j = 0; j < i; j++){
            totalDeg += g[j].size();
        }
        vector<double> samples = vector<double>(i);
        for(int j = 0; j < i; j++){
            samples[j] = g[j].size()/(double)totalDeg;
        }
        for(int j = 1; j < i; j++){
            samples[j] += samples[j-1];
        }
        double val = genRandom();
        for(int j = 0; j < i; j++ ){
            if(val <= samples[j]){
                addEdge(i, j);
                break;
            }
        }
    }
}

void printDegDistribution(){
    vector<ll> degs = vector<ll>(n, 0);
    for(int i = 0; i < n; i++){
        degs[g[i].size()]++;
    }
    cout << n << "\n";
    for(int i = 0; i < n; i++){
        cout << degs[i] << "\n";
    }
}

void divConquer(int l, int r){
    if(r - l == 1){
        addEdge(l, r);
        return;
    }
    if(r - l == 2){
        addEdge(l, l+1);
        addEdge(l, r);
        addEdge(l+1, r);
    }
    if(r-l <= 2){
        return;
    }
    ll mid = (r+l)/2;
    divConquer(l, mid);
    divConquer( mid + 1, r);
    addEdge(l, mid+1);
    addEdge(l+1, mid+1);
    addEdge(l, mid + 2);
}

void solve(){
    srand (time(NULL));
    n = 1000;
    g = vector<vector<ll>>(n); 
    divConquer(0, n-1);
    printDegDistribution();
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