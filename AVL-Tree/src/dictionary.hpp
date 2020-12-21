#pragma once

#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <stdexcept>
#include <iostream>
#include <utility>

   /*
            AVL Tree is balanced when all of the nodes has balance factor as : -1, 0, 1
            if it's not then the AVL tree is not balanced
            -1 means that the node has higher left subtree of one branch, node is so-called -> left-heavy
                  5
                 / \ 
                4   7
               /
              2
             1 means that the node has higher right subtree of one branch, node is so-called -> right-heavy     
                  5
                 / \ 
                4   7
                     \
                      8
             0 means that node is ideally balanced -> left and right heifht of the tree are equals to each other   
                  5
                 / \ 
                4   7
    */


template <typename Key, typename Info>
class Dictionary {

    private:

        struct Node
        {   
            //key of the node which has to be UNIQUE
            Key key;
            //particular data which in the case of dictionary is the std::string
            Info info;
            //pointers to the left and right subtree of the node
            Node* left;
            Node* right;

            //simple constructor for the node
            Node(const Info& _info, const Key& _key, 
            Node* _left = nullptr, Node* _right = nullptr){

                 key = _key;
                 info = _info;
                 left = _left;
                 right = _right;
            }

            Node* getLeftChild();
            Node* setLeftChild(Node*);
            Node* getRightChild();
            Node* setRightChild(Node*);
        };

        //Node pointer to the first element
        Node* root;
        int numOfElem = 0;

        Node* insertElem(const Key&, const Info&, Node*);
        Node* erase(Node*, const Key&);

        //double rotations
        Node* rotateLeft(Node*);
        Node* rotateRight(Node*);
        Node* lr_rotation(Node*);
        Node* rl_rotation(Node*);
    
        Node* balanceTree(Node*);

        //copy
        Node* copyDictionary(Node*);
        Node* getElemByKey(Node*, const Key&) const;
        Node* getMaxNode(Node*);

        void clearDictionary(Node*);
        void display(Node*, int depth = 0, int state = 0);
        void addDictionary(Node*);
        //exceptions
        void nonExistingException(const Dictionary<Key, Info>&, const Key&);
        void emptyDictException(const Dictionary<Key, Info>&);
       
        int count(const Info&, Node*) const;
        int getHeight(Node*);
        int getMaxHeight(int left, int right);
        int getCurrBalanceFactor(int left, int right);
        int getBalanceFactor(Node*);

        Key& getKey(Node*);
        Key& findMax(Node*);
        Key& findMin(Node*);

        bool compareNodes(Node*, Node*);

    public:
        class Iterator;
        Dictionary();
        Dictionary(const Dictionary&);
        ~Dictionary();

        bool isEmpty() const;
        bool findByKey(const Key&) const;
        bool isTreeBalanced();

        int getHeight();
        int count(const Info&) const;
        int getNumOfElem() const;
        Key& getRootKey();

        void insert(const Key&, const Info&);
        void erase(const Key&);
        void clearDictionary();
        void display();
        
        //pari of extremums : first-minimum, second-maximum
        std::pair<Key, Key> getExtremum();
        
        //operators overloading
        Dictionary<Key, Info>& operator=(const Dictionary<Key, Info>&);
        Dictionary<Key, Info>& operator+=(const Dictionary<Key, Info>&);
        Dictionary<Key, Info> operator+(const Dictionary<Key, Info>&);
        Info& operator[](const Key&);

        //logical operators
        bool operator==(const Dictionary<Key, Info>&);
        bool operator!=(const Dictionary<Key, Info>&);
        bool operator>=(const Dictionary<Key, Info>&) const;
        bool operator<=(const Dictionary<Key, Info>&) const;
        bool operator>(const Dictionary<Key, Info>&) const;
        bool operator<(const Dictionary<Key, Info>&) const;

        Iterator begin();
};


template <typename Key, typename Info>
class Dictionary<Key, Info>::Iterator{

    friend class Dictionary<Key, Info>;

    private: 
        Node* iter;
        //function which throws the exception if the iterator is nullptr
        void throwException(const Iterator&);

    public:
        Iterator();
        ~Iterator();
        Iterator(const Iterator&);
        Iterator(Node*);
        
