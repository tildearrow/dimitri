#include "../dimitri.h"

class WaveEffect: public SimpleEffect {
  enum Direction {
    Up=0, Right, Down, Left
  };
  float pos;
  Direction direction;
  public:
    std::vector<string> getParamNames();
    string getParam(string name);
    bool setParam(string name, string value);
    bool render(int width, int height, Color<float> where[256][256]);
    WaveEffect(): pos(0), direction(Right) {};
};
