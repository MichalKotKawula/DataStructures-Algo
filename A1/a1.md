# Part 2

| Function | Optimal runtime |
|---|---|
| insert() | O(n) |
| size() | O(1) |
| empty() | O(1) |
| erase() | O(n)|
| copy constr. | O(n) | 
| copy assignment  | O(n) |
| move constr. | O(n) |
| move assignment | O(n) |

# Part 5

Place the analysis of the majority element and find candidate function

## majorityElement  Function

```cpp
bool majorityElement(const int arr[], int& majority, int sz){
    int* tempArr = new int[sz]; 	//1
    int count = 0;                  //1
    bool found = false;			//1

  
    for (int i = 0; i < sz; i++) {  //1 + 2 (n - 1)
        tempArr[i] = arr[i];     	//1   
    }
  
    if (findCandidate(tempArr, majority, sz)) {  //1 + 3(n-1) + 22
        for (int i = 0; i < sz; ++i) {   		 //1 + 2(n - 1)
  
            if (arr[i] == majority) {            //1
				++count;		       //1
}

            if (count > sz / 2) {             //2
                found = true;			    //1
                i = sz;				    //1
            }
        }
    }
    delete[] tempArr;				//1
    return found;					//1
}

```

$$T (n) = 1 + 1 + 1 + 1 + 2(n - 1) + 1 + 1 + 3(n - 1) + 22 + 1 + 2(n - 1) + 1 + 1 + 2 + 1 + 1 + 1 + 1 $$
 
$$T (n) = 15 + 21 + 7(n - 1) $$

$$T (n) = 7(n - 1) + 36 $$

$$T (n) = 7n + 29 $$



$$T (n) = T(n-2) + 58 $$

$$T (n) = T(n-3) + 87 $$



$$T (n) = T(0) + 29n $$

$$T (n) = 29n + 1 $$



$$T(n)isO(n) $$

## Candidate Function

```cpp
bool findCandidate(int array[],int& candidate, int sz){
    int leftOver[sz]; //2
    int leftOverIterator = 0; //2
    int left = 0; //2
    bool isOdd = false; //2
    if((sz % 2) != 0){ // 2
        left = array[--sz]; //3
        isOdd = true; //1

    }
    for(int i = 0; i < sz; i+=2){ //2 + 2(n-1)
        if(array[i] == array[i + 1]){  // 4(n-1)
            leftOver[leftOverIterator] = array[i];  // 3(n-1)
            leftOverIterator++;  //n-1
        }
    }
    if(leftOverIterator == 1){ //1
        candidate = leftOver[0];  //2
        return true;  //1
    }
    if(leftOverIterator && findCandidate(leftOver, candidate, leftOverIterator)){ //1 + T(n-1)
        return true; // 1
    } else {
        candidate = left; //1
        return isOdd; //1
    }
}


```

Best case uses 14 + 11(n-1) operations thus

$T(0) = 14 + 11(n-1)$

$T(1) = 14 + 11(n-1)$

For T(n) >= 1 total operations are 

$T(n) = 14 + 11(n-1) + T(n-1)$

Because there are a total of 14 + 11(n-1) n's 

$T(n) = 14(n-1) + 11n^2 - 11n$

Thus

T(n) = 
$O(n^2)$



# Part 6 (team member: Ian Henriquez)
I learned a lot from this assignemt, i'd say the two biggest things i learned was

1. how to search and make insertions with a linked list using sentinel nodes

the entire concept of having to resort the list using accesCount I found very intersting and even though it took a while to fully implement i enjoyed learing

2. how to properly work with recursive functions

I found the findCandidate function to be pretty tough but it forced me to actually understand how recursion works 


My main difficulties were mostly just in figuring out how I was going to implement certain features,
but once we figured that out it was decently smooth sailing



# Part 6 (team member: Michal Kot-Kawula)
While working on this assignment I had a chance to review most of the material I have learned during this first half of the semester.
It was a perfect opportunity to test my knowledge regarding the concept of a doubly linked list on a bigger scale.
The helper functions and operators were not big of a challenge in this assignment but the search and insert functions using sentinel nodes were the biggest challenge.
My teammate was the one to fully figure out that concept, then helped me understand it.
I learned that understanding the problem is crucial before starting to implement it, because it saves time and confusion.
Overall it was a good experience, and I'm glad it was presented to us.
