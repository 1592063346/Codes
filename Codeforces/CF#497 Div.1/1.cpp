#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, a[N];

int main() {
  scanf("%d", &n);
  multiset<int> s;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    s.insert(a[i]);
  }
  sort(a + 1, a + 1 + n);
  int answer = 0;
  for (int i = n; i; --i) {
    multiset<int>:: iterator it = s.lower_bound(a[i]);
    if (it != s.begin()) {
      --it;
      ++answer;
      s.erase(it);
    }
  }
  printf("%d\n", answer);
  return 0;
}
