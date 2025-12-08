#include <iostream>
using namespace std;


void MyMathFunction(int a, int r, int counter) {
   int val;
   val = a * r;
   cout << val << " " <<  endl;
   if (counter > 4)   {
      cout << "End";
   }
   else {
      MyMathFunction(val, r, counter + 1);
   }
}


int main () {
   int mainNum1 = 1;
   int mainNum2 = 2;
   int ctr = 0;
   MyMathFunction(mainNum1, mainNum2, ctr);
   
   return 0;
}