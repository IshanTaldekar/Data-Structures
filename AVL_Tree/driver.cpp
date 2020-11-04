#include "avl_trees.cpp"
#include <limits>

int main() {

  avl_tree tree;

  int counter = 0;

  while(true) {

    long input;
    cout << "Input: ";
    cin >> input;
    cout << endl;

    tree.insert(input);
    tree.display();
    cin.clear();
    cin.sync();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    counter++;

    if (counter % 5 == 0) {

      cout << "MAX: " << tree.get_max() << endl;
      cout << "MIN: " << tree.get_min() << endl;
      cout << "NEXT GREATER OF: " << tree.get_next_lower(5) << endl;

    }

    cout << endl;

  }

  return 0;

}

