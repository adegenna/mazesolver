#include "search.h"
#include "utils.h"
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;
using namespace Eigen;

Path::Path() {
  
  path_.resize(1);
  
}

void Path::push( const vector<int>& ij ) {
  
  path_[ path_.size() - 1 ].push_back( ij );
  
}

void Path::pop_last_candidate_path( ) {
  
  path_.pop_back();
  
}

void Path::add_new_empty_candidate_path( ) {
  
  path_.resize( path_.size() + 1 );
  
}

void Path::writeToCSV( const std::string &filename ) const {
  
  ofstream outfile_ij(filename);
  
  for (int i = 0; i < path_.size(); i++) {
    for (int j = 0; j < path_[i].size(); j++) {
      outfile_ij << path_[i][j][0] << "," << path_[i][j][1] << endl;
    }
  }
  
  outfile_ij.close();
  
}
