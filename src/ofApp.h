#pragma once

#include "ofxGui.h"
#include "ofMain.h"
#include "Shape.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        vector<Shape> shapes;

        void randomButtonPressed();
        void swapButtonPressed();
        void explodeButtonPressed();
		
        void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        float xRotationInc;
    
        ofEasyCam cam;
        ofShader shader;
    
        ofxIntSlider shapeTypeSlider;
        ofxIntSlider numMeshesSlider;
        ofxIntSlider pointSizeSlider;
        ofxFloatSlider pointHueSlider;
        ofxFloatSlider pointSaturationSlider;
        ofxFloatSlider fuzzySlider;
        ofxFloatSlider randomFollow;
        ofxFloatSlider simplexRate;
        ofxFloatSlider simplexDepth;
        ofxFloatSlider simplexOffset;
        ofxFloatSlider simplexWrap;
        ofxFloatSlider rotateXSlider;
        ofxButton randomButton;
        ofxButton explodeButton;
        ofxButton swapButton;
    
        ofxPanel gui;
};
