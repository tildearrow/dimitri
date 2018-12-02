#include "dimitri.h"

void Device::processSimple() {
  float smoothTrans;
  if (prevEffect!=NULL) {
    prevEffect->render(width,height,tempMatrix1);
  }
  if (effect!=NULL) {
    effect->render(width,height,tempMatrix2);
  }
  transition+=0.04;
  if (transition>1) {
    transition=1;
  }
  smoothTrans=2*pow(transition,2)-pow(transition,4);
  if (transition>=1) {
    memcpy(matrix,tempMatrix2,sizeof(Color<float>)*256*height);
  } else {
    for (int j=0; j<height; j++) for (int i=0; i<width; i++) {
      matrix[j][i].r=tempMatrix1[j][i].r+(tempMatrix2[j][i].r-tempMatrix1[j][i].r)*smoothTrans;
      matrix[j][i].g=tempMatrix1[j][i].g+(tempMatrix2[j][i].g-tempMatrix1[j][i].g)*smoothTrans;
      matrix[j][i].b=tempMatrix1[j][i].b+(tempMatrix2[j][i].b-tempMatrix1[j][i].b)*smoothTrans;
    }
  }
}

bool Device::initSimple() {
  prevEffect=NULL;
  effect=NULL;
  transition=0;
  return true;
}

bool Device::changeEffect(SimpleEffect* to) {
  prevEffect=effect;
  effect=to;
  transition=0;
  return true;
}
