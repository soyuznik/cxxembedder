
from selenium.webdriver.chrome.options import Options
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time
import threading

import chromedriver_autoinstaller
chromedriver_autoinstaller.install()

def exec_thread():
    options = Options()
    #options.add_argument("--headless")
    
    driver = webdriver.Chrome(options=options)

    searchpath = "https://google.com"
    driver.get(searchpath);
   
    time.sleep(9)

    driver.quit()

