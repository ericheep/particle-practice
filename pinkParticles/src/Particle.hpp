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
    
        float x, y, z;
        float tarX, tarY, tarZ;
        float per;
        
        ofVec3f pos;
        ofVec3f tar;
    
        void setup();
        void update();
        void draw();
    
        void updateTarget(float _x, float _y, float _z);
        void pointBetweenPoint(float per);
        void setPer(float p);
};

#endif /* Particle_hpp */
