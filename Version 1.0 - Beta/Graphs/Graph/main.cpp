// Robin Kalia
// robinkalia@berkeley.edu
// Graphs: Class that contains implementation of various Graph Algorithms
// 
// main.cpp: Contains the illustrations of various Graph Algorithms

/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "Graph.hpp"

#include <string>

template<typename T1, typename T2>
void CreateSampleAdjacencyMatrix(std::vector<std::pair<Node<T1>, std::vector<T2> > > &adjacency_mat, int32_t offset=0);


int32_t main(int32_t argc, char* argv[])
{
	std::vector<std::pair<Node<int32_t>, std::vector<int32_t> > > adjacency_mat;
	int32_t offset = 100; // 96;
	CreateSampleAdjacencyMatrix<int32_t, int32_t>(adjacency_mat, offset);

	try {
		// Create a Sample Graph
		Graph<int32_t,int32_t> graph(adjacency_mat);

		// Display the Adjacency Matrix
		std::cout << "\nAdjacency Matrix:" << std::endl;
		graph.DisplayAdjacencyMatrix();

		// Display the Incidence Matrix
		std::cout << "\nIncidence Matrix:" << std::endl;
		graph.DisplayIncidenceMatrix();
		
		// Breadth First Search
		std::vector<std::string> bfs_traversal_edge_list = {};
		graph.BreadthFirstSearch(bfs_traversal_edge_list);
		std::cout << "\nBreadth First Search Traversal Edges List: { ";
		for (const auto& elem : bfs_traversal_edge_list)	
			std::cout << elem << (elem == bfs_traversal_edge_list[bfs_traversal_edge_list.size() - 1] ? " }" : ", ");
		std::cout << std::endl;

		// Depth First Search
		std::vector<std::string> dfs_edges_list = {};
		std::vector<std::pair<int64_t, int64_t> > dfs_traversal_edge_list = {};
		graph.DepthFirstSearch(dfs_traversal_edge_list);
		for (const auto &elem : dfs_traversal_edge_list) {
			std::string edge = std::to_string(elem.first) + "-" + std::to_string(elem.second);
			dfs_edges_list.push_back(edge);
		}
		std::cout << "\nDepth First Search Traversal Edges List: { ";
		for (const auto& elem : dfs_edges_list)
			std::cout << elem << (elem == dfs_edges_list[dfs_edges_list.size() - 1] ? " }\n" : ", ");

		// Check for the presence of Cycles
		std::vector<std::string> cycle_terminal_vertices_list = {};
		graph.FindCycles(cycle_terminal_vertices_list, 1);     // flag = 0 for Undirected Graph, flag = 1 for Directed Graph
		std::cout << "\nCycle Detection: ";
		if (cycle_terminal_vertices_list.size() == 0)
			std::cout << "No Cycle Detected" << std::endl;
		else {
			std::cout << "Number of Detected Cycles = " << cycle_terminal_vertices_list.size() << "\nCycle Terminal Vertices List: { ";
			for (const auto& elem : cycle_terminal_vertices_list)
				std::cout << elem << (elem == cycle_terminal_vertices_list[cycle_terminal_vertices_list.size() - 1] ? " }\n" : ", ");
		}

		// Topological Sort
		std::vector<std::string> topological_sort_vertices_list = {};
		graph.TopologicalSort(topological_sort_vertices_list);
		if (topological_sort_vertices_list.size() == 0)
			std::cout << "\nCycle detected in the Graph: Topological Sort Not Possible" << std::endl;
		else {
			std::cout << "\nToplogical Sort Vertices List: { ";
			for (const auto& elem : topological_sort_vertices_list)
				std::cout << elem << (elem == topological_sort_vertices_list[topological_sort_vertices_list.size() - 1] ? " }\n" : ", ");
		}

		// Shortest Path
		std::vector<std::string> shortest_path = {};
		int32_t vertex_id = 4;
		std::cout << "\nShortest Path from Vertex " << vertex_id << " with Dijkstra Algorithm";
		graph.ShortestPathAlgorithm(shortest_path, 0, vertex_id);
		for (const auto& elem : shortest_path)
			std::cout << elem << (elem == shortest_path[shortest_path.size() - 1] ? "\n" : "");
		
		shortest_path = {};
		vertex_id = 5;
		std::cout << "\nShortest Path from Vertex " << vertex_id << " with Ford Algorithm";
		graph.ShortestPathAlgorithm(shortest_path, 1, vertex_id);
		for (const auto& elem : shortest_path)
			std::cout << elem << (elem == shortest_path[shortest_path.size() - 1] ? "\n" : "");

		shortest_path = {};
		vertex_id = 6;
		std::cout << "\nShortest Path from Vertex " << vertex_id << " with Generic Label Correcting Algorithm";
		graph.ShortestPathAlgorithm(shortest_path, 2, vertex_id);
		for (const auto& elem : shortest_path)
			std::cout << elem << (elem == shortest_path[shortest_path.size() - 1] ? "\n" : "");

		shortest_path = {};
		std::cout << "\nAll-To-All Shortest Path for nodes " << vertex_id << " with WFI Algorithm\n";
		graph.ShortestPathAlgorithm(shortest_path, 3, vertex_id);
		for (const auto& elem : shortest_path)
			std::cout << elem << (elem == shortest_path[shortest_path.size() - 1] ? "\n" : "");

		// Minimum Spanning Tree
		std::vector<std::string> mst_adjacency_matrix = {};
		std::cout << "\nMinimum Spanning Tree with Kruskal Algorithm\n";
		graph.MinimumSpanningTree(mst_adjacency_matrix, 0);
		for (const auto& elem : mst_adjacency_matrix)
			std::cout << elem << (elem == shortest_path[shortest_path.size() - 1] ? "\n" : "");

		mst_adjacency_matrix = {};
		std::cout << "\nMinimum Spanning Tree with Dijkstra Algorithm\n";
		graph.MinimumSpanningTree(mst_adjacency_matrix, 1);
		for (const auto& elem : mst_adjacency_matrix)
			std::cout << elem << (elem == shortest_path[shortest_path.size() - 1] ? "\n" : "");

	}
	catch (const std::exception& ex) {
		std::string error = "\nCaught Error: " + std::string(ex.what());
		std::cout << error << std::endl;
	}

	return 0;
}

