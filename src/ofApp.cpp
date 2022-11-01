#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();
    
    fresnel.load("fresnel");
    
    randomButton.addListener(this, &ofApp::randomButtonPressed);
    swapButton.addListener(this, &ofApp::swapButtonPressed);
    explodeButton.addListener(this, &ofApp::explodeButtonPressed);

    gui.setup();
    gui.setSize(150, 70);
    gui.setDefaultHeight(12);
    gui.add(shapeTypeSlider.setup("shape", 1, 0, 6));
    gui.add(numMeshesSlider.setup("meshes", 300, 0, 400));
    gui.add(pointSizeSlider.setup("size", 2, 1, 15));
    gui.add(rotateXSlider.setup("rotate x", 0.0, 0.0, 1.0));
    gui.add(rotateYSlider.setup("rotate y", 0.0, 0.0, 1.0));
    gui.add(rotateZSlider.setup("rotate z", 0.0, 0.0, 1.0));

    gui.add(fuzzySlider.setup("fuzzy", 0.0, 0.0, 10.0));
    gui.add(randomFollow.setup("follow", 0.9, 0.0, 1.0));
    
    gui.add(simplexRate.setup("simp size", 2, 0., 20.0));
    gui.add(simplexOffset.setup("simp offset", 0.004, 0.0, 0.01));
    gui.add(simplexDepth.setup("simp depth", 0.025, 0.01, 0.05));
    gui.add(simplexWrap.setup("simp wrap", 2 * TWO_PI, 0.0, 4 * TWO_PI));

    gui.add(hueStartSlider.setup("hue start", 0.75, 0.0, 1.0));
    gui.add(hueDepthSlider.setup("hue depth", 0.05, 0.0, 1.0));
    gui.add(hueCurveSlider.setup("hue curve", 1.2, 0.0, 5.0));
    
    gui.add(saturationStartSlider.setup("saturation start", 0.2, 0.0, 1.0));
    gui.add(saturationDepthSlider.setup("saturation depth", 1.0, 0.0, 1.0));
    gui.add(saturationCurveSlider.setup("saturation curve", 1.6, 0.0, 5.0));
    
    gui.add(brightnessStartSlider.setup("bri start", 1.0, 0.0, 1.0));
    gui.add(brightnessDepthSlider.setup("bri depth", 0.4, 0.0, 1.0));
    gui.add(brightnessCurveSlider.setup("bri curve", 3.4, 0.0, 5.0));
    
    gui.add(bumpDepthSlider.setup("bump depth", 0.03, 0.0, 1.0));

    gui.add(randomButton.setup("random", 20, 12));
    // gui.add(explodeButton.setup("explode", 20, 12));
    gui.add(swapButton.setup("swap", 20, 12));

    ofSetVerticalSync(TRUE);
    cam.setDistance(300);
    cam.setTarget(ofVec3f(0.0, 0.0, 0.0));
    
    shapes.push_back(Shape(500, 8, 2, 100));
    shapes[0].setShapeType(0);
    
    xRotationInc = 0.0;
}

//--------------------------------------------------------------
void ofApp::update(){
    xRotationInc += rotateXSlider;
    
    if (xRotationInc > 360) {
        xRotationInc -= 360;
    }
        
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].setFuzzy(fuzzySlider);
        shapes[i].setSimplexMorph(simplexRate, simplexDepth, simplexOffset, simplexWrap);
        
        if (shapes[i].getShapeType() != shapeTypeSlider) {
            shapes[i].setShapeType(shapeTypeSlider);
        }
        
        if (shapes[i].getNumMeshes() != numMeshesSlider) {
            shapes[i].setMeshes(numMeshesSlider);
        }
        
        if (shapes[i].getRandomFollow() != randomFollow) {
            shapes[i].setRandomFollow(randomFollow);
        }
        
        ofVec3f rot = ofVec3f(rotateXSlider, rotateYSlider, rotateZSlider);
        shapes[i].rotate(rot);
        
        if (shapes[i].getPointSize() != pointSizeSlider) {
            shapes[i].setPointSize(pointSizeSlider);
        }
        
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
        fresnel.begin();
        {
            for (int i = 0;  i < shapes.size(); i++) {
                shapes[i].draw();
                shapes[i].clearMesh();
            }
            
            fresnel.setUniform3f("u_cameraPosition", cameraPosition);
            fresnel.setUniform1f("u_hueStart", hueStartSlider);
            fresnel.setUniform1f("u_hueDepth", hueDepthSlider);
            fresnel.setUniform1f("u_hueCurve", hueCurveSlider);
            
            fresnel.setUniform1f("u_saturationStart", saturationStartSlider);
            fresnel.setUniform1f("u_saturationDepth", saturationDepthSlider);
            fresnel.setUniform1f("u_saturationCurve", saturationCurveSlider);

            fresnel.setUniform1f("u_brightnessStart", brightnessStartSlider);
            fresnel.setUniform1f("u_brightnessDepth", brightnessDepthSlider);
            fresnel.setUniform1f("u_brightnessCurve", brightnessCurveSlider);
            
            fresnel.setUniform1f("u_saturation", saturationSlider);
            fresnel.setUniform1f("u_bumpDepth", bumpDepthSlider);
        }
        fresnel.end();

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

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
