/*************************************************************/
/*                                                           */
/*  Starter file for a2                                      */
/*                                                           */
/*  Author1 Name: Michal Kot-Kawula                          */
/*      - Chaining Table/ Chaining Table Documentation       */
/*  Author2 Name: Ian Henriquez                              */
/*      - LPTable/ LPTable Documentation                     */
/*                                                           */
/*************************************************************/

#include <string>
#include <utility>
#include <functional>
#include "mylist.h"

template <class TYPE>
class Table{
public:
    Table(){}
    virtual bool insert(const std::string& key, const TYPE& value)=0;
    virtual bool modify(const std::string& key, const TYPE& value)=0;
    virtual bool remove(const std::string& key)=0;
    virtual bool find(const std::string& key, TYPE& value)=0;
    virtual int numRecords() const = 0;
    virtual bool isEmpty() const = 0;
    virtual int capacity() const = 0;
    virtual ~Table(){}
};

template <class TYPE>
class SimpleTable:public Table<TYPE>{

    struct Record{
        TYPE data_;
        std::string key_;
        Record(const std::string& key, const TYPE& data){
            key_=key;
            data_=data;
        }

    };

    Record** records_;   //the table
    int capacity_;       //capacity of the array

    void grow(){
        Record** newarray=new Record*[capacity_*2+1];
        int sz = numRecords();

        for(int i=0;i<sz;i++){
            newarray[i]=records_[i];
        }
        capacity_*=2;
        delete [] records_;
    }
public:
    SimpleTable(int capacity);
    SimpleTable(const SimpleTable& rhs);
    SimpleTable(SimpleTable&& rhs);
    virtual bool insert(const std::string& key, const TYPE& value);
    virtual bool modify(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const SimpleTable& operator=(const SimpleTable& rhs);
    virtual const SimpleTable& operator=(SimpleTable&& rhs);
    virtual ~SimpleTable();
    virtual bool isEmpty() const{return numRecords()==0;}
    virtual int numRecords() const;
    virtual int capacity() const {return capacity_;}

};

template <class TYPE>
int SimpleTable<TYPE>::numRecords() const{
    int rc=0;
    for(int i=0;records_[i]!=nullptr;i++){
        rc++;
    }
    return rc;
}



template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity): Table<TYPE>(){
    records_=new Record*[capacity+1];
    capacity_=capacity;
    for(int i=0;i<capacity_+1;i++){
        records_[i]=nullptr;
    }
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& rhs){
    records_=new Record*[rhs.capacity_+1];
    capacity_=rhs.capacity_;
    for(int i=0;i<capacity_+1;i++){
        records_[i]=nullptr;
    }
    for(int i=0;i<rhs.numRecords();i++){
        insert(rhs.records_[i]->key_,rhs.records_[i]->data_);
    }
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& rhs){
    capacity_=rhs.capacity_;
    records_=rhs.records_;
    rhs.records_=nullptr;
    rhs.capacity_=0;
}

template <class TYPE>
bool SimpleTable<TYPE>::insert(const std::string& key, const TYPE& value){
    int idx=-1;
    int sz=numRecords();
    bool rc=false;
    for(int i=0;i<sz;i++){
        if(records_[i]->key_ == key){
            idx=i;
        }
    }
    if(idx==-1){
        if(sz == capacity_){
            grow();
        }
        records_[numRecords()]=new Record(key,value);
        for (int i=0; i<sz-1; i++) {      
            for (int j=0; j<sz-1-i; j++){   
                if (records_[j+1]->key_ < records_[j]->key_) {    
                    Record* tmp = records_[j];             
                    records_[j] = records_[j+1];        
                    records_[j+1] = tmp;           
                }
            }
        }
        rc=true;
    }

    return rc;
}

template <class TYPE>
bool SimpleTable<TYPE>::modify(const std::string& key, const TYPE& value){
    int idx=-1;
    bool rc=false;
    for(int i=0;i<numRecords();i++){
        if(records_[i]->key_ == key){
            idx=i;
        }
    }
    if(idx!=-1){
        records_[idx]->data_=value;
    }
    return rc;
}


