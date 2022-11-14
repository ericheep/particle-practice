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
    ofVec3f center;

    void setup();
    void update();
    void draw();
    void clearMesh();
    
    // supershape
    float supershape(float theta, float m, float n1, float n2, float n3);
    void setShapeA(float m, float n1, float n2, float n3);
    void setShapeB(float m, float n1, float n2, float n3);
    void setShapeType(int type);
    void setShape();

    // configuration
    void setMeshes(int _meshes);
    void setFuzzy(float fuzzy);
    void setSimplexMorph(float _rate, float _depth, float _offset, float _wrap, float _pow);
    void setPointSize(int size);
    void setPrimitiveType(int type);
    void setRotation(ofVec3f rotation);
    void setTwist(ofVec3f twist);
    void setRandomFollow(float randomFollow);
    void setCenter(ofVec3f center);
    
    // actions
    void random();
    void swap();
    void explode();
    
private:
    float a, b;
    float ma, n1a, n2a, n3a, ra;
    float mb, n1b, n2b, n3b, rb;
    float radius;
    int shapeType, numMeshes, primitiveType;
    
    void updateParticles();
    void updateNormals();
    void updateMesh();
    void updateRowNormals(int i1, int i2);
};

#endif /* Shape_hpp */
