/////////////////////////////////////////////////
//                                             //
//    Name:       Ren Gibbons                  //
//    Date:       December 14, 2016            //
//    Course:     CME211                       //
//    Submission: Final Project                //
//    File:       CGSolver.cpp                 //
//                                             //
//    See description in writeup.pdf           //
//                                             //
/////////////////////////////////////////////////


#ifndef CGSOLVER_HPP
#define CGSOLVER_HPP

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "sparse.hpp"
#include "matvecops.hpp"


/* Function that implements the CG algorithm for a linear system
 *
 * Ax = b
 *
 * where A is in CSR format.  The starting guess for the solution
 * is provided in x, and the solver runs a maximum number of iterations
 * equal to the size of the linear system.  Function returns the
 * number of iterations to converge the solution to the specified
 * tolerance, or -1 if the solver did not converge.
 */

int CGSolver(SparseMatrix &A,
             std::vector<double> &b,
             std::vector<double> &x,
             double              tol,
             std::string         input_file,
             std::string         soln_prefix);

void PrintSolution(std::string input_file,
                   std::string soln_prefix,
                   std::vector<double> &x,
                   int niter);

#endif /* CGSOLVER_HPP */