import serial
import time
import string
import RPi.GPIO as GPIO

device0 = '/dev/ttyACM0'
device1 = '/dev/ttyACM1'
device2 = '/dev/ttyACM2'
device3 = '/dev/ttyACM3'
device4 = '/dev/ttyACM4'
device5 = '/dev/ttyACM5'

baud = 9600

bumper = 15

while True:

    connect0 = True
    connect1 = True
    connect2 = True
    connect3 = True
    connect4 = True
    connect5 = True

    #print(connection)

    try:
        ser = serial.Serial(device0, baud)
        #print("Try 0")
    except serial.SerialException:
        connect0 = False

    try:
        ser = serial.Serial(device1, baud)
        #print("Try 1")
    except serial.SerialException:
        connect1 = False

    try:
        ser = serial.Serial(device2, baud)
        #print("Try 2")
    except serial.SerialException:
        connect2 = False

    try:
        ser = serial.Serial(device3, baud)
        #print("Try 3")
    except serial.SerialException:
        connect3 = False

    try:
        ser = serial.Serial(device4, baud)
        #print("Try 4")
    except serial.SerialException:
        connect4 = False

    try:
        ser = serial.Serial(device5, baud)
        #print("Try 5")
    except serial.SerialException:
        connect5 = False


    #print("connect 0: ",connect0)
    #print("connect 1: ",connect1)
    #print("connect 2: ",connect2)
    #print("connect 3: ",connect3)
    #print("connect 4: ",connect4)
    #print("connect 5: ",connect5)

    #print("Connection pending")    

    if connect0 or connect1 or connect2 or connect3 or connect4 or connect5:

        #print("Connection made")

        GPIO.setmode(GPIO.BCM)
        GPIO.setwarnings(False)

        GPIO.setup(bumper, GPIO.IN, GPIO.PUD_UP)

        if GPIO.input(bumper) == False:
            ser.write('b')
            print("you sent a b")

