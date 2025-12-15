#include <fstream>
#include <iostream>

struct TreeNode {
  int value;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;
  TreeNode *parent = nullptr;
};

class Queue {
private:
  struct queueNode {
    TreeNode *n;
    queueNode *next;
  };
  queueNode *front = nullptr;
  queueNode *rear = nullptr;

public:
  void enqueue(TreeNode *newNode) {
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

  TreeNode *dequeue() {
    // As long as there's something in the queue,
    // pop the front node and return it
    queueNode *temp = front;
    TreeNode *treeNode = front->n;
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

class MinHeap {
private:
  TreeNode *root = nullptr;

public:
  void insertIntoHeap(int value) {
    // If the heap is empty, just create the root node
    if (!root) {
      root = new TreeNode{value};
      return;
    }

    // Find the "next" position to insert the new node
    // This is to respect the shape property of the heap

    // Prepare our queues and new node pointer, only if root exists
    Queue currentQueue, nextQueue;
    TreeNode *nn = nullptr;

    currentQueue.enqueue(root);

    while (true) {
      // Pop the top node from the current queue
      TreeNode *curr = currentQueue.dequeue();

      // Check if it has a left or right child
      // if it does, enqueue them to the next level
      // if not, insert the new node there and break
      if (!curr->left) {
        nn = curr->left = new TreeNode{value};
        nn->parent = curr;
        break;
      } else {
        nextQueue.enqueue(curr->left);
      }

      if (!curr->right) {
        nn = curr->right = new TreeNode{value};
        nn->parent = curr;
        break;
      } else {
        nextQueue.enqueue(curr->right);
      }

      // If we've completely processed the current level,
      // swap to the next level
      if (!currentQueue.notEmpty()) {
        currentQueue = nextQueue;
        nextQueue = Queue();
      }
    }

    // Finallly, restore the order property of the heap
    siftUp(nn);
  }

  void deleteNode() {
    // If the heap is empty, return
    if (!root) {
      return;
    } else if (!root->left && !root->right) {
      // If the heap only has one node, delete the root and return
      delete root;
      root = nullptr;
      return;
    }

    // Find the last node in the heap
    Queue currentQueue, nextQueue;
    TreeNode *last = nullptr;

    currentQueue.enqueue(root);

    while (currentQueue.notEmpty()) {
      last = currentQueue.dequeue();

      // Try to enqueue left and right children
      // If they don't exist, nothing happens
      nextQueue.enqueue(last->left);
      nextQueue.enqueue(last->right);

      // If we've completely processed the current level,
      // swap with and reset the next level
      if (!currentQueue.notEmpty()) {
        currentQueue = nextQueue;
        nextQueue = Queue();
      }
    }

    // Sever the last node from the tree
    // This retains the shape property of the heap
    if (last->parent->right == last) {
      last->parent->right = nullptr;
    } else {
      last->parent->left = nullptr;
    }

    // Swap its value with the root
    std::swap(root->value, last->value);

    delete last;

    // Restore the order property of the heap
    siftDown(root);
  }

  void siftUp(TreeNode *n) {
    // Base case: We've reached the root or the parent is smaller
    if (!n->parent || n->parent->value < n->value) {
      return;
    } else {
      // General case: swap with parent and call again on the parent
      std::swap(n->parent->value, n->value);
      siftUp(n->parent);
    }
  }

  void siftDown(TreeNode *n) {
    // Base case: we've reached a leaf node
    if (!n->left) {
      return;
    }

    // General case: swap with the smaller child if child is
    // smaller than n, then call again on said child
    TreeNode *smallerChild = n->left;
    if (n->right && n->right->value < n->left->value) {
      smallerChild = n->right;
    }

    if (smallerChild->value < n->value) {
      std::swap(smallerChild->value, n->value);
      siftDown(smallerChild);
    }
  }

  void displayHeap() {
    // If the heap is empty, don't display anything
    if (!root) {
      return;
    }

    // Create the two queues
    Queue currentLevel, nextLevel;

    // Start by enqueueing the root of the tree
    currentLevel.enqueue(root);

    // Process nodes level by level
    while (currentLevel.notEmpty()) {
      // For each node in the current level, dequeue it, print it,
      // and enqueue its children to the next level
      TreeNode *currentNode = currentLevel.dequeue();

      std::cout << currentNode->value << " ";

      nextLevel.enqueue(currentNode->left);
      nextLevel.enqueue(currentNode->right);

      // If the current level is empty, swap to the next level
      if (!currentLevel.notEmpty()) {
        std::swap(currentLevel, nextLevel);
        std::cout << std::endl;
      }
    }

    std::cout << std::endl;
  }
};

int main() {
  std::ifstream inputFile("input.txt");

  MinHeap heap;

  std::cout << "Insertions:" << std::endl << std::endl;

  int inputNum;
  do {
    inputFile >> inputNum;
    if (inputFile) {
      std::cout << "Inserting " << inputNum
                << " into heap. New heap:" << std::endl;
      heap.insertIntoHeap(inputNum);
      heap.displayHeap();
    }

  } while (inputFile);

  std::cout << "Deletions:" << std::endl << std::endl;

  for (int i = 0; i < 3; i++) {
    heap.deleteNode();
    heap.displayHeap();
  }

  inputFile.close();

  return 0;
}