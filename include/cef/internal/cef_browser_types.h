#ifndef CEF_BROWSER_TYPES_H_
#define CEF_BROWSER_TYPES_H_

#include "../cef_base.h"
#include "cef_types.h"

namespace Cef {
class CefClient;
class CefRenderProcessHandler;

class CefWindowInfo {
 public:
  void SetAsChild(void* parent, const CefRect& rect) {
    parent_window_ = parent;
    rect_ = rect;
  }

 private:
  void* parent_window_ = nullptr;
  CefRect rect_;
};

class CefBrowser : public virtual RefCountedBase {
 public:
  REFCOUNTING_METHODS
};

class CefClient : public virtual RefCountedBase {
 public:
  REFCOUNTING_METHODS
  virtual CefRenderProcessHandler* GetRenderProcessHandler() { return nullptr; }
};

class CefBrowserHost {
 public:
  static void CreateBrowser(const CefWindowInfo& window_info,
                            const RefPtr<CefClient>& client,
                            const CefString& url,
                            const CefBrowserSettings& settings,
                            void* extra_info) {}
};

int CefExecuteProcess(const CefMainArgs& args,
                      const RefPtr<CefApp>& app,
                      void* windows_sandbox_info);

void CefInitialize(const CefMainArgs& args,
                   const CefSettings& settings,
                   const RefPtr<CefApp>& app,
                   void* windows_sandbox_info);

void CefRunMessageLoop();
void CefShutdown();
}  // namespace Cef

#endif  // CEF_BROWSER_TYPES_H_
