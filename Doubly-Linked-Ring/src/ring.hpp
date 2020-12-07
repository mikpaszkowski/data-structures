#pragma once

#ifndef RING_HPP
#define RING_HPP

#include <stdexcept>
#include <iostream>
#include <utility>

template <typename Data>
class Ring {

private:
	//structure of the node
	struct Node{
		Data data;
		Node* next;
		Node* back;

		//constructor for the node
		Node(const Data& _data, Node* _next = nullptr, Node* _back = nullptr){
			data = _data;
			next = _next;
			back = _back;
		};
	};
	//pointer any
	Node* any;
	//length of the ring
	int ring_length;

public:

	class Iterator;
	//constructors
	Ring();
	Ring(const Ring<Data>& ring);
	//destructor
	~Ring();

	//methods for checking current statement of the ring
	//the length
	int getRingLength() const; 		
	bool isEmpty() const; 
	//helpful method checking whether the element with a given dataa exists			
	bool find(const Data& data); 	

	//push methods
	void push(const Data& data);
	void pushReverse(const Data& data);  
	bool pushBefore(const Data& newData, const Data& databefore);
	bool pushAfter(const Data& newData, const Data& dataAfter);
	bool pushBetween(const Data& newData, const Data& databefore, const Data& dataAfter);

	
	void print(); 					

	int countElem(const Data& data); 

	//basic methods for retriving data
	Data getDataBeforeElem(const Data& data);	
	Data getDataAfterElem(const Data& data);	
	Data getDataBetweenElem(const Data& dataBefore, const Data& dataAfter);	


	//basic removed methods
	bool removeByOccur(const Data& data, int occurence = 1);
	void removeAll(const Data& data);
	bool removeBefore(const Data& data);
	bool removeAfter(const Data& data);
	void clearRing(); 			

	void copyWholeRing(const Ring<Data>& copyRing);

	//OPERATORS

	Ring<Data>& operator=(const Ring<Data>& ring); 
	Ring<Data>& operator+(const Ring<Data>& ring); 
	Ring<Data>& operator+=(const Ring<Data>& ring);
	Ring<Data>& operator-(const Ring<Data>& ring); 
	Ring<Data>& operator-=(const Ring<Data>& ring); 

	//logical opearators

	bool operator==(const Ring<Data>& ring) const; 
	bool operator!=(const Ring<Data>& ring) const; 

	//comparing the rings lengths
	bool operator>=(const Ring<Data>& ring) const; 
	bool operator<=(const Ring<Data>& ring) const; 
	bool operator>(const Ring<Data>& ring) const; 
	bool operator<(const Ring<Data>& ring) const; 

	//subRing method which returns the subRing basis on the passed parameters
	//starting index from which the subRing is pushing, the length of it
	//direction - clockwise or counterclockwise
	Ring<Data> subRing(int startIndex, int length, bool direction, bool direction2) const;

	//methods for iterator
	Iterator begin() const;
	Iterator end() const;
};


template <typename Data>
class Ring<Data>::Iterator{

	private:
		Node* iter;

	public: 

		Iterator();
		Iterator(Node* temp);
		Iterator(const Iterator& it);

		~Iterator() = default;

		Data& getData() const;

		Iterator& operator++();
		Iterator operator++(int);
		Iterator& operator+(int);
		Iterator& operator-(int);
		Iterator& operator--();
		Iterator operator--(int);

		Iterator& operator=(const Iterator&);

		bool operator==(const Iterator& it) const;
		bool operator!=(const Iterator& it) const;
		Data& operator*();

		Node* getNode();
};



//=====================RING===============


template <typename Data>
Ring<Data>::Ring(){
	this->ring_length = 0;
	this->any = nullptr;
}

template <typename Data>
Ring<Data>::Ring(const Ring<Data>& copyRing){
	this->any = nullptr;
	this->ring_length = copyRing.getRingLength();
	*this = copyRing;
}

