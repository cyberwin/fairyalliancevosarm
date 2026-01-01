#include "cyber_browser.h"
#include <iostream>

int main() {
    try {
        CyberBrowser browser;
        browser.run();
    } catch (const std::exception& e) {
        fprintf(stderr, "浏览器启动失败：%s\n", e.what());
        return 1;
    }
    return 0;
}
