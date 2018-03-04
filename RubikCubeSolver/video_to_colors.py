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
sensitivity = 5

historyTolerance = 20
history = 0
historyCube = [0,0,0,0,0,0,0,0,0]
index = "YBRGOW"
coloredCube = [0,0,0,0,0,0]
COLORS = ["Yellow","Blue","Red","Green","Orange","White"]
sizeHistory = []
corners = [0,0,0,0]
averageFaceLength = 10

# setup
calibrated = True
gridCalibrated = True
dynnamicTracking = True

def validate_sqaure(min,max,squareTolerance=0.5):
    try:
        temp =  float(abs(max[0] - min[0]))/abs(max[1] - min[1])
        if temp> 1 - sqaureTolerance and temp < 1 + sqaureTolerance:
            return True
        return False
    except:
        return False

def angle_cos(p0, p1, p2):
    d1, d2 = (p0-p1).astype('float'), (p2-p1).astype('float')
    return abs( np.dot(d1, d2) / np.sqrt( np.dot(d1, d1)*np.dot(d2, d2) ) )

def find_squares(img):
    squares = []
    for gray in cv2.split(img):
        for thrs in xrange(0, 255, 52):
            if thrs == 0:
                bin = cv2.Canny(gray, 0, 50, apertureSize=5)
                bin = cv2.dilate(bin, None)
            else:
                _retval, bin = cv2.threshold(gray, thrs, 255, cv2.THRESH_BINARY)
            bin, contours, _hierarchy = cv2.findContours(bin, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)
            for cnt in contours:
                cnt_len = cv2.arcLength(cnt, True)
                cnt = cv2.approxPolyDP(cnt, 0.10*cnt_len, True)
                if len(cnt) == 4 and cv2.contourArea(cnt) > 750 and cv2.isContourConvex(cnt):
                    cnt = cnt.reshape(-1, 2)
                    max_cos = np.max([angle_cos( cnt[i], cnt[(i+1) % 4], cnt[(i+2) % 4] ) for i in xrange(4)])
                    if max_cos < 0.1:
                        squares.append(cnt)
    return squares

def find_cube(img):
    global sizeHistory,corners
    min = [1000,1000]
    max = [0,0]

    squares = find_squares(img)
    # cv2.drawContours( img, squares, -1, (0, 255, 0), 3 )
    for i in squares:
        if validate_sqaure(i[1],i[3]):   
            for j in i:
                if sum(j) < sum(min) and j[0] > 0 and j[1] > 0:
                    min = j[:]
                elif sum(j) > sum(max) and j[0]<479 and j[1]<479:
                    max = j[:]

    # cv2.waitKey(0)
    if min[0]!=1000 and max[0]!=0:
        sizeHistory.append(int(min[0]*max[1]))
        if len(sizeHistory) == 2:
            del sizeHistory[0]
        if sizeHistory[0] >= np.max(sizeHistory) -10000 and validate_sqaure(min,max):
            corners = [min[0],min[1],max[0],max[1]]
    if min[0] !=1000 and max[0] != 0:
        return corners

def calibrate_grid():
    global xoff,yoff,size

    while 1:
        _, frame = cap.read()
        draw_grid(frame,corners = [])
        
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
    file = open("calibratedGrid.txt","w")
    file.write(str(xoff)+","+str(yoff)+","+str(size))
    file.close 

def draw_grid(frame,corners = [],cube=[0,0,0,0,0,0,0,0,0],thickness = 10):
    global size,xoff,yoff
    if corners != None and corners[1] != 479:
        if corners[1] != 479 and max((corners[2]-corners[0])/3,(corners[3]-corners[1])/3) > 10:
            try:
                tempX = corners[0]
                tempY = corners[1]
                tempSize = max((corners[2]-corners[0])/3,(corners[3]-corners[1])/3)
                if abs(tempX-xoff)>1:
                    xoff = corners[0]
                if abs(tempY-yoff)>1:
                    yoff = corners[1]
                if abs(tempSize-size)>1:
                    size = tempSize
            except:
                pass
    if size < 85 and size>40:
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
                if color:
                    cv2.rectangle(frame,(size*(x)+xoff+(thickness),size*(y)+yoff+(thickness)),(size*(x+1)+xoff-(thickness),size*(y+1)+yoff-(thickness)),color,thickness)

