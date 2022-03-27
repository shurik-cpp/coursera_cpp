#include <iostream>
#include <map>
#include <exception>

using namespace std;

template <typename Key, typename Value, typename V>
Value& GetRefStrict(map<Key, Value>& incomming, const V val) {

  if (!incomming.count(val)) {
    throw runtime_error("");
  }

  return incomming[val];
}

int main() {
  try {
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue
  }
  catch (runtime_error& ex) {
    cout << ex.what() << endl;
  }


  return 0;
}

/*
#include <map>
#include <stdexcept>

template<typename KeyType, typename ValueType>
ValueType& GetRefStrict(map<KeyType, ValueType>& input_map, KeyType key) {
  if (input_map.count(key) == 0) {
    throw runtime_error("no such key in dictionary");
  }
  return input_map[key];
}

*/
