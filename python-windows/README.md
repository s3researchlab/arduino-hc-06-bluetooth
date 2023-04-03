
## Install all dependencies

```bash
pip install -r requirements.txt
```


## Install

I had to install Pybluez from source on Windows 10. Below are the steps:

Download Microsoft C++ Build Tools (https://visualstudio.microsoft.com/visual-cpp-build-tools/)
Open downloaded vs_BuildTools installer and install Visual Studio Build Tools 2022
Download pybluez source files as a zipped file (https://github.com/pybluez/pybluez) (commit[4d46ce1])
Unzip the downloaded zipped file (pybluez-master)
Open powershell and cd into the folder
python3 setup.py install --user
