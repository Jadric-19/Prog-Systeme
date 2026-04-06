import os
import time
import random

debut = time.time()

pid1 = os.fork()

if pid1 == 0:
    random.seed(time.time() + os.getpid())
    temps = random.randint(1, 10)
    print(f"Fils 1 : je dors pendant {temps} secondes")
    time.sleep(temps)
    print("Fils 1 termine")
    os._exit(0)

pid2 = os.fork()

if pid2 == 0:
    random.seed(time.time())
    temps = random.randint(1, 10)
    print(f"Fils 2 : je dors pendant {temps} secondes")
    time.sleep(temps)
    print("Fils 2 termine")
    os._exit(0)

os.wait()
os.wait()

fin = time.time()

print(f"Duree totale : {int(fin - debut)} secondes")