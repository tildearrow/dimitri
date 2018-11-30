#include "dimitri.h"
#include "devices/razer.h"
#include "effects/spectrum.h"
#include "effects/wave.h"
#include <math.h>
#include <unistd.h>

int frame;

std::vector<Device*> dev;

RazerDeviceEnum rzDE;

//SpectrumEffect se;
WaveEffect se;

int main(int argc, char** argv) {
  frame=0;

  if (!rzDE.isUsable()) {
    dimLogE("OpenRazer daemon not running!\n");
    return 1;
  }
  rzDE.init();
  dev=rzDE.enumerate();
  for (auto& i: dev) {
    i->init();
  }
  dimLogI("%d devices.\n",dev.size());
  while (1) {
    //dimLogD("frame %d\n",frame);
    for (auto& h: dev) {
      se.render(h->matrixWidth(),h->matrixHeight(),h->matrix);
      h->uploadMatrix();
    }
    frame++;
    usleep(30000);
  }
  return 0;
}
