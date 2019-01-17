#include<bits/stdc++.h>

using namespace std;

const int whole = 360;

int main() {
  int tt, ta;
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d", &ta);
    ta <<= 1;
    int answer = whole / __gcd(whole, ta);
    if (ta >= 180 && whole / answer == whole - ta) {
      answer <<= 1;
    }
    printf("%d\n", answer);
  }
  return 0;
}
