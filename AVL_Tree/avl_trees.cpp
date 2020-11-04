#include "avl_trees.h"

avl_tree::avl_tree(int item) {
  /* initializes avl_tree object with root set to item */

  root = new Node(item);

}

avl_tree::~avl_tree() {
  /* destructor - relies on a recursive helper */

  delete_subtree(root);

}

void avl_tree::rotate_left(Node* &current_root) {
  /* Left tree rotations are implemented by choosing the right child node as the
     pivot, setting the current root's right child pointer to the left child of
     the pivot node, setting the pivot's left child pointer to the current root
     and making the pivot the new root node */

  if (!current_root || !current_root->right_child) return;

  Node* pivot_node = current_root->right_child;
  current_root->right_child = pivot_node->left_child;
  pivot_node->left_child = current_root;

  current_root = pivot_node;

}

void avl_tree::rotate_right(Node* &current_root) {
  /* Right tree rotations are implemented by assigning the left child node of the
     current root as the pivot, setting the root's right child pointer to the
     pivot's left child node, setting the pivot's right pointer to the current
     root, and making the pivot the new root node */

  if (!current_root || !current_root->left_child) return;

  Node* pivot_node = current_root->left_child;
  current_root->left_child = pivot_node->right_child;
  pivot_node->right_child = current_root;

  current_root = pivot_node;

}

void avl_tree::balance_left_heavy(Node*& current_root) {
  /* A node with a balance factor which is less than 0 is called left-heavy. */

  Node* pivot_node = current_root->left_child;

  if (pivot_node->balance_factor < 0) {
    /* If the pivot is also left-heavy, only a single right rotation is required */

    current_root->balance_factor = 0;
    pivot_node->balance_factor = 0;
    rotate_right(current_root);

  } else if (pivot_node->balance_factor > 0) {
    /* If the pivot is right-heavy, double rotations are required (i.e. a left
       right rotation: one left rotation, followed by a right rotation) */

    Node* secondary_pivot = pivot_node->right_child;

    switch(secondary_pivot->balance_factor) {
      /* update the balance factors */

    case -1:
      current_root->balance_factor = 1;
      pivot_node->balance_factor = 0;
      break;

    case 0:
      current_root->balance_factor = 0;
      pivot_node->balance_factor = 0;
      break;

    case 1:
      current_root->balance_factor = 0;
      pivot_node->balance_factor = -1;
      break;

    }

    rotate_left(pivot_node);
    current_root->right_child = pivot_node;
    rotate_right(current_root);
    secondary_pivot->balance_factor = 0;

  }

}

void avl_tree::balance_right_heavy(Node*& current_root) {
  /* A node with a balance factor which is greater than 0 is called right-heavy. */

  Node* pivot_node = current_root->right_child;

  if (pivot_node->balance_factor > 0) {
    /* If the pivot is also right-heavy, then only a single left rotation will
       be required */

    current_root->balance_factor = 0;
    pivot_node->balance_factor = 0;
    rotate_left(current_root);

  } else if (pivot_node->balance_factor < 0) {
    /* If the pivot is left-heavy, we must perform double tree rotations. A
       right rotation will be performed first, then left rotation (called a
       right left rotation). */

    Node* secondary_pivot = pivot_node->left_child;

    switch(secondary_pivot->balance_factor) {
      /* updates balance factors */

    case -1:
      current_root->balance_factor = 0;
      pivot_node->balance_factor = 1;
      break;

    case 0:
      current_root->balance_factor = 0;
      pivot_node->balance_factor = 0;
      break;

    case 1:
      current_root->balance_factor = 0;
      pivot_node->balance_factor = -1;
      break;

    }

    secondary_pivot->balance_factor = 0;

    rotate_right(pivot_node);
    current_root->left_child = pivot_node;
    rotate_left(current_root);

  }

}

bool avl_tree::insert(int value) {
  /* inserts node into the binary search tree by relying on a recursive helper */

  int status{};
  if ((status = insert(value, root)) == OP_FAILURE) return false;

  return true;  // returns true if node was inserted

}

