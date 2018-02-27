import cv2
import numpy as np

cap = cv2.VideoCapture(1)

size = 60
string = ""
 # Take each frame
_, frame = cap.read()
xoff = 230
yoff = 0
face = 0
white = 20
red = 180
yellow = 30
green = 70
blue = 110
orange = 10
tolerance = 10
while face < 6:
    _, frame = cap.read()    
    cube = [0,0,0,0,0,0,0,0,0]

    for x in range(3):
        for y in range(3):
            cube[x*3+y] = frame[(size/2)+size*y+yoff,(size/2)+size*x+xoff]            
            temp = np.uint8([[cube[x*3+y]]])
            hsv = cv2.cvtColor(temp,cv2.COLOR_BGR2HSV)[0][0]
            if hsv[1]<white + tolerance:
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
               
            # print cube[x*3+y],hsv
    

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
            cv2.rectangle(frame,(size*(x)+xoff,size*(y)+yoff),(size*(x+1)+xoff,size*(y+1)+yoff),color,5)
    cv2.imshow('frame',frame)
    k = cv2.waitKey(5) & 0xFF
    if k == 27:
        break
    elif k == 119:
        yoff-=10
    elif k == 115:
        yoff+=10
    elif k ==97:
        xoff-=10
    elif k== 100:
        xoff+=10
    elif k==255:
        pass
    elif k == 32:
        if " " not in cube:
            for x in range(3):
                for y in range(3):
                    string+=cube[y*3+x].lower()
            face+=1
            print "Saved face",face
        else:
            print "Error try again"
    elif k == 49:
        size+=1
    elif k == 50:
        size-=1
    else:
        print k

    
print string
file = open("Colors.txt","w") 
file.write(string) 
cv2.destroyAllWindows()