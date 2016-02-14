// Robin Kalia
// robinkalia@berkeley.edu
// BSTree: Implementation of various algorithms in Binary Search Tree
// 
// BSTree.hpp: Class that contains implementation of various algorithms utilized in the Binary Search Tree

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


#ifndef _OPENSOURCE_DATASTRUCTS_ALGOS_BSTREE_H
#define _OPENSOURCE_DATASTRUCTS_ALGOS_BSTREE_H

#include <vector>
#include <stack>

#include "BSTNode.hpp"

template<typename T>
class BSTree {
private:
	int32_t numNodes_;

	void DeleteNode(BSTNode<T> *node);
	void TransformMorrisInOrderTree(BSTree<T> *tree);
	void RestoreMorrisInOrderTree(BSTree<T> *tree);

protected:
	void InOrderDFS(const BSTNode<T>* node);
	void InOrderDFSStack();
	void MorrisInOrderDFS();

	void PreOrderDFS(const BSTNode<T>* node);
	void PreOrderDFSStack();

	void PostOrderDFS(const BSTNode<T>* node);

	void Visit(const BSTNode<T>* node);

public:
	BSTree()   { root_ = nullptr;  numNodes_ = 0; };
	~BSTree()  { DeleteNode(root_);  };

	BSTNode<T>* root_;
	BSTNode<T> *origRoot_;

	void CreateDummyTree(const std::vector<T> &elems);
	void BuildTree(BSTNode<T>* node, const std::vector<T> &elems);
	BSTree<T> *CreateDuplicateTree();

	void InorderDFS();
	void PreorderDFS();
	void PostorderDFS();

	void DeleteByMerging(const T& elem);
	void DeleteByCopying(const T& elem);
};


template<typename T>
void BSTree<T>::DeleteNode(BSTNode<T> *node)
{
	if (node != nullptr)	{
		DeleteNode(node->leftChild_);
		DeleteNode(node->rightChild_);
		node->leftChild_  = nullptr;
		node->rightChild_ = nullptr;
		delete node;
	}
}


template<typename T>
void BSTree<T>::Visit(const BSTNode<T>* node)
{
	std::cout << " " << node->key_;
}

template<typename T>
void BSTree<T>::InOrderDFS(const BSTNode<T>* node)
{
	if (node != nullptr)  {
		InOrderDFS(node->leftChild_);
		Visit(node);
		InOrderDFS(node->rightChild_);
	}
}

template<typename T>
void BSTree<T>::InorderDFS() {
	if (root_ == nullptr)  {
		std::cout << "Invalid Tree: Root is Null" << std::endl;
		return;
	}
	InOrderDFS(root_);
}


template<typename T>
void BSTree<T>::InOrderDFSStack()
{
	std::stack<BSTNode<T>* > stk;
	BSTNode<T>* node = root_;
	stk.push(node);
	while (node->leftChild_ != nullptr) {
		stk.push(node->leftChild_);
		node = node->leftChild_;
	}

	while (!stk.empty()) {
		BSTNode<T>* curr_node = stk.pop();
		Visit(curr_node);
		BSTNode<T>* curr_node_child = curr_node->rightChild_;
		if (curr_node_child != nullptr)		{
			stk.push(curr_node_child);
			while (curr_node_child->leftChild_ != nullptr)	{
				stk.push(curr_node->leftChild_);
				curr_node_child = curr_node_child->leftChild_;
			}
		}
	}
}


template<typename T>
void BSTree<T>::MorrisInOrderDFS()
{
	BSTree<T> *dup_tree = this->CreateDuplicateTree();
	dup_tree->origRoot_ = dup_tree->root_;
	TransformMorrisInOrderTree(dup_tree);
	BSTNode<T> *node = dup_tree->root_;
	while (node != nullptr)	{
		Visit(node);
		node = node->rightChild_;
	}

	RestoreMorrisInOrderTree(dup_tree);

	delete dup_tree;
}


