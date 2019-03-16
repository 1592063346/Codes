#include<bits/stdc++.h>

using namespace std;

int print(const char* msg) {
  printf("%s\n", msg);
  fflush(stdout);
  int x;
  scanf("%d", &x);
  for (int i = 0; i < x; ++i) {
    scanf("%*s");
  }
  return x;
}

int main() {
  while (1) {
    print("next 0");
    if (print("next 0 1") == 2) {
      break;
    }
  }
  while (1) {
    if (print("next 0 1 2 3 4 5 6 7 8 9") == 1) {
      break;
    }
  }
  print("done");
  return 0;
}
