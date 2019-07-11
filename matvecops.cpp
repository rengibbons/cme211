/////////////////////////////////////////////////
//                                             //
//    Name:     Ren Gibbons                    //
//    Date:     November 28,2016               //
//    Course:   CME211                         //
//    Homework: Project Part (a)               //
//    File:     matvecops.cpp                  //
//                                             //
/////////////////////////////////////////////////


#include <iostream>
#include <math.h>
#include "matvecops.hpp"


/* Add the elements of two vectors and return the summed vector. */
std::vector<double> addVecs(std::vector<double> v1,
                            std::vector<double> v2) {

  // Catch error if vector size is not equal.
  if (v1.size() != v2.size()) {
    std::cerr << "ERROR: Cannot add two vectors of unequal length." << std::endl;
    exit(1);
  }

  // Initialize sum vector and perform addition over each element.
  std::vector<double> sum;
  for (int ii = 0; ii < int(v1.size()); ++ii) {
    sum.push_back(v1[ii] + v2[ii]);
  }
  return sum;
}


/* Compute the L2 norm of a vector. */
double L2norm(std::vector<double> v) {

  // Initialize the sum vector and perform computation over each element.
  double sum = 0.0;
  for (int ii = 0; ii < int(v.size()); ++ii) {
    sum += v[ii] * v[ii];
  }

  // Take the square root of the sum.
  double norm = pow(sum, 0.5);
  return norm;
}


/* Multiply square nxn CSR matrix by a nx1 vector and return a nx1 vector. */
std::vector<double> multMatVec(std::vector<double> val,
                               std::vector<int>    row_ptr,
                               std::vector<int>    col_idx,
                               std::vector<double> x) {

  // Initialize the solution vector and the column position integer.
  std::vector<double> b;
  int col_pos = 0;
  for (int ii = 1; ii < int(row_ptr.size()); ++ii) {
    // Loop over row data element. Compute number of values in the row.
    int vals_per_row = row_ptr[ii] - row_ptr[ii - 1];

    // Initialize the value for the solution vector b.
    double b_val = 0.0;
    for (int jj = 0; jj < vals_per_row; ++jj) {
      // Loop over each value in the row and
      // sum the value for the solution vector.
      b_val += val[col_pos] * x[col_idx[col_pos]];
      col_pos += 1;
    }
    b.push_back(b_val);
  }
  return b;
}


/* Multiply each element of a vector by a scalar and return a vector. */
std::vector<double> multScalar(double s, std::vector<double> v) {

  // Loop over each element of the vector and multiply by the scalar in place.
  for (int ii = 0; ii < int(v.size()); ++ii) {
    v[ii] *= s;
  }
  return v;
}


/* Multiply the transpose of a nx1 vector by an nxn
   matrix by a nx1 vector and return a scalar. */
double multVecMatVec(std::vector<double> val,
                     std::vector<int>    row_ptr,
                     std::vector<int>    col_idx,
                     std::vector<double> x) {

  // Determine an intermediate column vector by multiplying
  // the nxn matrix by the nx1 vector.
  std::vector<double> col_vec = multMatVec(val, row_ptr, col_idx, x);

  // Mutiply the nx1 vector by the column vector.
  double mult_product = multVecs(x, col_vec);
  return mult_product;
}


/* Perform the dot product of two vectors by multiplying the elements
   of each vector, summing each term, and returning a double. */
double multVecs(std::vector<double> v1,
                 std::vector<double> v2) {

  // Catch error if vector size is not equal.
  if (v1.size() != v2.size()) {
    std::cerr << "ERROR: Cannot multiply two vectors of unequal length." << std::endl;
    exit(1);
  }

  // Initialize summed product and loop over each
  // element, summing the product of each vector.
  double mult_product = 0.0;
  for (int ii = 0; ii < int(v1.size()); ++ii) {
    mult_product += v1[ii] * v2[ii];
  }
  return mult_product;
}


/* Subtract the each element of vector v2 from vector v1
   and return the difference between the vectors. */
std::vector<double> subVecs(std::vector<double> v1,
                            std::vector<double> v2) {

  // Catch error if vector size is not equal.
  if (v1.size() != v2.size()) {
    std::cerr << "ERROR: Cannot subtract two vectors of unequal length." << std::endl;
    exit(1);
  }

  // Initialize the difference vector and peform subtraction over each element.
  std::vector<double> diff;
  for (int ii = 0; ii < int(v1.size()); ++ii) {
    diff.push_back(v1[ii] - v2[ii]);
  }
  return diff;
}