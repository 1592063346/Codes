#include<bits/stdc++.h>

using namespace std;

int b, k;

int main() {
  scanf("%d%d", &b, &k);
  int answer = 0;
  for (int i = 1; i <= k; ++i) {
    int x;
    scanf("%d", &x);
    answer += (x & 1) * ((i == k ? 1 : b) & 1);
  }
  puts(answer & 1 ? "odd" : "even");
  return 0;
}
