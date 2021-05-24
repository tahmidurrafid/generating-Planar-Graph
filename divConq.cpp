#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define P pair<ll, ll>
const ll mod = 1000000007; //1000000007 998244353 

ll n;
vector< set<ll> > g;
vector< bool > special;

vector< vector<ll> > circles;
vector< bool > visited;

void addEdge(ll u, ll v){
    g[u].insert(v);
    g[v].insert(u);
}

double genRandom(){
    return (double)rand() / RAND_MAX;
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

void addCircleEdge(ll u, ll v){
    circles[u].push_back(v);
    circles[v].push_back(u);
}

void removeCircleEdge(ll u, ll v){
    auto it = find(circles[u].begin(), circles[u].end(), v);
    if(it != circles[u].end()){
        circles[u].erase(it);
    }
    it = find(circles[v].begin(), circles[v].end(), u);
    if(it != circles[v].end()){
        circles[v].erase(it);
    }
}

ll getNext(ll cur, ll notThis){
    vector<ll> lis = circles[cur];
    if(lis[0] == notThis)
        return lis[1];
    return lis[0];
}

void printCircle(ll l, ll r){
    ll sp = l;
    for(int i = l ; i <= r; i++){
        if(circles[i].size() == 2){
            sp = i;
            break;
        }
    }
    ll temp;
    ll ts = circles[sp][0], tp = sp;
    cout << l << "++" << r << "\n";
    cout << sp << "_";
    while(ts != sp){
        cout << ts << "_";
        temp = ts;
        ts = getNext(ts, tp);
        tp = temp;
    }
    cout << "\n";
}

void divConquer(int l, int r){
    if(r - l == 1){
        addEdge(l, r);
        addCircleEdge(l, r);
        return;
    }
    if(r - l == 2){
        addEdge(l, l+1);
        addEdge(l, r);
        addEdge(l+1, r);
        addCircleEdge(l, l+1);
        addCircleEdge(l, r);
        addCircleEdge(l+1, r);
    }

    if(r-l <= 2){
        return;
    }

    ll mid = (r+l)/2;
    divConquer(l, mid);
    divConquer( mid + 1, r);
    ll x1 = l;
    if(mid - l > 1)
        while(circles[x1].size() != 2) x1++;
    ll x2 = circles[x1][0];
    ll y1 = mid+1;
    if(r - mid > 2)
        while(circles[y1].size() != 2) y1++;    
    ll y2 = circles[y1][0];
    addEdge(x1, y1);
    addEdge(x1, y2);
    addEdge(x2, y2);
    if(mid - l != 1){
        removeCircleEdge(x1, x2);
    }
    if(r - mid != 2){
        removeCircleEdge(y1, y2);
    }
    addCircleEdge(x1, y1);
    addCircleEdge(x2, y2);


    ll sp = l;
    ll temp;
    ll ts = circles[l][0], tp = l;

    sp = -1;
    for(int i = l; i <= r; i++){
        if(special[i] && circles[i].size()){
            sp = i;
            break;
        }
    }

    if(sp != -1){
        ll cur = circles[sp][0];
        ll par = sp;
        ll revCur, revPar;
        ll coun = 0;
        while(cur != sp){
            if(g[sp].count(cur) == 0){

                revCur = par;
                revPar = cur;
                while(revPar != sp && circles[revCur].size()){
                    removeCircleEdge(revCur, revPar);
                    if(circles[revCur].size() == 0)
                        break;
                    temp = revCur;
                    revCur = getNext(revCur, revPar);
                    revPar = temp;
                }
                addEdge(sp, cur);
                addCircleEdge(sp, cur);

            }
            temp = cur;
            cur = getNext(cur, par);
            par = temp;
        }
    }
}

void solve(){
    srand (time(NULL));
    n = 1000000;
    g = vector<set<ll>>(n);
    special = vector<bool>(n, false);
    circles = vector<vector<ll>>(n); 
    visited = vector<bool> (n, false);
    double prob = .05;
    for(int i = 0; i < n; i++){
        if(genRandom() <= prob){
            special[i] = true;
            // cout << i << " - ";
        }
    }
    // for(int i = 0; i < n; i+= 18){
    //     special[i] = true;
    // }

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