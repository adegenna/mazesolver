#ifndef __SEARCH_H__
#define __SEARCH_H__

#include <vector>
#include <Eigen/Dense>

class Node;

class DepthFirstSearch
{
public:
	DepthFirstSearch(const Eigen::MatrixXi &M_in,
					 const Node &ij_0_in,
					 const Node &ij_f_in);

	void writeSolutionToCSV(const std::string &filename) const;
	
	const std::vector<Node>& getSolutionNodes() const { return soln_nodes; }

private:
    DepthFirstSearch(const Eigen::MatrixXi &M_in,
                     const std::vector<int> &ij_0_in,
                     const std::vector<int> &ij_f_in);


	const std::vector<int> ij_f;

	std::vector<Node> soln_nodes;
	std::vector<std::vector<std::vector<int>>> soln_IJ;

	static void depth_first_solve(
		const Eigen::MatrixXi &M,
		const std::vector<int> &ij_0,
		const std::vector<int> &ij_f,
		std::vector<Node> &soln_nodes, std::vector<std::vector<std::vector<int>>> &soln_IJ);

	static std::vector<std::vector<int>> back_track_and_mark_dead_end_nodes(std::vector<Node> &stack_nodes,
																	 std::vector<std::vector<std::vector<int>>> &list_IJ);
};

#endif
