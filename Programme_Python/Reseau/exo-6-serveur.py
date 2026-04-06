import socket, threading

clients = []
lock = threading.Lock()
parleur = None

def handle(c, a):
    global parleur
    clients.append(c)

    while True:
        try:
            m = c.recv(1024).decode().strip()
            if not m: break

            if m == "1":
                with lock:
                    if parleur is None:
                        parleur = c
                        c.send(b"OK\n")
                    else:
                        c.send(b"WAIT\n")
            else:
                if c == parleur:
                    msg = f"{a[0]}: {m}\n".encode()
                    print(msg.decode(), end="")

                    with lock:
                        for x in clients:
                            if x != c:
                                x.send(msg)
                        parleur = None
                else:
                    c.send(b"NO\n")
        except:
            break

    clients.remove(c)
    c.close()

s = socket.socket()
s.bind(("0.0.0.0", 5000))
s.listen()

while True:
    c, a = s.accept()
    threading.Thread(target=handle, args=(c, a)).start()