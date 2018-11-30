#include "../dimitri.h"
#include "libopenrazer.h"
#include <QColor>
#include <QDebug>

class RazerDevice: public Device {
  libopenrazer::Device* inst;
  public:
    void setORDevice(libopenrazer::Device& ptr);
    Coords<int> getCoordsFromKeycode(short keycode);
    short getKeycodeFromCoords(Coords<int> c);
    void clearMatrix();
    bool uploadMatrix();
    bool init();
    bool quit();
};

class RazerDeviceEnum: public DeviceEnum {
  public:
    std::vector<Device*> enumerate();
    bool isUsable();
    bool init();
};
