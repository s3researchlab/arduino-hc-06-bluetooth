
import json 
import os.path
from .FileUtils import FileUtils

class CacheUtils:
    
    @staticmethod
    def init():
        FileUtils.createFolderIfNotExist(".cache")
    
    @staticmethod
    def save(filename:str, value:dict):
        
        filename = os.path.join(os.getcwd(), ".cache", filename)
       
        FileUtils.write(filename, json.dumps(value, indent = 4))
       
    def load(filename):
        
        filename = os.path.join(os.getcwd(), ".cache", filename)
        
        if not os.path.isfile(filename):
            return None
        
        return json.loads(FileUtils.load(filename))