template <typename Data>
Ring<Data>::~Ring(){
	this->clearRing();
}

template <typename Data>
int Ring<Data>::getRingLength() const{
	return this->ring_length;
}

template <typename Data>
void Ring<Data>::copyWholeRing(const Ring<Data>& copyRing){

	if(!isEmpty()){
		this->clearRing();
	}
	if(copyRing.isEmpty()){

		this->clearRing();
		this->any = nullptr;	
		this->ring_length = 0;


	}else{
		this->clearRing();
		this->ring_length = 0;
		this->any = new Node(copyRing.any->data);
		typename Ring<Data>::Iterator copyIt = copyRing.begin();

		do{
			this->push((*copyIt));
			copyIt++;

		}while(copyIt != copyRing.begin());
	}
}

template <typename Data>
typename Ring<Data>::Iterator Ring<Data>::begin() const{

	return any ? Iterator(any) : Iterator(nullptr);
}


template <typename Data>
typename Ring<Data>::Iterator Ring<Data>::end() const{

	return any ? Iterator(any->back) : Iterator(nullptr);
}

template <typename Data>
void Ring<Data>::push(const Data& data){

	//creating new node to be inserted
	Node* newNode = new Node(data);
	
	if(isEmpty()){

		any = newNode;
		any->next = any;
		any->back = any;
		ring_length++;

	}else if(any->next == any && any->back == any){

		any->next = newNode;
		any->back = newNode;
		newNode->next = any;
		newNode->back = any;
		ring_length++;

	}else{
		
		newNode->back = any->back;
		newNode->next = any;
		any->back->next = newNode;
		any->back = newNode;
		ring_length++;
	}
}

template <typename Data>
void Ring<Data>::pushReverse(const Data& data){

	//creating new node to be inserted
	Node* newNode = new Node(data);
	
	if(isEmpty()){

		any = newNode;
		any->next = any;
		any->back = any;
		ring_length++;

	}else if(any->next == any && any->back == any){

		any->back = newNode;
		any->next = newNode;
		newNode->next = any;
		newNode->back = any;
		ring_length++;

	}else{
		
		newNode->back = any;
		newNode->next = any->next;
		any->next->back = newNode;
		any->next = newNode;
		ring_length++;
	}
}

template <typename Data>
bool Ring<Data>::pushBefore(const Data& newData, const Data& dataBefore){
	if(isEmpty()){
		throw std::overflow_error("Ring is empty. Cannot find any element with gicen data.");
	}
	if(!find(dataBefore)){
		throw std::overflow_error("Cannot find element with given data.");
	}

	Node* newNode = new Node(newData);
	Node* prev;

	typename Ring<Data>::Iterator it = (*this).begin();
	typename Ring<Data>::Iterator it_end = (*this).end();

	Node* curr = it.getNode();

	if(getRingLength() == 1){

		curr = it.getNode();
		newNode->next = curr;
		newNode->back = curr;
		curr->back = newNode;
		curr->next = newNode;
		++ring_length;
		return true;
	}

	if(getRingLength() == 2){

		if(curr->data == dataBefore){

			curr = it.getNode();
			newNode->next = curr;
			newNode->back = curr->next;
			curr->next->back = newNode;
			curr->back= newNode;
			++ring_length;
			return true;

		}else if(curr->next->data == dataBefore){

			curr = it_end.getNode();
			newNode->next = curr;
			newNode->back = curr->back;
			curr->next->next= newNode;
			curr->back= newNode;
			++ring_length;
			return true;
		}
		return false;
	}

	do{

		if((*it) == dataBefore){

			curr = it.getNode();
			prev = curr->back;
			newNode->next = curr;
			newNode->back = prev;
			prev->next = newNode;
			curr->back = newNode;
			++ring_length;
			return true;
		}

		it++;

	}while(it != this->begin());
	return false;
}

