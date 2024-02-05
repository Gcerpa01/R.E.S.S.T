import time
import serial 
import sys
from serial.tools import list_ports
import serialReadConstants as SC
import threading
import matplotlib.pyplot as plt 




def select_serial_port():
    available_ports = [port.device for port in list_ports.comports()]

    print("\n")
    if not available_ports:
        print("No serial ports found. Please check your connection")
        sys.exit()
    
    print("The following serial ports are available")
    for i,port in enumerate(available_ports, start = 1):
        print("{}) {}".format(i,port))

    selectedPort = input("Choose the number of the serial port you want to use: ")
    
    try:
        selectedPort = int(selectedPort) - 1
        if 0 <= selectedPort < len(available_ports):
            return available_ports[selectedPort]
        else:
            print("Invalid selection.")
            sys.exit()
    except ValueError:
        print("Invalid input.")
        sys.exit()

def select_mode():
    print("\nWhat kind of communication line would you like with the serial port?")
    for i in SC.serialOptions:
        print(i)
    selectedMode = input("Choose the mode you want to use: ")

    try:
        selectedMode = int(selectedMode) - 1
        if 0 <= selectedMode < len(SC.serialOptions):
            return selectedMode
        else:
            print("Invalid selection")
            sys.exit()
    except ValueError:
        print("Invalid input.")
        sys.exit()

def select_read_mode():
    print("\nHow would you like the data to be read?")
    print("Please note that Graphing is currently unavailable while doing READ AND WRITE mode\n")
    for i,mode in enumerate(SC.serialReadOptions,start=1):
         print("{}) {}".format(i,mode))
    selectedMode = input("Choose the mode you want to use: ")

    try:
        selectedMode = int(selectedMode) - 1
        if 0 <= selectedMode < len(SC.serialOptions):
            return SC.serialReadOptions[selectedMode]
        else:
            print("Invalid selection")
            sys.exit()
    except ValueError:
        print("Invalid input.")
        sys.exit()

def select_baud_rate():
    print("\nWhat baud rate will you be using?")
    print("The most common baud rate used for arduinos is 9600")
    for i,baudRate in enumerate(SC.baudRate, start=1):
         print("{}) {}".format(i,baudRate))
    selectedBaudRate = input("Choose the baud rate you want to use: ")
    try:
        selectedBaudRate = int(selectedBaudRate) - 1
        if 0 <= selectedBaudRate < len(SC.baudRate):
            return SC.baudRate[selectedBaudRate]
        else:
            print("Invalid selection")
            sys.exit()
    except ValueError:
        print("Invalid selectoion.")
        sys.exit()

def appendWriteData():
    print("\nWhat would you like to append to the data being sent?")
    for i,appendment in enumerate(SC.serialWriteOptions,start=1):
        print("{}) {}".format(i,appendment))
    selectedAppendment = input("Choose which to append: ")
    try:
        selectedAppendment = int(selectedAppendment) - 1
        if 0 <= selectedAppendment < len(SC.serialWriteOptions):
            return SC.serialWriteOptions[selectedAppendment]
        else:
            print("Invalid selection")
            sys.exit()
    except ValueError:
        print("Invalid selectoion.")
        sys.exit()

def printReadData(serialCOM,readMode):
    while True:
        while serialCOM.inWaiting() == 0:
            pass
        serialData = serialCOM.readline().decode('utf-8').strip()
        if readMode == SC.printRead:
            print("\nRx: ",serialData)
        elif readMode == SC.graphRead:
            SC.dataValues.append(float(serialData))
            if len(SC.dataValues) > SC.samples:
                SC.dataValues.pop(0)

def writeData(serialCOM,appendment):
    while True:
        dataSend = input("\nEnter data to send: ") + appendment
        serialCOM.write(dataSend.encode('utf-8'))

def plot_data():
    plt.ion()
    fig, ax = plt.subplots()
    while True:
        ax.clear()
        ax.set_xlabel("Sample Index")
        ax.set_ylabel("Data Value")
        ax.set_xlim(0, SC.xlimit)
        ax.set_ylim(0, SC.ylimit)
        ax.plot(SC.dataValues)
        plt.draw()
        plt.pause(SC.pltPause)


if __name__=="__main__":

    serialPort= select_serial_port()
    serialMode = select_mode()
    
    if serialMode in SC.readIndexes:
        readMode = select_read_mode()   
    
    if serialMode in SC.writeIndexes:
        writeMode = appendWriteData()
    
    baudRate = select_baud_rate()
    
    try:
        microController = serial.Serial(serialPort,baudRate,timeout=SC.counter)
        time.sleep(SC.counter)
        print("\nConnected to port: {} with baud rate: {}".format(serialPort,baudRate))
        if serialMode in SC.readIndexes:
            read_thread = threading.Thread(target=printReadData, args=(microController,readMode))
            read_thread.start()

        if serialMode in SC.writeIndexes:
            write_thread = threading.Thread(target=writeData, args=(microController, writeMode))
            write_thread.start()
        
        if readMode == SC.graphRead:
            plot_data()
    
    except KeyboardInterrupt:
        microController.close()
        print("Serial communication was closed")
    except serial.SerialException as e:
        print("Error: {}".format(e))
    finally:
        if serialMode in SC.readIndexes:
            read_thread.join()
            if readMode == SC.graphRead:
                plot_thread.join()
        if serialMode in SC.writeIndexes:
            write_thread.join()
        print("Program is now closing")
