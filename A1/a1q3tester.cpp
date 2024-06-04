/**************************************************************************/
/*                                                                        */
/*   A1 part3 tester file                                                 */
/*                                                                        */
/*   To compile: g++ a1q3tester.cpp timer.cpp -std=c++0x                  */
/*   NOTE: if you are working in windows, change the #define              */
/*   PLATFORM line in timer.h, see comments in that file                  */
/*                                                                        */
/**************************************************************************/

#include "a1q3.h"
#include "timer.h"
#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

bool test1(std::string& error); 
bool test2(std::string& error); 
bool test3(std::string& error); 
bool test4(std::string& error); 
bool test5(std::string& error); 
bool test6(std::string& error);
bool test7(std::string& error);
bool test8(std::string& error);
bool test9(std::string& error);
bool test10(std::string& error);
bool test11(std::string& error);
bool test12(std::string& error);
bool test13(std::string& error);
const int numTests=13;
typedef bool (*TestPtr)(std::string&);
struct Record{
    std::string word_;
    int count_;
    std::string toString() const{ 
        std::string s="{";
        s+= word_;
        s+= ",";
        s+= std::to_string(count_);
        s+= "}";
        return s;
    }
};
ostream& operator<<(ostream& os, const Record rec){
    os << rec.word_;
    return os;
}
bool operator==(const Record& a,const Record& b){
    bool rc=false;
    if(a.word_==b.word_ && a.count_==b.count_){
        rc=true;
    }
    return rc;
}
bool operator!=(const Record& a,const Record& b){
    return !(a==b);
}

template <typename T>
void removeItem(T arr[],int idx,int sz);
template <typename T>
bool checkList(const CacheList<T>& list,const T arr2[],int sz);
template <typename T>
void duplicateArray(T dest[], const T src[],int sz);
template <typename T>
void printLists(const CacheList<T>& list,const T array[],int sz);
template<typename T>
typename CacheList<T>::iterator setIterator(CacheList<T>& list, int idx);
template <typename T>
void addFront(const T& data,T arr[],int sz);
template <typename T>
void addBack(const T& data,T arr[],int sz);
template <typename T>
void add(const T& data,int idx, T arr[],int sz);
template <typename T>
void moveItem(T arr[],int fromIdx, int toIdx, int sz);


int main(void){

    TestPtr runTest[numTests]={test1, test2, test3, test4, test5, 
                               test6, test7, test8, test9, test10,
                               test11,test12,test13
                           };
    std::string testSummary[numTests]={
                            "empty lists, size(), empty(), c/begin(), c/end()",
                            "insert(), size(), empty(), c/begin(), c/end()",
                            "insert(), increment operators pre and postfix",
                            "decrement operators pre and postfix",
                            "return values from increment operators",
                            "return values from decrement operators",
                            "search() function return value",
                            "doing an insertion() after a search()",
                            "erase(it)",
                            "more search() testing",
                            "copy constructor",
                            "copy assignment operator",
                            "moves and large data set and timing run"
                        };

    std::string msg;
    bool result=true;
    int numPassed=0;
    for(int i=0;result && i<numTests;i++){
        result = runTest[i](msg);
        if(!result){
            std::cout << "Test " << i+1 <<" - "<< testSummary[i]<< ": failed." << std::endl;
            std::cout << msg << std::endl;
        }
        else{
            numPassed++;
            std::cout << "Test " << i+1 <<" - "<< testSummary[i]<< ": passed." << std::endl;
        }
    }
    if(numPassed == numTests){
        std::cout << "Congratulations! You have passed testing for A1 part 1" << std::endl;
        return 0;
    }
    else{
        std::cout << "Looks like you still have some work left to do" << std::endl;
        return 1;
    }

}

