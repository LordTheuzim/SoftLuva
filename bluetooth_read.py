from bluetooth import *

port = 1
backlog = 1

socket = BluetoothSocket(RFCOMM)


client_sock , client_info = server_sock.accept()

print "Accepted connection from " , client info

nearby_devices = discover_devices()

