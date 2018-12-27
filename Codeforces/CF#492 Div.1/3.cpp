#include<bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

int n, dx[N], dy[N], answer[N];

long long dist(int x, int y) {
  return (long long) x * x + (long long) y * y;
}

bool better(pair<int, int> o, int x, int y) {
  return dist(o.first + x, o.second + y) <= dist(o.first - x, o.second - y);
}

int main() {
  scanf("%d", &n);
  pair<int, int> vec(0, 0);
  for (int i = 1; i <= n; ++i) {
    scanf("%d%d", &dx[i], &dy[i]);
    if (better(vec, dx[i], dy[i])) {
      vec.first += dx[i];
      vec.second += dy[i];
      answer[i] = 1;
    } else {
      vec.first -= dx[i];
      vec.second -= dy[i];
      answer[i] = -1;
    }
  }
  for (int i = 1; i <= n; ++i) {
    vec.first -= answer[i] * dx[i];
    vec.second -= answer[i] * dy[i];
    if (better(vec, -answer[i] * dx[i], -answer[i] * dy[i])) {
      vec.first -= answer[i] * dx[i];
      vec.second -= answer[i] * dy[i];
      answer[i] = -answer[i];
    } else {
      vec.first += answer[i] * dx[i];
      vec.second += answer[i] * dy[i];
    }
  }
  for (int i = 1; i <= n; ++i) {
    printf("%d%c", answer[i], " \n"[i == n]);
  }
  return 0;
}
