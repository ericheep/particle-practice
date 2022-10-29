//
//  Shape.cpp
//  pinkParticles
//
//  Created by Eric Heep on 9/22/22.
//

#include "Shape.hpp"

Shape::Shape(int _meshes, float _ma, float _mb, float _radius) {
    a = 1;
    b = 1;
    
    fuzzy = 0.1;
    randomFollow = 0.05;
        
    ma = _ma;
    mb = _mb;
    radius = _radius;
    
    setMeshes(_meshes);
    mesh.setMode(OF_PRIMITIVE_POINTS);
        
    glEnable(GL_POINT_SMOOTH);
    glPointSize(2);
}

void Shape::setShapeA(float m, float n1, float n2, float n3) {
  ma = m;
  n1a = n1;
  n2a = n2;
  n3a = n3;
}

void Shape::setShapeB(float m, float n1, float n2, float n3) {
  mb = m;
  n1b = n1;
  n2b = n2;
  n3b = n3;
}

void Shape::setPointSize(int _pointSize) {
    pointSize = _pointSize;
    glPointSize(pointSize);
}

int Shape::getPointSize() {
    return pointSize;
}

void Shape::setRandomPosition() {
    for (int i = 0; i < numMeshes + 1; i++) {
        for (int j = 0; j < numMeshes + 1; j++) {
            float x = ofRandom(-ofGetWidth(), ofGetWidth());
            float y = ofRandom(-ofGetWidth(), ofGetWidth());
            float z = ofRandom(-ofGetWidth(), ofGetWidth());

            particles[i][j].setPosition(x, y, z);
        };
    }
}

void Shape::swap() {
    for (int i = 0; i < numMeshes + 1; i++) {
        for (int j = 0; j < numMeshes + 1; j++) {
            ofVec3f position = particles[i][j].getPosition();
            particles[i][j].setPosition(-position);
        }
    }
}

void Shape::explode() {
    
}

void Shape::setRotateX(float rotationInc) {
    xRotationInc = rotationInc;
}

float Shape::getRotateX() {
    return xRotationInc;
}

void Shape::setRandomFollow(float randomFollow) {
    for (int i = 0; i < numMeshes + 1; i++) {
        for (int j = 0; j < numMeshes + 1; j++) {
            float mapped = ofMap(randomFollow, 0.0, 1.0, 0.001, 0.1);
            float rf = ofRandom(0.001, mapped);
            particles[i][j].setFollow(rf);
        }
    }
}

void Shape::setMeshes(int _numMeshes) {
    numMeshes = _numMeshes;

    for (int i = 0; i < numMeshes + 1; i++) {
        vector<Particle> particleRow;
        for (int j = 0; j < numMeshes + 1; j++) {
            float scalar = (i * numMeshes + j) / pow(numMeshes, 2.0);
            
            Particle p = Particle(0, 0, 0);
            p.setScalar(scalar);
            
            particleRow.push_back(p);
        
        }
        particles.push_back(particleRow);
    }
    
    updateShape();
    setRandomFollow(randomFollow);
}

void Shape::updateShape() {
   for (int i = 0; i < numMeshes + 1; i++) {
     float lat = ofMap(i, 0, numMeshes, -HALF_PI, HALF_PI);

     float r2 = supershape(lat, mb, n1b, n2b, n3b);

     for (int j = 0; j < numMeshes + 1; j++) {
       float lon = ofMap(j, 0, numMeshes, -PI, PI);
       float r1 = supershape(lon, ma, n1a, n2a, n3a);

       float x = radius * r1 * cos(lon) * r2 * cos(lat);
       float y = radius * r1 * sin(lon) * r2 * cos(lat);
       float z = radius * r2 * sin(lat);

       particles[i][j].updateTarget(x, y, z);
     }
   }
 }

void Shape::update(){
    for (int i = 0; i < numMeshes + 1; i++) {
        for (int j = 0; j < numMeshes + 1; j++) {
        
            if (fuzzy > 0) {
                particles[i][j].pos.x += ofRandom(-fuzzy, fuzzy);
                particles[i][j].pos.y += ofRandom(-fuzzy, fuzzy);
                particles[i][j].pos.z += ofRandom(-fuzzy, fuzzy);
            }
            particles[i][j].update();
        }
    }
}

void Shape::setFuzzy(float _fuzzy){
    fuzzy = _fuzzy;
}

void Shape::setPointHue(float _hue) {
    hue = _hue;
}

void Shape::setPointSaturation(float _saturation) {
    saturation = _saturation;
}

void Shape::setSimplexMorph(float _rate, float _depth, float _offset, float _wrap){
    for (int i = 0; i < numMeshes + 1; i++) {
        for (int j = 0; j < numMeshes + 1; j++) {
            particles[i][j].setSimplexMorph(_rate, _depth, _offset, _wrap);
        }
    }
}

void Shape::draw(){
    ofColor color;
    color.setHsb(hue, saturation, 255);
    ofSetColor(color);
        
    for (int i = 0; i < numMeshes + 1; i++) {
        for (int j = 0; j < numMeshes + 1; j++) {
            mesh.addVertex(particles[i][j].getPosition());
        }
    }
    
    mesh.drawVertices();
    mesh.clearVertices();
}

float Shape::supershape(float theta, float m, float n1, float n2, float n3) {
    float t1 = fabs((1.0 / a) * cos(m * theta / 4.0));
    t1 = pow(t1, n2);
    float t2 = fabs((1.0/ b) * sin(m * theta / 4.0));
    t2 = pow(t2, n3);
    float t3 = t1 + t2;
    
    return pow(t3, -1 / n1);
}

void Shape::setShapeType(int which) {
    switch(which) {
        case 0:
            // sphere
            setShapeA(0, 1, 1, 1);
            setShapeB(0, 1, 1, 1);
            updateShape();
            break;
        case 1:
            //squirtle
            setShapeA(8, 60, 100, 30);
            setShapeB(2, 10, 10, 10);
            updateShape();
            break;
        case 2:
            // flower
            setShapeA(6, 1, 1, 1);
            setShapeB(3, 1, 1, 1);
            updateShape();
            break;
        case 3:
            // ufo
            setShapeA(0.2, 0.1, 1.7, 1.7);
            setShapeB(2.0, 0.5, 0.2, 0.2);
            updateShape();
            break;
        case 4:
            // super flower
            setShapeA(5.2, 0.04, 1.70, 1.70);
            setShapeB(0., 1.0, 1.0, 1.0);
            updateShape();
            break;
        case 5:
            // classic
            setShapeA(8.0, -8.11, -0.08, 93);
            setShapeB(2.0, 0.99, 97.67, -0.439);
            updateShape();
            break;
        case 6:
            // symbol
            setShapeA(6, 60., 55, 1000);
            setShapeB(6, 250, 100, 100);
            updateShape();
            break;
    }
    shapeType = which;
}

int Shape::getShapeType() {
    return shapeType;
}

int Shape::getNumMeshes() {
    return numMeshes;
}

float Shape::getRandomFollow() {
    return randomFollow;
}
