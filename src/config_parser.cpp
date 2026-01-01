#include "config_parser.h"
#include "ini.h"

static int ini_parse_handler(void* user, const char* section, const char* name, const char* value) {
    auto* parser = static_cast<ConfigParser*>(user);
    parser->_config_data[std::string(section)][std::string(name)] = std::string(value);
    return 1;
}

void ConfigParser::load_file(const std::string& config_path) {
    if (!fs::exists(config_path)) {
        return;
    }
    ini_parse(config_path.c_str(), ini_parse_handler, this);
}

ConfigParser::ConfigParser(const std::string& config_path) {
    _cyber_php_path = fs::current_path().string() + "/CyberWinPHP";
    load_file(config_path);
}

std::string ConfigParser::get_value(const std::string& section, 
                                    const std::string& key, 
                                    const std::string& default_val) {
    if (_config_data.find(section) == _config_data.end()) {
        return default_val;
    }
    auto& section_map = _config_data[section];
    if (section_map.find(key) == section_map.end()) {
        return default_val;
    }

    std::string val = section_map[key];
    size_t pos = val.find("%CyberWinPHP_Path%");
    if (pos != std::string::npos) {
        val.replace(pos, 19, _cyber_php_path);
    }
    return val;
}

std::string ConfigParser::get_app_value(const std::string& key, const std::string& default_val) {
    return get_value("APP", key, default_val);
}
