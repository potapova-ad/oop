// Аргументы командной строки: 1 и 2 - координаты центра, 3 - радиус.

#include <cstdlib>
#include "complex.hpp"

int iteration_number(Complex z, Complex c, int n, Complex centre, float length);
void iteration(Complex &z, Complex c);

struct Color {
	unsigned char r, g, b;
};

int main(int argc, char **argv) {

	int width = 10000, height = 10000, n = 150;
	float x1 = atof(argv[1]) - atof(argv[3]);
	float x2 = atof(argv[1]) + atof(argv[3]);
	float y1 = atof(argv[2]) - atof(argv[3]);
	float y2 = atof(argv[2]) + atof(argv[3]);
	Complex centre(atof(argv[1]), atof(argv[2]));
    Color* data = new Color [width * height];
	Complex z;

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			Complex c = {x1 + (float)(x2-x1) / width * i, y1 + (float)(y2-y1) / width * j};

			int clr = iteration_number(z, c, n, centre, atof(argv[3]));
			data[i + width * j].r = 255 - (float)255 * clr / n;
			data[i + width * j].g = 255 - (float)255 * clr / n ;
			data[i + width * j].b = 255 - (float)255 * clr / n;
		}
	}

	FILE* file = fopen("mandelbrot.ppm", "wb");
	fprintf(file, "P6\n%d %d\n255\n", width, height);
	fwrite(data, sizeof(Color), height * width, file);
	fclose(file);

	delete [] data;

	return 0;
}

int iteration_number(Complex z, Complex c, int n, Complex centre, float length) {

	for (int i = 0 ; i < n; i++) {
		iteration(z, c);
		if (z.re * z.re + z.im * z.im > (centre.re - length) * (centre.re - length) + (centre.im - length) * (centre.im - length) )
			return i;
	}
	return n;
}

void iteration(Complex &z, Complex c) {
	z = z * z + c;
}
