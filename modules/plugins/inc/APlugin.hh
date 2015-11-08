#ifndef _APLUGIN_HH_
# define _APLUGIN_HH_

#include <thread>
#include "INetwork.hpp"

# define BLOCK_SIZE 50
# define NB_TRY_CONNECT 10

class APlugin {
public:
  enum eID {
    AUDIO_ID,
    VIDEO_ID
  };

  enum NetworkMode {
    CLIENT,
    SERVER
  };

private:
  std::thread *_threadIn;
  std::thread *_threadOut;
  std::string _address;
  APlugin::NetworkMode _networkMode;
  int _ID;
  bool _running;

public:
  bool run(const std::string & address, APlugin::NetworkMode mode);
  bool stop();
  APlugin(APlugin::eID id) : _ID(id), _running(false) {};
  virtual ~APlugin() {};

protected:
  virtual bool playInput(void *) = 0;
  virtual void *getOutput() = 0;

private:
  bool runThreadIn();
  bool runThreadOut();
  INetwork * initPeer(short port);
};

#endif
