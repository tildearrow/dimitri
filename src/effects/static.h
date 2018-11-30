#include "../dimitri.h"

class StaticEffect: public SimpleEffect {
  Color<float> c;
  public:
    std::vector<string> getParamNames();
    string getParam(string name);
    bool setParam(string name, string value);
    bool render(int width, int height, Color<float> where[256][256]);
    StaticEffect(): c(0,1,0) {};
};
