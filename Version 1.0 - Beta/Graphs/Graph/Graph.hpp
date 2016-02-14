// Robin Kalia
// robinkalia@berkeley.edu
// Graphs: Class that contains implementation of various Graph Algorithms
// 
// Graph.hpp: Contains the declaration and definition of different data members and methods of Graph class

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


#ifndef _OPENSOURCE_DATASTRUCTS_ALGOS_GRAPH_H
#define _OPENSOURCE_DATASTRUCTS_ALGOS_GRAPH_H

#include "Node.hpp"

#include <vector>
#include <tuple>
#include <queue>
#include <map>
#include <set>

#include <algorithm>

#include <stdint.h>

template<typename T1, typename T2>
class Graph {
private:

	// Convention: 
	// For digraphs, the distance is +ve for an edge directed from a row node to corresponding nodes along the row, 
	//                           and -ve otherwise for an opposite direction of the edge
	// Example: Adjacency Matrix
	//				 a   b   c   d
	//            a  0   2  -3  -4     a-->b, a<--c, a<--d             
	//            b -2   0  -3   1     b<--a, b<--c, b-->d     
	//            c  3   3   0  -2     c-->a, c-->b, c<--d      
	//            d  4  -1   2   0     d-->a, d<--b, d-->c
	//
	//           ------>b<--------                                          
	//           |      |        |                                 
	//           a<-----|--------c                                                  
	//           /\     \/       /\
	//            |------d--------|
	//
	// Undirected Graph G: G = G_Transpose
	// Directed Graph   G: G = -1 * G_Transpose
	// Simple Directed/Undirected Graph G: Gij = -1 or 1, where i is the row and j is the column

	int32_t numGraphNodes_;
	int32_t numGraphEdges_;

	std::vector<std::pair<Node<T1>, std::vector<T2> > > adjacencyMatrix_, incidenceMatrix_;
	 
	void CreateIncidenceMatrix();
	void CreateAdjacencyMatrix();
	
	void CreateGraphFromAdjacencyMatrix(const std::vector<std::pair<Node<T1>, std::vector<T2> > >& adjacency_matrix);
	void CreateGraphFromIncidencematrix(const std::vector<std::pair<Node<T1>, std::vector<T2> > >& incidence_matrix);

	bool CheckNodeNumQueueIsEmpty(std::deque<int64_t> &node_uuid_queue, std::map<int64_t, int32_t> &node_num_map);
	void DFS(int64_t front_node_uuid, std::vector<std::pair<int64_t, int64_t> > &dfs_traversal_edge_list, std::map<int64_t, int32_t> &node_index_map, std::map<int64_t, int32_t> &node_num_map, int32_t &count);
	void FindSimpleGraphCycles(std::vector<std::string> &cycle_terminal_vertices_list);	// Find cycles in normal undirected Graph
	void GraphDepthCycle(int64_t front_node_uuid, std::vector<std::string> &cycle_terminal_vertices_list, std::map<int64_t, int32_t> &node_index_map, std::map<int64_t, int32_t> &node_num_map, std::set<std::pair<int64_t, int64_t> > &edge_list_set, int32_t &count);
	void FindDigraphCycles(std::vector<std::string> &cycle_terminal_vertices_list); // Find cycles in Directed Graph
	void DigraphDepthCycle(int64_t front_node_uuid, std::vector<std::pair<int64_t, int64_t> > &cycle_terminal_nodes_list, std::map<int64_t, int32_t> &node_index_map, std::map<int64_t, int32_t> &node_num_map, int32_t &count);
	void TSort(int64_t front_node_uuid, std::map<int64_t, int32_t> &node_index_map, std::map<int64_t, int32_t> &node_num_map, std::map<int64_t, int32_t> &ts_node_num_map, int32_t &dfs_count, int32_t &ts_count, bool &TS_CYCLE_ABSENT_COND);
	
	// Shortest Path Algorithms
	void DijkstraShortestPathAlgorithm(std::vector<std::string> &shortest_path, int32_t start_vertex_index);
	void FordAlgorithm(std::vector<std::string> &shortest_path, int32_t start_vertex_index);
	void GenericLabelCorrectingAlgorithm(std::vector<std::string> &shortest_path, int32_t start_vertex_index);
	void WFIAlgorithm(std::vector<std::string> &shortest_path);

	void GenerateLabelAndNodeMap(std::map<int64_t, std::pair<T2, int64_t> > &label_map, int32_t start_vertex_index, std::map<int64_t, int32_t> &node_index_map);
	void GenerateShortestPathFromLabelMap(std::map<int64_t, std::pair<T2, int64_t> > &label_map, std::vector<std::string> &shortest_path);
	int64_t GetMinimalCurrentDistanceNodeID(std::map<int64_t, std::pair<T2, int64_t> > &label_map, std::set<int64_t> &node_uuid_set);

	// Minimum Spanning Tree algorithms
	void KruskalAlgorithm(std::vector<std::string> &mst_adjacency_matrix);
	void DijkstraMSTAlgorithm(std::vector<std::string> &mst_adjacency_matrix);
	void GenerateEdgesListAndNodeMap(std::vector<std::pair<T2, std::pair<int64_t, int64_t> > > &edges_list, std::map<int64_t, int32_t> &node_uuid_index_map);
	bool DetectCycle(std::vector<std::pair<int64_t, std::vector<T2> > > &adjacency_matrix, std::vector<std::pair<T2, std::pair<int64_t, int64_t> > > &path_edges_list);
	void GraphDepthCycle(std::vector<std::pair<int64_t, std::vector<T2> > > &adjacency_matrix, int64_t front_node_uuid, std::map<int64_t, int32_t> &node_index_map, std::map<int64_t, int32_t> &node_num_map, std::vector<std::pair<T2, std::pair<int64_t, int64_t> > > &path_edges_list, int32_t &dfs_count, bool &CYCLE_ABSENT_COND);
	void EliminateEdgeWithMaximumWeight(std::vector<std::pair<int64_t, std::vector<T2> > > &adjacency_matrix, std::vector<std::pair<T2, std::pair<int64_t, int64_t> > > &path_edges_list, std::map<int64_t, int32_t> &node_uuid_index_map);

	int32_t INFINITE_WEIGHT;

public:
	Graph(const std::vector<std::pair<Node<T1>, std::vector<T2> > >& matrix, bool flag = 0);
	~Graph();

	void DisplayAdjacencyMatrix();
	void DisplayIncidenceMatrix();

