#include "cyber_v8_handler.h"
#include "cef/cef.h"
#include <iostream>

std::string ReadIDCard() {
    return "{\"name\":\"张三\",\"id\":\"110101199001011234\",\"address\":\"北京市朝阳区\"}";
}

bool CyberV8Handler::Execute(const CefString& name,
                             CefRefPtr<CefV8Value> object,
                             const CefV8ValueList& arguments,
                             CefRefPtr<CefV8Value>& retval,
                             CefString& exception) {
    if (name == "ReadIDCard") {
        std::string card_info = ReadIDCard();
        retval = CefV8Value::CreateString(card_info);
        return true;
    }

    if (name == "PrintBill") {
        if (arguments.size() < 1 || !arguments[0]->IsString()) {
            exception = "参数错误：需要传入账单字符串";
            return false;
        }
        std::string bill = arguments[0]->GetStringValue();
        std::cout << "打印账单：" << bill << std::endl;
        retval = CefV8Value::CreateBool(true);
        return true;
    }

    exception = "未知方法：" + name.ToString();
    return false;
}

void CyberRenderHandler::OnContextCreated(CefRefPtr<CefBrowser> browser,
                                          CefRefPtr<CefFrame> frame,
                                          CefRefPtr<CefV8Context> context) {
    CefRefPtr<CefV8Value> window = context->GetGlobal();
    CefRefPtr<CefV8Value> hw_obj = CefV8Value::CreateObject(nullptr, nullptr);
    CefRefPtr<CyberV8Handler> handler = new CyberV8Handler();

    CefRefPtr<CefV8Value> read_id_func = CefV8Value::CreateFunction("ReadIDCard", handler);
    hw_obj->SetValue("ReadIDCard", read_id_func, V8_PROPERTY_ATTRIBUTE_NONE);

    CefRefPtr<CefV8Value> print_func = CefV8Value::CreateFunction("PrintBill", handler);
    hw_obj->SetValue("PrintBill", print_func, V8_PROPERTY_ATTRIBUTE_NONE);

    window->SetValue("CyberHardware", hw_obj, V8_PROPERTY_ATTRIBUTE_NONE);
}
