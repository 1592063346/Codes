#include<bits/stdc++.h>

using namespace std;

int my_sqrt(long long x) {
  int y = (int) sqrt(x + 0.5);
  while ((long long) y * y > x) {
    --y;
  }
  while ((long long) (y + 1) * (y + 1) <= x) {
    ++y;
  }
  return y;
}

const int N = 12345678;

long long phi[N];
bool is_prime[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  long long n;
  cin >> n;
  int m = my_sqrt(n);
  phi[1] = 1;
  vector<int> primes;
  fill(is_prime + 1, is_prime + 1 + m, true);
  for (int i = 2; i <= m; ++i) {
    if (is_prime[i]) {
      phi[i] = i - 1;
      primes.push_back(i);
    }
    for (auto x : primes) {
      if (x * i > m) {
        break;
      }
      is_prime[x * i] = false;
      if (i % x == 0) {
        phi[i * x] = phi[i] * x;
        break;
      } else {
        phi[i * x] = phi[i] * phi[x];
      }
    }
  }
  for (int i = 1; i <= m; ++i) {
    phi[i] += phi[i - 1];
  }
  long long answer = 0;
  for (long long l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    answer += (2 * phi[my_sqrt(n / l)] - 1) * (r - l + 1);
  }
  cout << answer << '\n';
  return 0;
}
