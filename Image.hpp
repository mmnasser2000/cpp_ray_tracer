#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>

class Image
{
	public:
		Image();
		~Image();
		void Initialize(const int xSize, const int ySize, SDL_Renderer *pRenderer);
	
		void SetPixel(const int x, const int y, const double red, const double green, const double blue);
		void Display();

		int getXSize();
		int getYSize();

		
	private:
		Uint32 ConvertColor(const double red, const double green, const double blue);
		void InitTexture();
		void ComputeMaxValues();
		
		std::vector<std::vector<double>> m_rChannel;
		std::vector<std::vector<double>> m_gChannel;
		std::vector<std::vector<double>> m_bChannel;
		
		int m_xSize;
		int m_ySize;

		double m_max_red, m_max_green, m_max_blue, m_overall_max;
		
		SDL_Renderer *m_pRenderer;
		SDL_Texture *m_pTexture;

};

#endif