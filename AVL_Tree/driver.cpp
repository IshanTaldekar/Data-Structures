#include "avl_trees.cpp"

int main() {

  avl_tree* tree = new avl_tree;
  int input_number {};
  int counter {0};
  while (counter < 100) {

    cout << "Input: ";
    cin >> input_number;

    cout << endl;
    tree->insert(input_number);
    tree->display();
    cout << endl;

    cout.flush();
    cin.clear();
    ++counter;

  }


  return 0;

}

