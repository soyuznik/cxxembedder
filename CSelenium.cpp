#include "CSelenium.h"



void element::click() {
    std::vector<string>* vec = new std::vector<string>;
    vec->push_back(std::to_string(this->__objectnr));
    __callpy_warg("cclick", vec);
    delete vec;

}

driver::driver(){}

void driver::get(std::string __path) {
    std::vector<string>* vec = new std::vector<string>;
    vec->push_back(__path);
    __callpy_warg("cget", vec);
    delete vec;
}
element* driver::find_element_by_id(std::string name) {
    std::vector<string>* vec = new std::vector<string>;
    vec->push_back(name);
    __callpy_warg("cfind_element_by_id", vec);
    delete vec;
    element* Elem = new element();
    Elem->__objectnr = this->py_elementsC;
    Elem->data = name;
    this->py_elementsC++;
    return Elem;
}
element* driver::find_element_by_name(std::string name) {
    std::vector<string>* vec = new std::vector<string>;
    vec->push_back(name);
    __callpy_warg("cfind_element_by_name", vec);
    delete vec;
    element* Elem = new element();
    Elem->__objectnr = this->py_elementsC;
    Elem->data = name;
    this->py_elementsC++;
    return Elem;
}
element* driver::find_element_by_xpath(std::string name) {
    std::vector<string>* vec = new std::vector<string>;
    vec->push_back(name);
    __callpy_warg("cfind_element_by_xpath", vec);
    delete vec;
    element* Elem = new element();
    Elem->__objectnr = this->py_elementsC;
    Elem->data = name;
    this->py_elementsC++;
    return Elem;
}
element* driver::find_element_by_link_text(std::string name) {
    std::vector<string>* vec = new std::vector<string>;
    vec->push_back(name);
    __callpy_warg("cfind_element_by_link_text", vec);
    delete vec;
    element* Elem = new element();
    Elem->__objectnr = this->py_elementsC;
    Elem->data = name;
    this->py_elementsC++;
    return Elem;
}
element* driver::find_element_by_partial_link_text(std::string name) {
    std::vector<string>* vec = new std::vector<string>;
    vec->push_back(name);
    __callpy_warg("cfind_element_by_partial_link_text", vec);
    delete vec;
    element* Elem = new element();
    Elem->__objectnr = this->py_elementsC;
    Elem->data = name;
    this->py_elementsC++;
    return Elem;
}
element* driver::find_element_by_tag_name(std::string name) {
    std::vector<string>* vec = new std::vector<string>;
    vec->push_back(name);
    __callpy_warg("cfind_element_by_tag_name", vec);
    delete vec;
    element* Elem = new element();
    Elem->__objectnr = this->py_elementsC;
    Elem->data = name;
    this->py_elementsC++;
    return Elem;
}
element* driver::find_element_by_class_name(std::string name) {
    std::vector<string>* vec = new std::vector<string>;
    vec->push_back(name);
    __callpy_warg("cfind_element_by_class_name", vec);
    delete vec;
    element* Elem = new element();
    Elem->__objectnr = this->py_elementsC;
    Elem->data = name;
    this->py_elementsC++;
    return Elem;
}
element* driver::find_element_by_css_selector(std::string name) {
    std::vector<string>* vec = new std::vector<string>;
    vec->push_back(name);
    __callpy_warg("cfind_element_by_css_selector", vec);
    delete vec;
    element* Elem = new element();
    Elem->__objectnr = this->py_elementsC;
    Elem->data = name;
    this->py_elementsC++;
    return Elem;
}


