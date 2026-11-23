import sys
import os

# Caminho do MSYS2 (onde o pandas está instalado)
caminho_msys2 = "C:/msys64/ucrt64/lib/python3.10/site-packages"

# Se a pasta existir e ainda não estiver no path, adiciona.
if os.path.exists(caminho_msys2) and caminho_msys2 not in sys.path:
    sys.path.append(caminho_msys2)