#include<bits/stdc++.h>

using namespace std;

const int N = 2345;

int n;
bitset<N> beat[N], ll[N], rr[N];
bool dp_l[N][N], dp_r[N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n;
  for (int i = 2; i <= n; ++i) {
    string s;
    cin >> s;
    for (int j = 1; j < i; ++j) {
      if (s[j - 1] == '1') {
        beat[i][j] = true;
      } else {
        beat[j][i] = true;
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    dp_l[i][i] = dp_r[i][i] = ll[i][i] = rr[i][i] = true;
  }
  for (int i = 2; i <= n; ++i) {
    bitset<N> seg;
    for (int j = 0; j < i; ++j) {
      seg[j] = true;
    }
    for (int j = 1; j + i - 1 <= n; ++j) {
      int x = j, y = j + i - 1;
      seg[x - 1] = false;
      seg[y] = true;
      bitset<N> result = beat[x] & rr[x + 1] & ll[y] & seg;
      if (result.count()) {
        dp_l[x][y] = ll[y][x] = true;
      }
      result = beat[y] & ll[y - 1] & rr[x] & seg;
      if (result.count()) {
        dp_r[x][y] = rr[x][y] = true;
      }
    }
  }
  int answer = 0;
  for (int i = 1; i <= n; ++i) {
    if (dp_r[1][i] && dp_l[i][n]) {
      ++answer;
    }
  }
  cout << answer << '\n';
  return 0;
}
