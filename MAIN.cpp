

#define PY_SSIZE_T_CLEAN
#include <python/pyhelper.hpp>



int main()
{
    CPyInstance inst;
    __initialize_path("/PythonSrc/");
    PyRun_SimpleString(
        "from selenium.webdriver.chrome.options import Options\n"
        "from selenium import webdriver\n"
        "from selenium.webdriver.common.by import By\n"
        "from selenium.webdriver.support.ui import WebDriverWait\n"
        "from selenium.webdriver.support import expected_conditions as EC\n"
        "import time\n"
        "import threading\n"
        "import chromedriver_autoinstaller\n"
        "chromedriver_autoinstaller.install()\n");

    PyRun_SimpleString("driver = webdriver.Chrome()\n");
    PyRun_SimpleString("driver.get(\"https://www.google.com/\")\n");

}