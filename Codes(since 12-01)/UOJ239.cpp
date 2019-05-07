#include<bits/stdc++.h>
#include "messy.h"

using namespace std;

vector<int> restore_permutation(int n, int w, int r) {
  function<void (int, int)> divide = [&] (int l, int r) {
    if (l != r) {
      int mid = l + r >> 1;
      string x(n, '0');
      for (int i = 0; i < l; ++i) {
        x[i] = '1';
      }
      for (int i = r + 1; i < n; ++i) {
        x[i] = '1';
      }
      for (int i = l; i <= mid; ++i) {
        x[i] = '1';
        add_element(x);
        x[i] = '0';
      }
      divide(l, mid);
      divide(mid + 1, r);
    }
  };
  divide(0, n - 1);
  compile_set();
  vector<int> answer(n), used(n);
  for (int i = 0; i < n; ++i) {
    used[i] = i;
  }
  function<void (int, int, vector<int>&)> solve = [&] (int l, int r, vector<int>& used) {
    if (l == r) {
      answer[used.back()] = l;
    } else {
      int mid = l + r >> 1;
      string x(n, '1');
      for (auto p : used) {
        x[p] = '0';
      }
      vector<int> to_left, to_right;
      for (auto p : used) {
        x[p] = '1';
        if (check_element(x)) {
          to_left.push_back(p);
        } else {
          to_right.push_back(p);
        }
        x[p] = '0';
      }
      solve(l, mid, to_left);
      solve(mid + 1, r, to_right);
    }
  };
  solve(0, n - 1, used);
  return answer;
}
