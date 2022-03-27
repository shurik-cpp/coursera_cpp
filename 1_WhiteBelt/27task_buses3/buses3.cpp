#include <iostream>
#include <map>
#include <set>

using namespace std;

int main(){
  map<set<string>, int> routes;
  int counterRoutes = 1;

  int q;
  cin >> q;

  for (int i = 0; i < q; ++i) {
    set<string> templateStops;

    int numberOfStops;
    cin >> numberOfStops;

    for (int i = 0; i < numberOfStops; ++ i){
      string stop;
      cin >> stop;
      templateStops.insert(stop);
    }
    if (routes.count(templateStops)){
      cout << "Already exists for " << routes[templateStops] << endl;
    }
    else {
      routes[templateStops] = counterRoutes;
      cout << "New bus " << counterRoutes << endl;
      ++counterRoutes;
    }
  }

  return 0;
}
