#include "global_context.h"
#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;
std::unique_ptr<GlobalContext> GlobalContext::_instance = nullptr;

GlobalContext::GlobalContext(const std::string& config_path) {
    _config_parser = std::make_unique<ConfigParser>(config_path);
    init_vars();
}

void GlobalContext::init_vars() {
    auto parser = _config_parser.get();
    // 原C#变量初始化
    CyberWinPHP_Path = parser->get_app_value("CyberWinPHP_Path", fs::current_path().string() + "/CyberWinPHP");
    浏览器_setting_path = CyberWinPHP_Path + "/browser.ini";
    eT_setting_path = CyberWinPHP_Path + "/eT_setting.ini";
    setting_path_eT = eT_setting_path;
    setting_path_酒店_前台 = CyberWinPHP_Path + "/hotel_front.ini";
    setting_path_配置 = CyberWinPHP_Path + "/global_config.ini";
    cT_wlzc2o_path = parser->get_app_value("cT_wlzc2o_path", CyberWinPHP_Path + "/wlzc2o/");
    setting_browser_ispopup = std::stoi(parser->get_app_value("browser_ispopup", "0")) == 1;

    // 业务变量初始化
    DefaultHome = parser->get_app_value("DefaultHome");
    Cache_Path = parser->get_app_value("Cache_Path", CyberWinPHP_Path + "/Cyber_Cache");
    ICO = parser->get_app_value("ICO");
    window_width = std::stoi(parser->get_value("interface", "window_width", "460"));
    window_height = std::stoi(parser->get_value("interface", "window_height", "640"));
    btn_size = std::stoi(parser->get_app_value("btn_size", "32"));
    showToolBar = std::stoi(parser->get_app_value("showToolBar", "1")) == 1;
    DeviceUUidEx = parser->get_app_value("DeviceUUidEx");
}

GlobalContext* GlobalContext::get_instance(const std::string& config_path) {
    if (_instance == nullptr) {
        if (config_path.empty()) {
            throw std::runtime_error("GlobalContext未初始化！请先传入配置文件路径");
        }
        _instance = std::make_unique<GlobalContext>(config_path);
    }
    return _instance.get();
}
