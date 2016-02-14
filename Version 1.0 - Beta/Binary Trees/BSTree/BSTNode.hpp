// Robin Kalia
// robinkalia@berkeley.edu
// BSTree: Implementation of various algorithms in Binary Search Tree
// 
// BSTNode.hpp: Contains implementation of the Node that is utilized in a Binary Search Tree

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


#ifndef _OPENSOURCE_DATASTRUCTS_ALGOS_BSTREE_NODE_H
#define _OPENSOURCE_DATASTRUCTS_ALGOS_BSTREE_NODE_H

#include <iostream>
#include <cstddef>
#include <stdint.h>


template<typename T>
class BSTNode {
public:
	BSTNode()  { this->leftChild_ = nullptr;  this->rightChild_ = nullptr; this->index_ = 0; }
	BSTNode(const T& val) : BSTNode()   { this->key_ = val; }
	BSTNode(const BSTNode<T>& node)   { this->key_ = node->key_;	this->leftChild_ = node->leftChild_;	this->rightChild_ = node->rightChild_; }
	~BSTNode() { this->leftChild_ = this->rightChild_ = nullptr; }

	BSTNode<T> *leftChild_, *rightChild_;
	T key_;
	int32_t index_;
};

#endif	// _OPENSOURCE_DATASTRUCTS_ALGOS_BSTREE_NODE_H