#include<bits/stdc++.h>

using namespace std;

const int N = 1234567, md1 = 1e9 + 7, md2 = 1e9 + 9, base = 2333;

struct hash_t {
  int x, y;

  hash_t() {
  }

  hash_t(int x, int y): x(x), y(y) {
  }

  hash_t operator + (hash_t a) {
    return hash_t((x + a.x) % md1, (y + a.y) % md2);
  }

  hash_t operator - (hash_t a) {
    return hash_t((x - a.x + md1) % md1, (y - a.y + md2) % md2);
  }

  hash_t operator * (int a) {
    return hash_t((long long) x * a % md1, (long long) y * a % md2);
  }

  hash_t operator * (hash_t a) {
    return hash_t((long long) x * a.x % md1, (long long) y * a.y % md2);
  }

  long long get() {
    return (long long) x * 233 + y;
  }
} power[N], value[N];

long long get(int l, int r) {
  return (value[r] - value[l - 1] * power[r - l + 1]).get();
}

int tt;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> tt;
  while (tt--) {
    string x;
    cin >> x;
    int n = x.length();
    power[0] = hash_t(1, 1);
    for (int i = 1; i <= n; ++i) {
      power[i] = power[i - 1] * base;
      value[i] = value[i - 1] * base + hash_t(x[i - 1] - 'a' + 1, x[i - 1] - 'a' + 1);
    }
    int l = 1, r = n;
    int answer = 0;
    while (l <= r) {
      for (int i = 1; l + i - 1 < r - i + 1; ++i) {
        if (get(l, l + i - 1) == get(r - i + 1, r)) {
          l = l + i;
          r = r - i;
          answer += 2;
          goto loop;
        }
      }
      ++answer;
      break;
      loop: continue;
    }
    cout << answer << '\n';
  }
  return 0;
}
