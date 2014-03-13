// STL version
#include <iostream>
#include <map>
int main(){
    long long sum = 0;
    std::map<int,int> myMap;
    std::map<int,int>::iterator it;
    int toTest;
    while(std::cin >>toTest){
        it = myMap.find(toTest);
        if(it == myMap.end()){
            myMap[toTest] = 1;
        } else {
            it->second++;
        }
    }
    for(it = myMap.begin(); it !=myMap.end();it++){
        if (it->second == 1) {
            int temp = it->first;
            sum += temp;
        }
    }
    std::cout << "Sum is "<< sum << std::endl;
    return 0;
    }