#include<bits/stdc++.h>

using namespace std;

#define rg register
#define pb push_back

typedef long long ll;

const int N = 2e5 + 10;

int n, a[N], tag[N * 5];

int main() {
  scanf("%d", &n);
  ll res = 0;
  for (rg int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]), ++tag[a[i]];
    res += a[i];
  }
  vector<int> ans;
  for (rg int i = 1; i <= n; ++i) {
    --tag[a[i]], res -= a[i];
    if (!(res & 1) && (res / 2 <= 1000000) && tag[res / 2]) {
      ans.pb(i);
    }
    ++tag[a[i]], res += a[i];
  }
  printf("%d\n", ans.size());
  for (auto v : ans) {
    printf("%d ", v);
  }
  puts("");
  return 0;
}
