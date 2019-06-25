#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int n, l, r, pre_last, suf_last, tt, ch[N][26], father[N], len[N], sum[N];
long long answer;
char s[N << 1];

int new_node(int from) {
  len[++tt] = len[from] + 2;
  return tt;
}

int extend(int last, int i, int c, int op) {
  int p = last;
  while (s[i + op * (1 + len[p])] - 'a' != c) {
    p = father[p];
  }
  if (!ch[p][c]) {
    int np = new_node(p), q = father[p];
    while (s[i + op * (1 + len[q])] - 'a' != c) {
      q = father[q];
    }
    father[np] = ch[q][c];
    sum[np] = sum[ch[q][c]] + 1;
    ch[p][c] = np;
  }
  return ch[p][c];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  while (cin >> n) {
    memset(ch, 0, sizeof ch);
    memset(father, 0, sizeof father);
    memset(s, 0, sizeof s);
    tt = 1;
    pre_last = suf_last = answer = 0;
    len[1] = -1;
    father[0] = 1;
    l = n + 1;
    r = n;
    while (n--) {
      int op;
      string x;
      cin >> op;
      if (op == 1) {
        cin >> x;
        s[--l] = x[0];
        pre_last = extend(pre_last, l, x[0] - 'a', 1);
        answer += sum[pre_last];
        if (len[pre_last] == r - l + 1) {
          suf_last = pre_last;
        }
      } else if (op == 2) {
        cin >> x;
        s[++r] = x[0];
        suf_last = extend(suf_last, r, x[0] - 'a', -1);
        answer += sum[suf_last];
        if (len[suf_last] == r - l + 1) {
          pre_last = suf_last;
        }
      } else if (op == 3) {
        cout << tt - 1 << '\n';
      } else {
        cout << answer << '\n';
      }
    }
  }
  return 0;
}