template<typename T1, typename T2>
void CreateSampleAdjacencyMatrix(std::vector<std::pair<Node<T1>, std::vector<T2> > > &adjacency_mat, int32_t offset)
{
	// Example: Adjacency Matrix Sample [With Cycle]
	//				 a   b   c   d   e   f   g 
	//            a  0   2  -3  -4	 0   0   0      a-->b, a<--c, a<--d             
	//            b -2   0  -3   1	-3	 4 	 5		b<--a, b<--c, b-->d, b<--e, b-->f, b-->g     
	//            c  3   3   0  -2	 0   3  -2      c-->a, c-->b, c<--d, c-->f, c<--g      
	//            d  4  -1   2   0	 8	 1   4      d-->a, d<--b, d-->c, d-->e, d-->f, d-->g
	//            e  0   3   0  -8   0   3  -6      e-->b, e<--d, e-->f, e<--g                                
	//            f  0  -4  -3  -1  -3   0   4      f<--b, f<--c, f<--d, f<--e, f-->g                          
	//            g  0  -5   2  -4   6  -4   0      g<--b, g-->c, g<--d, g-->e, g<--f                          
	//                                                                            

	// Example: Adjacency Matrix Sample [Without Cycle]
	//				 a   b   c   d   e   f   g 
	//            a  0   0   3   4	 0   0   0      a-->b, a<--c, a<--d             
	//            b  0   0   0  -1	 3	 0 	 0		b<--a, b<--c, b-->d, b<--e, b-->f, b-->g     
	//            c -3   0   0   2	 0   3   0      c-->a, c-->b, c<--d, c-->f, c<--g      
	//            d -4   1  -2   0	 8	 1   0      d-->a, d<--b, d-->c, d-->e, d-->f, d-->g
	//            e  0  -3   0  -8   0   0   6      e-->b, e<--d, e-->f, e<--g                                
	//            f  0   0  -3  -1   0   0   0      f<--b, f<--c, f<--d, f<--e, f-->g                          
	//            g  0   0   0   0  -6   0   0      g<--b, g-->c, g<--d, g-->e, g<--f                          
	//                                                                            

	int32_t num_dummy_nodes = 7;

	/*
	// Adjacency Matrix without a Cycle
	std::vector<std::vector<T2> > adjacency_mat_elems = {	{ T2(0), T2(0), T2(3), T2(4), T2(0), T2(0), T2(0) },
															{ T2(0), T2(0), T2(0), T2(-1), T2(3), T2(0), T2(0) },
															{ T2(-3), T2(0), T2(0), T2(2), T2(0), T2(3), T2(0) },
															{ T2(-4), T2(1), T2(-2), T2(0), T2(8), T2(1), T2(0) },
															{ T2(0), T2(-3), T2(0), T2(-8), T2(0), T2(0), T2(6) },
															{ T2(0), T2(0), T2(-3), T2(-1), T2(0), T2(0), T2(0) },
															{ T2(0), T2(0), T2(0), T2(0), T2(-6), T2(0), T2(0) }
														};
	*/


	// Adjacency Matrix with a Cycle 
	std::vector<std::vector<T2> > adjacency_mat_elems =	{	{ T2(0), T2(2), T2(-3), T2(-4), T2(0), T2(0), T2(0) },
															{ T2(-2), T2(0), T2(-3), T2(1), T2(-3), T2(4), T2(5) },
															{ T2(3), T2(3), T2(0), T2(-2), T2(0), T2(3), T2(-2) },
															{ T2(4), T2(-1), T2(2), T2(0), T2(8), T2(1), T2(4) },
															{ T2(0), T2(3), T2(0), T2(-8), T2(0), T2(3), T2(-6) },
															{ T2(0), T2(-4), T2(-3), T2(-1), T2(-3), T2(0), T2(4) },
															{ T2(0), T2(-5), T2(2), T2(-4), T2(6), T2(-4), T2(0) }
														};
	

	for (int32_t i = 1; i <= 7; i++) {
		Node<T1> new_node = Node<T1>(T1(i), i + offset);
		std::pair<Node<T1>, std::vector<T2> > adjacency_mat_row(new_node, adjacency_mat_elems[i - 1]);
		adjacency_mat.push_back(adjacency_mat_row);
	}
}