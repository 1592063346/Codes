#include<bits/stdc++.h>

using namespace std;

const int N = 4e6 + 10;

void cmax(int& x, int y) {
  if (x < y) {
    x = y;
  }
}

int n, lcp[N], extend[N], number0[N], number9[N];
char s[N], t[N];

void get_lcp() {
  lcp[0] = n;
  lcp[1] = 0;
  for (; t[1 + lcp[1]] == t[lcp[1]]; ++lcp[1]);
  int p = 1, r = p + lcp[1] - 1;
  for (int i = 2; i < n; ++i) {
    int len = lcp[i - p];
    if (i - 1 + len < r) {
      lcp[i] = len;
    } else {
      lcp[i] = max(0, r - i + 1);
      for (; t[i + lcp[i]] == t[lcp[i]]; ++lcp[i]);
      if (i + lcp[i] - 1 > r) {
        p = i;
        r = i + lcp[i] - 1;
      }
    }
  }
}

void get_extend() {
  extend[0] = 0;
  for (; s[extend[0]] == t[extend[0]]; ++extend[0]);
  int p = 0, r = p + extend[0] - 1;
  for (int i = 1; i < n; ++i) {
    int len = lcp[i - p];
    if (i - 1 + len < r) {
      extend[i] = len;
    } else {
      extend[i] = max(0, r - i + 1);
      for (; s[i + extend[i]] == t[extend[i]]; ++extend[i]);
      if (i + extend[i] - 1 > r) {
        p = i;
        r = i + extend[i] - 1;
      }
    }
  }
}

int main() {
  while (scanf("%s", s) == 1) {
    n = strlen(s);
    reverse(s, s + n);
    for (int i = n; i < (n << 1); ++i) {
      s[i] = '0';
    }
    n <<= 1;
    copy(s, s + n, t);
    int p = 0;
    for (int i = 0; i < n; ++i) {
      if (p) {
        t[i] = '9' - t[i] + '0';
      } else if (t[i] != '0') {
        p = i + 1;
        t[i] = '9' - t[i] + 1 + '0';
      }
    }
    number0[n] = 0;
    number9[n] = 0;
    for (int i = n - 1; ~i; --i) {
      number0[i] = s[i] == '0' ? 1 + number0[i + 1] : 0;
      number9[i] = s[i] == '9' ? 1 + number9[i + 1] : 0;
    }
    get_lcp();
    get_extend();
    int answer = 0;
    for (int i = 1; i < (n >> 1); ++i) {
      int j = min(extend[i], i);
      if (i <= extend[i]) {
        if (j >= p) {
          j += number9[i + j];
        } else {
          j += number0[i + j];
        }
      }
      cmax(answer, j);
    }
    printf("%d\n", answer);
  }
  return 0;
}
