import os

TAILLE = 100

def fils(tube_r):
    os.close(tube_w)  
    buffer = os.read(tube_r, TAILLE)
    os.close(tube_r)
    print(f"Message recu : {buffer.decode()}")

# parent
tube_r, tube_w = os.pipe()
pid = os.fork()

if pid == 0:
    fils(tube_r)
    os._exit(0)
else:
    os.close(tube_r)
    message = "Bonjour au fils !"
    os.write(tube_w, message.encode())
    os.close(tube_w)
    os.wait()