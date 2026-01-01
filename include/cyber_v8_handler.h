#ifndef CYBER_V8_HANDLER_H_
#define CYBER_V8_HANDLER_H_

#include "cef/cef.h"

class CyberV8Handler : public Cef::CefV8Handler {
public:
    IMPLEMENT_REFCOUNTING(CyberV8Handler);

    bool Execute(const Cef::CefString& name,
                 const Cef::CefV8ValueList& arguments,
                 const Cef::RefPtr<Cef::CefV8Value>& retval,
                 Cef::CefString& exception) override;
};

class CyberRenderHandler : public Cef::CefRenderProcessHandler {
public:
    IMPLEMENT_REFCOUNTING(CyberRenderHandler);

    void OnContextCreated(const Cef::RefPtr<Cef::CefBrowser>& browser,
                          const Cef::RefPtr<Cef::CefV8Context>& context) override;
};

#endif // CYBER_V8_HANDLER_H_
