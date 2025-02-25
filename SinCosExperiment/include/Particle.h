#pragma once
#include "cinder/Channel.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"

#include <vector>

class Particle {
 public:
	Particle();
	Particle( ci::Vec2f );
	void update();
	void draw();
	
	ci::Vec2f	mLoc;
	ci::Vec2f	mDir;
	float		mVel;
	
	float		mRadius;
	ci::Color	mColor;
    
    float   r, g, b, alphaValue;
};