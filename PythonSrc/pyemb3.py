# It imports the necessary modules to run the code.

from selenium.webdriver.chrome.options import Options
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time
import threading
import chromedriver_autoinstaller

chromedriver_autoinstaller.install()

option = ""
__elements = 0;
driver = ""
elements_list = []
objectnr_dict = {}
key_list = {
 'NULL' :  u'\ue000',
 'CANCEL:' : u'\ue001'  ,
 'HELP' :  u'\ue002',
 'BACKSPACE' : u'\ue003',
 'TAB' : u'\ue004',
 'CLEAR' : u'\ue005',
 'RETURN' : u'\ue006',
 'ENTER' : u'\ue007',
 'SHIFT' : u'\ue008',
 'CONTROL' : u'\ue009',
 'ALT' : u'\ue00a',
 'PAUSE' : u'\ue00b',
 'ESCAPE' : u'\ue00c',
 'SPACE' : u'\ue00d',
 'PAGE_UP' : u'\ue00e',
 'PAGE_DOWN' : u'\ue00f',
 'END' : u'\ue010',
 'HOME' : u'\ue011',
 'LEFT' : u'\ue012',
 'UP' : u'\ue013',
 'RIGHT' : u'\ue014',
 'DOWN' : u'\ue015',
 'INSERT' : u'\ue016',
 'DELETE' : u'\ue017',
 'SEMICOLON' : u'\ue018',
 'EQUALS' : u'\ue019',
 'NUMPAD0' : u'\ue01a'  ,
 'NUMPAD1' : u'\ue01b',
 'NUMPAD2' : u'\ue01c',
 'NUMPAD3' : u'\ue01d',
 'NUMPAD4' : u'\ue01e',
 'NUMPAD5' : u'\ue01f',
 'NUMPAD6' : u'\ue020',
 'NUMPAD7' : u'\ue021',
 'NUMPAD8' : u'\ue022',
 'NUMPAD9' : u'\ue023',
 'MULTIPLY' : u'\ue024',
 'ADD' : u'\ue025',
 'SEPARATOR' : u'\ue026',
 'SUBTRACT' : u'\ue027',
 'DECIMAL' : u'\ue028',
 'DIVIDE' : u'\ue029',
 'F1' : u'\ue031'  ,
 'F2' : u'\ue032',
 'F3' : u'\ue033',
 'F4' : u'\ue034',
 'F5' : u'\ue035',
 'F6' : u'\ue036',
 'F7' : u'\ue037',
 'F8' : u'\ue038',
 'F9' : u'\ue039',
 'F10' : u'\ue03a',
 'F11' : u'\ue03b',
 'F12' : u'\ue03c',
 'META' : u'\ue03d',
 'COMMAND' : u'\ue03d'
}

def GET__elements():
    return __elements;



def cclick(objectnr):
    elements_list(objectnr).click()


def cProxy():
    global driver;
    driver = webdriver.Proxy();
def cRemote():
    global driver;
    driver = webdriver.Remote();
def cPhantomJS():
    global driver;
    driver = webdriver.PhantomJS();
def cFirefox():
    global driver;
    driver = webdriver.Firefox();
def cChrome():
    global driver;
    driver = webdriver.Chrome();
def cIe():
    global driver;
    driver = webdriver.Ie();
def cOpera():
    global driver;
    driver = webdriver.Opera();


















# get webbrowser link
def cget(path):
    driver.get(path)




# single element appending
def cfind_element_by_id(name):
    global __elements;
    element = driver.find_element_by_id(name)
    elements_list.append(element);
    objectnr_dict[__elements] = name;
    __elements = + 1;
def cfind_element_by_name(name):
    global __elements;
    element = driver.find_element_by_name(name)
    elements_list.append(element);
    objectnr_dict[__elements] = name;
    __elements = + 1;
def cfind_element_by_xpath(name):
    global __elements;
    element = driver.find_element_by_xpath(name)
    elements_list.append(element);
    objectnr_dict[__elements] = name;
    __elements = + 1;
def cfind_element_by_link_text(name):
    global __elements;
    element = driver.find_element_by_link_text(name)
    elements_list.append(element);
    objectnr_dict[__elements] = name;
    __elements = + 1;
def cfind_element_by_partial_link_text(name):
    global __elements;
    element = driver.find_element_by_partial_link_text(name)
    elements_list.append(element);
    objectnr_dict[__elements] = name;
    __elements = + 1;
def cfind_element_by_tag_name(name):
    global __elements;
    element = driver.find_element_by_tag_name(name)
    elements_list.append(element);
    objectnr_dict[__elements] = name;
    __elements = + 1;
def cfind_element_by_class_name(name):
    global __elements;
    element = driver.find_element_by_class_name(name)
    elements_list.append(element);
    objectnr_dict[__elements] = name;
    __elements = + 1;
def cfind_element_by_css_selector(name):
    global __elements;
    element = driver.find_element_by_css_selector(name)
    elements_list.append(element);
    objectnr_dict[__elements] = name;
    __elements = + 1;


# multiple element appending
def cfind_elements_by_css_selector(name):
    global __elements;
    elements = driver.find_elements_by_css_selector(name)
    for element in elements:
        list.append(element);
        objectnr_dict[elements] = name;
        __elements =+ 1;


def cfind_elements_by_id(name):
    global __elements;
    elements = driver.find_element_by_id(name)
    for element in elements:
        list.append(element);
        objectnr_dict[elements] = name;
        __elements = + 1;
def cfind_elements_by_name(name):
    global __elements;
    elements = driver.find_element_by_name(name)
    for element in elements:
        list.append(element);
        objectnr_dict[elements] = name;
        __elements = + 1;
def cfind_elements_by_xpath(name):
    global __elements;
    elements = driver.find_element_by_xpath(name)
    for element in elements:
        list.append(element);
        objectnr_dict[elements] = name;
        __elements = + 1;
def cfind_elements_by_link_text(name):
    global __elements;
    elements = driver.find_element_by_link_text(name)
    for element in elements:
        list.append(element);
        objectnr_dict[elements] = name;
        __elements = + 1;
def cfind_elements_by_partial_link_text(name):
    global __elements;
    elements = driver.find_element_by_partial_link_text(name)
    for element in elements:
        list.append(element);
        objectnr_dict[elements] = name;
        __elements = + 1;
def cfind_elements_by_tag_name(name):
    global __elements;
    elements = driver.find_element_by_tag_name(name)
    for element in elements:
        list.append(element);
        objectnr_dict[elements] = name;
        __elements = + 1;
def cfind_elements_by_class_name(name):
    global __elements;
    elements = driver.find_element_by_class_name(name)
    for element in elements:
        list.append(element);
        objectnr_dict[elements] = name;
        __elements = + 1;
def cfind_elements_by_css_selector(name):
    global __elements;
    elements = driver.find_element_by_css_selector(name)
    for element in elements:
        list.append(element);
        objectnr_dict[elements] = name;
        __elements = + 1;






