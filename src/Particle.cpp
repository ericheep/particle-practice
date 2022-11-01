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

void Particle::setPosition(float _x, float _y, float _z) {
    pos.x = _x;
    pos.y = _y;
    pos.z = _z;
}

void Particle::setPosition(ofVec3f _pos) {
    pos = _pos;
}

void Particle::setTarget(ofVec3f _tar) {
    tar = _tar;
}

ofVec3f Particle::getTarget() {
    return tar;
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
    float scl = simplexDepth;
    float wrap = simplexWrap;
    
    float x = pos.x * scl + off;
    float y = pos.y * scl + off;
    float z = pos.z * scl + off;
    
    float radX = ofNoise(y, z) * wrap;
    float radZ = ofNoise(x, y) * wrap;
    float radY = ofNoise(x, z) * wrap;
    
    ofVec3f v(simplexRate, 0., 0.);
    v.rotateRad(radX, ofVec3f(1.0, 0.0, 0.0));
    v.rotateRad(radZ, ofVec3f(0.0, 0.0, 1.0));
    v.rotateRad(radY, ofVec3f(0.0, 1.0, 0.0));

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

void Particle::setSimplexMorph(float _rate, float _depth, float _offset, float _wrap) {
    simplexRate = _rate;
    simplexDepth = _depth;
    simplexOffset = _offset;
    simplexWrap = _wrap;
}

float Particle::getScalar() {
    return scalar;
}

ofVec3f Particle::getPosition() {
    return pos + morph;
}
