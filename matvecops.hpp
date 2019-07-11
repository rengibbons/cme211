/////////////////////////////////////////////////
//                                             //
//     Name:      Ren Gibbons                  //
//     Date:      November 28, 2016            //
//     Course:    CME211                       //
//     Homework:  Project Part (a)             //
//     File:      matvecops.hpp                //
//                                             //
/////////////////////////////////////////////////


#ifndef MATVECOPS_HPP
#define MATVECOPS_HPP

#include <vector>

/* Add two vectors. */
std::vector<double> addVecs(std::vector<double> v1,
                            std::vector<double> v2);

/* Compute the L2 norm of a vector. */
double L2norm(std::vector<double> r);

/* Muliply a square matrix by a vector. */
std::vector<double> multMatVec(std::vector<double> val,
                               std::vector<int>    row_ptr,
                               std::vector<int>    col_idx,
                               std::vector<double> x);

/* Mutliply the transpose of vector v by
   a square matrix by the same vector v.*/
double multVecMatVec(std::vector<double> val,
                     std::vector<int>    row_ptr,
                     std::vector<int>    col_idx,
                     std::vector<double> x);

/* Peform dot product on two vectors. */
double multVecs(std::vector<double> v1,
                std::vector<double> v2);

/* Multiply the elements of a vector by a scalar. */
std::vector<double> multScalar(double s, std::vector<double> v);

/* Subtract one vector from another. */
std::vector<double> subVecs(std::vector<double> v1,
                            std::vector<double> v2);

#endif /* MATVECOPS_HPP*/