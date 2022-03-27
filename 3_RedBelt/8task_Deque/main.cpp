#include <iostream>
#include <stdexcept>
#include <deque.h>

using namespace std;



int main() {

  Deque<int> d;

  d.PushFront(3);
  d.PushFront(2);
  d.PushFront(1);
  d.PushBack(4);
  d.PushBack(5);

  cout << "Back = " << d.Back() << endl;

//  cout << d[0] << ' ' << d[1] << endl;

//  d.PushFront(4);
//  d.PushBack(5);

//  for (size_t i = 0; i < d.Size(); ++i) {
//    cout << d[i] << ' ';
//  }
//  cout << endl;
//  cout << "d[3] = " << d[3] << endl;

//  for (size_t i = 0; i < d.Size(); ++i) {
//    cout << ++d[i] << ' ';
//  }
//  cout << endl;
//  cout << "Front = " << d.Front() << endl;
//  cout << "Back = " << d.Back() << endl;

//  d.At(3) = 51;
//  cout << "d[3] after 'd.At(3) = 51;' = " << d[3] << endl;
//  cout << "d.Front() = 10;" << endl;
//  d.Front() = 2;
//  cout << "Front = " << d.Front() << endl;

//  for (size_t i = 0; i < d.Size(); ++i) {
//    cout << d[i] << ' ';
//  }
//  cout << endl;

//  cout << "Size = " << d.Size() << endl;
  return 0;
}