template <class TYPE>
bool SimpleTable<TYPE>::remove(const std::string& key){
    int idx=-1;
    for(int i=0;i<numRecords();i++){
        if(records_[i]->key_ == key){
            idx=i;
        }
    }
    if(idx!=-1){
        delete records_[idx];
        for(int i=idx;i<numRecords()-1;i++){
            records_[i]=records_[i+1];
        }
        records_[numRecords()-1]=nullptr;
        return true;
    }
    else{
        return false;
    }
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const std::string& key, TYPE& value){
    int idx=-1;
    int size = numRecords();
    for(int i=0;i<size;i++){
        if(records_[i]->key_ == key){
            idx=i;
        }
    }
    if(idx==-1){
        return false;
    }
    else{
        value=records_[idx]->data_;
        return true;
    }
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& rhs){
    if(this!=&rhs){
        if(records_){
            while(numRecords() != 0){
                remove(records_[0]->key_);
            }
            delete [] records_;
        }
        records_=new Record*[rhs.capacity_+1];
        capacity_=rhs.capacity_;
        for(int i=0;i<capacity_;i++){
            records_[i]=nullptr;
        }
        for(int i=0;i<rhs.numRecords();i++){
            insert(rhs.records_[i]->key_,rhs.records_[i]->data_);
        }

    }
    return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& rhs){
    if(records_){
        while(numRecords() != 0){
            remove(records_[0]->key_);
        }
        delete [] records_;
    }
    records_=rhs.records_;
    capacity_=rhs.capacity_;
    rhs.records_=nullptr;
    rhs.capacity_=0;

    return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable(){
    if(records_){
        int sz=numRecords();
        for(int i=0;i<sz;i++){
            remove(records_[0]->key_);
        }
        delete [] records_;
    }
}

//Chaining Table
template <class TYPE>
class ChainingTable :public Table<TYPE> {

    //private struct
    struct Record {
        TYPE data_;
        std::string key_;
        Record() {}

        //custom constructor to initalize key and data
        Record(const std::string& key, const TYPE& data) {key_ = key;data_ = data;};

        //constructor to initialize key
        Record(const std::string& key) {key_ = key;}

        //comparison operator to compare current keys are equal
        bool operator==(Record rhs) {return (this->key_ == rhs.key_);}

        //comparison operator to compare current keys are not equal
        bool operator!=(Record rhs) {return (this->key_ != rhs.key_);}
    };

    //capacity of table
    int capacity_;
    // number of records
    double numRecords_ = 0.0;
    //maximum load factor of array
    double maxLoadFactor_;
    //hasing function
    std::hash<std::string> hashFunction;
    //variable pointing to CacheList 
    CacheList<Record>** cTable_;
   

public:
    ChainingTable(int capacity, double maxLoadFactor = 1.0);
    ChainingTable(const ChainingTable& other);
    ChainingTable(ChainingTable&& other);
    double loadFactor() const;
    virtual bool insert(const std::string& key, const TYPE& value);
    virtual bool modify(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const ChainingTable& operator=(const ChainingTable& other);
    virtual const ChainingTable& operator=(ChainingTable&& other);
    virtual ~ChainingTable();
    virtual bool isEmpty() const;
    virtual int numRecords() const;
    virtual int capacity() const;

};

//custom contructor initializing capacity and maxloadFactor
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int capacity, double maxLoadFactor) : Table<TYPE>() {
    this->capacity_ = capacity;
    this->maxLoadFactor_ = maxLoadFactor;
    this->cTable_ = new CacheList<Record> * [capacity];

    for (auto i = 0; i < capacity; ++i) {
        cTable_[i] = nullptr;
    }
}

//copy contructor
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other) {if (!other.isEmpty()) { *this = other; }}


//copy move constructor
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other) {if (!other.isEmpty()) { *this = other; }}


