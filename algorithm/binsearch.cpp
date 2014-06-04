#include <vector>
#include <utility>
#include <cassert>
#include <algorithm>

using namespace std;

template <class Key, class Value>
Value binsearch(vector<pair<Key, Value> > list, Key key) {
  auto cmp = [] (const pair<Key, Value> &a, const Key &b) {
    return a.first < b;
  };
  auto p = lower_bound(list.begin(), list.end(), key, cmp);
  if (p != list.end() && !(key < p->first))
    return p->second;
  else
    return Value();
}

#define TEST true
#if TEST

int main() {
  vector<pair<int, int> > search;
  for (int i=0; i<20; i++) {
    search.push_back(make_pair(i*2, i*2));
  }

  for(int i=0; i<20; i++) {
    assert(binsearch(search, 2*i+1) == 0);
    assert(binsearch(search, 2*i) == 2*i);
  }
}
#endif
