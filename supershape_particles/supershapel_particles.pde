import controlP5.*;
ControlP5 cp5;

import peasy.*;

OpenSimplex2 nois;
PeasyCam cam;
Shape shp;

color pink = color(255, 182, 193);
int whichShape = -1;
PShader shader1, shader2;

void setup() {
  size(1000, 1000, P3D);
  cam = new PeasyCam(this, 250);
  shp = new Shape(100, 8.0, 2.0, 50);
  shp.setShapeA(8.0, -8.11, -0.08, 93);
  shp.setShapeB(2.0, 0.99, 97.67, -0.439);
  shp.updateShapes();
  strokeWeight(1);
  
  shader1 = loadShader("simplexMorph.glsl");
  shader2 = loadShader("degauze.glsl");

  nois = new OpenSimplex2();

  cp5 = new ControlP5(this);
  cp5.addButton("randomize").setPosition(20, 20).setSize(75, 20);
  cp5.addButton("explode").setPosition(100, 20).setSize(75, 20);
  cp5.addButton("split").setPosition(180, 20).setSize(75, 20);

  cp5.addButton("degauze").setPosition(20, 45).setSize(75, 20);
  cp5.addButton("cycle").setPosition(100, 45).setSize(75, 20);
  cp5.addButton("opposite").setPosition(20, 70).setSize(75, 20);

  cp5.addSlider("meshes").setPosition(20, 100).setValue(200).setRange(3, 1000).setSize(100, 15);
  cp5.addSlider("fuzzy").setPosition(20, 120).setRange(0, 2.5).setSize(100, 15);
  cp5.addSlider("percentage").setPosition(20, 140).setRange(0, 1.0).setValue(0.9).setSize(100, 15);

  cp5.addButton("target").setPosition(20, 165).setSize(55, 20);
  cp5.addButton("swirl").setPosition(80, 165).setSize(55, 20);
  cp5.addButton("scatter").setPosition(140, 165).setSize(55, 20);
  cp5.addButton("wind").setPosition(200, 165).setSize(55, 20);
  cp5.addButton("boom").setPosition(260, 165).setSize(55, 20);
  cp5.addButton("vortex").setPosition(20, 190).setSize(55, 20);

  cp5.setAutoDraw(false);
}

float inc = 0.0;
float sine = 0.0;

void draw() {
  background(pink);
  
  inc += 0.01;
  
  if (inc > TWO_PI) {
     inc -= TWO_PI; 
  }
  
  sine = map(sin(inc), -1.0, 1.0, 0.0, 1.0);
  
  shader1.set("u_resolution", float(width), float(height));
  shader1.set("u_mouse", 0.05, 0.05);
  shader1.set("u_time", millis() / 1000.0);
  shader2.set("u_sine", sine);

  shader2.set("u_resolution", float(width), float(height));
  shader2.set("u_mouse", 0.05, 0.05);
  shader2.set("u_time", millis() / 1000.0);
  shader2.set("u_sine", sine);
  
  cam.rotateY(0.006);
  cam.rotateX(0.005);

  shp.update();
  shp.draw();

  gui();
  filter(shader1);
  // filter(shader2);
}

void randomize() {
  float ma = random(0, 30);
  float mb = random(0, 30);
  shp.setMA(ma);
  shp.setMB(mb);
  shp.updateShapes();
}

void explode() {
  shp.explode();
}

void split() {
  shp.split();
}

void degauze() {
  shp.degauze();
}

void opposite() {
  shp.opposite();
}

void meshes(int m) {
  shp.setMeshes(m);
}

void percentage(float p) {
  shp.setRandomPer(p);
}

void target() {
  shp.setMode("target");
}

void swirl() {
  shp.setMode("swirl");
  shp.randomSwirlSeed();
}

void wind() {
  shp.setMode("wind");
  shp.randomWindSeed();
}

void scatter() {
  shp.setMode("scatter");
}

void boom() {
  shp.setMode("boom");
}

void vortex() {
  shp.setMode("vortex");
}

void cycle() {
  whichShape = (whichShape + 1) % 4;

  switch(whichShape) {
  case 0:
    //squirtle
    shp.setShapeA(8, 60, 100, 30);
    shp.setShapeB(2, 10, 10, 10);
    break;
  case 1:
    // flower
    shp.setShapeA(6, 1, 1, 1);
    shp.setShapeB(3, 1, 1, 1);
    break;
  case 2:
    // ufo
    shp.setShapeA(0.2, 0.1, 1.7, 1.7);
    shp.setShapeB(2.0, 0.5, 0.2, 0.2);
    break;
  case 3:
    // super flower
    shp.setShapeA(5.2, 0.04, 1.70, 1.70);
    shp.setShapeB(0., 1.0, 1.0, 1.0);
    break;
  }

  shp.updateShapes();
}

void fuzzy(float f) {
  shp.setFuzzy(f);
}

void gui() {
  hint(DISABLE_DEPTH_TEST);
  cam.beginHUD();
  cp5.draw();
  cam.endHUD();
  hint(ENABLE_DEPTH_TEST);
}
