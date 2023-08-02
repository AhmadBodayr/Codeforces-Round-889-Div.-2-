#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll; 					
typedef unsigned long long ull; 
typedef long double ld;
#define inf 1000000000000000005
//////////////////Library///////////////////////////////////
struct Trie {
	Trie* child[26];
	bool isLeaf;

	Trie() {
		memset(child, 0, sizeof(child));
		isLeaf = 0;
	}

	void insert(char* str) {
		if(*str == '\0') isLeaf = 1;
		else {
			int curr = *str - '0';
			if(child[curr] == 0) child[curr] = new Trie();
			child[curr] -> insert(str + 1);
		}
	} 

	bool wordExist(char* str) {
		if(*str == '\0') return isLeaf;
		int curr = *str - '0';
		if(child[curr] == 0) return false;
		return child[curr] -> wordExist(str + 1); 
	}

	bool prefExist(char* str) {
		if(*str == '\0') return true;
		int curr = *str - '0';
		if(child[curr] == 0) return false;
		return child[curr] -> wordExist(str + 1);
	}
};

class DSU {
private:
    vector<int> root;
    vector<int> rank;
public:
    DSU(int sz) : root(sz), rank(sz) {
        for (int i = 0; i < sz; i++) {
            root[i] = i;
            rank[i] = 1;
        }
    }

    int find(int x) {
        if (x == root[x]) {
            return x;
        }
        return root[x] = find(root[x]);
    }

    void unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                root[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                root[rootX] = rootY;
            } else {
                root[rootY] = rootX;
                rank[rootX] += 1;
            }
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

/////////////////////////////////End library/////////////////////////////////////
ll t, n;
vector<pair<ll, ll>> out;
vector<ll> v;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL); 	

	// #ifndef ONLINE_JUDGDE
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);	
	// #endif
	///////////////////////////////////////////////////////////////
	cin >> t;
	while(t--) {
		cin >> n;
		out.clear();
		v.resize(n);
		ll maxIndex = 0, minIndex = 0;
		ll neg = 0, pos = 0;
		for(ll i = 0; i < n; i++) {
			cin >> v[i];
			if(v[i] > 0) pos++;
			if(v[i] < 0) neg++;
			if(v[i] > v[maxIndex]) maxIndex = i;
			if(v[i] < v[minIndex]) minIndex = i;
		}
		if(!neg) {
			cout << n - 1 << endl;
			for(ll i = 1; i < n; i++) {
				cout << i + 1 << " " << i << endl;
			}
			continue;
		}
		if(!pos) {
			cout << n - 1 << endl;
			for(ll i = n - 2; i >= 0; i--) {
				cout << i + 1 << " " << i + 2 << endl;
			}
			continue;
		} 
		if(max(pos, neg) >= 13) {
			vector<pair<ll, ll>> outPos, outNeg;
			vector<ll> vPos = v;
			vector<ll> vNeg = v;
			while(vPos[maxIndex] < 20) {
				vPos[maxIndex] *= 2;
				outPos.push_back({maxIndex + 1, maxIndex + 1});
			}
			while(vPos[0] < 0) {
				vPos[0] += vPos[maxIndex];
				outPos.push_back({1, maxIndex + 1});
			}
			for(ll i = 1; i < n; i++) {
				if(vPos[i] >= 0)  {
					vPos[i] += vPos[i - 1];
					outPos.push_back({i + 1 , i});
				} else {
					while(vPos[i] < 0) {
						vPos[i] += vPos[maxIndex];
						outPos.push_back({i + 1, maxIndex + 1});
					}
					if(vPos[i] < vPos[i - 1]) {
						vPos[i] += vPos[i - 1];
						outPos.push_back({i + 1, i});
					}
				}
			}
			if((ll) outPos.size() <= 31) {
				cout << (ll) outPos.size() << endl;
				for(ll i = 0; i < (ll) outPos.size(); i++) {
					cout << outPos[i].first << " " << outPos[i].second << endl;
				}
				continue;
			} 
			while(vNeg[minIndex] > -20) {
				vNeg[minIndex] *= 2;
				outNeg.push_back({minIndex + 1, minIndex + 1});
			}
			while(vNeg[n - 1] > 0) {
				vNeg[n - 1] += vNeg[minIndex];
				outNeg.push_back({n, minIndex + 1});
			}
			for(ll i = n - 2; i >= 0; i--) {
				if(vNeg[i] <= 0 && vNeg[i] > vNeg[i + 1]) {
					vNeg[i] += vNeg[i + 1];
					outNeg.push_back({i + 1, i + 2});
				} else if(vNeg[i] <= 0) {
					vNeg[i] += vNeg[i + 1];
					outNeg.push_back({i + 1, i + 2});
				} else {
					while(vNeg[i] > 0) {
						vNeg[i] += vNeg[minIndex];
						outNeg.push_back({i + 1, minIndex + 1});
					}
					if(vNeg[i] > vNeg[i + 1]) {
						vNeg[i] += vNeg[i + 1];
						outNeg.push_back({i + 1, i + 2});
					}
				}
			}
			cout << (ll) outNeg.size() << endl;
			for(ll i = 0; i < (ll) outNeg.size(); i++) {
				cout << outNeg[i].first << " " << outNeg[i].second << endl;
			}
		} else {
			ll maxi = -inf;
			bool pos = 1;
			ll index = 0;
			vector<pair<ll, ll>> out;
			for(ll i = 0; i < n; i++) {
				if(abs(v[i]) > maxi) {
					maxi = abs(v[i]);
					if(v[i] >= 0) pos = 1;
					else pos = 0;
					index = i;
				}
			}
			if(pos) {
				for(ll i = 0; i < n; i++) {
					if(v[i] < 0) {
						out.push_back({i + 1, index + 1});
					}
				}
				for(ll i = 1; i < n; i++) out.push_back({i + 1, i});
				cout << (ll) out.size() << endl;
				for(ll i = 0; i < (ll) out.size(); i++) 
					cout << out[i].first << " " << out[i].second << endl;
			} else {
				for(ll i = 0; i < n; i++) {
					if(v[i] > 0) {
						out.push_back({i + 1, index + 1});
					}
				}
				for(ll i = n - 2; i >= 0; i--) out.push_back({i + 1, i + 2});
				cout << (ll) out.size() << endl;
				for(ll i = 0; i < (ll) out.size(); i++) 
					cout << out[i].first << " " << out[i].second << endl;
			}
		}
	} // end test cases
} // end main