#include<bits/stdc++.h>

using namespace std;

const int N = 3456789;

string x;
int n, lcp[N];

void get_lcp() {
  lcp[0] = n;
  lcp[1] = 0;
  for (; x[1 + lcp[1]] == x[lcp[1]]; ++lcp[1]);
  int p = 1, r = p + lcp[1] - 1;
  for (int i = 2; i < n; ++i) {
    int len = lcp[i - p];
    if (i - 1 + len < r) {
      lcp[i] = len;
    } else {
      lcp[i] = max(0, r - i + 1);
      for (; x[i + lcp[i]] == x[lcp[i]]; ++lcp[i]);
      if (i + lcp[i] - 1 > r) {
        p = i;
        r = i + lcp[i] - 1;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> x;
  n = x.length();
  get_lcp();
  vector<int> foo, bar;
  for (int k = 0; k < n; ++k) {
    bar = vector<int>(1, k);
    for (auto i : foo) {
      if (bar.size() && x[i + k - bar.back()] > x[k]) {
        continue;
      }
      while (bar.size() && x[i + k - bar.back()] < x[k]) {
        bar.pop_back();
      }
      while (bar.size() && k - bar.back() >= bar.back() - i) {
        bar.pop_back();
      }
      bar.push_back(i);
    }
    foo = bar;
    int answer = foo[0];
    for (int t = 1; t < foo.size(); ++t) {
      int i = foo[t], j = answer;
      if (lcp[i + k - j + 1] < j - i) {
        int p = lcp[i + k - j + 1];
        answer = x[p] < x[i + k - j + p + 1] ? j : i;
        continue;
      }
      if (lcp[j - i] < i) {
        int p = lcp[j - i];
        answer = x[j - i + p] < x[p] ? j : i;
        continue;
      }
      answer = i;
    }
    cout << (answer + 1) << " \n"[k == n - 1];
  }
  return 0;
}
