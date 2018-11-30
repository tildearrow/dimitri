#include "../dimitri.h"

class SpectrumEffect: public SimpleEffect {
  float pos;
  public:
    std::vector<string> getParamNames();
    string getParam(string name);
    bool setParam(string name, string value);
    bool render(int width, int height, Color<float> where[256][256]);
    SpectrumEffect(): pos(0) {};
};
