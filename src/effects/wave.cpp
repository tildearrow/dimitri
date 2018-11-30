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
  if (direction==Up || direction==Down) {
    if (direction==Down) {
      pos-=0.025;
      if (pos<0) pos+=1;
    } else {
      pos+=0.025;
      pos-=(int)pos;
    }
    wpos=pos;
    for (int j=0; j<height; j++) {
      c.r=fmin(fmax(fabs(2.0-wpos*6+1.0)-1.0,0.0),1.0);
      c.g=(1.0-fmin(fmax(fabs(1.0-wpos*6.0+1.0)-1.0,0.0),1.0));
      c.b=(1.0-fmin(fmax(fabs(1.0-wpos*6.0+3.0)-1.0,0.0),1.0));
      for (int i=0; i<width; i++) {
        where[j][i]=c;
      }
      wpos+=0.1;
      wpos-=(int)wpos;
    }
    c.r=fmin(fmax(fabs(2.0-wpos*6+1.0)-1.0,0.0),1.0);
    c.g=(1.0-fmin(fmax(fabs(1.0-wpos*6.0+1.0)-1.0,0.0),1.0));
    c.b=(1.0-fmin(fmax(fabs(1.0-wpos*6.0+3.0)-1.0,0.0),1.0));
    where[0][20]=c;
  } else {
    if (direction==Right) {
      pos-=0.025;
      if (pos<0) pos+=1;
    } else {
      pos+=0.025;
      pos-=(int)pos;
    }
    wpos=pos;
    for (int i=0; i<width; i++) {
      c.r=fmin(fmax(fabs(2.0-wpos*6+1.0)-1.0,0.0),1.0);
      c.g=(1.0-fmin(fmax(fabs(1.0-wpos*6.0+1.0)-1.0,0.0),1.0));
      c.b=(1.0-fmin(fmax(fabs(1.0-wpos*6.0+3.0)-1.0,0.0),1.0));
      for (int j=(i!=20)?0:1; j<height; j++) {
        where[j][i]=c;
      }
      wpos+=0.05;
      wpos-=(int)wpos;
      if (i==11) {
        where[0][20]=c;
      }
    }
  }
  return true;
}
