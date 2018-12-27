#include<bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

int n, m1, m2, c1, c2, p, need[N], rest[N], stack_slow[N], stack_quick[N], top_slow, top_quick;

int check(int new_number) {
  top_slow = top_quick = 0;
  int cost = 0;
  memset(rest, 0, sizeof rest);
  for (int i = 1; i <= n; ++i) {
    if (i - m1 > 0) {
      stack_slow[++top_slow] = i - m1;
    }
    if (i - m2 > 0) {
      stack_quick[++top_quick] = i - m2;
    }
    int number = min(need[i] - rest[i], new_number);
    new_number -= number;
    rest[i] += number;
    cost += p * number;
    for (; top_slow && rest[i] < need[i];) {
      if (!rest[stack_slow[top_slow]]) {
        --top_slow;
      } else {
        int number = min(need[i] - rest[i], rest[stack_slow[top_slow]]);
        rest[stack_slow[top_slow]] -= number;
        rest[i] += number;
        cost += c1 * number;
      }
    }
    for (; top_quick && rest[i] < need[i];) {
      if (!rest[stack_quick[top_quick]]) {
        --top_quick;
      } else {
        int number = min(need[i] - rest[i], rest[stack_quick[top_quick]]);
        rest[stack_quick[top_quick]] -= number;
        rest[i] += number;
        cost += c2 * number;
      }
    }
    if (rest[i] < need[i]) {
      return INT_MAX;
    }
  }
  return cost;
}

int main() {
  scanf("%d%d%d%d%d%d", &n, &m1, &m2, &c1, &c2, &p);
  if (c1 > c2) {
    swap(c1, c2);
    swap(m1, m2);
    m2 = min(m2, m1);
  }
  int l = 1, r = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &need[i]);
    r += need[i];
  }
  while (r - l > 2) {
    int mid1 = l + (r - l) / 3;
    int mid2 = r - (r - l) / 3;
    int value1 = check(mid1), value2 = check(mid2);
    if (value1 == INT_MAX || value1 >= value2) {
      l = mid1;
    } else {
      r = mid2;
    }
  }
  int answer = INT_MAX;
  for (int i = l; i <= r; ++i) {
    answer = min(answer, check(i));
  }
  printf("%d\n", answer);
  return 0;
}
