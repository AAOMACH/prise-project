import socket

##mysock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
##mysock.bind(('127.0.0.1',1337))
##clientdata, addr = mysock.recvfrom(2048)
##print(clientdata)

import threading
import os

def Retrfile(name,sock):
    ## Function to send the file to client
##    filename = sock.recvfrom(1024)
    print(filename)
    if os.path.isfile(filename):

        x = "EXIST"
        length = str(os.path.getsize(filename))
        
        sock.sendto(x.encode('ascii'))
        sock.sendto(length.encode('ascii'))
        userResponse = sock.recvfrom(1024).decode('ascii')

        if userResponse[:2] == "ok":
            with open(filename, 'rb') as f:
            ## rb == read binary
                bytesToSend = f.read(100)
                sock.sendto(bytesToSend)
                while bytesToSend != "":
                    bytesToSend = f.read(100)
                    sock.sendto(bytesToSend)

    else:
        y = "ERR".encode("ascii")
        sock.sendto(y)
        print("a")

    sock.close()

def Main():
    host = "192.168.43.132"
    port = 1337
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.bind((host,port))
##    s.listen(5)

    print("Server ready")
    
##    clientdata, addr = s.recvfrom(2048)
##    filename = s.recvfrom(1024)
##    print(filename)
    while True:
##        c,addr = s.accept()
        print("Client connected")
        data = s.recvfrom(1024)
        print(data)
        
        #t = threading.Thread(target=Retrfile,args=('retrThread',clientdata))
        #t.start()

    s.close()

if __name__ == "__main__" :

    Main()
