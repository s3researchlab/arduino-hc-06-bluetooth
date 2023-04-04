import re

from src.BluetoothConnection import BluetoothConnection

conn = BluetoothConnection()

def onConnected(msg):
    print("Connected")

def onMsgReceived(data):
    
    m = re.search('p(\d+)', data)
    
    potValue = int(m.group(1))
    
    if potValue in range(0, 40):
        conn.send("l0")
    elif potValue in range(40, 80):
        conn.send("l1")
    elif potValue in range(80, 120):
        conn.send("l2")
    elif potValue in range(120, 160):
        conn.send("l3")
    elif potValue in range(160, 200):
        conn.send("l4")
    elif potValue in range(200, 256):
        conn.send("l5")

conn.on("received", onMsgReceived)
conn.on("connected", onConnected)

conn.listen()

