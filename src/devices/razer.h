#include "../dimitri.h"

class RazerDevice: public Device {
#ifdef _LOR_DEVICE
  libopenrazer::Device* inst;
#else
  void* inst;
#endif
  public:
#ifdef _LOR_DEVICE
    void setORDevice(libopenrazer::Device* ptr);
#else
    void setORDevice(void* ptr);
#endif
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
