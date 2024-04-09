import serial
import os
import time
import random
import pygetwindow as gw
from pynput.keyboard import Key, Controller
import ctypes
from pycaw.pycaw import AudioUtilities,IAudioEndpointVolume
from comtypes import CLSCTX_ALL



'''defining functions'''
arduino = serial.Serial('com3', 9600)

def main():

    data = arduino.readline()
    decoded = str(data[0:len(data)].decode('utf-8'))
    list_values = decoded.split("x")
    print(list_values)
    try: # we do a try here to skip the first instance of pyserial which spits out a fat wad of nothing
        list_values[-1] = list_values[-1][0]
        list_values[-2] = list_values[-2] # we get the \r\n parts out of the decoded outputs
    except:
        pass
    if len(list_values) == 3:
        return list_values

    return "No", 200,"aaaaa" # we set an initial return because first pyserial output is ass nothing





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

# Set audio control
devices = AudioUtilities.GetSpeakers()
interface = devices.Activate(IAudioEndpointVolume._iid_, CLSCTX_ALL, None)
volume = ctypes.cast(interface, ctypes.POINTER(IAudioEndpointVolume) )

def Audioconverter(audio_input):
    try:
        audio_converted = -65 + (65/(1050)) * (audio_input- 0)
    except:
        audio_converted = -64
    return audio_converted

videoplaying = False
audio_funny = False
while True:
    '''input from the arduino goes from 0 to 3 which corresponds to a video or no video'''
    # the destruct!

    #getting the inputs from the arduino
    list_of_inputs = main()
    play_sound = list_of_inputs[0]
    audio_iinput = list_of_inputs[-2]
    inp = list_of_inputs[-1]
    print(list_of_inputs)


    if (inp == '10'):
        os.startfile("C:\\Users\\Willi\\Videos\\bananas.mp4")
        time.sleep(2)
        window = gw.getWindowsWithTitle('VLC media player')[0]
        window.close()


    if (inp == '1') and videoplaying == False:
        os.startfile("C:\\Users\\Willi\\Videos\\bananas.mp4")
        time.sleep(2)
        window = gw.getWindowsWithTitle('VLC media player')[0]
        window.maximize()
        videoplaying = True


    elif inp == '2' and videoplaying == False:
        os.startfile("C:\\Users\\Willi\\Videos\\Yellow_Alert.mp4")
        time.sleep(2)  # gives time for file to actually start
        window = gw.getWindowsWithTitle('VLC media player')[0]
        window.maximize()
        videoplaying = True


    elif play_sound == 'Yes' and audio_funny == False:
        i = random.randrange(0,13)
        if i == 0:
            os.startfile('C:\\Users\\Willi\\Downloads\\Boo-womp - Sound Effect.mp3')

        elif i == 1:
            os.startfile('C:\\Users\\Willi\\Downloads\\you should kill yourself.. NOW!.mp3')

        elif i == 2:
            os.startfile('C:\\Users\\Willi\\Downloads\\Allwevegot.mp3')

        elif i == 3:
            os.startfile('C:\\Users\\Willi\\Downloads\\BasedJROD.mp3')

        elif i == 4:
            os.startfile('C:\\Users\\Willi\\Downloads\\Cass_Out_voiceline.mp3')

        elif i == 5:
            os.startfile('C:\\Users\\Willi\\Downloads\\Engage_Jacob.mp3')

        elif i == 6:
            os.startfile('C:\\Users\\Willi\\Downloads\\Grandpa_hate.mp3')

        elif i == 7:
            os.startfile('C:\\Users\\Willi\\Downloads\\ME_ITSME_VOICELINE.mp3')

        elif i == 8:
            os.startfile('C:\\Users\\Willi\\Downloads\\NoletCRCwompwomp.mp3')

        elif i == 9:
            os.startfile('C:\\Users\\Willi\\Downloads\\Peak_robotics.mp3')

        elif i == 10:
            os.startfile('C:\\Users\\Willi\\Downloads\\Resistors_SUCK.mp3')

        elif i == 11:
            os.startfile('C:\\Users\\Willi\\Downloads\\ROBOFLEET.mp3')

        elif i == 12:
            os.startfile('C:\\Users\\Willi\\Downloads\\superdupercoolamazingfantasticpoggerswackykookycraycrayclassic_endline.mp3')

        audio_funny = True

    elif inp == '0' and videoplaying == True:
        print(gw.getAllTitles())
        window = gw.getWindowsWithTitle('VLC media player')[0]
        window.close() # when turning off switch and theres a video playing, we close the video window to go back to the mainhub, the website
        videoplaying = False


    elif play_sound == 'No' and audio_funny == True:
        #if theres an audio file turn it to a file making it quiet
        # we dont close the file because then if we re open it wont be minimized
        os.startfile('C:\\Users\\Willi\\Downloads\\30 seconds of silence.mp3')
        audio_funny = False

    try:
        volume.SetMasterVolumeLevel(Audioconverter(int(audio_iinput)), None)
    except:
        pass
