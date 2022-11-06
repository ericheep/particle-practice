//
//  Particle.cpp
//  pinkParticles
//
//  Created by Eric Heep on 9/22/22.
//

#include "Particle.hpp"

Particle::Particle(float _x, float _y, float _z) {
    pos.x = 0;
    pos.y = 0;
    pos.z = 0;
    
    tar.x = x;
    tar.y = y;
    tar.z = z;
    
    off = 0.0;
    
    morph.x = 0;
    morph.y = 0;
    morph.z = 0;
    
    scalar = 0.0;
}

void Particle::updateTarget(float _x, float _y, float _z) {
    tar.x = _x;
    tar.y = _y;
    tar.z = _z;
}

ofVec3f Particle::getTarget() {
    return tar;
}

void Particle::setTarget(ofVec3f _tar) {
    tar = _tar;
}

void Particle::setPosition(float _x, float _y, float _z) {
    pos.x = _x;
    pos.y = _y;
    pos.z = _z;
}

void Particle::setPosition(ofVec3f _pos) {
    pos = _pos;
}

void Particle::setNormal(ofVec3f _normal) {
    normal = _normal;
}

ofVec3f Particle::getNormal() {
    return normal;
}

void Particle::setTriangleNormal(ofVec3f _triangleNormal) {
    triangleNormal = _triangleNormal;
}

ofVec3f Particle::getTriangleNormal() {
    return triangleNormal;
}

void Particle::setScalar(float s) {
    scalar = s;
}

void Particle::setFollow(float f) {
    follow = f;
}

void Particle::pointBetweenPoint(float per) {
  pos.x = pos.x + (tar.x - pos.x) * per;
  pos.y = pos.y + (tar.y - pos.y) * per;
  pos.z = pos.z + (tar.z - pos.z) * per;
}

void Particle::simplexMorph() {
    float x = pos.x * simplexDepth + off;
    float y = pos.y * simplexDepth + off;
    float z = pos.z * simplexDepth + off;
    
    float mappedX = ofMap(ofNoise(x), 0.0, 1.0, -1.0, 1.0);
    float mappedY = ofMap(ofNoise(y), 0.0, 1.0, -1.0, 1.0);
    float mappedZ = ofMap(ofNoise(z), 0.0, 1.0, -1.0, 1.0);
    
    float magnitude = pow(ofNoise(x, y, z), simplexPow);
    
    float rotX = mappedX * simplexWrap;
    float rotY = mappedY * simplexWrap;
    float rotZ = mappedZ * simplexWrap;

    ofVec3f v(magnitude * simplexRate, 0, 0);
    v.rotateRad(rotX, ofVec3f(1.0, 0.0, 0.0));
    v.rotateRad(rotY, ofVec3f(0.0, 1.0, 0.0));
    v.rotateRad(rotZ, ofVec3f(0.0, 0.0, 1.0));

    morph.x = v.x;
    morph.y = v.y;
    morph.z = v.z;
    
    off += simplexOffset;
}

//--------------------------------------------------------------
void Particle::update(){
    simplexMorph();
    pointBetweenPoint(follow);
}

//--------------------------------------------------------------
void Particle::draw(){
}

void Particle::setSimplexMorph(float _rate, float _depth, float _offset, float _wrap, float _pow) {
    simplexRate = _rate;
    simplexDepth = _depth;
    simplexOffset = _offset;
    simplexWrap = _wrap;
    simplexPow = _pow;
}

float Particle::getScalar() {
    return scalar;
}

ofVec3f Particle::getPosition() {
    return pos + morph;
}
