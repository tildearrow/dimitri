#include "static.h"

string StaticEffect::getParam(string name) {
  return "<ERROR!>";
}

std::vector<string> StaticEffect::getParamNames() {
  return std::vector<string>();
}

bool StaticEffect::setParam(string name, string value) {
  return false;
}

// TODO: fix red offset
bool StaticEffect::render(int width, int height, Color<float> where[256][256]) {
  for (int j=0; j<height; j++) for (int i=0; i<width; i++) {
    where[j][i]=c;
  }
  return true;
}
