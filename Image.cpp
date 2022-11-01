#include "Image.hpp"
#include <fstream>

Image::Image() {
	m_xSize = 0;
	m_ySize = 0;
	m_pTexture = NULL;
}

Image::~Image() {
	if (m_pTexture != NULL)
		SDL_DestroyTexture(m_pTexture);
}

void Image::Initialize(const int xSize, const int ySize, SDL_Renderer* pRenderer) {
	m_rChannel.resize(xSize, std::vector<double>(ySize, 0));
	m_gChannel.resize(xSize, std::vector<double>(ySize, 0));
	m_bChannel.resize(xSize, std::vector<double>(ySize, 0));
	
	m_xSize = xSize;
	m_ySize = ySize;
	
	m_pRenderer = pRenderer;
	
	InitTexture();	
}

void Image::SetPixel(const int x, const int y, const double red, const double green, const double blue) {
	m_rChannel.at(x).at(y) = red;
	m_gChannel.at(x).at(y) = green;
	m_bChannel.at(x).at(y) = blue;
}

void Image::Display() {
	ComputeMaxValues();

	Uint32 *tempPixels = new Uint32[m_xSize * m_ySize];
	
	memset(tempPixels, 0, m_xSize * m_ySize * sizeof(Uint32));
	
	for (int x=0; x<m_xSize; ++x) {
		for (int y=0; y<m_ySize; ++y) {
			tempPixels[(y*m_xSize)+x] = ConvertColor(m_rChannel.at(x).at(y), m_gChannel.at(x).at(y), m_bChannel.at(x).at(y));
		}
	}
	
	SDL_UpdateTexture(m_pTexture, NULL, tempPixels, m_xSize * sizeof(Uint32));	
	
	delete[] tempPixels;
	
	SDL_Rect srcRect, bounds;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = m_xSize;
	srcRect.h = m_ySize;
	bounds = srcRect;
	SDL_RenderCopy(m_pRenderer, m_pTexture, &srcRect, &bounds);	
}

void Image::InitTexture() {
	Uint32 rmask, gmask, bmask, amask;
	
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
	#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
	#endif
	
	if (m_pTexture != NULL)
		SDL_DestroyTexture(m_pTexture);
	
	SDL_Surface *tempSurface = SDL_CreateRGBSurface(0, m_xSize, m_ySize, 32, rmask, gmask, bmask, amask);
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);	
}

Uint32 Image::ConvertColor(const double red, const double green, const double blue) {
	unsigned char r = static_cast<unsigned char>((red/m_overall_max) * 255);
	unsigned char g = static_cast<unsigned char>((green/m_overall_max) * 255);
	unsigned char b = static_cast<unsigned char>((blue/m_overall_max) * 255);

	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Uint32 pixelColor = (b << 24) + (g << 16) + (r << 8) + 255;
	#else
		Uint32 pixelColor = (255 << 24) + (b << 16) + (g << 8) + r;
	#endif
	
	return pixelColor;
}

int Image::getXSize() {
	return m_xSize;
}
int Image::getYSize() {
	return m_ySize;
}

void Image::ComputeMaxValues() {
	m_max_red = 0.0;
	m_max_green = 0.0;
	m_max_blue = 0.0;
	m_overall_max = 0.0;


	for (int x=0; x<m_xSize; ++x) {
		for (int y=0; y<m_ySize; ++y) {
			double red_value = m_rChannel.at(x).at(y);
			double green_value = m_gChannel.at(x).at(y);
			double blue_value = m_bChannel.at(x).at(y);
			
			if (red_value > m_max_red) {
				m_max_red = red_value;
			}
			if (green_value > m_max_green) {
				m_max_green = green_value;
			}	
			if (blue_value > m_max_blue) {
				m_max_blue = blue_value;
			}
			if (m_max_red > m_overall_max) {
				m_overall_max = m_max_red;
			}
			if (m_max_green > m_overall_max) {
				m_overall_max = m_max_green;
			}
			if (m_max_blue > m_overall_max) {
				m_overall_max = m_max_blue;
			}
		}
	}
}