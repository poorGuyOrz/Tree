#include <bits/stdc++.h>
using namespace std;

struct node {
  int key;
  int height;
  struct node *left, *right;
};

int getHeight(node *root) {
  if (root == nullptr) return 0;
  return root->height;
}

struct node *newNode(int item) {
  auto *temp = (struct node *)malloc(sizeof(struct node));
  temp->key = item;
  temp->left = temp->right = nullptr;
  temp->height = 1;
  return temp;
}

void updateHeight(node *root) { root->height = max(getHeight(root->left), getHeight(root->right)) + 1; }

void leftRotation(node *&root) {
  node *temp = root->right;
  root->right = temp->left;  // 1. 让B的左子树成为结点A的右子树
  temp->left = root;         // 2. 让结点A成为B的左子树
  // 由于更改了树的结构，因此更新变动结点的高度
  updateHeight(root);
  updateHeight(temp);
  root = temp;  // 3. 将根结点设定为结点B
}

void rightRotation(node *&root) {
  node *temp = root->left;
  root->left = temp->right;  // 1. 让A的右子树成为结点B的左子树
  temp->right = root;        // 2. 让结点B成为A的右子树
  // 由于更改了树的结构，因此更新变动结点的高度
  updateHeight(root);
  updateHeight(temp);
  root = temp;  // 3. 将根结点设定为结点A
}

int getBalanceFactor(node *root) {
  // 左子树与右子树高度之差
  return getHeight(root->left) - getHeight(root->right);
}

// 中序遍历
void inorder(struct node *root) {
  if (root != nullptr) {
    inorder(root->left);
    cout << root->key << " : ";
    inorder(root->right);
  }
}

// 先序遍历
void preOrder(node *root) {
  if (root != nullptr) {
    cout << root->key << " : ";
    preOrder(root->left);
    preOrder(root->right);
  }
}

void dfs(node *root) {
  std::stack<node *> stack;
  stack.push(root);
  while (!stack.empty()) {
    node *n = stack.top();
    stack.pop();
    cout << n->key << " : ";
    if (n->right != nullptr) stack.push(n->right);
    if (n->left != nullptr) stack.push(n->left);
  }
}

void bfs(node *root) {
  std::queue<node *> queue;
  queue.push(root);
  while (!queue.empty()) {
    node *n = queue.front();
    queue.pop();
    cout << n->key << " : ";
    if (n->left != nullptr) queue.push(n->left);
    if (n->right != nullptr) queue.push(n->right);
  }
}

// 后序遍历
void poOrder(node *root) {
  if (root != nullptr) {
    poOrder(root->left);
    poOrder(root->right);
    cout << root->key << " : ";
  }
}

void balanceNode(node *&root) {
  if (getBalanceFactor(root) == 2) {
    if (getBalanceFactor(root->left) == 1)
      rightRotation(root);  // LL
    else {                  // LR
      leftRotation(root->left);
      rightRotation(root);
    }
  } else if (getBalanceFactor(root) == -2) {
    if (getBalanceFactor(root->right) == -1)
      leftRotation(root);  // RR
    else {                 // RL
      rightRotation(root->right);
      leftRotation(root);
    }
  }
}

struct node *insert(struct node *node, int key) {
  if (node == nullptr) return newNode(key);

  if (key < node->key)
    node->left = insert(node->left, key);
  else if (key > node->key)
    node->right = insert(node->right, key);
  else
    return node;

  updateHeight(node);

  balanceNode(node);

  return node;
}

struct node *minValueNode(struct node *node) {
  auto current = node;
  while (current && current->left != nullptr) current = current->left;
  return current;
}

struct node *maxValueNode(struct node *node) {
  auto current = node;
  while (current && current->right != nullptr) current = current->right;
  return current;
}

struct node *deleteNode(struct node *root, int key) {
  if (root == nullptr) return root;

  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    if (root->left == nullptr and root->right == nullptr)
      return nullptr;
    else if (root->left == nullptr) {
      auto temp = root->right;
      free(root);
      return temp;
    } else if (root->right == nullptr) {
      auto temp = root->left;
      free(root);
      return temp;
    }

    auto temp = minValueNode(root->right);

    root->key = temp->key;

    root->right = deleteNode(root->right, temp->key);
  }

  // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
  updateHeight(root);
  balanceNode(root);

  return root;
}
