#ifndef _APLUGIN_HH_
# define _APLUGIN_HH_

enum eID {
  AUDIO_ID,
  VIDEO_ID
};

class APlugin {
private:
  int _ID;
public:
  virtual bool sendData(unsigned char *, unsigned int) = 0;
  virtual unsigned char *getData() = 0;
  APlugin(eID id) : _ID(id) {};
  virtual ~APlugin() {};
};

#endif
