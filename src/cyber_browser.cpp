#include "cyber_browser.h"
#include "cef/cef.h"

class CyberCefClient : public CefClient {
private:
    CefRefPtr<CyberRenderHandler> _render_handler;
public:
    CyberCefClient() { _render_handler = new CyberRenderHandler(); }
    virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override {
        return _render_handler;
    }
    IMPLEMENT_REFCOUNTING(CyberCefClient);
};

CyberBrowser::CyberBrowser() {
    _global_ctx = GlobalContext::get_instance("./browser.ini");
    init_cef();
    load_o2o_toolbar_buttons();
    create_browser_window();
}

void CyberBrowser::init_cef() {
    CefMainArgs main_args(0, nullptr);
    CefRefPtr<CefApp> app;
    int exit_code = CefExecuteProcess(main_args, app, nullptr);
    if (exit_code >= 0) exit(exit_code);

    CefSettings settings;
    settings.cache_path = _global_ctx->get_Cache_Path();
    settings.locale = "zh-CN";
    settings.browser_subprocess_path = CefString("./cef_helper");
    settings.remote_debugging_port = std::stoi(_global_ctx->get_config_parser()->get_app_value("remote_debug_port", "9222"));
    settings.autoplay_policy = CEF_AUTOPLAY_POLICY_ALLOW_ALL;

    CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
    command_line->AppendSwitch("ignore-certificate-errors");
    command_line->AppendSwitch("allow-insecure-localhost");
    
    std::string user_agent = _global_ctx->get_config_parser()->get_app_value("UserAgent", "CyberWinBrowser/2025 (Linux ARM64) CEF/108.0.5359.124");
    command_line->AppendSwitchWithValue("user-agent", user_agent);

    command_line->AppendSwitch("enable-npapi");
    command_line->AppendSwitch("enable-flash");
    command_line->AppendSwitch("enable-media-stream");
    command_line->AppendSwitchWithValue("autoplay-policy", "no-user-gesture-required");

    CefInitialize(main_args, settings, app, command_line);
}

void CyberBrowser::load_o2o_toolbar_buttons() {
    const ConfigParser* parser = _global_ctx->get_config_parser();
    for (int i = 1;; i++) {
        std::string key = std::to_string(i);
        std::string value = parser->get_value("toolbar", key);
        if (value.empty()) break;

        size_t sep1 = value.find('|');
        size_t sep2 = value.find('|', sep1 + 1);
        if (sep1 == std::string::npos || sep2 == std::string::npos) continue;

        ToolBarButton btn;
        btn.label = value.substr(0, sep1);
        btn.icon_path = value.substr(sep1 + 1, sep2 - sep1 - 1);
        btn.url = value.substr(sep2 + 1);
        _toolbar_buttons.push_back(btn);

        printf("加载O2O按钮：%s, 图标：%s, 链接：%s\n", btn.label.c_str(), btn.icon_path.c_str(), btn.url.c_str());
    }
}

void CyberBrowser::create_browser_window() {
    CefWindowInfo window_info;
    window_info.SetAsChild(nullptr, CefRect(0, 0, 
        _global_ctx->get_window_width(), _global_ctx->get_window_height()));

    CefRefPtr<CyberCefClient> client = new CyberCefClient();
    CefBrowserHost::CreateBrowser(window_info, client, 
        _global_ctx->get_DefaultHome(), CefBrowserSettings(), nullptr);
}

void CyberBrowser::run() {
    CefRunMessageLoop();
    CefShutdown();
}
