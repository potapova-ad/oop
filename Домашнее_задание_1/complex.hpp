#include <iostream>
#include <cstdio>
#include <cmath>

class Complex {
public:

	Complex(float re = 0, float im = 0) :
		re(re),
		im(im) {
		};

	~Complex() {
	}

    Complex(Complex &other) {
		re = other.re;
		im = other.im;
	}

	Complex(Complex &&other) {
		re = other.re;
		im = other.im;
	}

	Complex &operator= (Complex &right) {
		re = right.re;
		im = right.im;
		return *this;
	}

	Complex &operator= (Complex &&right) {
		re = right.re;
		im = right.im;
		return *this;
	}

    Complex &operator+= (Complex &right) {
		re += right.re;
		im += right.im;
		return *this;
	}

	Complex &operator+= (Complex &&right) {
		re += right.re;
		im += right.im;
		return *this;
	}

    Complex &operator-= (Complex &right) {
		re -= right.re;
		im -= right.im;
		return *this;
	}

	Complex &operator-= (Complex &&right) {
		re -= right.re;
		im -= right.im;
		return *this;
	}

    Complex &operator*= (Complex &right) {
		float tempRe = re;
		float tempIm = im;

		re = tempRe * right.re - tempIm * right.im;
		im = tempIm * right.re + tempRe * right.im;
		return *this;
	}

	Complex &operator*= (Complex &&right) {
		float tempRe = re;
		float tempIm = im;

		re = tempRe * right.re - tempIm * right.im;
		im = tempIm * right.re + tempRe * right.im;
		return *this;
	}

    Complex &operator/= (Complex &right) {
		float tempRe = re;
		float tempIm = im;

		if (right.re == 0 && right.im == 0) {
			std::cout << "Error" << std::endl;
			return *this;
		}

		re = (tempRe * right.re + tempIm * right.im) / (right.re * right.re + right.im * right.im);
		im = (tempIm * right.re - tempRe * right.im) / (right.re * right.re + right.im * right.im);
		return *this;
	}

	Complex &operator/= (Complex &&right) {
		float tempRe = re;
		float tempIm = im;

		if (right.re == 0 && right.im == 0) {
			std::cout << "Error" << std::endl;
			return *this;
		}

		re = (tempRe * right.re + tempIm * right.im) / (right.re * right.re + right.im * right.im);
		im = (tempIm * right.re - tempRe * right.im) / (right.re * right.re + right.im * right.im);
		return *this;
	}

    Complex operator+ (){
		return *this;
	}

    Complex operator- () {
		re = -re;
		im = -im;
		return *this;
	}

    Complex operator~ (){
		Complex res = *this;
		res.im = -res.im;
		return res;
	}

    bool operator== (Complex &other) const{
		if (re == other.re && im == other.im) return true;
		return false;
	}

	bool operator== (Complex &&other) const{
		if (re == other.re && im == other.im) return true;
		return false;
	}

    float re;
	float im;
};

Complex operator+ (Complex &left, Complex &right) {
	Complex res = left;
	res += right;
	return res;
}

Complex operator+ (Complex &&left, Complex &right) {
	Complex res = left;
	res += right;
	return res;
}

Complex operator+ (Complex &left, Complex &&right) {
	Complex res = left;
	res += right;
	return res;
}

Complex operator+ (Complex &&left, Complex &&right) {
	Complex res = left;
	res += right;
	return res;
}

Complex operator- (Complex &left, Complex &right) {
	Complex res = left;
	res -= right;
	return res;
}

Complex operator- (Complex &&left, Complex &right) {
	Complex res = left;
	res -= right;
	return res;
}

Complex operator- (Complex &left, Complex &&right) {
	Complex res = left;
	res -= right;
	return res;
}

Complex operator- (Complex &&left, Complex &&right) {
	Complex res = left;
	res -= right;
	return res;
}

Complex operator* (Complex &left, Complex &right) {
	Complex res = left;
	res *= right;
	return res;
}

Complex operator* (Complex &&left, Complex &right) {
	Complex res = left;
	res *= right;
	return res;
}

Complex operator* (Complex &left, Complex &&right) {
	Complex res = left;
	res *= right;
	return res;
}

Complex operator* (Complex &&left, Complex &&right) {
	Complex res = left;
	res *= right;
	return res;
}

Complex operator/ (Complex &left, Complex &right) {
	Complex res = left;
	res /= right;
	return res;
}

Complex operator/ (Complex &&left, Complex &right) {
	Complex res = left;
	res /= right;
	return res;
}

Complex operator/ (Complex &left, Complex &&right) {
	Complex res = left;
	res /= right;
	return res;
}

Complex operator/ (Complex &&left, Complex &&right) {
	Complex res = left;
	res /= right;
	return res;
}

std::ostream &operator<< (std::ostream &left, Complex &right)  {
	left << "(" << right.re << " + " << right.im << "i)";
	return left;
}

std::ostream &operator<< (std::ostream &left, Complex &&right)  {
	left << "(" << right.re << " + " << right.im << "i)";
	return left;
}

std::istream &operator>> (std::istream &left, Complex &right)  {
	left >> right.re >> right.im;
	return left;
}

Complex exp(Complex &z) {
	Complex res;
	float mult = exp(z.re);
		 res.re = mult * cos(z.im);
		 res.im = mult * sin(z.im);
	return res;
}

Complex exp(Complex &&z) {
	Complex res;
	float mult = exp(z.re);
		 res.re = mult * cos(z.im);
		 res.im = mult * sin(z.im);
	return res;
}

Complex sin(Complex &z) {
	Complex res(cosh(z.re) * sin(z.im), sinh(z.im) * cos(z.re));
	return res;
}

Complex sin(Complex &&z) {
	Complex res(cosh(z.re) * sin(z.im), sinh(z.im) * cos(z.re));
	return res;
}

float norm(Complex &z) {
	return sqrt(z.re * z.re + z.im * z.im);
}

float norm(Complex &&z){
	return sqrt(z.re * z.re + z.im * z.im);
}
