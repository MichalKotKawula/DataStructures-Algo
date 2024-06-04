/*******************************************************************/
/*                                                                 */
/*  A1 Part 3: Majority Element starter file                       */
/*                                                                 */
/*  Author1 Name: Ian Henriquez                                    */
/*      - Find Candidate                                           */
/*  Author2 Name: Michal Kot-Kawula                                */
/*      - majorityElement                                          */
/*                                                                 */
/*******************************************************************/
bool findCandidate(int array[],int& candidate, int sz);
bool majorityElement(const int arr[], int& majority, int sz);


bool majorityElement(const int arr[], int& majority, int sz){
    int* tempArr = new int[sz];
    int count = 0;
    bool found = false;

  
    for (int i = 0; i < sz; i++) {
        tempArr[i] = arr[i];
    }
  
    if (findCandidate(tempArr, majority, sz)) {
        for (int i = 0; i < sz; ++i) {
  
            if (arr[i] == majority) {++count;}

            if (count > sz / 2) {
                found = true;
                i = sz;
            }
        }
    }
    delete[] tempArr;
    return found;
}
bool findCandidate(int array[],int& candidate, int sz){
    int* leftOver = new int[sz];
    int leftOverIterator = 0;
    int left = 0;
    bool isOdd = false;
    if ((sz % 2) != 0) {
        left = array[--sz];
        isOdd = true;

    }
    for (int i = 0; i < sz; i += 2) {
        if (array[i] == array[i + 1]) {
            leftOver[leftOverIterator] = array[i];
            leftOverIterator++;
        }
    }
    if (leftOverIterator == 1) {
        candidate = leftOver[0];
        return true;
    }
    if (leftOverIterator && findCandidate(leftOver, candidate, leftOverIterator)) {
        delete[] leftOver;
        return true;
    }
    else {
        candidate = left;
        delete[] leftOver;
        return isOdd;
    }
}


