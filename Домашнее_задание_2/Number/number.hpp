#pragma once

class Number {

    public:

	Number();
	Number(long long int a);
	Number(const char *a);
	~Number();
	Number(const Number &right);
	Number(Number &&right);
	Number &operator= (const Number &right);
	Number operator+= (const Number &right);
	bool isEven() const;
	Number operator*= (const Number &right);
	bool operator== (const Number &right) const;
	bool operator!= (const Number &right) const;
	bool operator> (const Number &right) const;
	void resize(size_t new_size);
	void div2();
	friend Number operator+ (const Number &left, const Number &right);
	friend Number operator* (const Number &left, const Number &right);
	friend std::ostream &operator<<(std::ostream& stream, const Number& right);

    private:

	static const int base = 100;
	size_t size;
	size_t capacity;
	char* data;
};
