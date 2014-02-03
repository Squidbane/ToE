#include <iostream>
#include <map>
#include <vector>
using namespace std;

string uglifyThis(string pretty) {
    string ugly = pretty;
    int colonLocation = ugly.find(':');
    //basic_string<char>::iterator endLocation = ugly.end();
    //basic_string<char>::iterator beginLocation = ugly.begin();
    int endLocation = ugly.length();
    //cout << ugly.length()-colonLocation <<endl;
    for(unsigned int i=0; i < (endLocation - colonLocation); i++){
        ugly.insert(ugly.begin()+colonLocation+1, 'x');
        //cout<<ugly<<endl;
    }
    //cout << colonLocation<<endl;
    for(int i=0; i < (colonLocation); i++){
        ugly.insert(ugly.begin(), 'x');
    }
    return ugly;
}

int main()
{
    uglifyThis("123450:1234");
//
//    myMap["january"] = 1;
//    myMap["february"] = 2;
//    myMap["march"] = 3;
//    myMap["april"] = 4;
//    myMap["may"] = 5;
//    myMap["june"] = 6;
//    myMap["july"] = 7;
//    myMap["august"] = 8;
//    myMap["september"] = 9;
//    myMap["october"] = 10;
//    myMap["november"] = 11;
//    myMap["december"] = 12;
//    myMap["January"] = 1;
//    myMap["February"] = 2;
//    myMap["March"] = 3;
//    myMap["April"] = 4;
//    myMap["May"] = 5;
//    myMap["June"] = 6;
//    myMap["July"] = 7;
//    myMap["August"] = 8;
//    myMap["September"] = 9;
//    myMap["October"] = 10;
//    myMap["November"] = 11;
//    myMap["December"] = 12;
//    myMap["1 :5"] = 1;
//    myMap["1 :4"] = 2;
//    myMap["20 :3"] = 3;
//    myMap["1 :1"] = 4;
//    myMap["1 :10"] = 5;
//    myMap["100 :10001"] = 6;
//    myMap["1 :2"] = 7;
//    myMap["2 :1"] = 8;
//    myMap["2 :1"] = 9;
//    myMap["1000 :100"] = 10;
//    myMap["10 :10"] = 11;
//    myMap["22 : 2"] = 12;

    map<string,int> myMap;
    vector<string> myVector;
    vector<string>::iterator myIterator;
    myVector.push_back("1:5");
    myVector.push_back("1:4");
    myVector.push_back("20:3");
    myVector.push_back("1:1");
    myVector.push_back("1:10");
    myVector.push_back("100:10001");
    myVector.push_back("100:10000");
    myVector.push_back("100:100");
    myVector.push_back("100:1000000");
    myVector.push_back("100:10000000");
    myVector.push_back("1:2");
    myVector.push_back("2:1");
    myVector.push_back("10:10");
    myVector.push_back("22:2");
    int i = 0;
    string temp;
    for (myIterator = myVector.begin(); myIterator != myVector.end(); myIterator++){
        i++;
        temp = myIterator->data();
        temp = uglifyThis(temp);
        myMap[temp] = i;
        //cout << myIterator->first << "\t" << myIterator->second << endl;
    }
    map<string,int>::iterator iteratorTwo;
    for (iteratorTwo = myMap.begin(); iteratorTwo != myMap.end(); iteratorTwo++){
        cout << iteratorTwo->first << "\t\t" << iteratorTwo->second << endl;
    }

    return 0;
}