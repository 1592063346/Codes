#include<bits/stdc++.h>

using namespace std;

int f(int x) {
  if (x & 1) {
    return x % 4 == 1 ? 1 + (x - 1) / 4 * 8 : 7 + (x - 3) / 4 * 8;
  } else {
    return x % 4;
  }
}

struct state {
  int first, second;

  state () {}
  state (int first, int second): first(first), second(second) {}

  bool operator < (const state& a) const {
    return first < a.first;
  }
};

set<state> interval;

bool check(int l, state x) {
  return l >= x.first && l <= x.second;
}

int q;

int main() {
  scanf("%d", &q);
  long long answer = 0;
  for (int i = 1; i <= q; ++i) {
    int type, l, r;
    scanf("%d", &type);
    if (type == 1) {
      scanf("%d%d", &l, &r);
      state new_interval = state (l, r);
      set<state>:: iterator it = interval.lower_bound(new_interval), pos, pl, pr;
      if (it != interval.begin()) {
        --it;
      }
      vector<state> del;
      for (bool appeared = false; it != interval.end(); ++it) {
        int ll = (*it).first, rr = (*it).second;
        if (check(rr, new_interval) || check(ll, new_interval) || check(new_interval.first, *it) || check(new_interval.second, *it)) {
          l = min(l, ll);
          r = max(r, rr);
          appeared = true;
          if (it != interval.begin()) {
            pos = it;
            --pos;
            answer ^= (long long) ll * ll - (long long) (*pos).second * (*pos).second;
          }
          answer ^= f(rr) ^ f(ll);
          del.emplace_back(ll, rr);
        } else if (appeared) {
          pos = it;
          --pos;
          answer ^= (long long) ll * ll - (long long) (*pos).second * (*pos).second;
          break;
        }
        if (ll > new_interval.second) {
          break;
        }
      }
      for (auto v : del) {
        interval.erase(state (v.first, v.second));
      }
      new_interval = state (l, r);
      interval.insert(new_interval);
      answer ^= f(r) ^ f(l);
      it = interval.lower_bound(new_interval);
      bool ppl = false, ppr = false;
      if (it != interval.begin()) {
        pl = it;
        --pl;
        ppl = true;
        int pls = (*pl).second;
        answer ^= (long long) l * l - (long long) pls * pls;
      }
      pr = it;
      ++pr;
      if (pr != interval.end()) {
        ppr = true;
        int prf = (*pr).first;
        answer ^= (long long) prf * prf - (long long) r * r;
      }
      if (!del.size() && ppl && ppr) {
        int prf = (*pr).first;
        int pls = (*pl).second;
        answer ^= (long long) prf * prf - (long long) pls * pls;
      }
    } else {
      printf("%lld\n", answer);
    }
  }
  return 0;
}
