#include<bits/stdc++.h>
#include "paint.h"

using namespace std;

const int N = 234567;

int sum_white[N], diff[N];
bool f[N][105], fmust[N][105], g[N][105], gmust[N][105];

bool no_white(int l, int r) {
  return sum_white[r] - sum_white[l - 1] == 0;
}

string solve_puzzle(string s, vector<int> c) {
  int n = s.length(), k = c.size();
  for (int i = 0; i < n; ++i) {
    sum_white[i + 1] = sum_white[i] + (s[i] == '_');
  }
  f[0][0] = g[n + 1][0] = true;
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= k; ++j) {
      if (s[i - 1] != 'X') {
        f[i][j] = f[i - 1][j];
      }
      if (j) {
        if (i == c[j - 1] && no_white(1, i)) {
          fmust[i][j] |= f[0][j - 1];
        } else if (i > c[j - 1] && no_white(i - c[j - 1] + 1, i) && s[i - c[j - 1] - 1] != 'X') {
          fmust[i][j] |= f[i - c[j - 1] - 1][j - 1];
        }
        f[i][j] |= fmust[i][j];
      }
    }
  }
  reverse(c.begin(), c.end());
  for (int i = n; i; --i) {
    for (int j = 0; j <= k; ++j) {
      if (s[i - 1] != 'X') {
        g[i][j] = g[i + 1][j];
      }
      if (j) {
        if (n - i + 1 == c[j - 1] && no_white(i, n)) {
          gmust[i][j] |= g[n + 1][j - 1];
        } else if (n - i + 1 > c[j - 1] && no_white(i, i + c[j - 1] - 1) && s[i + c[j - 1] - 1] != 'X') {
          gmust[i][j] |= g[i + c[j - 1] + 1][j - 1];
        }
        g[i][j] |= gmust[i][j];
      }
    }
  }
  reverse(c.begin(), c.end());
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= k; ++j) {
      if (fmust[i][j]) {
        if ((i == n && j == k) || (i < n && s[i] != 'X' && g[i + 2][k - j])) {
          ++diff[i - c[j - 1] + 1];
          --diff[i + 1];
        }
      }
    }
  }
  reverse(c.begin(), c.end());
  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= k; ++j) {
      if (gmust[i][j]) {
        if ((i == 1 && j == k) || (i > 1 && s[i - 2] != 'X' && f[i - 2][k - j])) {
          ++diff[i];
          --diff[i + c[j - 1]];
        }
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    diff[i] += diff[i - 1];
  }
  string answer = "";
  for (int i = 1; i <= n; ++i) {
    if (s[i - 1] == 'X') {
      answer += "X";
    } else if (s[i - 1] == '_') {
      answer += "_";
    } else {
      bool foo = false;
      for (int j = 0; j <= k; ++j) {
        if (f[i - 1][j] & g[i + 1][k - j]) {
          foo = true;
        }
      }
      if (!foo) {
        answer += "X";
      } else {
        if (diff[i]) {
          answer += "?";
        } else {
          answer += "_";
        }
      }
    }
  }
  return answer;
}
