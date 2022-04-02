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

global option
driver = ""
elements_list = []

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

def init_selenium(param):
    options = Options()
    if not param == "":
        paramlist = param.split(" ");
    else:
        print("init_selenium --NO ARGS")
    if "headless" in paramlist:
        options.add_argument("--headless")
        print("init_selenium --HEADLESS")

    global driver;
    driver = webdriver.Chrome(options=options)


def get_search(PATH):
    global driver;
    if not PATH == "":
        driver.get(PATH)
    else:
        print("get_search --NO PATH SPECIFIED")


def wait_elem_XPATH(ELEMDATA , TIME):
    global driver;
    try:
        element1 = WebDriverWait(driver, int(TIME)).until(
            EC.presence_of_element_located((By.XPATH, ELEMDATA)))
    except:
        print("wait_elem_XPATH --INVALID ARGS")

def get_elem_XPATH(ELEMDATA):
    global driver;
    element3 = driver.find_element_by_xpath(ELEMDATA)
    global elements_list;
    elements_list.append(element3);


def get_elem_NAME(ELEMDATA):
    global driver;
    element3 = driver.find_element_by_name(ELEMDATA)
    #global elements_list;
    elements_list.append(element3);

def click_ELEMENT(ELEMNUMBER):
    global elements_list;
    elements_list[int(ELEMNUMBER)].click()

def type_ELEMENT(ELEMNUMBER , TEXT):
    global elements_list;
    if(TEXT == "u/ENTER"):
        TEXT = key_list.get('ENTER');
    elements_list[int(ELEMNUMBER)].send_keys(TEXT)

def driver_QUIT():
    global driver;
    driver.quit()


def driver_WAIT(sec):
    driver.implicitly_wait(int(sec)) # seconds




