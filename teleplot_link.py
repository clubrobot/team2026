import pySerial

is_platformio=False

try:
    Import("Env")
    is_platformio=True
except NameError:
    print("Script lancé sans platformio")
    port = input("Port du robot: ")
    baud = input("Baud de communication")

