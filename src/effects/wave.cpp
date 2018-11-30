#include "wave.h"

string WaveEffect::getParam(string name) {
  return "<ERROR!>";
}

std::vector<string> WaveEffect::getParamNames() {
  return std::vector<string>();
}

bool WaveEffect::setParam(string name, string value) {
  return false;
}

// TODO: fix on mouse. yeah, it almost looks correct but it is not
bool WaveEffect::render(int width, int height, Color<float> where[256][256]) {
  float wpos;
  Color<float> c;
  pos+=0.01;
  pos-=(int)pos;
  wpos=pos;
  for (int i=0; i<width; i++) {
    c.r=fmax(0.05,fmin(fmax(fabs(2.0-wpos*6+1.0)-1.0,0.0),1.0));
    c.g=fmax(0.05,(1.0-fmin(fmax(fabs(1.0-wpos*6.0+1.0)-1.0,0.0),1.0)));
    c.b=fmax(0.05,(1.0-fmin(fmax(fabs(1.0-wpos*6.0+3.0)-1.0,0.0),1.0)));
    for (int j=0; j<height; j++) {
      where[j][i]=c;
    }
    wpos+=0.05;
    wpos-=(int)wpos;
  }
  return true;
}
