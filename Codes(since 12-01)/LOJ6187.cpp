#include<bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10, M = 450, md = 10003;

int n, tt, a[N], last[N];
unsigned long long b[N], value[N], lazy[N];

unsigned long long rng() {
  unsigned long long result = 0;
  for (int i = 0; i < 5; ++i) {
    result = (result << 15) | rand();
  }
  return result;
}

struct hash_t {
  vector<pair<unsigned long long, int>> bottle[md];
  vector<unsigned long long> mem;

  void reset() {
    for (auto x : mem) {
      bottle[x % md].clear();
    }
    mem.clear();
  }

  void insert(unsigned long long x) {
    int p = x % md;
    for (auto& info : bottle[p]) {
      if (info.first == x) {
        ++info.second;
        return;
      }
    }
    mem.push_back(x);
    bottle[p].emplace_back(x, 1);
  }

  int query(unsigned long long x) {
    int p = x % md;
    for (auto info : bottle[p]) {
      if (info.first == x) {
        return info.second;
      }
    }
    return 0;
  }
} tables[M];

void rebuild(int t, int l, int r, unsigned long long x) {
  for (int i = (t - 1) * M + 1; i <= min(t * M, tt); ++i) {
    b[i] ^= lazy[t];
  }
  for (int i = l; i <= r; ++i) {
    b[i] ^= x;
  }
  lazy[t] = 0;
  tables[t].reset();
  for (int i = (t - 1) * M + 1; i <= min(t * M, tt); ++i) {
    tables[t].insert(b[i]);
  }
}

void modify(int l, int r, unsigned long long x) {
  int bl = (l - 1) / M + 1, br = (r - 1) / M + 1;
  for (int i = bl + 1; i < br; ++i) {
    lazy[i] ^= x;
  }
  if (bl == br) {
    rebuild(bl, l, r, x);
  } else {
    rebuild(bl, l, bl * M, x);
    rebuild(br, (br - 1) * M + 1, r, x);
  }
}

int query(unsigned long long x) {
  int result = 0, t = (tt - 1) / M + 1;
  for (int i = 1; i < t; ++i) {
    result += tables[i].query(x ^ lazy[i]);
  }
  for (int i = (t - 1) * M + 1; i <= tt; ++i) {
    if ((b[i] ^ lazy[t]) == x) {
      ++result;
    }
  }
  return result;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i <= 1e6; ++i) {
    value[i] = rng();
  }
  long long answer = 0, sum = 0;
  for (int i = 1; i <= n; ++i) {
    tt = i;
    b[i] = sum ^ lazy[(i - 1) / M + 1];
    modify(last[a[i]] + 1, i, value[a[i]]);
    last[a[i]] = i;
    answer += query(sum ^= value[a[i]]);
  }
  printf("%lld\n", answer);
  return 0;
}
