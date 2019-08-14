#include "list.h"

int main() {

  List<int> list;

  list.insertFront(8);
  list.insertFront(7);
  list.insertFront(6);
  list.insertFront(5);
  list.insertFront(4);
  list.insertFront(3);
  list.insertFront(2);
  list.insertFront(1);


  list.print(cout);

  list.waterfall();

  list.print(cout);


  return 0;
}
