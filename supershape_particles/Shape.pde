class Shape {
  float a = 1;
  float b = 1;

  float ma, n1a, n2a, n3a, ra;
  float mb, n1b, n2b, n3b, rb;
  float radius, fuzzy, randomPer;
  int meshes;

  Particle[][] particles;

  Shape(int _meshes, float _ma, float _mb, float _radius) {
    ma = _ma;
    mb = _mb;
    radius = _radius;
    fuzzy = 0;

    setMeshes(_meshes);
  }

  float supershape(float theta, float m, float n1, float n2, float n3) {
    float t1 = abs((1/a) * cos(m * theta / 4));
    t1 = pow(t1, n2);
    float t2 = abs((1/b) * sin(m * theta / 4));
    t2 = pow(t2, n3);
    float t3 = t1 + t2;

    return pow(t3, -1 / n1);
  }

  void setMeshes(int _meshes) {
    meshes = _meshes;
    particles = new Particle[meshes + 1][meshes + 1];

    for (int i = 0; i < meshes + 1; i++) {
      for (int j = 0; j < meshes + 1; j++) {
        particles[i][j] = new Particle(0, 0, 0);
      }
    }
    updateShapes();
    setRandomPer(randomPer);
  }

  void setMA(float _m) {
    ma = _m;
  }

  void setMB(float _m) {
    mb = _m;
  }

  void setMode(String mode) {
    for (int i = 0; i < meshes + 1; i++) {
      for (int j = 0; j < meshes + 1; j++) {
        particles[i][j].setMode(mode);
      }
    }
  }

  void opposite() {
    for (int i = 0; i < meshes + 1; i++) {
      for (int j = 0; j < meshes + 1; j++) {
        particles[i][j].x = particles[meshes - i][meshes - j].tarX;
        particles[i][j].y = particles[meshes - i][meshes - j].tarY;
        particles[i][j].z = particles[meshes - i][meshes - j].tarZ;
      }
    }
  }

  void setShapeA(float m, float n1, float n2, float n3) {
    ma = m;
    n1a = n1;
    n2a = n2;
    n3a = n3;
  }

  void setShapeB(float m, float n1, float n2, float n3) {
    mb = m;
    n1b = n1;
    n2b = n2;
    n3b = n3;
  }

  void setRandomPer(float p) {
    randomPer = p;

    for (int i = 0; i < meshes + 1; i++) {
      for (int j = 0; j < meshes + 1; j++) {
        float rand = random(0.0, p);
        float per = map(rand, 0.0, 1.0, 0.05, 0.25);
        particles[i][j].setPer(per);
      }
    }
  }

  void randomSwirlSeed() {
    int seed = int(random(0, 999));
    for (int i = 0; i < meshes + 1; i++) {
      for (int j = 0; j < meshes + 1; j++) {
        particles[i][j].setSwirlSeed(seed);
      }
    }
  }

  void randomWindSeed() {
    int seed = int(random(0, 999));
    for (int i = 0; i < meshes + 1; i++) {
      for (int j = 0; j < meshes + 1; j++) {
        particles[i][j].setWindSeed(seed);
      }
    }
  }

  void updateShapes() {
    for (int i = 0; i < meshes + 1; i++) {
      float lat = map(i, 0, meshes, -HALF_PI, HALF_PI);
      float r2 = supershape(lat, mb, n1b, n2b, n3b);

      for (int j = 0; j < meshes + 1; j++) {
        float lon = map(j, 0, meshes, -PI, PI);
        float r1 = supershape(lon, ma, n1a, n2a, n3a);

        float x = radius * r1 * cos(lon) * r2 *  cos(lat);
        float y = radius * r1 * sin(lon) * r2 * cos(lat);
        float z = radius * r2 * sin(lat);

        particles[i][j].updateTarget(x, y, z);
      }
    }
  }

  void split() {
    int dir = int(random(0, 3));
    for (int i = 0; i < meshes + 1; i++) {
      for (int j = 0; j < meshes + 1; j++) {
        PVector explodeV = new PVector(0, 0, 0);
        float dist = 50;

        if (int(random(2)) == 0) {
          if (dir == 0) {
            explodeV.set(+dist, 0, 0);
          } else if (dir == 1) {
            explodeV.set(0, +dist, 0);
          } else if (dir == 2) {
            explodeV.set(0, 0, +dist);
          }
        } else {
          if (dir == 0) {
            explodeV.set(-dist, 0, 0);
          } else if (dir == 1) {
            explodeV.set(0, -dist, 0);
          } else if (dir == 2) {
            explodeV.set(0, 0, -dist);
          }
        }

        particles[i][j].tarX += explodeV.x;
        particles[i][j].tarY += explodeV.y;
        particles[i][j].tarZ += explodeV.z;
      }
    }
  }

  void explode() {
    for (int i = 0; i < meshes + 1; i++) {
      for (int j = 0; j < meshes + 1; j++) {
        float theta = particles[i][j].calcTheta();
        PVector explodeV = new PVector(0, 0, 0);
        float dist = 25;

        if (theta > HALF_PI) {
          explodeV.set(+dist, -dist, dist);
        } else if (theta > 0) {
          explodeV.set(+dist, +dist, dist);
        } else if (theta > -HALF_PI) {
          explodeV.set(-dist, +dist, dist);
        } else {
          explodeV.set(-dist, -dist, dist);
        }

        if (particles[i][j].z < 0) {
          explodeV.z *= -1;
        }

        particles[i][j].tarX += explodeV.x;
        particles[i][j].tarY += explodeV.y;
        particles[i][j].tarZ += explodeV.z;
      }
    }
  }

  void degauze() {
    for (int i = 0; i < meshes + 1; i++) {
      for (int j = 0; j < meshes + 1; j++) {
        particles[i][j].x = random(-width, width);
        particles[i][j].y = random(-width, width);
        particles[i][j].z = random(-height, height);
      }
    }
  }

  void setFuzzy(float f) {
    fuzzy = f;
  }

  void update() {
    for (int i = 0; i < meshes + 1; i++) {
      for (int j = 0; j < meshes + 1; j++) {

        if (fuzzy > 0) {
          particles[i][j].x += random(-fuzzy, fuzzy);
          particles[i][j].y += random(-fuzzy, fuzzy);
          particles[i][j].z += random(-fuzzy, fuzzy);
        }

        particles[i][j].update();
      }
    }
  }

  void draw() {
    for (int i = 0; i < meshes + 1; i++) {
      for (int j = 0; j < meshes + 1; j++) {
        particles[i][j].draw();
      }
    }
  }
}
