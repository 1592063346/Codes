#include<bits/stdc++.h>

using namespace std;

const int N = 1e3 + 10, mod = 1e9 + 7;

int add(int x, int y) {
  x = (x + y) % mod;
  if (x < 0) {
    x += mod;
  }
  return x;
}

int sub(int x, int y) {
  x = (x - y) % mod;
  if (x < 0) {
    x += mod;
  }
  return x;
}

int mul(int x, int y) {
  return (long long) x * y % mod;
}

int qpow(int v, int p) {
  int result = 1;
  for (; p; p >>= 1, v = mul(v, v)) {
    if (p & 1) {
      result = mul(result, v);
    }
  }
  return result;
}

struct point_t {
  int x, y;
  bool ban;

  point_t() {}
  point_t(int x, int y): x(x), y(y) {
    ban = false;
  }

  point_t operator + (point_t a) {
    return point_t(x + a.x, y + a.y);
  }

  point_t operator - (point_t a) {
    return point_t(x - a.x, y - a.y);
  }
} p[N], q[N];

long long dot(point_t a, point_t b) {
  return (long long) a.x * b.x + (long long) a.y * b.y;
}

long long cross(point_t a, point_t b) {
  return (long long) a.x * b.y - (long long) a.y * b.x;
}

int n, id;
map<long long, int> number;
vector<double> alls[N * N];

template<typename T, typename R, const int md>
struct hash_t {
  vector<pair<T, R>> bottle[md];
  R unfound = 0;

  int f(int x) {
    return x % md;
  }

  int f(pair<int, int> x) {
    return (x.first * 233ll + x.second) % md;
  }

  void insert(T x, R y) {
    int p = f(x);
    bottle[p].emplace_back(x, y);
  }

  R& operator [] (T x) {
    int p = f(x);
    for (auto& info : bottle[p]) {
      if (info.first == x) {
        return info.second;
      }
    }
    return unfound;
  }
};

hash_t<int, int, 1000003> all_x0;
hash_t<pair<int, int>, int, 1000003> all_y;

int main() {
  int inv2 = mod + 1 >> 1;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &p[i].x, &p[i].y);
    for (int j = 0; j < i; ++j) {
      double midx = (p[i].x + p[j].x) * 0.5;
      double midy = (p[i].y + p[j].y) * 0.5;
      int pmidx = mul(add(p[i].x, p[j].x), inv2);
      int pmidy = mul(add(p[i].y, p[j].y), inv2);
      if (p[i].y == p[j].y) {
        if (!all_x0[pmidx]) {
          all_x0.insert(pmidx, ++id);
        }
        alls[all_x0[pmidx]].push_back(midy);
      } else {
        int k = mul(sub(p[i].x, p[j].x), qpow(sub(p[j].y, p[i].y), mod - 2));
        int b = sub(pmidy, mul(pmidx, k));
        if (!all_y[{k, b}]) {
          all_y.insert({k, b}, ++id);
        }
        alls[all_y[{k, b}]].push_back(midx);
      }
    }
  }
  for (int i = 1; i <= id; ++i) {
    sort(alls[i].begin(), alls[i].end());
  }
  long long answer = 0;
  for (int i = 0; i < n; ++i) {
    int m = 0;
    for (int j = 0; j < n; ++j) {
      if (i != j) {
        q[m++] = p[j] - p[i];
      }
    }
    q[m++] = point_t(0, 1);
    q[m++] = point_t(0, -1);
    q[m++] = point_t(1, 0);
    q[m++] = point_t(-1, 0);
    q[m - 1].ban = q[m - 2].ban = q[m - 3].ban = q[m - 4].ban = true;
    sort(q, q + m, [&] (const point_t& a, const point_t& b) {
      return atan2(a.y, a.x) < atan2(b.y, b.x);
    });
    for (int j = 0; j < m; ++j) {
      bool ban = q[j].ban;
      q[j] = q[j] + p[i];
      q[j].ban = ban;
    }
    int j, k, t = 0;
    while (q[t].ban) {
      ++t;
    }
    j = t;
    while (dot(q[t] - p[i], q[j] - p[i]) >= 0) {
      j = (j + 1) % m;
    }
    int oldt = t;
    k = j;
    long long tt = 0;
    while (1) {
      point_t vec = q[t] - p[i];
      while (dot(vec, q[k] - p[i]) < 0) {
        if (!q[k].ban) {
          tt += number[dot(q[k] - p[i], q[k] - p[i])]++;
        }
        k = (k + 1) % m;
      }
      while (dot(vec, q[j] - p[i]) >= 0) {
        if (!q[j].ban) {
          tt -= --number[dot(q[j] - p[i], q[j] - p[i])];
        }
        j = (j + 1) % m;
      }
      if (!q[t].ban) {
        if (p[i].x == q[t].x) {
          if (all_x0[(p[i].x % mod + mod) % mod]) {
            vector<double>& all = alls[all_x0[(p[i].x % mod + mod) % mod]];
            double l = p[i].y;
            double r = q[t].y;
            if (l > r) {
              swap(l, r);
            }
            answer += tt * (lower_bound(all.begin(), all.end(), r) - upper_bound(all.begin(), all.end(), l));
          }
        } else{ 
          int k = mul(sub(p[i].y, q[t].y), qpow(sub(p[i].x, q[t].x), mod - 2));
          int b = sub(p[i].y, mul(p[i].x, k));
          if (all_y[{k, b}]) {
            vector<double>& all = alls[all_y[{k, b}]];
            double l = p[i].x;
            double r = q[t].x;
            if (l > r) {
              swap(l, r);
            }
            answer += tt * (lower_bound(all.begin(), all.end(), r) - upper_bound(all.begin(), all.end(), l));
          }
        }
      }
      if ((t + 1) % m == oldt) {
        break;
      } else {
        t = (t + 1) % m;
      }
    }
    number.clear();
  }
  printf("%lld\n", answer << 2);
  return 0;
}