/* test1: Create an empty list, check size(), empty(), begin(), end() 
   cbegin() and cend()
   functions.  test returns true if passed, false otherwise
*/
bool test1(std::string& error){
    CacheList<Record> theList;
    int result;
    bool rc=true;
    result=theList.size();
    if(result != 0){
        rc=false;
        error = "Error 1a: size() function returned ";
        error += std::to_string(result);
        error += " on an empty list, should return 0." ;        
    }
    if(rc && theList.empty()==false){
        rc=false;
        error = "Error 1b: empty() function returned false on empty list, should return true";
    }
    if(rc && theList.begin() != theList.end()){
        error = "Error 1c: list is empty, begin() and end() should return iterator to same node";
        rc=false;
    }
    if(rc && theList.cbegin() != theList.cend()){
        error = "Error 1d: list is cempty, cbegin() and cend() should return iterator to same node";
        rc=false;
    }
    return rc;
}
/*test2: test insertion and * operators and size(), empty(), begin() and end() are consistent*/
bool test2(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };
    CacheList<Record> theList;


    bool rc=true;
    CacheList<Record>::iterator it1=theList.insert(recs[0]);
   
    if(theList.size() != 1){
        rc=false;
        error = "Error 2a: size() function returned ";
        error += std::to_string(theList.size());
        error += ".  size() should return 1" ;        
    }

    if(rc && theList.empty() == true){
        rc=false;
        error = "Error 2b: empty() function returned true on a non-empty list";
    }

    if(rc && theList.begin() == theList.end()){
        error = "Error 2c: list is not empty, begin() and end() should return iterator to different nodes";
        rc=false;        
    }  

    if(rc && theList.cbegin() == theList.cend()){
        error = "Error 2d: list is not empty, cbegin() and cend() should return iterator to different nodes";
        rc=false;        
    }

    if(rc && *(theList.begin())!= recs[0]){
        error = "Error 2e: first node in list should match record inserted. It does not\n";
        error +="Your data: ";
        error += (*theList.begin()).toString();
        error += "\nCorrect data: ";
        error += recs[0].toString();
        rc=false;  
    }

    if(rc && *(theList.cbegin())!= recs[0]){
        error = "Error 2f: first node in list should match record inserted. It does not\n";
        error +="Your data: ";
        error += (*theList.cbegin()).toString();
        error += "\nCorrect data: ";
        error += recs[0].toString();
        rc=false;  
    }

    if(rc && it1 != theList.begin()){
        error = "Error 2g: return value from insert() does not point to correct node\n";
        rc=false;  
    }

    return rc;
}

/*test3: further test insertion() function and ++ operators*/
bool test3(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };

    CacheList<Record> theList;
    bool rc=true;
    int listSize;
    CacheList<Record>::iterator it;

    for(int i=0;rc && i<10;i++){
        it=theList.insert(recs[i]);
        if(*it != recs[i]){
            error = "Error 3a: Incorrect return value from insert().\n";
            error += "returned node needs to contain inserted value";
            rc=false;
        }
    }
    it=theList.begin();
    for(int i=9; rc && i>=0;i--){
        if(*it != recs[i]){
            error = "Error 3b: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or iterator::operator++(int)";
            rc=false;
        }
        it++;
    }
    
    for(int i=10;rc && i<20;i++){
        it=theList.insert(recs[i]);
        if(*it != recs[i]){
            error = "Error 3c: Incorrect return value from insert().\n";
            error += "returned node needs to contain inserted value";
            rc=false;
        }
    }


    it=theList.begin();
    for(int i=19;rc && i>=0;i--){
        if(*it != recs[i]){
            error = "Error 3d: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or iterator::operator++(int)";
            rc=false;
        }
        it++;
    }

    CacheList<Record>::const_iterator it2= theList.cbegin();
    for(int i=19;rc && i>=0;i--){
        if(*it2 != recs[i]){
            error = "Error 3e: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it2).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or const_iterator::operator++(int)";
            rc=false;
        }
        it2++;
    }

    it= theList.begin();
    for(int i=19;rc && i>=0;i--){
        if(*it != recs[i]){
            error = "Error 3f: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or iterator::operator++()";
            rc=false;
        }
        ++it;
    }

    it2= theList.cbegin();
    for(int i=19;rc && i>=0;i--){
        if(*it2 != recs[i]){
            error = "Error 3g: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it2).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or const_iterator::operator++(int)";
            rc=false;
        }
        ++it2;
    }

    return rc;
}


