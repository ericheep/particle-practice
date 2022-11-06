//
//  Particle.hpp
//  pinkParticles
//
//  Created by Eric Heep on 9/22/22.
//

#ifndef Particle_hpp
#define Particle_hpp

#include <stdio.h>
#include <ofMain.h>

class Particle {
public:
    Particle(float _x, float _y, float _z);
    
    float x, y, z, off;
    float tarX, tarY, tarZ;
    float scalar, follow;
    
    bool simplexFlag, windMorphFlag;
    float simplexRate, simplexDepth, simplexOffset, simplexWrap, simplexPow;
        
    ofVec3f pos;
    ofVec3f tar;
    ofVec3f morph;
    ofVec3f normal;
    ofVec3f triangleNormal;
    
    void setup();
    void update();
    void draw();
        
    void setPosition(float x, float y, float z);
    void setPosition(ofVec3f _pos);
    ofVec3f getPosition();

    void setNormal(ofVec3f _normal);
    ofVec3f getNormal();
    
    void setTriangleNormal(ofVec3f _triangleNormal);
    ofVec3f getTriangleNormal();

    void setTarget(ofVec3f tar);
    void updateTarget(float _x, float _y, float _z);
    ofVec3f getTarget();

    void pointBetweenPoint(float per);
    void setPer(float p);
    void setSimplexMorph(float _rate, float _depth, float _offset, float _wrap, float _pow);
    void setWindMorph(bool f);
    void setScalar(float s);
    void setFollow(float f);
    float getScalar();
        
private:
    void simplexMorph();
};

#endif /* Particle_hpp */
