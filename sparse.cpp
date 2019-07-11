/////////////////////////////////////////////////
//                                             //
//    Name:       Ren Gibbons                  //
//    Date:       December 14, 2016            //
//    Course:     CME211                       //
//    Submission: Final Project                //
//    File:       heat.cpp                     //
//                                             //
//    See description in writeup.pdf           //
//                                             //
/////////////////////////////////////////////////


#include "sparse.hpp"


/* Method to modify sparse matrix dimensions */
void SparseMatrix::Resize(int nrows_new, int ncols_new) {
  nrows = nrows_new;
  ncols = ncols_new;
}

/* Method to add an entry to matrix in COO format */
void SparseMatrix::AddEntry(int ii, int jj, double val) {
  i_idx.push_back(ii);
  j_idx.push_back(jj);
  a.push_back(val);
}

/* Method to convert COO matrix to CSR format using provided function */
void SparseMatrix::ConvertToCSR() {
  COO2CSR(a, i_idx, j_idx);
}

/* Return the vector of matrix values */
std::vector<double> SparseMatrix::GetVals() {
  return a;
}

/* Return the vector of row data values */
std::vector<int> SparseMatrix::GetRows() {
  return i_idx;
}

/* Return the vector of column values */
std::vector<int> SparseMatrix::GetCols() {
  return j_idx;
}