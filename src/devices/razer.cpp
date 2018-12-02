#include "libopenrazer.h"
#include <QColor>
#include <QDebug>
#include <qmetatype.h>
#define _LOR_DEVICE
#include "razer.h"

void RazerDevice::setORDevice(libopenrazer::Device* ptr) {
  inst=new libopenrazer::Device(*ptr);
}

void RazerDevice::clearMatrix() {
}

Coords<int> RazerDevice::getCoordsFromKeycode(short keycode) {
  return Coords<int>(0,0);
}

short RazerDevice::getKeycodeFromCoords(Coords<int> c) {
  return -1;
}

bool RazerDevice::init() {
  QList<int> size=inst->getMatrixDimensions();
  height=size[0];
  width=size[1];
  return false;
}

bool RazerDevice::quit() {
  return false;
}

bool RazerDevice::uploadMatrix() {
  QVector<QColor> colors;
  for (int j=0; j<height; j++) {
    colors.clear();
    for (int i=0; i<width; i++) colors << QColor(matrix[j][i].r*255,matrix[j][i].g*255,matrix[j][i].b*255);
    inst->setKeyRow(j,0,width-1,colors);
  }
  if (!inst->setCustom()) dimLogE("failure\n");
  libopenrazer::getTurnOffOnScreensaver();
  return true;
}

std::vector<Device*> RazerDeviceEnum::enumerate() {
  std::vector<Device*> ret;
  RazerDevice* add;
  QStringList probe=libopenrazer::getConnectedDevices();
  
  for (auto& i: probe) {
    libopenrazer::Device dev=libopenrazer::Device(i);
    if (!dev.hasMatrix()) break;
    add=new RazerDevice;
    add->setORDevice(&dev);
    ret.push_back(add);
  }
  return ret;
}

bool RazerDeviceEnum::isUsable() {
  return libopenrazer::isDaemonRunning();
}

bool RazerDeviceEnum::init() {
  libopenrazer::syncEffects(false);
  return true;
}
