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


#include "CGSolver.hpp"


/* Solve a linear system using the conjugate gradient iterative
   algorithm. See full description in CGSolver.hpp header file. */
int CGSolver(SparseMatrix &A,
             std::vector<double> &b,
             std::vector<double> &x,
             double              tol,
             std::string         input_file,
             std::string         soln_prefix) {

  // Get data for sparse matrix.
  std::vector<double> val = A.GetVals();
  std::vector<int> row_ptr = A.GetRows();
  std::vector<int> col_idx = A.GetCols();

  // Max number of iterations is the size of the linear system.
  int nitermax = int(row_ptr.size()) - 1;

  // Initialize the elements of the solution vector to 1.
  for (int ii = 0; ii < int(b.size()); ++ii) {
    x.push_back(1);
  }

  // Initialize all needed data structures and variables.
  std::vector<double> temp_vec;
  std::vector<double> r_next;
  std::vector<double> r;
  std::vector<double> p;
  double L2normr0    = 0.0;
  double L2normr     = 0.0;
  double numerator   = 0.0;
  double denomenator = 0.0;
  double alpha       = 0.0;
  double beta        = 0.0;
  int niter          = 0;
  bool converged     = false;

  // Print the initial solution.
  PrintSolution(input_file, soln_prefix, x, niter);

  // Compute the initial residual and L2-norm of the residual.
  temp_vec = multMatVec(val, row_ptr, col_idx, x);
  r = subVecs(b, temp_vec);
  L2normr0 = L2norm(r);

  // Set the basis vector equal to the residual.
  p = r;
  while (niter < nitermax) {
    niter += 1;

    // Compute the solution step size.
    numerator = multVecs(r, r);
    denomenator = multVecMatVec(val, row_ptr, col_idx, p);
    alpha = numerator / denomenator;

    // Update the solution given the new step size.
    x = addVecs(x, multScalar(alpha, p));

    // Update the reisual and L2-norm of the residual.
    temp_vec = multMatVec(val, row_ptr, col_idx, p);
    r_next = subVecs(r, multScalar(alpha, temp_vec));
    L2normr = L2norm(r_next);

    // Stop if tolerance is satisfied.
    if (L2normr / L2normr0 < tol) {
      converged = true;
      break;
    }

    // Compute the new basis step size.
    numerator = multVecs(r_next, r_next);
    denomenator = multVecs(r, r);
    beta = numerator / denomenator;

    // Update the basis vector.
    p = addVecs(r_next, multScalar(beta, p));

    // Set the old residual functions.
    r = r_next;

    // Print intermediate solution for every 10th iteration.
    if (niter % 10 == 0) {
      PrintSolution(input_file, soln_prefix, x, niter);
    }
  }

  // Print the final solution.
  PrintSolution(input_file, soln_prefix, x, niter);

  // Return number of iterations to reach convergence,
  // or a flag to indicate convergence was not met.
  if (converged) {
    return niter;
  } else {
    return -1;
  }
}

/* Method to print solution to file */
void PrintSolution(std::string input_file,
                   std::string soln_prefix,
                   std::vector<double> &x,
                   int niter) {

  // Determine solution file name.
  std::string soln_file;
  std::stringstream s;
  s << soln_prefix << std::setw(3) << std::setfill('0') << niter << ".txt";
  soln_file = s.str();


  // Open solution file and prepare for writing.
  std::ofstream fout;
  fout.open(soln_file);
  if (!fout.is_open()) {
    std::cerr << "ERROR. Could not write to solution file." << std::endl;
    exit(0);
  }

  // Print input file name in order to compare
  // input and solution files in postprocessing.
  fout << input_file << std::endl;

  // Set printing preferences for the file.
  fout.setf(std::ios::fixed, std::ios::floatfield);
  fout.setf(std::ios::showpoint);
  fout.precision(10);

  // Write solution temperatures to output, one temperature per row.
  for (unsigned int ii = 0; ii < x.size(); ++ii) {
    fout << std::setw(10) << x[ii] << std::endl;
  }
  fout.close();
}