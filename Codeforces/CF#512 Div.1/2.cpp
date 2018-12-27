#include<bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, bitsum[N], odd[N], even[N];
long long a[N];

int getbit(long long x) {
  int result = 0;
  for (; x; x -= x & -x) {
    ++result;
  }
  return result;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%I64d", &a[i]);
  }
  for (int i = n; i; --i) {
    bitsum[i] = bitsum[i + 1] + getbit(a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    odd[i] = odd[i - 1];
    even[i] = even[i - 1];
    if (bitsum[i] & 1) {
      ++odd[i];
    } else {
      ++even[i];
    }
  }
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    int p = i, maxbit = 0, sumbit = 0;
    for (; p; --p) {
      sumbit += getbit(a[p]);
      cmax(maxbit, getbit(a[p]));
      if (sumbit >= 60 << 1) {
        break;
      }
      if (sumbit >= maxbit << 1 && !(sumbit & 1)) {
        ++ans;
      }
    }
    if (bitsum[i + 1] & 1) {
      ans += odd[p];
    } else {
      ans += even[p];
    }
  }
  printf("%I64d\n", ans);
  return 0;
}
