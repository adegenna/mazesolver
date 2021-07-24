#ifndef __PATH_H__
#define __PATH_H__

#include <vector>
#include <Eigen/Dense>

class Path
{
public:
	Path( );
	
	void push( const std::vector<int>& ij );
	
	void pop_last_candidate_path( );
	
	void add_new_empty_candidate_path( );

	void writeToCSV( const std::string& filename ) const;
	
private:
	
	std::vector<std::vector<std::vector<int>>> path_;

};

#endif
