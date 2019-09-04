#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Defines and one-liners
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
template <typename T> inline T& back(vector<T> &vec) { return *(vec.end() - 1); }
template <typename T> inline void pop(vector<T> &vec) { return vec.erase(vec.end() - 1); }

// Scan, Debug, and other nonsense
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> void printArray(ostream& out,T* arr,int sz){out<<"[";for(int i=0;i<sz;i++){out<<arr[i]<<", "; } out<<"]";}
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out,type obj){out<<"("<<#propa<<"="<<obj. propa<<", "<<#propb<<"="<<obj. propb<<")";return out;}

void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f,R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

vector<int> cfactors;

template <int MAX>
struct PrimeSieve {
    bool isPrime[MAX]; vector<int> primes;
    PrimeSieve() {}
    inline void doWithFactor(int x) { cfactors.push_back(x); }
    // inline void doWithPrimeFactors(vector<pair<int, int>> &facts) { assert(("Needs to be implemented!", 0)); }
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
    void factor(int v, bool prime_factor) { // if prime_factor is true, it will only prime factor the number
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

        // if (!prime_factor)
            factorRec(1, 0, facts.size(), facts);
        // else
        //     doWithPrimeFactors(facts);
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

const int MPS = 32001;
int n;
PrimeSieve<MPS> sieve;
unordered_map<int, unordered_set<int>> save;

void rec(int left) {
    if (save.find(left) != save.end()) return;

    cfactors.clear();
    sieve.factor(left, false);

    vector<int> cfactors2 = vector<int>(cfactors.begin() + 1, cfactors.end());
    unordered_set<int> curSave;

    for (int factor : cfactors2) {
        rec(left / factor);
        for (int val : save[left / factor]) {
            curSave.insert(val + factor - 1);
        }
    }

    save[left] = curSave;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    sieve.calc();

    save[1] = {0};
    rec(n);

    auto ss = vector<int>(save[n].begin(), save[n].end());
    sort(ss.begin(), ss.end());
    
    cout << ss.size() << "\n";
    for (auto x : ss)
        cout << x << " ";
    cout << "\n";

    return 0;
}
