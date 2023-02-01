#include "Color.h"

Color::Color() : r(255), g(255), b(255) {}

Color::Color(unsigned char r, unsigned char g, unsigned char b) :
	r(r), g(g), b(b)
{}

Color& Color::SetBrightness(float br) {
	r = (unsigned char)(r * br);
	g = (unsigned char)(g * br);
	b = (unsigned char)(b * br);

	return *this;
}
