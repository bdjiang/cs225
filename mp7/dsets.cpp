/* Your code here! */
#include "dsets.h"
#include <iostream>
/**
Creates n unconnected root nodes at the end of the vector
**/
void DisjointSets::addelements(int n) {
	for (int i = 0; i < n; i++){
		_arr.push_back(-1);
	}
}

/**
Finds the set an element resides in
**/
int DisjointSets::find(int elem) {
	if(_arr[elem] < 0) {
    return elem;
  } else {
    return (_arr[elem] = find(_arr[elem]));
  }
}

/**
Unions two sets
**/
void DisjointSets::setunion(int a, int b) {
  a = find(a);
  b = find(b);

  int newSize = _arr[a] + _arr[b];

  if (_arr[a] < _arr[b]) {
    _arr[b] = a;
    _arr[a] = newSize;
  } else {
    _arr[a] = b;
    _arr[b] = newSize;
  }
}