//insert using chaining as a collision resolution method
//This function is passed a key-value pair. If your table already has a record with a matching key, the function does nothing and returns false. 
//Otherwise the new key-value pair is added to the table and true is returned. 
//When inserting, if adding a new record causes the load factor to exceed the maxLoadFactor, function will grow the array. 
//(each time the table is grown, the capacity is doubled)
template <class TYPE>
bool ChainingTable<TYPE>::insert(const std::string& key, const TYPE& value) {
   
    //add records to table
    size_t index = hashFunction(key) % capacity_;

    if (cTable_[index] == nullptr){cTable_[index] = new CacheList<Record>();}

    //find by key
    auto it = cTable_[index]->search(key);

    //if found return false
    if (it != cTable_[index]->end()){return false;}


    Record rec(key, value);
    cTable_[index]->insert(rec);
    numRecords_++;


    //if loadFactor exceeded grow table * 2
    double load = loadFactor();
    if (load > maxLoadFactor_) {

        int newCapacity = capacity_ * 2;
        CacheList<Record>** newTable = new CacheList<Record>*[newCapacity];
        for (auto i = 0; i < newCapacity; ++i) {
            newTable[i] = nullptr;
        }
        //repopulate table
        for (int i = 0; i < capacity_; ++i){
            if(cTable_[i] != nullptr){
                for (auto it = cTable_[i]->begin(); it != cTable_[i]->end(); ++it) {
                    const std::string& myKY = (*it).key_;
                    size_t newIndex = hashFunction(myKY) % newCapacity;
                    if (newTable[newIndex] == nullptr) {
                        newTable[newIndex] = new CacheList<Record>();
                    }
                    newTable[newIndex]->insert(*it);
                }
            }
        }
        //delete old table
        for (auto i = 0; i < capacity_; ++i) {
            if (cTable_[i] != nullptr) {
                delete cTable_[i];
            }
        }
        delete[] cTable_;
        cTable_ = newTable;
        capacity_ = newCapacity;
    }

    return true;
}


//modify function
//This function is passed a key-value pair. 
//If your table already has a record with a matching key, the record's value is replaced by the value passed to this function. 
//If no record exists with a matching key, function does nothing and returns false.
template <class TYPE>
bool ChainingTable<TYPE>::modify(const std::string& key, const TYPE& value) {
    size_t i = hashFunction(key) % capacity_;


    if (cTable_[i] == nullptr){cTable_[i] = new CacheList<Record>();}

    else{
        auto it = cTable_[i]->search(key);

        if (it != cTable_[i]->end()){
            (*it).data_ = value;
            return true;
        }
    }
    return false;
}

//remove function
//This function is passed a key. 
//If your table contains a record with a matching key, the record (both the key and the value) is removed from the table
template <class TYPE>
bool ChainingTable<TYPE>::remove(const std::string& key) {
    size_t i = hashFunction(key) % capacity_;

    if (cTable_[i] != nullptr){

        auto it = cTable_[i]->search(key);

        if (it != cTable_[i]->end()){
            cTable_[i]->erase(it);
            numRecords_--;
            return true;
        }
    }
    return false;
}


//find function
//This function is passed a key and a reference for passing back a found value. 
//If your table contains a record with a matching key, the function returns true, and passes back the value from the record. 
//If it does not find a record with a matching key, function returns false.
template <class TYPE>
bool ChainingTable<TYPE>::find(const std::string& key, TYPE& value) {
    size_t i = hashFunction(key) % capacity_;

    if (cTable_[i] != nullptr){

        auto it = cTable_[i]->search(key);

        if (it != cTable_[i]->end()){
            value = (*it).data_;
            return true;
        }
    }
    return false;
}

