#include <iostream>
#include <iomanip>
#include "number.hpp"
#include <cstring>

Number::Number() {
	capacity = 1;
	size = 0;
	data = new char [capacity] {};
}

Number::Number(long long int a) {

    int temp = a;
    capacity = 0;
    while (temp != 0) {
        temp /= base;
        capacity += 1;
    }

    if (capacity == 0) {
        capacity = 1;
    }

    data = new char[capacity];

    for (int i = 0; i < capacity; ++i) {
        data[i] = a % base;
        a /= base;
    }

    size = capacity;

}

Number::Number(const char *str){

	size_t temp_size = strlen(str);
	capacity = temp_size / 2 + temp_size % 2;
	size = capacity;

	data = new char [capacity] {};

	size_t t;
	for (int i = 0; i < capacity - 1; ++i){
		t = 2 * (capacity - i - (temp_size % 2)) - (2 - temp_size % 2);
		data[i] = (str[t ] - '0') * 10 + (str[t + 1] - '0') ;
	}

	if (temp_size % 2) {
		data[capacity - 1] = str[0] - '0' ;
	}
	else if (temp_size != 0) {
		data[capacity - 1] = (str[0] - '0') * 10 + (str[ 1] - '0') ;
	}
}

Number::~Number() {
	delete [] data;
}

Number &Number::operator= (const Number &right) {
	if (this == &right)
        return *this;

	size = right.size;
	capacity = right.capacity;

	delete [] data;

	data = new char [capacity] {};

	for (int i = 0; i < size; ++i)
		data[i] = right.data[i];

	return *this;
}

Number::Number(const Number &right) {
	size = right.size;
	capacity = right.capacity;

	data = new char [capacity] {};

	for (int i  = 0; i < right.size; ++i)
		data[i] = right.data[i];
}

Number::Number(Number &&right) {
	size     = right.size;
	capacity = right.capacity;
	std::swap(data, right.data);
}

Number Number::operator+= (const Number &right) {
	size_t remainder = 0, temp = 0, count = 0;

	count = std::max(right.size, size);
	if (capacity <= count)
		resize(count + 2);
	size = count;

	for (int i = 0; i < count; ++i) {
		temp = 0;
		if (i < right.size)
			temp = right.data[i];

		temp += remainder + data[i];

		data[i] = temp % base;
		remainder = temp / base;
	}

	if (remainder != 0) {
		data[size] += remainder;
		++size;
	}
	return *this;
}

Number operator+ (const Number &left, const Number &right) {
	Number result = left;
	result += right;
	return result;
}

Number Number::operator*= (const Number &right) {
	long long int remainder = 0, t = 0, temp_size = 2 * std::max(size, right.size) + 2;

	Number sum = 0ll;
	if (capacity <= temp_size)
		resize(temp_size);

	Number temp;
	temp.resize(temp_size);

	for (int i = 0; i < right.size; ++i) {
		remainder = 0;
		temp.size = i + size ;
		for (int j = 0; j < size; ++j) {
			t = data[j] * right.data[i] + remainder;
			temp.data[j + i] = t % base;
			remainder = t / base;
		}

		if (remainder != 0) {
			temp.data[temp.size] = remainder;
			++temp.size;
		}

		sum += temp;
	}

	capacity = sum.capacity;
	size = sum.size;
	std::swap(data, sum.data);

	return *this;
}


Number operator* (const Number &left, const Number &right) {
	Number result;
	if (left > right) {
		result = left;
		result *= right;
		return result;
	}
	result = right;
	result *= left;
	return result;
}


std::ostream &operator<<(std::ostream& stream, const Number& right) {
	stream << (int)right.data[right.size - 1];

	for (size_t i = 0; i < right.size - 1 ; ++i) {
		stream << std::setfill('0') << std::setw(2) << (int)right.data[right.size - 2 - i];
	}
	return stream;
}


void Number::resize(size_t new_size) {
	char *new_data = new char [new_size] {};

	int copy_size = std::min(new_size, size);
	size = copy_size;

	for (int i = 0 ; i < copy_size; ++i)
		new_data[i] = data[i];

	delete [] data;

	data = new_data;
	capacity = new_size;
}


bool Number::isEven() const {
	return (!(data[0] % 2));
}


void Number::div2() {
	int remainder = 0, temp = 0;
	for (int i = size - 1; i >= 0; --i) {
		temp = data[i] + remainder * base;
		data[i] = temp / 2 ;
		remainder = temp % 2;
	}
	if (size != 0 && data[size - 1] == 0)
		size--;
}


bool Number::operator== (const Number &right) const{
	if (right.size != size) return false;
	for (int i = 0; i < size; ++i)
		if (data[i] != right.data[i]) return false;
	return true;
}

bool Number::operator!= (const Number &right) const{
	return !(*this == right);
}

bool Number::operator> (const Number &right) const {
	if (size > right.size) return true;
		else if (size < right.size) return false;

	for (int i = size - 1; i >= 0; --i)
		if (data[i] > right.data[i]) return true;
			else if (data[i] != right.data[i]) return false;
				else continue;
	return false;
}
