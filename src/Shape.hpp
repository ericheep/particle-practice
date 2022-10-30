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

        ofVboMesh mesh;
        // ofVec3f v1[0];
        // ofVec3f v2[0];
    
        float a, b;
        float ma, n1a, n2a, n3a, ra;
        float mb, n1b, n2b, n3b, rb;
        float radius, fuzzy, randomFollow, hue, depth, saturation;
        float xRotationInc, yRotationInc, zRotationInc;
        int shapeType, numMeshes, pointSize;
    
        void setup();
        void update();
        void draw();
        void clearMesh();
    
        float supershape(float theta, float m, float n1, float n2, float n3);
    
        void setMeshes(int _meshes);
        void setFuzzy(float _fuzzy);
        void setSimplexMorph(float _rate, float _depth, float _offset, float _wrap);
    
        void updateShape();
        void setPointSize(int size);
        void setHueStart(float hue);
        void setHueDepth(float depth);
        void setPointSaturation(float saturation);
        void setRotateX(float rotationInc);
        void setRandomPosition();
        void swap();
        void explode();
        void setShapeA(float m, float n1, float n2, float n3);
        void setShapeB(float m, float n1, float n2, float n3);
        void setRandomFollow(float rf);
        void setShapeType(int which);
        
        int getShapeType();
        int getNumMeshes();
        int getPointSize();
        float getRandomFollow();
        float getRotateX();
        ofVec3f getCentroid();
};

#endif /* Shape_hpp */