template <typename Data>
bool Ring<Data>::pushAfter(const Data& newData, const Data& dataAfter){
	if(isEmpty()){
		throw std::overflow_error("Ring is empty. Cannot find any element with gicen data.");
	}
	if(!find(dataAfter)){
		throw std::overflow_error("Cannot find element with given data.");
	}

	Node* newNode = new Node(newData);
	Node* next;

	typename Ring<Data>::Iterator it = (*this).begin();
	typename Ring<Data>::Iterator it_end = (*this).end();

	Node* curr = it.getNode();

	if(getRingLength() == 1){

		curr = it.getNode();
		newNode->next = curr;
		newNode->back = curr;
		curr->back = newNode;
		curr->next = newNode;
		++ring_length;
		return true;
	}

	if(getRingLength() == 2){

		if(curr->data == dataAfter){

			curr = it.getNode();
			newNode->back = curr;
			newNode->next= curr->next;
			curr->next->back = newNode;
			curr->next= newNode;
			++ring_length;
			return true;

		}else if(curr->next->data == dataAfter){

			curr = it_end.getNode();
			newNode->back = curr;
			newNode->next = curr->back;
			curr->next->next= newNode;
			curr->next= newNode;
			++ring_length;
			return true;
		}
		return false;
	}

	do{

		if((*it) == dataAfter){

			curr = it.getNode();
			next = curr->next;

			newNode->next = next;
			newNode->back = curr;
			curr->next = newNode;
			next->back = newNode;
			++ring_length;
			return true;
		}

		it++;

	}while(it != this->begin());
	return false;
}

template <typename Data>
bool Ring<Data>::pushBetween(const Data& newData, const Data& dataBefore, const Data& dataAfter){
	if(isEmpty()){
		throw std::overflow_error("Ring is empty. Cannot find any element with gicen data.");
	}
	if(getRingLength() == 1){
		throw std::underflow_error("Not enough elements in Ring to execute.");
	}
	if(!find(dataBefore) && !(find(dataAfter))){
		throw std::overflow_error("Cannot find element with given data.");
	}

	if(this->getDataAfterElem(dataAfter) == dataBefore){
		throw std::overflow_error("Given elements are not next to each other.");
	}

	//creating the newNode to be pushed to the ring
	Node* newNode = new Node(newData);
	Node* after;

	typename Ring<Data>::Iterator it = (*this).begin();
	typename Ring<Data>::Iterator it_end = (*this).end();

	Node* curr = it.getNode();

	if(getRingLength() == 2){

		if((*it) == dataAfter && (*it_end) == dataBefore){

			curr = it.getNode();
			newNode->back = curr;
			newNode->next= curr->next;
			curr->next->back = newNode;
			curr->next= newNode;
			++ring_length;
			return true;

		}else if((*it) == dataBefore && (*it_end) == dataAfter){

			curr = it_end.getNode();
			newNode->back = curr;
			newNode->next = curr->back;
			curr->next->next= newNode;
			curr->next= newNode;
			++ring_length;
			return true;
		}
		return false;
	}
	typename Ring<Data>::Iterator next_it = (*this).begin();

	//decrementing the next_it iterator to check the current and the previous elements
	//by the iterators
	--next_it;
	do{
		if((*it) == dataAfter && (*next_it) == dataBefore){
			curr = it.getNode();
			after = next_it.getNode();
			newNode->next = curr;
			newNode->back = after;
			after->next = newNode;
			curr->back = newNode;
			++ring_length;
			return true;
		}
		it++;
		next_it++;
	}while(it != this->begin());
	
	return false;
}

// 	void reverseDirection();


template <typename Data>
void Ring<Data>::clearRing(){

	if(isEmpty()) return;

	Node* curr = any;
	Node* temp = any;

	do{
		temp = curr;
		curr = curr->next;
		delete temp;
		--ring_length;
	}while(curr != any);

	any = nullptr;
	ring_length = 0;
}

