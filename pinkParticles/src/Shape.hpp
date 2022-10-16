//
//  Shape.hpp
//  pinkParticles
//
//  Created by Eric Heep on 9/22/22.
//

#ifndef Shape_hpp
#define Shape_hpp

#include <stdio.h>
#include "ofMain.h"
#include "Particle.hpp"

class Shape {
    public:
        Shape(int _meshes, float _ma, float _mb, float _radius);
        vector<vector<Particle>> particles;

        ofMesh mesh;
        
        float a, b;
        float ma, n1a, n2a, n3a, ra;
        float mb, n1b, n2b, n3b, rb;
        float radius, fuzzy, randomPer;
        int meshes;
    
        void setup();
        void update();
        void draw();
    
        float supershape(float theta, float m, float n1, float n2, float n3);
    
        void setMeshes(int _meshes);
        void setFuzzy(float _fuzzy);
        void updateShape();
        void setShapeA(float m, float n1, float n2, float n3);
        void setShapeB(float m, float n1, float n2, float n3);
        void setRandomPer(float p);
};

#endif /* Shape_hpp */
