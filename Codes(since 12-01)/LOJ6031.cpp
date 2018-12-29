#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, coef = 301;

int n, m, q, k, last, t, ch[N][26], father[N], len[N], endpos[N], c[N], sorted[N], f[N][18];
long long answer_subtask1[N], answer_subtask2[400][400];
vector<pair<int, int>> que[N];
vector<int> pos[400][400];
char s[N], w[N];

int newnode(int from) {
  ++t;
  len[t] = len[from] + 1;
  return t;
}

void extend(int c) {
  int p = last, np = newnode(p);
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
  for (int i = 1; i <= t; ++i) {
    ++c[len[i]];
  }
  for (int i = 1; i <= n; ++i) {
    c[i] += c[i - 1];
  }
  for (int i = t; i; --i) {
    sorted[c[len[i]]--] = i;
  }
}

int main() {
  len[0] = -1;
  last = newnode(0);
  scanf("%d%d%d%d%s", &n, &m, &q, &k, s);
  for (int i = 0; i < n; ++i) {
    extend(s[i] - 'a');
    ++endpos[last];
  }
  radix_sort();
  for (int i = 2; i <= t; ++i) {
    int u = sorted[i];
    f[u][0] = father[u];
    for (int j = 1; (1 << j) <= t; ++j) {
      f[u][j] = f[f[u][j - 1]][j - 1];
    }
  }
  for (int i = t; i > 1; --i) {
    int u = sorted[i];
    endpos[father[u]] += endpos[u];
  }
  bool subtask1 = q < coef;
  for (int i = 1; i <= m; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    if (subtask1) {
      que[r].emplace_back(l, i);
    } else {
      pos[l][r].push_back(i);
    }
  }
  for (int i = 1; i <= q; ++i) {
    int a, b;
    scanf("%s%d%d", w, &a, &b);
    ++a;
    ++b;
    long long answer = 0;
    if (subtask1) {
      fill(answer_subtask1 + 1, answer_subtask1 + 1 + m, 0);
      for (int j = 0, u = 1, samel = 0; j < k; ++j) {
        int c = w[j] - 'a';
        for (; u != 1 && !ch[u][c]; u = father[u]) {
          samel = len[father[u]];
        }
        if (ch[u][c]) {
          u = ch[u][c];
          ++samel;
        }
        for (auto v : que[j]) {
          int now = u, length = j - v.first + 1;
          if (length <= samel && len[now] >= length) {
            for (int p = 17; ~p; --p) {
              if (len[f[now][p]] >= length) {
                now = f[now][p];
              }
            }
            answer_subtask1[v.second] = endpos[now];
          }
        }
      }
      for (int j = a; j <= b; ++j) {
        answer += answer_subtask1[j];
      }
    } else {
      for (int j = 0; j < k; ++j) {
        for (int j2 = j; j2 < k; ++j2) {
          answer_subtask2[j][j2] = 0;
        }
      }
      for (int j = 0, u; j < k; ++j) {
        u = 1;
        for (int j2 = j; j2 < k; ++j2) {
          int c = w[j2] - 'a';
          if (ch[u][c]) {
            u = ch[u][c];
            answer_subtask2[j][j2] = endpos[u];
          } else {
            break;
          }
        }
      }
      for (int j = 0; j < k; ++j) {
        for (int j2 = j; j2 < k; ++j2) {
          if (answer_subtask2[j][j2]) {
            int num = upper_bound(pos[j][j2].begin(), pos[j][j2].end(), b) - lower_bound(pos[j][j2].begin(), pos[j][j2].end(), a);
            answer += num * answer_subtask2[j][j2];
          }
        }
      }
    }
    printf("%lld\n", answer);
  }
  return 0;
}
