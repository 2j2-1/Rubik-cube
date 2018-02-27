import cv2
import numpy as np

cap = cv2.VideoCapture(0)


string = ""
# Take each frame
# _, frame = cap.read()
for face in range(6):
    frame = cv2.imread('face'+str(face)+'.jpg')
    xoff = 0
    yoff = 0
    cube = [0,0,0,0,0,0,0,0,0]
    kernel = np.ones((20,20),np.float32)/400
    # frame = cv2.filter2D(frame,-1,kernel)
    for x in range(3):
        for y in range(3):
            cube[x*3+y] = frame[64+128*y,64+128*x]            
            green = np.uint8([[cube[x*3+y]]])
            hsv = cv2.cvtColor(green,cv2.COLOR_BGR2HSV)[0][0]
            if hsv[1]<30:
                cube[x*3+y] = "W" 
            elif hsv[0]>170 and hsv[0] < 190:
                cube[x*3+y] = "R"    
            elif hsv[0]>20 and hsv[0] < 40:
                cube[x*3+y] = "Y"
            elif hsv[0]>60 and hsv[0] < 80:
                cube[x*3+y] = "G"
            elif hsv[0]>90 and hsv[0] < 110:
                   cube[x*3+y] = "B"
            elif hsv[0]>0 and hsv[0] < 20:
                    cube[x*3+y] = "O"
            else:
                cube[x*3+y] = " "
               
            # print cube[x*3+y],hsv
    for x in range(3):
        for y in range(3):
            string+=cube[y*3+x].lower()

    for x in range(3):
        for y in range(3):
            if cube[x*3+y] == "R":
                cv2.rectangle(frame,(128*(x)+xoff,128*(y)+yoff),(128*(x+1)+xoff,128*(y+1)+yoff),(0,0,255),-1)
            elif cube[x*3+y] == "G":
                cv2.rectangle(frame,(128*(x)+xoff,128*(y)+yoff),(128*(x+1)+xoff,128*(y+1)+yoff),(0,255,0),-1)
            elif cube[x*3+y] == "Y":
                cv2.rectangle(frame,(128*(x)+xoff,128*(y)+yoff),(128*(x+1)+xoff,128*(y+1)+yoff),(0,255,255),-1)
            elif cube[x*3+y] == "O":
                cv2.rectangle(frame,(128*(x)+xoff,128*(y)+yoff),(128*(x+1)+xoff,128*(y+1)+yoff),(0,128,255),-1)
            elif cube[x*3+y] == "W":
                cv2.rectangle(frame,(128*(x)+xoff,128*(y)+yoff),(128*(x+1)+xoff,128*(y+1)+yoff),(255,255,255),-1)
            elif cube[x*3+y] == "B":
                cv2.rectangle(frame,(128*(x)+xoff,128*(y)+yoff),(128*(x+1)+xoff,128*(y+1)+yoff),(255,0,0),-1)
            else:
                cv2.rectangle(frame,(128*(x)+xoff,128*(y)+yoff),(128*(x+1)+xoff,128*(y+1)+yoff),(0,0,0),-1)
    # cv2.imshow('frame',frame)
    # k = cv2.waitKey(0) & 0xFF

print string
file = open("Colors.txt","w") 
file.write(string) 
cv2.destroyAllWindows()