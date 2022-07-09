#include "python/pyhelper.hpp"



int main()
{
    START_PYTHON
    RUN_PYTHON(
    from selenium.webdriver.chrome.options import Options;
    from selenium import webdriver;
    from selenium.webdriver.common.by import By;
    from selenium.webdriver.support.ui import WebDriverWait;
    from selenium.webdriver.support import expected_conditions as EC;
    import time;
    import threading;
    import chromedriver_autoinstaller;
    chromedriver_autoinstaller.install();
    driver = webdriver.Chrome();
    driver.get("https://www.google.com/");
    );
}