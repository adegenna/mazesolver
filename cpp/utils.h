#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include <Eigen/Dense>
#include <fstream>

std::vector< std::vector<int> > find_possible_moves( const int i ,
						     const int j ,
						     const Eigen::MatrixXi& M );

std::vector< std::vector<int> > find_exit_points_of_maze( const Eigen::MatrixXi& M );

bool check_if_ij_is_maze_node( const Eigen::MatrixXi& M ,
			       const int i , const int j ,
			       const std::vector<int> last_ij );

void print_vector_vector_int( const std::vector<std::vector<int>>& list_IJ );

void writeMazeToCSV( const std::string &filename , const Eigen::MatrixXi& M );

template<typename M>
M load_csv( const std::string& path ) {
  
  std::ifstream indata;
  indata.open(path);
  std::string line;
  std::vector<int> values;
  uint rows = 0;
  
  while (std::getline(indata, line)) {
    
    std::stringstream lineStream(line);
    std::string cell;
    
    while (std::getline(lineStream, cell, ',')) {
      values.push_back(std::stod(cell));
    }
    
    ++rows;
    
  }
  
  return Eigen::Map<const Eigen::Matrix<typename M::Scalar, M::RowsAtCompileTime, M::ColsAtCompileTime, Eigen::RowMajor>>(values.data(), rows, values.size()/rows);

}

#endif