        //methods for moving the iterator to the left or to the right
        bool right();
        bool left();

        //operator overloading
        Iterator& operator=(const Iterator&);
        //logical operators
        bool operator==(const Iterator&);
        bool operator!=(const Iterator&);
        Key& getKey();
        Info& getInfo();
        Key& operator*();
};

template <typename Key, typename Info>
Dictionary<Key, Info>::Iterator::Iterator(){
    this->iter = nullptr;
}
template <typename Key, typename Info>
Dictionary<Key, Info>::Iterator::~Iterator(){
    this->iter = nullptr;
}
template <typename Key, typename Info>
Dictionary<Key, Info>::Iterator::Iterator(const Iterator& iterator){
    this->iter = iterator.iter;
}
template <typename Key, typename Info>
Dictionary<Key, Info>::Iterator::Iterator(Node* node){
    this->iter = node;
}
template <typename Key, typename Info>
void  Dictionary<Key, Info>::Iterator::throwException(const Iterator& iterator){
    if(iterator.iter == nullptr){
        throw std::underflow_error("Empty iterator. Cannot retrive any data.");
    }
    return;
}

template <typename Key, typename Info>
bool Dictionary<Key, Info>::Iterator::right(){
    //checking whether the Node iter exists
    //to avoid the segmentation fault
    if(this->iter == nullptr){
        return false;
    }
    //assignning to the current node its right node
    iter = iter->right;
    return true;
}
template <typename Key, typename Info>
bool Dictionary<Key, Info>::Iterator::left(){
    //checking whether the Node iter exists
    //to avoid the segmentation fault
    if(this->iter == nullptr){
        return false;
    }
    //assignning to the current node its left node
    iter = iter->left;
    return true;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Iterator& Dictionary<Key, Info>::Iterator::operator=(const Iterator& iterator){
    this->iter = iterator.iter;
    return *this;
}
template <typename Key, typename Info>
bool Dictionary<Key, Info>::Iterator::operator==(const Iterator& iterator){
    return (this->iter == iterator.iter);
}
template <typename Key, typename Info>
bool Dictionary<Key, Info>::Iterator::operator!=(const Iterator& iterator){
    return !(*this== iterator.iter);
}

template <typename Key, typename Info>
Key& Dictionary<Key, Info>::Iterator::getKey(){
    throwException(*this);
    return iter->key;
}
template <typename Key, typename Info>
Info& Dictionary<Key, Info>::Iterator::getInfo(){
    throwException(*this);
    return iter->info;
}
template <typename Key, typename Info>
Key& Dictionary<Key, Info>::Iterator::operator*(){
    throwException(*this);
    return iter->key;
}

template <typename Key, typename Info>
Dictionary<Key, Info>::Dictionary(){
    this->root = nullptr;
    this->numOfElem = 0;
}

template <typename Key, typename Info>
Dictionary<Key, Info>::Dictionary(const Dictionary<Key, Info>& source){
    this->root = nullptr;
    *this = source;
}

template <typename Key, typename Info>
Dictionary<Key, Info>::~Dictionary(){
    clearDictionary(root);
}

template <typename Key, typename Info>
bool Dictionary<Key, Info>::isEmpty() const{
    return (root == nullptr);
}

template <typename Key, typename Info>
bool Dictionary<Key, Info>::isTreeBalanced(){
    if( (getBalanceFactor(root) < -1) || (getBalanceFactor(root) > 1)){
        std::cout <<"balanceFactor of root : " <<getBalanceFactor(root) <<std::endl;
        return false;
    }
    return true;
}

template <typename Key, typename Info>
int Dictionary<Key, Info>::getHeight(){
    return getHeight(this->root);
}

template <typename Key, typename Info>
int Dictionary<Key, Info>::getHeight(Node* node){
    
    //creating the varaible for storing the height
    int height = 0;

    if(node != nullptr){
        int leftHeight = getHeight(node->getLeftChild());
        int rightHeight = getHeight(node->getRightChild());
        int maxHeight = getMaxHeight(leftHeight, rightHeight);
        height = 1 + maxHeight;
    }
    return height;
}

template <typename Key, typename Info>
int Dictionary<Key, Info>::getNumOfElem() const{
    return (this->numOfElem);
}

template <typename Key, typename Info>
int Dictionary<Key, Info>::getBalanceFactor(Node* node){

    int balanceFactor = 0;
    if(node != nullptr){
        int leftHeight = getHeight(node->getLeftChild());
        int rightHeight = getHeight(node->getRightChild());
        balanceFactor = rightHeight - leftHeight;
    }
    return balanceFactor;
}

template <typename Key, typename Info>
Key& Dictionary<Key, Info>::getRootKey(){
    return getKey(root);
}

template <typename Key, typename Info>
Key& Dictionary<Key, Info>::getKey(Node* node){

    return node->key;
}


template <typename Key, typename Info>
void Dictionary<Key, Info>::display(Node* node, int depth, int state){

    this->emptyDictException(*this);

    if(node->getRightChild()){
        display(node->getRightChild(), depth + 1, 1);
    }

    for(int i = 0; i < depth; i++){
        std::cout<<"     ";
    }
    if(state == 1){
        std::cout<<"┌───";
    }else if(state == 2){
       std::cout<<"└───";
    }
    std::cout << "(" << node->key<<","<<node->info<< ")" << std::endl;

    if(node->getLeftChild()){
        display(node->getLeftChild(), depth + 1, 2);
    }
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::display(){
    std::cout <<"============================================="<<std::endl;
    this->display(root);
    std::cout <<"============================================="<<std::endl;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::clearDictionary(){
    clearDictionary(root);
    this->root = nullptr;
    this->numOfElem = 0;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::clearDictionary(Node* rootElem){
    if(rootElem == nullptr) return;
    clearDictionary(rootElem->getLeftChild());
    clearDictionary(rootElem->getRightChild());
    delete rootElem;
}


template <typename Key, typename Info>
void Dictionary<Key, Info>::insert(const Key& key, const Info& info){
    if(findByKey(key)){
        throw std::overflow_error("Element already exists in dictionary.");
    }
    //assignning the balanced node to the root
    //after the inserting the new element
    root = insertElem(key, info, root);
    //increasing the number of elements of the tree
    numOfElem++;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::insertElem(const Key& key, const Info& info, Node* elem){

    //checking whether the passed node is nullptr
    if(!elem){
        //if it is, then is returned the new instance of Node
        return new Node(info, key);
    }

    //if the given key is bigger than the current node's key 
    //then it is moving to the right
    if(key > elem->key){
        //assigning to the right child the given elements
        //by recursion
        elem->setRightChild( insertElem(key, info, elem->getRightChild()) );
        //balancing the parent to which was assgined the newly inserted element
        elem = balanceTree(elem);
    //if the given key is smaller then we're moving to the left
    }else if(key < elem->key){
        //analogically the same as above
        //we're proceeding untill we find the "node" to which we can assign the new child/element
        elem->setLeftChild( insertElem(key, info, elem->getLeftChild()) );
        elem = balanceTree(elem);
    }
    //return the node after balancing 
    return balanceTree(elem);
}


template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::erase(Node* node, const Key& key){

    //checking whether the node pointer is nullptr
    if(!node){
        return nullptr;
    }

    //traversing through the tree to find the element to be deleted
    //moving to the right if the looking element has bigger key that the current
    if(key < node->key){
        node->setLeftChild( erase(node->getLeftChild(), key) );
        //moving to the left if the given key is smaller than the current
    }else if(key > node->key){
        node->setRightChild( erase(node->getRightChild(), key) );
        //if the element is found, there is FOUR CASES
    }else{
        //FIRST CASE -> node to be deleted is the leaf (does not have left and right child)
        if(node->getLeftChild() == nullptr && node->getRightChild() == nullptr){
            delete node;
            return nullptr;
        //SECOND CASE -> node to be deleted had only the left child
        }else if(node->getLeftChild() == nullptr && node->getRightChild() != nullptr){
            Node* rightSubTree = node->getRightChild();
            delete node;
            return rightSubTree;
        //THIRD CASE -> node to be deleted had only the right child
        }else if(node->getLeftChild() != nullptr && node->getRightChild() == nullptr){
            Node* leftSubTree = node->getLeftChild();
            delete node;
            return leftSubTree;
        //FOURTH CASE -> node to be deleted had both right and left childs
        }else{
            //in such a case we have to find the maximal node in the left subtree
            Node* maxSubLeft = getMaxNode( node->getLeftChild() );
            //assigning the key of the maximal node to the current node
            node->key = maxSubLeft->key;
            node->info = maxSubLeft->info;
            //setting the left child as the returned node after deleting the 
            node->setLeftChild( erase(node->getLeftChild(), maxSubLeft->key) );
        }   
    }
    return balanceTree(node);
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::erase(const Key& key){

    //CHECKING THE EXCEPTIONS
    this->emptyDictException(*this);
    this->nonExistingException(*this, key);

    root = erase(root, key);
    //DECREASING THE NUMBER OF ELEMENTS
    numOfElem--;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::balanceTree(Node* node){


    //first case when the node is right-heavy
    if(getBalanceFactor(node) > 1){
        //if the left node is right-heavy//leaf
        if(getBalanceFactor(node->getLeftChild()) >= 0){
            node = rotateLeft(node);
        //if the left node is right-heavy
        }else{
            node = lr_rotation(node);
        }
    //second case where the node is left-heavy
    }else if(getBalanceFactor(node) < -1){
        //if the right node is right-heavy/leaf
        if(getBalanceFactor(node->getRightChild()) >= 0){
            node = rotateRight(node);
        //if the right node is left-heavy
        }else{
            node = rl_rotation(node);
        }
    }
    //the tree is balanced -> balanceFactor = 0
    return node;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::rotateLeft(Node* node){
    //creating the new element and assigning to it 
    //the right child of the passed node
    Node* parentElem = node->getRightChild();
    //setting the current rightChild of the node as left child of the parent element
    node->setRightChild( parentElem->getLeftChild() );
    //setting the left child of the parentElement as a node
    parentElem->setLeftChild(node);
    return parentElem;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::rotateRight(Node* node){

    //analogically the same as rotateLeft method
    Node* parentElem = node->getLeftChild();
    node->setLeftChild( parentElem->getRightChild() );
    parentElem->setRightChild(node);
    return parentElem;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::lr_rotation(Node* node){
    //to perform the left-right rotation, first we need to perform a left rotation
    //on the left node
    Node* parentElem = node->getLeftChild();
    node->setLeftChild( rotateLeft(parentElem) );
    //then we are performing a right rotation on the node
    return rotateRight(node);
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::rl_rotation(Node* node){
    //first performing the right-left rotation on the left subNode
    Node* parentElem = node->getRightChild();
    //then we're performing the right rotation and assigning it to the right child of the node 
    node->setRightChild( rotateRight(parentElem) );
    //left rotation on the given node
    return rotateLeft(node);
}


template <typename Key, typename Info>
int Dictionary<Key, Info>::getCurrBalanceFactor(int left, int right){
   return (right - left);
}

//method returning the bigger number - used in the computing the height if the node
template <typename Key, typename Info>
int Dictionary<Key, Info>::getMaxHeight(int left, int right){

    if(right > left){
        return right;
    }else{
        return left;
    }
}

template <typename Key, typename Info>
int Dictionary<Key, Info>::count(const Info& info) const{
    //invoking the private method for the count
    return count(info, root);
}

template <typename Key, typename Info>
int Dictionary<Key, Info>::count(const Info& info, Node* node) const{
    //if the recursion has met the leaf then is returned the 0
    if(!node){
        return 0;
    }
    //if we find the element with a given key then we're invoking the
    //same methods by recursion
    if(info == node->info){
        //adding one to the returned value beacuse of the found the same key
        return ( 1 + count(info, node->getRightChild()) + count(info, node->getLeftChild()) );
    }else{
        //withoud adding one beacuse the key is not the same 
        return ( count(info, node->getRightChild()) + count(info, node->getLeftChild()) );
    }
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::getElemByKey(Node* node, const Key& key) const{
     //if the current node is nullptr then it means that
    //we've met the leaf which does not have any edges to left or right nodes
    if(!node){
        return nullptr;
    };
    //if searching key is bigger than the key in the current node
    if(key > node->key){
        //then we have to look into the right subtree
        return getElemByKey(node->getRightChild(), key);
    }
    //if searching key is smaller than the key in the current node
    if(key < node->key){
        //then we have to look into the left subtree
        return getElemByKey(node->getLeftChild(), key);
    }else{
        //if any of the statements are fulfilled then then we find our key in the current node
        return node;
    }
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::getMaxNode(Node* node){

    //checking whether there exists right child 
    //which is needed for getting the maximal elements
  if(node->getRightChild() == nullptr){
      return node;
  }else{
      return getMaxNode(node->getRightChild());
  }
}

template <typename Key, typename Info>
bool Dictionary<Key, Info>::findByKey(const Key& key) const{
    //invoking the function findByKey on the root node
    if(getElemByKey(root, key)){
        //if the returned is not nullptr===exists
        //then we are returning the true
        return true;
    }
    //false if the elements does not exists
    return false;
}


template <typename Key, typename Info>
Key& Dictionary<Key, Info>::findMin(Node* node){
    //throwing exception if the tree is empty
    this->emptyDictException(*this);
    //while loop on the left edges to find the minial element
    //the while loop is proceeding until there is 
    //no left child, what means that it is leaf 
    while(node->getLeftChild() != nullptr){
        node = node->getLeftChild();
    }
    //returning the key of the minimal node
    return node->key;
}

//definition analogically the same as in the case of findMin
template <typename Key, typename Info>
Key& Dictionary<Key, Info>::findMax(Node* node){

    this->emptyDictException(*this);

    while(node->getRightChild() != nullptr){
        node = node->getRightChild();
    }
    return node->key;
}

template <typename Key, typename Info>
std::pair<Key, Key> Dictionary<Key, Info>::getExtremum(){
    //creating the instance of the std::pair to store
    //maximum and minimum
    std::pair<Key, Key> newPair;
    //assigning to the first member the minimal element key
    newPair.first = findMin(this->root);
    //assigning to the second member the maximal element key
    newPair.second = findMax(this->root);
    //returning the newly created pair
    return newPair;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::Node::getLeftChild(){
    return this->left;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::Node::getRightChild(){
    return this->right;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::Node::setLeftChild(Node* newNode){
    this->left = newNode;
    return this->left;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::Node::setRightChild(Node* newNode){
    this->right = newNode;
    return this->right;
}

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Iterator Dictionary<Key, Info>::begin(){
    return Iterator(root);
}  

template <typename Key, typename Info>
typename Dictionary<Key, Info>::Node* Dictionary<Key, Info>::copyDictionary(Node* node){

    //creating the new node to be copied
    Node* newNode = nullptr;
    if(node != nullptr){
        //creating the instance of node with a data of the node
        newNode = new Node(node->info, node->key);
        //increasing the number of the inserted elements
        ++numOfElem;
        //connecting the newNode with the subtrees of copied node
        //with the left one of the passed node
        newNode->setLeftChild( copyDictionary(node->getLeftChild()) );
        //with the right one of the passed node
        newNode->setRightChild( copyDictionary(node->getRightChild()) );
    }
    //returning the first root node of the tree
    return newNode;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::addDictionary(Node* source){

    //checking whether the passed source is not empty
    if(source== nullptr) return;
    //if the passed node does not exists in the dictionary then
    //it is inserted to the dictionary/tree
    if( !(this->findByKey(source->key)) ){
        this->insert(source->key, source->info);
    }
    //recursion is used to the traverse through the left and right subtrees of the nodes
    this->addDictionary(source->left);
    this->addDictionary(source->right);
}

template <typename Key, typename Info>
bool Dictionary<Key, Info>::compareNodes(Node* first, Node* second){

    //if both of the node is nullptr then is returned true
    if(first == nullptr && second == nullptr){
        return true;
    }
    //of one of the node is nullptr and the next one exists
    //then is returned true
    if(!first && second){
        return false;
    }else if(first && !second){
        return false;
    }
    //if the nodes are the same (have the same keys)
    //then the recusrsion is invoked 
    //moving to checking the next pair of nodes of the left and right subtree
    //returning true only when both of the methods return true
    if(first->key == second->key){
       return ( compareNodes(first->getLeftChild(), second->getLeftChild()) && compareNodes(first->getRightChild(), second->getRightChild()) );
    }else{
        //returning false in any other cases
        return false;
    }
}

//two instances of Dictionary class are treated as the same/equal
//when they have the same elements with the same keys
template <typename Key, typename Info>
bool Dictionary<Key, Info>::operator==(const Dictionary<Key, Info>& source){
    //usage of the compareNodes method
    //returning true only when the tree are have the same nodes
    if(compareNodes(this->root, source.root)){
        return true;
    }else{
        return false;
    }
}

template <typename Key, typename Info>
bool Dictionary<Key, Info>::operator!=(const Dictionary<Key, Info>& source){
    //usage of the operator==
     return !(*this == source);
}


template <typename Key, typename Info>
bool Dictionary<Key, Info>::operator>(const Dictionary<Key, Info>& source) const{
    //comparing the number of elements of each tree
    if(this->getNumOfElem() > source.getNumOfElem()) return true;
    return false;
}

template <typename Key, typename Info>
bool Dictionary<Key, Info>::operator<(const Dictionary<Key, Info>& source) const{
    //usage of the operator> to obtain the operator<
    if( !(*this > source)) return true;
    return false;
}

template <typename Key, typename Info>
bool Dictionary<Key, Info>::operator>=(const Dictionary<Key, Info>& source) const{
    //checking the length in the first step
    if(this->getNumOfElem() == source.getNumOfElem()) return true;
    //then if the statement above is not fulfilled then
    //using the operator>
    if( (*this > source) ) return true;
    return false;
}

template <typename Key, typename Info>
bool Dictionary<Key, Info>::operator<=(const Dictionary<Key, Info>& source) const{
    if(this->getNumOfElem() == source.getNumOfElem()) return true;
    if( !(*this > source) ) return true;
    return false;
}

template <typename Key, typename Info>
Dictionary<Key, Info>& Dictionary<Key, Info>::operator=(const Dictionary<Key, Info>& source){
    //usageo of the copyDictionary method for the
    //operator=
    this->clearDictionary(root);  //clearing the current dictionary
    this->numOfElem = 0;    //setting the number of elements to 0 
    this->root = copyDictionary(source.root);   //assigning the returned node to the root node
    return *this;
}

template <typename Key, typename Info>
Dictionary<Key, Info> Dictionary<Key, Info>::operator+(const Dictionary<Key, Info>& source){
    
    //constructing the new instance of the Dictionary
    Dictionary<Key, Info> newSource;
    
    //if the current dictionary and the passed one are empty then
    //is returned empty newSource
    if(this->isEmpty() && source.isEmpty()){
        return newSource;
    }
    //assinging the current dictionary to the newSource instance
    newSource = *this;
    //then, by the usage of the addDictionary method, is added the source elements to the
    //newSource (only the non-existing elements in the newSource)
    newSource.addDictionary(source.root);
    //return of the newSource instance
    return newSource;
}

template <typename Key, typename Info>
Dictionary<Key, Info>& Dictionary<Key, Info>::operator+=(const Dictionary<Key, Info>& source){
    //usage of the operator+ 
    *this = *this + source;
    return *this;
}

template <typename Key, typename Info>
Info& Dictionary<Key, Info>::operator[](const Key& key){
   
   //checkingth the exceptions 
   emptyDictException(*this);
   nonExistingException(*this, key);

    //usage of the getElemByKey method to retrive the node from the dictionary
   Node* node = getElemByKey(root, key);
   //returning the info of the node
   return node->info;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::nonExistingException(const Dictionary<Key, Info>& source, const Key& key){
 
 if( !(source.findByKey(key)) ){
       throw std::underflow_error("There is no element with a given Key.");
   }
   return;
}
template <typename Key, typename Info>
void Dictionary<Key, Info>::emptyDictException(const Dictionary<Key, Info>& source){
 
 if(source.isEmpty()){
       throw std::underflow_error("Dictionary is empty. Cannot get any info.");
   }
   return;
}


#endif 