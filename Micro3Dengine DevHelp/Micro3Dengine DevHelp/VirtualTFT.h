#pragma once

#define SDL_MAIN_HANDLED

#include <iostream> 
#include "SDL.h"

#include "ILogger.h"
#include "../../Micro3Dengine/object3d.h"

template <class numT>
class Face3D;


class VirtualTFT
{
public:

    VirtualTFT(unsigned width, unsigned height, ILogger* logger = nullptr) :
        _height(height),
        _width(width)
    {
        _logger = logger;
    }

    bool Init();

    void DrawLineBuffer(Uint16* colorB, unsigned width, unsigned lineNumber);
    void DrawPixel(unsigned int x, unsigned int y, Uint8 r, Uint8 g, Uint8 b);
 
    void DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, Uint8 r, Uint8 g, Uint8 b);

private:
    void DrawFastHLine(int x, int y, int w, Uint8 r, Uint8 g, Uint8 b);
public:
    void DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                      int16_t x2, int16_t y2, Uint8 r, Uint8 g, Uint8 b);

    template<class numT>
    void FillTriangle(Face3D<numT> face, Color& color)
    {
        FillTriangle(face.vector1->X, face.vector1->Y, face.vector2->X, face.vector2->Y,
            face.vector3->X, face.vector3->Y, color.r, color.g, color.b);
    }

    void FillTriangle(int x0, int y0, int x1, int y1,
        int x2, int y2, Uint8 r, Uint8 g, Uint8 blue);

    void ClearFrame(Uint8 r, Uint8 g, Uint8 b);
    void UpdateFrame();

    unsigned Height() { return _height; }
    unsigned Width() { return _width; }

private:
    void Log(const char* msg, int level) {
        if (_logger != nullptr) {
            _logger->Log(msg, level);
        }
    }

    ILogger* _logger;

    int _width;
    int _height;
    
    SDL_Window*   _window;
    SDL_Renderer* _renderer;
    SDL_Surface*  _surface;

    SDL_Texture * uiTexture;
    Uint32* uiPixels;
};


