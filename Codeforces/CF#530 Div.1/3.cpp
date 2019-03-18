#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, p[N], depth[N], degree[N];
long long s;

long long solve(int x) {
  int rest = n, v = 1;
  long long t = 1, answer = 0;
  for (; rest; rest -= t, t *= x, ++v) {
    t = min(t, (long long) rest);
    answer += (long long) t * v;
  }
  return answer;
}

int main() {
  scanf("%d%lld", &n, &s);
  if (s < 2 * n - 1 || s > (long long) n * (n + 1) >> 1) {
    puts("No");
  } else {
    puts("Yes");
    int l = 1, r = n - 1;
    while (l != r) {
      int mid = l + r >> 1;
      if (s < solve(mid)) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    depth[1] = 1;
    for (int i = 2; i <= n; ++i) {
      p[i] = (i - 2) / l + 1;
      depth[i] = depth[p[i]] + 1;
      ++degree[p[i]];
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;
    for (int i = 2; i < n; ++i) {
      if (!degree[i]) {
        que.emplace(depth[i], i);
      }
    }
    int max_depth = depth[n], max_u = n;
    long long sum = solve(l);
    while (sum < s) {
      int x = que.top().second;
      que.pop();
      if (--degree[p[x]] == 0) {
        que.emplace(depth[p[x]], p[x]);
      }
      if (sum - depth[x] + max_depth + 1 <= s) {
        sum += -depth[x] + max_depth + 1;
        p[x] = max_u;
        depth[x] = ++max_depth;
        ++degree[max_u];
        max_u = x;
      } else {
        for (int i = 1; i <= n; ++i) {
          if (i != x && degree[i] < l && sum - depth[x] + depth[i] + 1 == s) {
            sum += -depth[x] + depth[i] + 1;
            p[x] = i;
            break;
          }
        }
      }
    }
    for (int i = 2; i <= n; ++i) {
      printf("%d%c", p[i], " \n"[i == n]);
    }
  }
  return 0;
}
