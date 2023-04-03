import re
import bluetooth

from src.BluetoothConnection import BluetoothConnection

conn = BluetoothConnection()

def onConnected(msg):
    print("Connected")

def onMsgReceived(data):
    
    m = re.search('p(\d+)', data)
    
    potValue = int(m.group(1))
    
    if potValue == 0:
        conn.send("l0;")
    elif potValue in range(1, 40):
        conn.send("l1;")
    elif potValue in range(41, 80):
        conn.send("l2;")
    elif potValue in range(81, 120):
        conn.send("l3;")
    elif potValue in range(121, 160):
        conn.send("l4;")
    elif potValue in range(161, 200):
        conn.send("l5;")
    elif potValue in range(201, 256):
        conn.send("l6;")

conn.on("received", onMsgReceived)
conn.on("connected", onConnected)

conn.listen()

