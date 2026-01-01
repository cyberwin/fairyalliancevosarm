#ifndef CEF_V8_TYPES_H_
#define CEF_V8_TYPES_H_

#include "../cef_base.h"
#include "cef_types.h"

namespace Cef {
class CefV8Value : public virtual RefCountedBase {
 public:
  REFCOUNTING_METHODS
  static RefPtr<CefV8Value> CreateObject(void* ptr, void* ptr2) {
    return RefPtr<CefV8Value>(new CefV8Value());
  }

  static RefPtr<CefV8Value> CreateString(const CefString& str) {
    return RefPtr<CefV8Value>(new CefV8Value());
  }

  static RefPtr<CefV8Value> CreateBool(bool value) {
    return RefPtr<CefV8Value>(new CefV8Value());
  }

  void SetValue(const CefString& key,
                const RefPtr<CefV8Value>& value,
                int attribute) {}
};

typedef std::vector<RefPtr<CefV8Value>> CefV8ValueList;

class CefV8Handler : public virtual RefCountedBase {
 public:
  REFCOUNTING_METHODS
  virtual bool Execute(const CefString& name,
                       const CefV8ValueList& arguments,
                       const RefPtr<CefV8Value>& retval,
                       CefString& exception) = 0;
};

class CefV8Context {
 public:
  RefPtr<CefV8Value> GetGlobal() {
    return RefPtr<CefV8Value>(new CefV8Value());
  }
};

class CefRenderProcessHandler : public virtual RefCountedBase {
 public:
  REFCOUNTING_METHODS
  virtual void OnContextCreated(const RefPtr<CefBrowser>& browser,
                                const RefPtr<CefV8Context>& context) {}
};

const int V8_PROPERTY_ATTRIBUTE_NONE = 0;
}  // namespace Cef

#endif  // CEF_V8_TYPES_H_