/*test 4: test decrement (--) operators*/
bool test4(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };
    CacheList<Record> theList;
    CacheList<Record>::iterator it;
    bool rc=true;
    int listSize;
    for(int i=0;rc && i<20;i++){
        it=theList.insert(recs[i]);
        if(*it != recs[i]){
            error = "Error 4a: Incorrect return value from insert().\n";
            error += "returned node needs to contain inserted value";
            rc=false;
        }

    }
    it = theList.end();
    for(int i=0;rc && i<20;i++){
        it--;
        if(*it != recs[i]){
            error = "Error 4b: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or iterator::operator--(int)";
            rc=false;
        }
    }

    CacheList<Record>::const_iterator it2 = theList.cend();
    for(int i=0;rc && i<20;i++){
        it2--;
        if(*it2 != recs[i]){
            error = "Error 4c: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it2).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or const_iterator::operator--(int)";
            rc=false;
        }

    }

    it = theList.end();
    for(int i=0;rc && i<20;i++){
        --it;
        if(*it != recs[i]){
            error = "Error 4d: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or iterator::operator--()";
            rc=false;
        }

    }

    it2 = theList.cend();
    for(int i=0;rc && i<20;i++){
        --it2;
        if(*it2 != recs[i]){
            error = "Error 4e: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it2).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or const_iterator::operator--(int)";
            rc=false;
        }

    }

    return rc;

}
/*test 5: Test return values of increment operators*/
bool test5(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };

    CacheList<Record> theList;
    bool rc=true;
    int listSize;
    for(int i=19;rc && i>=0;i--){
        theList.insert(recs[i]);
    }
    Record rec;
    CacheList<Record>::iterator it= theList.begin();
    for(int i=0;rc && i<20;i++){
        if((rec = *(it++)) != recs[i]){
            error = "Error 5a: data in node at referred to by *(it++) is not correct\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (rec).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably return of postfix iterator";
            rc=false;
        }
    }
    CacheList<Record>::const_iterator it2= theList.cbegin();
    for(int i=0;rc && i<20;i++){
        if((rec = *(it2++)) != recs[i]){
            error = "Error 5b: data in node at referred to by *(it++) is not correct\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (rec).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably return of postfix const_iterator";
            rc=false;
        }
    }



    it = theList.begin();

    for(int i=0;rc && i<20;i++){
        if(i<19 && (rec = *(++it)) != recs[i+1] ){
            error = "Error 5c: data in node at referred to by *(++it) is not correct\n  Data at node # ";
            error += std::to_string(i+2);
            error += "(numbered from 1):";
            error += rec.toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably return of prefix iterator";
            rc=false;
  
        }
    }
    it2= theList.cbegin();
    for(int i=0;rc && i<20;i++){
        if(i<19 && (rec = *(++it2)) != recs[i+1] ){
            error = "Error 5d: data in node at referred to by *(++it) is not correct\n  Data at node # ";
            error += std::to_string(i+2);
            error += "(numbered from 1):";
            error += rec.toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably return of prefix const_iterator";
            rc=false;

        }
    }

    return rc;
}

/*Test 6: Test return values of decrement operators*/
bool test6(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };

    CacheList<Record> theList;
    bool rc=true;
    int listSize;
    Record mirror[20];
    for(int i=0;i<20;i++){
        theList.insert(recs[i]);
        mirror[19-i]=recs[i];
    }
    CacheList<Record>::iterator it= theList.end();
    it--;
    Record rec;
    for(int i=19;rc && i>0;i--){
        if((rec = *(it--)) != mirror[i]){
            error = "Error 6a: data in node at referred to by *(it--) is not correct\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += rec.toString();
            error += "The correct data is";
            error += mirror[i].toString();
            error += "\nbug probably return of postfix iterator";
            rc=false;
        }
    }
    CacheList<Record>::const_iterator it2= theList.cend();
    it2--;
    for(int i=19;rc && i>0;i--){
        if((rec = *(it2--)) != mirror[i]){
            error = "Error 6b: data in node at referred to by *(it--) is not correct\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += rec.toString();
            error += "The correct data is";
            error += mirror[i].toString();
            error += "\nbug probably return of postfix const_iterator";
            rc=false;
        }
    }


    it = theList.end();

    for(int i=19;rc && i>0;i--){
        if((rec = *(--it)) != mirror[i] ){
            error = "Error 6c: data in node at referred to by *(++it) is not correct\n  Data at node # ";
            error += std::to_string(i+2);
            error += "(numbered from 1):";
            error += rec.toString();
            error += "The correct data is";
            error += mirror[i].toString();
            error += "\nbug probably return of prefix iterator";
            rc=false;
  
        }
    }
    it2= theList.cend();
    for(int i=19;rc && i>=0;i--){
        if((rec = *(--it2)) != mirror[i] ){
            error = "Error 6d: data in node at referred to by *(++it) is not correct\n  Data at node # ";
            error += std::to_string(i+2);
            error += "(numbered from 1):";
            error += rec.toString();
            error += "The correct data is";
            error += mirror[i].toString();
            error += "\nbug probably return of prefix iterator";
            rc=false;

        }
    }

    return rc;

}

