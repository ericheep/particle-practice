#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    randomButton.addListener(this, &ofApp::randomButtonPressed);
    swapButton.addListener(this, &ofApp::swapButtonPressed);
    explodeButton.addListener(this, &ofApp::explodeButtonPressed);

    gui.setup();
    gui.setDefaultWidth(50);
    gui.setDefaultHeight(12);
    gui.add(shapeTypeSlider.setup("shape", 0, 0, 6));
    gui.add(numMeshesSlider.setup("number meshes", 300, 0, 500));
    gui.add(pointSizeSlider.setup("point size", 0, 1, 20));
    gui.add(pointHueSlider.setup("point hue", 0.0, 0.0, 255));
    gui.add(pointSaturationSlider.setup("point saturation", 255, 0.0, 255));
    gui.add(rotateXSlider.setup("rotate x", 0.05, 0.0, 1.0));
    gui.add(fuzzySlider.setup("fuzzy", 0.0, 0.0, 1.5));
    gui.add(randomFollow.setup("random follow", 0.5, 0.0, 1.0));
    gui.add(simplexRate.setup("simplex size", 0., 0., 20.0));
    gui.add(simplexOffset.setup("simplex offset", 0.001, 0.0, 0.01));
    gui.add(simplexDepth.setup("simplex depth", 0.01, 0.01, 0.05));
    gui.add(simplexWrap.setup("simplex wrap", 2 * TWO_PI, 0.0, 4 * TWO_PI));
    gui.add(randomButton.setup("random position", 20, 20));
    gui.add(explodeButton.setup("explode", 20, 20));
    gui.add(swapButton.setup("swap", 20, 20));

    ofSetVerticalSync(TRUE);
    cam.setDistance(100);
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
        shapes[i].update();
        
        if (shapes[i].getShapeType() != shapeTypeSlider) {
            shapes[i].setShapeType(shapeTypeSlider);
        }
        
        if (shapes[i].getNumMeshes() != numMeshesSlider) {
            shapes[i].setMeshes(numMeshesSlider);
        }
        
        if (shapes[i].getRandomFollow() != randomFollow) {
            shapes[i].setRandomFollow(randomFollow);
        }
        
        if (shapes[i].getRotateX() != rotateXSlider) {
            shapes[i].setRotateX(rotateXSlider);
        }
        
        if (shapes[i].getPointSize() != pointSizeSlider) {
            shapes[i].setPointSize(pointSizeSlider);
        }
        
        shapes[i].setPointHue(pointHueSlider);
        shapes[i].setPointSaturation(pointSaturationSlider);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);

    ofEnableDepthTest();
    cam.begin();
    
    ofPushMatrix();
    ofRotateZDeg(xRotationInc);
    for (int i = 0;  i < shapes.size(); i++) {
        shapes[i].draw();
    }
    
    
    ofPopMatrix();
    // cam.rotateRad(rotateXSlider, 0, 0, 0);
    cam.end();
    ofDisableDepthTest();

    gui.draw();

}

void ofApp::randomButtonPressed() {
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].setRandomPosition();
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
