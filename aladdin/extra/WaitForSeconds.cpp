#include "WaitForSeconds.h"

NAMESPACE_ALA
{
  ALA_CLASS_SOURCE_1(ala::WaitForSeconds, ala::Action)

  WaitForSeconds::WaitForSeconds(const float totalWaitTime) : _elapsedTime(0), _totalWaitTime(totalWaitTime) {

}

void WaitForSeconds::onStart() {
  _elapsedTime = 0;
}

void WaitForSeconds::onUpdate(const float delta) {
  _elapsedTime += delta;

  if (_elapsedTime >= _totalWaitTime) done();
}
}