template<typename T>
void BSTree<T>::TransformMorrisInOrderTree(BSTree<T> *tree)
{
	BSTNode<T> *node = tree->root_;
	BSTNode<T> *prev_node = node;

	int32_t count =  (node->leftChild_ == nullptr) ? 1 : 0;
	while ((node->leftChild_ != nullptr)||(node->rightChild_ != nullptr)) {
		BSTNode<T> *left_node = node->leftChild_;

		if (left_node != nullptr) {
			BSTNode<T> *left_node_rightmost_child = left_node;
			while (left_node_rightmost_child->rightChild_ != nullptr)	left_node_rightmost_child = left_node_rightmost_child->rightChild_;
			left_node_rightmost_child->rightChild_ = node;
			if (prev_node != node) prev_node->rightChild_ = left_node;
			node = left_node;
			prev_node = node;

			if ((node->leftChild_ == nullptr) && (count == 0)) {
				tree->root_ = node;
				++count;
			}
		}
		else {
			prev_node = node;
			node = node->rightChild_;
		}
	}
}


template<typename T>
void BSTree<T>::RestoreMorrisInOrderTree(BSTree<T> *tree)
{
	BSTNode<T> *node = tree->root_;
	BSTNode<T> *prev_node = node;
	BSTNode<T> *pred_node = nullptr;

	while (node->rightChild_ != nullptr) {
		if (node->rightChild_->leftChild_ != nullptr)	{
			prev_node = node->rightChild_->leftChild_;
			node = node->rightChild_;
			if (pred_node != nullptr)	pred_node->rightChild_ = node;
			prev_node->rightChild_ = nullptr;
			pred_node = node;
		}
		prev_node = node;
		node = node->rightChild_;
	}

	tree->root_ = tree->origRoot_;
}



template<typename T>
void BSTree<T>::PreorderDFS()
{
	if (root_ == nullptr)  {
		std::cout << "Invalid Tree: Root is Null" << std::endl;
		return;
	}
	PreOrderDFS(root_);
}


template<typename T>
void BSTree<T>::PreOrderDFS(const BSTNode<T>* node)
{
	if (node != nullptr) {
		Visit(node);
		PreOrderDFS(node->leftChild_);
		PreOrderDFS(node->rightChild_);
	}
}


template<typename T>
void BSTree<T>::PreOrderDFSStack()
{
	std::stack<BSTNode<T>* > stk;
	BSTNode<T>* node = root_;
	stk.push(node);
	while (!stk.empty()) {
		BSTNode<T>* curr_node = stk.pop();
		Visit(curr_node);
		if (curr_node->rightChild_ != nullptr)	stk.push(curr_node->rightChild_);
		if (curr_node->leftChild_ != nullptr)	stk.push(curr_node->leftChild_);
	}
}



template<typename T>
void BSTree<T>::PostorderDFS()
{
	if (root_ == nullptr)  {
		std::cout << "Invalid Tree: Root is Null" << std::endl;
		return;
	}
	PostOrderDFS(root_);
}


template<typename T>
void BSTree<T>::PostOrderDFS(const BSTNode<T>* node)
{
	if (node != nullptr) {
		PostOrderDFS(node->leftChild_);
		PostOrderDFS(node->rightChild_);
		Visit(node);
	}
}







//////////////////////////////////////
//                 0              
//         1               2
//      3     4         5     6
//	   7 8   9 10     11 12 13 14
//
// Inorder    [LVR]:  7,3,8,1,9,4,10,0,11,5,12,2,13,6,14
// Preorder   [VLR]:  0,1,3,7,8,4,9,10,2,5,11,12,6,13,14
// Postorder  [LRV]:  7,8,3,9,10,4,1,11,12,5,13,14,6,2,0


template<typename T>
void BSTree<T>::CreateDummyTree(const std::vector<T> &elems)
{
	root_ = new BSTNode<T>(elems[0]);
	++numNodes_;

	BuildTree(root_, elems);
}

template<typename T>
void BSTree<T>::BuildTree(BSTNode<T>* node, const std::vector<T> &elems)
{
	int32_t left_index = (node->index_ << 1) + 1;
	if (left_index < elems.size()) {
		int32_t left_index = (node->index_ << 1) + 1;
		node->leftChild_ = new BSTNode<T>(elems[left_index]);
		node->leftChild_->index_ = left_index;
		++numNodes_;
		BuildTree(node->leftChild_, elems);
	}

	int32_t right_index = (node->index_ + 1) << 1;
	if (right_index < elems.size()) {
		node->rightChild_ = new BSTNode<T>(elems[right_index]);
		node->rightChild_->index_ = right_index;
		++numNodes_;
		BuildTree(node->rightChild_, elems);
	}
}


