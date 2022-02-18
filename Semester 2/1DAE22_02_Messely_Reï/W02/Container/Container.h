#pragma once
class Container
{
public:
	Container(int capacity = 10);
	~Container();

	int Size();
	int Capacity();
	int Get(int index);
	void Set(int index, int newvalue);
	void Pushback(int element);

private:
	void Reserve(int newCapacity);

	int m_Size;
	int m_Capacity;
	int* m_pElement;
};