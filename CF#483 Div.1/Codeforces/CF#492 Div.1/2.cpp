#include<bits/stdc++.h>

using namespace std;

const int N = 205;

int n, a[N];

int main() {
  scanf("%d", &n);
  n <<= 1;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  int answer = 0;
  for (int i = 1, j; i <= n; i += 2) {
    for (j = i + 1; j <= n; ++j) {
      if (a[j] == a[i]) {
        break;
      }
    }
    answer += j - i - 1;
    for (; j > i; --j) {
      swap(a[j], a[j - 1]);
    }
  }
  printf("%d\n", answer);
  return 0;
}
