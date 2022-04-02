#pragma once
#include <vector>
/* 

Select and
ActionChains and
Exceptions and
Desired Capabilities and
Touch Actions and
Proxy and
Service and
Application Cache
not implemented




*/
#include <conio.h>
#include <iostream>
#include <string>
#include <filesystem>
#include <python/pyhelper.hpp>

class expected_condition;
class WebDriverWait;
struct By;
struct Keys;
class Alert;
class element;
class driver;
class webdriver;




class expected_condition {
	expected_condition();
	std::string flag;
	std::string name;
	bool presence_of_element_located(std::string _flag, std::string _name);
	bool title_is(std::string _flag, std::string _name);
	bool title_contains(std::string _flag, std::string _name);
	bool visibility_of_element_located(std::string _flag, std::string _name);
	bool visibility_of(std::string _flag, std::string _name);
	bool presence_of_all_elements_located(std::string _flag, std::string _name);
	bool text_to_be_present_in_element(std::string _flag, std::string _name);
	bool text_to_be_present_in_element_value(std::string _flag, std::string _name);
	bool frame_to_be_available_and_switch_to_it(std::string _flag, std::string _name);
	bool invisibility_of_element_located(std::string _flag, std::string _name);
	bool element_to_be_clickable(std::string _flag, std::string _name);
	bool staleness_of(std::string _flag, std::string _name);
	bool element_to_be_selected(std::string _flag, std::string _name);
	bool element_located_to_be_selected(std::string _flag, std::string _name);
	bool element_selection_state_to_be(std::string _flag, std::string _name);
	bool element_located_selection_state_to_be(std::string _flag, std::string _name);
	bool alert_is_present(std::string _flag, std::string _name);
};
class WebDriverWait {
	bool stop_waiting = false;
	WebDriverWait(driver driver, double time);
	element until(bool should_wait);
};
struct By {
	
