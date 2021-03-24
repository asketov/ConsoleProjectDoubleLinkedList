#include <iostream>

struct DataType
{
	double coef, degree;
};

class IBaseClass
{
public:
	bool virtual EnQueue(DataType info) = 0;
	DataType virtual DeQueue(void) = 0;
};

class Connected : public IBaseClass
{
private:
	struct element
	{
		DataType data;
		element* next;
	} *front, * rear; //индексы головы и хвоста
public:
	Connected() { front = rear = NULL; }
	~Connected()
	{
		element* temp;
		while (front)
		{
			temp = front;
			front = front->next;
			delete temp;
		}
	}
	bool EnQueue(DataType info) override
	{
		element* temp = new element;
		if (temp == NULL) return 1;
		temp->data = info;
		temp->next = NULL;
		if (front == NULL)
			front = rear = temp;
		else
		{
			rear->next = temp;
			rear = rear->next;
		}
		return 1;
	}

	DataType DeQueue(void) override
	{
		DataType temp = front->data;
		element* tmp = front;
		front = front->next;
		delete tmp;
		return temp;
	}


};

class vector : public IBaseClass
{
private:
	int front, rear; //индексы головы и хвоста
	int maxlength;  //размер массива
	DataType* data; //массив для хранения элементов
public:
	vector(int n ) : maxlength(n)
	{
		data = new DataType[maxlength];
		front = 0;
		rear = maxlength - 1;
	}
	~vector()
	{
		delete[] data;
	}
	bool EnQueue(DataType info) override
	{
		rear = (rear + 1) % maxlength;
		data[rear] = info;
		return 1;
	}
	DataType DeQueue(void) override
	{
		int temp = front;
		front = (front + 1) % maxlength;
		return data[temp];
	}
};