	void BreadthFirstSearch(std::vector<std::string> &bfs_traversal_edge_list = {});    // Also known as Level Order Traversal
	void DepthFirstSearch(std::vector<std::pair<int64_t, int64_t> > &dfs_traversal_edge_list);
	void FindCycles(std::vector<std::string> &cycle_terminal_vertices_list, int32_t flag = 0); // flag = 0 --> Undirected Graph;  flag = 1 --> Directed Graph
	void TopologicalSort(std::vector<std::string> &topological_sort_vertices_list);

	void ShortestPathAlgorithm(std::vector<std::string> &shortest_path, int32_t flag = 0, int32_t start_vertex_index=0);
	void MinimumSpanningTree(std::vector<std::string> &mst_adjacency_matrix, int32_t flag = 0);

};


template<typename T1, typename T2>
Graph<T1,T2>::~Graph()
{
	adjacencyMatrix_.clear();
	incidenceMatrix_.clear();
}


template<typename T1, typename T2>
Graph<T1, T2>::Graph(const std::vector<std::pair<Node<T1>, std::vector<T2> > >& matrix, bool flag /* = 0 */) : INFINITE_WEIGHT(0xFFFFFFF)
{
	if (flag)	CreateGraphFromIncidencematrix(matrix);
	else CreateGraphFromAdjacencyMatrix(matrix);
}


template<typename T1, typename T2>
void Graph<T1, T2>::CreateGraphFromAdjacencyMatrix(const std::vector<std::pair<Node<T1>, std::vector<T2> > >& adjacency_matrix)
{
	adjacencyMatrix_ = adjacency_matrix;
	CreateIncidenceMatrix();
}


template<typename T1, typename T2>
void Graph<T1, T2>::CreateGraphFromIncidencematrix(const std::vector<std::pair<Node<T1>, std::vector<T2> > >& incidence_matrix)
{ 
	incidenceMatrix_ = incidence_matrix;
	CreateAdjacencyMatrix();
}


template<typename T1, typename T2>
void Graph<T1, T2>::CreateIncidenceMatrix()
{
	numGraphNodes_ = adjacencyMatrix_.size();
	numGraphEdges_ = 0;

	for (int32_t i = 0; i<numGraphNodes_; i++)
		for (int32_t j = i + 1; j < numGraphNodes_; j++)
			numGraphEdges_ += (adjacencyMatrix_[i].second[j] != 0) ? 1 : 0;
	
	std::vector<std::pair<Node<T1>, std::vector<T2> > > incidence_matrix(numGraphNodes_);
	for (int32_t i = 0; i < numGraphNodes_; i++) {
		incidence_matrix[i].first = adjacencyMatrix_[i].first;
		std::vector<T2> edge_weights(numGraphEdges_, 0);
		incidence_matrix[i].second = edge_weights;
	}
	
	int32_t count = 0;
	for (int32_t i = 0; (i < numGraphNodes_)&&(count<numGraphEdges_); i++) {
		for (int32_t j = i+1; (j < numGraphNodes_)&&(count<numGraphEdges_); j++)
			if (adjacencyMatrix_[i].second[j] != 0) {
				incidence_matrix[i].second[count] = adjacencyMatrix_[i].second[j];
				incidence_matrix[j].second[count] = adjacencyMatrix_[j].second[i];
				count += 1;
			}
	}

	incidenceMatrix_ = incidence_matrix;
}

template<typename T1, typename T2>
void Graph<T1, T2>::CreateAdjacencyMatrix()
{
	numGraphEdges_ = incidenceMatrix_[0].second.size();
	numGraphNodes_ = incidenceMatrix_.size();

	std::vector<std::pair<Node<T1>, std::vector<T2> > > adjacency_matrix(numGraphNodes_);
	for (int32_t i = 0; i < numGraphNodes_; i++)	{
		adjacency_matrix[i].first = incidenceMatrix_[i].first;
		adjacency_matrix[i].second = std::vector<T2>(numGraphNodes_, 0);          // Just check if we need to remove a 0
	}

	for (int32_t i = 0; i < numGraphEdges_; i++) {
		std::vector<int32_t> node_indices;
		for (int32_t j = 0; j < numGraphNodes_; j++)
			if (incidenceMatrix_[j].second[i] != 0)		node_indices.push_back(j);
		adjacency_matrix[node_indices[0]].second[node_indices[1]] = incidenceMatrix_[node_indices[0]].second[i];
		adjacency_matrix[node_indices[1]].second[node_indices[0]] = incidenceMatrix_[node_indices[1]].second[i];
	}

	adjacencyMatrix_ = adjacency_matrix;
}


template<typename T1, typename T2>
void Graph<T1, T2>::DisplayAdjacencyMatrix()
{
	std::cout << std::endl << "\t";
	for (const auto& elem : adjacencyMatrix_)		std::cout << elem.first.uuid_ << "\t";
	
	for (const auto& elem : adjacencyMatrix_) {
		std::cout << std::endl << elem.first.uuid_ << "\t";
		for (const auto& elem2 : elem.second)		std::cout << elem2 << "\t";
	}

	std::cout << "\n\n";
}


template<typename T1, typename T2>
void Graph<T1, T2>::DisplayIncidenceMatrix()
{
	std::cout << std::endl << "\t";
	for (int32_t i = 0; i < incidenceMatrix_[0].second.size(); i++) {
		std::vector<int32_t> node_indices;
		for (int32_t j = 0; j < numGraphNodes_; j++)
			if (incidenceMatrix_[j].second[i] != 0)	node_indices.push_back(j);

		std::cout << incidenceMatrix_[node_indices[0]].first.uuid_ << "-" << incidenceMatrix_[node_indices[1]].first.uuid_ << "\t";
	}

	for (const auto& elem : incidenceMatrix_) {
		std::cout << std::endl << elem.first.uuid_ << "\t";
		for (const auto& elem2 : elem.second)		std::cout << elem2 << "\t";
	}

	std::cout << "\n\n";
}


template<typename T1, typename T2>
void Graph<T1, T2>::BreadthFirstSearch(std::vector<std::string> &bfs_traversal_edge_list)
{
	bfs_traversal_edge_list = {};
	
	Node<T1> start_node = adjacencyMatrix_[0].first;
	std::deque<int64_t> node_uuid_queue;
	std::map<int64_t, int32_t> node_num_map;
	std::map<int64_t, int32_t> node_index_map;
	for (int32_t i = 0; i < adjacencyMatrix_.size(); i++)	{
		node_num_map.insert(std::pair<int64_t, int32_t>(adjacencyMatrix_[i].first.uuid_, 0)); 
		node_index_map.insert(std::pair<int64_t, int32_t>(adjacencyMatrix_[i].first.uuid_, i));
	}
	
	int32_t count = 0;
	node_uuid_queue.push_back(start_node.uuid_);
	while (!node_uuid_queue.empty()) {
		int64_t front_node_uuid = node_uuid_queue.front();
		node_uuid_queue.pop_front();
		node_num_map[front_node_uuid] = ++count;
		for (int32_t j = 0; j < adjacencyMatrix_.size(); j++)
			if ((adjacencyMatrix_[node_index_map[front_node_uuid]].second[j] > 0 /* !=0 && !-ve*/)&&(node_num_map[adjacencyMatrix_[j].first.uuid_] == 0)) 
			{
				node_num_map[adjacencyMatrix_[j].first.uuid_] = ++count;
				node_uuid_queue.push_back(adjacencyMatrix_[j].first.uuid_);
				std::string edge = std::to_string(front_node_uuid) + "-" + std::to_string(adjacencyMatrix_[j].first.uuid_);
				bfs_traversal_edge_list.push_back(edge);
			}
	}
}


