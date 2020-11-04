/*

 * Author: Ishan Taldekar
 * Description: Just trying to understand AVL Trees well.

 */

#ifndef AVL_TREE
#define AVL_TREE

#include <iostream>
#include <string>
using namespace std;

/* status codes for insert and delete operations */
#define OP_CHANGED_HEIGHT 0  // insert/delete successful, subtree height changed
#define OP_MAINTAINED_HEIGHT 1  // insert/delete successful, subtree height maintained
#define OP_FAILURE 2

struct Node {

  int data;
  int balance_factor;  // the height difference of child sub-trees
  Node* left_child;
  Node* right_child;

  Node(int item): data(item), balance_factor(0), left_child(nullptr), right_child(nullptr) {}

};

class avl_tree {
  /* An AVL tree is a self-balancing binary tree, which enforces that the
     difference in the height of any nodes child subtrees can be at most 1. In
     AVL trees, search, insertion and deletion take O(log N) time complexity in
     average and worst cases. Read-only operations can be carried out on an AVL
     tree in a similar fashion as a binary search tree; however, any modifications
     must ensure that the tree remains balanced. AVL Trees are beneficial in
     cases where insertions and deletions are not that frequent but you have
     to frequently look-up for items present. */

public:

  avl_tree(): root(nullptr) {}  // default constructor

  avl_tree(int);  // constructor initializes the root to the value passed
  ~avl_tree();  // destructor
  bool insert(int);  // inserts new node in tree
  Node* find(int);  // finds a node with the matching value, if it exists.
  bool remove(int);  // finds and deletes the node
  int get_min();  // returns minimum value currently in tree
  int get_max();  // returns maximum value currently in tree
  int get_median();  // returns the root i.e. value separating the higher half from the lower half (right subtree and left subtree)
  bool contains(int);  // checks if tree contains node with given value
  int get_next_lower(int);  // returns the next lowest value in the tree
  int get_next_higher(int);  // returns next highest value in the tree
  void display();  // output tree to console

private:

  Node* root;  // tree root (member variable)

  void get_min(int&, Node*);  // get_min recursive helper function
  void get_max(int&, Node*);  // get_max recursive helper function
  void delete_subtree(Node*&);  // deletes node along with its children
  void display_subtree(Node*, int);  // TODO: COMMENT
  int insert(int, Node*&);  // inserts new node in tree (recursive helper)
  void rotate_left(Node*&);  // left tree-rotation
  void rotate_right(Node*&);  //right tree-rotation
  void balance_left_heavy(Node*&);  // balance left-heavy subtree
  void balance_right_heavy(Node*&);  // balance right_heavy subtree

};

#endif