template <typename Data>
int Ring<Data>::countElem(const Data& data) {

	if(isEmpty()){
		throw std::underflow_error("Ring is empty. Cannot count any element.");
	}

	int numOfElem = 0;
	typename Ring<Data>::Iterator it = (*this).begin();

	do{
		if((*it) == data){
			++numOfElem;
		}
		it++;
	}while(it != this->begin());

	return numOfElem;
}


template <typename Data>
Data Ring<Data>::getDataBeforeElem(const Data& dataBefore){
	if(isEmpty()){
		throw std::underflow_error("Ring is empty. Cannot retrive any data");
	}
	if(!find(dataBefore)){
		throw std::overflow_error("Cannot find element with given data.");
	}

	typename Ring<Data>::Iterator it = (*this).begin();

	do{
		if((*it) == dataBefore){
			--it;
			return it.getData();
		}
		it++;
	}while(it != this->begin());

	throw std::runtime_error("Element has not been found.");
}

template <typename Data>
Data Ring<Data>::getDataAfterElem(const Data& dataAfter){
	if(isEmpty()){
		throw std::underflow_error("Ring is empty. Cannot retrive any data");
	}
	if(!find(dataAfter)){
		throw std::overflow_error("Cannot find element with given data.");
	}

	typename Ring<Data>::Iterator it = (*this).begin();

	do{
		if((*it) == dataAfter){
			++it;
			return it.getData();
		}
		it++;
	}while(it != this->begin());

	throw std::runtime_error("Element has not been found.");
}

template <typename Data>
Data Ring<Data>::getDataBetweenElem(const Data& dataBefore, const Data& dataAfter){
	if(isEmpty()){
		throw std::underflow_error("Ring is empty. Cannot retrive any data");
	}
	if(getRingLength() == 2){
		throw std::underflow_error("Not enough elements in Ring to execute.");
	}
	if(!find(dataBefore) && !(find(dataAfter))){
		throw std::overflow_error("Cannot find element with given data.");
	}

	if(this->getDataAfterElem(dataAfter) == dataBefore){
		throw std::overflow_error("Given elements arenot next to each other.");
	}

	typename Ring<Data>::Iterator it = (*this).begin();
	typename Ring<Data>::Iterator next_it = (*this).begin();
	typename Ring<Data>::Iterator between_it = (*this).begin();

	--next_it;
	--next_it;
	--between_it;
	do{
		if((*it) == dataBefore && (*next_it) == dataAfter){
			return between_it.getData();
		}
		it++;
		next_it++;
		between_it++;
	}while(it != this->begin());

	throw std::runtime_error("Element has not been found.");
}


template <typename Data>
bool Ring<Data>::removeByOccur(const Data& data, int occurenceToBeDelted){
	if(isEmpty()){
		throw std::underflow_error("Ring is empty. Cannot remove any elements");
	}
	if(occurenceToBeDelted <= 0){
		throw std::out_of_range("Invalid argument - occurence.");
	}

	if( !(this->find(data)) ){
		throw std::underflow_error("Elements with a given data does not exists.");
	}

	if( (getRingLength() == 1) && (any->data == data) && (occurenceToBeDelted == 1) ){
		delete any;
		any = nullptr;
		--ring_length;
		return true;
	}

	Node* curr = any;
	Node* temp = any;
	int numOfOccurence = 0;

	do{
		if(curr->data == data){
			++numOfOccurence;

			if(numOfOccurence == occurenceToBeDelted){

				if(curr == any){
					temp = curr;
					curr->back->next = curr->next;
					curr->next->back = curr->back;
					curr = curr->next;
					any = curr->next;
					delete temp;
					--ring_length;
					return true;
				}else{
					temp = curr;
					curr->back->next = curr->next;
					curr->next->back = curr->back;
					curr = curr->next;
					delete temp;
					--ring_length;
					return true;
				}
			}
		}else{
			curr = curr->next;
		}

	}while(curr != any);

return false;
}

