#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Defines
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f,R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

const int MAX = 200001, MV = 2000001;

template <int MAX>
struct PrimeSieve {
    bool isPrime[MAX]; vector<int> primes; int cnt[MAX];
    PrimeSieve() {}
    void doWithFactor(int x) { cnt[x]++; }
    void doWithPrimeFactors(vector<pair<int, int>> &facts) { assert(("Needs to be implemented!", 0)); }
    void calc() {
        memset(isPrime, true, sizeof isPrime);
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i < MAX; i++) {
            if (isPrime[i]) {
                for (int j = i + i; j < MAX; j += i)
                    isPrime[j] = false;
                primes.push_back(i);
            }
        }
    }
    void factor(int v, bool prime_factor) {
        int sqv = sqrt(v);
        vector<pair<int, int>> facts;

        for (int prime : primes) {
            if (prime > sqv)
                break;

            int cnt = 0;
            while (v % prime == 0) {
                v /= prime;
                cnt++;
            }

            if (cnt)
                facts.push_back(make_pair(prime, cnt));
        }
        if (v > 1)
            facts.push_back(make_pair(v, 1));
        
        if (!prime_factor)
            factorRec(1, 0, facts.size(), facts);
        else
            doWithPrimeFactors(facts);
    }
    void factorRec(int cur, int pos, int sz, vector<pair<int, int>> &facts) {
        if (pos == sz) {
            doWithFactor(cur);
            return;
        }
        
        for (int i = 0; i <= facts[pos].second; i++) {
            factorRec(cur, pos + 1, sz, facts);
            cur *= facts[pos].first;
        }
    }
};

int n, buf;
ll best = 0;
PrimeSieve<MV> sieve;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve.calc();
    scan(n);

    for (int i = 0; i < n; i++) {
        scan(buf);
        sieve.factor(buf, false);
    }

    for (int i = 1; i < MV; i++)
        if (sieve.cnt[i] > 1)
            best = max(best, (ll)sieve.cnt[i] * i);
    cout << best << "\n";

    return 0;
}