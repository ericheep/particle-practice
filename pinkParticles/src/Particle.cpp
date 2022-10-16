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
    
    per = 0.01;
}

void Particle::updateTarget(float _x, float _y, float _z) {
    tar.x = _x;
    tar.y = _y;
    tar.z = _z;
}

void Particle::setPer(float p) {
    per = p;
}

void Particle::pointBetweenPoint(float per) {
  pos.x = pos.x + (tar.x - pos.x) * per;
  pos.y = pos.y + (tar.y - pos.y) * per;
  pos.z = pos.z + (tar.z - pos.z) * per;
}

//--------------------------------------------------------------
void Particle::update(){
    pointBetweenPoint(per);
}

//--------------------------------------------------------------
void Particle::draw(){
    ofDrawCircle(pos, 1);
}
