// Robin Kalia
// robinkalia@berkeley.edu
// Graphs: Class that contains implementation of various Graph Algorithms
// 
// Edge.hpp: Contains the declaration and definition of different data members and methods of the Edge class

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


#ifndef _OPENSOURCE_DATASTRUCTS_ALGOS_GRAPH_EDGE_H
#define _OPENSOURCE_DATASTRUCTS_ALGOS_GRAPH_EDGE_H


#include "Node.hpp"

template<typename T1, typename T2>
class Edge
{
public:
	Node<T1> *startNode_;
	Node<T1> *endNode_;
	T2 edgeWeight_;

	Edge(Node<T1> *start_node, Node<T1> *end_node, const T2& edge_weight);
	~Edge();
};


template<typename T1, typename T2>
Edge<T1, T2>::Edge(Node<T1> *start_node, Node<T1> *end_node, const T2& edge_weight)
{
	startNode_	= start_node;
	endNode_	= end_node;
	edgeWeight_ = edge_weight;
}


template<typename T1, typename T2>
Edge<T1, T2>::~Edge()
{

}


#endif		//_OPENSOURCE_DATASTRUCTS_ALGOS_GRAPH_EDGE_H