#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, mod = 1e9 + 7;

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
 
template<typename T>
int mul(T x) {
  return x;
}
 
template<typename T, typename... U>
int mul(T x, U... y) {
  return (long long) x * mul(y...) % mod;
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

int s(int x, int n) {
  int answer = mul((1 - qpow(x, n) + mod) % mod, qpow(mul((1 - x + mod) % mod, (1 - x + mod) % mod), mod - 2));
  sub(answer, mul(mul(n, qpow(x, n)), qpow((1 - x + mod) % mod, mod - 2)));
  return mul(answer, x);
}

int s2(int x, int n) {
  int a1 = x;
  int an = qpow(x, n);
  return mul(a1, (1 - an + mod) % mod, qpow((1 - x + mod) % mod, mod - 2));
}

long long same_diff(int x, int y) {
  if (x > y) {
    return 0;
  }
  int s = y - x + 1;
  return (long long) (x + y) * s >> 1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n;
  long long k;
  cin >> n >> k;
  int l = 0, r = n;
  while (l != r) {
    int mid = (l + r >> 1) + 1;
    if (same_diff(n - mid, n - 1) <= k) {
      l = mid;
    } else {
      r = mid - 1;
    }
  }
  int answer = mul(n + 1, s2(n + 1, l));
  sub(answer, s(n + 1, l));
  int diff = k - same_diff(n - l, n - 1) + 1;
  add(answer, mul(diff, qpow(n + 1, l + 1)));
  int rest = n - l - diff;
  add(answer, mul(qpow(n + 1, l + 1), s(n + 1, n - l - 1)));
  add(answer, mul(qpow(n + 1, n - rest), s2(n + 1, rest)));
  cout << answer << "\n";
  return 0;
}
