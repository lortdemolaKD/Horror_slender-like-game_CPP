#pragma once
#include"libs.h"

class Sound
{
private: 
	irrklang::ISoundEngine* sound = irrklang::createIrrKlangDevice();
	const char* file;
	bool rep;
	float val;
public:
	Sound(const char* audio, bool repete, float valume)
	{
		this->sound = irrklang::createIrrKlangDevice();
		this->sound->setSoundVolume(valume);
		this->file = audio;
		this->rep = repete;
		this->val = valume;
		
	}
	~Sound()
	{
		this->sound->drop();
	}
	void play() 
	{
		this->sound->play2D(file, rep);
	}
	bool Isplaying()
	{
		return this->sound->isCurrentlyPlaying(file);
	}
	void stop()
	{
		this->sound->stopAllSounds();
	}
	void chvalume(float valume)
	{
		float vl;
		std::cout << this->val << endl;
		if (this->val <= 1.f || this->val >= 0.f) {
			vl = this->val + valume;
			this->sound->setSoundVolume(vl);
		}
		if (this->val > 1.f ) {
			vl = 1.f;
			this->sound->setSoundVolume(vl);
		}
		if (this->val < 0.f) {
			vl = 0.f;
			this->sound->setSoundVolume(vl);
		}
		this->val = vl;
	}

};