/*Test 7: Test search()*/
bool test7(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };

   CacheList<Record> theList;
   CacheList<Record>::iterator result;
   CacheList<Record>::iterator it;
    bool rc=true;
    int listSize;
    Record mirror[20];
    for(int i=0;rc && i<15;i++){
        theList.insert(recs[i]);
        mirror[14-i]=recs[i];
    }
    for(int i=0;rc && i<15;i++){
        result=theList.search(mirror[i]);
        if(result == theList.end()){
            rc=false;
            error = "Error 7a: item that should have been in the linked list was not found\n";
            error += "item being searched for: ";
            error += mirror[i].toString();
        }
        else if(*result != mirror[i]){
            rc=false;
            error = "Error 7b: item found was not the one being searched for\n";
            error += "item found: ";
            error += (*result).toString();
            error += "item being searched for: ";
            error += mirror[i].toString();
        }
        moveItem(mirror,i,0,15);
    }
    it = theList.begin();
    for(int i=0;i<15;i++){
        if(*it != mirror[i]){
            rc=false;
            error = "Error 7c: the list was not properly adjusted during search";
        }
        it++;
    }
    for(int i=15;rc && i<20;i++){
        result=theList.search(recs[i]);
        if(result != theList.end()){
            rc=false;
            error = "Error 7d: searching for an item that should not be in the list resulted in something that wasn't end() \n";
            error += "item being searched for: ";
            error += recs[i].toString();
        }        
    }
    return rc;
}

/*Test 8: Test proper insertion behaviour with different access*/
bool test8(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };

   CacheList<Record> theList;
   CacheList<Record>::iterator result;
   CacheList<Record>::iterator it;
    bool rc=true;
    int listSize;
    Record mirror[20];
    for(int i=0;rc && i<15;i++){
        theList.insert(recs[i]);
        mirror[14-i]=recs[i];
    }
    theList.search(recs[0]);
    moveItem(mirror,14,0,15);
    if(theList.size()!= 15){
        rc=false;
        error = "Error 8a: size is not correct after search() operation\n";
    }
    it = theList.begin();
    for(int i=0;rc && i<15;i++){
        if(*it != mirror[i]){
            rc=false;
            error = "Error 8b: adjustment of list was not correctly done after performing search()\n";
        }
        it++;
    }
    theList.insert(recs[15]);
    add(recs[15],1,mirror,15);
    it=theList.begin();
    if(rc && theList.size()!= 16){
        rc=false;
        error = "Error 8c: size is not correct when inserting after a search()\n";
    }
    for(int i=0;rc && i<16;i++){
        if(*it != mirror[i]){
            rc=false;
            error = "Error 8d: calling insert() after doing a search() does not correctly place object\n";
        }
        it++;
    }
    for(int i=1;rc && i < 3;i++){
        theList.search(mirror[i]);
        moveItem(mirror,i,0,16);
    }
    for(int i=0;rc && i<2;i++){
        for(int i=0;i < 3;i++){
            theList.search(mirror[i]);
            moveItem(mirror,i,0,16);
        }
    }
    for(int i=0;rc && i<5;i++){
        theList.search(mirror[3+i]);
        moveItem(mirror,3+i,3,16);
    }

    theList.insert(recs[16]);

    add(recs[16],8,mirror,16);
    it=theList.begin();
    if(rc && theList.size()!= 17){
        rc=false;
        error = "Error 8e: size is not correct when inserting after a search()\n";
    }
    for(int i=0;rc && i<17;i++){
        if(*it != mirror[i]){
            rc=false;
            error = "Error 8f: calling insert() after doing a search() does not correctly place object\n";
        }
        it++;
    }

    return rc;
}



