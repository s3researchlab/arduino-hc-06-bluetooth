import os.path

class FileUtils:
    
    @staticmethod
    def createFolderIfNotExist(path):
        
        if not os.path.isdir(path):
            os.mkdir(os.path.join(os.getcwd(), path))
    
    @staticmethod
    def write(filename:str, content:str):
        
        with open(filename, "w") as text_file:
            text_file.write(content)
       
    def load(filename):
        
        if not os.path.isfile(filename):
            return None
        
        with open(filename, encoding="utf-8") as file:
            return file.read()