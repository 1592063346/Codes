#include<bits/stdc++.h>

using namespace std;

const int N = 1e4 + 10, base = 5e6, mod = 1e9 + 7;

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

long long n;
int k, sq, fac[N], inv_fac[N], pre[base + 10], spow[base + 10], sigma[base + 10], l[N], r[N], y[N];
bool is_prime[base + 10];
vector<int> primes;

template<typename T>
struct my_array {
  T a[N * 20];

  T& operator [] (long long x) {
    return x <= sq ? a[x] : a[sq + n / x];
  }
};

my_array<int> sum_pow, s;

void sieve() {
  fill(is_prime + 1, is_prime + 1 + base, true);
  pre[1] = 1;
  for (int i = 2; i <= base; ++i) {
    if (is_prime[i]) {
      primes.push_back(i);
      pre[i] = mod - 1;
    }
    for (auto v : primes) {
      if (i * v > base) {
        break;
      }
      is_prime[i * v] = false;
      if (i % v == 0) {
        pre[i * v] = 0;
        break;
      } else {
        pre[i * v] = (mod - pre[i]) % mod;
      }
    }
  }
  for (int i = 1; i <= base; ++i) {
    spow[i] = sigma[i] = qpow(i, k);
  }
  for (auto i : primes) {
    for (int j = 1; j * i <= base; ++j) {
      add(sigma[j * i], sigma[j]);
    }
  }
  for (int i = 2; i <= base; ++i) {
    pre[i] = mul(pre[i], qpow(i, k));
    add(pre[i], pre[i - 1]);
    add(spow[i], spow[i - 1]);
    add(sigma[i], sigma[i - 1]);
  }
}

void init(int n) {
  fac[0] = 1;
  inv_fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = mul(fac[i - 1], i);
  }
  inv_fac[n] = qpow(fac[n], mod - 2);
  for (int i = n - 1; i; --i) {
    inv_fac[i] = mul(inv_fac[i + 1], i + 1);
  }
  for (int i = 1; i <= n; ++i) {
    y[i] = qpow(i, k);
    add(y[i], y[i - 1]);
  }
}

int get_sum_pow(long long n) {
  if (n <= base) {
    return spow[n];
  } else if (sum_pow[n]) {
    return sum_pow[n];
  } else {
    int result = 0;
    l[0] = 1;
    r[k + 3] = 1;
    for (int i = 1; i <= k + 2; ++i) {
      l[i] = mul(l[i - 1], ((n - i) % mod + mod) % mod);
    }
    for (int i = k + 2; i; --i) {
      r[i] = mul(r[i + 1], ((n - i) % mod + mod) % mod);
    }
    for (int i = 1; i <= k + 2; ++i) {
      int prefac = inv_fac[i - 1];
      int suffac = k + 2 - i & 1 ? mul(inv_fac[k + 2 - i], mod - 1) : inv_fac[k + 2 - i];
      add(result, mul(l[i - 1], r[i + 1], prefac, suffac, y[i]));
    }
    return sum_pow[n] = result;
  }
}

int get_sigma(long long n) {
  if (n <= base) {
    return sigma[n];
  } else {
    int result = 0, pre = 0;
    for (long long i = 1, last; i <= n; i = last + 1) {
      last = n / (n / i);
      int now = get_sum_pow(last);
      add(result, mul(n / i, (now - pre + mod) % mod));
      pre = now;
    }
    return result;
  }
}

int get_s(long long n) {
  if (n <= base) {
    return pre[n];
  } else if (s[n]) {
    return s[n];
  } else {
    int result = 0;
    int pre = 1;
    result = 1;
    for (long long i = 2, last; i <= n; i = last + 1) {
      last = n / (n / i);
      int now = get_sum_pow(last);
      sub(result, mul(get_s(n / i), (now - pre + mod) % mod));
      pre = now;
    }
    return s[n] = result;
  }
}

int main() {
  scanf("%lld%d", &n, &k);
  sieve();
  sq = sqrt(n);
  init(k + 2);
  int answer = 0, pre = 0;
  for (long long i = 1, last; i <= n; i = last + 1) {
    last = n / (n / i);
    int s = get_sigma(n / i), now = get_s(last);
    add(answer, mul((now - pre + mod) % mod, s, s));
    pre = now;
  }
  printf("%d\n", answer);
  return 0;
}
