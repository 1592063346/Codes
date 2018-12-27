#include<bits/stdc++.h>

using namespace std;

#define X first
#define Y second
#define rg register
#define mp make_pair

typedef pair<int, int> pii;

const int N = 2e5 + 10;

int n, k, a[N], tag[N], times[N];

priority_queue<pii> Q;

int main() {
  scanf("%d%d", &n, &k);
  for (rg int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]), ++tag[a[i]];
  }
  for (rg int i = 1; i <= 200000; ++i) {
    Q.push(mp(tag[i], i)), ++times[i];
  }
  for (rg int i = 1; i <= k; ++i) {
    pii x = Q.top(); Q.pop();
    printf("%d%c", x.Y, " \n"[i == k]);
    Q.push(mp(tag[x.Y] / ++times[x.Y], x.Y));
  }
  return 0;
}
