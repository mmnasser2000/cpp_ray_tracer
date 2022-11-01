#ifndef RayTracerAppH
#define RayTracerAppH

#include <SDL2/SDL.h>
#include "Image.hpp"
#include "scene.h"
#include "camera.hpp"

class RayTracerApp {

    public:
        RayTracerApp();
        int execute();
        bool init();
        void event(SDL_Event *e);
        void loop();
        void render();
        void exit();
        
    private:   
        void PrintVector(const qbVector<double> &inputVector);
        Image m_image;
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;
        Scene scene;
};

#endif