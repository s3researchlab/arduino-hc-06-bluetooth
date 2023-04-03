import bluetooth
import sys
from tabulate import tabulate
from .Cache import Cache

class BluetoothConnection:
    
    def __init__(self):
        self.sock = None
        self.events = {}
        
    def on(self, eventName, callback = None):
        
        if self.events.get(eventName) == None:
            self.events.update({eventName: []})
            
        self.events.get(eventName).append(callback)
         
    def fire(self, eventName, text):
        
        callbacks = self.events.get(eventName)
        
        if callbacks == None:
            return
        
        for callback in callbacks:
            callback(text)
            
    def send(self, text):
        self.sock.send(text)
   
    def discoverDevices(self):
    
        print("Discovering devices...")
    
        nearby_devices = bluetooth.discover_devices(lookup_names=True)
        print("Found {} devices.".format(len(nearby_devices)))

        devices = {}
        
        index = 1
        
        for addr, name in nearby_devices:
            devices.update({index: {"addr": addr, "name": name}})
            index += 1
            
        return devices
    
    def selectDevice(self):
        
        cache = Cache.load("cache.json")
        
        if cache == None:
            
            devices = self.discoverDevices()
        
            table = []
            
            for key, value in devices.items():
                table.append([key, value.get("addr"), value.get("name")])
        
            print(tabulate(table, tablefmt="psql", headers=["Id","Address", "Name"]))
        
            index = input("Type the device's id (first column): ")

            device = devices.get(int(index))
            
            Cache.save("cache.json", device)
            
            return device

        else:
            return cache
    
    def listen(self):
        
        device = self.selectDevice()
        
        addr = device.get("addr")
        
        service_matches = bluetooth.find_service(address=addr)

        if len(service_matches) == 0:
            print("Couldn't find the SampleServer service.")
            sys.exit(0)
            
        first_match = service_matches[0]
        
        name = device.get("name")
        port = first_match["port"]
        host = first_match["host"]

        print("Connecting to \"{}\" on {}, Port {}".format(name, host, port))

        # Create the client socket OPTION 1
        self.sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
        self.sock.connect((host, port))
        
        self.fire("connected", "")
        
        try:
            while 1:
                data = self.sock.recv(1024)
                if data:
                    self.fire("received", data.decode())
        except:
            print("Closing socket")
            self.sock.close()
            raise  