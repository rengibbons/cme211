/////////////////////////////////////////////////
//                                             //
//    Name:       Ren Gibbons                  //
//    Date:       December 14, 2016            //
//    Course:     CME211                       //
//    Submission: Final Project                //
//    File:       sparse.hpp                   //
//                                             //
//    See description in writeup.pdf           //
//                                             //
/////////////////////////////////////////////////

/* The SparseMatrix class contains data for a sparse
 * matrix and can perform simple operations like
 * adding entries, returning data structures, resizing,
 * and converting in place from COO to CSR format.
 */


#ifndef SPARSE_HPP
#define SPARSE_HPP

#include <vector>

#include "COO2CSR.hpp"


class SparseMatrix {

  public:
    /* Method to modify sparse matrix dimensions */
    void Resize(int nrows_new, int ncols_new);

    /* Method to add entry to matrix in COO format */
    void AddEntry(int i, int j, double val);

    /* Method to convert COO matrix to CSR format using provided function */
    void ConvertToCSR();

    /* Return a vector of matrix values */
    std::vector<double> GetVals();

    /* Return a vector of row data values */
    std::vector<int> GetRows();

    /* Return a vector of column values */
    std::vector<int> GetCols();

  private:
    std::vector<int> i_idx;
    std::vector<int> j_idx;
    std::vector<double> a;
    int ncols;
    int nrows;
};

#endif /* SPARSE_HPP */