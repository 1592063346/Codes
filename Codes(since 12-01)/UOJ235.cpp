#include "molecules.h"
#include<bits/stdc++.h>

using namespace std;

vector<int> find_subset(int l, int u, vector<int> w) {
  vector<pair<long long, int>> values;
  int n = w.size();
  values.emplace_back(0, 0);
  for (int i = 0; i < n; ++i) {
    values.emplace_back(w[i], i);
  }
  sort(values.begin(), values.end());
  for (int i = 1; i <= n; ++i) {
    values[i].first += values[i - 1].first;
  }
  for (int i = 1; i <= n; ++i) {
    int x = lower_bound(values.begin(), values.end(), pair<long long, int>(values[i].first - u, 0)) - values.begin();
    if (values[i].first - values[x].first >= l) {
      vector<int> result;
      for (int j = x + 1; j <= i; ++j) {
        result.push_back(values[j].second);
      }
      return result;
    }
  }
  return vector<int>();
}
