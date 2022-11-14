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
    
    // void setPosition(float x, float y, float z);
    void setPosition(ofVec3f _pos);
    ofVec3f getPosition();

    void setNormal(ofVec3f _normal);
    void setNormalDifference(ofVec3f _normalDifference);
    ofVec3f getNormal();
    
    void setTriangleNormal(ofVec3f _triangleNormal);
    ofVec3f getTriangleNormal();

    void setTarget(ofVec3f tar);
    
    void setTwist(ofVec3f twist);
    void setRotation(ofVec3f rotation);

    void setFuzzy(float fuzzy);
    void setCenter(ofVec3f center);
    void setPer(float p);
    void setSimplexMorph(float rate, float depth, float offset, float wrap, float pow);
    void setRandomFollow(float randomFollow);
        
    void update();
private:
    float x, y, z, off;
    float tarX, tarY, tarZ;
    float scalar, follow, fuzzy;
    
    bool simplexFlag, windMorphFlag;
    float simplexRate, simplexDepth, simplexOffset, simplexWrap, simplexPow;
    
    ofVec3f pos, tar, morph, normal, center, rotation, twist, twisted, brownian;
    
    void pointBetweenPoint(float per);
    void updateSimplexMorph();
    void updateFuzzy();
    void updateTwist();
};

#endif /* Particle_hpp */
