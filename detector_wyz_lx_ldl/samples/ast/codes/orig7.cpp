#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

void insert(map<set<int>, pair<string, int> > &m, 
	    const set<int>& s, const pair<string, int>& r) {
  pair<set<int>, pair<string, int> > p1 = make_pair(s, r);
  m.insert(p1);
}

void insert(vector<map<set<int>, pair<string, int> > >& v, 
	    const map<set<int>, pair<string, int> > m) {
  v.push_back(m);
}


int main(int argc, char** argv) {
  
  vector<map<set<int>, pair<string, int> > > strange_structure;

  map<set<int>, pair<string, int> > map1;
  map<set<int>, pair<string, int> > map2;

  pair<string, int> r1 = make_pair("hello", 21);
  pair<string, int> r2 = make_pair("world", 19);

  set<int> set1;
  set<int> set2;

  insert(map1, set1, r1);
  insert(map2, set2, r2);

  insert(strange_structure, map1);
  insert(strange_structure, map2);

}
