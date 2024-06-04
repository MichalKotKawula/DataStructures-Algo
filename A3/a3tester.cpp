/**********************************************************/
/*                                                        */
/*   Written by: Catherine Leung                          */
/*   Version 1.0                                          */
/*                                                        */
/*   To compile this program:                             */
/*     c++ a3tester.cpp a3.cpp timer.cpp -std=c++0x       */
/*                                                        */
/*                                                        */
/**********************************************************/

#include <cctype>
#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>

using namespace std;
#include "a3.h"
#include "timer.h"


bool test1(std::string key[], int max, std::string& error); 
bool test2(std::string key[], int max, std::string& error); 
bool test3(std::string key[], int max, std::string& error); 
bool test4(std::string key[], int max, std::string& error); 
bool test5(std::string key[], int max, std::string& error); 

void toLower(char* word);
typedef bool (*TestPtr)(std::string [],  int , std::string& );

const int numWords=234368;
const int numInitial=10000;
const int numTests = 5;


int main(int argc, char* argv[]){
    Timer createTimer;
    FILE* fp=fopen("a3dictionary.txt","r");
    char curr[1000];              //used to read in words from text file
    std::string* keys = new std::string[numWords];
    for(int i=0;i<numWords;i++){
        fscanf(fp,"%s\n",curr);
        toLower(curr);
        keys[i].append(curr);
    }
    TestPtr runTest[numTests]={test1, test2, test3, test4, test5};


    std::string msg;
    bool result=true;
    int numPassed=0;
    Timer t;
    double times[numTests];

    for(int i=0;result && i<numTests;i++){
        t.reset();
        t.start();
        result = runTest[i](keys,numWords,msg);
        t.stop();
        times[i]=t.currtime();
        if(!result){
            std::cout << msg << std::endl;
        }
        else{
            numPassed++;
            std::cout << "Test " << i+1 << " passed!" << std::endl;
        }
    }
    if(numPassed == numTests){
        std::cout << std::endl;
        std::cout << "  Test Number  |    Time     " << std::endl;
        std::cout << "---------------|-------------" << std::endl;

        for(int i=0;i<numTests;i++){
            std::cout << "   Test ";
            std::cout.width(2);
            std::cout << i+1;
            std::cout << "     |  " << times[i] << std::endl;
        }
        std::cout << std::endl;
        std::cout << "Congratulations! You have passed testing for A2 part 3" << std::endl;
        return 0;
    }
    else{
        std::cout << std::endl;
        std::cout << "Looks like you still have some work left to do" << std::endl;
        return 1;
    }

}



/*test Trie constructor and search*/
bool test1(std::string key[], int max, std::string& error){
    std::string words[8] = {"yellow", "yell", "yeti", "yes","red","redraw","ran","y"};
    std::string partials[6] ={"yel","yello","yetis","ranger","redr","redra"};
    Trie theTrie(words,5);
    for(int i=0;i<5;i++){
        if(!theTrie.lookup(words[i])){
            error = "Error 1a: " + words[i] + " should be in the Trie but it was not found";
            return false;
        }
    }

    for(int i=5;i<8;i++){
        if(theTrie.lookup(words[i])){
            error = "Error 1b: " + words[i] + " should not be in the Trie but lookup() returned true\n";
            return false;
        }
    }
    for (int i=0;i<6;i++){
        if(theTrie.lookup(partials[i])){
            error = "Error 1c: " + partials[i] + " should not be in the Trie but lookup() returned true\n";
            return false;
        }
    }
    return true;
}


/*test Trie and addword and search*/
bool test2(std::string key[], int max, std::string& error){
    std::string words[8] = {"yellow", "yell", "yeti", "yes","red","redraw","ran","y"};
    std::string partials[6] ={"yel","yello","yetis","ranger","redr","redra"};
    Trie theTrie(words,0);
    for(int i=0;i<8;i++){
        theTrie.addWord(words[i]);
    }
    for(int i=0;i<8;i++){
        if(!theTrie.lookup(words[i])){
            error = "Error 2a: " + words[i] + " should be in the Trie but it was not found";
            return false;
        }
    }
    for (int i=0;i<6;i++){
        if(theTrie.lookup(partials[i])){
            error = "Error 2b: " + partials[i] + " should not be in the Trie but lookup() returned true\n";
            return false;
        }
    }

    Trie secondTrie(words,8);
    for(int i=0;i<8;i++){
        if(!secondTrie.lookup(words[i])){
            error = "Error 2c: " + words[i] + " should be in the Trie but it was not found";
            return false;
        }
    }
    for (int i=0;i<6;i++){
        if(secondTrie.lookup(partials[i])){
            error = "Error 2d: " + partials[i] + " should not be in the Trie but lookup() returned true\n";
            return false;
        }
    }

    return true;
}
/*test suggest*/
bool test3(std::string key[], int max, std::string& error){
    std::string words[7] = {"yellow", "yell", "yeti", "yes","red","redraw","ran"};
    Trie theTrie(words,3);
    for(int i=3;i<7;i++){
        theTrie.addWord(words[i]);
    }
    std::string prefix[11]={
       "yel", "red", "y"
    };
    int numCorrectSuggestions[11]={
        2,2,4
    };
    std::string correctSuggestions[11][30]={
        {"yell","yellow"},{"red","redraw"},{"yell","yellow","yes","yeti"}
    };
    std::string suggestList[10];

    for(int i=0;i<3;i++){
        int result = theTrie.beginsWith(prefix[i], suggestList);
        if(result != numCorrectSuggestions[i]){
            error = "Error 3a: return value from beginsWith() function was not correct";
            return false;
        }
        bool isSame=true;
        for(int j=0;isSame && j<result;j++){
            if(suggestList[j] != correctSuggestions[i][j]){
                isSame=false;
            }
        }
        if(!isSame){
            error="Error 3b: list of words with given prefix was not correct.";
            return false;
        }
    }
    return true;
}