template<typename T1, typename T2>
void Graph<T1, T2>::DepthFirstSearch(std::vector<std::pair<int64_t, int64_t> > &dfs_traversal_edge_list)
{
	dfs_traversal_edge_list = {};
	
	std::deque<int64_t> node_uuid_queue;
	std::map<int64_t, int32_t> node_num_map;
	std::map<int64_t, int32_t> node_index_map;
	for (int32_t i = 0; i < adjacencyMatrix_.size(); i++)	{
		node_num_map.insert(std::pair<int64_t, int32_t>(adjacencyMatrix_[i].first.uuid_, 0));
		node_index_map.insert(std::pair<int64_t, int32_t>(adjacencyMatrix_[i].first.uuid_, i));
		node_uuid_queue.push_back(adjacencyMatrix_[i].first.uuid_);
	}

	int32_t count = 0;
	while (!CheckNodeNumQueueIsEmpty(node_uuid_queue, node_num_map)) {
		int64_t front_node_uuid = node_uuid_queue.front();
		node_uuid_queue.pop_front();

		DFS(front_node_uuid, dfs_traversal_edge_list, node_index_map, node_num_map, count);
	}
}


template<typename T1, typename T2>
void Graph<T1, T2>::DFS(int64_t front_node_uuid, std::vector<std::pair<int64_t, int64_t> > &dfs_traversal_edge_list, std::map<int64_t, int32_t> &node_index_map, std::map<int64_t, int32_t> &node_num_map, int32_t &count)
{
	node_num_map[front_node_uuid] = ++count;
	for (int32_t j = 0; j < adjacencyMatrix_.size(); j++)
		if ((adjacencyMatrix_[node_index_map[front_node_uuid]].second[j] > 0 /* !=0 && !-ve*/) && (node_num_map[adjacencyMatrix_[j].first.uuid_] == 0))
		{
			dfs_traversal_edge_list.push_back(std::pair<int64_t, int64_t>(front_node_uuid, adjacencyMatrix_[j].first.uuid_));

			DFS(adjacencyMatrix_[j].first.uuid_, dfs_traversal_edge_list, node_index_map, node_num_map, count);
		}
}


template<typename T1, typename T2>
void Graph<T1, T2>::FindCycles(std::vector<std::string> &cycle_terminal_vertices_list, int32_t flag)
{
	cycle_terminal_vertices_list = {};

	switch (flag)
	{
	case 0:
		FindSimpleGraphCycles(cycle_terminal_vertices_list);
		break;

	case 1:
		FindDigraphCycles(cycle_terminal_vertices_list);
		break;

	default:
		break;
	}

}


template<typename T1, typename T2>
void Graph<T1, T2>::FindSimpleGraphCycles(std::vector<std::string> &cycle_terminal_vertices_list)
{
	cycle_terminal_vertices_list = {};
	
	std::deque<int64_t> node_uuid_queue;
	std::map<int64_t, int32_t> node_num_map;
	std::map<int64_t, int32_t> node_index_map;
	std::set<std::pair<int64_t, int64_t> > edge_list_set = {};
	for (int32_t i = 0; i < adjacencyMatrix_.size(); i++)	{
		node_num_map.insert(std::pair<int64_t, int32_t>(adjacencyMatrix_[i].first.uuid_, 0));
		node_index_map.insert(std::pair<int64_t, int32_t>(adjacencyMatrix_[i].first.uuid_, i));
		node_uuid_queue.push_back(adjacencyMatrix_[i].first.uuid_);
	}

	int32_t count = 0;
	while (!CheckNodeNumQueueIsEmpty(node_uuid_queue, node_num_map)) {
		int64_t front_node_uuid = node_uuid_queue.front();
		node_uuid_queue.pop_front();

		GraphDepthCycle(front_node_uuid, cycle_terminal_vertices_list, node_index_map, node_num_map, edge_list_set, count);
	}
}


template<typename T1, typename T2>
void Graph<T1, T2>::GraphDepthCycle(int64_t front_node_uuid, std::vector<std::string> &cycle_terminal_vertices_list, std::map<int64_t, int32_t> &node_index_map, std::map<int64_t, int32_t> &node_num_map, std::set<std::pair<int64_t, int64_t> > &edge_list_set, int32_t &count)
{
	node_num_map[front_node_uuid] = ++count;
	for (int32_t j = 0; j < adjacencyMatrix_.size(); j++)
		if (adjacencyMatrix_[node_index_map[front_node_uuid]].second[j] > 0 /* !=0 && !-ve*/) {
			if (node_num_map[adjacencyMatrix_[j].first.uuid_] == 0) {
				edge_list_set.insert(std::pair<int64_t, int64_t>(front_node_uuid, adjacencyMatrix_[j].first.uuid_));
				GraphDepthCycle(adjacencyMatrix_[j].first.uuid_, cycle_terminal_vertices_list, node_index_map, node_num_map, edge_list_set, count);
			} 
			else {
				std::pair<int64_t, int64_t > edge= std::pair<int64_t, int64_t>(front_node_uuid, adjacencyMatrix_[j].first.uuid_);
				if (edge_list_set.find(edge) == edge_list_set.end())
				{
					std::string cyclic_edge = std::to_string(front_node_uuid) + "-" + std::to_string(adjacencyMatrix_[j].first.uuid_);
					cycle_terminal_vertices_list.push_back(cyclic_edge);
				}
			}
		}
}



