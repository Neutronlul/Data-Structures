#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct node {
  int key;
  int height;
  node *left = nullptr;
  node *right = nullptr;
};

class Queue {
private:
  struct queueNode {
    node *treeNode;
    queueNode *next;
  };
  queueNode *front = nullptr;
  queueNode *rear = nullptr;

public:
  void enqueue(node *newNode) {
    // Do nothing if newNode is nullptr
    if (!newNode) {
      return;
    }

    // If the queue is empty, create the first node
    // Otherwise, append to the end and step the rear pointer
    if (!front) {
      front = new queueNode{newNode, nullptr};
      rear = front;
    } else {
      rear->next = new queueNode{newNode, nullptr};
      rear = rear->next;
    }
  }
  node *dequeue() {
    // As long as there's something in the queue,
    // pop the front node and return it
    queueNode *temp = front;
    node *treeNode = front->treeNode;
    front = front->next;

    // If the queue only had one node, set rear to nullptr as well
    if (!front) {
      rear = nullptr;
    }

    delete temp;

    return treeNode;
  }
  bool notEmpty() { return front != nullptr; }
};

node *newNode(int key) {
  node *newNode = new node;
  newNode->key = key;
  newNode->height = 0; // insertions will always be leaf nodes
  return (newNode);
}

// Returns the height of a node
// Leaf nodes have a height of -1
int height(node *node) {
  if (node == nullptr) {
    return -1;
  } else {
    return node->height;
  }
}

node *leftRotate(node *x) {
  struct node *y = x->right;
  // add more code to rotate to the left, update heights for x and y

  struct node *z = y->left;

  // Rotate to the left
  y->left = x;
  x->right = z;

  // Update heights
  x->height = std::max(height(x->left), height(x->right)) + 1;
  y->height = std::max(height(y->left), height(y->right)) + 1;

  return y;
}

node *rightRotate(node *x) {
  struct node *y = x->left;
  // add more code to rotate to the right, update heights for x and y

  struct node *z = y->right;

  // Rotate to the right
  y->right = x;
  x->left = z;

  // Update heights
  x->height = std::max(height(x->left), height(x->right)) + 1;
  y->height = std::max(height(y->left), height(y->right)) + 1;

  return y;
}

// Balance = height of the left subtree - height of the right subtree
int getBalance(node *node) { return height(node->left) - height(node->right); }

node *rebalance(node *node) {
  node->height = std::max(height(node->left), height(node->right)) + 1;

  int balance = getBalance(node); // node->left - node->right

  // If Left heavy outside : return rightRotate(node);
  if (balance == 2 && getBalance(node->left) == 1)
    return rightRotate(node);

  // If right heavy outside: return leftRotate(node);
  if (balance == -2 && getBalance(node->right) == -1)
    return leftRotate(node);

  // If left heavy inside: left rotation first, right rotation 2nd, return top
  // node
  if (balance == 2 && getBalance(node->left) == -1) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  // if right heavy inside: right rotation first, left rotation 2nd, return top
  // node
  if (balance == -2 && getBalance(node->right) == 1) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  // if no rotation, return node
  return node;
}

// non-tail recursive algorithm because of rebalance
node *insert(node *node, int key) {
  // recursive Code for inserting a node
  // When insert happens set height to 0 for the node
  if (node == NULL)
    return (newNode(key));
  if (key < node->key)
    node->left = insert(node->left, key);
  else
    node->right = insert(node->right, key);
  node = rebalance(node); // update heights and rebalance
  return node;
}

std::vector<int> parseInput(const std::string &lineText) {
  std::istringstream iss(lineText);
  std::vector<int> keys;
  int number;

  while (iss >> number) {
    keys.push_back(number);
  }

  return keys;
}

// Builds a tree from an array of integers
node *buildTree(const std::vector<int> &keys) {
  node *root = nullptr;

  // Go through the array and insert each element into the tree
  for (int i = 0; i < keys.size(); i++) {
    root = insert(root, keys[i]);
  }

  return root;
}

void displayTree(node *root, std::ofstream &outputFile) {
  // Create the two queues
  Queue currentLevel, nextLevel;

  // Start by enqueueing the root of the tree
  currentLevel.enqueue(root);

  // Process nodes level by level
  while (currentLevel.notEmpty()) {
    // For each node in the current level, dequeue it, print it,
    // and enqueue its children to the next level
    node *currentNode = currentLevel.dequeue();

    outputFile << currentNode->key << " ";

    // Print the height and balance
    outputFile << "(" << currentNode->height << ", " << getBalance(currentNode)
               << ") ";

    nextLevel.enqueue(currentNode->left);
    nextLevel.enqueue(currentNode->right);

    // If the current level is empty, swap to the next level
    if (!currentLevel.notEmpty()) {
      currentLevel = nextLevel;
      nextLevel = Queue();
      outputFile << std::endl;
    }
  }

  outputFile << std::endl;
}

int main() {
  // Open input file
  std::ifstream inputFile("input.txt");
  std::string lineText;

  // Prepare output file
  std::ofstream outputFile("output.txt");

  // This supports multiple datasets in the input file
  // one dataset per line, space separated integers
  while (std::getline(inputFile, lineText)) {
    // Parse the line into an array of integers
    std::vector<int> keys = parseInput(lineText);

    // Build the AVL tree from the array
    node *tree = buildTree(keys);

    outputFile << "Tree for dataset {" << lineText << "}:" << std::endl;

    // print the tree to the output file, level by level
    displayTree(tree, outputFile);
  }

  inputFile.close();
  outputFile.close();

  return 0;
}