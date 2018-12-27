#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, max_value = 32000000;
const long long inf = 1e18;

int t;
bool is_prime[max_value], inq[N];
long long n, k, d[N];
vector<int> primes;
map<long long, vector<long long>> s, arr;

void sieve() {
  memset(is_prime, true, sizeof is_prime);
  for (int i = 2; i < max_value; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
    for (auto v : primes) {
      int d = i * v;
      if (d >= max_value) {
        break;
      }
      is_prime[d] = false;
      if (i % v == 0) {
        break;
      }
    }
  }
}

void exgcd(long long a, long long b, long long& d, long long& x, long long& y) {
  if (!b) {
    d = a;
    x = 1;
    y = 0;
  } else {
    exgcd(b, a % b, d, y, x);
    y -= x * (a / b);
  }
}

void solve(long long k, vector<long long>& e) {
  memset(inq, false, sizeof inq);
  inq[0] = true;
  for (int i = 1; i < e[0]; ++i) {
    d[i] = inf;
  }
  queue<int> que;
  que.push(0);
  while (!que.empty()) {
    int x = que.front();
    que.pop();
    inq[x] = false;
    for (auto y : e) {
      int to = (x + y) % e[0];
      if (d[to] > d[x] + y) {
        d[to] = d[x] + y;
        if (!inq[to]) {
          que.push(to);
          inq[to] = true;
        }
      }
    }
  }
  for (int i = 0; i < e[0]; ++i) {
    arr[k].push_back(d[i]);
  }
}

int main() {
  sieve();
  scanf("%d", &t);
  for (int kase = 1; kase <= t; ++kase) {
    scanf("%lld%lld", &n, &k);
    if (k == 1) {
      puts("NO");
      continue;
    }
    if (!s.count(k)) {
      long long j = k;
      for (auto i : primes) {
        if (j % i == 0) {
          s[k].push_back(i);
          while (j % i == 0) {
            j /= i;
          }
        }
      }
      if (j != 1) {
        s[k].push_back(j);
      }
      sort(s[k].begin(), s[k].end());
    }
    if (s[k].size() == 1) {
      puts(n % s[k][0] == 0 ? "YES" : "NO");
    } else if (s[k].size() == 2) {
      long long x, y, d;
      exgcd(s[k][0], s[k][1], d, x, y);
      long long tmp = ((n % s[k][0]) * (y % s[k][0]) % s[k][0] + s[k][0]) % s[k][0];
      puts(tmp * s[k][1] <= n ? "YES" : "NO");
    } else {
      if (!arr.count(k)) {
        solve(k, s[k]);
      }
      puts(arr[k][n % s[k][0]] < inf && arr[k][n % s[k][0]] <= n ? "YES" : "NO");
    }
  }
  return 0;
}
