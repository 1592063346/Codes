#include<bits/stdc++.h>

using namespace std;

const int N = 3010, base = 2333, md0 = 1e9 + 7, md1 = 1e9 + 9;

int n, len[N];
pair<int, int> diff[N];
char from[N][N], goal[N][N];

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

  inline long long get() {
    return (long long) hash0 * md1 + hash1;
  }
} h0[N][N], h1[N][N], power[N];

inline long long get_hash(hash_t* h, int l, int r) {
  return (h[r] - h[l - 1] * power[r - l + 1]).get();
}

bool all_begin() {
  char type = 0;
  for (int i = 1; i <= n; ++i) {
    if (~diff[i].first) {
      if (diff[i].first == 1) {
        return false;
      } else if (type && from[i][diff[i].first - 1] != type) {
        return false;
      }
      type = from[i][diff[i].first - 1];
    }
  }
  return true;
}

bool all_end() {
  char type = 0;
  for (int i = 1; i <= n; ++i) {
    if (~diff[i].first) {
      if (diff[i].second == len[i]) {
        return false;
      } else if (type && from[i][diff[i].second + 1] != type) {
        return false;
      }
      type = from[i][diff[i].second + 1];
    }
  }
  return true;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", from[i] + 1);
    len[i] = strlen(from[i] + 1);
    for (int j = 1; j <= len[i]; ++j) {
      h0[i][j] = h0[i][j - 1] * base + from[i][j];
    }
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%s", goal[i] + 1);
    for (int j = 1; j <= len[i]; ++j) {
      h1[i][j] = h1[i][j - 1] * base + goal[i][j];
    }
  }
  power[0] = hash_t(1, 1);
  for (int i = 1; i <= 3000; ++i) {
    power[i] = power[i - 1] * base;
  }
  pair<int, int> mindiff(0, 3001);
  int source;
  for (int i = 1; i <= n; ++i) {
    diff[i].first = -1;
    for (int j = 1; j <= len[i]; ++j) {
      if (from[i][j] != goal[i][j]) {
        diff[i].first = j;
        break;
      }
    }
    if (~diff[i].first) {
      for (int j = len[i]; j; --j) {
        if (from[i][j] != goal[i][j]) {
          diff[i].second = j;
          break;
        }
      }
      if (diff[i].second - diff[i].first < mindiff.second - mindiff.first) {
        mindiff = diff[i];
        source = i;
      }
    }
  }
  bool ok = true;
  for (int i = 1; i <= n; ++i) {
    if (~diff[i].first) {
      if (diff[i].second - diff[i].first != diff[source].second - diff[source].first) {
        ok = false;
      }
    }
  }
  if (ok) {
    while (1) {
      if (all_begin()) {
        for (int i = 1; i <= n; ++i) {
          if (~diff[i].first) {
            --diff[i].first;
          }
        }
      } else if (all_end()) {
        for (int i = 1; i <= n; ++i) {
          if (~diff[i].first) {
            ++diff[i].second;
          }
        }
      } else {
        break;
      }
    }
  }
  int length = diff[source].second - diff[source].first + 1;
  for (int i = 1; i <= n && ok; ++i) {
    if (~diff[i].first) {
      bool find = false;
      for (int j = 1; j + length - 1 <= len[i]; ++j) {
        int k = j + length - 1;
        if (get_hash(h0[i], j, k) == get_hash(h0[source], diff[source].first, diff[source].second)) {
          find = true;
          if (j != diff[i].first || get_hash(h1[i], j, k) != get_hash(h1[source], diff[source].first, diff[source].second)) {
            ok = false;
          }
          break;
        }
      }
      if (!find) {
        ok = false;
      }
    } else {
      for (int j = 1; j + length - 1 <= len[i]; ++j) {
        int k = j + length - 1;
        if (get_hash(h0[i], j, k) == get_hash(h0[source], diff[source].first, diff[source].second)) {
          ok = false;
          break;
        }
      }
    }
  }
  if (!ok) {
    puts("NO");
  } else {
    puts("YES");
    for (int i = diff[source].first; i <= diff[source].second; ++i) {
      printf("%c", from[source][i]);
    }
    puts("");
    for (int i = diff[source].first; i <= diff[source].second; ++i) {
      printf("%c", goal[source][i]);
    }
    puts("");
  }
  return 0;
}  
