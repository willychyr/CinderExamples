#include "cinder/app/AppBasic.h"
#include "cinder/ImageIO.h"
#include "cinder/gl/Texture.h"
#include "cinder/Perlin.h"
#include "cinder/Channel.h"
#include "cinder/Vector.h"
#include "cinder/Utilities.h"
#include "ParticleController.h"
#include <vector>

#define RESOLUTION 10
#define NUM_PARTICLES_TO_SPAWN 55

using namespace ci;
using namespace ci::app;
using std::vector;

class TutorialApp : public AppBasic {
 public:
	void prepareSettings( Settings *settings );
	void keyDown( KeyEvent event );
	void mouseDown( MouseEvent event );
	void mouseUp( MouseEvent event );
	void mouseMove( MouseEvent event );
	void mouseDrag( MouseEvent event );
	void setup();
	void update();
	void draw();
	
	Perlin mPerlin;
	
	Vec2i mMouseLoc;
	Vec2f mMouseVel;
	bool mIsPressed;
	
	ParticleController mParticleController;
	
	bool mDrawParticles;
	bool mSaveFrames;
    
    std::vector <ParticleController> multiLines;
    
    Vec2f centerPoint;
};

void TutorialApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 800, 600 );
	settings->setFrameRate( 50.0f );
}

void TutorialApp::setup()
{	
	mPerlin = Perlin();
	
	//Url url( "http://www.libcinder.org/media/tutorial/paris.jpg" );
	//mChannel = Channel32f( loadImage( loadUrl( url ) ) );
	//mTexture = mChannel;

	mMouseLoc = Vec2i( 0, 0 );
	mMouseVel = Vec2f::zero();
	mDrawParticles = true;
	mIsPressed = false;
	mSaveFrames = false;
    
    gl::enableAlphaBlending();   
    
    centerPoint.set( getWindowWidth()/2, getWindowHeight()/2 );
    mParticleController.addParticles( NUM_PARTICLES_TO_SPAWN, centerPoint, mMouseVel );    

}


void TutorialApp::mouseDown( MouseEvent event )
{
	mIsPressed = true;
}

void TutorialApp::mouseUp( MouseEvent event )
{
	mIsPressed = false;
}

void TutorialApp::mouseMove( MouseEvent event )
{
	mMouseVel = ( event.getPos() - mMouseLoc );
	mMouseLoc = event.getPos();
}

void TutorialApp::mouseDrag( MouseEvent event )
{
	mouseMove( event );
}

void TutorialApp::keyDown( KeyEvent event )
{

	
	if( event.getChar() == 's' ){
		mSaveFrames = ! mSaveFrames;
	}
}

void TutorialApp::update()
{
	
	
	if( mIsPressed ){
		//mParticleController.addParticles( NUM_PARTICLES_TO_SPAWN, mMouseLoc, mMouseVel );
        ParticleController sampleLine;
    
        sampleLine.init();
        
        sampleLine.addParticles( NUM_PARTICLES_TO_SPAWN, mMouseLoc, mMouseVel );
        
        multiLines.push_back(sampleLine);
    }

    for (int i = 0; i < multiLines.size(); i++) {
        multiLines[i].update( mPerlin, mMouseLoc );
        
        if (multiLines[i].dead) {
            multiLines.erase (multiLines.begin()+i);
        }
    }
    
    console() << toString(multiLines.size() ) + "\n" << std::endl;
        
	mParticleController.update( mPerlin, mMouseLoc );
}

void TutorialApp::draw()
{	
	gl::clear( Color( 0, 0, 0 ), true );
		
	if( mDrawParticles ){
		glDisable( GL_TEXTURE_2D );
		mParticleController.draw();
        
        for (int i = 0; i < multiLines.size(); i++) {
            multiLines[i].draw();
        }
	}
	
	if( mSaveFrames ){
		writeImage( getHomeDirectory() + "image_" + toString( getElapsedFrames() ) + ".png", copyWindowSurface() );
	}
}

CINDER_APP_BASIC( TutorialApp, RendererGl )
