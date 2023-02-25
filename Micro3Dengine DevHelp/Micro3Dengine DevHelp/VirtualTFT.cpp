#include "VirtualTFT.h"

bool VirtualTFT::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	int result = SDL_CreateWindowAndRenderer(100 + _width * 2, 100 + _height * 2, NULL, &_window, &_renderer);
	if (result != 0) {
		Log("Failed to create window and renderer:", 1);
		return false;
	}
	uiTexture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
								  _width * 2 + 100, _height * 2 + 100);
	return true;
}

void VirtualTFT::ClearFrame(Uint8 r, Uint8 g, Uint8 b)
{
	int pitch = 0;
	uiPixels = nullptr;
	if (!SDL_LockTexture(uiTexture, NULL, (void**)&uiPixels, &pitch)) {
		// lockedPixels now points to driver-provided memory that we can write to that the driver will then copy to uiTexture
	    // can't ignore pitch, it might be wider than UI_WIDTH
	}


	for (unsigned i = 0; i < 22; i++) {
		Uint32 color = ((10 << 8 | 10+i*5) << 8) | 50 + i*8 | 0xff000000;

		for (unsigned y = 0; y < 20; y++) {
			DrawFastHLine(0, i * 10 + y, _width,  color);
		}
	}

	//Uint32 color = ((r << 8 | g) << 8) | b | 0xff000000;
	//memset(uiPixels, color, (_width *2 + 100) * (_height * 2 + 100) * 4);
}

void VirtualTFT::UpdateFrame()
{
	SDL_UnlockTexture(uiTexture);

	SDL_Rect rect;
	rect.x = rect.y = 0;
	rect.w = _width * 2 + 100;
	rect.h = _height * 2 + 100;

	SDL_RenderCopy(_renderer, uiTexture, &rect, &rect);
	SDL_RenderPresent(_renderer);
}

void VirtualTFT::DrawPixel(unsigned int x, unsigned int y, Uint8 r, Uint8 g, Uint8 b)
{
	if (x<0 || x>_width - 1 || y<0 || y > _height - 1) return;

	Uint32 color = ((r << 8 | g) << 8) | b | 0xff000000;
	
	y *= 2;	x *= 2;
	x += 50;

	unsigned y1 = y * (_width * 2 + 100);
	uiPixels[y1 + x] = color;
	uiPixels[y1 + x + 1] = color;
	y++;
	y1 = y * (_width * 2 + 100);
	uiPixels[y1 + x] = color;
	uiPixels[y1 + x + 1] = color;
}

void VirtualTFT::DrawLineBuffer(Uint16* colorB, unsigned width, unsigned lineNumber) {
	for (unsigned x = 0; x < width; x++)
	{
		Uint8 r = colorB[x] >> 8 | 0b00000111;
		Uint8 g = (colorB[x] >> 2) | 0b00000011;
		Uint8 b = colorB[x] << 3 | 0b00000111;
		DrawPixel(x, lineNumber, r, g, b);
	}
}

#define swap(x, y) { int temp = x; x = y; y = temp; }


void VirtualTFT::DrawFastHLine(int x, int y, int w, Uint32 color)
{
	// mirroring
	y = _height - y;

	y *= 2; x *= 2;
	x += 50;

	unsigned y1 = y * (_width * 2 + 100) + x;
	unsigned y2 = (y+1) * (_width * 2 + 100) +x;
	unsigned stop = x + w * 2;

	Uint32* p1 = &uiPixels[y1];
	Uint32* p2 = &uiPixels[y2];
	
	for (unsigned i = x; i < stop; i++) {
		*p1++ = color;
		*p2++ = color;
	}
}

void VirtualTFT::FillTriangle(int x0, int y0, int x1, int y1,
	int x2, int y2, Uint8 red, Uint8 green, Uint8 blue) {

	Uint32 color = ((red << 8 | green) << 8) | blue | 0xff000000;

	// Sort coordinates by Y order (y2 >= y1 >= y0)
	if (y0 > y1) {
		swap(y0, y1); swap(x0, x1);
	}
	if (y1 > y2) {
		swap(y2, y1); swap(x2, x1);
	}
	if (y0 > y1) {
		swap(y0, y1); swap(x0, x1);
	}

	float dx02 = x2 - x0;
	float dy02 = y2 - y0;
	//dx02 /= dy02;

	float  dx01 = x1 - x0;
	float  dy01 = y1 - y0;

//	dx01 /= dy01;

	float dx12 = x2 - x1;
	float dy12 = y2 - y1;

//	dx12 /= dy12;

	unsigned start;
	if (y0 < 0) { start = 0; }
	else
	{
		if (y0 < _height) { start = y0; }
		else { return; }
	}
	unsigned stop;
	if (y2 >= _height) { stop = _height; }
	else
	{
		if (y2 > 0) { stop = y2; }
		else { return; }
	}

	float dxy01 = dx01 / dy01;
	float dxy02 = dx02 / dy02;
	float dxy12 = dx12 / dy12;

	int left = x0, right = x0;

	int actualYStep = start - y0;
	left = x0 + dxy01 * actualYStep;
	for (int actualLine = start; actualLine < stop; actualLine++)
	{	
		if (actualLine < y1) {
			int actualYStep = actualLine - y0;
			
			left = x0 + dxy01 * actualYStep;
			right = x0 + dxy02 * actualYStep;

			if (left > right) { swap(left, right); }
			if (right < 0) { right = 0; }
			else if (right >= _width) { right = _width - 1; }
			if (left < 0) { left = 0; }
			else if (left >= _width) { left = _width - 1; }
			DrawFastHLine(left, actualLine, right - left, color);
		}
		else
		{	// triangle lower part
			int stepy02 = actualLine - y0;
			int stepy12 = actualLine - y1;

			left = x0 + dxy02 * stepy02;
			right = x1 + dxy12 * stepy12;

			if (left > right) { swap(left, right, int); }

			if (right < 0) { right = 0; }
			else if (right >= _width) { right = _width - 1; }

			if (left < 0) { left = 0; }
			else if (left >= _width) { left = _width - 1; }

			DrawFastHLine(left, actualLine, right - left, color);
		}
	}
}

//*********************

void VirtualTFT::DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
	int16_t x2, int16_t y2, Uint8 r, Uint8 g, Uint8 b)
{
	DrawLine(x0, y0, x1, y1, r, g, b);
	DrawLine(x1, y1, x2, y2, r, g, b);
	DrawLine(x2, y2, x0, y0, r, g, b);
}

void VirtualTFT::DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, Uint8 r, Uint8 g, Uint8 b) {
	int16_t steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep) {
		swap(x0, y0);
		swap(x1, y1);
	}

	if (x0 > x1) {
		swap(x0, x1);
		swap(y0, y1);
	}

	int16_t dx, dy;
	dx = x1 - x0;
	dy = abs(y1 - y0);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y0 < y1) {
		ystep = 1;
	}
	else {
		ystep = -1;
	}

	for (; x0 <= x1; x0++) {
		if (steep) {
			DrawPixel(y0, x0, r, g, b);
		}
		else {
			DrawPixel(x0, y0, r, g, b);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}