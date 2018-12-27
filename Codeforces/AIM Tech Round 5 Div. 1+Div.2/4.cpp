#include<bits/stdc++.h>

using namespace std;

const int N = 363304, mod = 1e9 + 7;

int n;
char cmd[10];
set<pair<int, int>> no_sell;

int main() {
  scanf("%d", &n);
  int ans = 1, pool = 1;
  for (int i = 1; i <= n; ++i) {
    int p;
    scanf("%s%d", cmd, &p);
    if (cmd[1] == 'D') {
      bool l_0 = true, r_1 = true;
      int type = -1;
      set<pair<int, int>>:: iterator it = no_sell.lower_bound(make_pair(p, -1));
      if (it != no_sell.end() && (*it).second == 0) {
        r_1 = false;
        type = 0;
      }
      if (it != no_sell.begin() && (*--it).second == 1) {
        l_0 = false;
        type = 1;
      }
      if (l_0 & r_1) {
        ++pool;
      }
      no_sell.insert(make_pair(p, type));
    } else {
      pool = 1;
      set<pair<int, int>>:: iterator it = no_sell.lower_bound(make_pair(p, -1)), it_l = it, it_r = it;
      if (!~(*it).second) {
        ans = (ans << 1) % mod;
      }
      bool cant = it == no_sell.begin();
      --it_l;
      ++it_r;
      vector<int> s0, s1;
      for (; !cant; --it_l) {
        if ((*it_l).second == 1) {
          ans = 0;
        }
        if ((*it_l).second == 0) {
          break;
        }
        s0.push_back((*it_l).first);
        if (it_l == no_sell.begin()) {
          break;
        }
      }
      for (;; ++it_r) {
        if (it_r == no_sell.end()) {
          break;
        }
        if ((*it_r).second == 0) {
          ans = 0;
        }
        if ((*it_r).second == 1) {
          break;
        }
        s1.push_back((*it_r).first);
      }
      no_sell.erase(it);
      for (auto v : s0) {
        no_sell.erase(no_sell.lower_bound(make_pair(v, -1)));
        no_sell.insert(make_pair(v, 0));
      }
      for (auto v : s1) {
        no_sell.erase(no_sell.lower_bound(make_pair(v, -1)));
        no_sell.insert(make_pair(v, 1));
      }
    }
    if (!ans) {
      break;
    }
  }
  printf("%I64d\n", (long long) ans * pool % mod);
  return 0;
}