/*Test 9: Test erase(it)*/
bool test9(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };

    CacheList<Record> theList;
    CacheList<Record>::iterator result;
    CacheList<Record>::iterator it;
    Record mirror[20];
    bool rc=true;

    for(int i=0;i<20;i++){
        theList.insert(recs[i]);
        mirror[19-i]=recs[i];
    }
    for(int i=19; i>= 17;i-- ){
        it=setIterator(theList,i);
        result=theList.erase(it);
        if(result!=theList.end()){
            rc=false;
            error = "Error 9a: when last item in list is erased, return value should be end()";
        }
        else{
            if(theList.search(mirror[i]) != theList.end()){
                rc=false;
                error = "Error 9b: when last item in list is erased, item should not be found in list";
            }
            else if(theList.size() != i){
                rc=false;
                error = "Error 9c: size() is not correct after erase(it) of last node\n your function returned: ";
                error += std::to_string(theList.size());
                error += ".  It should return: ";
                error += std::to_string(i);

            }
        }
    }
    CacheList<Record>::const_iterator it2=theList.cbegin();
    for(int i=0;rc && i<17;i++){
        if(*it2 !=mirror[i]){
            rc=false;
            error = "Error 9d: a record that was not erased is no longer in list";
        }
        it2++;
    }
    if(rc && it2!=theList.cend()){
        rc=false;
        error = "Error 9e: the list has more records than expected after erasing from end of list";
    }
    for(int i=0;rc && i< 3 ;i++ ){
        it=theList.begin();
        result=theList.erase(it);
        if(result != theList.begin()){
            rc=false;
            error = "Error 9f: when first item in list is erased, return value should be begin()";
        }
        else{
            if(theList.search(mirror[0]) != theList.end()){
                rc=false;
                error = "Error 9g: when first item in list is erased, item should not be found in list";
            }
            else if(theList.size() != 16-i){
                rc=false;
                error = "Error 9h: size() is not correct after erase(it) of first node\n Your function returned: ";
                error += std::to_string(theList.size());
                error += ".  It should return:";
                error += std::to_string(16-i);
            }
        }
        removeItem(mirror,0,17-i);
    }

    it2=theList.cbegin();
    for(int i=0;rc && i<14;i++){
        if(*it2 !=mirror[i]){
            rc=false;
            error = "Error 9i: a record that was not erased is no longer in list";
        }
        it2++;
    }
    if(rc && it2!=theList.cend()){
        rc=false;
        error = "Error 9j: the list has more records than expected after erasing from end of list";
    }

    int listSize=14;
    CacheList<Record>::iterator next;
    for(int i=1; i< listSize ;i++ ){
        next=setIterator(theList,i);
        result=theList.erase(next++);
        if(result != next){
            rc=false;
            error = "Error 9k: when erasing a node, return value is not the next node in list";
        }
        else{
            if(theList.search(mirror[i]) != theList.end()){
                rc=false;
                error = "Error 9l: when a node in list is erased, item should not be found in list";
            }
            else if(theList.size() != listSize-1){
                rc=false;
                error = "Error 9m: size() is not correct after erase(it) of first node\n Your function returned: ";
                error += std::to_string(theList.size());
                error += ".  It should return:";
                error += std::to_string(16-i);

            }
        }
        removeItem(mirror,i,listSize);
        listSize--;
    }
    it2=theList.cbegin();
    for(int i=0;rc && i<listSize;i++){
        if(*it2 !=mirror[i]){
            rc=false;
            error = "Error 9n: a record that was not erased is no longer in list";
        }
        it2++;
    }
    if(rc && it2!=theList.cend()){
        rc=false;
        error = "Error 9o: the list has more records than expected after erasing from end of list";
    }


    return rc;

}

