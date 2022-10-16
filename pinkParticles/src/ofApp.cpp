#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableDepthTest();
    ofSetVerticalSync(TRUE);
    
    cam.setDistance(150);
    
    gui.setup();
    gui.add(fuzzy.setup("fuzzy", 100, 0.0, 1.0));

    
    shapes.push_back(Shape(500, 8, 2, 100));
    shapes[0].setShapeA(8.0, -8.11, -0.08, 93);
    shapes[0].setShapeB(2.0, 0.99, 97.67, -0.439);
    shapes[0].updateShape();
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].setFuzzy(fuzzy);
        shapes[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofBackground(255, 182, 193);
    
    for (int i = 0;  i < shapes.size(); i++) {
        shapes[i].draw();
    }
    
    cam.end();
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
