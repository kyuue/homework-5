#include<iostream>

using namespace std;

template<class T>
class UniquePtr {
public:
	UniquePtr(T * ptr) :data(ptr) {}
	UniquePtr(const UniquePtr<T> &) = delete; // unique_ptr gibi
	UniquePtr & operator=(const UniquePtr<T> &) = delete;
	~UniquePtr()
	{
		std::cout << "normal delete called\n";
		delete data;
	}

	//dereferencing operator
	T& operator*() { return *data; }
	T operator*() const { return *data; }

	UniquePtr<T>* operator->()
	{
		return this;
	}


private:
	T * data;
	// int counter; // shared_ptr icin
};

template<class T>
class UniquePtr<T[]> {
public:
	UniquePtr(T * ptr) :data(ptr), originalAddress(ptr) {}

	UniquePtr(UniquePtr<T> & other)
	{
		*this = other;
	}

	UniquePtr & operator=(UniquePtr<T> & other)
	{
		if (other.data == this->data)
			return *this;

		//++other.counter;

		this->originalAddress = other.originalAddress;

		this->data = other.data;

		return *this;
	}


	~UniquePtr()
	{
		std::cout << "array delete called\n";

		delete[] originalAddress;
	}

	//dereferencing operator
	T& operator*() { return *data; }
	T operator*() const { return *data; }

	UniquePtr<T>* operator->()
	{
		return this;
	}

	T* operator++()
	{
		return ++data;
	}

	T* operator++(int)
	{
		T* temp = data;
		++data;
		return temp;
	}

	T* operator+=(int in)
	{
		data += in;

		return data;
	}

private:
	T * data, *originalAddress;
};

template<class T>
class SharedPtr {
public:
	SharedPtr(T * ptr) :data(ptr), counter(1) {}

	SharedPtr(SharedPtr<T> & other) 
	{
		*this = other;
	}

	SharedPtr & operator=(SharedPtr<T> & other) 
	{
		if (other.data == this->data)
			return *this;

		//++other.counter;

		this->data = other.data;

		this->counter = other.counter + 1;

		return *this;
	}


	~SharedPtr()
	{
		std::cout << "normal delete called\n";

		--counter;

		if (counter == 0)
			delete data;
	}

	//dereferencing operator
	T& operator*() { return *data; }
	T operator*() const { return *data; }

	SharedPtr<T>* operator->()
	{
		return this;
	}


private:
	T * data;
	int counter; // shared_ptr icin
};

template<class T>
class SharedPtr<T[]> {
public:
	SharedPtr(T * ptr) :data(ptr), originalAddress(ptr), counter(1) {}

	SharedPtr(SharedPtr<T> & other)
	{
		*this = other;
	}

	SharedPtr & operator=(SharedPtr<T> & other)
	{
		if (other.data == this->data)
			return *this;

		//++other.counter;

		this->originalAddress = other.originalAddress;

		this->data = other.data;

		this->counter = other.counter + 1;

		return *this;
	}


	~SharedPtr()
	{
		std::cout << "array delete called\n";

		--counter;

		if (counter == 0)
			delete[] originalAddress;
	}

	//dereferencing operator
	T& operator*() { return *data; }
	T operator*() const { return *data; }

	SharedPtr<T>* operator->()
	{
		return this;
	}

	T* operator++()
	{
		return ++data;
	}

	T* operator++(int)
	{
		T* temp = data;
		++data;
		return temp;
	}

	T* operator+=(int in)
	{
		data += in;

		return data;
	}

private:
	T * data, *originalAddress;
	int counter; // shared_ptr icin
};

int main()
{
	UniquePtr<int[]> sPtr{ new int[1024] {} };

	cout << "data:" << *sPtr << endl;
	++(*sPtr);
	cout << "data:" << *sPtr << endl;

	sPtr++;

	cout << "data:" << *sPtr << endl;


	return 0;
}