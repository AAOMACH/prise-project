import socket
import threading
import os
import time

host = "127.0.0.1"
port = 1337

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind((host,port))
print('Server ready')


filename, addr = s.recvfrom(1024)
filename = filename.decode('ascii')
print(filename)

##while True:
    
if os.path.isfile(filename):

    x = "EXIST"
    length = str(os.path.getsize(filename))
    
    s.sendto(x.encode('ascii'),(host,1338))
##    time.sleep(3)
    s.sendto(length.encode('ascii'),(host,1339))
##    time.sleep(3)
    print('sent')
    userResponse,addr = s.recvfrom(2048)
    userResponse = userResponse.decode('ascii')
##    time.sleep(3)
    print('3')

    if userResponse == "ok":
        with open(filename, 'rb') as f:
        ## rb == read binary
            bytesToSend = f.read(100)
            s.sendto(bytesToSend,(host,port))
            while bytesToSend != "":
                bytesToSend = f.read(100)
                s.sendto(bytesToSend,(host,port))

    else:
        print('Failed')

else:
    y = "ERR".encode("ascii")
    s.sendto(y,(host,port))

s.close()
