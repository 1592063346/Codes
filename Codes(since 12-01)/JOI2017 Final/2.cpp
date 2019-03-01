#include<bits/stdc++.h>

using namespace std;

const int N = 3e3 + 10;

int n, m, k, s[N];
long long a, b, c, t;

struct node_t {
  int i, p, next_num;

  node_t(int i, int p, int next_num): i(i), p(p), next_num(next_num) {}

  bool operator < (const node_t& a) const {
    return next_num < a.next_num;
  }
};

int solve(int i, int p) {
  long long rest = t - (s[i] - s[1]) * b - (p - s[i]) * c;
  return rest >= 0 ? 1 + min(rest / a, (long long) s[i + 1] - p - 1) : 0;
}

int main() {
  scanf("%d%d%d%lld%lld%lld%lld", &n, &m, &k, &a, &b, &c, &t);
  k -= m;
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &s[i]);
  }
  priority_queue<node_t> que;
  int answer = 0;
  long long go = 1 + t / b;
  for (int i = 1; i < m; ++i) {
    if (go < s[i]) {
      break;
    } else {
      long long rest = (t - (s[i] - s[1]) * b) / a;
      answer += min(s[i] + rest, (long long) s[i + 1] - 1) - s[i] + 1;
      if (s[i] + rest < s[i + 1] - 1) {
        que.emplace(i, s[i] + rest, solve(i, s[i] + rest + 1));
      }
    }
  }
  if (go >= s[m]) {
    ++answer;
  }
  while (!que.empty() && k--) {
    node_t x = que.top();
    que.pop();
    answer += x.next_num;
    if (x.p + x.next_num < s[x.i + 1] - 1) {
      que.emplace(x.i, x.p + x.next_num, solve(x.i, x.p + x.next_num + 1));
    }
  }
  printf("%d\n", --answer);
  return 0;
}
