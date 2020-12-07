#pragma once

#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP
#include <iostream>



template <typename Key, typename Info>
class Sequence {


private:
    struct Node {
        Key key;
        Info info;
        Node* next;

         Node(const Key& k, const Info& i, Node* _next = nullptr){
            key = k;
            info = i;
            next = _next;
        };
    };
    //structure Node is a well-known singly-linked list elements with
    //template types as Key key responsible for storing the key of the node
    //and Info info responsible for storing data of the element
    //it also contains the Node* next pointer which poins to the next element in the
    //singly-linked list

    Node* head;
    //pointer which points to the first element of the singly-linked list

    int Sequence_length;

    void printNode(Node*& curr) const;
    //private method which display all the information about the
   //particular node which is passed to this method

   void copySequence(const Sequence<Key, Info>& copy);

public:
    Sequence();
    //constructor of the Sequence class which set the head pointer to the nullptr

    ~Sequence();
    //destructor of the Sequence class instance which use the public method clearSequence()
    //which deletes all the elements of singly-linked list and what is more importnat
    //free the memory taken by the nodes to prevent memory leaking after destruction

    Sequence(const Sequence<Key, Info>&);
    //copy constructor sets its head pointer to nullptr
    //then by usage of 'this' operator assign the passed Sequence
    //to the new created one

    //operators overloading
    Sequence<Key, Info>& operator=(const Sequence<Key, Info>&);
    Sequence<Key, Info>& operator+(const Sequence<Key, Info>&);
    Sequence<Key, Info>& operator+=(const Sequence<Key, Info>&);


    Info operator[](int index);
    //operator overloading which traverse the sequence and return
    //the info of element of passed index where indexes of elements in the sequence
    //are understand as elements of array : a[0], a[1],....

    //simple bool operators
    bool operator==(const Sequence<Key, Info>&) const;
    //operator== returns true if two sequences has exactly the same 
    //elements

    bool operator!=(const Sequence<Key, Info>&) const;
    //operator!= returns true when they are different

    //these operators are comparing the length of the sequences
    bool operator>(const Sequence<Key, Info>&) const;
    bool operator>=(const Sequence<Key, Info>&) const;
    bool operator<(const Sequence<Key, Info>&) const;
    bool operator<=(const Sequence<Key, Info>&) const;

    
    //getters which returns the info of the elements
    //basis on the key and number of occurences
    Info getInfoByKey(const Key& key, int occurence = 1) const;
    //method returns info of the last or first element
    Info getFirstElemInfo() const;
    Info getLastElemInfo() const;

    //these methhods return the key of the element
    //in the same way as the three previous methods
    Key getKeyByInfo(const Info& info, int occurence = 1) const;
    Key getFirstElemKey() const;
    Key getLastElemKey() const;


    //insert methods
    void insertAtBegining(const Key&, const Info&);
    //method which insert the element at the beginning of the singly-linked list
    //by creating the new Node with the given Key and Info and setting head pointed to this 
    //node and setting the next pointer to the previously first element

    void insertAtTheEnd(const Key& k, const Info& i);
    //method which creates the element with the given Key and Info and insert
    //it at the end by setting the pointer 'next' of the last element (obtained by itterating)
    //from null to the newly created element

    void insertAfter(const Key& k, const Info& i, const Key& where, const int& occurance = 1);
    //method which creates the element with the given Key and Info and insert
    //it after the element with a given Key

    //removing methods
    bool clearSequence();
    //method which iterate through the singly-linked list and deletes all of its elements
    //set the head pointer to the nullptr and protect from memory leaking

    //removing methods which traverse the sequence
    //and returns true or false wether the elements was deleted
    //or false if the elements does not exists
    bool removeByKey(const Key& k, int occurence = 1);
    bool removeByInfo(const Info& info, int occurence = 1);
    bool removeLastElem();
    bool removeFirstElem();
    bool removeAtPosition(const int&);
    
