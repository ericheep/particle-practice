#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofDisableArbTex();
    
    shader.load("shader");
    
    randomButton.addListener(this, &ofApp::randomButtonPressed);
    swapButton.addListener(this, &ofApp::swapButtonPressed);
    explodeButton.addListener(this, &ofApp::explodeButtonPressed);

    
    gui.setup();
    gui.setSize(150, 70);
    gui.setDefaultHeight(12);
    gui.add(shapeTypeSlider.setup("shape", 0, 0, 6));
    gui.add(numMeshesSlider.setup("meshes", 200, 0, 300));
    gui.add(pointSizeSlider.setup("size", 0, 2, 15));
    gui.add(hueStartSlider.setup("hue start", 0.66, 0.0, 1.0));
    gui.add(hueDepthSlider.setup("hue depth", 0.1, 0.0, 1.0));
    gui.add(saturationSlider.setup("sat", 1.0, 0.0, 1.0));
    gui.add(rotateXSlider.setup("rotate", 0.05, 0.0, 0.5));
    gui.add(fuzzySlider.setup("fuzzy", 0.0, 0.0, 1.5));
    gui.add(randomFollow.setup("follow", 0.9, 0.0, 1.0));
    gui.add(simplexRate.setup("simp size", 0.0, 0., 20.0));
    gui.add(simplexOffset.setup("simp offset", 0.002, 0.0, 0.01));
    gui.add(simplexDepth.setup("simp depth", 0.01, 0.01, 0.05));
    gui.add(simplexWrap.setup("simp wrap", 2 * TWO_PI, 0.0, 4 * TWO_PI));
    gui.add(fresnelPowerSlider.setup("fresnel pow", 1.0, 0.001, 10.));
    gui.add(randomButton.setup("random", 20, 12));
    gui.add(explodeButton.setup("explode", 20, 12));
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
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    ofEnableDepthTest();
    ofVec3f cameraPosition = cam.getGlobalPosition();
    // cout << cameraPosition << endl;
    //ofVec3f centroid = shapes[0].getCentroid();
    //ofVec3f dir = camPosition - centroid;
    
    cam.begin();
    {
        ofPushMatrix();
        ofRotateZDeg(xRotationInc);
        shader.begin();
        {
            shader.setUniform3f("u_cameraPosition", cameraPosition);
            shader.setUniform1f("u_hueStart", hueStartSlider);
            shader.setUniform1f("u_hueDepth", hueDepthSlider);
            shader.setUniform1f("u_saturation", saturationSlider);
            shader.setUniform1f("u_power", fresnelPowerSlider);

            for (int i = 0;  i < shapes.size(); i++) {
                shapes[i].update();
                shapes[i].draw();
                shapes[i].clearMesh();
            }
        }
        shader.end();
        
        //cam.rotateRad(rotateXSlider, 0, 0, 0);
        ofPopMatrix();

    }
    cam.end();
    //
    
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
