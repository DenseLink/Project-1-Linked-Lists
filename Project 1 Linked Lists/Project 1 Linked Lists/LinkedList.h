#pragma once
#include <iostream>
#include <istream>
#include <fstream>
#include <deque>
#include <exception>
#include <stdexcept>
#include <vector>
#include <string>
#include "leaker.h"

using namespace std;

template <typename T>
class LinkedList
{
public:
	struct Node
	{
		T data;
		Node* next = nullptr;
		Node* prev = nullptr;
	};
private:
	/*Node* next;
	Node* prev;*/

	Node* head;
	Node* tail;
	Node* temp;
	unsigned int nodeCount;
	Node* currentNode;
public:
	//int nodesize;
	//Behaviors
	void PrintForward() const;
	void PrintReverse() const;
	void PrintForwardRecursive(const Node* node) const;
	void PrintReverseRecursive(const Node* node) const;

	//Accessors
	unsigned int NodeCount() const;
	void FindAll(vector<Node*>& outData, const T& value) const;
	const Node* Find(const T& data) const;
	Node* Find(const T& data);
	const Node* GetNode(unsigned int index) const;
	Node* GetNode(unsigned int index);
	Node* Head();
	const Node* Head() const;
	Node* Tail();
	const Node* Tail() const;
	//Insertion
	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	void InsertAfter(Node* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);
	//Removal
	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T& data);
	bool RemoveAt(int index);
	void Clear();
	//Operators
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	bool operator==(const LinkedList<T>& rhs) const;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);
	//Construction/Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	~LinkedList();

};

