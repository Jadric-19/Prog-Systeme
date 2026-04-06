import socket
import threading

clients = []

def handle(c1, c2):
    try:
        while True:
            msg = c1.recv(1024)
            if not msg:
                break

            c2.send(b"L'autre client dit : " + msg)
            c2.send(b"\nSaisissez la reponse : ")

            msg = c2.recv(1024)
            if not msg:
                break

            c1.send(b"L'autre client dit : " + msg)
            c1.send(b"\nSaisissez la reponse : ")
    except:
        pass
    finally:
        c1.close()
        c2.close()

s = socket.socket()
s.bind(("0.0.0.0", 12345))
s.listen(5)

print("Serveur en attente...")

while True:
    c, addr = s.accept()
    print("Client connecte :", addr)
    clients.append(c)

    if len(clients) >= 2:
        c1 = clients.pop(0)
        c2 = clients.pop(0)
        threading.Thread(target=handle, args=(c1, c2)).start()