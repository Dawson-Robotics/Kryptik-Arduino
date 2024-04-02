import serial
import os
import time
import pygetwindow as gw
from pynput.keyboard import Key, Controller

'''defining functions'''
def main():
    arduino = serial.Serial('com3', 9600)
    data = arduino.readline()
    decoded = str(data[0:len(data)].decode('utf-8'))
    return decoded.strip()



'''first open the website and let it act as the main hub ish'''
os.system("start \"\" http://dawtrek.crcrobotics.com/")

time.sleep(1) # gives time for file to actually start
print(gw.getAllTitles(), end = '\n') # Debug to see if im fucking up
window1 = gw.getWindowsWithTitle('DAW TREK - Google Chrome')[0]
window1.maximize()

# Automate the press of f11 to put the website in fullscreen
keyboard = Controller()
keyboard.press(Key.f11)
keyboard.release(Key.f11)


videoplaying = False
while True:
    inp = main()
    print(inp)
    '''input from the arduino goes from 0 to 3 which corresponds to a video or no video'''
    if (inp == '1') and videoplaying == False:
        os.startfile('C:\\Users\\William\\Videos\\Captures\\(6) Gordon Ramsay Smashes Salmon _ comp _ - YouTube - Google Chrome 2023-01-11 01-56-28.mp4')
        time.sleep(1)  # gives time for file to actually start
        window = gw.getWindowsWithTitle('VLC media player')[0]
        window.maximize()
        videoplaying = True

    elif inp == '2' and videoplaying == False:
        os.startfile('C:\\Users\\William\\Videos\\Captures\\Dawson CRC Robotics Tutorial for Kryptik 2024_ How to pick a CRC Theme.mp4')
        time.sleep(1)  # gives time for file to actually start
        window = gw.getWindowsWithTitle('VLC media player')[0]
        window.maximize()
        videoplaying = True

    elif inp == '2' and videoplaying == False:
        os.startfile('C:\\Users\\William\\Videos\\Captures\\Dawson CRC Robotics Tutorial for Kryptik 2024_ How to pick a CRC Theme.mp4')
        time.sleep(1)  # gives time for file to actually start
        window = gw.getWindowsWithTitle('VLC media player')[0]
        window.maximize()
        videoplaying = True

    elif inp == '0' and videoplaying == True:
        window.close() # when turning off switch and theres a video playing, we close the video window to go back to the mainhub, the website
        videoplaying = False

