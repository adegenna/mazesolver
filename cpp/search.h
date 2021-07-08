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
		depth_first_solve(soln_nodes, soln_IJ);
	}

	void writeSolutionToCSV(const std::string &filename) const;

	const std::vector<Node> &getSolutionNodes() const { return soln_nodes; }
	const std::vector<std::vector<std::vector<int>>> &getSolutionIJ() const { return soln_IJ; }

private:
	const Eigen::MatrixXi &M;
	const std::vector<int> &ij_0;
	const std::vector<int> &ij_f;

	std::vector<Node> soln_nodes;
	std::vector<std::vector<std::vector<int>>> soln_IJ;

	void depth_first_solve(std::vector<Node> &soln_nodes, std::vector<std::vector<std::vector<int>>> &soln_IJ);

	std::vector<std::vector<int>> back_track_and_mark_dead_end_nodes(std::vector<Node> &stack_nodes,
																	 std::vector<std::vector<std::vector<int>>> &list_IJ) const;
};

#endif
