/*
  ==============================================================================

    abstractDeviceManager.cpp
    Created: 27 Jul 2016 1:46:50pm
    Author:  yvan

  ==============================================================================
*/


#include "../internalHeaders.h"

YSE::DEVICE::abstractDeviceManager::abstractDeviceManager() 
  : master(nullptr)
  , currentInputChannels(0)
  , currentOutputChannels(2)
{
}

YSE::DEVICE::abstractDeviceManager::~abstractDeviceManager()
{
  close();
}

Bool YSE::DEVICE::abstractDeviceManager::init()
{
  updateDeviceList();
  return true;
}



bool YSE::DEVICE::abstractDeviceManager::doOnCallback(int numSamples)
{
  if (master == nullptr) return false;

  if (INTERNAL::Global().needsUpdate()) {
    // update global objects
    INTERNAL::Time().update();
    INTERNAL::ListenerImpl().update();
    SOUND::Manager().update();
    CHANNEL::Manager().update();
    REVERB::Manager().update();
    MIDI::Manager().update();
    SCALE::Manager().update();
    MOTIF::Manager().update();
    // TODO: check if we still have to release sounds (see old code)
    INTERNAL::Global().updateDone();
  }

  // player and synth managers update all the time, because midi messages might come in
  // between two buffer updates and should have the least latency possible
  INTERNAL::DeviceTime().update();
  PLAYER::Manager().update((Flt)numSamples / (Flt)SAMPLERATE);
  SYNTH::Manager().update();

  if (SOUND::Manager().empty()) return false;

  /* adjust channels if needed
  this actually realocates a lot of memory but it is only done when changing to an
  output that doesn't have the same amount of channels. Some jitter is to be expected
  at that point anyway.
  */
  if (CHANNEL::Manager().getNumberOfOutputs() != master->out.size()) {
    CHANNEL::Manager().changeChannelConf();
    master->resize(true);
  }

  return true;
}

void YSE::DEVICE::abstractDeviceManager::setMaster(CHANNEL::implementationObject * ptr)
{
  master = ptr;
}

YSE::CHANNEL::implementationObject & YSE::DEVICE::abstractDeviceManager::getMaster()
{
  return *master;
}

const std::vector<YSE::DEVICE::interfaceObject>& YSE::DEVICE::abstractDeviceManager::getDeviceList()
{
  return devices;
}

const std::string & YSE::DEVICE::abstractDeviceManager::getDefaultTypeName()
{
  return defaultTypeName;
}

const std::string & YSE::DEVICE::abstractDeviceManager::getDefaultDeviceName()
{
  return defaultDeviceName;
}
