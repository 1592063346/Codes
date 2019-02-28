#include<bits/stdc++.h>

using namespace std;

const int N = 3e3 + 10, base = 2333, md0 = 1e9 + 7, md1 = 1e9 + 9, md2 = 1e6 + 7, mod = 1e9 + 7;

void add(int& x, int y) {
  x += y;
  if (x >= mod) {
    x -= mod;
  }
}

void sub(int& x, int y) {
  x -= y;
  if (x < 0) {
    x += mod;
  }
}

int n, f[N][N];
bool appeared[N][N];
char s[N];

struct hash_t {
  int hash0, hash1;

  hash_t() {}
  hash_t(int hash0, int hash1): hash0(hash0), hash1(hash1) {}

  hash_t operator + (const int& x) const {
    return hash_t((hash0 + x) % md0, (hash1 + x) % md1);
  };

  hash_t operator * (const int& x) const {
    return hash_t((long long) hash0 * x % md0, (long long) hash1 * x % md1);
  }

  hash_t operator + (const hash_t& x) const {
    return hash_t((hash0 + x.hash0) % md0, (hash1 + x.hash1) % md1);
  };

  hash_t operator - (const hash_t& x) const {
    return hash_t((hash0 + md0 - x.hash0) % md0, (hash1 + md1 - x.hash1) % md1);
  };

  hash_t operator * (const hash_t& x) const {
    return hash_t((long long) hash0 * x.hash0 % md0, (long long) hash1 * x.hash1 % md1);
  }

  long long get() {
    return (long long) hash0 * md1 + hash1;
  }
} h[N], power[N];

long long get_hash(int l, int r) {
  return (h[r] - h[l - 1] * power[r - l + 1]).get();
}

void hash_init() {
  for (int i = 1; i <= n; ++i) {
    h[i] = h[i - 1] * base + s[i];
  }
  power[0] = hash_t(1, 1);
  for (int i = 1; i <= n; ++i) {
    power[i] = power[i - 1] * base;
  }
}

struct hash_table {
  vector<long long> pool[md2];

  bool find(long long x) {
    int t = x % md2;
    for (auto value : pool[t]) {
      if (value == x) {
        return true;
      }
    }
    return false;
  }

  void insert(long long x) {
    pool[x % md2].push_back(x);
  }
} table;

bool ban(int l, int r) {
  if (r - l + 1 == 4) {
    if (s[l] == '0' && s[l + 1] == '0' && s[r - 1] == '1' && s[r] == '1') {
      return true;
    }
    if (s[l] == '0' && s[l + 1] == '1' && s[r - 1] == '0' && s[r] == '1') {
      return true;
    }
    if (s[l] == '1' && s[l + 1] == '1' && s[r - 1] == '1' && s[r] == '0') {
      return true;
    }
    if (s[l] == '1' && s[l + 1] == '1' && s[r - 1] == '1' && s[r] == '1') {
      return true;
    }
    return false;
  }
  return false;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", s + i);
  }
  hash_init();
  int answer = 0;
  for (int i = 1; i <= n; ++i) {
    f[i][i - 1] = 1;
    for (int j = i; j <= n; ++j) {
      for (int k = j; k > max(j - 4, i - 1); --k) {
        if (!ban(k, j)) {
          add(f[i][j], f[i][k - 1]);
        }
      }
      if (!table.find(get_hash(i, j))) {
        table.insert(get_hash(i, j));
        add(answer, f[i][j]);
      } else {
        appeared[i][j] = true;
      }
    }
  }
  vector<int> ouf(1, answer);
  for (int i = n; i > 1; --i) {
    for (int j = 1; j <= i; ++j) {
      if (!appeared[j][i]) {
        sub(answer, f[j][i]);
      }
    }
    ouf.push_back(answer);
  }
  for (int i = (int) ouf.size() - 1; ~i; --i) {
    printf("%d\n", ouf[i]);
  }
  return 0;
}
