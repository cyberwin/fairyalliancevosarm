#ifndef CYBER_BROWSER_H_
#define CYBER_BROWSER_H_

#include <string>
#include <vector>
#include "global_context.h"
#include "cyber_v8_handler.h"
#include "cef/cef.h"

struct ToolBarButton {
    std::string label;
    std::string icon_path;
    std::string url;
};

class CyberBrowser {
public:
    CyberBrowser();
    void run();

private:
    void init_cef();
    void load_o2o_toolbar_buttons();
    void create_browser_window();

    GlobalContext* _global_ctx;
    std::vector<ToolBarButton> _toolbar_buttons;
};

#endif // CYBER_BROWSER_H_