    //boolean methods which returns true if, with the specified key or/and info
    //passed, the elements was found in the sequence
    bool findByInfo(const Info&, int occurence = 1) const;
    bool findByKey(const Key& key, int occurence = 1) const;
    bool findElem(const Key& key, const Info& info, int occurence = 1);
    

    bool isEmpty() const;
    //this method is a very short one which return true if head pointer is nullptr
    //or false if it's not
    //method was designed to simplify the solution and make the code more clear and neat

    int sequenceLength() const;
    //method which iterates through the singly-linked list and adding up the occurances
    //of elements to the variable which is returned by this function
    //this function as the rest of the similar methods uses the isEmpty method
    //to check whether the sequence is empty or not ( if so then return 0)

    //printing methods
    void printSequenceData() const;
    void printSequenceKeys() const;
    void printSequenceInfo() const;

    Sequence<Key, Info> subSeqToEndFrom(int startIndex) const;
    //method which returns the rest of the sequence from the given index

    Sequence<Key, Info> subSeqFromByLength(int startIndex, int length) const;
    //method which returns the part of the sequence called subsequence depending on the
    //startIndex and length parameters


    Sequence<Key, Info> subSeqFromBeginTo(int lastIndex) const;
    //method which returns part of the sequence from the beginning to the given
};

//at the end of this file is also the shuffle method
//and the method called shuffleExpetions ti handle the exceptions
//based on passed elements to this method


template<typename Key, typename Info>
Sequence<Key, Info>::Sequence() {
    this->head = nullptr;
    this->Sequence_length = 0;
}

template<typename Key, typename Info>
Sequence<Key, Info>::~Sequence() {
    clearSequence();
}

template<typename Key, typename Info>
Sequence<Key, Info>::Sequence(const Sequence<Key, Info>& copy) {
    this->head = nullptr;
    this->copySequence();
}


template<typename Key, typename Info>
void Sequence<Key, Info>::copySequence(const Sequence<Key, Info>& copy){

    Node* curr;

    if(head != nullptr) clearSequence();

    if(copy.head == nullptr){
        this->head = nullptr;
        this->Sequence_length = 0;
    }else{
        curr = copy.head;

        this->head = new Node(curr->key, curr->info);

        curr = curr->next;

        while(curr != nullptr){
            this->insertAtTheEnd(curr->key, curr->info);
            curr = curr->next;
        }
    }
}

template<typename Key, typename Info>
Info Sequence<Key, Info>::operator[](int index){

    if((index < 0) || (index > (sequenceLength() - 1) ) ){
        throw std::invalid_argument("ERROR : operator[] : invalid index value.");
    };
    if(isEmpty()){
        throw std::out_of_range("ERROR : operator[] : sequence is empty.");
    }

    Node* curr = head;
    int n = 0;

    while(curr){
        if(n == index) return curr->info;
        ++n;
        curr = curr->next;
    }
    throw std::out_of_range("ERROR : operator[] : element of given index does not exists");
}

template<typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator=(const Sequence<Key, Info>& elem) {

    if (this == &elem) return *this;
    if (elem.isEmpty()) return *this;
    this->clearSequence();
    this->head = nullptr;
    this->Sequence_length = 0;

    Node* curr = elem.head;
    while (curr) {
        this->insertAtTheEnd(curr->key, curr->info);
        curr = curr->next;
    }
    return *this;
}

template<typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator+(const Sequence<Key, Info>& elem) {

    Sequence<Key, Info>& newSequence(*this);
    if (elem.isEmpty()) return newSequence;

    Node* curr = elem.head;

    while (curr) {
        newSequence.insertAtTheEnd(curr->key, curr->info);
        curr = curr->next;
    }
    //std::cout << "newSequence size : "<< newSequence.sequenceLength() << std::endl;
    //newSequence.printSequenceKeys();
    return newSequence;
}

template<typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key, Info>::operator+=(const Sequence<Key, Info>& elem) {
    
    *this = *this + elem;
    return *this;
}


