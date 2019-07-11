/////////////////////////////////////////////////
//                                             //
//    Name:       Ren Gibbons                  //
//    Date:       December 14, 2016            //
//    Course:     CME211                       //
//    Submission: Final Project                //
//    File:       heat.hpp                     //
//                                             //
//    See description in writeup.pdf           //
//                                             //
/////////////////////////////////////////////////

/* Heat class reads an input file describing the domain of
 * the heat problem to be solved and sets up a linear
 * system of equations in sparse matrix form that can
 * be solved to find the temperature at each point in
 * the domain. The class has another method that solves
 * the system by calling a conjugate gradient solver.
 */


#ifndef HEAT_HPP
#define HEAT_HPP

#include <fstream>
#include <cmath>
#include <string>
#include <vector>

#include "CGSolver.hpp"
#include "sparse.hpp"


class HeatEquation2D {

  public:
    /* Method to setup Ax=b system */
    int Setup(std::string input_file);

    /* Method to solve system using CGsolver */
    int Solve(std::string input_file, std::string soln_prefix, double tol);

  private:
    SparseMatrix A;
    std::vector<double> b, x;

};

#endif /* HEAT_HPP */