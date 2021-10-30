// rHSL2RGB version 1.0
// random HSL to RGB output
// © 2021 enzyme42.com

float hl = 0;
float hh = 360;
float hmax = 360.000f;
float sl = 70;
float sh = 100;
float smax = 100.000f;
float ll = 20;
float lh = 50;
float lmax = 100.000f;

float h, s, l, r, g, b, cr, cg, cb = 0.000f;
int fadeSteps = 64;
int fadeDelay = 50;
int changeDelay = 2000;
bool randomize = true;

float HueToRGB(float p, float q, float t) {
  if (t < 0) {
    t += 1;
  }
  if (t > 1) {
    t -= 1;
  }
  if (t < 1 / 6.0) {
    return p + (q - p) * 6 * t;
  }
  if (t < 1 / 2.0) {
    return q;
  }
  if (t < 2 / 3.0) {
    return p + (q - p) * (2 / 3.0 - t) * 6;
  }
  return p;
}

int HSLToRGB(float h, float s, float l, char color){
  float r, g, b;

  if (s == 0) {
    r = g = b = l;
  } else {
    const auto q = l < 0.5 ? l * (1 + s) : l + s - l * s;
    const auto p = 2 * l - q;
    r = HueToRGB(p, q, h + 1 / 3.0);
    g = HueToRGB(p, q, h);
    b = HueToRGB(p, q, h - 1 / 3.0);
  }
  
  if(color == 'r') {
    return round(r*255);
  } else if(color == 'g') {
    return round(g*255);
  } else if(color == 'b') {
    return round(b*255);
  }
}

float fade(float target, float current) {
  if(current < target) {
    current = current + ceil((target - current) / fadeSteps);
  } else if(current > target) {
    current = current - ceil((current - target) / fadeSteps);
  }
  
  return current;
}

void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  if(randomize == true) {
    randomSeed(analogRead(3));

    h = random(hl, hh) / hmax;
    s = random(sl, sh) / smax;
    l = random(ll, lh) / lmax;  

    r = HSLToRGB(h, s, l, 'r');
    g = HSLToRGB(h, s, l, 'g');
    b = HSLToRGB(h, s, l, 'b');

    randomize = false;
  }

  cr = fade(r, cr);
  cg = fade(g, cg);
  cb = fade(b, cb);
    
  analogWrite(0, cr);
  analogWrite(1, cg);
  analogWrite(4, cb);

  delay(fadeDelay);

  if(cr == r && cg == g && cb == b) {
    randomize = true;
    delay(changeDelay);
  }
}
