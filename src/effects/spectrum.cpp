#include "spectrum.h"

string SpectrumEffect::getParam(string name) {
  return "<ERROR!>";
}

std::vector<string> SpectrumEffect::getParamNames() {
  return std::vector<string>();
}

bool SpectrumEffect::setParam(string name, string value) {
  return false;
}

// TODO: fix red offset
bool SpectrumEffect::render(int width, int height, Color<float> where[256][256]) {
  Color<float> c;
  pos+=0.0003;
  pos-=(int)pos;
  c.r=fmax(0.05,fmin(fmax(fabs(2.0-pos*6+1.0)-1.0,0.0),1.0));
  c.g=fmax(0.05,(1.0-fmin(fmax(fabs(1.0-pos*6.0+1.0)-1.0,0.0),1.0)));
  c.b=fmax(0.05,(1.0-fmin(fmax(fabs(1.0-pos*6.0+3.0)-1.0,0.0),1.0)));
  for (int j=0; j<height; j++) for (int i=0; i<width; i++) {
    where[j][i]=c;
  }
  return true;
}
