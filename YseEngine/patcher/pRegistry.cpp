#include "pRegistry.h"
#include "pObjectList.hpp"

#include "genericObjects\pDac.h"
#include "genericObjects/pLine.h"
#include "generatorObjects/pSine.h"

#include "guiObjects\gInt.h"
#include "guiObjects\gFloat.h"
#include "guiObjects\gSlider.h"
#include "guiObjects\gButton.h"
#include "guiObjects\gToggle.h"

#include "time\gMetro.h"

#include "math/dAdd.h"
#include "math/dSubstract.h"
#include "math/dDivide.h"
#include "math/dMultiply.h"
#include "math/pMidiToFrequency.h"
#include "math/pFrequencyToMidi.h"

#include "filters\pBandpass.h"
#include "filters\pHighpass.h"
#include "filters\pLowpass.h"

#include "math\gAdd.h"
#include "math\gDivide.h"
#include "math\gMultiply.h"
#include "math\gSubstract.h"
#include "math\gRandom.h"

using namespace YSE::PATCHER;

YSE::PATCHER::pRegistry & YSE::PATCHER::Register() {
  static pRegistry s;
  return s;
}

pRegistry::pRegistry() {
  // add all objects here

  // Generic DSP
  Add(OBJ::D_LINE, pLine::Create);

  Add(OBJ::D_SINE, pSine::Create);

  Add(OBJ::D_ADD, dAdd::Create);
  Add(OBJ::D_SUBSTRACT, dSubstract::Create);
  Add(OBJ::D_MULTIPLY, dMultiply::Create);
  Add(OBJ::D_DIVIDE, dDivide::Create);
  
  // Generic GUI
  Add(OBJ::G_INT, gInt::Create);
  Add(OBJ::G_FLOAT, gFloat::Create);
  Add(OBJ::G_SLIDER, gSlider::Create);
  Add(OBJ::G_BUTTON, gButton::Create);
  Add(OBJ::G_TOGGLE, gToggle::Create);

  Add(OBJ::G_ADD, gAdd::Create);
  Add(OBJ::G_DIVIDE, gDivide::Create);
  Add(OBJ::G_MULTIPLY, gMultiply::Create);
  Add(OBJ::G_SUBSTRACT, gSubstract::Create);
  Add(OBJ::G_RANDOM, gRandom::Create);

  Add(OBJ::G_METRO, gMetro::Create);

  Add(OBJ::MIDITOFREQUENCY, pMidiToFrequency::Create);
  Add(OBJ::FREQUENCYTOMIDI, pFrequencyToMidi::Create);

  Add(OBJ::D_LOWPASS, pLowpass::Create);
  Add(OBJ::D_BANDPASS, pBandpass::Create);
  Add(OBJ::D_HIGHPASS, pHighpass::Create);
}

pObject* pRegistry::Get(const std::string & objectID) {
  auto it = map.find(objectID);
  if (it != map.end()) return it->second();
  return nullptr;
}

void pRegistry::Add(const std::string & objectID, pObjectFunc f) {
  map.insert(std::pair<std::string, pObjectFunc>(objectID, f));
}

bool pRegistry::IsValidObject(const char * objectID) {
  auto it = map.find(objectID);
  return it != map.end();
}