int avl_tree::insert(int value, Node*& current_node) {
  /* TODO: COMMENT */

  int status = OP_CHANGED_HEIGHT;

  if (!current_node) {

    current_node = new Node(value);
    return status;

  } else {

    if (value < current_node->data) {

      status = insert(value, current_node->left_child);

      if (status == OP_CHANGED_HEIGHT) {

        current_node->balance_factor -= 1;

        if (current_node->balance_factor == -2) {

          balance_left_heavy(current_node);
          status = OP_MAINTAINED_HEIGHT;

        }

      }

    } else if (value > current_node->data) {

      status = insert(value, current_node->right_child);

      if (status == OP_CHANGED_HEIGHT) {

        current_node->balance_factor += 1;

        if (current_node->balance_factor == 2) {

          balance_right_heavy(current_node);
          status = OP_MAINTAINED_HEIGHT;

        }

      }

    } else {

      status = OP_FAILURE;

    }

  }

  return status;

}

bool avl_tree::remove(int target_value) {
  /* TODO */

  return false;

}

void avl_tree::display() {

  int depth = 0;
  display_subtree(root, depth);

}

void avl_tree::display_subtree(Node* current_node, int depth) {

  if (!current_node) return;

  if (current_node->left_child) {

    display_subtree(current_node->left_child, depth + 1);

  }

  if (current_node) {

      for (int i = 0; i < depth; i++)
        cout << "  ";
      cout << current_node->data << endl;

  }

  if (current_node->right_child) {

    display_subtree(current_node->right_child, depth + 1);

  }

}

Node* avl_tree::find(int target_value) {

  Node* current_node = root;

  while (current_node) {
    /* traverse through the tree until the value is found or its no longer
       possible to traverse further */

    if (current_node->data == target_value) return current_node;

    if (target_value < current_node->data) current_node = current_node->left_child;
    else if (target_value > current_node->data) current_node = current_node->right_child;

  }

  return nullptr;

}

void avl_tree::delete_subtree(Node* &current_node) {
  /* deletes from subtree rooted at bode in a depth-first manner */

  if(!current_node) return;

  if (current_node->left_child) delete_subtree(current_node->left_child);  // traverse the left subtree first
  if (current_node->right_child) delete_subtree(current_node->right_child);  // then traverse the right subtree

  delete current_node;

}

int avl_tree::get_min() {
    /* returns the smallest integer in the tree by relying on a recursive helper */

  if (!root) return 0;

  int min_value{};
  get_min(min_value, root);

  return min_value;

}

void avl_tree::get_min(int& value, Node* current_node) {
    /* traverses down the leftmost subtree and returns the value at the leaf node */

  if (!current_node) return;

  if (current_node->left_child) get_min(value, current_node->left_child);
  else value = current_node->data;

}

int avl_tree::get_max() {

  if (!root) return 0;

  int max_value{};
  get_max(max_value, root);

  return max_value;

}

void avl_tree::get_max(int& value, Node* current_node) {
  /* traverses down the leftmost subtree and returns the value at the leaf node */

  if (!current_node) return;

  if (current_node->right_child) get_max(value, current_node->right_child);
  else value = current_node->data;

}

bool avl_tree::contains(int target_value) {
  /* if find returns a node (not NULL) then return true */

  Node* result;
  if (!(result = find(target_value))) return false;
  return true;

}

int avl_tree::get_next_lower(int value) {
  /* returns value within tree that is immediately smaller than the current value */
  /* TODO */



}

int avl_tree::get_next_higher(int value) {
  /* returns value within tree that is immediately larger than the current value */

  Node* current_node{nullptr};

  if ((current_node = find(value))) {

    if (current_node->right_child) {

      current_node = current_node->right_child;

      while (current_node->left_child) {

        current_node = current_node->left_child;

      }

      return current_node->data;
    }

  }

  return value;

}

int avl_tree::get_median() {
  /* TODO */


}