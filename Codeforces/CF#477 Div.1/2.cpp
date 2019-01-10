#include<bits/stdc++.h>

using namespace std;

const int N = 3e5 + 10;

int n, x1, x2, used[N];
pair<int, int> c[N];
vector<int> sa, sb;

bool solve(int x1, int x2) {
  int total = 0, total_k = 0, i;
  vector<int> a, b;
  bool ok = false;
  for (i = n; i; --i) {
    a.push_back(c[i].second);
    total += c[i].first;
    ++total_k;
    if (total >= x1 && c[i].first >= (x1 - 1) / total_k + 1) {
      ok = true;
      break;
    }
  }
  if (!ok) {
    return false;
  }
  total = 0;
  total_k = 0;
  ok = false;
  for (--i; i; --i) {
    b.push_back(c[i].second);
    total += c[i].first;
    ++total_k;
    if (total >= x2 && c[i].first >= (x2 - 1) / total_k + 1) {
      ok = true;
      break;
    }
  }
  if (!ok) {
    return false;
  }
  sa = a;
  sb = b;
  return true;
}

void print() {
  puts("Yes");
  printf("%d %d\n", sa.size(), sb.size());
  for (int i = 0; i < sa.size(); ++i) {
    printf("%d%c", sa[i], " \n"[i + 1 == sa.size()]);
  }
  for (int i = 0; i < sb.size(); ++i) {
    printf("%d%c", sb[i], " \n"[i + 1 == sb.size()]);
  }
}

int main() {
  scanf("%d%d%d", &n, &x1, &x2);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &c[i].first);
    c[i].second = i;
  }
  sort(c + 1, c + 1 + n);
  if (!solve(x1, x2)) {
    if (!solve(x2, x1)) {
      puts("No");
    } else {
      swap(sa, sb);
      print();
    }
  } else {
    print();
  }
  return 0;
}
