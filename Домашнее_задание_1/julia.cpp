// Аргументы командной строки: 1 и 2 - координаты центра, 3 и 4 - координаты c, 5 - радиус.

#include <cstdlib>
#include "complex.hpp"

struct Color {
	unsigned char r, g, b;
};

int iteration_number(Complex z, Complex c, int n, Complex centre, float length);
void iteration(Complex &z, Complex c);


int main(int argc, char **argv) {

	Complex centre(atof(argv[3]), atof(argv[4]));

	int width = 800, height = 800, n = 150;

	float x1 = atof(argv[1]) - atof(argv[5]);
	float x2 = atof(argv[1]) + atof(argv[5]);
	float y1 = atof(argv[2]) - atof(argv[5]);
	float y2 = atof(argv[2]) + atof(argv[5]);

	Color* data = new Color [width * height];
	Complex z(atof(argv[3]), atof(argv[4]));

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			Complex c = {x1 + (float)(x2 - x1) / width * i, y1 + (float)(y2 - y1) / width * j};

			int clr = iteration_number(c, z, n, centre, atof(argv[5]));
			data[i + width * j].r = 255 - (float)255 * clr / n;
			data[i + width * j].g = 255 - (float)255 * clr / n ;
			data[i + width * j].b = 255 - (float)255 * clr / n;
		}
	}

	FILE* file = fopen("julia.ppm", "wb");
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