template<typename T1, typename T2>
void Graph<T1, T2>::FindDigraphCycles(std::vector<std::string> &cycle_terminal_vertices_list)
{
	std::vector<std::pair<int64_t, int64_t> > cycle_terminal_nodes_list = {};

	std::deque<int64_t> node_uuid_queue;
	std::map<int64_t, int32_t> node_num_map;
	std::map<int64_t, int32_t> node_index_map;
	for (int32_t i = 0; i < adjacencyMatrix_.size(); i++)	{
		node_num_map.insert(std::pair<int64_t, int32_t>(adjacencyMatrix_[i].first.uuid_, 0));
		node_index_map.insert(std::pair<int64_t, int32_t>(adjacencyMatrix_[i].first.uuid_, i));
		node_uuid_queue.push_back(adjacencyMatrix_[i].first.uuid_);
	}

	int32_t count = 0;
	while (!CheckNodeNumQueueIsEmpty(node_uuid_queue, node_num_map)) {
		int64_t front_node_uuid = node_uuid_queue.front();
		node_uuid_queue.pop_front();

		DigraphDepthCycle(front_node_uuid, cycle_terminal_nodes_list, node_index_map, node_num_map, count);
	}

	for (const auto& elem : cycle_terminal_nodes_list) {
		std::string terminal_nodes = "(" + std::to_string(elem.first) + "," + std::to_string(elem.second) + ")";
		cycle_terminal_vertices_list.push_back(terminal_nodes);
	}
}


template<typename T1, typename T2>
void Graph<T1, T2>::DigraphDepthCycle(int64_t front_node_uuid, std::vector<std::pair<int64_t, int64_t> > &cycle_terminal_nodes_list, std::map<int64_t, int32_t> &node_index_map, std::map<int64_t, int32_t> &node_num_map, int32_t &count)
{
	node_num_map[front_node_uuid] = ++count;
	for (int32_t j = 0; j < adjacencyMatrix_.size(); j++)
		if (adjacencyMatrix_[node_index_map[front_node_uuid]].second[j] > 0 /* !=0 && !-ve*/) {
			if (node_num_map[adjacencyMatrix_[j].first.uuid_] == 0) {
				DigraphDepthCycle(adjacencyMatrix_[j].first.uuid_, cycle_terminal_nodes_list, node_index_map, node_num_map, count);
			}
			else if (node_num_map[adjacencyMatrix_[j].first.uuid_] != INFINITE_WEIGHT) {
				cycle_terminal_nodes_list.push_back(std::pair<T1, T2>(front_node_uuid, adjacencyMatrix_[j].first.uuid_));
			}
		}

	node_num_map[front_node_uuid] = INFINITE_WEIGHT;
}


template<typename T1, typename T2>
void Graph<T1,T2>::TopologicalSort(std::vector<std::string> &topological_sort_vertices_list)
{
	std::deque<int64_t> node_uuid_queue;
	topological_sort_vertices_list = {};
	std::map<int64_t, int32_t> node_num_map;
	std::map<int64_t, int32_t> node_index_map;
	std::map<int64_t, int32_t> ts_node_num_map;

	for (int32_t i = 0; i < adjacencyMatrix_.size(); i++)	{
		node_num_map.insert(std::pair<int64_t, int32_t>(adjacencyMatrix_[i].first.uuid_, 0));
		ts_node_num_map.insert(std::pair<int64_t, int32_t>(adjacencyMatrix_[i].first.uuid_, 0));
		node_index_map.insert(std::pair<int64_t, int32_t>(adjacencyMatrix_[i].first.uuid_, i));
		node_uuid_queue.push_back(adjacencyMatrix_[i].first.uuid_);
	}

	int32_t dfs_count = 0;
	int32_t ts_count = 0;
	bool TS_CYCLE_ABSENT_COND = true;
	while ( (!CheckNodeNumQueueIsEmpty(node_uuid_queue, node_num_map)) && (TS_CYCLE_ABSENT_COND) ) {
		int64_t front_node_uuid = node_uuid_queue.front();
		node_uuid_queue.pop_front();

		TSort(front_node_uuid, node_index_map, node_num_map, ts_node_num_map, dfs_count, ts_count, TS_CYCLE_ABSENT_COND);
	}

	if (TS_CYCLE_ABSENT_COND) {
		std::vector<std::pair<int32_t, int64_t> > ts_node_num_map_vector;
		for (const auto &elem : ts_node_num_map)	
			ts_node_num_map_vector.push_back(std::pair<int32_t, int64_t>(elem.second, elem.first));
		std::sort(ts_node_num_map_vector.begin(), ts_node_num_map_vector.end());

		for (const auto& elem : ts_node_num_map_vector)	topological_sort_vertices_list.push_back(std::to_string(elem.second));
	}
}


template<typename T1, typename T2>
void Graph<T1, T2>::TSort(int64_t front_node_uuid, std::map<int64_t, int32_t> &node_index_map, std::map<int64_t, int32_t> &node_num_map, std::map<int64_t, int32_t> &ts_node_num_map, int32_t &dfs_count, int32_t &ts_count, bool &TS_CYCLE_ABSENT_COND)
{
	node_num_map[front_node_uuid] = ++dfs_count;
	for (int32_t j = 0; j < adjacencyMatrix_.size(); j++)
		if (adjacencyMatrix_[node_index_map[front_node_uuid]].second[j] > 0 /* !=0 && !-ve*/) {
			if (node_num_map[adjacencyMatrix_[j].first.uuid_] == 0)
				TSort(adjacencyMatrix_[j].first.uuid_, node_index_map, node_num_map, ts_node_num_map, dfs_count, ts_count, TS_CYCLE_ABSENT_COND);
			else if (ts_node_num_map[adjacencyMatrix_[j].first.uuid_] == 0) {
				TS_CYCLE_ABSENT_COND = false;
				// std::string error_str = "Cycle detected in the Graph: Topological Sort Not Possible";
				// throw std::exception(error_str.c_str());
			}
		}
	ts_node_num_map[front_node_uuid] = ++ts_count;
}


template<typename T1, typename T2>
bool Graph<T1, T2>::CheckNodeNumQueueIsEmpty(std::deque<int64_t> &node_uuid_queue, std::map<int64_t, int32_t> &node_num_map)
{
	for (int32_t i = 0; i < node_uuid_queue.size(); i++)
		if (node_num_map[node_uuid_queue[i]] != 0)	{
			node_uuid_queue.erase(node_uuid_queue.begin() + i);
			i--;
		}

	if (node_uuid_queue.empty())	return true;
	return false;
}


template<typename T1, typename T2>
void Graph<T1, T2>::ShortestPathAlgorithm(std::vector<std::string> &shortest_path, int32_t flag, int32_t start_vertex_index)
{
	shortest_path = {};

	switch (flag)
	{
	case 0:
		DijkstraShortestPathAlgorithm(shortest_path, start_vertex_index);
		break;

	case 1:
		FordAlgorithm(shortest_path, start_vertex_index);
		break;

	case 2:
		GenericLabelCorrectingAlgorithm(shortest_path, start_vertex_index);
		break;

	default:
		// All to All Shortest Path Algorithm
		WFIAlgorithm(shortest_path);
		break;
	}
}


