#include "libopenrazer.h"
#include <QColor>
#include <QDebug>

int main(int argc, char** argv) {
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

    if (device.hasMatrix()) {
      QList<int> dimen=device.getMatrixDimensions();
      QVector<QColor> colors=QVector<QColor>();
      for (int i=0; i<dimen[1]; i++) colors << QColor(0,i*6,128-i*4);
      for (int i=0; i<dimen[0]; i++) {
        device.setKeyRow(i, 0, dimen[1]-1, colors);
        device.setCustom();
      }
    }
  }
  return 0;
}
