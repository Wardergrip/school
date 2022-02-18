#pragma once
class Container
{
public:
	Container(int capacity = 10);
	~Container();

	int Size() const;
	int Capacity() const;
	int Get(int index) const;
	void Set(int index, int newvalue);
	void Pushback(int element);
	void Info(const std::string& preface = "") const;

private:
	void Reserve(int newCapacity);

	int m_Size;
	int m_Capacity;
	int* m_pElement;
};