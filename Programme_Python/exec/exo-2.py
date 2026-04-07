import os
import sys

if len(sys.argv) != 2:
    print("Usage: python3 prog.py <repertoire_destination>")
    sys.exit(1)

R = sys.argv[1]

# Copier le repertoire courant vers R
os.execvp("cp", ["cp", "-r", ".", R])