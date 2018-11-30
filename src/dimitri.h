#ifndef _DIMITRI_H
#define _DIMITRI_H
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdexcept>
#include <vector>
#include <string>
#include <linux/input-event-codes.h>

#define LOGLEVEL_ERROR 0
#define LOGLEVEL_WARN 1
#define LOGLEVEL_INFO 2
#define LOGLEVEL_DEBUG 3

#define logLevel 3

typedef std::string string;

#define S(x) string(x)

int dimLogD(const char* format, ...);
int dimLogI(const char* format, ...);
int dimLogW(const char* format, ...);
int dimLogE(const char* format, ...);

bool operator ==(const struct timespec& l, const struct timespec& r);
bool operator >(const struct timespec& l, const struct timespec& r);
bool operator <(const struct timespec& l, const struct timespec& r);
struct timespec operator +(const struct timespec& l, const struct timespec& r);
struct timespec operator -(const struct timespec& l, const struct timespec& r);
struct timespec operator +(const struct timespec& l, const long& r);
struct timespec operator -(const struct timespec& l, const long& r);
struct timespec mkts(time_t sec, long nsec);
struct timespec stots(string s);
string tstos(struct timespec ts);
struct timespec curTime(clockid_t clockSource);

template<typename T> struct Coords {
  T x, y;
  Coords(T xv, T yv): x(xv), y(yv) {}
  Coords(): x(0), y(0) {}
};

template<typename T> struct Color {
  T r, g, b;
  Color(T red, T green, T blue): r(red), g(green), b(blue) {}
  Color(): r(0), g(0), b(0) {}
};

template<typename T> struct AlphaColor {
  T r, g, b, a;
};

class SimpleEffect {
  protected:
    string name;
  public:
    virtual std::vector<string> getParamNames()=0;
    virtual string getParam(string name)=0;
    virtual bool setParam(string name, string value)=0;
    virtual bool render(int width, int height, Color<float> where[256][256])=0;
};

class Device {
  protected:
    string id;
    string name;
    int width, height;
    Coords<int> keypos[KEY_CNT];
  public:
    // should be enough to contain most devices
    Color<float> matrix[256][256];
    virtual Coords<int> getCoordsFromKeycode(short keycode)=0;
    virtual short getKeycodeFromCoords(Coords<int> c)=0;
    virtual void clearMatrix()=0;
    virtual bool uploadMatrix()=0;
    int matrixWidth() {return width;}
    int matrixHeight() {return height;}
    virtual bool init()=0;
    virtual bool quit()=0;
};

class DeviceEnum {
  public:
    virtual std::vector<Device*> enumerate() {
      return std::vector<Device*>();
    }
    virtual bool isUsable() {
      return false;
    }
    virtual bool init() {
      return false;
    }
};

#endif