	std::string ID = "id";
	std::string XPATH = "xpath";
	std::string LINK_TEXT = "link text";
	std::string PARTIAL_LINK_TEXT = "partial link text";
	std::string NAME = "name";
	std::string TAG_NAME = "tag name";
	std::string CLASS_NAME = "class name";
	std::string CSS_SELECTOR = "css selector";

};
//NULL is removed
struct Keys {
	std::string ADD = std::string("u/ADD");
	std::string 	ALT = std::string("u/ALT");
	std::string 	ARROW_DOWN = std::string("u/ARROW_DOWN");
	std::string 	ARROW_LEFT = std::string("u/ARROW_LEFT");
	std::string 	ARROW_RIGHT = std::string("u/ARROW_RIGHT");
	std::string 	ARROW_UP = std::string("u/ARROW_UP");
	std::string 	BACKSPACE = std::string("u/BACKSPACE");
	std::string 	BACK_SPACE = std::string("u/BACK_SPACE");
	std::string 	CANCEL = std::string("u/CANCEL");
	std::string CLEAR = std::string("u/CLEAR");
	std::string COMMAND = std::string("u/COMMAND");
	std::string CONTROL = std::string("u/CONTROL");
	std::string DECIMAL = std::string("u/DECIMAL");
	std::string DELETE = std::string("u/DELETE");
	std::string DIVIDE = std::string("u/DIVIDE");
	std::string DOWN = std::string("u/DOWN");
	std::string END = std::string("u/END");
	std::string ENTER = std::string("u/ENTER");
	std::string EQUALS = std::string("u/EQUALS");
	std::string ESCAPE = std::string("u/ESCAPE");
	std::string F1 = std::string("u/F1");
	std::string F2 = std::string("u/F2");
	std::string 	F3 = std::string("u/F3");
	std::string 	F4 = std::string("u/F4");
	std::string 	F5 = std::string("u/F5");
	std::string 	F6 = std::string("u/F6");
	std::string 	F7 = std::string("u/F7");
	std::string 	F8 = std::string("u/F8");
	std::string 	F9 = std::string("u/F9");
	std::string 	F10 = std::string("u/F10");
	std::string 	F11 = std::string("u/F11");
	std::string 	F12 = std::string("u/F12");
	std::string 	HELP = std::string("u/HELP");
	std::string 	HOME = std::string("u/HOME");
	std::string 	INSERT = std::string("u/INSERT");
	std::string 	LEFT = std::string("u/LEFT");
	std::string 	LEFT_ALT = std::string("u/LEFT_ALT");
	std::string 	LEFT_CONTROL = std::string("u/LEFT_CONTROL");
	std::string 	LEFT_SHIFT = std::string("u/LEFT_SHIFT");
	std::string 	META = std::string("u/META");
	std::string 	MULTIPLY = std::string("u/MULTIPLY");
	std::string 	NUMPAD1 = std::string("u/NUMPAD1");
	std::string 	NUMPAD2 = std::string("u/NUMPAD2");
	std::string 	NUMPAD3 = std::string("u/NUMPAD3");
	std::string 	NUMPAD4 = std::string("u/NUMPAD4");
	std::string 	NUMPAD5 = std::string("u/NUMPAD5");
	std::string 	NUMPAD6 = std::string("u/NUMPAD6");
	std::string 	NUMPAD7 = std::string("u/NUMPAD7");
	std::string 	NUMPAD8 = std::string("u/NUMPAD8");
	std::string 	NUMPAD9 = std::string("u/NUMPAD9");
	std::string 	NUMPAD0 = std::string("u/NUMPAD0");
	std::string 	PAGE_DOWN = std::string("u/PAGE_DOWN");
	std::string 	PAGE_UP = std::string("u/PAGE_UP");
	std::string 	PAUSE = std::string("u/PAUSE");
	std::string 	RETURN = std::string("u/RETURN");
	std::string 	RIGHT = std::string("u/RIGHT");
	std::string 	SEMICOLON = std::string("u/SEMICOLON");
	std::string 	SEPARATOR = std::string("u/SEPARATOR");
	std::string 	SHIFT = std::string("u/SHIFT");
	std::string 	SPACE = std::string("u/SPACE");
	std::string 	SUBTRACT = std::string("u/SUBTRACT");
	std::string 	TAB = std::string("u/TAB");
	std::string 	UP = std::string("u/UP");
	std::string 	ZENKAKU_HANKAKU = std::string("u/ZENKAKU_HANKAKU");
};
class Alert {
public:
	std::string text;
	Alert(driver driver);
	void accept();
	void dismiss();
	void send_keys(std::string keys);
};
struct switch_to {
	Alert alert;
};
struct cookie {
	std::string name;
	std::string value;
};
class driver {
	std::string browser_name;
	int py_elementsC = 0;
	friend class webdriver;
	friend class element;
public:
	driver();
	//switch_to switch_to;
	std::string current_url;
	std::string title;
	std::string path;
	std::vector<std::string> elements;
	//@param path the driver should get
	void get(std::string __path);
	element* find_element_by_id(std::string name);
	element* find_element_by_name(std::string name);
	element* find_element_by_xpath(std::string name);
	element* find_element_by_link_text(std::string name);
	element* find_element_by_partial_link_text(std::string name);
	element* find_element_by_tag_name(std::string name);
	element* find_element_by_class_name(std::string name);
	element* find_element_by_css_selector(std::string name);

	std::vector<element*> find_elements_by_id(std::string name);
	std::vector<element*> find_elements_by_name(std::string name);
	std::vector<element*> find_elements_by_xpath(std::string name);
	std::vector<element*> find_elements_by_link_text(std::string name);
	std::vector<element*> find_elements_by_partial_link_text(std::string name);
	std::vector<element*> find_elements_by_tag_name(std::string name);
	std::vector<element*> find_elements_by_class_name(std::string name);
	std::vector<element*> find_elements_by_css_selector(std::string name);
	
	element find_element(std::string flag, std::string name);
	std::vector<element> find_elements(std::string flag, std::string name);


	void add_cookie(cookie cookie);
	std::vector<cookie> get_cookies();

	void implicitly_wait(double time);
	void forward();
	void back();
	void switch_to_window(std::string windowName);
	void switch_to_frame(std::string frameName);
	void switch_to_default_content();
	void close();
	void quit();


	
};
class element : public driver {
	int __objectnr;
	std::string data;
	friend class driver;
public:
	element();
	void clear();
	void send_keys(std::string keys);
	void click();
	void submit();

};
class webdriver : public driver {
public:
	webdriver() { __initialize_path("pyemb3"); }
	//@return the driver
	driver* Firefox();
	driver* Chrome();
	driver* Ie();
	driver* Opera();
	driver* PhantomJS();
	driver* Remote();
	driver* Proxy();
	


};