def calibrate():
    global yellow,blue,red,green,orange
    calibratedColors = ["Yellow","Blue","Red","Green","Orange"]
    for i in range(5):
        print "Please show", calibratedColors[i], "side "
        while 1:
            try:
                cube = []
                _, frame = cap.read()   
                coloredCube = []
                for x in range(3):
                    for y in range(3):       
                        temp = np.uint8([[frame[(size/2)+size*y+yoff,(size/2)+size*x+xoff]]])
                        hsv = cv2.cvtColor(temp,cv2.COLOR_BGR2HSV)[0][0]
                        if hsv[0] != 0:
                            coloredCube.append(hsv[0])

                temp = sum(coloredCube) / len(coloredCube)
                draw_grid(frame,find_cube(frame))
                cv2.imshow("calibrate",frame)
                k = cv2.waitKey(5) & 0xFF
                if k == 32 and temp not in calibratedColors:
                    calibratedColors[i] = temp
                    print calibratedColors[i]
                    break
            except:
                pass

    yellow = calibratedColors[0]
    blue = calibratedColors[1]
    red = calibratedColors[2]
    green = calibratedColors[3]
    orange = calibratedColors[4]
    file = open("calibratedColors.txt","w")
    for i in calibratedColors: 
        file.write(str(i)+"\n") 

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
            try:
                temp = np.uint8([[frame[(size/2)+size*y+yoff,(size/2)+size*x+xoff]]])
                hsv = cv2.cvtColor(temp,cv2.COLOR_BGR2HSV)[0][0]
                if hsv[1]<white and (hsv[0]<50 or hsv[0]>140):
                    cube[x*3+y].append("W") 
                elif hsv[0]>150:
                    cube[x*3+y].append("R")
                elif hsv[0]> yellow - tolerance and hsv[0] < yellow + tolerance:
                    cube[x*3+y].append("Y")
                elif hsv[0] > green - tolerance and hsv[0] < green + tolerance:
                    cube[x*3+y].append("G")
                elif hsv[0]>blue - tolerance and hsv[0] < blue + tolerance:
                       cube[x*3+y].append("B")
                elif hsv[0]>orange - tolerance and hsv[0] < orange + tolerance:
                    if hsv[2] > 130:
                        cube[x*3+y].append("O")
                    else:
                        cube[x*3+y].append("R")
                else:
                    cube[x*3+y].append(" ")
            except:
                cube[x*3+y].append(" ")
            if len(cube[x*3+y])==averageFaceLength:
                del cube[x*3+y][0]

def setup():
    global yellow,blue,red,green,orange
    global gridCalibrated,calibrated,dynnamicTracking
    global xoff,yoff,size

    if not gridCalibrated:
        calibrate_grid()  
        gridCalibrated = True
        dynnamicTracking = False
        cv2.destroyAllWindows()
    else:
        file = open("calibratedGrid.txt","r")
        temp = file.read().split(",")
        xoff = int(temp[0])
        yoff = int(temp[1])
        size = int(temp[2])
        file.close()

    if not calibrated:
        calibrate()
        calibrated = True
        cv2.destroyAllWindows()
    else:
        file = open("calibratedColors.txt","r") 
        temp = file.read().split() 
        yellow = int(temp[0])
        blue = int(temp[1])
        red = int(temp[2])
        green = int(temp[3])
        orange = int(temp[4])
        file.close()

def saveFace(k):
    global history,string,averageCube,face,historyCube
    if (k == 32 or history == historyTolerance):
        if lts(historyCube,string):
            if " " not in averageCube:
                for x in range(3):
                    for y in range(3):
                        string+=averageCube[y*3+x].lower()
                coloredCube[index.index(averageCube[4])] = averageCube[:]
                
                print "Saved",COLORS[index.index(averageCube[4])],"face"
                history = 0
                face+=1
            else:
                print "Error could not dected postions", averageCube.index(" "), "color"
                
        else:
            print "Already Scaned",COLORS[index.index(averageCube[4])],"face"
            history = 0

    if historyCube == averageCube and " " not in averageCube:
        history+=1
    else:
        historyCube = averageCube[:]
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

setup()
from collections import Counter
averageCube = [[],[],[],[],[],[],[],[],[]]
cube = [[],[],[],[],[],[],[],[],[]]

_, frame = cap.read()

while face < 6:
    _, frame = cap.read()
    cubePostion = find_cube(frame)
    k = cv2.waitKey(5) & 0xFF
    get_color(frame)
    for i in range(len(cube)):
        averageCube[i] = Counter(cube[i]).most_common(1)[0][0]
    draw_grid(frame,cubePostion if dynnamicTracking else [],averageCube)
    saveFace(k)
    cv2.imshow('Rubik Cube Scanner',frame)
    if k == 27:
        break
save()
cv2.destroyAllWindows()