template <typename Data>
void Ring<Data>::removeAll(const Data& data){
	if(isEmpty()){
		throw std::underflow_error("Ring is empty. Cannot remove any elements");
	}

	if(getRingLength() == 1 && any->data == data){
		delete any;
		any = nullptr;
		--ring_length;
		return;
	}

	Node* curr = any;
	Node* temp = any;
	int occurance = 0;

	do{
		if(curr->data == data){
			++occurance;
			temp = curr;
			curr->back->next = curr->next;
			curr->next->back = curr->back;
			curr = curr->next;
			delete temp;
			--ring_length;
		}else{
			curr = curr->next;
		}

	}while(curr != any);

	if(!occurance){
		throw std::overflow_error("Cannot remove non-existing elements.");
	}
}

template <typename Data>
bool Ring<Data>::removeBefore(const Data& dataBefore){

	if(isEmpty()){
		throw std::underflow_error("Ring is empty. Cannot delete any data");
	}
	if(!find(dataBefore)){
		throw std::overflow_error("Cannot delete element with given data.");
	}
	if(getRingLength() == 1){
		throw std::underflow_error("Ring has only one element.");
	}

	typename Ring<Data>::Iterator it = (*this).begin();

	Node* curr = it.getNode();
	Node* prev = curr->back;
	Node* temp;

	if(getRingLength() == 2){

		if(curr->data == dataBefore){

			temp = prev;
			any->next = any;
			any->back = any;
			delete temp;
			--ring_length;
			return true;

		}else if(curr->next->data == dataBefore){

			temp = prev;
			any = curr;
			any->next = any;
			any->back = any;
				
			delete temp;
			--ring_length;
			return true;
		}
		return false;
	}

	do{

		if((*it) == dataBefore && (*it) == any->data){

			curr = it.getNode();
			prev = curr->back;
			temp = prev;
			any = curr;

			curr->back = prev->back->back;
			prev->back->next = curr;

			delete temp;
			
			--ring_length;
			return true;
		}else if((*it) == dataBefore){
	
			curr = it.getNode();

			prev = curr->back;
			temp = prev;

			curr->back = prev->back->back;
			prev->back->next = curr;

			delete temp;
			
			--ring_length;
			return true;
		}
		it++;

	}while(it != this->begin());
	return false;

}

template <typename Data>
bool Ring<Data>::removeAfter(const Data& dataAfter){

	if(isEmpty()){
		throw std::underflow_error("Ring is empty. Cannot delete any data");
	}
	if(!find(dataAfter)){
		throw std::overflow_error("Cannot delete element with given data.");
	}
	if(getRingLength() == 1){
		throw std::underflow_error("Ring has only one element.");
	}

	typename Ring<Data>::Iterator it = (*this).begin();

	Node* curr = it.getNode();
	Node* prev = curr->back;
	Node* next = curr->next;
	Node* temp;

	if(getRingLength() == 2){

		if(curr->data == dataAfter){

			temp = prev;
			any->next = any;
			any->back = any;
			delete temp;
			--ring_length;
			return true;

		}else if(curr->next->data == dataAfter){

			temp = prev;
			any = curr;
			any->next = any;
			any->back = any;
				
			delete temp;
			--ring_length;
			return true;
		}
		return false;
	}

	do{

		if((*it) == dataAfter && curr->next->data == dataAfter){
			
			curr = it.getNode();
			next = curr->next;
			temp = next;
			any = curr;

			curr->next = next->next;
			next->next->back = curr;

			delete temp;
			
			--ring_length;
			return true;
		}else if((*it) == dataAfter){
	
			curr = it.getNode();
			next = curr->next;
			temp = next;

			curr->next = next->next;
			next->next->back = curr;

			delete temp;
			
			--ring_length;
			return true;
		}
		it++;

	}while(it != this->begin());
	return false;

}

// 	bool removeAfter(const Data& data);
// 	bool removeBetween(const Data&, const Data&);

