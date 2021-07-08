#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <vector>
#include <Eigen/Dense>

class Node;

class DepthFirstSearch
{
public:
	DepthFirstSearch(const Eigen::MatrixXi &M_in,
					 const std::vector<int> &ij_0_in,
					 const std::vector<int> &ij_f_in)
		: M(M_in), ij_0(ij_0_in), ij_f(ij_f_in)
	{
	}

	std::tuple<std::vector<Node>, std::vector<std::vector<std::vector<int>>>> depth_first_solve() const;

private:
	const Eigen::MatrixXi &M;
	const std::vector<int> &ij_0;
	const std::vector<int> &ij_f;

	std::vector<std::vector<int>> back_track_and_mark_dead_end_nodes(std::vector<Node> &stack_nodes,
																	 std::vector<std::vector<std::vector<int>>> &list_IJ) const;
};

#endif
