#ifndef SEARCH_TEST_H_
#define SEARCH_TEST_H_

#include "gtest/gtest.h"
#include "math.h"
#include <Eigen/Dense>

class SearchTest: public ::testing::Test {
  
 protected:
  
  virtual void SetUp() {
        
    correct_nodes_.push_back( { 31 , 16 } );
    correct_nodes_.push_back( { 28 , 18 } );    
    correct_nodes_.push_back( { 23 , 18 } );    
    correct_nodes_.push_back( { 21 , 15 } );    
    correct_nodes_.push_back( { 16 ,  8 } );    
    correct_nodes_.push_back( { 14 ,  8 } );    
    correct_nodes_.push_back( { 10 ,  8 } );    
    correct_nodes_.push_back( {  5 , 12 } );    
    correct_nodes_.push_back( {  8 , 15 } );    
    correct_nodes_.push_back( { 12 , 15 } );    
    correct_nodes_.push_back( { 12 , 18 } );    
    correct_nodes_.push_back( { 12 , 20 } );    
    correct_nodes_.push_back( { 10 , 22 } );    
    correct_nodes_.push_back( {  7 , 23 } );    
    correct_nodes_.push_back( {  7 , 26 } );    
    correct_nodes_.push_back( {  5 , 26 } );    
    correct_nodes_.push_back( {  3 , 28 } );    
    correct_nodes_.push_back( {  3 , 30 } );
    
  }
  
  std::vector<std::vector<int>> correct_nodes_;
    
};

#endif
