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
    
    fuzzy = 0.0;
    randomFollow = 0.0;
        
    ma = _ma;
    mb = _mb;
    radius = _radius;
    
    setMeshes(_meshes);
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

void Shape::setPointSize(int _pointSize) {
    pointSize = _pointSize;
    glPointSize(pointSize);
}

int Shape::getPointSize() {
    return pointSize;
}

void Shape::random() {
    for (int i = 0; i < numMeshes; i++) {
        for (int j = 0; j < numMeshes; j++) {
            float x = ofRandom(-ofGetWidth(), ofGetWidth());
            float y = ofRandom(-ofGetWidth(), ofGetWidth());
            float z = ofRandom(-ofGetWidth(), ofGetWidth());

            particles[i][j].setPosition(x, y, z);
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

void Shape::setRandomFollow(float randomFollow) {
    for (int i = 0; i < numMeshes; i++) {
        for (int j = 0; j < numMeshes; j++) {
            float mapped = ofMap(randomFollow, 0.0, 1.0, 0.001, 0.1);
            float rf = ofRandom(0.001, mapped);
            particles[i][j].setFollow(rf);
        }
    }
}

void Shape::rotate(ofVec3f r) {
    for (int i = 0; i < numMeshes; i++) {
        for (int j = 0; j < numMeshes; j++) {
            ofVec3f rot = particles[i][j].getTarget().getRotated(r.x, r.y, r.z);
            particles[i][j].setTarget(rot);
        }
    }
}

void Shape::setMeshes(int _numMeshes) {
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
    
    updateShape();
    setRandomFollow(randomFollow);
}

ofVec3f calculateNormal(ofVec3f a, ofVec3f b, ofVec3f c) {
    ofVec3f BA = (b - a);
    ofVec3f CA = (c - a);

    return (BA.cross(CA));
}

//  = ( (2*(Zleft - Zright) - Zupright + Zdownleft + Zup - Zdown) / ax,
// (2*(Zdown - Zup)    + Zupright + Zdownleft - Zup - Zleft) / ay, 6 )

ofVec3f calculateSixAdjacentNormals(ofVec3f l, ofVec3f p, ofVec3f r, ofVec3f u, ofVec3f ur, ofVec3f d, ofVec3f dl) {
    float x = 2 * (l.z - r.z) - u.z + dl.z + u.z - d.z / abs(p.x - l.x);
    float y = 2 * (d.z - u.z) + ur.z + dl.z - u.z - l.z / abs(p.y - u.y);
    float z = 6;
    
    return ofVec3f(x, y, z).normalize();
}

void Shape::updateShape() {
   for (int i = 0; i < numMeshes; i++) {
     float lat = ofMap(i, 0, numMeshes - 1, -HALF_PI, HALF_PI);
     float r2 = supershape(lat, mb, n1b, n2b, n3b);

     for (int j = 0; j < numMeshes; j++) {
       float lon = ofMap(j, 0, numMeshes - 1, -PI, PI);
       float r1 = supershape(lon, ma, n1a, n2a, n3a);

       float x = radius * r1 * cos(lon) * r2 * cos(lat);
       float y = radius * r1 * sin(lon) * r2 * cos(lat);
       float z = radius * r2 * sin(lat);

       particles[i][j].updateTarget(x, y, z);
     }
   }
}

void Shape::updatePositions() {
    for (int i = 0; i < numMeshes; i++) {
        for (int j = 0; j < numMeshes; j++) {
            if (fuzzy > 0) {
                particles[i][j].pos.x += ofRandom(-fuzzy, fuzzy);
                particles[i][j].pos.y += ofRandom(-fuzzy, fuzzy);
                particles[i][j].pos.z += ofRandom(-fuzzy, fuzzy);
            }
            
            particles[i][j].update();
        }
    }
}

ofVec3f calculateFourAdjacentNormals(ofVec3f l, ofVec3f p, ofVec3f r, ofVec3f u, ofVec3f d) {
    float x = (l.z - r.z) / abs(p.x - l.x);
    float y = (d.z - u.z) / abs(p.y - u.y);
    float z = 2;
    
    return ofVec3f(x, y, z).normalize();
}

void Shape::updateNormals() {
    for (int i = 0; i < numMeshes; i++) {
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
            
            if (i == 0) {
                u = particles[i + 1][(j + int(numMeshes / 2)) % numMeshes].getPosition();
                d = particles[i + 1][j].getPosition();
            } else if (i == numMeshes - 1) {
                u = particles[i - 1][j].getPosition();
                d = particles[i - 1][(j + int(numMeshes / 2)) % numMeshes].getPosition();
            } else {
                u = particles[i - 1][j].getPosition();
                d = particles[i + 1][j].getPosition();
            }
                        
            ofVec3f n1 = calculateNormal(l, p, u);
            ofVec3f n2 = calculateNormal(u, p, r);
            ofVec3f n3 = calculateNormal(l, p, d);
            ofVec3f n4 = calculateNormal(d, p, r);
            
            ofVec3f normal = (n1 + n2 + n3 + n4).normalize();
            particles[i][j].setNormal(normal);
        }
    }
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
    updatePositions();
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
    fuzzy = _fuzzy;
}

void Shape::setHueStart(float _hue) {
    hue = _hue;
}

void Shape::setHueDepth(float _depth) {
    depth = _depth;
}

void Shape::setPointSaturation(float _saturation) {
    saturation = _saturation;
}

void Shape::setSimplexMorph(float _rate, float _depth, float _offset, float _wrap, float _pow){
    for (int i = 0; i < numMeshes; i++) {
        for (int j = 0; j < numMeshes; j++) {
            particles[i][j].setSimplexMorph(_rate, _depth, _offset, _wrap, _pow);
        }
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

void Shape::setShapeType(int which) {
    switch(which) {
        case 0:
            // sphere
            setShapeA(0, 1, 1, 1);
            setShapeB(0, 1, 1, 1);
            updateShape();
            break;
        case 1:
            //squirtle
            setShapeA(8, 60, 100, 30);
            setShapeB(2, 10, 10, 10);
            updateShape();
            break;
        case 2:
            // flower
            setShapeA(6, 1, 1, 1);
            setShapeB(3, 1, 1, 1);
            updateShape();
            break;
        case 3:
            // ufo
            setShapeA(0.2, 0.1, 1.7, 1.7);
            setShapeB(2.0, 0.5, 0.2, 0.2);
            updateShape();
            break;
        case 4:
            // super flower
            setShapeA(5.2, 0.04, 1.70, 1.70);
            setShapeB(0., 1.0, 1.0, 1.0);
            updateShape();
            break;
        case 5:
            // classic
            setShapeA(8.0, -8.11, -0.08, 93);
            setShapeB(2.0, 0.99, 97.67, -0.439);
            updateShape();
            break;
        case 6:
            // symbol
            setShapeA(6, 60., 55, 1000);
            setShapeB(6, 250, 100, 100);
            updateShape();
            break;
    }
    shapeType = which;
}

void Shape::setPrimitiveType(int type) {
    primitiveType = type;
    switch(type) {
        case 0:
            mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
            break;
        case 1:
            mesh.setMode(OF_PRIMITIVE_POINTS);
            break;
        case 2:
            mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
            break;
    }
}

int Shape::getPrimitiveType() {
    return primitiveType;
}

int Shape::getShapeType() {
    return shapeType;
}

int Shape::getNumMeshes() {
    return numMeshes;
}

float Shape::getRandomFollow() {
    return randomFollow;
}
