#include<bits/stdc++.h>

using namespace std;

int m;
long long n, k, b;

double slope(pair<long long, long long> x, pair<long long, long long> y) {
  return (double) (y.second - x.second) / (y.first - x.first);
}

long long f(pair<long long, long long> x) {
  return k * x.first + b + x.second;
}

int main() {
  scanf("%lld%d", &n, &m);
  vector<pair<long long, long long>> convex(1, {0, 0});
  while (m--) {
    int opt, len, c, d;
    pair<long long, long long> add;
    scanf("%d", &opt);
    switch (opt) {
      case 1:
        scanf("%d", &len);
        n += len;
        convex = vector<pair<long long, long long>>(1, {0, 0});
        k = 0;
        b = 0;
        break;
      case 2:
        scanf("%d", &len);
        add = {n, -(k * n + b)};
        n += len;
        for (int i; (i = convex.size()) > 1 && slope(add, convex[i - 1]) <= slope(convex[i - 1], convex[i - 2]); convex.pop_back());
        convex.push_back(add);
        break;
      case 3:
        scanf("%d%d", &d, &c);
        k += c;
        b += d;
        break;
    }
    for (int i; (i = convex.size()) > 1 && f(convex[i - 1]) >= f(convex[i - 2]); convex.pop_back());
    printf("%lld %lld\n", convex.back().first + 1, f(convex.back()));
  }
  return 0;
}
