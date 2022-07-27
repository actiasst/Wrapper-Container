#include <iostream>
#include <algorithm>

using namespace std;

class ActualValue {
	int a;
	int b;
	int c;

public:
	ActualValue() : a{ 0 },
		b{ 1 },
		c{ 2 } { }

	void setValues(int a, int b, int c) {
		this->a = a;
		this->b = b;
		this->c = c;
	}

	void printValues() {
		std::cout << a << " " << b << " " << c << std::endl;
	}
};

class Wrapper {
	ActualValue* wrappedValue;

public:
	Wrapper() : wrappedValue{ new ActualValue } { }

	ActualValue* getActualValue() {
		return wrappedValue;
	}

	operator ActualValue*() {
		return getActualValue();
	}
};

class Container {
	unsigned int size;
	Wrapper* actualValueArray;

public:
	Container() : size{ 10 },
		actualValueArray{ new Wrapper[size] } { }

	ActualValue* operator[](const size_t index) {
		return actualValueArray[index].getActualValue();
	}

	Wrapper* begin() {
		return actualValueArray;
	}

	Wrapper* end() {
		return &actualValueArray[size];
	}
};

int main() {
	int startValue{ 0 };
	Container container{};
	for_each(container.begin(), container.end(),
		[&startValue](ActualValue* value) {value->setValues(startValue, startValue + 1, startValue + 2); ++startValue; });
	for(ActualValue* value : container)
		value->printValues();
	system("pause");
}