#include "dimitri.h"

int dimLogD(const char* format, ...) {
  va_list va;
  int ret;
  if (logLevel<LOGLEVEL_DEBUG) return 0;
  printf("\x1b[1;34m[debug]\x1b[m ");
  va_start(va,format);
  ret=vprintf(format,va);
  va_end(va);
  return ret;
}

int dimLogI(const char* format, ...) {
  va_list va;
  int ret;
  if (logLevel<LOGLEVEL_INFO) return 0;
  printf("\x1b[1;32m[info]\x1b[m ");
  va_start(va,format);
  ret=vprintf(format,va);
  va_end(va);
  return ret;
}

int dimLogW(const char* format, ...) {
  va_list va;
  int ret;
  if (logLevel<LOGLEVEL_WARN) return 0;
  printf("\x1b[1;33m[warning]\x1b[m ");
  va_start(va,format);
  ret=vprintf(format,va);
  va_end(va);
  return ret;
}

int dimLogE(const char* format, ...) {
  va_list va;
  int ret;
  if (logLevel<LOGLEVEL_ERROR) return 0;
  printf("\x1b[1;31m[ERROR]\x1b[m ");
  va_start(va,format);
  ret=vprintf(format,va);
  va_end(va);
  return ret;
}

