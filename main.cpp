#include "Tree.h"

// Driver Code
int main() {
  /* Let us create following BST
          50
         /  \
       30    70
      /  \  /  \
    20   4060  80
  */
  struct node *root = nullptr;
  root = insert(root, 50);
  root = insert(root, 30);
  root = insert(root, 20);
  root = insert(root, 40);
  root = insert(root, 70);
  root = insert(root, 60);
  root = insert(root, 80);

  //  root = insert(root, 9);
  //  root = insert(root, 5);
  //  root = insert(root, 10);
  //  root = insert(root, 0);
  //  root = insert(root, 6);
  //  root = insert(root, 11);
  //  root = insert(root, -1);
  //  root = insert(root, 1);
  //  root = insert(root, 2);

  cout << "Inorder traversal of the given tree \n";
  inorder(root);
  cout << "\npreOrder traversal of the given tree \n";
  preOrder(root);
  cout << "\npoOrder traversal of the given tree \n";
  poOrder(root);
  cout << "\ndfs traversal of the given tree \n";
  dfs(root);
  cout << "\nbfs traversal of the given tree \n";
  bfs(root);
  cout << getBalanceFactor(root) << endl;

  cout << "\nDelete 20\n";
  root = deleteNode(root, 10);
  cout << "Inorder traversal of the modified tree \n";
  inorder(root);

  cout << "\nDelete 30\n";
  root = deleteNode(root, 30);
  cout << "Inorder traversal of the modified tree \n";
  inorder(root);

  cout << "\nDelete 50\n";
  root = deleteNode(root, 50);
  cout << "Inorder traversal of the modified tree \n";
  inorder(root);

  return 0;
}
