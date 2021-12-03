#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

typedef struct Node
{
	int row; // 행
	int col; // 열
	Node* next;
	void display()
	{
		printf("%d %d\n", row, col);
	}
};

class LinkedQueue
{
	Node* front;
	Node* rear;
	int len = 0;
public:
	LinkedQueue() : front(NULL), rear(NULL) { }
	bool isEmpty()
	{
		return front == NULL;
	}

	void enqueue(int r, int c)
	{
		Node* node = (Node*)malloc(sizeof(Node));
		node->row = r;
		node->col = c;
		node->next = NULL;
		if (isEmpty())
		{
			front = rear = node;
		}
		else
		{
			rear->next = node;
			rear = rear->next;
		}
		len++;
	}

	

	int dequeue()
	{
		if (isEmpty())
			cout << "Q is Empty" << endl;
		Node* delNode = front;
		int row = delNode->row;
		int col = delNode->col;
		front = delNode->next;
		free(delNode);
		len--;
		return row, col;
	}

	int firstRow()
	{
		return front->row;
	}

	int firstCol()
	{
		return front->col;
	}

	void display()
	{
		printf("큐 내용 : ");
		for (Node* p = front; p != NULL; p = p->next)
			p->display();

	}
};