#include<bits/stdc++.h>

using namespace std;

int n, m, q;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m;
  m <<= 1;
  vector<long long> buffer(1 << m);
  auto get_number = [&] (string x) {
    int y = 0;
    for (int i = 0; i < m; i += 2) {
      y |= x[i >> 1] - '1' << i;
    }
    return y;
  };
  while (n--) {
    string x;
    cin >> x;
    ++buffer[get_number(x)];
  }
  auto pre_sum = [&] (vector<long long> buffer) {
    vector<long long> result = buffer;
    for (int i = 0; i < m; i += 2) {
      for (int j = 0; j < 1 << m; ++j) {
        int here = j >> i & 3;
        if (here) {
          result[j] += result[j ^ (here << i) ^ (here - 1 << i)];
        }
      }
    }
    return result;
  };
  auto suf_sum = [&] (vector<long long> buffer) {
    vector<long long> result = buffer;
    for (int i = 0; i < m; i += 2) {
      for (int j = (1 << m) - 1; ~j; --j) {
        int here = j >> i & 3;
        if (here < 3) {
          result[j] += result[j ^ (here << i) ^ (here + 1 << i)];
        }
      }
    }
    return result;
  };
  auto pre_sub = [&] (vector<long long> buffer) {
    vector<long long> result = buffer;
    for (int i = m - 2; i >= 0; i -= 2) {
      for (int j = (1 << m) - 1; ~j; --j) {
        int here = j >> i & 3;
        if (here) {
          result[j] -= result[j ^ (here << i) ^ (here - 1 << i)];
        }
      }
    }
    return result;
  };
  auto suf_sub = [&] (vector<long long> buffer) {
    vector<long long> result = buffer;
    for (int i = m - 2; i >= 0; i -= 2) {
      for (int j = 0; j < 1 << m; ++j) {
        int here = j >> i & 3;
        if (here < 3) {
          result[j] -= result[j ^ (here << i) ^ (here + 1 << i)];
        }
      }
    }
    return result;
  };
  vector<long long> pre_s = pre_sum(buffer), pre_mul = pre_s;
  vector<long long> suf_s = suf_sum(buffer), suf_mul = suf_s;
  for (int i = 0; i < 1 << m; ++i) {
    pre_mul[i] *= pre_mul[i];
    suf_mul[i] *= suf_mul[i];
  }
  pre_mul = pre_sub(pre_mul);
  suf_mul = suf_sub(suf_mul);
  vector<long long> s1 = pre_sum(pre_mul);
  vector<long long> s2 = suf_sum(suf_mul);
  vector<long long> s3 = suf_sum(pre_mul);
  vector<long long> s4 = pre_sum(suf_mul);
  cin >> q;
  while (q--) {
    int type, y;
    string x;
    cin >> type >> x;
    y = get_number(x);
    if (type == 1) {
      cout << (s1[y] - pre_s[y] >> 1) << '\n';
    } else if (type == 2) {
      cout << (s2[y] - suf_s[y] >> 1) << '\n';
    } else if (type == 3) {
      cout << (s3[y] - suf_s[y] >> 1) << '\n';
    } else {
      cout << (s4[y] - pre_s[y] >> 1) << '\n';
    }
  }
  return 0;
}
