#include<bits/stdc++.h>

using namespace std;

int n;
unsigned int a, b, c, d;
bitset<100000000> prime;

int id(int x) {
  return x % 2 && x % 3 ? x - x / 2 - x / 3 + x / 6 : 0;
}

int main() {
  scanf("%d%u%u%u%u", &n, &a, &b, &c, &d);
  unsigned int answer = 0;
  for (int i = 2; i <= n; ++i) {
    if (i <= 3 || (id(i) && !prime[id(i)])) {
      if (i > 3) {
        for (int j = i + i; j <= n; j += i) {
          if (id(j)) {
            prime[id(j)] = 1;
          }
        }
      }
      unsigned int times = 0;
      for (int m = n; m; times += m / i, m /= i);
      answer += times * (a * i * i * i + b * i * i + c * i + d);
    }
  }
  printf("%u\n", answer);
  return 0;
}