/*Test 10: Test search some more*/
bool test10(std::string& error){
    const int cap=10000;
    const int numSearches=200;
    Record recs[20]={
        {"the",1},
        {"quick",2},
        {"brown",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"tea",20}
    };
    //used for adjusting list for searching test
    int searchParams[30][2]={
        {19,0},
        {19,0},
        {19,0},
        {19,0},
        {19,0},
        {19,0},
        {19,0},
        {0,0},
        {1,0},
        {2,0},

        {3,0},
        {4,0},
        {5,0},
        {8,6},
        {9,6},
        {10,6},
        {0,0},
        {0,0},
        {0,0},
        {4,1},
        
        {1,1},
        {2,2},
        {9,3},
        {19,7},
        {7,3},
        {3,2},
        {2,1},
        {2,0},
        {2,0},
        {18,8}

    };
    CacheList<Record> theList;
    CacheList<Record>::iterator result;
    CacheList<Record>::iterator it;
    Record mirror[20];
    bool rc=true;

    for(int i=0;i<20;i++){
        theList.insert(recs[i]);
        mirror[19-i]=recs[i];
    }


    for(int i=0;i<20;i++){
        CacheList<Record>::iterator it = theList.search(mirror[i]);
        moveItem(mirror,i,0,20);
        if(it == theList.end() || *it != mirror[0]){
            rc =false;
            cout << "Error 10a: Bug in search, returned iterator returned does not point at correct node" << endl;
        }
        if(!checkList(theList,mirror,20)){
            rc  = false;
            cout << "Error 10b: Bug in search(), your list was not properly adjusted" << endl;
        }
    }
    for(int i=0;i<30;i++){
        CacheList<Record>::iterator it = theList.search(mirror[searchParams[i][0]]);
        moveItem(mirror,searchParams[i][0],searchParams[i][1],20);
        if(it == theList.end() || *it != mirror[searchParams[i][1]]){
            rc =false;
            cout << "Error 10c: Bug in search, returned iterator returned does not point at correct node" << endl;
        }
        if(!checkList(theList,mirror,20)){
            rc  = false;
            cout << i << endl;
            cout << "Error 10d: Bug in search(), your list was not properly adjusted" << endl;
            cout << "search key was: " << mirror[searchParams[i][1]] << endl;
        }            

    }
    return rc;
}



/*Test 11: Test copy constructor Operator*/
bool test11(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown ",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };

    CacheList<Record> theList;
    CacheList<Record>::iterator origIt;
    CacheList<Record>::iterator copyIt;
    bool rc=true;

    for(int i=0;rc && i<20;i++){
        theList.insert(recs[i]);
    }

    CacheList<Record> copy=theList;

    if(copy.size() != theList.size()){
        rc=false;
        error = "Error 11a: list created with copy constructor does not properly copy the size";
    }
    if(rc && copy.empty()){
        rc=false;
        error = "Error 11b: list created with copy constructor is empty()";
    }
    origIt=theList.begin();
    copyIt=copy.begin();
    while(rc && origIt!=theList.end()){
        if(copyIt == copy.end()){
            rc=false;
            error = "Error 11c: duplicate list has less nodes than original";            
        }
        if(rc && *origIt != *copyIt){
            rc=false;
            error = "Error 11d: duplicate list does not have same data as original";            
        }
        if(rc && &(*origIt) == &(*copyIt)){
            rc=false;
            error = "Error 11e: deep copy does not appear to have been made";            
        }
        origIt++;
        copyIt++;
    }
    if(rc && copyIt!=copy.end()){
        rc=false;
        error = "Error 11f: duplicate list appears to have more nodes than original";            
    }

    return rc;
}


