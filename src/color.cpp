#include "color.hpp"

#include <cmath>
#include <algorithm>

Color& Color::HSV() {
	if (!this->isRGB) return *this;

	double nr = this->r / 255.0;
	double ng = this->g / 255.0;
	double nb = this->b / 255.0;

	this->h = 0.0f;
	this->s = 0.0f;
	this->v = 0.0f;

	double maxCh = std::max(nr, std::max(ng, nb));
	double minCh = std::min(nr, std::min(ng, nb));
	double range = maxCh - minCh;

	// Brightness
	this->v = maxCh;

	// Saturate 
	if (maxCh != 0) this->s = range / maxCh;
	else { 
		this->h = -1;
		this->s = 0;
		return *this;    
	}
	

	if (maxCh == nr) this->h = (ng - nb) / range;
	else if (maxCh == ng) this->h = 2 + (nb - ng) / range;    
	else this->h = 4 + (nr - ng) / range;
	
	this->h *= 60.0f;
	if (this->h < 0) this->h += 360;
	
	this->isRGB = false;

	return *this;
}

Color& Color::RGB() {

	if (this->isRGB) return *this;

	double fR, fG, fB;

	double fC = this->v * this->s;
	double fHPrime = std::fmod(this->h / 60.0, 6);
	double fX = fC * (1 - std::fabs(std::fmod(fHPrime, 2) - 1));
	double fM = this->v - fC;
	
	if(0 <= fHPrime && fHPrime < 1) {
		fR = fC;
		fG = fX;
		fB = 0;
	} else if(1 <= fHPrime && fHPrime < 2) {
		fR = fX;
		fG = fC;
		fB = 0;
	} else if(2 <= fHPrime && fHPrime < 3) {
		fR = 0;
		fG = fC;
		fB = fX;
	} else if(3 <= fHPrime && fHPrime < 4) {
		fR = 0;
		fG = fX;
		fB = fC;
	} else if(4 <= fHPrime && fHPrime < 5) {
		fR = fX;
		fG = 0;
		fB = fC;
	} else if(5 <= fHPrime && fHPrime < 6) {
		fR = fC;
		fG = 0;
		fB = fX;
	} else {
		fR = 0;
		fG = 0;
		fB = 0;
	}
  
	fR += fM;
	fG += fM;
	fB += fM; 

	this->r = std::round(fR * 255.0);
	this->g = std::round(fG * 255.0);
	this->b = std::round(fB * 255.0);

	this->isRGB = true;

	return *this;
}
