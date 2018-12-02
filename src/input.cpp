#include "dimitri.h"

void* inthread(void* data) {
  ((InputWatch*)data)->run();
  return NULL;
}

extern bool mustChange;

void InputWatch::run() {
  XEvent event;
  dimLogI("input thread running.\n");
  while (1) {
    dimLogD("reading event.\n");
    XNextEvent(disp,&event);
    if (event.type==KeyPress) {
      dimLogD("got an event.\n");
      mustChange=true;
    }
  }
}

bool InputWatch::start() {
  disp=XOpenDisplay(NULL);
  if (disp==NULL) return false;
  rootw=DefaultRootWindow(disp);
  XGrabKey(disp,XKeysymToKeycode(disp,XK_8),0,rootw,true,GrabModeAsync,GrabModeAsync);
  if (pthread_create(&thread,NULL,inthread,this)<0) {
    XCloseDisplay(disp);
    return false;
  }
  return true;
}