/*Test 12: Test copy assignment operator*/
bool test12(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown ",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };

    CacheList<Record> theList;
    CacheList<Record>::iterator origIt;
    CacheList<Record>::iterator copyIt;
    CacheList<Record> copy1;
    CacheList<Record> copy2;
    Record mirror1[20];
    Record mirror2[20];
    bool rc=true;
    int i;
    for(i=0;i<20;i++){
        theList.insert(recs[i]);
        copy1.insert(recs[i]);
        mirror1[19-i] = recs[i];
    }
    for(i=5;i<15;i++){
        copy2.insert(recs[i]);
        mirror2[14-i] = recs[i];
    }

    copy1=copy2;

    if(copy1.size() != copy2.size()){
        rc=false;
        error = "Error 12a: list assigned to by copy assignment does not properly copy the size";
    }
    if(rc && copy1.empty()){
        rc=false;
        error = "Error 12b: list assigned to by copy assignment is empty()";
    }
    origIt=copy2.begin();
    copyIt=copy1.begin();
    i=0;
    while(rc && origIt!=copy2.end()){
        if(copyIt == copy1.end()){
            rc=false;
            error = "Error 12c: duplicate list has less nodes than original";            
        }
        if(rc && *origIt != *copyIt){
            rc=false;
            error = "Error 12d: duplicate list does not have same data as original";            
        }
        if(rc && *copyIt != mirror2[i++]){
            rc=false;
            error = "Error 12e: duplicate list does not match record added to list";  
        }
        if(rc && &(*origIt) == &(*copyIt)){
            rc=false;
            error = "Error 12f: deep copy does not appear to have been made";  
        }
        origIt++;
        copyIt++;
    }
    if(rc && copyIt!=copy1.end()){
        rc=false;
        error = "Error 12g: duplicate list appears to have more nodes than original";            
    }

    copy1 = copy2 = theList;

    if(copy1.size() != copy2.size() || copy1.size() !=theList.size()){
        rc=false;
        error = "Error 12h: list assigned to by copy assignment does not properly copy the size";
    }
    if(rc && (copy1.empty() || copy2.empty())){
        rc=false;
        error = "Error 12i: list assigned to by copy assignment is empty()";
    }
    origIt=theList.begin();
    copyIt=copy1.begin();
    while(rc && origIt!=theList.end()){
        if(copyIt == copy1.end()){
            rc=false;
            error = "Error 12j: duplicate list has less nodes than original";            
        }
        if(rc && *origIt != *copyIt){
            rc=false;
            error = "Error 12k: duplicate list does not have same data as original";            
        }
        if(rc && &(*origIt) == &(*copyIt)){
            rc=false;
            error = "Error 12l: deep copy does not appear to have been made";            
        }
        origIt++;
        copyIt++;
    }
    if(rc && copyIt!=copy1.end()){
        rc=false;
        error = "Error 12m: duplicate list appears to have more nodes than original";            
    }
    origIt=theList.begin();
    copyIt=copy2.begin();
    while(rc && origIt!=theList.end()){
        if(copyIt == copy2.end()){
            rc=false;
            error = "Error 12n: duplicate list has less nodes than original";            
        }
        if(rc && *origIt != *copyIt){
            rc=false;
            error = "Error 12o: duplicate list does not have same data as original";            
        }
        if(rc && &(*origIt) == &(*copyIt)){
            rc=false;
            error = "Error 12p: deep copy does not appear to have been made";            
        }
        origIt++;
        copyIt++;
    }
    if(rc && copyIt!=copy2.end()){
        rc=false;
        error = "Error 12q: duplicate list appears to have more nodes than original";            
    }

    return rc;   
}

