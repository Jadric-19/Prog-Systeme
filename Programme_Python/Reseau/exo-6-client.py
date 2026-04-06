import socket
import threading

def recevoir(s):
    while True:
        try:
            print(s.recv(1024).decode(), end="")
        except:
            break

def main():
    s = socket.socket()
    s.connect(("127.0.0.1", 5000))

    threading.Thread(target=recevoir, args=(s,), daemon=True).start()

    while True:
        msg = input()
        s.send(msg.encode())

main()