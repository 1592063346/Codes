#include<bits/stdc++.h>

using namespace std;

const int N = 123456;

int x, y, z, n;

struct info_t {
  int a, b, c;
} info[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> x >> y >> z;
  n = x + y + z;
  for (int i = 1; i <= n; ++i) {
    cin >> info[i].a >> info[i].b >> info[i].c;
  }
  sort(info + 1, info + 1 + n, [&] (const info_t& x, const info_t& y) {
    return x.b - x.a < y.b - y.a;
  });
  multiset<int> heap1, heap2, heap3;
  long long answer = 0;
  for (int i = 1; i <= n; ++i) {
    answer += info[i].c;
  }
  for (int i = 1; i <= x; ++i) {
    heap1.insert(info[i].a - info[i].c);
  }
  for (int i = x + 1; i <= n; ++i) {
    heap2.insert(info[i].b - info[i].c);
  }
  while (heap2.size() > y) {
    heap3.insert(*heap2.begin());
    heap2.erase(heap2.begin());
  }
  for (auto x : heap1) {
    answer += x;
  }
  for (auto x : heap2) {
    answer += x;
  }
  long long t = answer;
  for (int i = x + 1; i <= n - y; ++i) {
    int foo = info[i].b - info[i].c, bar = info[i].a - info[i].c;
    if (heap2.find(foo) != heap2.end()) {
      int add = *(--heap3.end());
      heap3.erase(heap3.find(add));
      heap2.erase(heap2.find(foo));
      heap2.insert(add);
      t -= foo;
      t += add;
    } else {
      heap3.erase(heap3.find(foo));
    }
    if (bar >= *heap1.begin()) {
      t -= *heap1.begin();
      t += bar;
      heap1.erase(heap1.begin());
      heap1.insert(bar);
    }
    answer = max(answer, t);
  }
  cout << answer << '\n';
  return 0;
}
