/////////////////////////////////////////////////
//                                             //
//    Name:       Ren Gibbons                  //
//    Date:       December 14, 2016            //
//    Course:     CME211                       //
//    Submission: Final Project                //
//    File:       main.cpp                     //
//                                             //
//    See description in writeup.pdf           //
//                                             //
/////////////////////////////////////////////////


#include "heat.hpp"

#include <iostream>
#include <string>


int main(int argc, char *argv[]) {

  /* Specify iterating tolerance */
  double tol = 1.e-5;

  /* Get command line arguments */
  if (argc != 3) {
    std::cout << "Usage:" << std::endl;
    std::cout << "  " << argv[0] << " <input file> <soln prefix>" << std::endl;
    return 0;
  }

  /* Store names of files */
  std::string input_file   = argv[1];
  std::string soln_prefix   = argv[2];

  /* Setup 2D heat equation system */
  HeatEquation2D sys;
  int status = sys.Setup(input_file);
  if (status) {
    std::cerr << "ERROR: System setup was unsuccessful!" << std::endl;
    return 1;
  }

  /* Solve system using CG */
  status = sys.Solve(input_file, soln_prefix, tol);
  if (!status) {
    std::cerr << "ERROR: System solve was unsuccessful!" << std::endl;
    return 1;
  } else {
    std::cout << "SUCCESS: CG solver converged in "
              << status
              << " iterations."
               << std::endl;
    return 0;
  }
}