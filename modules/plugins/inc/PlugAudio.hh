#ifndef _PLUGAUDIO_HH_
# define _PLUGAUDIO_HH_

#include "APlugin.hh"
/*
#include "BabelOpus.hh"
#include "BabelAudio.hh"
*/

class PlugAudio : public APlugin {
private:
	/*
	BabelOpus _opus;
	BabelAudio _audio;
	*/
protected:
	bool playInput(void *);
	void *getOutput();

public:
	PlugAudio();
	~PlugAudio();
};

#endif
