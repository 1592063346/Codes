#include<bits/stdc++.h>

using namespace std;

const int N = 1234567;

long long t;
bool visit[N];
int p, q, n, m, value[N], sum[N];
pair<int, int> id[N];
vector<int> circle[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> p >> q >> n >> m >> t;
  while (n--) {
    int x;
    cin >> x;
    value[x] = 1;
  }
  for (int i = 0, j = -1; i < p; ++i) {
    if (visit[i]) {
      continue;
    }
    ++j;
    int x = i;
    while (!visit[x]) {
      circle[j].push_back(value[x]);
      id[x] = {j, circle[j].size() - 1};
      visit[x] = true;
      x += q;
      x %= p;
    }
    int y = circle[j].size();
    for (int k = 0; k < y; ++k) {
      circle[j].push_back(circle[j][k]);
    }
    for (int k = 1; k < circle[j].size(); ++k) {
      circle[j][k] += circle[j][k - 1];
    }
    sum[j] = circle[j][y - 1];
  }
  int period = p / __gcd(p, q);
  long long answer = 0;
  while (m--) {
    int x;
    cin >> x;
    long long up = (t - 1 - x) / q + 1;
    x %= p;
    int belong = id[x].first;
    answer += up / period * sum[belong];
    up %= period;
    if (up) {
      answer += circle[belong][id[x].second + up - 1] - (!id[x].second ? 0 : circle[belong][id[x].second - 1]);
    }
  }
  cout << answer << '\n';
  return 0;
}
