#include "dimitri.h"
#include "devices/razer.h"
#include "effects/static.h"
#include "effects/spectrum.h"
#include "effects/wave.h"
#include <math.h>
#include <unistd.h>

int frame;

std::vector<Device*> dev;

RazerDeviceEnum rzDE;

struct timespec nextTime;

InputWatch inWatch;

void sleepUntilNext() {
  struct timespec t, rem;
  t=curTime(CLOCK_MONOTONIC);
  t=nextTime-t;
  nanosleep(&t,NULL);
  nextTime=nextTime+mkts(0,(1000000000/40));
}

int main(int argc, char** argv) {
  frame=0;
  nextTime=curTime(CLOCK_MONOTONIC)+mkts(0,(1000000000/40));

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
  inWatch.start();
  while (1) {
    dimLogD("frame %d\n",frame);
    int i=0;
    for (auto& h: dev) {
      h->processSimple();
      h->uploadMatrix();
      i++;
    }
    frame++;
    sleepUntilNext();
  }
  return 0;
}
