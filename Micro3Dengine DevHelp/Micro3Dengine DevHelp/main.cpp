
#define SDL_MAIN_HANDLED

#include <iostream> 
#include "sdl\include\SDL2\SDL.h"

const int width =800, height =600;

// ------------------------------
class ILogger {
public:
    virtual void Log(std::string message, int level =0) = 0;
};

class Logger : public ILogger {
    public:
    void Log(std::string message, int level =0) override {

    }
};

// -----------------------------
class Application 
{
public:
    Application(ILogger * logger) : logger(logger), 
                                    window(nullptr),
                                    window_surface(nullptr) {};
    bool InitSDL();

    bool Draw();

private:
    void Log(std::string msg, int level);
    
    SDL_Window  * window;
    SDL_Renderer *window_renderer;
    SDL_Surface * window_surface;
    SDL_Event     m_window_event;
    ILogger * logger;

public:
    ~Application();
};

bool Application::InitSDL() {
    SDL_Init( SDL_INIT_EVERYTHING );
    window = SDL_CreateWindow("SDL Test", 100, 100, width, height, SDL_WINDOW_ALLOW_HIGHDPI);

    if (window == nullptr) {
        Log("Could not create window.", 3);
        return false;
    }

    window_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // window_surface = SDL_GetWindowSurface(window);

    if(window_renderer == nullptr);
    {
        Log("Could not get renderer.", 3);
        return false;
    }
    return true;
}

void Application::Log(std::string msg, int level /* =0*/) {
    if (logger!=nullptr) {
        logger->Log(msg, level);
    }
}

bool Application::Draw() {
    SDL_RenderClear(window_renderer);

    SDL_Rect rect;
    rect.x = 250;
    rect.y = 150;
    rect.w = 200;
    rect.h = 200;

    SDL_SetRenderDrawColor(window_renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(window_renderer, &rect);

    SDL_SetRenderDrawColor(window_renderer, 0, 0, 0, 255);

    SDL_RenderPresent(window_renderer);
}

Application::~Application() 
{    
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// ------------------------------------

int main (int argc, char* argv[]) 
{
    Logger logger;
    Application app(&logger);
    
    if (!app.InitSDL()) {
        //std::getchar();
        return 0;
    }
    
    app.Draw();
    
    //

    // InitObjects();

    SDL_Event event;
    while (true) {
        SDL_PollEvent(&event);

        if ( SDL_QUIT == event.type) {
            break;
        }
    }
    return 0;
}