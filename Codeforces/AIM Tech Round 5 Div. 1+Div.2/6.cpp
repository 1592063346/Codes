#include<bits/stdc++.h>

using namespace std;

int q;
map<pair<int, int>, int> need;
map<long long, set<pair<int, int>>> cycle;

int main() {
  scanf("%d", &q);
  int n = 0;
  for (int i = 1; i <= q; ++i) {
    int t, x, y;
    scanf("%d%d%d", &t, &x, &y);
    int simple_x = x / __gcd(x, y);
    int simple_y = y / __gcd(x, y);
    if (t == 1) {
      ++n;
      ++need[pair<int, int> (simple_x, simple_y)];
      long long dist2 = (long long) x * x + (long long) y * y;
      for (auto p : cycle[dist2]) {
        int tx = x + p.first;
        int ty = y + p.second;
        int gcd = __gcd(tx, ty);
        tx /= gcd, ty /= gcd;
        need[pair<int, int> (tx, ty)] += 2;
      }
      cycle[dist2].insert(make_pair(x, y));
    } else if (t == 2) {
      --n;
      --need[pair<int, int> (simple_x, simple_y)];
      long long dist2 = (long long) x * x + (long long) y * y;
      cycle[dist2].erase(make_pair(x, y));
      for (auto p : cycle[dist2]) {
        int tx = x + p.first;
        int ty = y + p.second;
        int gcd = __gcd(tx, ty);
        tx /= gcd, ty /= gcd;
        need[pair<int, int> (tx, ty)] -= 2;
      }
    } else {
      printf("%d\n", n - need[pair<int, int> (simple_x, simple_y)]);
    }
  }
  return 0;
}