//============two the same function implementaions with a oppoiste boolean values
template<typename Key, typename Info>
bool Sequence<Key, Info>::operator==(const Sequence<Key, Info>& elem) const{

    if(this->Sequence_length != elem.Sequence_length) return false;

    Node* currRight = elem.head;
    Node* currLeft = this->head;

    while(currRight && currLeft){

        if(currLeft->info != currRight->info) return false;
        if(currLeft->key != currRight->key) return true;
        currRight = currRight->next;
        currLeft = currLeft->next;
    }
    return true;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::operator!=(const Sequence<Key, Info>& elem) const{

    if(this->Sequence_length != elem.Sequence_length) return true;

    Node* currRight = elem.head;
    Node* currLeft = this->head;

    while(currRight && currLeft){
        
        if(currLeft->info != currRight->info) return true;
        if(currLeft->key != currRight->key) return true;
        currRight = currRight->next;
        currLeft = currLeft->next;
    }
    return false;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::operator>(const Sequence<Key, Info>& elem) const{
    if(this->sequenceLength() > elem.sequenceLength()){
        return true;
    }{
        return false;
    }
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::operator>=(const Sequence<Key, Info>& elem) const{
    if(this->sequenceLength() >= elem.sequenceLength()){
        return true;
    }{
        return false;
    }
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::operator<(const Sequence<Key, Info>& elem) const{
    if(this->sequenceLength() < elem.sequenceLength()){
        return true;
    }{
        return false;
    }
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::operator<=(const Sequence<Key, Info>& elem) const{
    if(this->sequenceLength() <= elem.sequenceLength()){
        return true;
    }{
        return false;
    }
}

template<typename Key, typename Info>
Key Sequence<Key, Info>::getKeyByInfo(const Info& info, int occurence) const{

    if (isEmpty()){
        throw std::out_of_range("ERROR : getInfo : Sequence is empty cannot retrive any data.");
    };
    if(occurence <= 0){
        throw std::invalid_argument("ERROR : getInfo : invalid occurence value.");
    };

    Node* curr = head;
    int n = 0;

    while(curr){
        if(curr->info == info) ++n;
        if(n == occurence) return curr->key;
        curr = curr->next;
    };
    throw std::runtime_error("ERROR : getKey : element of given info does not exists");
}

template<typename Key, typename Info>
Info Sequence<Key, Info>::getInfoByKey(const Key& key, int occurence) const{

    if (isEmpty()){
        throw std::out_of_range("ERROR : getInfo : Sequence is empty cannot retrive any data.");
    };
    if(occurence <= 0){
        throw std::invalid_argument("ERROR : getInfo : invalid occurence value.");
    };

    Node* curr = head;
     int n = 0;

     while(curr){
         if(curr->key == key) ++n;
         if(n == occurence) return curr->info;
         curr = curr->next;
     };
    
    throw std::runtime_error("ERROR : getInfoByKey : element of given key does not exists");
}

template<typename Key, typename Info>
Info Sequence<Key, Info>::getFirstElemInfo() const{

    if (isEmpty()){
        throw std::out_of_range("ERROR : getInfo : Sequence is empty cannot retrive any data.");
    };

    return head->info;
}

template<typename Key, typename Info>
Info Sequence<Key, Info>::getLastElemInfo() const{

    if (isEmpty()){
        throw std::out_of_range("ERROR : getInfo : Sequence is empty cannot retrive any data.");
    };

    if(head->next == nullptr){
        return head->info;
    }

    Node* curr = head;

    while(curr->next){
        curr = curr->next;
    };
    return curr->info;
}

template<typename Key, typename Info>
Key Sequence<Key, Info>::getFirstElemKey() const{
    if (isEmpty()){
        throw std::out_of_range("ERROR : getInfo : Sequence is empty cannot retrive any data.");
    };

    return head->key;
}

template<typename Key, typename Info>
Key Sequence<Key, Info>::getLastElemKey() const{

    if (isEmpty()){
        throw std::out_of_range("ERROR : getInfo : Sequence is empty cannot retrive any data.");
    };

    if(head->next == nullptr){
        return head->key;
    }

    Node* curr = head;

    while(curr->next){
        curr = curr->next;
    };
    return curr->key;
}





template<typename Key, typename Info>
void Sequence<Key, Info>::insertAtBegining(const Key& k, const Info& i) {

    Node* newNode = new Node(k, i, head);
    head = newNode;
    ++Sequence_length;
}

template<typename Key, typename Info>
void Sequence<Key, Info>::insertAtTheEnd(const Key& k, const Info& i) {

    Node* newNode = new Node(k, i);
    Node* curr = head;

    if (isEmpty()) {
        head = newNode;
        ++Sequence_length;
    }
    else {
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = newNode;
        ++Sequence_length;
    }
}

template<typename Key, typename Info>
void Sequence<Key, Info>::insertAfter(const Key& k, const Info& i, const Key& where, const int& occurance) {

    if (isEmpty()) {
        throw std::out_of_range("Sequence is empty. Cannot execute insertAfter function.");
    };

    if(occurance <= 0){
        throw std::invalid_argument("ERROR : insertAfter : invalid occurence value");
    };

    Node* curr = head;
    int n = 0;

/// tu zle wgl
    while (where != curr->key) {
        curr = curr->next;
        if (!curr){
            throw std::out_of_range("ERROR : insertAfter : cannot insert element after non-existing element.");
        };
        if (where == curr->key) ++n;
        if (n >= occurance) break;
    }

    Node* newNode = new Node(i, k, curr->next);
    curr->next = newNode;
    ++Sequence_length;
}


template<typename Key, typename Info>
bool Sequence<Key, Info>::removeByKey(const Key& givenKey, int occurence) {

    if (isEmpty()) {
        throw std::out_of_range("Sequence is empty. Cannot execute removeBYKey function.");
    }
    
    if (occurence <= 0){
        throw std::invalid_argument("insertAfter - invalid occurence value.");
    };

        Node* curr = head;
        Node* prev = head;
        int n = 0;

        while (curr) {
            if (curr->key == givenKey) {

                ++n;

                if (curr == head) {
                    head = curr->next;
                    delete curr;
                    --Sequence_length;
                    prev = head;
                    curr = head;
                }
                else {
                    prev->next = curr->next;
                    delete curr;
                    --Sequence_length;
                    curr = prev->next;
                }

                if(n == occurence) return true;
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }
        return false;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::removeByInfo(const Info& givenInfo, int occurence){
    if (isEmpty()) {
        throw std::out_of_range("Sequence is empty. Cannot execute removeBYKey function.");
    }
    
    if (occurence <= 0){
        throw std::invalid_argument("insertAfter - invalid occurence value.");
    };

        Node* curr = head;
        Node* prev = head;
        int n = 0;

        while (curr) {
            if (curr->info == givenInfo) {

                ++n;

                if (curr == head) {
                    //head points to t he next element
                    head = curr->next;
                    //free memory of the curr element
                    delete curr;
                    //decreasing the sequence length
                    --Sequence_length;
                    //prev element points now at head
                    prev = head;
                    //current element points at head
                    curr = head;
                }
                else {
                    prev->next = curr->next;
                    delete curr;
                    --Sequence_length;
                    curr = prev->next;
                }

                //when n equals to the given number of occurence then true is returned
                if(n == occurence) return true;
            }
            else {
                //when the analysing node do not have info equals to the given one
                //then the next element is searching
                prev = curr;
                curr = curr->next;
            }
        }
        //false when no element was found with given info
        return false;

}

template<typename Key, typename Info>
bool Sequence<Key, Info>::removeFirstElem() {

     if (isEmpty()) {
        throw std::out_of_range("Sequence is empty. Cannot execute removeFirstElem function.");
    };

    Node* curr = head;
    head = head->next;
    delete curr;
    --Sequence_length;
    return true;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::removeLastElem() {
    //memory leak jeżeli 


    if (isEmpty()) {
        std::cout << "Sequence is empty. Cannot remove last element." << std::endl;
        return false;
    };

    if (head->next == nullptr) {
        head = nullptr;
        return true;
    };
    Node* curr = head;
    Node* prev = head;
    while (curr->next) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = nullptr;
    delete curr;
    --Sequence_length;
    return true;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::removeAtPosition(const int& position) {

    if ((position > sequenceLength() - 1) || (position < 0)) {
        throw std::invalid_argument("removeAtPosition - invalid position value.");
    };
    if (position == 0) {
        return removeFirstElem();
    };

    //wywalic wyjątek lengtht - 1
    if (position == (sequenceLength() - 1)) {
        return removeLastElem();
    };

    int n = 0;
    Node* curr = head;
    Node* prev = head;

    while ((n != position) && (prev = curr)) {
        prev = curr;
        curr = curr->next;
        n++;
    };
    prev->next = curr->next;
    delete curr;
    --Sequence_length;
    return true;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::findByInfo(const Info& info, int occurence) const {
    
    if(isEmpty()){
        throw std::out_of_range("ERROR : find(const Info& info, int occurence) : Sequence is empty. Cannot find elemnt of given info");
    };

    if(occurence <= 0){
        throw std::invalid_argument("ERROR : find(const Info& info, int occurence) : invalid arguments.");
    }

    Node* curr = head;
    int n = 0;

    while(curr){
        if(curr->info == info) ++n;
        if(n == occurence) return true;
        curr = curr->next;
    };

    return false;
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::findByKey(const Key& key, int occurence) const {
    
    if(isEmpty()){
        throw std::out_of_range("ERROR : find(const Info& info, int occurence) : Sequence is empty. Cannot find elemnt of given info");
    };

    if(occurence <= 0){
        throw std::invalid_argument("ERROR : find(const Info& info, int occurence) : invalid arguments.");
    }

    Node* curr = head;
    int n = 0;

    while(curr){
        if(curr->key == key) ++n;
        if(n == occurence) return true;
        curr = curr->next;
    };
    return false;
}


template<typename Key, typename Info>
bool Sequence<Key, Info>::findElem(const Key& key, const Info& info, int occurence){
    if(isEmpty()){
        throw std::out_of_range("ERROR : find(const Info& info, int occurence) : Sequence is empty. Cannot find elemnt of given info");
    };

    if(occurence <= 0){
        throw std::invalid_argument("ERROR : find(const Info& info, int occurence) : invalid arguments.");
    }

    Node* curr = head;
    int n = 0;

    while(curr){
        if((curr->key == key) && (curr->info == info)) ++n;
        if(n == occurence) return true;
        curr = curr->next;
    };
    return false;
}




template<typename Key, typename Info>
void Sequence<Key, Info>::printSequenceData() const {

    if (isEmpty()) {
        std::cerr << "Sequence is empty. Printing sequence data impossible." << std::endl;
        return;
    }
    else {

        Node* curr = head;
        while (curr) {
            this->printNode(curr);
            curr = curr->next;
        }
        return;
    }
}

template<typename Key, typename Info>
void Sequence<Key, Info>::printSequenceKeys() const {

    if (isEmpty()) {
        std::cerr << "Sequence is empty. Printing sequence keys impossible" << std::endl;
        return;
    }
    else {
        Node* curr = head;
        while (curr) {
            std::cout << " " << curr->key << " ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }
}

template<typename Key, typename Info>
void Sequence<Key, Info>::printSequenceInfo() const {
    if (isEmpty()) {
        std::cerr << "Sequence is empty. Printing sequence info impossible" << std::endl;
        return;
    }
    else {
        Node* curr = head;
        while (curr) {
            std::cout << " " << curr->info << " ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }
}

template<typename Key, typename Info>
bool Sequence<Key, Info>::clearSequence() {

    if (isEmpty()) {
        return true;
    }
    else {
        Node* curr = head;
        Node* toBeDeleted;

        while (curr) {
            toBeDeleted = curr;
            curr = curr->next;
            delete toBeDeleted;
            --Sequence_length;
        }
        head = nullptr;
    }
    return true;
}



template<typename Key, typename Info>
bool Sequence<Key, Info>::isEmpty() const {
    return (head == nullptr);
}
template<typename Key, typename Info>
int Sequence<Key, Info>::sequenceLength() const {

    int length = 0;

    if (isEmpty()) {
        return 0;
    }
    else {
        Node* curr = head;
        while (curr) {
            ++length;
            curr = curr->next;
        }
        return length;
    }
}

template<typename Key, typename Info>
void Sequence<Key, Info>::printNode(Node*& curr) const {

    if (!curr) {
        throw std::invalid_argument("printNode(Node* &curr) : given node is null");
    }
    else {
        std::cout << "key: " << curr->key;
        std::cout << " info: " << curr->info << std::endl;
    }
}


template<typename Key, typename Info>
Sequence<Key, Info> Sequence<Key, Info>::subSeqFromByLength(int startIndex, int length) const{

    if(isEmpty()){
        throw std::out_of_range("Sequence is empty. Cannot execute subSeqFromByLength() method");
    };

    if((startIndex < 0) || (startIndex > sequenceLength() - 1)){
        throw std::invalid_argument("subSeqFromByLength - invalid startIndex value.");
    };

    if((length < 0) || (startIndex > (sequenceLength() - 1))){
        throw std::out_of_range("subSeqFromByLength - invalid length value.");
    };

    Sequence<Key, Info> newSequence;

    Node* curr = head;
     int n = 0;

    while (curr) {
        if(n == startIndex) break;
        ++n;
        curr = curr->next;
    };

    n = 1;
    while (curr) {
        newSequence.insertAtTheEnd(curr->key, curr->info);
        if(n == length) break;
        ++n;
        curr = curr->next;
    };
    return newSequence;
}

template<typename Key, typename Info>
Sequence<Key, Info> Sequence<Key, Info>::subSeqToEndFrom(int startIndex) const{

    if(isEmpty()){
        throw std::out_of_range("Sequence is empty. Cannot execute subSeqToEndFrom()");
    };

    if((startIndex < 0) || (startIndex > (sequenceLength() - 1))){
        throw std::invalid_argument("subSeqToEndFrom - invalid startIndex value.");
    };

    Sequence<Key, Info> newSequence;
    Node* curr = head;
    int n = 0;

    while (curr) {
        if(n == startIndex) break;
        ++n;
        curr = curr->next;
    };

    while (curr) {
        newSequence.insertAtTheEnd(curr->key, curr->info);
        curr = curr->next;
    };
    return newSequence;
}

template<typename Key, typename Info>
Sequence<Key, Info> Sequence<Key, Info>::subSeqFromBeginTo(int lastIndex) const{

    if(isEmpty()){
         throw std::out_of_range("Sequence is empty. Cannot execute subSeqFromBeginTo()");
    };

    if((lastIndex < 0) || (lastIndex > (sequenceLength() - 1))){
        throw std::out_of_range("subSeqFromBeginTo - invalid lastIndex value.");
    };

    Sequence<Key, Info> newSequence;
    Node* curr = head;
    int n = 0;

    //while loop where into the newSequence
    //are inserted elements from the beginning to the element
    //with the lastIndex
    while (curr) {
        newSequence.insertAtTheEnd(curr->key, curr->info);
        if(n == lastIndex) return newSequence;
        ++n;
        curr = curr->next;
    };
    return newSequence;
}

template<typename Key, typename Info>
void shuffleExceptions(
    const Sequence<Key, Info>& source1, int startIndex1, int length1,
    const Sequence<Key, Info>& source2, int startIndex2, int length2,
    int limit){

    if (source1.isEmpty()) {
        throw std::invalid_argument("Cannot execute shuffle method. 'source1' sequence is empty!");
    };

    if (source2.isEmpty()) {
        throw std::invalid_argument("Cannot execute shuffle method. 'source2' sequence is empty.");
    };

    //checking given length
    if (length1 <= 0) {
        throw std::invalid_argument("Cannot execute shuffle method. Incorrect length1 value should be positve integer.");
    };
    if (length2 <= 0) {
        throw std::invalid_argument("Cannot execute shuffle method. Incorrect length2 value should be positve integer.");
    }
    if (startIndex1 < 0 || startIndex1 >= source1.sequenceLength() - 1) {
        throw std::invalid_argument("Cannot execute shuffle method. Incorrect startIndex1: out of source1 range.");
    };

    if (startIndex2 < 0 || startIndex2 >= source2.sequenceLength() - 1) {
        throw std::invalid_argument("Cannot execute shuffle method. Incorrect startIndex2: out of source2 range.");
    };

    if (limit <= 0) {
        throw std::invalid_argument("Cannot execute shuffle method. Incorrect limit value must be positive.");
    };
}


template<typename Key, typename Info>
Sequence<Key, Info> shuffle(
    const Sequence<Key, Info>& source1, int startIndex1, int length1,
    const Sequence<Key, Info>& source2, int startIndex2, int length2,
    int limit) {

    Sequence<int, int> shuffleSeq;

    //function checking the parameters and throwing exceptions
    shuffleExceptions(source1, startIndex1, length1, 
    source2, startIndex2, length2, limit);
    
    //boolean values which controls the process of "shuffling" and while loop
    bool source1In = true;
    bool source2In = false;
    bool source1Finish = false;
    bool source2Finish = false;
    bool shuffleDone = false;
    
    //beginning of the loop with boolean false false variable
    while(!shuffleDone){
        //beginning from the source1 -> source1In = true
        if(source1In){
            //checking if the starting index is not bigger than the last index
            if(!(startIndex1 > (source1.sequenceLength() - 1))){
                //if it's false then source2Finish is set to true
                //what means that there is no other elements to be extracted
                source2Finish = true;
                //checking if the length of the sequence to be extracted
                //is out of the range of the source1
                if((startIndex1 + length1) > source1.sequenceLength()){
                    //if it will be out of the range of source1 then
                    //to the shuffleSeq is added the rest of the sequence source1
                    shuffleSeq += source1.subSeqToEndFrom(startIndex1);
                }else{
                    //if it won't be out of range then to the shuffleSeq
                    //is added the part of the source1 from startIndex1 of
                    //length length1
                    shuffleSeq += source1.subSeqFromByLength(startIndex1, length1);
                    //next subsequence extracted from the source1
                    //will be from index increased bt the length1
                    startIndex1 += length1;
                }
            }
        //analogically the same as in the source1
        }else if(source2In){
            if(!(startIndex2 > (source2.sequenceLength() - 1))){
                source2Finish = true;
                if((startIndex2 + length2) > source2.sequenceLength()){
                    shuffleSeq += source1.subSeqToEndFrom(startIndex1);
                    shuffleDone=true;
                }else{
                    shuffleSeq += source2.subSeqFromByLength(startIndex2, length2);
                    startIndex2 += length2;
                }
            }
        };
        //change the processed sequence source1, source2
        source1In = !source1In;
        source2In = !source2In;

        //checking if the remaining number of elements to be put in the shuffleSeq
        //is shorter than the length of each source sequences
        if( (limit - shuffleSeq.sequenceLength()) < length1){
            //if it is true then the length is changed to the remaining
            //available number of places
            length1 = (limit - shuffleSeq.sequenceLength());
        }
         if( (limit - shuffleSeq.sequenceLength()) < length2){
            length2 = (limit - shuffleSeq.sequenceLength());
        }
        //if during the processing the length of shuffleSeq is equal to the limit
        //then shuffleDone is set to true and process is stopped
        if(shuffleSeq.sequenceLength() == limit) shuffleDone = true;

        //checking if the startIndex is out of range of the sequence source
        if((startIndex1 > (source1.sequenceLength() - 1))) source1Finish = true;
        if((startIndex2 > (source2.sequenceLength() - 1))) source2Finish = true;
        //if the two sources are run of the elements then the process is done
        if(source1Finish && source2Finish) shuffleDone = true;
    }
    return shuffleSeq;
}


#endif // !SEQUENCE_HPP


