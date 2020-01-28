import serial 
#import RPi.GPIO as GPIO
import time
from guizero import App, Combo, Text, CheckBox, ButtonGroup, PushButton, info, TextBox

ser=serial("/dev/ttyACM0",9600) #change ACM number as found from ls /dev/tty/ACM*
ser.baudrate=9600

##def do_booking():
##    info("Booking", "Thank you for booking")
##    print(film_choice.value)
##    print(vip_seat.value)
##    print(row_choice.value)

serr = ser.readline()
def LeftRoom():
    info("Lights on", "Keep Exploring")
    if light_choiceL.value == "On":
        ser.write(b'9')
    if light_choiceL.value == "Off":
        ser.write(b'X')
def RightRoom():
    info("Lights on", "Keep Exploring")
    if light_choiceR.value == "On":
        ser.write(b'8')
    if light_choiceR.value == "Off":
        ser.write(b'Y')
        

def color_selection():
    info("Color Selection", "Choose another color.")
    print(color_choice.value)
    if color_choice.value == "Purple":
        ser.write(b'1')
    elif color_choice.value == "Green":
        ser.write(b'2')
    elif color_choice.value == "Blue":
        ser.write(b'3')
    elif color_choice.value == "Red":
        ser.write(b'4')
    elif color_choice.value == "Aqua":
        ser.write(b'5')
    elif color_choice.value == "Yellow":
        ser.write(b'6')
    elif color_choice.value == "White":
        ser.write(b'7')
    elif color_choice.value == "Off":
        ser.write(b'0')
    elif color_choice.value == "Fade":
        ser.write(b'A')
    else:
        ser.write(b'9')
def LED_Rooms():
    info("Room Left", "Your selection has been confirmed.")
    print(light_choiceL.value)

def TempArduino():
    info("Temperature Output", "Keep exploring")
    serr=ser.readline()
    Output = Text(app,text = serr, size=15,font="Times New Roman",color="red",grid=[1,15], align="right")
    if TempOutput.value == "Yes":
        serr=ser.readline()
        print(serr) 


app = App(title = "RGB LED Selection", width= 750, height=750, layout="grid")
welcome_message = Text(app, text="Welcome to the Living Intelligence Smart Home", size=20, font="Times New Roman", color = "blue",grid=[1,0],align="top")
color_choice = Combo(app, options=["Purple", "Green", "Blue", "Red","Yellow", "Aqua", "Yellow", "White","Fade","Off"], grid=[1,2], align="left")
color_description = Text(app, text="What color would you like for the RGB LED?", grid=[1,1], align = "left")
light_roomR = Text(app, text="Would you like to turn on the lights in the right room?", grid=[1,6], align = "left")
light_choiceR = Combo(app, options=["On","Off"], grid=[1,7], align="left")
light_roomL = Text(app, text="Would you like to turn on the lights in left room?", grid=[1,2], align = "right")
light_choiceL = Combo(app, options=["On","Off"], grid=[1,3], align="right")
LeftFinal = PushButton(app, command = LeftRoom, text ="Confirm if you want lights on in left room", grid=[1,10], align="top")
RightFinal = PushButton(app, command = RightRoom, text ="Confirm if you want lights on in right room", grid=[1,11], align="top")
final_color = PushButton(app, command=color_selection, text="confirm color", grid=[1,8],align="top")
TempReading = Text(app, text="Would you like to know the temperature and humidity of your house?",grid=[1,4],align="right")
TempOutput = Combo(app,options=["Yes","No"], grid=[1,5],align="right")
final_Temp = PushButton(app,command=TempArduino, text="temperature reading", grid=[1,9], align="top")

#my_name = TextBox(app, width=40)
#update_text = PushButton(app, command=say_my_name, text="Display my name")

app.display()

##vip_seat = CheckBox(app, text="VIP seat?", grid=[1,1], align = "left")

##row_choice = ButtonGroup(app, options=[["Front","F"], ["Middle","M"],["Back","B"]],selected="M", horizontal=True, grid=[1,2], align="left")

##book_seats = PushButton(app, command=do_booking, text="Book seat", grid=[1,3], align="left")


##def blink(pin):
##    GPIO.output(pin,GPIO.HIGH)
##    time.sleep(1)
##    GPIO.output(pin,GPIO.LOW)
##    time.sleep(1)
##    return
##
##GPIO.setmode(GPIO.BOARD)
##GPIO.setup(11,GPIO.OUT)
##
##while True:
##
##    read_ser=ser.readline()
##    print(read_ser)
##    if(read_ser=="Hello From Arduino!"):
##        blink(11)


        