template<typename T1, typename T2>
void Graph<T1, T2>::GenerateLabelAndNodeMap(std::map<int64_t, std::pair<T2, int64_t> > &label_map, int32_t start_vertex_index, std::map<int64_t, int32_t> &node_index_map)
{
	for (const auto &elem : adjacencyMatrix_) {
		T2 currDist = (elem.first.uuid_ == adjacencyMatrix_[start_vertex_index].first.uuid_) ? T2(0) : T2(INFINITE_WEIGHT);
		label_map.insert(std::pair<int64_t, std::pair<T2, int64_t> >(elem.first.uuid_, std::pair<T2, int64_t>(currDist, adjacencyMatrix_[start_vertex_index].first.uuid_)));
	}

	for (int32_t i = 0; i < adjacencyMatrix_.size(); i++)	{
		node_index_map.insert(std::pair<int64_t, int32_t>(adjacencyMatrix_[i].first.uuid_, i));
	}
}


template<typename T1, typename T2>
void Graph<T1, T2>::GenerateShortestPathFromLabelMap(std::map<int64_t, std::pair<T2, int64_t> > &label_map, std::vector<std::string> &shortest_path)
{
	for (const auto& elem : adjacencyMatrix_) {
		std::string elem_details = std::to_string(elem.first.uuid_) + "  -->  " + 
			                       std::to_string(label_map[elem.first.uuid_].first) + "     " +
								   std::to_string(label_map[elem.first.uuid_].second) + "\n";
		shortest_path.push_back(elem_details);
	}
}


template<typename T1, typename T2>
void Graph<T1, T2>::DijkstraShortestPathAlgorithm(std::vector<std::string> &shortest_path, int32_t start_vertex_index)
{
	std::map<int64_t, std::pair<T2, int64_t> > label_map;	// Node_ID --> Current Distance, Predecessor_Node_ID
	std::map<int64_t, int32_t> node_index_map;		// Node_ID --> Number of Node in the Adjacency Matrix
	GenerateLabelAndNodeMap(label_map, start_vertex_index, node_index_map);
	
	std::set<int64_t> node_uuid_set;
	for (const auto &elem : adjacencyMatrix_)	 node_uuid_set.insert(elem.first.uuid_);
	
	int32_t count = 0;
	while (!node_uuid_set.empty())
	{
		int64_t minimal_curr_dist_node_id = GetMinimalCurrentDistanceNodeID(label_map, node_uuid_set);
		node_uuid_set.erase(minimal_curr_dist_node_id);

		for (int32_t j = 0; j < adjacencyMatrix_.size(); j++)
			if (adjacencyMatrix_[node_index_map[minimal_curr_dist_node_id]].second[j] > 0 /* !=0 && !-ve*/) {
				if (label_map[adjacencyMatrix_[j].first.uuid_].first > label_map[minimal_curr_dist_node_id].first + adjacencyMatrix_[node_index_map[minimal_curr_dist_node_id]].second[j]) {
					label_map[adjacencyMatrix_[j].first.uuid_].first = label_map[minimal_curr_dist_node_id].first + adjacencyMatrix_[node_index_map[minimal_curr_dist_node_id]].second[j];
					label_map[adjacencyMatrix_[j].first.uuid_].second = minimal_curr_dist_node_id;
				}
			}

		++count;

		// Print this if you want to see the change in shortest path distances in all iterations
		std::string path_iter_str = "";
		for (int32_t i = 0; i < adjacencyMatrix_.size(); i++)	{
			path_iter_str += "(" + std::to_string(adjacencyMatrix_[i].first.uuid_) +
							 "->" + std::to_string(label_map[adjacencyMatrix_[i].first.uuid_].first) +
							 "," + std::to_string(label_map[adjacencyMatrix_[i].first.uuid_].second) + ")";
			path_iter_str += (i == adjacencyMatrix_.size() - 1) ? "" : ";";
		}
		std::cout << "\nIteration " << count << ": [" << path_iter_str << "]";
	}

	std::string iterations = "\nNumber of Iterations = " + std::to_string(count) + "\n";
	shortest_path.push_back(iterations);
	GenerateShortestPathFromLabelMap(label_map, shortest_path);
}


template<typename T1, typename T2>
int64_t Graph<T1, T2>::GetMinimalCurrentDistanceNodeID(std::map<int64_t, std::pair<T2, int64_t> > &label_map, std::set<int64_t> &node_uuid_set)
{
	int64_t min_dist_node_id;
	T2 min_dist;

	bool CONTINUE_LOOP_COND = true;
	int32_t match_index;
	for (int32_t i = 0; (i<adjacencyMatrix_.size()) && (CONTINUE_LOOP_COND); i++)
		if (node_uuid_set.count(adjacencyMatrix_[i].first.uuid_) > 0) {
			CONTINUE_LOOP_COND = false;
			min_dist_node_id = adjacencyMatrix_[i].first.uuid_;
			min_dist = label_map[adjacencyMatrix_[i].first.uuid_].first;
			match_index = i;
		}	

	for (int32_t i = 0; (i < adjacencyMatrix_.size()) && (i != match_index) && (node_uuid_set.count(adjacencyMatrix_[i].first.uuid_) > 0); i++) {
		if (min_dist > label_map[adjacencyMatrix_[i].first.uuid_].first) {
			min_dist_node_id = adjacencyMatrix_[i].first.uuid_;
			min_dist = label_map[adjacencyMatrix_[i].first.uuid_].first;
		}
	}

	return min_dist_node_id;
}


