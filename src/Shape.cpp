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
    
    randomFollow = 0.0;
        
    ma = _ma;
    mb = _mb;
    radius = _radius;
    
    setMeshes(_meshes);
    
    center = ofVec3f(0.0, 0.0, 0.0);
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
}

void Shape::setMeshes(int _numMeshes) {
    if (numMeshes != _numMeshes) {
        numMeshes = _numMeshes;
        
        particles.clear();
        for (int i = 0; i < numMeshes; i++) {
            vector<Particle> particleRow;
            for (int j = 0; j < numMeshes; j++) {
                Particle p = Particle(0, 0, 0);
                particleRow.push_back(p);
            }
            
            particles.push_back(particleRow);
        }
        
        setShape();
    }
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

void Shape::setShapeType(int _shapeType) {
    if (shapeType != _shapeType) {
        switch(_shapeType) {
            case 0:
                // sphere
                setShapeA(0, 1, 1, 1);
                setShapeB(0, 1, 1, 1);
                setShape();
                break;
            case 1:
                //squirtle
                setShapeA(8, 60, 100, 30);
                setShapeB(2, 10, 10, 10);
                setShape();
                break;
            case 2:
                // flower
                setShapeA(6, 1, 1, 1);
                setShapeB(3, 1, 1, 1);
                setShape();
                break;
            case 3:
                // ufo
                setShapeA(0.2, 0.1, 1.7, 1.7);
                setShapeB(2.0, 0.5, 0.2, 0.2);
                setShape();
                break;
            case 4:
                // super flower
                setShapeA(5.2, 0.04, 1.70, 1.70);
                setShapeB(0., 1.0, 1.0, 1.0);
                setShape();
                break;
            case 5:
                // classic
                setShapeA(8.0, -8.11, -0.08, 93);
                setShapeB(2.0, 0.99, 97.67, -0.439);
                setShape();
                break;
            case 6:
                // symbol
                setShapeA(6, 60., 55, 1000);
                setShapeB(6, 250, 100, 100);
                setShape();
                break;
            case 7:
                // symbol
                setShapeA(7, 0.2, 1.7, 1.7);
                setShapeB(7, 0.2, 1.7, 1.7);
                setShape();
                break;
        }
        
        shapeType = _shapeType;
    }
}

float Shape::supershape(float theta, float m, float n1, float n2, float n3) {
    float t1 = fabs((1.0 / a) * cos(m * theta / 4.0));
    t1 = pow(t1, n2);
    float t2 = fabs((1.0/ b) * sin(m * theta / 4.0));
    t2 = pow(t2, n3);
    float t3 = t1 + t2;
    
    return pow(t3, -1 / n1);
}

void Shape::setCenter(ofVec3f _center) {
    center = _center;
}

void Shape::setPointSize(int _pointSize) {
    glPointSize(_pointSize);
}

void Shape::setRandomFollow(float _randomFollow) {
    randomFollow = _randomFollow;
}

void Shape::setSimplexMorph(float _rate, float _depth, float _offset, float _wrap, float _pow){
    for (int i = 0; i < numMeshes; i++) {
        for (int j = 0; j < numMeshes; j++) {
            particles[i][j].setSimplexMorph(_rate, _depth, _offset, _wrap, _pow);
        }
    }
}

void Shape::setRotation(ofVec3f rotation) {
    for (int i = 0; i < numMeshes; i++) {
        for (int j = 0; j < numMeshes; j++) {
            particles[i][j].setRotation(rotation);
        }
    }
}

void Shape::setShape() {
   for (int i = 0; i < numMeshes; i++) {
     float lat = ofMap(i, 0, numMeshes - 1, -HALF_PI, HALF_PI);
     float r2 = supershape(lat, mb, n1b, n2b, n3b);

     for (int j = 0; j < numMeshes; j++) {
       float lon = ofMap(j, 0, numMeshes - 1, -PI, PI);
       float r1 = supershape(lon, ma, n1a, n2a, n3a);

       float x = radius * r1 * cos(lon) * r2 * cos(lat);
       float y = radius * r1 * sin(lon) * r2 * cos(lat);
       float z = radius * r2 * sin(lat);

       particles[i][j].setTarget(ofVec3f(x, y, z));
     }
   }
}

// update
void Shape::updateParticles() {
    for (int i = 0; i < numMeshes; i++) {
        for (int j = 0; j < numMeshes; j++) {
            particles[i][j].update();
        }
    }
}

ofVec3f calculateNormal(ofVec3f a, ofVec3f b, ofVec3f c) {
    ofVec3f BA = (b - a);
    ofVec3f CA = (c - a);

    return (BA.cross(CA));
}

void Shape::updateRowNormals(int i1, int i2) {
    for (int j = 0; j < numMeshes; j++) {
        ofVec3f normal = particles[i2][j].getNormal();
        particles[i1][j].setNormal(normal);
    }
}

void Shape::updateNormals() {
    for (int i = 1; i < numMeshes - 1; i++) {
        for (int j = 0; j < numMeshes; j++) {
            ofVec3f l, p, r, u, d;
            if (j == 0) {
                l = particles[i][numMeshes - 1].getPosition();
                r = particles[i][j + 1].getPosition();
            } else if (j == numMeshes - 1) {
                l = particles[i][j - 1].getPosition();
                r = particles[i][0].getPosition();
            } else {
                l = particles[i][j - 1].getPosition();
                r = particles[i][j + 1].getPosition();
            }
            
            u = particles[i - 1][j].getPosition();
            d = particles[i + 1][j].getPosition();
                        
            ofVec3f n1 = calculateNormal(l, p, u);
            ofVec3f n2 = calculateNormal(u, p, r);
            ofVec3f n3 = calculateNormal(l, p, d);
            ofVec3f n4 = calculateNormal(d, p, r);
            
            ofVec3f normal = (n1 + n2 + n3 + n4).normalize();
            particles[i][j].setNormal(normal);
        }
    }
    updateRowNormals(0, 1);
    updateRowNormals(numMeshes - 1, numMeshes - 2);
}

void Shape::updateMesh() {
    for (int i = 0; i < numMeshes; i++) {
        for (int j = 0; j < numMeshes; j++) {
            mesh.addVertex(particles[i][j].getPosition());
            mesh.addNormal(particles[i][j].getNormal());
            
            if (i < numMeshes - 1) {
                mesh.addVertex(particles[i + 1][j].getPosition());
                mesh.addNormal(particles[i + 1][j].getNormal());
            }
        }
    }
}

void Shape::update(){
    updateParticles();
    updateNormals();
    updateMesh();
}

void Shape::draw(){
    mesh.draw();
}

void Shape::clearMesh() {
    mesh.clearVertices();
    mesh.clearNormals();
}

void Shape::setFuzzy(float _fuzzy){
    for (int i = 0; i < numMeshes; i++) {
        for (int j = 0; j < numMeshes; j++) {
            particles[i][j].setFuzzy(_fuzzy);
        }
    }
}

void Shape::setPrimitiveType(int _primitiveType) {
    if(primitiveType != _primitiveType) {
        switch(_primitiveType) {
            case 0:
                mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
                break;
            case 1:
                mesh.setMode(OF_PRIMITIVE_POINTS);
                break;
            case 2:
                mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
                break;
            case 3:
                mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
                break;
        }
                
        primitiveType = _primitiveType;
    }
}

// actions
void Shape::random() {
    for (int i = 0; i < numMeshes; i++) {
        for (int j = 0; j < numMeshes; j++) {
            float x = ofRandom(-ofGetWidth(), ofGetWidth());
            float y = ofRandom(-ofGetWidth(), ofGetWidth());
            float z = ofRandom(-ofGetWidth(), ofGetWidth());

            particles[i][j].setPosition(ofVec3f(x, y, z));
        }
    }
}

void Shape::swap() {
    for (int i = 0; i < numMeshes; i++) {
        for (int j = 0; j < numMeshes; j++) {
            ofVec3f position = particles[i][j].getPosition();
            particles[i][j].setPosition(-position);
        }
    }
}

void Shape::explode() {
    
}
