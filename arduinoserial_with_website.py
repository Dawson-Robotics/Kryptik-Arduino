import serial
import os
import time
import pygetwindow as gw
from pynput.keyboard import Key, Controller

'''defining functions'''
arduino = serial.Serial('com3', 9600)
def main():

    data = arduino.readline()
    decoded = str(data[0:len(data)].decode('utf-8'))
    return decoded.strip()



'''first open the website and let it act as the main hub ish'''
os.system("start \"\" http://dawtrek.crcrobotics.com/")

time.sleep(2.5) # gives time for file to actually start
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
    '''input from the arduino goes from 0 to 3 which corresponds to a video or no video'''
    # the destruct!
    if (inp == '10'):
        os.startfile("C:\\Users\\tinhr\\OneDrive\\Images\\Projets vidéo\\QVEY8403.MOV")
        time.sleep(10)
        window = gw.getWindowsWithTitle('Lecteur multimédia VLC')[0]
        window.close()


    if (inp == '1') and videoplaying == False:
        os.startfile("C:\\Users\\tinhr\\OneDrive\\Images\\Projets vidéo\\ALERTE_ROUGE.mp4")
        time.sleep(2)
        window = gw.getWindowsWithTitle('Lecteur multimédia VLC')[0]
        window.maximize()
        videoplaying = True

    elif inp == '2' and videoplaying == False:
        os.startfile("C:\\Users\\tinhr\\OneDrive\\Images\\Projets vidéo\\QVEY8403.MOV")
        time.sleep(2)  # gives time for file to actually start
        window = gw.getWindowsWithTitle('Lecteur multimédia VLC')[0]
        window.maximize()


        videoplaying = True

    elif inp == '0' and videoplaying == True:
        print(gw.getAllTitles())
        window = gw.getWindowsWithTitle('Lecteur multimédia VLC')[0]
        window.close() # when turning off switch and theres a video playing, we close the video window to go back to the mainhub, the website
        videoplaying = False


