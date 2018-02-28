import cv2
import numpy as np


cap = cv2.VideoCapture(0)

string = ""
_, frame = cap.read()
#config
xoff = 200
yoff = 135
size = 60
face = 0
white = 150
red = 180
yellow = 30
green = 70
blue = 105
orange = 10
tolerance = 10
sensitivity = 10

historyTolerance = 30
history = 0
historyCube = [0,0,0,0,0,0,0,0,0]
index = "YBRGOW"
coloredCube = [0,0,0,0,0,0]
calibrated = True
gridCalibrated = False
COLORS = ["Yellow","Blue","Red","Green","Orange","White"]

def calibrate_grid():
    while 1:
        _, frame = cap.read()
        draw_grid(frame)
        global xoff,yoff,size
        k = cv2.waitKey(5) & 0xFF
        if k == 119:
            yoff-=sensitivity
        elif k == 115:
            yoff+=sensitivity
        elif k ==97:
            xoff-=sensitivity
        elif k== 100:
            xoff+=sensitivity
        elif k == 49:
            size+=1
        elif k == 50:
            size-=1
        elif k == 27:
            break
        cv2.imshow('Calibrate Grid',frame)

def draw_grid(frame,cube=[0,0,0,0,0,0,0,0,0],thickness = 10):
    for x in range(3):
        for y in range(3):
            if cube[x*3+y] == "R":
                color = [0,0,255]
            elif cube[x*3+y] == "G":
                color = [0,255,0]
            elif cube[x*3+y] == "Y":
                color = [0,255,255]
            elif cube[x*3+y] == "O":
                color = [0,128,255]
            elif cube[x*3+y] == "W":
                color = [255,255,255]
            elif cube[x*3+y] == "B":
                color = (255,0,0)
            else:
                color = [0,0,0]
            cv2.rectangle(frame,(size*(x)+xoff+(thickness),size*(y)+yoff+(thickness)),(size*(x+1)+xoff-(thickness),size*(y+1)+yoff-(thickness)),color,thickness)

def calibrate():
    global yellow,blue,red,green,orange
    calibratedColors = ["Yellow","Blue","Red","Green","Orange"]
    for i in range(5):
        print "Please show", calibratedColors[i], "side "
        while 1:
            _, frame = cap.read()   
            coloredCube = [0,0,0,0,0,0,0,0,0]
            for x in range(3):
                for y in range(3):
                    cube[x*3+y] = frame[(size/2)+size*y+yoff,(size/2)+size*x+xoff]            
                    temp = np.uint8([[cube[x*3+y]]])
                    hsv = cv2.cvtColor(temp,cv2.COLOR_BGR2HSV)[0][0]
                    coloredCube[x*3+y] = hsv[0]
            temp = sum(coloredCube) / len(coloredCube)
            draw_grid(frame,[0,0,0,0,0,0,0,0,0])
            cv2.imshow("calibrate",frame)
            k = cv2.waitKey(5) & 0xFF
            if k == 32 and temp not in calibratedColors:
                calibratedColors[i] = temp
                print calibratedColors[i]
                break
    yellow = calibratedColors[0]
    blue = calibratedColors[1]
    red = calibratedColors[2]
    green = calibratedColors[3]
    orange = calibratedColors[4]

def lts(list,string):
    tempString = ""
    for x in range(3):
            for y in range(3):
                tempString+=list[y*3+x]
    for i in range(len(string)-len(tempString)+1):
        if tempString.lower()==string[i:i+len(tempString)]:
            return False
    return True

def get_color(frame):
    for x in range(3):
        for y in range(3):
            cube[x*3+y] = frame[(size/2)+size*y+yoff,(size/2)+size*x+xoff]            
            temp = np.uint8([[cube[x*3+y]]])
            hsv = cv2.cvtColor(temp,cv2.COLOR_BGR2HSV)[0][0]
            if hsv[1]<white and hsv[0]<50:
                cube[x*3+y] = "W" 
            elif hsv[0]>red - tolerance and hsv[0] < red + tolerance:
                cube[x*3+y] = "R"    
            elif hsv[0]> yellow - tolerance and hsv[0] < yellow + tolerance:
                cube[x*3+y] = "Y"
            elif hsv[0] > green - tolerance and hsv[0] < green + tolerance:
                cube[x*3+y] = "G"
            elif hsv[0]>blue - tolerance and hsv[0] < blue + tolerance:
                   cube[x*3+y] = "B"
            elif hsv[0]>orange - tolerance and hsv[0] < orange + tolerance:
                    cube[x*3+y] = "O"
            else:
                cube[x*3+y] = " "

def setup():
    global gridCalibrated,calibrated
    if not gridCalibrated:
        calibrate_grid()  
        gridCalibrated = True
        cv2.destroyAllWindows()
    if not calibrated:
        calibrate()
        calibrated = True
        cv2.destroyAllWindows()

def saveFace(k):
    global history,string,cube,face,historyCube
    if (k == 32 or history == historyTolerance):
        if lts(historyCube,string):
            if " " not in cube:
                for x in range(3):
                    for y in range(3):
                        string+=cube[y*3+x].lower()
                coloredCube[index.index(cube[4])] = cube
                
                print "Saved",COLORS[index.index(cube[4])],"face"
                history = 0
                face+=1
            else:
                print "Error could not dected postions", cube.index(" "), "color"
                
        else:
            print "Already Scaned",COLORS[index.index(cube[4])],"face"
            history = 0

    if historyCube == cube and " " not in cube:
        history+=1
    else:
        historyCube = cube[:]
        history = 0

def save():
    string = ""
    try:
        for i in range(6):
            for x in range(3):
                    for y in range(3):
                        string+=coloredCube[i][y*3+x].lower()
    except:
        pass

    print string
    file = open("Colors.txt","w") 
    file.write(string) 
    

while face < 6:
    _, frame = cap.read()    
    cube = [0,0,0,0,0,0,0,0,0]

    k = cv2.waitKey(5) & 0xFF
    setup()
    get_color(frame)
    draw_grid(frame,cube)
    saveFace(k)
    cv2.imshow('Rubik Cube Scanner',frame)
    if k == 27:
        break
save()
cv2.destroyAllWindows()
