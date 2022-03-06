from selenium.webdriver.chrome.options import Options
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
import time
import threading

def exec_thread():
    options = Options()
    options.add_argument("--headless")
    PATH = r"D:\Users\user\PycharmProjects\pythonProject\chromedriver.exe"
    driver = webdriver.Chrome(PATH, options=options)

    searchpath = "https://form.dragnsurvey.com/survey/r/28a7e321"
    driver.get(searchpath);
    #589 gangura
    gangura = r'//*[@id="dnsSurvey"]/div/div[2]/div[3]/div/form[1]/div[2]/div[2]/div[10]'
    #598 ulmnu
    ulmu = r'//*[@id="dnsSurvey"]/div/div[2]/div[3]/div/form[2]/div[2]/div[2]/div[1]'
    #button "VOTEAZA"
    butt = r'//*[@id="dnsSurvey"]/div/div[2]/div[3]/div/div/div/button'

########################################################################
    element1 = WebDriverWait(driver, 1000000).until(
        EC.presence_of_element_located((By.XPATH, gangura)))

    time.sleep(2);
    element1 = driver.find_element_by_xpath(gangura)
    element1.click()
    time.sleep(2)
#####################################################################
    element2 = WebDriverWait(driver, 1000000).until(
        EC.presence_of_element_located((By.XPATH, ulmu)))
    time.sleep(2)
    element2 = driver.find_element_by_xpath(ulmu)
    element2.click()
    time.sleep(2)
#####################################################################
    element3 = WebDriverWait(driver, 1000000).until(
        EC.presence_of_element_located((By.XPATH, butt)))

    time.sleep(2);
    element3 = driver.find_element_by_xpath(butt)
    element3.click()
    time.sleep(2)

    driver.quit()

threads = [];

for i in range(1000):
    thread = threading.Thread(target=exec_thread);
    thread.daemon = True
    threads.append(thread);
for i in range(1000):
    threads[i].start()
    print("> started thread nr." + str(i) +"  --" + str(threads[i].native_id));
    time.sleep(2)

for i in range(1000):
    threads[i].join()

