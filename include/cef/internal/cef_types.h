#ifndef CEF_TYPES_H_
#define CEF_TYPES_H_

#include <string>
#include <vector>

namespace Cef {
typedef std::string CefString;

struct CefRect {
  int x;
  int y;
  int width;
  int height;
  CefRect() : x(0), y(0), width(0), height(0) {}
  CefRect(int x_, int y_, int w_, int h_) : x(x_), y(y_), width(w_), height(h_) {}
};

enum CefAutoplayPolicy {
  AUTOPLAY_POLICY_DEFAULT = 0,
  AUTOPLAY_POLICY_ALLOW_ALL = 1,
  AUTOPLAY_POLICY_DENY_ALL = 2,
};

struct CefSettings {
  CefString cache_path;
  CefString locale;
  CefString browser_subprocess_path;
  int remote_debugging_port = 0;
  CefAutoplayPolicy autoplay_policy = AUTOPLAY_POLICY_DEFAULT;
};

struct CefMainArgs {
  int argc;
  char** argv;
  CefMainArgs(int argc_, char** argv_) : argc(argc_), argv(argv_) {}
};

struct CefBrowserSettings {
  CefBrowserSettings() = default;
};

typedef std::vector<CefString> CefStringList;
}  // namespace Cef

#endif  // CEF_TYPES_H_
