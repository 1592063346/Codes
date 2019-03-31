#include<bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10;

int n, m;
unsigned int a[N], sum[N], c[N], answer[N];
vector<pair<int, int> > event[N];
map<unsigned int, int> last;

void modify(int x, unsigned int value) {
  for (; x; x -= x & -x) {
    c[x] ^= value;
  }
}

unsigned int query(int x) {
  int result = 0;
  for (; x <= n; x += x & -x) {
    result ^= c[x];
  }
  return result;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%u", &a[i]);
    sum[i] = sum[i - 1] ^ a[i];
  }
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    event[r].push_back(make_pair(l, i));
  }
  for (int i = 1; i <= n; ++i) {
    if (last[a[i]]) {
      modify(last[a[i]], a[i]);
    }
    modify(i, a[i]);
    last[a[i]] = i;
    for (int j = 0; j < event[i].size(); ++j) {
      pair<int, int> p = event[i][j];
      answer[p.second] = sum[i] ^ sum[p.first - 1] ^ query(p.first);
    }
  }
  for (int i = 1; i <= m; ++i) {
    printf("%u\n", answer[i]);
  }
  return 0;
}
