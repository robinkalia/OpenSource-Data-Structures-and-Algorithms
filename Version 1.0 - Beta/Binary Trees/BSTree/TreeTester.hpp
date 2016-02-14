// Robin Kalia
// robinkalia@berkeley.edu
// BSTree: Implementation of various algorithms in Binary Search Tree
// 
// TreeTester.hpp: Class that tests various methods of the BSTree class

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

#ifndef _OPENSOURCE_DATASTRUCTS_ALGOS_BSTREE_TESTER_H
#define _OPENSOURCE_DATASTRUCTS_ALGOS_BSTREE_TESTER_H

#include "BSTree.hpp"

template<typename T>
class TreeTester {
private:
	BSTree<T> tree;

protected:



public:
	void TestTree();

};



template<typename T>
void TreeTester<T>::TestTree()
{
	int32_t max_h = 4;
	int32_t max_elems = 1 << max_h - 1;
	std::vector<T> elem_list;
	for (int32_t i = 0; i < max_elems; i++)     elem_list.push_back(static_cast<T>(i));

	tree.CreateDummyTree(elem_list);

	tree.InOrderDFS();
	tree.PreOrderDFS();
	tree.PostOrderDFS();
}

#endif		// _OPENSOURCE_DATASTRUCTS_ALGOS_BSTREE_TESTER_H