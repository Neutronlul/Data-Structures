#include <iostream>
using namespace std;

int countSwaps = 0;

void printArray(int a[], int size, int end) {
    countSwaps++;
    if (countSwaps == end) {
        cout << "Swapped " << countSwaps << " times: " << endl;
        for (int i = 0; i < size; i++) {
            cout << a[i] << ",";
        }
        cout << endl;
    }
}

int hoare(int a[], int first, int last, int size, int stoppingPoint) {
    int pivot = first;
    int lower = first + 1;
    int upper = last;
    while (true) {
        while (lower <= upper && a[upper] >= a[pivot]) {
            upper--;
        }
        while (lower <= upper && a[lower] <= a[pivot]) {
            lower++;
        }
        if (lower > upper) {
            break;
        }
        swap(a[lower], a[upper]);
        printArray(a, size, stoppingPoint);
        
    }
    swap(a[upper], a[pivot]);
    printArray(a, size, stoppingPoint);
    return upper;
}

int lumuto(int A[], int lo, int hi, int size, int stoppingPoint) {
    int pivot = hi;
    int i = lo;
    for (int j = lo; j < pivot; j++) {
        if (A[j] <= A[pivot]) {
            swap(A[i], A[j]);
            printArray(A, size, stoppingPoint);
            i++;
        }
    }
    swap(A[i], A[pivot]);
    printArray(A, size, stoppingPoint);
    return i;
}
int main() {
    // 1.
    cout << "Using Hoare's algorithm, what would the array look like immediately after the 3rd swap" << endl;
    cout << "5,7,6,2,9,3" << endl;
    int arr1[] = {5,7,6,2,9,3};
    hoare(arr1, 0, sizeof(arr1) / sizeof(arr1[0]) - 1, sizeof(arr1) / sizeof(arr1[0]), 3);
    cout << endl;

    // 2.
    cout << "Using Lumuto's algorithm, what would the array look like immediately after the 3rd swap" << endl;
    cout << "3,3,6,2,9,3" << endl;
    int arr2[] = {3,3,6,2,9,3};
    countSwaps = 0;
    lumuto(arr2, 0, sizeof(arr2) / sizeof(arr2[0]) - 1, sizeof(arr2) / sizeof(arr2[0]), 3);
    cout << endl;

    // 3.
    cout << "Using Hoare's algorithm, what would the array look like immediately after the 4th swap" << endl;
    cout << "5,7,6,2,9,3" << endl;
    int arr3[] = {5,7,6,2,9,3};
    countSwaps = 0;
    hoare(arr3, 0, sizeof(arr3) / sizeof(arr3[0]) - 1, sizeof(arr3) / sizeof(arr3[0]), 4);
    hoare(arr3, 0, sizeof(arr3) / sizeof(arr3[0]) - 1, sizeof(arr3) / sizeof(arr3[0]), 4);
    cout << endl;

    // 4.
    cout << "Using Lumuto's algorithm, what would the array look like immediately after the 1st swap" << endl;
    cout << "5,7,6,2,9,3" << endl;
    int arr4[] = {5,7,6,2,9,3};
    countSwaps = 0;
    lumuto(arr4, 0, sizeof(arr4) / sizeof(arr4[0]) - 1, sizeof(arr4) / sizeof(arr4[0]), 1);
    cout << endl;

    // 5.
    cout << "Using Hoare's algorithm, what would the array look like immediately after the 2nd swap" << endl;
    cout << "5,7,6,2,9,3" << endl;
    int arr5[] = {5,7,6,2,9,3};
    countSwaps = 0;
    hoare(arr5, 0, sizeof(arr5) / sizeof(arr5[0]) - 1, sizeof(arr5) / sizeof(arr5[0]), 2);
    cout << endl;

    // 6.
    cout << "Given the mergesort algorithm and the following array:5,7,6,2,9,3, what would be the value of low and high that is passed in to the mergesort function, respectively, when the mergesort function is  called the 3rd time" << endl;
    int arr6[] = {5,7,6,2,9,3};
    
    // 7.
    cout << "Given the quicksort algorithm and the following array: array:5,7,6,2,9,3, what would be the value of low and high, respectively, when the quicksort function is executed the 3rd time using the above Hoare's algorithm" << endl;
    int arr7[] = {5,7,6,2,9,3};
    

    return 0;
}