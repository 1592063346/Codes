#include<bits/stdc++.h>

using namespace std;

const int N = 234567;

int tt, t, k, n, ch[N][26], father[N], len[N], value[N], node[N], number[N], diff[N], last;
string x;

int newnode(int x) {
  int y = ++t;
  memset(ch[y], 0, sizeof ch[y]);
  len[y] = len[x] + 1;
  value[y] = father[y] = 0;
  return y;
}

void extend(int c) {
  int p = last, np = newnode(p);
  value[np] = 1;
  for (; p && !ch[p][c]; p = father[p]) {
    ch[p][c] = np;
  }
  if (!p) {
    father[np] = 1;
  } else {
    int q = ch[p][c];
    if (len[p] + 1 == len[q]) {
      father[np] = q;
    } else {
      int nq = newnode(p);
      memcpy(ch[nq], ch[q], sizeof ch[q]);
      father[nq] = father[q];
      father[np] = father[q] = nq;
      for (; p && ch[p][c] == q; p = father[p]) {
        ch[p][c] = nq;
      }
    }
  }
  last = np;
}

void radix_sort() {
  fill(number, number + n + 1, 0);
  for (int i = 1; i <= t; ++i) {
    ++number[len[i]];
  }
  for (int i = 1; i <= n; ++i) {
    number[i] += number[i - 1];
  }
  for (int i = t; i; --i) {
    node[number[len[i]]--] = i;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  len[0] = -1;
  cin >> tt;
  while (tt--) {
    cin >> x >> k;
    n = x.length();
    t = 0;
    last = newnode(0);
    for (int i = 0; i < n; ++i) {
      extend(x[i] - 'a');
    }
    radix_sort();
    fill(diff + 1, diff + n + 2, 0);
    for (int i = t; i; --i) {
      int x = node[i];
      if (value[x] == k) {
        ++diff[len[father[x]] + 1];
        --diff[len[x] + 1];
      }
      value[father[x]] += value[x];
    }
    int answer = -1, times = 1;
    for (int i = 1; i <= n; ++i) {
      diff[i] += diff[i - 1];
      if (diff[i] >= times) {
        times = diff[i];
        answer = i;
      }
    }
    cout << answer << '\n';
  }
  return 0;
}
