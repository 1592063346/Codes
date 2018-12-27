#include<bits/stdc++.h>

using namespace std;

long long n;
int k;
char cmd[5];

long long random_number(long long l, long long r) {
  return l + rand() % (r - l + 1);
}

int main() {
  srand(time(0));
  scanf("%I64d%d", &n, &k);
  while (1) {
    long long l = 1, r = n;
    while (r - l >= min(44ll, n)) {
      long long mid = l + r >> 1;
      printf("%I64d %I64d\n", l, mid);
      fflush(stdout);
      scanf("%s", cmd);
      if (*cmd == 'Y') {
        l = max(1ll, l - k);
        r = min(n, mid + k);
      } else {
        l = max(1ll, mid + 1 - k);
        r = min(n, r + k);
      }
    }
    long long pos = random_number(l, r);
    printf("%I64d %I64d\n", pos, pos);
    fflush(stdout);
    scanf("%s", cmd);
    if (*cmd == 'Y') {
      break;
    }
  }
  return 0;
}