template<typename T>
LinkedList<T>::LinkedList()
{
	/*data = NULL;
	next = nullptr;
	prev = nullptr;*/
	nodeCount = 0;
	head = nullptr;
	tail = nullptr;
	//temp = nullptr;
	currentNode = nullptr;
	//nodesize=0;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list)
{

	//Node* temp2 = head;
	Node* temp1 = list.head;
	//Node* temp3 = head;
	//Node* newHead = temp2;
	while (temp1 != nullptr)
	{
		AddTail(temp1->data);
		temp1 = temp1->next;
	}
	//while (temp1 != nullptr)
	//	//for (unsigned int i = 0; i < nodeCount1; i++)
	//{
	//	Node* bNode = new Node;
	//	//if node is not a lone head
	//	if (temp1->next != nullptr && temp1->prev == nullptr)
	//	{


	//		bNode->data = temp1->data;
	//		bNode->prev = nullptr;
	//		bNode->next = nullptr;
	//		temp1 = temp1->next;

	//		temp2 = bNode;
	//		newHead = bNode;
	//	}
	//	//if node is between head and tail
	//	else if (temp1->next != nullptr && temp1->prev != nullptr)
	//	{
	//		bNode->data = temp1->data;
	//		bNode->prev = temp2;
	//		bNode->next = nullptr;
	//		//temp3->next = bNode;
	//		temp2->next = bNode;
	//		temp1 = temp1->next;
	//		temp2 = temp2->next;

	//	}
	//	//if node is a tail
	//	else if (temp1->next == nullptr && temp1->prev != nullptr)
	//	{
	//		bNode->data = temp1->data;
	//		bNode->next = nullptr;
	//		bNode->prev = temp2;
	//		temp2->next = bNode;
	//		temp2 = newHead;
	//		temp1 = temp1->next;
	//	}

	//}

}

template<typename T>
void LinkedList<T>::PrintForward() const
{

	Node* temp1 = head;
	//Node* deletethis = new Node;
	//deletethis->next = nullptr;
	//deletethis->prev = nullptr;

	while (temp1->next != nullptr)
	{
		if (temp1->next != nullptr)
		{
			//for (unsigned int i; i = 0; i++)
			//{
			cout << temp1->data << endl;
			//}
			temp1 = temp1->next;
		}
	}
	if (temp1->next == nullptr)
	{
		cout << temp1->data << endl;
	}
	//temp1 = temp1->next;
	//temp1 = deletethis;
	//delete temp1;// = nullptr;
}

template<typename T>
void LinkedList<T>::PrintReverse() const
{
	//Node* temp1 = new Node;
	Node* temp1 = tail;
	//Node* deletethis = new Node;
	//deletethis->next = nullptr;
	//deletethis->prev = nullptr;
	while (temp1->prev != nullptr)
	{
		if (temp1->prev != nullptr)
		{
			cout << temp1->data << endl;
			temp1 = temp1->prev;
		}
	}
	if (temp1->prev == nullptr)
	{
		cout << temp1->data << endl;
	}
	//temp1 = temp1->next;
	//temp1 = deletethis;
	//delete temp1;
}

template<typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const
{

	if (node != nullptr)
	{
		cout << node->data << endl;
		node = node->next;
		//node = node->next;
		PrintForwardRecursive(node);
	}
	/*else if (temp1->data != node->data)
	{
		temp1 = temp1->next;
		PrintForwardRecursive(node);
	}*/
}

template<typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const
{
	{

		if (node != nullptr)
		{
			cout << node->data << endl;
			node = node->prev;
			//node = node->next;
			PrintReverseRecursive(node);
		}
		/*else if (temp1->data != node->data)
		{
			temp1 = temp1->next;
			PrintForwardRecursive(node);
		}*/
	}
}

template<typename T>
unsigned int LinkedList<T>::NodeCount() const
{
	return nodeCount;
}

template<typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const
{
	//Major revision being that I don't need to augment the actual node.
	//Node* temp1 = head;// new Node;
	//temp1 = head;
	//Node* temp2 = head;// new Node;
	//Node* temp2 = new Node;
	Node* nNode = head;
	while (nNode->next != nullptr)
	{
		//if this is the first node in this find all copy function
		if (nNode == nullptr && value == nNode->data)
		{
			nNode->data = value;
			//nNode->prev = nullptr;
			//nNode->next = nullptr;
			outData.push_back(nNode);
			//temp2 = nNode;
		}
		// if this node is not the first node nor is it the last in this list
		else if (value == nNode->data)
		{
			nNode->data = value;
			//temp2->next = nNode;
			//nNode->prev = temp2;
			//nNode->next = nullptr;
			outData.push_back(nNode);
			//temp2 = temp2->next;
		}
		nNode = nNode->next;
	}
	if (nNode->next == nullptr && value == nNode->data)
	{
		nNode->data = value;
		//temp2->next = nNode;
		//nNode->prev = temp2;
		//nNode->next = nullptr;
		outData.push_back(nNode);
	}
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const //LOOK HERE FOR DEFINING NODES
//const Node* LinkedList<T>::Find(const T& data) const
{
	Node* temp1 = head;
	while (temp1->data != data && temp1->next != nullptr) //This while loop will go through all nodes with the exception of the final one and check to see if data = Node data
	{
		temp1 = temp1->next;
	}
	if (temp1->next == nullptr && data != temp1->data) //This if loop will do the same thing as the while loop but it will be limited to the final node
	{
		return NULL;
	}
	else //This else statement will activate if the while loop stops short and the if statement is not activated and return temp1.
	{
		return temp1;
	}
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data)
{

	Node* temp1 = head;
	while (temp1->data != data && temp1->next != nullptr) //This while loop will go through all nodes with the exception of the final one and check to see if data = Node data
	{
		temp1 = temp1->next;
	}
	if (temp1->next == nullptr && data != temp1->data) //This if loop will do the same thing as the while loop but it will be limited to the final node
	{
		return NULL;
	}
	else //This else statement will activate if the while loop stops short and the if statement is not activated and return temp1.
	{
		return temp1;
	}
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const
{
	Node* temp1 = head;
	int tempNodeCount;
	tempNodeCount = 0;
	try
	{
		for (unsigned int i = 0; i < index; i++)
		{
			if (temp1->next == nullptr)
			{
				throw runtime_error("index is out of range.");
			}

			else
			{
				temp1 = temp1->next;
				tempNodeCount++;
			}
		}
	}
	catch (runtime_error& excpt) {
		cout << excpt.what() << endl;
	}
	return temp1;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index)
{
	Node* temp1 = head;
	int tempNodeCount;
	tempNodeCount = 0;
	try
	{
		for (unsigned int i = 0; i < index; i++)
		{
			if (temp1->next == nullptr)
			{
				throw runtime_error("index is out of range.");
			}

			else
			{
				temp1 = temp1->next;
				tempNodeCount++;
			}
		}
	}
	catch (runtime_error& excpt) {
		cout << excpt.what() << endl;
	}
	return temp1;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head()
{
	return head;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const
{
	Node* temp1 = new Node;
	temp1 = head;
	return temp1;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail()
{
	return tail;
}

template<typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const
{
	Node* temp1 = new Node;
	temp1 = tail;
	return temp1;
}

template<typename T>
void LinkedList<T>::AddHead(const T& pdata)
{
	//this -> data = data; 
	//Node* data = data; // can i use either?
	//if there is nothing present within the linked list set the node here.
	if (head == nullptr)
	{

		Node* nNode = new Node;
		nNode->prev = nullptr; //the arrows are used when accessing data from pointers
		nNode->next = nullptr;
		nNode->data = pdata; // the period is used when accessing memory from nonpointers
		head = nNode;
		tail = nNode;
		//currentNode = nNode;
		nodeCount++;
	}
	//Create a head if there are already objects in this linked list.
	else
	{
		//I need to save the pointer information prior to creating the new node
			//Node* temp = prev;

		// I then need to establish the new node
		Node* nNode = new Node;
		nNode->prev = nullptr;
		nNode->next = head; //I am making sure the new head has a viable link to the next node
		nNode->data = pdata;
		//How do I set the 'previous' pointer in the original header to the new head?
		head->prev = nNode;
		//Node* currentNode.prev= nNode;
		//Node* currentNode = nullptr; //Here I am returning the pointer to null so it has a clean slate for the next time I use it
		head = nNode;
		//currentNode = head;
		nodeCount++;
	}



}

template<typename T>
void LinkedList<T>::AddTail(const T& pdata)
{
	Node* nNode = new Node;

	//If there is no tail already
	if (tail == nullptr)
	{
		//Node* nNode = new Node;
		tail = nNode;
		//head = tail;
		nNode->prev = nullptr; //the arrows are used when accessing data from pointers
		nNode->next = nullptr;
		nNode->data = pdata; // the period is used when accessing memory from nonpointers
		head = nNode;
		//tail = nNode;
		//currentNode = nNode;
		nodeCount++;
	}
	//If there is a tail already
	else
	{
		//I need to save the pointer information prior to creating the new node
			//Node* temp = prev;
		//currentNode = tail;
		// I then need to establish the new node
		//Node* nNode = new Node;
		nNode->prev = tail;
		nNode->next = nullptr;
		nNode->data = pdata;
		//nNode = tail;
		//nNode = nNode->next;
		//nNode->prev = tail;
		//nNode->next = nullptr; //I am making sure the new head has a viable link to the next node
		//nNode->data = pdata;
		//How do I set the 'previous' pointer in the original header to the new head?
		tail->next = nNode;
		//Node* currentNode.prev= nNode;
		//Node* currentNode = nullptr; //Here I am returning the pointer to null so it has a clean slate for the next time I use it
		tail = nNode;
		nodeCount++;
	}
}
template<typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count)
{



	//I shall now establish the parameters of the new Node
	//nNode->data = data->at(0);
	//nNode->next = head;
	//nNode->prev = nullptr;
	//head->prev = nNode;
	//head = nNode;
	//currentNode = head;
	//nodeCount++;

	//Node* temp1 = head;
	//Node* temp2 = head;
	//I shall now deal with the rest of the array
	unsigned int thisIsAnnoying;
	thisIsAnnoying = count - 1;

	for (unsigned int i = 0; i < count; i++)
	{

		Node* nNode = new Node;
		nNode->data = data[thisIsAnnoying];
		thisIsAnnoying--;
		nNode->next = head;
		nNode->prev = nullptr;
		head->prev = nNode;
		head = nNode;
		//temp2 = temp1;//I'm saving the data that comes after the node insert as temp2
		//temp2 = temp2->next;

		//nNode->data = data->at(i);
		/*nNode->prev = temp1;
		nNode->next = temp2;

		temp1->next = nNode;
		temp2->prev = nNode;

		temp1 = nNode;
		temp2 = nNode;*/
		//cout << nNode->data << endl;
		nodeCount++;
	}
	//nNode = nNode->next;
	//temp1 = nNode;
	//temp2 = nNode;

}

template<typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count)
{

	//Node* temp1 = tail;
	//Node* temp2 = tail;
	//I shall now deal with the rest of the array
	for (unsigned int i = 0; i < count; i++)
	{
		Node* nNode = new Node;
		nNode->data = data[i];
		nNode->next = nullptr;
		nNode->prev = tail;
		tail->next = nNode;
		tail = nNode;



		/*	tail = nNode;
			temp1 = tail;*/
		nodeCount++;
	}


}

template<typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data)
{
	//node = head; //was temp1 throughout this function
	Node* temp2 = new Node;
	Node* reference = head;
	Node* temp1 = head;


	while (temp1 != nullptr) {
		//if data does not match
		if (reference->data != node->data)
		{
			//node = node->next;
			reference = reference->next;
			temp1 = temp1->next;
			//cout << "temp1 data " << temp1->data;

			//cout << data << " This is data " << Find();
		}
		//if first node is tail
		else if (reference->next == nullptr && reference->data == node->data)
		{
			//temp1->data = data;
			//temp2->data;
			//temp2->prev = temp1;
			temp2->next = nullptr;
			temp1->next = temp2;
			tail = temp2;
			temp1 = temp1->next;
			reference = temp1;
		}
		//if first node is not a tail
		else if (reference->next != nullptr && reference->data == node->data)
		{
			temp2->data = data;
			reference = temp1->next;

			temp2->next = reference;
			temp2->prev = temp1;
			reference->prev = temp2;
			temp1->next = temp2;
			temp1 = reference;
			//reference = temp1;
		}
	}
}

template<typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data)
{
	//node = head; //was temp1 throughout this function
	Node* temp2 = new Node;
	Node* reference = head;
	Node* temp1 = head;


	while (temp1 != nullptr) {
		//if data does not match
		if (reference->data != node->data)
		{
			//node = node->next;
			reference = reference->next;
			temp1 = temp1->next;
			//cout << "temp1 data " << temp1->data;

			//cout << data << " This is data " << Find();
		}
		//if first node is header
		//else if (reference->prev == nullptr && reference->data == node->data)
		//{
		//	//temp1->data = data;
		//	temp2->data;
		//	temp2->prev = nullptr;
		//	temp2->next = temp1;
		//	temp1->prev = temp2;
		//	head = temp2;
		//	temp1 = temp1->next;
		//	reference = temp1;
		//}
		//if first node is not a header
		else if (reference->prev != nullptr && reference->data == node->data)
		{
			temp2->data = data;
			reference = temp1->prev;

			temp2->prev = reference;
			temp2->next = temp1;
			reference->next = temp2;
			temp1->prev = temp2;
			temp1 = temp1->next;
			reference = temp1;
		}
	}
}

template<typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index)
{

	//node = head; //was temp1 throughout this function
	Node* temp2 = new Node;
	Node* reference = head;
	Node* temp1 = head;

	bool breaky;
	breaky = false;
	while (breaky == false) {
		//if data does not match
	//	cout << data << "this is a test" << index;
		//cout << nodeCount << endl;
		for (unsigned int i = 1; i < index; i++)
		{
			temp1 = temp1->next;
			reference = temp1;
		}

		//if node is at the end of a list
		if (temp1->next == nullptr)
		{
			temp1 = tail;
			temp2->data = data;
			temp2->next = nullptr;
			temp2->prev = temp1;
			temp1->next = temp2;
			tail = temp2;
			nodeCount++;
		}
		//if node is not at the end of a list
		else if (temp1->next != nullptr && temp1->prev != nullptr)
		{
			temp1 = temp1->next;
			temp2->next = temp1;
			temp1->prev = temp2;
			reference->next = temp2;
			temp2->prev = reference;
			temp2->data = data;
			nodeCount++;
		}
		//if insert is at the head
		else if (index == 0)
		{
			temp1 = head;
			temp2->next = temp1;

			//reference->next = temp2;
			temp2->prev = nullptr;
			temp2->data = data;
			head = temp2;
			nodeCount++;
		}
		breaky = true;
	}
}

template<typename T>
bool LinkedList<T>::RemoveHead()
{
	bool answer;
	answer = false;
	//if node is a lone header
	if (head != nullptr && head->prev == nullptr && head->next == nullptr)
	{
		//Node* temp1 = head;
		//Node* temp2 = head;

		delete head;
		tail = nullptr;
		head = nullptr;
		//head = temp1;
		answer = true;
		nodeCount--;
	}
	//if node is not a lone header
	else if (head != nullptr && head->prev == nullptr && head->next != nullptr)
	{
		Node* temp1 = head;
		//Node* temp2 = head;

		temp1 = temp1->next;
		temp1->prev = nullptr;
		delete head;
		head = temp1;
		answer = true;
		nodeCount--;
	}
	else
	{
		answer = false;
	}
	return answer;
}

template<typename T>
bool LinkedList<T>::RemoveTail()
{
	bool answer;
	answer = false;
	Node* temp1 = tail;
	//while (tail != nullptr)
	//{
		//if node is a lone tail
	if (tail != nullptr && tail->next == nullptr && tail->prev == nullptr)
	{

		delete temp1;
		tail = nullptr;
		head = nullptr;
		answer = true;
		nodeCount--;
	}
	//if node is not a lone tail
	else if (tail != nullptr && tail->next == nullptr && tail->prev != nullptr)
	{

		temp1 = temp1->prev;
		temp1->next = nullptr;
		delete tail;
		tail = temp1;
		answer = true;
		nodeCount--;
	}
	/*else
	{
		answer = false;
	}*/
	//}
	return answer;
}

template<typename T>
unsigned int LinkedList<T>::Remove(const T& data)
{

	Node* temporaryHead = head;
	//temporaryHead = head;

	Node* temp1 = head;// new Node;
	Node* temp2 = head;// new Node;
	//temp1 = head;
	//temp2 = head;

	int nodesDeleted;
	nodesDeleted = 0;
	T pdata;
	pdata = data;

	while (temporaryHead->next != nullptr) //This while loop will go through all nodes with the exception of the final one and check to see if data = Node data
	{


		//if the data doesn't match with node
		if (temporaryHead->data != pdata)
		{
			temporaryHead = temporaryHead->next;
			temp1 = temporaryHead;
			temp2 = temporaryHead;
		}

		//if node is a lone header
		if (temporaryHead->prev == nullptr && temporaryHead->next == nullptr && temporaryHead->data == pdata)
		{
			temp2 = temp2->next;
			delete temp2;

			//temp2->prev = nullptr;
			delete temp1;
			//head = temp2;
			delete head;
			delete temporaryHead;

			//currentNode--;
			nodeCount--;
			nodesDeleted++;
			//temp1 = temp2;
		}
		//if node is not a lone header
		else if (temporaryHead->prev == nullptr && temporaryHead->next != nullptr && temporaryHead->data == pdata)
		{
			temp2 = temp2->next;
			delete temp1;
			delete head;

			temp2->prev = nullptr;
			head = temp2;
			temporaryHead = temporaryHead->next;
			temp1 = temporaryHead;
			temp2 = temporaryHead;
			//delete head;

			nodeCount--;
			nodesDeleted++;
			//temp1 = temp2;
		}

		//if node is between header and tail
		else if (temporaryHead->next != nullptr && temporaryHead->prev != nullptr && temporaryHead->data == pdata)
		{
			temp2 = temporaryHead;
			temp2 = temp2->next;
			temp1 = temporaryHead;
			temp1 = temp1->prev;
			temp1->next = temp2;
			temp2->prev = temp1;

			delete temporaryHead;
			temporaryHead = temp2;
			temp1 = temporaryHead;
			//currentNode->next = temp2;
			//temp2->prev = currentNode;
			nodeCount--;
			nodesDeleted++;
			//temp1 = temp2;
		}
	}
	if (temporaryHead->next == nullptr && temporaryHead->data == pdata) //This if loop will do the same thing as the while loop but it will be limited to the final node
	{
		//if node is a tail

		//currentNode = temp1->prev;
		delete temp1;
		delete head;
		delete tail;
		delete temporaryHead;
		nodeCount--;
		nodesDeleted++;
	}

	return nodesDeleted;
}

template<typename T>
bool LinkedList<T>::RemoveAt(int index)
{
	Node* temp1 = head;// new Node;
	Node* temp2 = head; // new Node;
	//temp1 = head;
	//temp2 = head;

	int tempNodeCount;
	tempNodeCount = 0;
	unsigned int k;
	k = index;
	bool answer;
	answer = true;


	try//the function within this try block is seeing if the index provided goes out of range
	{
		for (unsigned int i = 0; i < k || answer == false; i++)
		{
			if (i >= nodeCount)
			{
				answer = false;
				throw runtime_error("Error: index out of range.");

			}

			else
			{
				temp1 = temp1->next;
				tempNodeCount++;
			}
		}
	}
	catch (runtime_error& excpt) {
		answer = false;
	}

	//for (unsigned int i = 0; i < k; i++)
	//{
	//	if (temp1->next == nullptr)
	//	{

	//		answer = false;
	//	}
	//}

	if (answer == true)
	{
		temp2 = temp1;//I'm saving the data that comes after the node insert as temp2
	}
	//if node is a lone header
	if (temp1 != nullptr && temp1->prev == nullptr && temp1->next == nullptr)
	{
		delete temp1;
		delete head;
		delete tail;
		delete temp2;
		nodeCount--;
		answer = true;
	}
	//if node is a header
	if (temp1 != nullptr && temp1->prev == nullptr && temp1->next == nullptr)
	{
		temp2 = temp2->next;


		temp2->prev = nullptr;

		head = temp2;
		delete temp1;
		nodeCount--;
		answer = true;
	}
	//if node is a lone tail
	else if (temp1 != nullptr && temp1->next == nullptr && temp1->prev == nullptr)
	{
		delete temp1;
		delete temp2;
		delete tail;
		delete head;

		nodeCount--;
		answer = true;
	}
	//if node is a tail
	else if (temp1 != nullptr && temp1->next == nullptr && temp1->prev != nullptr)
	{
		temp2 = temp2->prev;

		tail = temp2;
		tail->next = nullptr;
		delete temp1;
		nodeCount--;
		answer = true;
	}
	//if node is between header and tail
	else if (temp1 != nullptr && temp1->next != nullptr && temp1->prev != nullptr)
	{
		temp2 = temp2->next;
		currentNode = temp1->prev;

		currentNode->next = temp2;
		temp2->prev = currentNode;
		nodeCount--;
		delete temp1;
		answer = true;
	}
	return answer;
}

template<typename T>
void LinkedList<T>::Clear()
{
	//Node* Temp1 = new Node;
	Node* Temp1 = head;
	//Node* Temp2 = new Node;
	Node* Temp2 = Temp1;

	while (Temp1 != nullptr)//&& Temp1->prev == nullptr)
	{
		Temp1 = Temp1->next;
		delete Temp2;
		Temp2 = Temp1;

		//nodeCount--;
	//	Temp1->prev = nullptr;
	}

	head = nullptr;
	tail = nullptr;
	currentNode = nullptr;
	//if (Temp1->next == nullptr)
	//{
	//	delete Temp2;
	//	delete Temp1;
	//	//nodeCount--;
	//}
	nodeCount = 0;
}

template<typename T>
const T& LinkedList<T>::operator[](unsigned int index) const
{
	Node* temp1 = head;
	Node* nNode = new Node;
	int tempNodeCount;
	tempNodeCount = 0;
	try//the function within this try block is seeing if the index provided goes out of range
	{
		for (unsigned int i = 0; i < index; i++)
		{
			if (temp1->next == nullptr)
			{
				throw runtime_error("index is out of range.");
			}
			else
			{
				temp1 = temp1->next;
				tempNodeCount++;
			}
		}
	}
	catch (runtime_error& excpt) {
		cout << excpt.what() << endl;
	}
	temp1 = temp1->prev;//I'm saving the data that comes after the node insert as temp2
	T nData;
	nData = temp1->data;
	return nData;
}

template<typename T>
T& LinkedList<T>::operator[](unsigned int index)
{
	Node* temp1 = head; // new Node;
	//temp1 = head;
	//Node* nNode = new Node;
	int tempNodeCount;
	tempNodeCount = 0;
	try//the function within this try block is seeing if the index provided goes out of range
	{
		for (unsigned int i = 0; i < index; i++)
		{
			if (temp1->next == nullptr)
			{
				throw runtime_error("index is out of range.");
			}
			else
			{
				temp1 = temp1->next;
				tempNodeCount++;
			}
		}
	}
	catch (runtime_error& excpt) {
		cout << excpt.what() << endl;
	}

	//temp1 = temp1->prev;//I'm saving the data that comes after the node insert as temp2
	//cout << "this is desting temp1 data " << temp1->data << endl;
	//T nData;
	//nData = temp1->data;
	//temp1 = temp1->next;
	//delete temp1;
	return temp1->data;//nData;
}

template<typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const
{
	Node* temp1 = head;
	bool answer;
	answer = true;
	//temp1 = head;
	Node* templist = rhs.head;
	while (temp1->data == templist->data && temp1->next != nullptr) //This while loop will go through all nodes with the exception of the final one and check to see if data = Node data
	{
		temp1 = temp1->next;
		templist = templist->next;
	}
	if (temp1->data != templist->data)
	{
		//delete temp1;
		answer = false;
	}
	if (temp1->next == nullptr && templist->data != temp1->data) //This if loop will do the same thing as the while loop but it will be limited to the final node
	{
		//delete temp1;
		answer = false;
	}
	else
	{
		answer = true;
	}

	return answer;



}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{

	//Node* temp2 = new Node;
	Node* temp1 = rhs.head;
	//Node* temp3 = head;
	//Node* newHead = temp2;

	while (temp1 != nullptr)
	{
		AddTail(temp1->data);
		temp1 = temp1->next;
	}


	//while (temp1 != nullptr)
	//	//for (unsigned int i = 0; i < nodeCount1; i++)
	//{
	//	Node* bNode = new Node;
	//	//if node is not a lone head
	//	if (temp1->next != nullptr && temp1->prev == nullptr)
	//	{


	//		bNode->data = temp1->data;
	//		bNode->prev = nullptr;
	//		bNode->next = nullptr;
	//		temp1 = temp1->next;

	//		temp2 = temp2->next;
	//		newHead = bNode;
	//	}
	//	//if node is between head and tail
	//	else if (temp1->next != nullptr && temp1->prev != nullptr)
	//	{
	//		bNode->data = temp1->data;
	//		bNode->prev = temp2;
	//		bNode->next = nullptr;
	//		//temp3->next = bNode;
	//		temp2->next = bNode;
	//		temp1 = temp1->next;
	//		temp2 = temp2->next;

	//	}
	//	//if node is a tail
	//	else if (temp1->next == nullptr && temp1->prev != nullptr)
	//	{
	//		bNode->data = temp1->data;
	//		bNode->next = nullptr;
	//		bNode->prev = temp2;
	//		temp2->next = bNode;
	//		temp2 = newHead;
	//		temp1 = temp1->next;
	//	}

	//}



	return *this;
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	//Node* Temp1 = new Node;
	Node* Temp1 = head;
	//Node* Temp2 = new Node;
	Node* Temp2 = Temp1;

	while (Temp1 != nullptr)//&& Temp1->prev == nullptr)
	{
		Temp1 = Temp1->next;
		delete Temp2;
		Temp2 = Temp1;
		//nodeCount--;
	//	Temp1->prev = nullptr;
	}
	//if (Temp1->next == nullptr)
	//{
	//	delete Temp2;
	//	delete Temp1;
	//	//nodeCount--;
	//}
	nodeCount = 0;
}
