#ifndef GLOBAL_CONTEXT_H_
#define GLOBAL_CONTEXT_H_

#include <string>
#include <memory>
#include "config_parser.h"

class GlobalContext {
public:
    static GlobalContext* get_instance(const std::string& config_path = "");
    ~GlobalContext() = default;

    // 原C#映射变量
    std::string CyberWinPHP_Path;
    std::string 浏览器_setting_path;
    std::string eT_setting_path;
    std::string setting_path_eT;
    std::string setting_path_酒店_前台;
    std::string setting_path_配置;
    std::string cT_wlzc2o_path;
    bool setting_browser_ispopup;

    // 业务变量
    std::string DefaultHome;
    std::string Cache_Path;
    std::string ICO;
    int window_width;
    int window_height;
    int btn_size;
    bool showToolBar;
    std::string DeviceUUidEx;

    const ConfigParser* get_config_parser() const { return _config_parser.get(); }

private:
    explicit GlobalContext(const std::string& config_path);
    void init_vars();
    static std::unique_ptr<GlobalContext> _instance;
    std::unique_ptr<ConfigParser> _config_parser;
};

#endif // GLOBAL_CONTEXT_H_
