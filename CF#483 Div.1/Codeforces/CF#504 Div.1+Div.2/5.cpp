#include<bits/stdc++.h>

using namespace std;

bool query(int x, int y, int goal_x, int goal_y) {
  printf("? %d %d %d %d\n", x, y, goal_x, goal_y);
  fflush(stdout);
  char reply[5];
  scanf("%s", reply);
  return *reply == 'Y';
}

int n;

int main() {
  scanf("%d", &n);
  pair<int, int> now (1, 1);
  vector<int> steps1, steps2;
  for (int i = 1; i < n; ++i) {
    if (query(now.first, now.second + 1, n, n)) {
      steps1.push_back(0);
      ++now.second;
    } else {
      steps1.push_back(1);
      ++now.first;
    }
  }
  now = pair<int, int> (n, n);
  for (int i = 1; i < n; ++i) {
    if (query(1, 1, now.first - 1, now.second)) {
      steps2.push_back(1);
      --now.first;
    } else {
      steps2.push_back(0);
      --now.second;
    }
  }
  reverse(steps2.begin(), steps2.end());
  printf("! ");
  for (auto v : steps1) {
    printf("%c", v ? 'D' : 'R');
  }
  for (auto v : steps2) {
    printf("%c", v ? 'D' : 'R');
  }
  return 0;
}