template<typename T1, typename T2>
void Graph<T1, T2>::FordAlgorithm(std::vector<std::string> &shortest_path, int32_t start_vertex_index)
{
	std::map<int64_t, std::pair<T2, int64_t> > current_label_map, previous_label_map;	// Node_ID --> Current Distance, Predecessor_Node_ID
	std::map<int64_t, int32_t> node_index_map;		// Node_ID --> Number of Node in the Adjacency Matrix
	GenerateLabelAndNodeMap(current_label_map, start_vertex_index, node_index_map);
    
	std::vector<std::pair<std::pair<int64_t, int64_t>, T2> > edge_node_uuids_dist_map;
	for (int32_t i = 0; i < adjacencyMatrix_.size(); i++) {
		for (int32_t j = 0; j < adjacencyMatrix_[i].second.size(); j++) {
			if (adjacencyMatrix_[i].second[j] > 0)
				edge_node_uuids_dist_map.push_back(std::pair<std::pair<int64_t, int64_t>, T2>(std::pair<int64_t, int64_t>(adjacencyMatrix_[i].first.uuid_, adjacencyMatrix_[j].first.uuid_), adjacencyMatrix_[i].second[j]));
		}
	}

	bool CONTINUE_EXHAUSTIVE_FORD_ALGO_COND = true;
	int64_t iteration_count = 0;

	while (CONTINUE_EXHAUSTIVE_FORD_ALGO_COND) {

		for (const auto &elem : edge_node_uuids_dist_map)
			if (current_label_map[elem.first.second].first > current_label_map[elem.first.first].first + elem.second) {
				current_label_map[elem.first.second].first = current_label_map[elem.first.first].first + elem.second;
				current_label_map[elem.first.second].second = elem.first.first;
			}

		++iteration_count;
		if (iteration_count > 1) {
			bool EXACT_MATCH_COND = true;
			for (const auto& elem : adjacencyMatrix_)
				EXACT_MATCH_COND = EXACT_MATCH_COND && (previous_label_map[elem.first.uuid_].first == current_label_map[elem.first.uuid_].first);
			CONTINUE_EXHAUSTIVE_FORD_ALGO_COND = !EXACT_MATCH_COND;
		}
		previous_label_map = current_label_map;

		// Print this if you want to see the change in shortest path distances in all iterations
		std::string path_iter_str = "";
		for (int32_t i = 0; i < adjacencyMatrix_.size(); i++)	{
			path_iter_str += "(" + std::to_string(adjacencyMatrix_[i].first.uuid_) +
							 "->" + std::to_string(current_label_map[adjacencyMatrix_[i].first.uuid_].first) +
							 "," + std::to_string(current_label_map[adjacencyMatrix_[i].first.uuid_].second) + ")";
			path_iter_str += (i == adjacencyMatrix_.size() - 1) ? "" : ";";
		}
		std::cout << "\nIteration " << iteration_count << ": [" << path_iter_str << "]";
	}
	
	std::string iterations = "\nNumber of Iterations = " + std::to_string(iteration_count) + "\n";
	shortest_path.push_back(iterations);
	
	GenerateShortestPathFromLabelMap(current_label_map, shortest_path);
}


template<typename T1, typename T2>
void Graph<T1, T2>::GenericLabelCorrectingAlgorithm(std::vector<std::string> &shortest_path, int32_t start_vertex_index)
{
	std::map<int64_t, std::pair<T2, int64_t> > label_map;	// Node_ID --> Current Distance, Predecessor_Node_ID
	std::map<int64_t, int32_t> node_index_map;		// Node_ID --> Number of Node in the Adjacency Matrix
	GenerateLabelAndNodeMap(label_map, start_vertex_index, node_index_map);

	std::map<int64_t, int32_t> node_uuid_frequency;
	for (const auto &elem : adjacencyMatrix_)	node_uuid_frequency.insert(std::pair<int64_t, int32_t>(elem.first.uuid_, 0));
	
	std::deque<int64_t> node_uuid_queue;
	node_uuid_queue.push_back(adjacencyMatrix_[start_vertex_index].first.uuid_);
	node_uuid_frequency[adjacencyMatrix_[start_vertex_index].first.uuid_] += 1;

	int32_t count = 0;
	while (!node_uuid_queue.empty())
	{
		int64_t minimal_curr_dist_node_id = node_uuid_queue.front();
		node_uuid_queue.pop_front();

		bool FOUND_ELEM_COND = false;
		for (int32_t j = 0; j < adjacencyMatrix_.size(); j++)
		if (adjacencyMatrix_[node_index_map[minimal_curr_dist_node_id]].second[j] > 0 /* !=0 && !-ve*/) {
			if (label_map[adjacencyMatrix_[j].first.uuid_].first > label_map[minimal_curr_dist_node_id].first + adjacencyMatrix_[node_index_map[minimal_curr_dist_node_id]].second[j]) {
				label_map[adjacencyMatrix_[j].first.uuid_].first = label_map[minimal_curr_dist_node_id].first + adjacencyMatrix_[node_index_map[minimal_curr_dist_node_id]].second[j];
				label_map[adjacencyMatrix_[j].first.uuid_].second = minimal_curr_dist_node_id;
				
				FOUND_ELEM_COND = false;
				for (const auto & elem: node_uuid_queue)
					if (elem == adjacencyMatrix_[j].first.uuid_) {
						FOUND_ELEM_COND = true;
						break;
					}
				
				if (!FOUND_ELEM_COND)	{
					node_uuid_frequency[adjacencyMatrix_[j].first.uuid_] += 1;
					std::deque<int64_t>::iterator it = node_uuid_queue.begin();
					for (; it != node_uuid_queue.end(); ++it)
						if (node_uuid_frequency[*it] < node_uuid_frequency[adjacencyMatrix_[j].first.uuid_]) 
							break;
					node_uuid_queue.insert(it, adjacencyMatrix_[j].first.uuid_);
				}
			}
		}

		++count;

		// Print this if you want to see the change in shortest path distances in all iterations
		std::string path_iter_str = "";
		for (int32_t i = 0; i < adjacencyMatrix_.size(); i++)	{
			path_iter_str += "(" + std::to_string(adjacencyMatrix_[i].first.uuid_) +
				"->" + std::to_string(label_map[adjacencyMatrix_[i].first.uuid_].first) +
				"," + std::to_string(label_map[adjacencyMatrix_[i].first.uuid_].second) + ")";
			path_iter_str += (i == adjacencyMatrix_.size() - 1) ? "" : ";";
		}
		std::cout << "\nIteration " << count << ": [" << path_iter_str << "]";
	}

	std::string iterations = "\nNumber of Iterations = " + std::to_string(count) + "\n";
	shortest_path.push_back(iterations);
	GenerateShortestPathFromLabelMap(label_map, shortest_path);
}


