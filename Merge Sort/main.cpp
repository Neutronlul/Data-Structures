#include <iostream>

struct node {
  int value;
  node *next = nullptr;
};

// helper function to create a linked list from an array
node *arrayToList(int arr[], int size) {
  if (size == 0) {
    return nullptr;
  }
  node *head = new node{arr[0], nullptr};
  node *curr = head;
  for (int i = 1; i < size; i++) {
    curr->next = new node{arr[i], nullptr};
    curr = curr->next;
  }
  return head;
}

// helper printing function
void printList(node *head, const std::string &msg = "") {
  std::cout << msg;
  node *curr = head;
  while (curr) {
    std::cout << curr->value << " ";
    curr = curr->next;
  }
  std::cout << std::endl;
}

// this function takes in two pointers to nodes (by reference)
// and returns the node with the smaller value
// it also advances the pointer of the list from which the node was taken
node *getFirstNode(node *&a, node *&b) {
  if (a->value <= b->value) {
    node *first = a;
    a = a->next;
    return first;
  } else {
    node *first = b;
    b = b->next;
    return first;
  }
}

// we can assume that head's list has at least two nodes
// because this if only called from mergeSort's general case
//
// for a list with an uneven number of nodes, the first sublist (a)
// will have one more node than the second sublist (b)
void split(node *head, node *&a, node *&b) {
  // start middle and end on node 1 and 2 respectively
  node *middle = head;
  node *end = head->next;

  // as long as end is more than 1 node away from the end of the list
  // advance middle by 1 and end by 2
  //
  // we need to check for end being not null to avoid the case where
  // end jumps past the end of the list
  while (end && end->next) {
    middle = middle->next;
    end = end->next->next;
  }

  // at this point, end is null and doesn't matter
  // the first sublist (a) is just the head of the original list
  // the second sublist (b) starts at middle->next, which is done
  // so that the link can be severed between the two sublists
  a = head;
  b = middle->next;

  // sever the link between the two sublists
  middle->next = nullptr;
}

// despite the arguments being passed by copy,
// this merges in-place, which means no new nodes are created
node *merge(node *a, node *b) {
  // create the head of the list to be returned
  // and a pointer that will be used to build it
  node *newHead = getFirstNode(a, b);
  node *curr = newHead;

  // as long as we haven't reached the end of either sublist
  // append the list with the smaller value to the merged list
  // advance the pointer of that sublist
  // and advance curr to the newly added node
  while (a && b) {
    if (a->value <= b->value) {
      curr->next = a;
      a = a->next;
    } else {
      curr->next = b;
      b = b->next;
    }
    // either way, advance curr
    curr = curr->next;
  }

  // at this point, either a or b is empty
  // append the non-empty list to the merged list
  if (a) {
    curr->next = a;
  } else {
    curr->next = b;
  }

  // finally, return the head of the sorted list
  return newHead;
}

node *mergeSort(node *head) {
  // base case: 0 or 1 nodes
  if (head == nullptr) {
    return nullptr;
  } else if (head->next == nullptr) {
    return head;
  }
  // general case : 2 or more nodes

  // initialize pointers for the two sublists
  node *a = nullptr;
  node *b = nullptr;

  // split the list into two sublists
  // after this, head points to the first sublist (a)
  // and shouldn't be used without reassignment
  split(head, a, b);

  // recursively sort each sublist
  a = mergeSort(a);
  b = mergeSort(b);

  // merge the two sorted sublists
  head = merge(a, b);

  return head;
}

// helper function to test mergeSort
void testMergeSort(int arr[], int size, const std::string &header) {
  node *head = nullptr;
  head = arrayToList(arr, size);
  std::cout << header << std::endl;
  printList(head, "Original linked list : ");
  head = mergeSort(head);
  printList(head, "Sorted linked list   : ");
  std::cout << std::endl;
}

int main() {
  int *arr0 = nullptr;
  int arr1[] = {5};
  int arr2[] = {12, 7};
  int arr3[] = {4, 9, 1, 7, 3};
  int arr4[] = {2, 27, 18, 6, 5, 6, 22, 12, 3, 15};

  // test case 1: empty list
  testMergeSort(arr0, 0, "Test Case 1: Empty List");

  // test case 2: single node list
  testMergeSort(arr1, 1, "Test Case 2: Single Node List");

  // test case 3: two node list
  testMergeSort(arr2, 2, "Test Case 3: Two Node List");

  // test case 4: odd number of nodes
  testMergeSort(arr3, 5, "Test Case 4: Odd Number of Nodes");

  // test case 5: even number of nodes
  testMergeSort(arr4, 10, "Test Case 5: Even Number of Nodes");

  return 0;
}