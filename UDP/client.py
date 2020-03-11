import socket
##mysock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
##mysock.connect(("127.0.0.1",1337))
##x = 'hello from client'
##x = x.encode('ascii')
##mysock.sendto(x,('127.0.0.1',1337))

def Main():

    host = "127.0.0.1"
    port = 1337
    
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.connect((host,port))
    filename = input("Enter file name with its extension: ")
    
    if filename != "q":
        print(1)
        x = filename.encode('ascii')
        s.sendto(x,(host,port))
        print(2)
        data,addr = s.recvfrom(2048)
        length,addr = s.recvfrom(2048)
        
        data = data.decode('ascii')
        length = length.decode('ascii')
        print(3)

        if data == 'EXIST':
            ans = 'ok'
            s.sendto(ans.encode('ascii'),(host,1340))
            filesize = int(length)
            message = input("file exist."+str(filesize) + "download Y/N : ")
            
            if message == 'Y':
                w = "ok"
                s.sendto(w.encode("ascii"),(host,port))
                f = open('new_'+filename,'wb')
                data,addr = s.recvfrom(100)
                totalRecv = len(data)
                f.write(data)
                
                while totalRecv < filesize:
                    data = s.recvfrom(100)
                    totalRecv += len(data)
                    f.write(data)
                    print("0:.21".format((totalRecv/float(filesize))))

                print("download complete")

        else:
            print("File does not exist")

    s.close()

if __name__ == "__main__":
    Main()
