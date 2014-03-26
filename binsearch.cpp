#include <vector>
#include <utility>
#include <cassert>

using namespace std;

template <class Key, class Value>
Value binsearch(vector<pair<Key, Value> > list, Key key) {
  int min = 0;
  int max = list.size(); 

  // put an upper bound on the number of comparisons so no infinite loop. Yaaay!
  for (int i=0; i<list.size(); i++) {
    int mid = min + (max - min)/2;
    Key midKey = list[mid].first;
    if (midKey == key) {
      return list[mid].second;
    }
    if (key < midKey) {
      max = mid;
    } else if (key > midKey) {
      min = mid;
    }
  }
  return (Value)NULL;
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
