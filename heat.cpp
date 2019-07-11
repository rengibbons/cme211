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


#include "heat.hpp"


/* Method to setup Ax=b system */
int HeatEquation2D::Setup(std::string input_file) {

  // Open and read file.
  std::ifstream f;
  f.open(input_file);
  if (!f.is_open()) {
    std::cerr << "ERROR: Input file name does not exist." << std::endl;
    return 1;
  }
  double length, width, h, Tc, Th;
  f >> length >> width >> h >> Tc >> Th;
  f.close();

  // Compute the number of rows and columns.
  unsigned int nrows = (unsigned int)(width / h + 1);
  unsigned int ncols = (unsigned int)(length / h + 1);

  // Get total number of nodes and initialize matrix.
  unsigned int nnodes = (nrows-2) * ncols - (nrows - 2);
  A.Resize(nnodes, nnodes);

  // Initialize global index counter.
  int glb_ind = 0;

  // Assemble matrix and RHS for top row of free nodes.
  for (unsigned int ii = 0; ii < ncols-1; ++ii) {
      A.AddEntry(glb_ind, ii,          4.0);
      A.AddEntry(glb_ind, ii+ncols-1, -1.0); // Below
      b.push_back(Th);
    if (ii != 0 && ii != (ncols - 2)) {
      // Interior column node.
      A.AddEntry(glb_ind, ii+1, -1.0); // Left
      A.AddEntry(glb_ind, ii-1, -1.0); // Right
    } else if (ii == 0) {
      // Left side column node.
      A.AddEntry(glb_ind, 1,       -1.0); // Right
      A.AddEntry(glb_ind, ncols-2, -1.0); // Left (right boundary)
    } else {
      // Right side column node.
      A.AddEntry(glb_ind, ii-1, -1.0); // Left
      A.AddEntry(glb_ind, 0,    -1.0); // Right (left boundary)
    }
    glb_ind += 1;
  }

  // Assemble matrix and RHS for all rows except top and bottom free rows.
  for (unsigned int ii = 0; ii < (nrows - 4); ++ii) {
    for (unsigned int jj = 0; jj < (ncols - 1); ++jj) {
      A.AddEntry(glb_ind, ncols-1+ii*(ncols-1)+jj,      4.0);
      A.AddEntry(glb_ind, ncols-1+(ii-1)*(ncols-1)+jj, -1.0); // Above
      A.AddEntry(glb_ind, ncols-1+(ii+1)*(ncols-1)+jj, -1.0); // Below
      b.push_back(0.0);
      if (jj != 0 && jj != (ncols -2)) {
        // Interior column node.
        A.AddEntry(glb_ind, ncols-1+ii*(ncols-1)+jj-1, -1.0); // Left
        A.AddEntry(glb_ind, ncols-1+ii*(ncols-1)+jj+1, -1.0); // Right
      } else if (jj == 0) {
        // Left side column node.
        A.AddEntry(glb_ind, ncols-1+ii*(ncols-1)+(ncols-2), -1.0); // Left
        A.AddEntry(glb_ind, ncols-1+ii*(ncols-1)+1,         -1.0); // Right
      } else {
        // Right side column node.
        A.AddEntry(glb_ind, ncols-1+ii*(ncols-1)+jj-1, -1.0); // Left
        A.AddEntry(glb_ind, ncols-1+ii*(ncols-1),      -1.0); // Right
      }
      glb_ind += 1;
    }
  }

  // Assemble matrix and RHS vetor for bottom row of free nodes.
  for (unsigned int ii = 0; ii < ncols-1; ++ii) {
      A.AddEntry(glb_ind, (nrows-3)*(ncols-1)+ii,  4.0);
      A.AddEntry(glb_ind, (nrows-4)*(ncols-1)+ii, -1.0); // Above
      double x = ii * h;
      double T = -Tc * (exp(-10 * pow(x - length / 2, 2)) - 2);
      b.push_back(T);
    if (ii != 0 && ii != (ncols - 2)) {
      // Interior column node.
      A.AddEntry(glb_ind, (nrows-3)*(ncols-1)+ii-1, -1.0); // Left
      A.AddEntry(glb_ind, (nrows-3)*(ncols-1)+ii+1, -1.0); // Right
    } else if (ii == 0) {
      // Left side column node.
      A.AddEntry(glb_ind, (nrows-3)*(ncols-1)+(ncols-2), -1.0); // Left
      A.AddEntry(glb_ind, (nrows-3)*(ncols-1)+ii+1,      -1.0); // Right
    } else {
      // Right side column node.
      A.AddEntry(glb_ind, (nrows-3)*(ncols-1)+ii-1, -1.0); // Left
      A.AddEntry(glb_ind, (nrows-3)*(ncols-1),      -1.0); // Right
    }
    glb_ind += 1;
  }

  // Convert to CSR format.
  A.ConvertToCSR();
  return 0;
}


/* Method to solve system using CGsolver */
int HeatEquation2D::Solve(std::string input_file,
                          std::string soln_prefix,
                          double tol) {

  // Solve the linear system.
  int niter = CGSolver(A, b, x, tol, input_file, soln_prefix);
  return niter;
}