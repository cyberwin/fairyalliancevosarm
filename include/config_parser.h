#ifndef CONFIG_PARSER_H_
#define CONFIG_PARSER_H_

#include <string>
#include <map>
#include <filesystem>

namespace fs = std::filesystem;

class ConfigParser {
public:
    explicit ConfigParser(const std::string& config_path);
    std::string get_value(const std::string& section, const std::string& key, const std::string& default_val = "");
    std::string get_app_value(const std::string& key, const std::string& default_val = "");

private:
    void load_file(const std::string& config_path);
    std::map<std::string, std::map<std::string, std::string>> _config_data;
    std::string _cyber_php_path;
};

#endif // CONFIG_PARSER_H_
