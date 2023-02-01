#pragma once

class Color {
public:
	Color();
	Color(unsigned char r, unsigned char g, unsigned char b);

	Color& SetBrightness(float br);

	unsigned char r;
	unsigned char g;
	unsigned char b;
};
