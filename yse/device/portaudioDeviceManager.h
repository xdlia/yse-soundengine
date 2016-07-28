/*
  ==============================================================================

    portaudioDeviceManager.h
    Created: 27 Jul 2016 5:20:20pm
    Author:  yvan

  ==============================================================================
*/

#ifdef PORTAUDIO_BACKEND

#ifndef PORTAUDIODEVICEMANAGER_H_INCLUDED
#define PORTAUDIODEVICEMANAGER_H_INCLUDED

#pragma comment(lib, "portaudio_x86.lib")

#include "../classes.hpp"
#include "../headers/types.hpp"
#include "abstractDeviceManager.h"

#include "portaudio.h"

namespace YSE {
  
  namespace DEVICE {

    class managerObject : public abstractDeviceManager {
    public:
      managerObject();

      virtual Bool init();
      virtual void close();
      virtual Flt cpuLoad();

      virtual void updateDeviceList();
      virtual void openDevice(const YSE::DEVICE::setupObject & object);
      virtual void addCallback();

      static int paCallback(
        const void *input
        , void *output
        , unsigned long numSamples
        , const PaStreamCallbackTimeInfo* timeInfo
        , PaStreamCallbackFlags statusFlags
        , void * userData);

    private:
      void audioDeviceError(PaError err);
      
      PaStream * stream;
      PaError err;
      UInt bufferPos;
      bool initDone, open, started;
    };

    managerObject & Manager();

  }

}



#endif  // PORTAUDIODEVICEMANAGER_H_INCLUDED

#endif // PORTAUDIO_BACKEND