template<typename T1, typename T2>
void Graph<T1, T2>::WFIAlgorithm(std::vector<std::string> &shortest_path)
{
	std::vector<std::pair<int32_t, std::vector<T2> > > weight_matrix;

	for (int32_t i = 0; i < adjacencyMatrix_.size(); i++) {
		std::vector<T2> row_weights;
		for (int32_t j = 0; j < adjacencyMatrix_[i].second.size(); j++)
			if (i == j)	row_weights.push_back(T2(0));
			else if (adjacencyMatrix_[i].second[j] > 0)		row_weights.push_back(adjacencyMatrix_[i].second[j]);
			else row_weights.push_back(T2(INFINITE_WEIGHT));
		weight_matrix.push_back(std::pair<int32_t, std::vector<T2> >(i, row_weights));
	}

	for (int32_t i = 0; i < adjacencyMatrix_.size(); i++)	
		for (int32_t j = 0; j < adjacencyMatrix_.size(); j++)	
			for (int32_t k = 0; k < adjacencyMatrix_.size(); k++)	
				if (weight_matrix[j].second[k] > weight_matrix[j].second[i] + weight_matrix[i].second[k])
					weight_matrix[j].second[k] = weight_matrix[j].second[i] + weight_matrix[i].second[k];
	
	// Writing the matrix for the All-To-All Shortest Path
	std::string nodes_info_str = "\t";
	for (const auto& elem : adjacencyMatrix_)	nodes_info_str += std::to_string(elem.first.uuid_) + "\t";
	shortest_path.push_back(nodes_info_str + "\n");

	for (const auto& elem : weight_matrix) {
		nodes_info_str = std::to_string(adjacencyMatrix_[elem.first].first.uuid_) + "\t";
		for (const auto & elem2 : elem.second)
			nodes_info_str += std::to_string(elem2) + "\t";
		nodes_info_str += "\n";
		shortest_path.push_back(nodes_info_str);
	}
}


template<typename T1, typename T2>
void Graph<T1, T2>::MinimumSpanningTree(std::vector<std::string> &mst_adjacency_matrix, int32_t flag)
{
	mst_adjacency_matrix = {};

	switch (flag)
	{
	case 0:
		KruskalAlgorithm(mst_adjacency_matrix);
		break;

	case 1:
		DijkstraMSTAlgorithm(mst_adjacency_matrix);
		break;

	default:
		break;
	}
}


template<typename T1, typename T2>
void Graph<T1, T2>::KruskalAlgorithm(std::vector<std::string> &mst_adjacency_matrix)
{
	std::vector<std::pair<T2, std::pair<int64_t, int64_t> > > edges_list, path_edges_list;
	std::map<int64_t, int32_t> node_uuid_index_map;
	GenerateEdgesListAndNodeMap(edges_list, node_uuid_index_map);
	std::sort(edges_list.begin(), edges_list.end());

	std::vector<std::pair<int64_t, std::vector<T2> > > intermediate_adjacency_matrix, temp_intermediate_adjacency_matrix;
	for (const auto &elem : adjacencyMatrix_) {
		std::vector<T2> row_edge_weights(elem.second.size(), T2(0));
		intermediate_adjacency_matrix.push_back(std::pair<int64_t, std::vector<T2> >(elem.first.uuid_, row_edge_weights));
	}

	intermediate_adjacency_matrix[node_uuid_index_map[edges_list[0].second.first]].second[node_uuid_index_map[edges_list[0].second.second]] = edges_list[0].first;
	intermediate_adjacency_matrix[node_uuid_index_map[edges_list[0].second.second]].second[node_uuid_index_map[edges_list[0].second.first]] = T2(-1) * edges_list[0].first;

	std::set<int64_t> parsed_nodes_set;
	parsed_nodes_set.insert(edges_list[0].second.first);
	parsed_nodes_set.insert(edges_list[0].second.second);

	for (int32_t i = 1; (i < edges_list.size())&&(parsed_nodes_set.size() < numGraphNodes_); i++) {
		temp_intermediate_adjacency_matrix = intermediate_adjacency_matrix;
		temp_intermediate_adjacency_matrix[node_uuid_index_map[edges_list[i].second.first]].second[node_uuid_index_map[edges_list[i].second.second]] = edges_list[i].first;
		temp_intermediate_adjacency_matrix[node_uuid_index_map[edges_list[i].second.second]].second[node_uuid_index_map[edges_list[i].second.first]] = T2(-1) * edges_list[i].first;
		if (!DetectCycle(temp_intermediate_adjacency_matrix, path_edges_list)) {
			intermediate_adjacency_matrix = temp_intermediate_adjacency_matrix;
			if (parsed_nodes_set.count(edges_list[i].second.first) == 0)	parsed_nodes_set.insert(edges_list[i].second.first);
			if (parsed_nodes_set.count(edges_list[i].second.second) == 0)	parsed_nodes_set.insert(edges_list[i].second.second);
		}
	}

	// Writing the matrix for the All-To-All Shortest Path
	std::string nodes_info_str = "\t";
	for (const auto& elem : adjacencyMatrix_)	nodes_info_str += std::to_string(elem.first.uuid_) + "\t";
	mst_adjacency_matrix.push_back(nodes_info_str + "\n");

	for (const auto& elem : intermediate_adjacency_matrix) {
		nodes_info_str = std::to_string(elem.first) + "\t";
		for (const auto & elem2 : elem.second)		nodes_info_str += std::to_string(elem2) + "\t";
		nodes_info_str += "\n";
		mst_adjacency_matrix.push_back(nodes_info_str);
	}
}


template<typename T1, typename T2>
void Graph<T1, T2>::DijkstraMSTAlgorithm(std::vector<std::string> &mst_adjacency_matrix)
{
	std::vector<std::pair<T2, std::pair<int64_t, int64_t> > > edges_list, path_edges_list; 
	std::map<int64_t, int32_t> node_uuid_index_map;
	GenerateEdgesListAndNodeMap(edges_list, node_uuid_index_map);

	std::vector<std::pair<int64_t, std::vector<T2> > > intermediate_adjacency_matrix, temp_intermediate_adjacency_matrix;
	for (const auto &elem : adjacencyMatrix_) {
		std::vector<T2> row_edge_weights(elem.second.size(), T2(0));
		intermediate_adjacency_matrix.push_back(std::pair<int64_t, std::vector<T2> >(elem.first.uuid_, row_edge_weights));
	}

	intermediate_adjacency_matrix[node_uuid_index_map[edges_list[0].second.first]].second[node_uuid_index_map[edges_list[0].second.second]] = edges_list[0].first;
	intermediate_adjacency_matrix[node_uuid_index_map[edges_list[0].second.second]].second[node_uuid_index_map[edges_list[0].second.first]] = T2(-1) * edges_list[0].first;

	std::set<int64_t> parsed_nodes_set;
	parsed_nodes_set.insert(edges_list[0].second.first);
	parsed_nodes_set.insert(edges_list[0].second.second);

	for (int32_t i = 1; (i < edges_list.size()) && (parsed_nodes_set.size() < numGraphNodes_); i++) {
		temp_intermediate_adjacency_matrix = intermediate_adjacency_matrix;
		temp_intermediate_adjacency_matrix[node_uuid_index_map[edges_list[i].second.first]].second[node_uuid_index_map[edges_list[i].second.second]] = edges_list[i].first;
		temp_intermediate_adjacency_matrix[node_uuid_index_map[edges_list[i].second.second]].second[node_uuid_index_map[edges_list[i].second.first]] = T2(-1) * edges_list[i].first;
		if (DetectCycle(temp_intermediate_adjacency_matrix, path_edges_list)) {
			EliminateEdgeWithMaximumWeight(temp_intermediate_adjacency_matrix, path_edges_list, node_uuid_index_map);
		}
		intermediate_adjacency_matrix = temp_intermediate_adjacency_matrix;
		for (const auto &elem : intermediate_adjacency_matrix)
			for (int32_t j = 0; j < elem.second.size(); j++)
				if (elem.second[j] > 0) {
					if (parsed_nodes_set.count(elem.first) == 0)		
						parsed_nodes_set.insert(elem.first);
					if (parsed_nodes_set.count(intermediate_adjacency_matrix[j].first) == 0)		
						parsed_nodes_set.insert(intermediate_adjacency_matrix[j].first);
				}
	}

	// Writing the matrix for the All-To-All Shortest Path
	std::string nodes_info_str = "\t";
	for (const auto& elem : adjacencyMatrix_)	nodes_info_str += std::to_string(elem.first.uuid_) + "\t";
	mst_adjacency_matrix.push_back(nodes_info_str + "\n");

	for (const auto& elem : intermediate_adjacency_matrix) {
		nodes_info_str = std::to_string(elem.first) + "\t";
		for (const auto & elem2 : elem.second)		nodes_info_str += std::to_string(elem2) + "\t";
		nodes_info_str += "\n";
		mst_adjacency_matrix.push_back(nodes_info_str);
	}
}


