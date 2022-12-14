#pragma once

#include "ofxGui.h"
#include "ofMain.h"
#include "Shape.hpp"
#include "ofxShaderFilter.h"
#include "ofShader.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        vector<Shape> shapes;

        void randomButtonPressed();
        void swapButtonPressed();
        void explodeButtonPressed();
        
        ofEasyCam cam;
        ofShader lighting;

        ofxIntSlider primitiveTypeSlider;
        ofxIntSlider shapeTypeSlider;
        ofxIntSlider numMeshesSlider;
        ofxIntSlider pointSizeSlider;
    
        ofxFloatSlider fuzzySlider;
        ofxFloatSlider randomFollow;
    
        // simplex sliders
        ofxFloatSlider simplexAmountSlider;
        ofxFloatSlider simplexDepth;
        ofxFloatSlider simplexOffset;
        ofxFloatSlider simplexWrap;
        ofxFloatSlider simplexPow;

        // rotation sliders
        ofxFloatSlider rotateXSlider;
        ofxFloatSlider rotateYSlider;
        ofxFloatSlider rotateZSlider;
    
        // fresnel sliders
        ofxFloatSlider hueStartSlider;
        ofxFloatSlider hueDepthSlider;
        ofxFloatSlider hueCurveSlider;
    
        ofxFloatSlider saturationAmountSlider;
        ofxFloatSlider saturationCurveSlider;
    
        ofxFloatSlider brightnessAmountSlider;
        ofxFloatSlider brightnessCurveSlider;
    
        ofxFloatSlider alphaAmountSlider;
        ofxFloatSlider alphaCurveSlider;
    
        ofxFloatSlider scaleFactorSlider;
        ofxFloatSlider bumpDepthSlider;

        ofxButton randomButton;
        ofxButton explodeButton;
        ofxButton swapButton;
    
        ofxPanel gui;
};
