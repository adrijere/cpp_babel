#ifndef _APLUGIN_HH_
# define _APLUGIN_HH_

#include <thread>

enum eID {
  AUDIO_ID,
  VIDEO_ID
};

class APlugin {
private:
  std::thread *_set;
  std::thread *_get;
  int _ID;

public:
  bool run();
  bool runSet();
  bool runGet();
  virtual bool sendData(void *) = 0;
  virtual void *getData() = 0;
  APlugin(eID id) : _ID(id) {};
  virtual ~APlugin() {};
};

#endif