/*test Trie lookup with lots of words*/
bool test4(std::string key[], int max, std::string& error){
    Trie theTrie(key,max);
    for(int i=0;i<max;i++){
        theTrie.addWord(key[i]);
    }
    for(int i=0;i<max;i++){
        if(!theTrie.lookup(key[i])){
            error = "Error 4a: " + key[i] + " should be in the Trie but it was not found";
            return false;
        }
    }
    return true;
}

/*test suggest on large data set*/
bool test5(std::string key[], int max, std::string& error){
    Trie theTrie(key,max);
    std::string prefix[11]={
        "apple", "carrot", "sublime","carth",
        "dramat","famil","city","world",
        "yard","adver","event"

    };
    int numCorrectSuggestions[11]={
        15, 8, 5, 6, 17, 18, 11, 19, 14, 29, 19
    };
    std::string correctSuggestions[11][30]={
        {   "apple","appleberry","appleblossom","applecart","appledrane","applegrower","applejack",
            "applejohn","applemonger","applenut","appleringy","appleroot","applesauce","applewife",
            "applewoman"
        },
        {   "carrot","carrotage","carroter","carrotiness","carrottop","carrotweed","carrotwood",
            "carroty"
        },
        {   "sublime","sublimed","sublimely","sublimeness","sublimer"
        },
        {   "carthaginian","carthame","carthamic","carthamin","carthamus","carthusian"
        },
        {   "dramatic","dramatical","dramatically","dramaticism","dramatics","dramaticule",
            "dramatism","dramatist","dramatizable","dramatization","dramatize","dramatizer",
            "dramaturge","dramaturgic","dramaturgical","dramaturgist","dramaturgy"
        },
        {   "familia","familial","familiar","familiarism","familiarity","familiarization",
            "familiarize","familiarizer","familiarizingly","familiarly","familiarness",
            "familism","familist","familistery","familistic","familistical","family","familyish"
        },
        {   "city","citycism","citydom","cityfolk","cityful","cityish","cityless","cityness",
            "cityscape","cityward","citywards"
        },
        {   "world","worlded","worldful","worldish","worldless","worldlet","worldlike",
            "worldlily","worldliness","worldling","worldly","worldmaker","worldmaking",
            "worldproof","worldquake","worldward","worldwards","worldway","worldy"
        },
        {   "yard","yardage","yardang","yardarm","yarder","yardful","yarding","yardkeep",
            "yardland","yardman","yardmaster","yardsman","yardstick","yardwand"
        },
        {
            "adverb","adverbial","adverbiality","adverbialize","adverbially","adverbiation",
            "adversant","adversaria","adversarious","adversary","adversative","adversatively",
            "adverse","adversely","adverseness","adversifoliate","adversifolious","adversity",
            "advert","advertence","advertency","advertent","advertently","advertisable",
            "advertise","advertisee","advertisement","advertiser","advertising"

        },
        {
            "event","eventful","eventfully","eventfulness","eventide","eventime","eventless",
            "eventlessly","eventlessness","eventognath","eventognathi","eventognathous",
            "eventration","eventual","eventuality","eventualize","eventually","eventuate",
            "eventuation"
        },

    };
    std::string suggestList[60];

    for(int i=0;i<11;i++){
        int result = theTrie.beginsWith(prefix[i], suggestList);
        if(result != numCorrectSuggestions[i]){
            error = "Error 5a: return value from beginsWith() function was not correct";
            return false;
        }
        bool isSame=true;
        for(int j=0;isSame && j<result;j++){
            if(suggestList[j] != correctSuggestions[i][j]){
                isSame=false;
            }
        }
        if(!isSame){
            error="Error 5b: list of words with given prefix was not correct.";
            return false;
        }
    }

    return true;
}


void toLower(char* word){
    for(int i=0;word[i]!='\0';i++){
        word[i]=tolower(word[i]);
    }
}


