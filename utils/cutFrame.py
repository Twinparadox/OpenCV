import cv2
import numpy as np

# file path
file = "C:\\Users\\user\\Documents\\Adobe\\Premiere Pro\13.0\\fr11_1.avi"

cap = cv2.VideoCapture(file)

if cap.isOpened() == False:
  print("Error opening video stream or file")

idx = 0

# directory path to save frames
path = './frames_premier/frs'
while cap.isOpened():
    ret, frame = cap.read()
    
    # 이름 순으로 정렬하는 경우, fr13이 fr2보다 먼저 나오는 문제가 발생하므로
    # 빈 자리에 0을 매핑
    if ret==True:
        cv2.imshow('Frame', frame)
        if idx<10:
            strIdx ="00"+str(idx)
        elif idx<100:
            strIdx = "0"+str(idx)
        else:
            strIdx= str(idx)
        cv2.imwrite(path+strIdx+'.png',frame)
        idx += 1
    else:
        break

cap.release()