#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "Image.hpp"
#include "camera.hpp"
#include "objectsphere.hpp"
#include "objectplane.hpp"
#include "objectcone.hpp"
#include "pointlight.hpp"

#define KA 0.3
#define KD 0.7

class Scene {
	public:
		Scene();		
		
		bool Render(Image &outputImage);
		
	private:
		Camera m_camera;
		std::vector<std::shared_ptr<ObjectAbstract>> m_objects;
		std::vector<std::shared_ptr<LightAbstract>> m_lights;
		
		
};


#endif