/*Test 13: Timing runs on large data sets*/
bool test13(std::string& error){
    int listSize=20000;
    Timer t;
    bool rc=true;
    int* array=new int[listSize];
    for(int i=0;i<listSize;i++){
        array[i]=i+1;
    }

    CacheList<int> theList;
    CacheList<int> copy2;
    for(int i=listSize-1;i>=0;i--){
        theList.insert(array[i]);
        copy2.insert(array[i]);

    }

    CacheList<int>::const_iterator it;
    it=theList.cbegin();
    for(int i=0;rc && i<listSize;i++){
        if(*it !=array[i]){
            rc=false;
            error = "Error 13a: insertion error on large data set\n";
            error += "Your record: ";
            error += std::to_string(*it);
            error += "correct data ";
            error += std::to_string(array[i]);

        }
        it++;
    }
    t.reset();
    t.start();
    CacheList<int> copy1 = theList;
    t.stop();
    std::cout << "copy constructor on list with " << listSize << " nodes: " << t.currtime() << std::endl;
    it = theList.cbegin();
    for(int i=0;rc && i<listSize;i++){
        if(*it !=array[i]){
            rc=false;
            error = "Error 13b: copy constructor error on large data set\n";
            error += "Your record: ";
            error += std::to_string(*it);
            error += "correct data ";
            error += std::to_string(array[i]);
        }
        it++;
    }
    t.reset();
    t.start();
    copy2 = theList;
    t.stop();
    std::cout << "assignment operator on list with " << listSize << " nodes: " << t.currtime() << std::endl;
    it = theList.cbegin();
    for(int i=0;rc && i<listSize;i++){
        if(*it !=array[i]){
            rc=false;
            error = "Error 13c: assignment operator error on large data set\n";
            error += "Your record: ";
            error += std::to_string(*it);
            error += "correct data ";
            error += std::to_string(array[i]);
        }
        it++;
    }
    t.reset();
    t.start();
    CacheList<int> copy3=std::move(theList);
    t.stop();
    std::cout << "move constructor on list with " << listSize << " nodes: " << t.currtime() << std::endl;
    it = copy3.cbegin();
    for(int i=0;rc && i<listSize;i++){
        if(*it !=array[i]){
            rc=false;
            error = "Error 13d: move constructor error on large data set\n";
            error += "Your record: ";
            error += std::to_string(*it);
            error += "correct data ";
            error += std::to_string(array[i]);
        }
        it++;
    }
    t.reset();
    t.start();
    copy2=std::move(copy3);
    copy1=std::move(copy2);
    t.stop();
    std::cout << "move assignment on list with " << listSize << " nodes: " << t.currtime() << std::endl;
    it = copy1.cbegin();
    for(int i=0;rc && i<listSize;i++){
        if(*it !=array[i]){
            rc=false;
            error = "Error 13e: move assignment error on large data set\n";
            error += "Your record: ";
            error += std::to_string(*it);
            error += "correct data ";
            error += std::to_string(array[i]);
        }
        it++;
    }


    delete [] array;
    return rc;
}



template <typename T>
void addFront(const T& data,T arr[],int sz){
    add(data,0,arr,sz);
}
template <typename T>
void addBack(const T& data,T arr[],int sz){
    arr[sz]=data;
}
template <typename T>
void add(const T& data,int idx, T arr[],int sz){
    for(int i=sz-1;i>=idx;i--){
        arr[i+1]=arr[i];
    }
    arr[idx]=data;
}
template <typename T>
void removeItem(T arr[],int idx,int sz){
    for(int i=idx;i<sz-1;i++){
        arr[i]=arr[i+1];
    }
}
template <typename T>
bool checkList(const CacheList<T>& list,const T array[],int sz){
    bool rc=true;
    if(sz != list.size()){
        rc=false;
    }
    else{
        auto it=list.cbegin();
        int i;
        for(i=0;i<sz && it!=list.cend() && rc;i++,it++){
            if(*it != array[i]){
                rc=false;
            }
        }
        if(it!=list.cend() || i < sz){
            rc=false;
        }
    }
    return rc;
}

template <typename T>
void duplicateArray(T dest[], const T src[],int sz){
    for(int i=0;i<sz;i++){
        dest[i]=src[i];
    }
}

template <typename T>
void printLists(const CacheList<T>& list,const T array[],int sz){
    auto it=list.cbegin();
    int i;
    for(i=0;i<sz && it!=list.cend();i++,it++){
        cout << "correct item: " ;
        cout.width(25);
        cout.setf(ios::left);
        cout << array[i] << "  your list: " << *it << endl;
    }
    for( ;i<sz;i++){
        cout << "correct item: ";
        cout.width(20);
        cout.setf(ios::left);
        cout << array[i] << "  your list: <past end of list>" <<  endl;
    }	
    for( ;it!=list.cend();it++){
        cout << "correct item: ";
        cout.width(20);
        cout.setf(ios::left);
        cout << "<past end of list>"  << "  your list: " <<  *it << endl;
    }
    cout << endl;

}
//returns iterator to the idx'th node in the list
template <typename T>
typename CacheList<T>::iterator setIterator(CacheList<T>& list, int idx){
    typename CacheList<T>::iterator it=list.begin();
    for(int i=0;i<idx;i++){
        it++;
    }
    return it;
}


template <typename T>
void moveItem(T arr[],int fromIdx, int toIdx, int sz){
    T tmp=arr[fromIdx];
    removeItem(arr,fromIdx,sz);
    add(tmp,toIdx,arr,sz-1);

}




