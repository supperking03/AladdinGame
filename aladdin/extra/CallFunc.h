#ifndef __ALADDIN_EXTRA_CALL_FUNC_H__
#define __ALADDIN_EXTRA_CALL_FUNC_H__

#include "Action.h"

NAMESPACE_ALA
{
  ALA_CLASS_HEADER_1(CallFunc, ala::Action)
private:
  std::function<void()> _func;

public:
  CallFunc(const std::function<void()>& func);

protected:
  void onStart() override;
};
}

#endif //!__ALADDIN_EXTRA_CALL_FUNC_H__
