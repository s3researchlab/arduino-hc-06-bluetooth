
import json 
import os.path

class Cache:
    
    @staticmethod
    def createFolderIfNotExist(path):
        
        if not os.path.isdir(path):
            os.mkdir(os.path.join(os.getcwd(), ".cache"))
    
    @staticmethod
    def save(filename:str, value:dict):
        
        Cache.createFolderIfNotExist(".cache")
       
        filename = os.path.join(os.getcwd(), ".cache", filename)
       
        with open(filename, "w") as text_file:
            text_file.write(json.dumps(value, indent = 4) )
       
    def load(filename):
        
        Cache.createFolderIfNotExist(".cache")
        
        filename = os.path.join(os.getcwd(), ".cache", filename)
        
        if not os.path.isfile(filename):
            return None
        
        with open(filename, encoding="utf-8") as file:
            read_data = file.read()
            return json.loads(read_data)