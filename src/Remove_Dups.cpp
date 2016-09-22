//============================================================================
// Name        : Remove_Dups.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;

class List
{
public:
	struct Node
	{
		int number;
		string str;
		Node* next;
		Node* previous;

		Node(int _num = 0, string _str = "")
		{
			number = _num;
			str.assign(_str);
			next = NULL;
			previous = NULL;
		}
	};

	int getNumber();
	string getString();

	List();
	~List();
	void init();
	void add(int num, string str);
	Node* getCurrentNode(){return current;};
	Node* getHead(){return head;};
	void printNode();
	void removeDuplicate();
	void eraseNodeByNum(int num);
	Node* eraseNode(Node* temp);
	Node* returnTemp(Node* tmp);

private:
	Node* current;
	Node* head;
};

void List::eraseNodeByNum(int num)
{
	Node* temp = head;
	while(temp != NULL)
	{
		if(temp->number == num)
			eraseNode(temp);
		temp = temp->next;
	}
}

//erase currentNode
//Node* List::eraseNode(Node* tempNode)
List::Node* List::eraseNode(Node* tempNode)
{
//	cout << "tempNode: " << tempNode->number << endl;
//	cout << "previous: " << tempNode->previous->number << endl;

	if(tempNode == head)
	{
		Node* temp = head;
		head = head->next;
		tempNode = head;
		delete temp;
	}
	else if(tempNode == NULL)
	{
		return NULL;
	}
	else
	{
		Node* temp = tempNode;
		tempNode->previous->next = tempNode->next;

		if(tempNode->next != NULL)
		{
			tempNode->next->previous = tempNode->previous;
		}
		tempNode = tempNode->previous;

		delete temp;
	}
	return tempNode;
}

//find same number value, if more than one node have same number value,
//erase node and leave only one node so node can have unique number value.
void List::removeDuplicate()
{
	Node* temp = head;
	while(temp != NULL)
	{
		int uniqueNumber = temp->number;

		int count = 0;
		Node* iter = head;
		while(iter != NULL)
		{
			if(iter->number == uniqueNumber)
			{
				count++;
				if(count > 1)
				{
					iter = eraseNode(iter);
					count--;
				}
			}
			iter = iter->next;
		}
		temp = temp->next;
	}
}

void List::printNode()
{
	Node* temp = head;
	while(temp != NULL)
	{
		cout << temp->number << " " << temp->str << endl;
		temp = temp->next;
	}
}

void List::add(int num, string _str)
{

	//go to the end of the list.
	while(current->next != NULL)
	{
		current->previous = current;
		current = current->next;
	}

	//create new Node and add it to the end of the list
	Node* newNode = new Node(num, _str);

	current->next = newNode;
	newNode->previous = current;
	current = current->next;

}

List::~List()
{
	Node* temp = head;
	while(temp != NULL)
	{
		temp = eraseNode(temp);
	}
}

void List::init()
{
	//initialize, create Node and add it to the list.
	Node* newNode = new Node(1, "First Node");
	//newNode->next = NULL;
	current = newNode;
	head = newNode;
}

List::List() : current(NULL)
			 , head(NULL)
{
	init();
}

int List::getNumber()
{
	return current->number;
}

string List::getString()
{
	return current->str;
}

int main()
{
	List myList;


	myList.add(2, "second Node");
	myList.add(3, "Third Node");
	myList.add(4, "fouth Node");
	myList.add(5, "fifth Node");
	myList.add(5, "fifth Node");
	myList.add(4, "fouth Node");
	myList.add(5, "fifth Node");
	myList.add(5, "fifth Node");
	myList.add(5, "fifth Node");

	//myList.eraseNode(myList.getCurrentNode());
	//myList.eraseNodeByNum(3);
	myList.removeDuplicate();

	myList.printNode();

	return 0;
}

