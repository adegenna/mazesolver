#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include <Eigen/Dense>

std::vector< std::vector<int> > find_possible_moves( const int i ,
						     const int j ,
						     const Eigen::MatrixXi& M );




#endif