//copy assignement operator
//copy data from current table to other. If current table not empty delete all data
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other) {
    if (!this->isEmpty()){
        for (int i = 0; i < capacity_; i++) {
            if (cTable_[i] != nullptr)
                delete cTable_[i];
        }
        delete[] cTable_;
    }

    this->capacity_ = other.capacity_;
    this->maxLoadFactor_ = other.maxLoadFactor_;
    this->numRecords_ = other.numRecords_;
    this->cTable_ = new  CacheList<Record> * [this->capacity_];

    for (auto i = 0; i < this->capacity_; ++i)
    {
        if (other.cTable_[i]) {
            cTable_[i] = new CacheList<Record>(*other.cTable_[i]);
        }
        else {cTable_[i] = nullptr;}
    }
    return *this;
}


//move assignment operator
//Deepcopying data from current table to other
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other) {
    if (!this->isEmpty()){

        CacheList<Record>** tempList = this->cTable_;
        this->cTable_ = other.cTable_;
        other.cTable_ = tempList;

        int tempCap = this->capacity_;
        this->capacity_ = other.capacity_;
        other.capacity_ = tempCap;

        double tempRec = this->numRecords_;
        this->numRecords_ = other.numRecords_;
        other.numRecords_ = tempRec;

        double tempMaxLoad = this->maxLoadFactor_;
        this->maxLoadFactor_ = other.maxLoadFactor_;
        other.maxLoadFactor_ = tempMaxLoad;
    }
    return *this;
}


//destructor
//destructs all emlements of Eecords table
template <class TYPE>
ChainingTable<TYPE>::~ChainingTable() {
    for (int i = 0; i < capacity_; i++) {
        if (cTable_[i] != nullptr)
            delete cTable_[i];
    }
    delete[] cTable_;
}

//This function checks if table is empty.
template <class TYPE>
bool ChainingTable<TYPE>::isEmpty() const {return numRecords() == 0;}

//This function returns the number of records in the table.
template <class TYPE>
int ChainingTable<TYPE>::numRecords() const {return this->numRecords_;}

//This function returns capacity of the table.
template <class TYPE>
int ChainingTable<TYPE>::capacity() const {    return this->capacity_;}

//This function returns the load factor of the table. (number of records divided by capacity of table)
template <class TYPE>
double ChainingTable<TYPE>::loadFactor() const {return numRecords_ / capacity_;}


template <class TYPE>
class LPTable:public Table<TYPE>{
    struct Record{
        std::string key_;
        TYPE data_;
        Record(const std::string& key, const TYPE& data) {
            key_ = key;
            data_ = data;
        };
    };
    Record** records_;
    int capacity_;
    double maxLoadFactor_;
    double numRecords_ = 0.0;

    // this function grows the table by 2x and rehashes all the records. it is called when the load factor is greater than the max load factor and takes no parameters and returns nothing
    void grow(){
        Record** temp = new Record * [capacity_ * 2];
    
        for (int i = 0; i < capacity_ * 2; i++){
            temp[i] = nullptr;
        }
        for (int i = 0; i < capacity_; i++){
            if (records_[i] != nullptr){
                int index = std::hash<std::string>{}(records_[i]->key_) % (capacity_ * 2);
                while (temp[index] != nullptr){
                    index = (index + 1) % (capacity_ * 2);
                }
                temp[index] = records_[i];
            }
        }
        delete[] records_;
        records_ = temp;
        capacity_ *= 2;
    }

public:
    LPTable(int capacity, double maxLoadFactor=0.7);
    LPTable(const LPTable& other);
    LPTable(LPTable&& other);
    double loadFactor() const;
    virtual bool insert(const std::string& key, const TYPE& value);
    virtual bool modify(const std::string& key, const TYPE& value);
    virtual bool remove(const std::string& key);
    virtual bool find(const std::string& key, TYPE& value);
    virtual const LPTable& operator=(const LPTable& other);
    virtual const LPTable& operator=(LPTable&& other);
    virtual ~LPTable();
    virtual bool isEmpty() const;
    virtual int numRecords() const;
    virtual int capacity() const;

};

