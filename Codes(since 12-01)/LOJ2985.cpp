#include<bits/stdc++.h>
#include "shop.h"

using namespace std;

const int N = 1e5 + 10;

int s[2], t[2], pos[N];

bool query_1_1(int i, int j) {
  s[0] = i;
  t[0] = j;
  return query(s, 1, t, 1);
}

bool query_1_2(int i, int j, int k) {
  s[0] = i;
  t[0] = j;
  t[1] = k;
  return query(s, 1, t, 2);
}

void find_price(int task_id, int n, int k, int* ans) {
  memset(ans, 0, sizeof ans);
  if (task_id == 3) {
    for (int i = 0; i < n; ++i) {
      pos[i] = i;
    }
    if (!query_1_1(0, n - 1)) {
      reverse(pos, pos + n);
    }
    int l = 0, r = n - 2, tmp = n - 1;
    while (l <= r) {
      int mid = l + r >> 1;
      if (query_1_2(pos[n - 1], pos[mid], pos[mid + 1])) {
        tmp = mid;
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    for (int i = tmp + 1; i < n; ++i) {
      ans[pos[i]] = 1;
      k = !k;
    }
    if (k) {
      ans[pos[tmp]] = 1;
    }
    return;
  }
  int p1 = 0;
  if (task_id != 6) {
    for (int i = 1; i < n; ++i) {
      if (!query_1_1(i, p1)) {
        p1 = i;
      }
    }
  } else {
    // :)
    srand(233);
    for (int i = 1; i < 50; ++i) {
      int x = rand() % n;
      if (!query_1_1(x, p1)) {
        p1 = x;
      }
    }
  }
  ans[p1] = 1;
  k = !k;
  vector<int> unk;
  for (int i = 0; i < n; ++i) {
    if (i != p1) {
      unk.push_back(i);
    }
  }
  for (int i = 1; i < unk.size(); ++i) {
    if (query_1_2(p1, unk[i - 1], unk[i])) {
      k = !k;
      if (query_1_1(unk[i - 1], unk[i])) {
        swap(unk[i - 1], unk[i]);
      }
      ans[unk[i - 1]] = 1;
    } else {
      if (!query_1_1(unk[i - 1], unk[i])) {
        swap(unk[i - 1], unk[i]);
      }
    }
  }
  if (unk.size() && k) {
    ans[unk.back()] = 1;
  }
}
