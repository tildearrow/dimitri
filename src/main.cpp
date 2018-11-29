#include "libopenrazer.h"
#include <unistd.h>
#include <QColor>
#include <QDebug>

int frame;

int main(int argc, char** argv) {
  frame=0;
  if (!libopenrazer::isDaemonRunning()) {
    printf("OpenRazer daemon not running!\n");
    return 1;
  }
  QStringList serialnrs=libopenrazer::getConnectedDevices();
  libopenrazer::syncEffects(false);
  foreach (const QString &str, serialnrs) {
    libopenrazer::Device device=libopenrazer::Device(str);
    printf("name: %s\n",qPrintable(device.getDeviceName()));
    printf("serial: %s\n",qPrintable(str));
    QVector<QColor> colors=QVector<QColor>();

    if (device.hasMatrix()) {
      QList<int> dimen=device.getMatrixDimensions();
      for (int i=0; i<dimen[1]; i++) colors<<QColor(0,0,0);
      while (1) {
        printf("frame %d\n",frame);
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
  }
  return 0;
}