//this is the constructor for the LPTable class it takes in a capacity and a maxLoadFactor and sets the capacity_ and maxLoadFactor_ to the values passed in and then creates an array of pointers to records of size capacity_ and sets all the values to nullptr
template <class TYPE>
LPTable<TYPE>::LPTable(int capacity, double maxLoadFactor): Table<TYPE>(){
    capacity_=capacity;
    maxLoadFactor_=maxLoadFactor;
    records_=new Record*[capacity_ + 1];
    for (int i = 0; i < capacity_ + 1; i++){
        records_[i] = nullptr;
    }
}

//this is the copy constructor for the LPTable class it takes in a const reference to an LPTable object and sets the capacity_ and maxLoadFactor_ to the values of the other object and then creates an array of pointers to records of size capacity_ and sets all the values to nullptr and then copies all the values from the other object into the new object 
template <class TYPE>
LPTable<TYPE>::LPTable(const LPTable<TYPE>& other){
    records_ = new Record * [other.capacity_ + 1];
    for (int i = 0; i < other.capacity_; i++){
        if (other.records_[i] != nullptr){
            records_[i] = new Record(other.records_[i]->key_, other.records_[i]->data_);
        }
        else{
            records_[i] = nullptr;
        }
    }
    maxLoadFactor_=other.maxLoadFactor_;
    capacity_=other.capacity_;
    numRecords_=other.numRecords_;
}

//this is the move constructor for the LPTable class it takes in a reference to an LPTable object and sets the capacity_ and maxLoadFactor_ to the values of the other object and then creates an array of pointers to records of size capacity_ and sets all the values to nullptr and then copies all the values from the other object into the new object and then sets the other object to default values
template <class TYPE>
LPTable<TYPE>::LPTable(LPTable<TYPE>&& other){
    records_ = other.records_;
    maxLoadFactor_ = other.maxLoadFactor_;
    capacity_ = other.capacity_;
    numRecords_ = other.numRecords_;
    other.records_ = nullptr;
    other.maxLoadFactor_ = 0;
    other.numRecords_ = 0;
    other.capacity_ = 0;
}

//this is the insert function for the LPTable class it takes in a key and a value and then creates a new record with the key and value and then hashes the key and finds the index of where to insert the record and then inserts the record into the array and then returns true if the record was inserted and false if the record was not inserted. it also grows the array if the load factor is greater than the maxLoadFactor_
template <class TYPE>
bool LPTable<TYPE>::insert(const std::string& key, const TYPE& value){
    int index = std::hash<std::string>{}(key) % capacity_;
    TYPE temp;
    if (find(key, temp)){
        return false;
    }
    while (records_[index] != nullptr){
        index = (index + 1) % capacity_;
    }
    records_[index] = new Record(key, value);
    numRecords_++;
    if (loadFactor() > maxLoadFactor_){
        grow();
    }
    return true;
    
}

//this is the modify function for the LPTable class it takes in a key and a value and then hashes the key and finds the index of where to insert the record and then inserts the record into the array and then returns true if the record was inserted and false if the record was not inserted. it also grows the array if the load factor is greater than the maxLoadFactor_
template <class TYPE>
bool LPTable<TYPE>::modify(const std::string& key, const TYPE& value){
    std::hash<std::string> hashFunction;
    size_t hash = hashFunction(key);
    int index = hash % capacity_;
    while(records_[index]!=nullptr){
        if(records_[index]->key_==key){
            records_[index]->data_=value;
            return true;
        }
        index=(index+1)%capacity_;
    }
    return false;

}

//this is the remove function for the LPTable class it takes in a key and then hashes the key and finds the index of where to remove the record and then removes the record from the array and then returns true if the record was removed and false if the record was not removed.
template <class TYPE>
bool LPTable<TYPE>::remove(const std::string& key){
    int emptyIndex = std::hash<std::string>{}(key) % capacity_;
    while(records_[emptyIndex] != nullptr){
        if(records_[emptyIndex]->key_ == key){
            delete records_[emptyIndex];
            records_[emptyIndex] = nullptr;
            int currentIndex = (emptyIndex + 1) % capacity_;
            while(records_[currentIndex] != nullptr){
                int index = std::hash<std::string>{}(records_[currentIndex]->key_) % capacity_;
                if((currentIndex < index && (index <= emptyIndex || emptyIndex < currentIndex)) || (index <= emptyIndex && emptyIndex < currentIndex)){
                    records_[emptyIndex] = records_[currentIndex];
                    records_[currentIndex] = nullptr;
                    emptyIndex = currentIndex;
                }
                currentIndex = (currentIndex + 1) % capacity_;
            }
            numRecords_--;
            return true;
        }
        emptyIndex = (emptyIndex + 1) % capacity_;
    }
    return false;

    
}

