#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

struct Node {
  std::string name;
  Node *next = nullptr;
  Node *prev = nullptr;
};

struct NodeList {
  Node *head = nullptr;
  Node *tail = nullptr;
};

// traverses through the list and returns the node that the new node should be
// inserted before
Node *findInsertPosition(NodeList &list, const std::string &data) {
  // start at the node after the head because insertNode() already checked the
  // head
  Node *curr = list.head->next;

  // traverse through the list until the name to insert is less than curr->name
  while (data > curr->name) {
    curr = curr->next;
  }

  // return curr, which should come after the new node in the list
  return curr;
}

/*
if(!head){ //no other nodes
}else if (data< head->name){ //smaller than head
}else if (data> tail->name){ //larger than tail
}else{ //somewhere in the middle
}
*/
void insertNode(NodeList &list, const std::string &data) {
  if (!list.head) {
    Node *newNode = new Node{data, nullptr, nullptr};
    list.head = newNode;
    list.tail = newNode;
  } else if (data < list.head->name) {
    Node *newNode = new Node{data, list.head, nullptr};
    list.head->prev = newNode;
    list.head = newNode;
  } else if (data > list.tail->name) {
    Node *newNode = new Node{data, nullptr, list.tail};
    list.tail->next = newNode;
    list.tail = newNode;
  } else {
    Node *insertBefore = findInsertPosition(list, data);
    Node *newNode = new Node{data, insertBefore, insertBefore->prev};
    insertBefore->prev->next = newNode;
    insertBefore->prev = newNode;
  }
}

Node *findMatchingNode(NodeList &list, const std::string &data) {
  // start at the head
  Node *curr = list.head;

  // traverse through the list until a matching name is found or the end is
  // reached
  while (curr && curr->name != data) {
    curr = curr->next;
  }

  // returns nullptr if no such node exists
  return curr;
}

// student may be at the head, the tail or in the middle
/*
to be more specific, there are 5 cases:
1. node is the head and the tail (only node in the list)
2. node is the head
3. node is the tail
4. node is in the middle
5. node does not exist/list is empty
*/
void deleteNode(NodeList &list, const std::string &data) {
  Node *deletionTarget = findMatchingNode(list, data);

  // case 5: handle no matching node; also handles empty list
  if (deletionTarget) {
    // case 1/2: node is the head
    if (deletionTarget == list.head) {
      // advance the head
      list.head = list.head->next;

      // case 2: if the list is not empty at this point, set the new head's prev
      // pointer to nullptr
      if (list.head) {
        list.head->prev = nullptr;
      }
    } else {
      // case 3/4: node is in the middle or at the tail
      // set the next pointer of the node before the
      // deletion target to the node after it
      deletionTarget->prev->next = deletionTarget->next;
    }
    // case 1/3: node is the tail
    if (deletionTarget == list.tail) {
      // advance (retreat?) the tail
      list.tail = list.tail->prev;

      // case 3: if the list is not empty at this point, set the new tail's next
      // pointer to nullptr
      if (list.tail) {
        list.tail->next = nullptr;
      }
    } else {
      // case 2/4: node is in the middle or at the head
      // set the prev pointer of the node after the
      // deletion target to the node before it
      deletionTarget->next->prev = deletionTarget->prev;
    }

    delete deletionTarget;
  }
}

// traverse the list in ascending order and print to outputFile
void displayAscending(const NodeList &list, std::ofstream &outputFile) {
  // start at the head
  Node *curr = list.head;

  // for each node, print the name to the file and advance to the next node
  while (curr) {
    outputFile << curr->name << std::endl;
    curr = curr->next;
  }
}

// traverse the list in descending order and print to outputFile
void displayDescending(const NodeList &list, std::ofstream &outputFile) {
  // start at the tail
  Node *curr = list.tail;

  // for each node, print the name to the file and advance (retreat?) to the
  // previous node
  while (curr) {
    outputFile << curr->name << std::endl;
    curr = curr->prev;
  }
}

void convertToLower(std::string &str) {
  std::transform(str.begin(), str.end(), str.begin(),
                 [](unsigned char c) { return std::tolower(c); });
}

int main() {
  // initialize empty list
  NodeList list;

  // build list from input file
  std::ifstream inputFile("input.txt");
  std::string lineText;

  // for each line in the file:
  // if it starts with "delete ", call deleteNode()
  // else call insertNode()
  while (std::getline(inputFile, lineText)) {
    convertToLower(lineText);

    if (lineText.substr(0, 7) == "delete ") {
      deleteNode(list, lineText.substr(7));
    } else {
      insertNode(list, lineText);
    }
  }
  inputFile.close();

  // output: only runs on non-empty lists
  if (list.head) {
    // open target output file
    std::ofstream outputFile("output.txt");

    // display list in ascending order
    displayAscending(list, outputFile);

    // display separator
    outputFile << "=============" << std::endl;

    // display list in descending order
    displayDescending(list, outputFile);

    outputFile.close();
  }

  return 0;
}