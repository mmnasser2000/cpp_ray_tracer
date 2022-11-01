#include "RayTracerApp.h"
#include <ctime>

int main(int argc, char **argv) {
    auto start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);
    std::cout << "started at " << std::ctime(&start_time) << std::endl;

   RayTracerApp app;
   return app.execute();
}