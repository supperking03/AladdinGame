#include "CallFunc.h"

NAMESPACE_ALA
{
  ALA_CLASS_SOURCE_1(CallFunc, ala::Action)

  CallFunc::CallFunc(const std::function<void()>& func) : _func(func) {}

void CallFunc::onStart() {
  _func();

  done();
}
}
