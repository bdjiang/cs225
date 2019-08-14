#include "exam.h"
#include <iostream>

using namespace exam;
using namespace std;

Matrix exam::flip_vert(const Matrix &m) {
  int rows = m.get_num_rows();
  int columns = m.get_num_columns();
  Matrix flipped(rows,columns);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      int number = m.get_coord(i, columns - j - 1);
      flipped.set_coord(i,j,number);
    }
  }

  return flipped;

}// Your code here!