std::vector<element*> driver::find_elements_by_id(std::string name) {
    int before_elem = stoi(__callpy_getarg("GET__elements"));
    std::vector<string>* vec = new std::vector<string>;
    vec->push_back(name);
    __callpy_warg("cfind_elements_by_id", vec);
    delete vec;
    std::vector<element*> ELEMENTS;
    int after_elem = stoi(__callpy_getarg("GET__elements"));
    for (before_elem; before_elem < after_elem; before_elem++) {
        element* Elem = new element();
        Elem->__objectnr = this->py_elementsC;
        Elem->data = name;
        this->py_elementsC++;
        ELEMENTS.push_back(Elem);
    }
    return ELEMENTS;
}
std::vector<element*> driver::find_elements_by_name(std::string name) {
    int before_elem = stoi(__callpy_getarg("GET__elements"));
    std::vector<string>* vec = new std::vector<string>;
    vec->push_back(name);
    __callpy_warg("cfind_elements_by_name", vec);
    delete vec;
    std::vector<element*> ELEMENTS;
    int after_elem = stoi(__callpy_getarg("GET__elements"));
    for (before_elem; before_elem < after_elem; before_elem++) {
        element* Elem = new element();
        Elem->__objectnr = this->py_elementsC;
        Elem->data = name;
        this->py_elementsC++;
        ELEMENTS.push_back(Elem);
    }
    return ELEMENTS;
}
std::vector<element*> driver::find_elements_by_xpath(std::string name) {
    int before_elem = stoi(__callpy_getarg("GET__elements"));
    std::vector<string>* vec = new std::vector<string>;
    vec->push_back(name);
    __callpy_warg("cfind_elements_by_xpath", vec);
    delete vec;
    std::vector<element*> ELEMENTS;
    int after_elem = stoi(__callpy_getarg("GET__elements"));
    for (before_elem; before_elem < after_elem; before_elem++) {
        element* Elem = new element();
        Elem->__objectnr = this->py_elementsC;
        Elem->data = name;
        this->py_elementsC++;
        ELEMENTS.push_back(Elem);
    }
    return ELEMENTS;
}
std::vector<element*> driver::find_elements_by_link_text(std::string name) {
    int before_elem = stoi(__callpy_getarg("GET__elements"));
    std::vector<string>* vec = new std::vector<string>;
    vec->push_back(name);
    __callpy_warg("cfind_elements_by_link_text", vec);
    delete vec;
    std::vector<element*> ELEMENTS;
    int after_elem = stoi(__callpy_getarg("GET__elements"));
    for (before_elem; before_elem < after_elem; before_elem++) {
        element* Elem = new element();
        Elem->__objectnr = this->py_elementsC;
        Elem->data = name;
        this->py_elementsC++;
        ELEMENTS.push_back(Elem);
    }
    return ELEMENTS;
}
std::vector<element*> driver::find_elements_by_partial_link_text(std::string name) {
    int before_elem = stoi(__callpy_getarg("GET__elements"));
    std::vector<string>* vec = new std::vector<string>;
    vec->push_back(name);
    __callpy_warg("cfind_elements_by_partial_link_text", vec);
    delete vec;
    std::vector<element*> ELEMENTS;
    int after_elem = stoi(__callpy_getarg("GET__elements"));
    for (before_elem; before_elem < after_elem; before_elem++) {
        element* Elem = new element();
        Elem->__objectnr = this->py_elementsC;
        Elem->data = name;
        this->py_elementsC++;
        ELEMENTS.push_back(Elem);
    }
    return ELEMENTS;
}
std::vector<element*> driver::find_elements_by_tag_name(std::string name) {
    int before_elem = stoi(__callpy_getarg("GET__elements"));
    std::vector<string>* vec = new std::vector<string>;
    vec->push_back(name);
    __callpy_warg("cfind_elements_by_tag_name", vec);
    delete vec;
    std::vector<element*> ELEMENTS;
    int after_elem = stoi(__callpy_getarg("GET__elements"));
    for (before_elem; before_elem < after_elem; before_elem++) {
        element* Elem = new element();
        Elem->__objectnr = this->py_elementsC;
        Elem->data = name;
        this->py_elementsC++;
        ELEMENTS.push_back(Elem);
    }
    return ELEMENTS;
}
std::vector<element*> driver::find_elements_by_class_name(std::string name) {
    int before_elem = stoi(__callpy_getarg("GET__elements"));
    std::vector<string>* vec = new std::vector<string>;
    vec->push_back(name);
    __callpy_warg("cfind_elements_by_class_name", vec);
    delete vec;
    std::vector<element*> ELEMENTS;
    int after_elem = stoi(__callpy_getarg("GET__elements"));
    for (before_elem; before_elem < after_elem; before_elem++) {
        element* Elem = new element();
        Elem->__objectnr = this->py_elementsC;
        Elem->data = name;
        this->py_elementsC++;
        ELEMENTS.push_back(Elem);
    }
    return ELEMENTS;
}
std::vector<element*> driver::find_elements_by_css_selector(std::string name) {
    int before_elem = stoi(__callpy_getarg("GET__elements"));
    std::vector<string>* vec = new std::vector<string>;
    vec->push_back(name);
    __callpy_warg("cfind_elements_by_css_selector", vec);
    delete vec;
    std::vector<element*> ELEMENTS;
    int after_elem = stoi(__callpy_getarg("GET__elements"));
    for (before_elem; before_elem < after_elem; before_elem++) {
        element* Elem = new element();
        Elem->__objectnr = this->py_elementsC;
        Elem->data = name;
        this->py_elementsC++;
        ELEMENTS.push_back(Elem);
    }
    return ELEMENTS;
}


driver* webdriver::Firefox() {
    __callpy_noarg("cFirefox");
    driver* browser = new driver();
    browser->browser_name = "Firefox";
    return browser;
}
driver* webdriver::Chrome() {
    __callpy_noarg("cChrome");
    driver* browser = new driver();
    browser->browser_name = "Chrome";
    return browser;
}
driver* webdriver::Proxy() {
    __callpy_noarg("cProxy");
    driver* browser = new driver();
    browser->browser_name = "Proxy";
    return browser;
}
driver* webdriver::Ie() {
    __callpy_noarg("cIe");
    driver* browser = new driver();
    browser->browser_name = "Ie";
    return browser;
}
driver* webdriver::Opera() {
    __callpy_noarg("cOpera");
    driver* browser = new driver();
    browser->browser_name = "Opera";
    return browser;
}
driver* webdriver::Remote() {
    __callpy_noarg("cRemote");
    driver* browser = new driver();
    browser->browser_name = "Remote";
    return browser;
}
driver* webdriver::PhantomJS() {
    __callpy_noarg("cPhantomJS");
    driver* browser = new driver();
    browser->browser_name = "PhantomJS";
    return browser;
}