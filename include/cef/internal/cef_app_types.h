#ifndef CEF_APP_TYPES_H_
#define CEF_APP_TYPES_H_

#include "../cef_base.h"
#include "cef_types.h"

namespace Cef {
class CefApp : public virtual RefCountedBase {
 public:
  REFCOUNTING_METHODS
  virtual ~CefApp() = default;
};

class CefCommandLine : public virtual RefCountedBase {
 public:
  REFCOUNTING_METHODS
  static RefPtr<CefCommandLine> CreateCommandLine() {
    return RefPtr<CefCommandLine>(new CefCommandLine());
  }

  void AppendSwitch(const CefString& switch_) { switches_.push_back(switch_); }
  void AppendSwitchWithValue(const CefString& switch_, const CefString& value) {
    switch_values_[switch_] = value;
  }

 private:
  std::vector<CefString> switches_;
  std::map<CefString, CefString> switch_values_;
};
}  // namespace Cef

#endif  // CEF_APP_TYPES_H_