template<typename T>
BSTree<T>* BSTree<T>::CreateDuplicateTree()
{
	BSTree<T> *new_tree = new BSTree<T>();
	CopyBranches(new_tree->root_, this->root_);
	return new_tree;
}


template<typename T>
void CopyBranches(BSTNode<T> *new_tree_node, BSTNode<T> orig_tree_node)
{
	if (orig_tree_node != nullptr) {
		new_tree_node = new BSTNode<T>(orig_tree_node->key_);
		CopyBranches(new_tree_node->leftChild_,  orig_tree_node->leftChild_);
		CopyBranches(new_tree_node->rightChild_, orig_tree_node->rightChild_)
	}
}


template<typename T>
void BSTree<T>::DeleteByMerging(const T& elem)
{
	if (root_ == nullptr)	return;
	BSTNode<T> *node = root_;
	BSTNode<T> *parent_node = nullptr;

	while (node->key_ != elem) {
		parent_node = node;
		if (node->key_ > elem)	node = node->leftChild_;
		else node = node->rightChild_;
	}

	if (node == nullptr)	return;
	if ((node->leftChild_ == nullptr) && (node->rightChild_ == nullptr))	{
		if (parent_node->leftChild_ == node)	parent_node->leftChild_ = nullptr;
		else parent_node->rightChild_ = nullptr;
	} else if ((node->leftChild_ == nullptr) || (node->rightChild_ == nullptr))	
	{
		BSTNode<T>* selected_child = (node->leftChild_ != nullptr) ? node->leftChild_ : node->rightChild_;
		if (parent_node->leftChild_ == node) parent_node->leftChild_ = selected_child;
		else parent_node->rightChild_ = selected_child;
	}
	else {
		BSTNode<T> *left_child_rightmost_node = node->leftChild_;
		while (left_child_rightmost_node->rightChild_ != nullptr)	left_child_rightmost_node = left_child_rightmost_node->rightChild_;
		left_child_rightmost_node->rightChild_ = node->rightChild_;
		if (parent_node->leftChild_ == node)	parent_node->leftChild_ = node->leftChild_;
		else parent_node->rightChild_ = node->leftChild_;
	}

	delete node;
	node = nullptr;
}


template<typename T>
void BSTree<T>::DeleteByCopying(const T& elem)
{
	if (root_ == nullptr)	return;
	BSTNode<T> *node = root_;

	BSTNode<T> *parent_node = nullptr;

	while (node->key_ != elem) {
		parent_node = node;
		if (node->key_ > elem)	node = node->leftChild_;
		else node = node->rightChild_;
	}

	if (node == nullptr)	return;
	if ((node->leftChild_ == nullptr) && (node->rightChild_ == nullptr))	{
		if (parent_node->leftChild_ == node)	parent_node->leftChild_ = nullptr;
		else parent_node->rightChild_ = nullptr;

		delete node;
		node = nullptr;
	}
	else if ((node->leftChild_ == nullptr) && (node->rightChild_ != nullptr)) {
		BSTNode<T> *right_child_leftmost_node_prev_node = node;
		BSTNode<T> *right_child_leftmost_node = node->rightChild_;
		while (right_child_leftmost_node->leftChild_ != nullptr)	{
			right_child_leftmost_node_prev_node = right_child_leftmost_node;
			right_child_leftmost_node = right_child_leftmost_node->leftChild_;
		}
		node->key_ = right_child_leftmost_node->key_;
		
		right_child_leftmost_node_prev_node->leftChild_ = right_child_leftmost_node->rightChild_;

		delete right_child_leftmost_node;
		right_child_leftmost_node = nullptr;
	}
	else {
		BSTNode<T> *left_child_rightmost_node_prev_node = node;
		BSTNode<T> *left_child_rightmost_node = node->leftChild_;
		while (right_child_leftmost_node->rightChild_ != nullptr)	{
			left_child_rightmost_node_prev_node = right_child_leftmost_node;
			left_child_rightmost_node = right_child_leftmost_node->rightChild_;
		}
		node->key_ = left_child_rightmost_node->key_;

		left_child_rightmost_node_prev_node->rightChild_ = left_child_rightmost_node->leftChild_;

		delete left_child_rightmost_node;
		left_child_rightmost_node = nullptr;
	}
}


#endif		// _OPENSOURCE_DATASTRUCTS_ALGOS_BSTREE_H