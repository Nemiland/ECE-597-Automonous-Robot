import pygame
import time #These are the required libraries (make sure they are installed)
import bluetooth # needed for bluetooth communication
 
bluetooth_addr = "cc:50:e3:a9:2c:8a" # The address from the HC-05 sensor
bluetooth_port = 1 # Channel 1 for RFCOMM
bluetoothSocket = bluetooth.BluetoothSocket (bluetooth.RFCOMM)
bluetoothSocket.connect((bluetooth_addr,bluetooth_port))


pygame.joystick.init() 
joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())] #pygame will find any number of joysticks present on your computer


pygame.init()
pygame.joystick.init()
done = False
Xaxis = 0
Yaxis = 0
button = []

for i in range(12):#create an array to put button values in
    button.append(0)


while done==False:
    for event in pygame.event.get(): #whenever we quit pygame pygame will end
        if event.type == pygame.QUIT:
            done=True

    joystick_count = pygame.joystick.get_count() #we find out how many joysticks are plugged in

    #for i in range(joystick_count): #take that num and iterate through joysticks to get their data
    joystick = pygame.joystick.Joystick(0)
    joystick.init()
    buttonPacket = 0
    for j in range(8): #send the first few values of buttons (adding more and decreasing the delay on sending packets seems to make recieved packets less accurate)
        buttonPacket = (buttonPacket<<1)+joystick.get_button(j)
       
       
    bluetoothSocket.send(str(buttonPacket)+"\t")
    #time.sleep(1)
    print(buttonPacket)
        

    

    Xaxis = int(round(joystick.get_axis(0) * 15 + 15)) #this should be the "drone" setup for X and Y axes.  The last joystick found is the primary
    Yaxis = int(round(30-(joystick.get_axis(3)* 15 + 15)))

    #The joystick axis are indexed at 0, so Left X = 0, Left Y = 1, Right X = 2, Right Y = 3 and so on if you have more

    print("X axis = " + str(Xaxis) + " Y axis = " + str(Yaxis))

    packet = [Xaxis, Yaxis + ( 1 << 5)] #now we will send this packet over to the arduino
    bluetoothSocket.send(str(Xaxis)+'\t'+str(Yaxis)+'\n')
        
    time.sleep(.05) #delay is needed for accuracy on arduino 


bluetoothSocket.close()	