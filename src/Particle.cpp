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
    
    morph.x = 0;
    morph.y = 0;
    morph.z = 0;
    
    follow = 0.5;
    fuzzy = 0.0;
    
    simplexRate = 0;
    simplexDepth = 0;
    simplexOffset = 0;
    simplexWrap = 0;
    simplexPow = 0;;
    
    off = 0.0;
}

void Particle::setCenter(ofVec3f _center) {
    center = _center;
}

void Particle::setTarget(ofVec3f _tar) {
    tar = _tar;
}

void Particle::setPosition(ofVec3f _pos) {
    pos = _pos;
}

void Particle::setNormal(ofVec3f _normal) {
    normal = _normal;
}

void Particle::setRotation(ofVec3f _rotation) {
    rotation = _rotation;
}

ofVec3f Particle::getNormal() {
    return normal;
}

void Particle::setFollow(float _follow) {
    follow = _follow;
}

void Particle::setFuzzy(float _fuzzy) {
    fuzzy = _fuzzy;
}

void Particle::pointBetweenPoint(float per) {
  pos.x = pos.x + (tar.x - pos.x) * per;
  pos.y = pos.y + (tar.y - pos.y) * per;
  pos.z = pos.z + (tar.z - pos.z) * per;
}

void Particle::updateFuzzy() {
    pos.x += ofRandom(-fuzzy, fuzzy);
    pos.y += ofRandom(-fuzzy, fuzzy);
    pos.z += ofRandom(-fuzzy, fuzzy);
}

void Particle::updateSimplexMorph() {
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

void Particle::update(){
    updateFuzzy();
    updateSimplexMorph();
    pointBetweenPoint(follow);
}

void Particle::setSimplexMorph(float _rate, float _depth, float _offset, float _wrap, float _pow) {
    simplexRate = _rate;
    simplexDepth = _depth;
    simplexOffset = _offset;
    simplexWrap = _wrap;
    simplexPow = _pow;
}

ofVec3f Particle::getPosition() {
    return pos + morph;
}
