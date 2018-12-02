#include "dimitri.h"

void Device::processSimple() {      
  effect->render(width,height,matrix);
}
