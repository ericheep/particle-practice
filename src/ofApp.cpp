#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();
    
    lighting.load("lighting");
    
    randomButton.addListener(this, &ofApp::randomButtonPressed);
    swapButton.addListener(this, &ofApp::swapButtonPressed);
    explodeButton.addListener(this, &ofApp::explodeButtonPressed);

    gui.setup();
    gui.setSize(150, 70);
    gui.setDefaultHeight(12);
    gui.add(primitiveTypeSlider.setup("primitive type", 0, 0, 3));
    gui.add(shapeTypeSlider.setup("shape", 0, 0, 7));
    gui.add(numMeshesSlider.setup("meshes", 200, 0, 400));
    gui.add(pointSizeSlider.setup("size", 2, 1, 15));
    gui.add(rotateXSlider.setup("rotate x", 0.0, 0.0, 1.0));
    gui.add(rotateYSlider.setup("rotate y", 0.0, 0.0, 1.0));
    gui.add(rotateZSlider.setup("rotate z", 0.0, 0.0, 1.0));

    gui.add(fuzzySlider.setup("fuzzy", 0.0, 0.0, 10.0));
    gui.add(randomFollow.setup("follow", 0.9, 0.0, 1.0));
    
    gui.add(simplexAmountSlider.setup("simp amount", 5, 0, 25));
    gui.add(simplexOffset.setup("simp offset", 0.004, 0.0, 0.01));
    gui.add(simplexDepth.setup("simp depth", 0.01, 0.0, 0.10));
    gui.add(simplexWrap.setup("simp wrap", 2 * TWO_PI, 0.0, 2 * TWO_PI));
    gui.add(simplexPow.setup("simp pow", 1.0, 0.0, 8.0));

    gui.add(hueStartSlider.setup("hue start", 0.75, 0.0, 1.0));
    gui.add(hueDepthSlider.setup("hue depth", 0.05, 0.0, 1.0));
    gui.add(hueCurveSlider.setup("hue curve", 1.2, 0.0, 5.0));
    
    gui.add(saturationAmountSlider.setup("sat amount", 1.0, 0.0, 1.0));
    gui.add(saturationCurveSlider.setup("sat curve", 1.0, 0.0, 2.0));
    
    gui.add(brightnessAmountSlider.setup("bri amount", 1.0, 0.0, 1.0));
    gui.add(brightnessCurveSlider.setup("bri curve", 1.0, 0.0, 2.0));
    
    gui.add(alphaAmountSlider.setup("alpha amount", 1.0, 0.0, 1.0));
    gui.add(alphaCurveSlider.setup("alpha curve", 1.0, 0.0, 2.0));
    
    gui.add(bumpDepthSlider.setup("bump depth", 1.0, 0.0, 1000.0));
    gui.add(scaleFactorSlider.setup("scale factor", 0.0, -10.0, 10.0));

    gui.add(randomButton.setup("random", 20, 12));
    // gui.add(explodeButton.setup("explode", 20, 12));
    gui.add(swapButton.setup("swap", 20, 12));

    ofSetVerticalSync(TRUE);
    cam.setDistance(300);
    cam.setTarget(ofVec3f(0.0, 0.0, 0.0));
    
    shapes.push_back(Shape(100, 8, 2, 100));
    shapes[0].setShapeType(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].setFuzzy(fuzzySlider);
        shapes[i].setSimplexMorph(simplexAmountSlider, simplexDepth, simplexOffset, simplexWrap, simplexPow);
        
        shapes[i].setPrimitiveType(primitiveTypeSlider);
        shapes[i].setShapeType(shapeTypeSlider);
        shapes[i].setMeshes(numMeshesSlider);
        shapes[i].setRandomFollow(randomFollow);
        shapes[i].setPointSize(pointSizeSlider);
        
        ofVec3f rotation = ofVec3f(rotateXSlider, rotateYSlider, rotateZSlider);
        shapes[i].setRotation(rotation);
        
        shapes[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    ofEnableDepthTest();
    
    ofVec3f cameraPosition = cam.getGlobalPosition();
    
    cam.begin();
    {
        lighting.begin();
        {
            for (int i = 0;  i < shapes.size(); i++) {
                shapes[i].draw();
                shapes[i].clearMesh();
            }
            
            lighting.setUniform3f("u_cameraPosition", cameraPosition);
            lighting.setUniform1f("u_hueStart", hueStartSlider);
            lighting.setUniform1f("u_hueDepth", hueDepthSlider);
            lighting.setUniform1f("u_hueCurve", hueCurveSlider);
            
            lighting.setUniform1f("u_saturationAmount", saturationAmountSlider);
            lighting.setUniform1f("u_saturationCurve", saturationCurveSlider);

            lighting.setUniform1f("u_brightnessAmount", brightnessAmountSlider);
            lighting.setUniform1f("u_brightnessCurve", brightnessCurveSlider);
            
            lighting.setUniform1f("u_alphaAmount", alphaAmountSlider);
            lighting.setUniform1f("u_alphaCurve", alphaCurveSlider);
            
            lighting.setUniform1f("u_bumpDepth", bumpDepthSlider);
        }
        lighting.end();
    }
    cam.end();
    
    ofDisableDepthTest();
    gui.draw();
}

void ofApp::randomButtonPressed() {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].random();
    }
}

void ofApp::swapButtonPressed() {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].swap();
    }
}

void ofApp::explodeButtonPressed() {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].explode();
    }
}