template<typename T1, typename T2>
void Graph<T1, T2>::GenerateEdgesListAndNodeMap(std::vector<std::pair<T2, std::pair<int64_t, int64_t> > > &edges_list, std::map<int64_t, int32_t> &node_uuid_index_map)
{
	int32_t index_count = 0;
	for (const auto &elem : adjacencyMatrix_) {
		node_uuid_index_map.insert(std::pair<int64_t, int32_t>(elem.first.uuid_, index_count));
		++index_count;
		for (int32_t j = 0; j < elem.second.size(); j++) 
			if (elem.second[j] > 0)	
				edges_list.push_back(std::pair<T2, std::pair<int64_t, int64_t> >(elem.second[j], std::pair<int64_t, int64_t>(elem.first.uuid_,adjacencyMatrix_[j].first.uuid_)));
	}
}


template<typename T1, typename T2>
bool Graph<T1, T2>::DetectCycle(std::vector<std::pair<int64_t, std::vector<T2> > > &adjacency_matrix, std::vector<std::pair<T2, std::pair<int64_t, int64_t> > > &path_edges_list)
{
	path_edges_list = {};

	std::deque<int64_t> node_uuid_queue;
	std::map<int64_t, int32_t> node_num_map;
	std::map<int64_t, int32_t> node_index_map;
	
	for (int32_t i = 0; i < adjacency_matrix.size(); i++)	{
		node_num_map.insert(std::pair<int64_t, int32_t>(adjacency_matrix[i].first, 0));
		node_index_map.insert(std::pair<int64_t, int32_t>(adjacency_matrix[i].first, i));
		node_uuid_queue.push_back(adjacency_matrix[i].first);
	}

	int32_t dfs_count = 0;
	bool CYCLE_ABSENT_COND = true;
	while ((!CheckNodeNumQueueIsEmpty(node_uuid_queue, node_num_map)) && (CYCLE_ABSENT_COND)) {
		int64_t front_node_uuid = node_uuid_queue.front();
		node_uuid_queue.pop_front();

		GraphDepthCycle(adjacency_matrix, front_node_uuid, node_index_map, node_num_map, path_edges_list, dfs_count, CYCLE_ABSENT_COND);
	}

	return (!CYCLE_ABSENT_COND);
}


template<typename T1, typename T2>
void Graph<T1, T2>::GraphDepthCycle(std::vector<std::pair<int64_t, std::vector<T2> > > &adjacency_matrix, int64_t front_node_uuid, std::map<int64_t, int32_t> &node_index_map, std::map<int64_t, int32_t> &node_num_map, std::vector<std::pair<T2, std::pair<int64_t, int64_t> > > &path_edges_list, int32_t &dfs_count, bool &CYCLE_ABSENT_COND)
{
	node_num_map[front_node_uuid] = ++dfs_count;
	for (int32_t j = 0; (j < adjacency_matrix.size()) && (CYCLE_ABSENT_COND); j++)
		if (adjacency_matrix[node_index_map[front_node_uuid]].second[j] > 0 /* !=0 && !-ve*/) {
			if (node_num_map[adjacency_matrix[j].first] == 0) {
				GraphDepthCycle(adjacency_matrix, adjacency_matrix[j].first, node_index_map, node_num_map, path_edges_list, dfs_count, CYCLE_ABSENT_COND);
				if (!CYCLE_ABSENT_COND)		
					path_edges_list.insert(path_edges_list.begin(), std::pair<T2, std::pair<int64_t, int64_t> >(adjacency_matrix[node_index_map[front_node_uuid]].second[j], std::pair<int64_t, int64_t>(front_node_uuid, adjacency_matrix[j].first)));
			} else if (path_edges_list.empty()) {
				// Cycle detected in the Graph: MST not possible with this cycle
				CYCLE_ABSENT_COND = false;
				path_edges_list.insert(path_edges_list.begin(), std::pair<T2, std::pair<int64_t, int64_t> >(adjacency_matrix[node_index_map[front_node_uuid]].second[j], std::pair<int64_t, int64_t>(front_node_uuid, adjacency_matrix[j].first)));
			}
		}
}


template<typename T1, typename T2>
void Graph<T1, T2>::EliminateEdgeWithMaximumWeight(std::vector<std::pair<int64_t, std::vector<T2> > > &adjacency_matrix, std::vector<std::pair<T2, std::pair<int64_t, int64_t> > > &path_edges_list, std::map<int64_t, int32_t> &node_uuid_index_map)
{
	std::sort(path_edges_list.begin(), path_edges_list.end());

	adjacency_matrix[node_uuid_index_map[path_edges_list[path_edges_list.size() - 1].second.first]].second[node_uuid_index_map[path_edges_list[path_edges_list.size() - 1].second.second]] = 0;
	adjacency_matrix[node_uuid_index_map[path_edges_list[path_edges_list.size() - 1].second.second]].second[node_uuid_index_map[path_edges_list[path_edges_list.size() - 1].second.first]] = 0;
}

#endif		// _OPENSOURCE_DATASTRUCTS_ALGOS_GRAPH_H