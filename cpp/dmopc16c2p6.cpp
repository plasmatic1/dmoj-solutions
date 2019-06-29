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

struct folder {
    string name;
    set<string> files;
    map<string, folder*> folders;
    folder(string name0) : name(name0) {}
};

string NOS = "";
folder *root = nullptr, *fake = nullptr;
int n, bl;
string bs;
vector<string> line, tmpSpl;
vector<folder*> path;

bool isFile(string &s) {
    for (char ch : s)
        if (ch == '.')
            return true;
    return false;
}

void split(string &s, vector<string> &v, char delim) {
    v.clear();
    int lastSp = -1;
    for (int i = 0, len = s.length(); i < len; i++) {
        if (s[i] == delim) {
            v.push_back(s.substr(lastSp + 1, i - lastSp - 1));
            lastSp = i;
        }
    }
    v.push_back(s.substr(lastSp + 1));
}

string replace(const string &s, string find, string repl) {
    int fLen = find.length(), sLen = s.length();
    string ret = "";
    for (int i = 0; i < sLen; i++) {
        if (s.substr(i, fLen) == find) {
            ret += repl;
            i += fLen - 1; 
        }
        else
            ret += s[i];
    }
    return ret;
}

void readLine() {
    getline(cin, bs);
    split(bs, line, ' ');
}

bool matchDirect(const string s, string matcher) {
    if (s.length() != matcher.length()) return false;
    for (int i = 0, len = s.length(); i < len; i++) {
        if (matcher[i] == ']') {
            if (s[i] != '.')
                return false;
        }
        else if (matcher[i] != '.' && s[i] != matcher[i])
            return false;
    }
    return true;
}

bool matchRegex(const string s, string reg) {
    reg = replace(reg, "\\.", "]");
    int regLen = reg.length(), sLen = s.length();
    if (reg[0] == '^' && reg[regLen - 1] == '$')
        return matchDirect(s, reg.substr(1, regLen - 2));
    else if (reg[0] == '^') {
        if (regLen > sLen)
            return false;
        return matchDirect(s.substr(0, regLen - 1), reg.substr(1));
    }
    else if (reg[regLen - 1] == '$') {
        if (regLen > sLen)
            return false;
        return matchDirect(s.substr(sLen - regLen + 1), reg.substr(0, regLen - 1));
    }
    else {
        int sLen = s.length();
        if (sLen < regLen) return 0;
        for (int i = 0; i <= sLen - regLen; i++)
            if (matchDirect(s.substr(i, regLen), reg))
                return true;
        return false;
    }
}

bool printFolder(folder *f, string &regex, bool useRegex) {
    tmpSpl.clear();
    for (auto &s : f->files)
        if (!useRegex || matchRegex(s, regex))
            tmpSpl.push_back(s);
    for (auto &s : f->folders)
        if (!useRegex || matchRegex(s.second->name, regex))
            tmpSpl.push_back(s.second->name);
    sort(tmpSpl.begin(), tmpSpl.end());
    for (auto &s : tmpSpl)
        cout << s << "\n";
    return tmpSpl.size();
}

void R_listFolder(folder *f, vector<string> &names, string &regex, bool useRegex) {
    for (auto &s : f->files)
        if (!useRegex || matchRegex(s, regex))
            names.push_back(s);
    for (auto &s : f->folders) {
        if (!useRegex || matchRegex(s.second->name, regex))
            names.push_back(s.second->name);
        R_listFolder(s.second, names, regex, useRegex);
    }
}

bool R_printFolder(folder *f, string &regex, bool useRegex) {
    tmpSpl.clear();
    R_listFolder(f, tmpSpl, regex, useRegex);
    sort(tmpSpl.begin(), tmpSpl.end());
    for (auto &s : tmpSpl)
        cout << s << "\n";
    return tmpSpl.size();
}

inline void ppush(folder *f) { path.push_back(f); }
inline void ppop() { path.pop_back(); }
inline void pclear() { path.clear(); ppush(root); }
inline folder* ptop() { return path.back(); }

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);
    root = new folder("this should not print");

    int lastLay = -1;
    ppush(root);
    for (int i = 0; i < n; i++) {
        scan(bl, bs);

        assert(bl - lastLay <= 1);

        int dif = lastLay - bl;
        while (dif-- > -1)
            ppop();
        
        if (isFile(bs)) {
            ptop()->files.insert(bs);
            ppush(fake);
        }
        else {
            folder *cur = new folder(bs);
            ptop()->folders[bs] = cur;
            ppush(cur);
        }

        lastLay = bl;
    }

    pclear();
    do {
        readLine();
        // debug(line); cout.flush();

        if (line[0] == "ls") {
            if (line.size() > (size_t)1) {
                if (line[1] == "-r") {
                    if (line.size() > (size_t)2) {
                        assert(line[2] == "|" && line[3] == "grep");
                        string regex = line[4];
                        if (!R_printFolder(ptop(), regex, true)) cout << "\n";
                        cout << "\n";
                    }
                    else {
                        if (!R_printFolder(ptop(), NOS, false)) cout << "\n";
                        cout << "\n";
                    }
                }
                else if (line[1] == "|") {
                    assert(line[2] == "grep");
                    string regex = line[3];
                    if (!printFolder(ptop(), regex, true)) cout << "\n";
                    cout << "\n";
                }
            }
            else {
                if (!printFolder(ptop(), NOS, false)) cout << "\n";
                cout << "\n";
            }
        }
        else if (line[0] == "cd") {
            string &path = line[1];
            if (path[0] == '~' && path[1] == '/') {
                pclear();
                path = path.substr(2);
            }
            if (path != "") {
                split(path, tmpSpl, '/');
                for (string &s : tmpSpl) {
                    if (s != "")
                        ppush(ptop()->folders[s]);
                }
            }
        }
        else if (line[0] == "grep") {
            assert(0); // This should not be possible
        }
        else if (line[0] == "mkdir") {
            folder* newF = new folder(line[1]);
            ptop()->folders[line[1]] = newF;
        }
        else if (line[0] == "touch")
            ptop()->files.insert(line[1]);
        else if (line[0] == "pwd") {
            cout << "~/";
            for (int i = 1, sz = path.size(); i < sz; i++)
                cout << path[i]->name << '/';
            cout << "\n\n";
        }
    } while (line[0] != "exit");

    return 0;
}