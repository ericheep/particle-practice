//
//  Shape.cpp
//  pinkParticles
//
//  Created by Eric Heep on 9/22/22.
//

#include "Shape.hpp"

Shape::Shape(int _meshes, float _ma, float _mb, float _radius) {
    a = 1;
    b = 1;
    
    fuzzy = 0.1;
    randomPer = 0.05;
        
    ma = _ma;
    mb = _mb;
    radius = _radius;
    
    setMeshes(_meshes);
    
    mesh.setMode(OF_PRIMITIVE_POINTS);
        glEnable(GL_POINT_SMOOTH);
        glPointSize(1);
}

void Shape::setShapeA(float m, float n1, float n2, float n3) {
  ma = m;
  n1a = n1;
  n2a = n2;
  n3a = n3;
}

void Shape::setShapeB(float m, float n1, float n2, float n3) {
  mb = m;
  n1b = n1;
  n2b = n2;
  n3b = n3;
}

void Shape::setRandomPer(float randomPer) {
    for (int i = 0; i < meshes + 1; i++) {
        for (int j = 0; j < meshes + 1; j++) {
            float rand = ofRandom(0.0, randomPer);
            float per = ofMap(rand, 0.0, 1.0, 0.05, 0.25);
            
            particles[i][j].setPer(per);
        }
    }
}

void Shape::setMeshes(int _meshes) {
    meshes = _meshes;

    for (int i = 0; i < meshes + 1; i++) {
        vector<Particle> particleRow;
        for (int j = 0; j < meshes + 1; j++) {
            particleRow.push_back(Particle(0, 0, 0));
        }
        particles.push_back(particleRow);
    }
    
    updateShape();
    setRandomPer(randomPer);
}

void Shape::updateShape() {
   for (int i = 0; i < meshes + 1; i++) {
     float lat = ofMap(i, 0, meshes, -HALF_PI, HALF_PI);

     float r2 = supershape(lat, mb, n1b, n2b, n3b);

     for (int j = 0; j < meshes + 1; j++) {
       float lon = ofMap(j, 0, meshes, -PI, PI);
       float r1 = supershape(lon, ma, n1a, n2a, n3a);

       float x = radius * r1 * cos(lon) * r2 * cos(lat);
       float y = radius * r1 * sin(lon) * r2 * cos(lat);
       float z = radius * r2 * sin(lat);

       particles[i][j].updateTarget(x, y, z);
     }
   }
 }

void Shape::update(){
    for (int i = 0; i < meshes + 1; i++) {
        for (int j = 0; j < meshes + 1; j++) {
        
            if (fuzzy > 0) {
                particles[i][j].pos.x += ofRandom(-fuzzy, fuzzy);
                particles[i][j].pos.y += ofRandom(-fuzzy, fuzzy);
                particles[i][j].pos.z += ofRandom(-fuzzy, fuzzy);
            }

            particles[i][j].update();
        }
    }
}

void Shape::setFuzzy(float _fuzzy){
    fuzzy = _fuzzy;
}

void Shape::draw(){
    for (int i = 0; i < meshes + 1; i++) {
        for (int j = 0; j < meshes + 1; j++) {
            mesh.addVertex(particles[i][j].pos);
        }
    }
    
    mesh.drawVertices();
    mesh.clearVertices();
}

float Shape::supershape(float theta, float m, float n1, float n2, float n3) {
    float t1 = fabs((1.0 / a) * cos(m * theta / 4.0));
    t1 = pow(t1, n2);
    float t2 = fabs((1.0/ b) * sin(m * theta / 4.0));
    t2 = pow(t2, n3);
    float t3 = t1 + t2;
    
    return pow(t3, -1 / n1);
}
