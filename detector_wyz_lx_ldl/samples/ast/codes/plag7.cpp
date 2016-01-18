#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

typedef vector<map<set<int>, pair<string, int> > > strange_type;
typedef map<set<int>, pair<string, int> > map_type;
typedef set<int> set_type;
typedef pair<string, int> pair_type;

void insert(map_type &m, 
	    const set_type& s, const pair_type& r) {
  pair<set_type, pair_type> p1 = make_pair(s, r);
  m.insert(p1);
}

void insert(strange_type& v, 
	    const map_type& m) {
  v.push_back(m);
}


int main(int argc, char** argv) {
  
  strange_type strange_structure;

  map_type map1;
  map_type map2;

  pair_type r1 = make_pair("hello", 21);
  pair_type r2 = make_pair("world", 19);

  set_type set1;
  set_type set2;

  insert(map1, set1, r1);
  insert(map2, set2, r2);

  insert(strange_structure, map1);
  insert(strange_structure, map2);

}
