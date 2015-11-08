#ifndef _APLUGIN_HH_
# define _APLUGIN_HH_

#include <thread>

enum eID {
  AUDIO_ID,
  VIDEO_ID
};

class APlugin {
private:
  std::thread *_threadIn;
  std::thread *_threadOut;
  int _ID;
  bool _running;

public:
  bool run();
  bool stop();
  APlugin(eID id) : _ID(id), _running(false) {};
  virtual ~APlugin() {};

protected:
  virtual bool runThreadIn() = 0;
  virtual bool runThreadOut() = 0;
  virtual bool playInput(void *) = 0;
  virtual void *getOutput() = 0;

private:
  bool runThreadIn_wrapper();
  bool runThreadOut_wrapper();
};

#endif
