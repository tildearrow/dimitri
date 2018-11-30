#include "dimitri.h"
#include "devices/razer.h"
#include <math.h>
#include <unistd.h>

int frame;

std::vector<Device*> dev;

RazerDeviceEnum rzDE;

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
    dimLogD("frame %d\n",frame);
    for (auto& h: dev) {
      for (int j=0; j<h->matrixHeight(); j++) {
        for (int i=0; i<h->matrixWidth(); i++) {
          h->matrix[j][i].r=fmod((float)(frame+i)/64.f,1);
          h->matrix[j][i].g=fmod((float)(frame-i+22)/64.f,1);
          h->matrix[j][i].b=fmod((float)(frame+j)/64.f,1);
        }
      }
      h->uploadMatrix();
    }
    frame++;
    usleep(30000);
  }
  /*
  QStringList serialnrs=libopenrazer::getConnectedDevices();
  libopenrazer::syncEffects(false);
  for (const QString &str: serialnrs) {
    libopenrazer::Device device=libopenrazer::Device(str);
    dimLogI("name: %s\n",qPrintable(device.getDeviceName()));
    dimLogD("serial: %s\n",qPrintable(str));
    QVector<QColor> colors=QVector<QColor>();

    if (device.hasMatrix()) {
      QList<int> dimen=device.getMatrixDimensions();
      for (int i=0; i<dimen[1]; i++) colors<<QColor(0,0,0);
      while (1) {
        dimLogD("frame %d\n",frame);
        for (int i=0; i<dimen[0]; i++) {
          //for (int i=0; i<dimen[1]; i++) colors[i]=QColor(0,((frame+i*2)*16)%255,128-i*4);
          for (int i=0; i<dimen[1]; i++) colors[i]=QColor(0,255,0);
          device.setKeyRow(i, 0, dimen[1]-1, colors);
        }
        device.setCustom();
        frame++;
        usleep(30000);
      }
    }
  }*/
  return 0;
}
