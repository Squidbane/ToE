#include <iostream>
using namespace std;
int returnValue, n;
int fact(int n) {
  int i = 0;
  int product = 1;
  while (i < n) {
    i++;
    product = product * i;
  }
  returnValue = product;
  return returnValue;
}
int main(){
  cout << "Give me a relatively small positive integer ";
  cin >> n;
  fact(n);
  cout << "The factorial of " << n << " is " << returnValue << endl;
  return 0;
}