template <typename Data>
bool Ring<Data>::isEmpty() const{
	return (any == nullptr);
}


template <typename Data>
bool Ring<Data>::find(const Data& data){
	if(isEmpty()){
		throw std::underflow_error("Ring is empty");
	}

	typename Ring<Data>::Iterator it = (*this).begin();

	do{
		if((*it) == data) {
			return true;
		}
		it++;

	}while(it != this->begin());

	return false;
}


template <typename Data>
void Ring<Data>::print(){

	if(isEmpty()){
		throw std::underflow_error("Ring is empty. Cannot print the ring.");
	}
	typename Ring<Data>::Iterator it = (*this).begin();

	do{
		std::cout << (*it) << " ";
		it++;

	}while(it != this->begin());
	std::cout << std::endl;
}

template <typename Data>
Ring<Data>& Ring<Data>::operator=(const Ring<Data>& ring){

	if(this == &ring){
		return *this;	
	}
	this->clearRing();
	this->ring_length = 0;
	if(ring.isEmpty()){
		return *this;
	}
	typename Ring<Data>::Iterator it = ring.begin();
	
	do{
		push(it.getData());
		it++;
	}while(it != ring.begin());

	return *this;
}

template <typename Data>
Ring<Data>& Ring<Data>::operator+=(const Ring<Data>& copyRing){

	*this = *this + copyRing;
	return *this;
}

template <typename Data>
Ring<Data>& Ring<Data>::operator+(const Ring<Data>& copyRing){

	if(copyRing.isEmpty()){
		return *this;
	}

	typename Ring<Data>::Iterator it = copyRing.begin();

	do{
		this->push((*it));
		it++;
	}while(it != copyRing.begin());

	return *this;
}


template <typename Data>
Ring<Data>& Ring<Data>::operator-(const Ring<Data>& copyRing){

	if(copyRing.isEmpty()){
		return *this;
	}

	typename Ring<Data>::Iterator it = copyRing.begin();

	int numOfRemovedElem = 0;

	do{
		if(this->find((*it))){
			this->removeByOccur((*it));
			++numOfRemovedElem;
		}
		if(numOfRemovedElem == this->getRingLength()){
			break;
		}
		it++;
	}while(it != copyRing.begin());

	return *this;
}

template <typename Data>
Ring<Data>& Ring<Data>::operator-=(const Ring<Data>& copyRing){

	*this = *this - copyRing;
	return *this;
}

template <typename Data>
bool Ring<Data>::operator==(const Ring<Data>& copyRing) const{

	if(this->getRingLength() != copyRing.getRingLength()){
		return false;
	}

	if(this->isEmpty() && copyRing.isEmpty()){
		return true;
	}

	typename Ring<Data>::Iterator currIt = (*this).begin();

	typename Ring<Data>::Iterator copyIt = copyRing.begin();


	do{

		if((*currIt) != (*copyIt)){
			return false;
		}
		currIt++;
		copyIt++;
	}while((currIt != this->begin()) && (copyIt != copyRing.begin()));

	return true;
}

template <typename Data>
bool Ring<Data>::operator!=(const Ring<Data>& copyRing) const{

	if(this->getRingLength() != copyRing.getRingLength()){
		return true;
	}

	if(this->isEmpty() && copyRing.isEmpty()){
		return false;
	}

	typename Ring<Data>::Iterator currIt = (*this).begin();

	typename Ring<Data>::Iterator copyIt = copyRing.begin();


	do{

		if((*currIt) != (*copyIt)){
			return true;
		}
		currIt++;
		copyIt++;
	}while((currIt != this->begin()) && (copyIt != copyRing.begin()));

	return false;
}

template <typename Data>
bool Ring<Data>::operator>(const Ring<Data>& copyRing) const{
	if(this->getRingLength() > copyRing.getRingLength()){
		return true;
	}
	return false;
}

