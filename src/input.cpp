#include "dimitri.h"

void* inthread(void* data) {
  ((InputWatch*)data)->run();
  return NULL;
}

void InputWatch::run() {
  XEvent event;
  while (1) {
    XNextEvent(disp,&event);
    dimLogD("got an event.\n");
  }
}

bool InputWatch::start() {
  disp=XOpenDisplay(NULL);
  if (disp==NULL) return false;
  if (pthread_create(&thread,NULL,inthread,this)<0) {
    XCloseDisplay(disp);
    return false;
  }
  return true;
}
