class Particle {
  float x, y, z;
  float tarX, tarY, tarZ;
  float theta, per, offset;
  float scatterX, scatterY, scatterZ;
  PVector boomVector;
  float vortexTheta;

  boolean targetFlag, scatterFlag, swirlFlag, windFlag, boomFlag, vortexFlag;
  int windSeed, swirlSeed;

  color col;

  Particle(float _x, float _y, float _z) {
    x = _x;
    y = _y;
    z = _z;

    col = color(255, 255, 255);

    scatterX = random(-.1, .1);
    scatterY = random(-.1, .1);
    scatterZ = random(-.1, .1);

    targetFlag = true;
    scatterFlag = false;
    swirlFlag = false;
    windFlag = false;
    boomFlag = false;
    vortexFlag = false;

    windSeed = 0;
    swirlSeed = 0;
  }

  float calcTheta() {
    return atan2(x, y);
  }

  float calcPhi() {
    return atan2(x, z);
  }

  void setFlagsFalse() {
    targetFlag = false;
    scatterFlag = false;
    swirlFlag = false;
    windFlag = false;
    boomFlag = false;
    vortexFlag = false;
  }

  void setSwirlSeed(int s) {
    swirlSeed = s;
  }

  void setWindSeed(int s) {
    windSeed = s;
  }

  void setMode(String mode) {
    setFlagsFalse();

    switch(mode) {
    case "target":
      targetFlag = true;
      break;
    case "scatter":
      scatterFlag = true;
      break;
    case "swirl":
      swirlFlag = true;
      break;
    case "wind":
      windFlag = true;
      break;
    case "boom":
      boomFlag = true;
      boomInit();
      break;
    case "vortex":
      vortexFlag = true;
      vortexInit();
      break;
    }
  }

  void setPer(float p) {
    per = p;
  }

  void scatter() {
    x += scatterX;
    y += scatterY;
    z += scatterZ;
  }

  void swirl() {
    float scl = 0.025;
    offset += 0.00;//25;
    float perlinXY = nois.noise3_ImproveXZ(swirlSeed, scl * x + offset, scl * y + offset, scl * z + offset);

    // PVector v = PVector.fromAngle(map(perlinXY, -1.0, 1.0, 0, TWO_PI));
    PVector v1 = PVector.fromAngle(perlinXY * TWO_PI * 4.0);
    v1.setMag(0.025);
    //PVector v2 = PVector.fromAngle(perlinXZ * TWO_PI);

    x += v1.x;
    y += v1.y;
    z += v1.z;
  }

  void wind() {
    //float scl = 0.005;
    float scl = 0.05;
    offset += 0.0;

    float perlinXY = nois.noise3_ImproveXZ(windSeed, scl * x + offset, scl * y + offset, scl * z + offset);

    PVector v1 = PVector.fromAngle(perlinXY * TWO_PI * 4.0);
    v1.setMag(0.5);

    x += v1.x;
    y += v1.y;
    z += v1.z;
  }

  void boomInit() {
    boomVector = new PVector(x, y, z);
    boomVector.normalize();
  }

  void boom() {
    x += boomVector.x;
    y += boomVector.y;
    z += boomVector.z;
  }
  
  void vortexInit() {
    vortexTheta = calcTheta();  
  }
  
  void vortex() {
    vortexTheta = (vortexTheta + 0.01) % TWO_PI;
    PVector v1 = PVector.fromAngle(vortexTheta);
    v1.setMag(1.0);

    x += v1.x;
    y += v1.y;
    z += v1.z;
  }

  void updateTarget(float _x, float _y, float _z) {
    tarX = _x;
    tarY = _y;
    tarZ = _z;
  }

  void pointBetweenPoint(float per) {
    x = x + (tarX - x) * per;
    y = y + (tarY - y) * per;
    z = z + (tarZ - z) * per;
  }

  void update() {
    if (targetFlag) {
      pointBetweenPoint(per);
    }
    if (scatterFlag) {
      scatter();
    }
    if (swirlFlag) {
      swirl();
    }
    if (windFlag) {
      wind();
    }
    if (boomFlag) {
      boom();
    }
    if (vortexFlag) {
      vortex();
    }
  }

  void draw() {

    stroke(col);
    point(x, y, z);
  }
}
