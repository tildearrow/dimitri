#include "../dimitri.h"

class WaveEffect: public SimpleEffect {
  float pos;
  public:
    std::vector<string> getParamNames();
    string getParam(string name);
    bool setParam(string name, string value);
    bool render(int width, int height, Color<float> where[256][256]);
    WaveEffect(): pos(0) {};
};