template <typename Data>
bool Ring<Data>::operator<(const Ring<Data>& copyRing) const{
	if(this->getRingLength() < copyRing.getRingLength()){
		return true;
	}
	return false;
}

template <typename Data>
bool Ring<Data>::operator<=(const Ring<Data>& copyRing) const{
	if(this->getRingLength() <= copyRing.getRingLength()){
		return true;
	}
	return false;
}

template <typename Data>
bool Ring<Data>::operator>=(const Ring<Data>& copyRing) const{
	if(this->getRingLength() >= copyRing.getRingLength()){
		return true;
	}
	return false;
}

template <typename Data>
typename Ring<Data>::Node* Ring<Data>::Iterator::getNode(){
	return this->iter;
}


//===============Iterator=====================



template <typename Data>
Data& Ring<Data>::Iterator::getData() const{
	return iter->data;
}

//iterator constructors
template <typename Data>
Ring<Data>::Iterator::Iterator(){
	iter = nullptr;
}

template <typename Data>
Ring<Data>::Iterator::Iterator(Node* node){
	iter = node;
}

// //CHECK
// //copy constructor
template <typename Data>
Ring<Data>::Iterator::Iterator(const Iterator& it){
	*this = it;
}

template <typename Data>
typename Ring<Data>::Iterator& Ring<Data>::Iterator::operator++(){
	iter = iter->next;

	return *this;
}

template <typename Data>
typename Ring<Data>::Iterator Ring<Data>::Iterator::operator++(int){
	Iterator curr(iter);
	iter = iter->next;
	return curr;
}

//dokonczyc================FROM==========================

template <typename Data>
typename Ring<Data>::Iterator& Ring<Data>::Iterator::operator+(int num){
	Iterator curr(iter);
	for(int i = 0; i < num; i++){
		curr.iter = curr.iter->next;
	}
	return curr;
}

template <typename Data>
typename Ring<Data>::Iterator& Ring<Data>::Iterator::operator--(){
	iter = iter->back;
	return *this;
}

template <typename Data>
typename Ring<Data>::Iterator Ring<Data>::Iterator::operator--(int){
	Iterator curr(iter);
	iter = iter->back;
	return curr;
}

template <typename Data>
typename Ring<Data>::Iterator& Ring<Data>::Iterator::operator-(int num){
	Iterator curr(iter);
	for(int i = 0; i < num; i++){
		curr.iter = curr.iter->back;
	}
	return curr;
}


template <typename Data>
typename Ring<Data>::Iterator& Ring<Data>::Iterator::operator=(const Iterator& iterator){
	iter = iterator.iter;

	return *this;
}

template <typename Data>
bool Ring<Data>::Iterator::operator==(const Iterator& it) const{
	return (iter == it.iter);
}

template <typename Data>
bool Ring<Data>::Iterator::operator!=(const Iterator& it) const{
	return (iter != it.iter);
}

template <typename Data>
Data& Ring<Data>::Iterator::operator*(){
	return iter->data;
}

template <typename Data>
Ring<Data> Ring<Data>::subRing(int startIndex, int step, bool direction, bool direction2) const{

	if(startIndex < 0 || step < 0){
		throw std::invalid_argument("Invalid passed arguments.");
	}
	if(isEmpty()){
		throw std::underflow_error("Ring is empty. Cannot retrive any subring");
	}

	Ring<Data> newRing;

	typename Ring<Data>::Iterator it = (*this).begin();

	int currentIndex = 0;
	int currentLength = 0;

	do{

		if(direction){
			//checking if the current element has the same "index"
			if(currentIndex == startIndex){
				if(direction2){
					newRing.push((*it));
					++currentLength;
					it++;
				}else{
					newRing.push((*it));
					++currentLength;
					--it;
				}
				//if the retrived subRing length is equal to the step then
				//the if statement is broken and newRing is returned
				if(currentLength == step) break;
			}else{
				++currentIndex;
				it++;
			}
		}else{
			if(currentIndex == startIndex){
				if(direction2){
					newRing.push((*it));
					++currentLength;
					it++;
				}else{
					newRing.push((*it));
					++currentLength;
					--it;
				}
				if(currentLength == step) break;
			}else{
				++currentIndex;
				--it;
			}
		}
	}while(true); //the process controls only the number of pushed elements
	return newRing;
}


