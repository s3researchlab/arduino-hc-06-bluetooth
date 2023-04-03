
## Install all dependencies

```bash
pip install -r requirements.txt
```


## Install

You have to install Pybluez from the source on Windows 11. Below are the steps:

- Download Microsoft C++ Build Tools (https://visualstudio.microsoft.com/visual-cpp-build-tools/)
- Open downloaded `vs_BuildTools` installer and install Visual Studio Build Tools 2022
- Download `pybluez` source files as a zipped file (https://github.com/pybluez/pybluez) (commit[4d46ce1])
- Unzip the downloaded zipped file (pybluez-master)
- Open Powershell and `cd` into the folder

```bash
python setup.py install --user
```