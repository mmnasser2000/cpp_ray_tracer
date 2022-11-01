#include "RayTracerApp.h"
#include "./qbLinAlg/qbVector.h"
#include <ctime>

RayTracerApp::RayTracerApp() {
        isRunning = true;
        window = NULL;
        renderer = NULL;
}

bool RayTracerApp::init() {
    if (SDL_INIT_EVERYTHING < 0) {
        return false;
    }
    window = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
    
    if (window != NULL) {
        renderer = SDL_CreateRenderer(window, -1, 0);
        m_image.Initialize(1280, 720, renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        scene.Render(m_image);
        m_image.Display();
        
        auto end = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);
        std::cout << "ended at " << std::ctime(&end_time) << std::endl;
        
        SDL_RenderPresent(renderer);
    } else {
        return false;
    }
    return true;
}
int RayTracerApp::execute() {
    SDL_Event sdlEvent;
    if (!init()) {
        return -1;
    }
    while (isRunning) {
        while (SDL_PollEvent(&sdlEvent) != 0) {
            event(&sdlEvent);
        }
        loop();
        render();
    }
    return 0;
}
void RayTracerApp::event(SDL_Event *e) {
    if (e->type == SDL_QUIT) {
        isRunning = false;
    }
}
void RayTracerApp::loop() {
    
}
void RayTracerApp::render() {
    
}
void RayTracerApp::exit() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

void RayTracerApp::PrintVector(const qbVector<double> &inputVector) {
	int nRows = inputVector.GetNumDims();
	for (int row=0; row<nRows; ++row) {
		std::cout << std::fixed << std::setprecision(3) << inputVector.GetElement(row) << std::endl;
	}
}