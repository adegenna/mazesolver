#ifndef UTILS_TEST_H_
#define UTILS_TEST_H_

#include "gtest/gtest.h"
#include "math.h"
#include <Eigen/Dense>

class UtilsTest: public ::testing::Test {
  
 protected:
  
  virtual void SetUp() {
    
    M_.resize(4,5);
    
    M_ << 1 , 1 , 0 , 1 , 1 ,
          1 , 1 , 0 , 1 , 1 ,
          1 , 0 , 0 , 0 , 1 ,
          1 , 0 , 1 , 1 , 1 ;
  }
  
  Eigen::MatrixXi M_;
  
};

#endif