//this is the find function for the LPTable class it takes in a key and a value and then hashes the key and finds the index of where to find the record and then finds the record in the array and then returns true if the record was found and false if the record was not found.
template <class TYPE>
bool LPTable<TYPE>::find(const std::string& key, TYPE& value){
    std::hash<std::string> hashFunction;
    size_t hash = hashFunction(key);
    int index = hash % capacity_;
    while(records_[index]!=nullptr){
        if(records_[index]->key_==key){
            value=records_[index]->data_;
            return true;
        }
        index=(index+1)%capacity_;
    }
    return false;
}

//this is the assignment operator for the LPTable class it takes in a const reference to an LPTable object and then deletes the current array and then creates a new array of the same size and then copies all the values from the other object into the new object and then returns a reference to the new object
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(const LPTable<TYPE>& other){
    if (this != &other) {
        delete[] records_;
        records_ = new Record * [other.capacity_ + 1];
        for (int i = 0; i < other.capacity_; i++){
            if (other.records_[i] != nullptr){
                records_[i] = new Record(other.records_[i]->key_, other.records_[i]->data_);
            }
            else{
                records_[i] = nullptr;
            }
        }
        maxLoadFactor_ = other.maxLoadFactor_;
        capacity_ = other.capacity_;
        numRecords_ = other.numRecords_;
    }
    return *this;
}

//this is the move assignment operator for the LPTable class it takes in a reference to an LPTable object and then deletes the current array and then sets the capacity_ and maxLoadFactor_ to the values of the other object and then creates an array of pointers to records of size capacity_ and sets all the values to nullptr and then copies all the values from the other object into the new object and then sets the other object to default values and then returns a reference to the new object
template <class TYPE>
const LPTable<TYPE>& LPTable<TYPE>::operator=(LPTable<TYPE>&& other){
    if (this != &other) {
        delete[] records_;
        records_ = other.records_;
        maxLoadFactor_ = other.maxLoadFactor_;
        capacity_ = other.capacity_;
        numRecords_ = other.numRecords_;
        other.records_ = nullptr;
        other.maxLoadFactor_ = 0;
        other.capacity_ = 0;
        other.numRecords_ = 0;
    }
    return *this;
}

//this is the destructor for the LPTable class it deletes all the records in the array and then deletes the array
template <class TYPE>
LPTable<TYPE>::~LPTable(){
    for (int i = 0; i < capacity_; i++) {
        if (records_[i] != nullptr)
            delete records_[i];
    }
    delete[] records_;

}

//this is the isEmtpy function for the LPTable class it returns true if the array is empty and false if the array is not empty. it takes in no parameters
template <class TYPE>
bool LPTable<TYPE>::isEmpty() const {
    return numRecords()==0;
}

//this is the numRecords function for the LPTable class it returns the number of records in the array. it takes in no parameters and returns an int
template <class TYPE>
int LPTable<TYPE>::numRecords() const {
    return numRecords_;
}

//this is the capacity function for the LPTable class it returns the capacity of the array. it takes in no parameters and returns an int
template <class TYPE>
int LPTable<TYPE>::capacity() const {
    return capacity_;
}

//this is the loadFactor function for the LPTable class it returns the load factor of the array. it takes in no parameters and returns a double
template <class TYPE>
double LPTable<TYPE>::loadFactor() const {
    return (double)numRecords()/capacity_;
}


