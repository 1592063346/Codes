#include<bits/stdc++.h>

using namespace std;

const int N = 234567;

int n, m, t, tt, a[N], b[N], h[N], root[2][N], number[2][N];
long long s[N], sum_value;

struct node_t {
  int l, r, number;
  long long sum;
} nodes[N * 20];

int modify(int l, int r, int o, int p) {
  int x = ++tt;
  nodes[x] = nodes[o];
  ++nodes[x].number;
  nodes[x].sum += h[p];
  if (l != r) {
    int mid = l + r >> 1;
    if (p <= mid) {
      nodes[x].l = modify(l, mid, nodes[o].l, p);
    } else {
      nodes[x].r = modify(mid + 1, r, nodes[o].r, p);
    }
  }
  return x;
}

int query(int l, int r, int ll, int rr, int k) {
  if (l == r) {
    sum_value += (long long) h[l] * k;
    return h[l];
  } else {
    int mid = l + r >> 1;
    if (nodes[nodes[rr].r].number - nodes[nodes[ll].r].number >= k) {
      return query(mid + 1, r, nodes[ll].r, nodes[rr].r, k);
    } else {
      sum_value += nodes[nodes[rr].r].sum - nodes[nodes[ll].r].sum;
      return query(l, mid, nodes[ll].l, nodes[rr].l, k - nodes[nodes[rr].r].number + nodes[nodes[ll].r].number);
    }
  }
}

pair<int, long long> query(int opt, int l, int r, int k) {
  sum_value = 0;
  pair<int, long long> result;
  result.first = query(1, t, root[opt][l - 1], root[opt][r], k);
  result.second = sum_value;
  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    b[i] = a[i] - a[i - 1];
    s[i] = s[i - 1] + abs(b[i]);
    h[++t] = abs(b[i]) << 1;
  }
  sort(h + 1, h + 1 + t);
  t = unique(h + 1, h + 1 + t) - h - 1;
  for (int i = 1; i <= n; ++i) {
    int sgn = b[i] > 0 ? 1 : -1;
    b[i] = abs(b[i]) << 1;
    b[i] = lower_bound(h + 1, h + 1 + t, b[i]) - h;
    if (sgn == 1) {
      root[0][i] = modify(1, t, root[0][i - 1], b[i]);
      root[1][i] = root[1][i - 1];
      number[0][i] = number[0][i - 1] + 1;
      number[1][i] = number[1][i - 1];
    } else {
      root[0][i] = root[0][i - 1];
      root[1][i] = modify(1, t, root[1][i - 1], b[i]);
      number[0][i] = number[0][i - 1];
      number[1][i] = number[1][i - 1] + 1;
    }
  }
  while (m--) {
    int l, r, k;
    cin >> l >> r >> k;
    int add0 = a[l], add1 = a[r], number0 = number[0][r] - number[0][l], number1 = number[1][r] - number[1][l];
    long long sum = s[r] - s[l] + add0 + add1, answer = sum;
    add0 <<= 1;
    add1 <<= 1;
    int ll = 1, rr = min(number0, number1) + 1;
    while (1) {
      int mid = ll != rr ? (ll + rr >> 1) + 1 : ll;
      pair<int, long long> result0 = query(0, l + 1, r, min(mid, number0));
      pair<int, long long> result1 = query(1, l + 1, r, min(mid, number1));
      if (mid == number0 + 1) {
        result0.first = min(result0.first, add0);
        result0.second += add0;
      } else if (result0.first < add0) {
        result0 = query(0, l + 1, r, mid - 1);
        result0.first = min(result0.first, add0);
        result0.second += add0;
      }
      if (mid == number1 + 1) {
        result1.first = min(result1.first, add1);
        result1.second += add1;
      } else if (result1.first < add1) {
        result1 = query(1, l + 1, r, mid - 1);
        result1.first = min(result1.first, add1);
        result1.second += add1;
      }
      result0.first -= k;
      result1.first -= k;
      result0.second -= (long long) mid * k;
      result1.second -= (long long) mid * k;
      answer = min(answer, sum - result0.second - result1.second);
      if (ll == rr) {
        break;
      } else if ((long long) result0.first + result1.first >= 0) {
        ll = mid;
      } else {
        rr = mid - 1;
      }
    }
    cout << (answer >> 1) << '\n';
  }
  return 0;
}
