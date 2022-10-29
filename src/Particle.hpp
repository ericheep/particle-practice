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
        float simplexRate, simplexDepth, simplexOffset, simplexWrap;
        
        ofVec3f pos;
        ofVec3f tar;
        ofVec3f morph;
    
        void setup();
        void update();
        void draw();
        
        void setPosition(float x, float y, float z);
        void setPosition(ofVec3f _pos);
        void updateTarget(float _x, float _y, float _z);
        void pointBetweenPoint(float per);
        void setPer(float p);
        void setSimplexMorph(float _rate, float _depth, float _offset, float _wrap);
        void setWindMorph(bool f);
        void setScalar(float s);
        void setFollow(float f);
        float getScalar();
        ofVec3f getPosition();
    
    private:
        void simplexMorph();
};

#endif /* Particle_hpp */