template <typename Data>
std::pair<Ring<Data>, Ring<Data>> split(const Ring<Data>& source,
int startIndex, int length, bool direction,
int step1, bool direction1, int step2, bool direction2){

	//firstly checking the passed parameters
	//and throw an exception
	if(source.isEmpty()){
		throw std::overflow_error("source IS EMPTY.");
	}
	if(startIndex < 0 || length <= 0 || step1 < 0 || step2 < 0){
		throw std::invalid_argument("Invalid arguments passed.");
	}

	//creating the instance of the std::pair where should placed the two rings
	std::pair< Ring<Data>, Ring<Data> > ringBuffer;

	//creating two empty rings where will be stored part of the source ring
	Ring<Data> firstRing;
	Ring<Data> secondRing;

	//number of visited elements in the iterating
	//when its value is equal to the passed length then the process of splitting is done
	int visitedElem = 0;

	//variable which helps to stop at element from which
	//we start to put elements to each subRings
	int currentIndex = 0;
	
	//variable which controls the step length of subRings
	//inserted to the firstRing and secondRing
	int currLengthFirst = 0;
	int currLengthSecond = 0;

	//bollean variables which controls the whole process
	//of iteration and splitting the source ring
	bool firstProcess = true;
	bool secondProcess = false;
	bool processFinish = false;

	//iterator begin
	typename Ring<Data>::Iterator it = source.begin();

	//do..while loop which iterates through the
	//ring and breaks when the element with given startIndex
	//is found
	do{	
		//if the direction is true then the itaration
		//is clockwise
		if(direction){
			++currentIndex;
			it++;
		}else{
			//if the direction is false then the itaration
			//is counterclockwise
			++currentIndex;
			--it;
		}
		//each iteration increase the number of visited elements
		++visitedElem;
	}while(currentIndex != startIndex);

	//while loop starts with default processFinish set to false
	while(!processFinish){

		//the whole source ring is splitted alternately
		//once in the firstRing and once in the secondRIng
		if(firstProcess){
				//checking if the current element has the same "index"

			//if the direction1 is true then the elements are retrived clockwise
			if(direction1){
				firstRing.push((*it));
				++currLengthFirst;
				++it;
			}else{
				//if it's not then the elements are pushed counterclockwise
				firstRing.pushReverse((*it));
				++currLengthFirst;
				++it;
			}
			//checking if the retrived subRing to the firstRing
			//has the length of step1
			if(currLengthFirst == step1) {
				//if it's true then then the boolean variables are set to the opposite
				//to started retriving the data to the secondRing
				currLengthFirst = 0;
				firstProcess = !firstProcess;
				secondProcess = !secondProcess;
			}
			//incrementing the visitedElem variable
			++visitedElem;
		}

	//analogically the same
		if(secondProcess){

			if(direction2){

				secondRing.push((*it));
				++currLengthSecond;
				it++;
			}else{

				secondRing.pushReverse((*it));
				++currLengthSecond;
				it++;
			}

			if(currLengthSecond == step2) {
				currLengthSecond = 0;
				firstProcess = !firstProcess;
				secondProcess = !secondProcess;
			}
			++visitedElem;
		}

	//checking if the number of visited elements
	//is equal to the length
		if(visitedElem == length){
			//if it's true then the process is stopped
			processFinish = true;
		}
	}
	//pushing created rings to the ringBuffer instance of std::pair
	ringBuffer.first = firstRing;
	ringBuffer.second = secondRing;
	return ringBuffer;
}

#endif // !RING_HPP