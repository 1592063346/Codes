#include<bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  vector<pair<int, int>> a(n), b(n);
  vector<int> answera(n), answerb(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i].first;
    a[i].second = i;
  }
  for (int i = 0; i < n; ++i) {
    cin >> b[i].first;
    b[i].second = i;
  }
  sort(a.begin(), a.end(), greater<pair<int, int>>());
  sort(b.begin(), b.end(), greater<pair<int, int>>());
  long long sa = 0, sb = 0, answer = 0;
  int ga = 0, gb = 0;
  for (int i = 0, j = 0; i < n; ++i) {
    sa += a[i].first;
    while (j < n && sb < sa) {
      sb += b[j++].first;
    }
    if (answer < min(sa, sb) - i - j - 1) {
      answer = min(sa, sb) - i - j - 1;
      ga = i + 1;
      gb = j;
    }
  }
  sa = sb = 0;
  for (int i = 0, j = 0; i < n; ++i) {
    sb += b[i].first;
    while (j < n && sa < sb) {
      sa += a[j++].first;
    }
    if (answer < min(sa, sb) - i - j - 1) {
      answer = min(sa, sb) - i - j - 1;
      ga = j;
      gb = i + 1;
    }
  }
  cout << answer << '\n';
  for (int i = 0; i < ga; ++i) {
    answera[a[i].second] = true;
  }
  for (int i = 0; i < gb; ++i) {
    answerb[b[i].second] = true;
  }
  for (int i = 0; i < n; ++i) {
    cout << answera[i] << " \n"[i + 1 == n];
  }
  for (int i = 0; i < n; ++i) {
    cout << answerb[i] << " \n"[i + 1 == n];
  }
  return 0;
}
