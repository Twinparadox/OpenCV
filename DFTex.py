import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt

img = cv.imread("D:\\Downloads\\room.jpg", cv.IMREAD_GRAYSCALE)
img = cv.resize(img, dsize=(640, 480), interpolation=cv.INTER_AREA)
height, width = img.shape

for i in range(0,height,5):
    cv.line(img,(0,i),(width-1,i),(0,0,0),1)

if img is None:
    print('Error opening image')

rows, cols = img.shape
m = cv.getOptimalDFTSize(rows)
n = cv.getOptimalDFTSize(cols)
padded = cv.copyMakeBorder(img, 0, m - rows, 0, n - cols, cv.BORDER_CONSTANT, value=[0, 0, 0])

planes = [np.float32(padded), np.zeros(padded.shape, np.float32)]
complexI = cv.merge(planes)  # Add to the expanded another plane with zeros

cv.dft(complexI, complexI)  # this way the result may fit in the source matrix

cv.split(complexI, planes)  # planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
cv.magnitude(planes[0], planes[1], planes[0])  # planes[0] = magnitude
magI = planes[0]

matOfOnes = np.ones(magI.shape, dtype=magI.dtype)
cv.add(matOfOnes, magI, magI)  # switch to logarithmic scale
cv.log(magI, magI)

# non crop = fourier spectrum
# crop = shifted spectrum
magI_rows, magI_cols = magI.shape
# crop the spectrum, if it has an odd number of rows or columns
magI = magI[0:(magI_rows & -2), 0:(magI_cols & -2)]
cx = int(magI_rows / 2)
cy = int(magI_cols / 2)
q0 = magI[0:cx, 0:cy]  # Top-Left - Create a ROI per quadrant
q1 = magI[cx:cx + cx, 0:cy]  # Top-Right
q2 = magI[0:cx, cy:cy + cy]  # Bottom-Left
q3 = magI[cx:cx + cx, cy:cy + cy]  # Bottom-Right
tmp = np.copy(q0)  # swap quadrants (Top-Left with Bottom-Right)
magI[0:cx, 0:cy] = q3
magI[cx:cx + cx, cy:cy + cy] = tmp
tmp = np.copy(q1)  # swap quadrant (Top-Right with Bottom-Left)
magI[cx:cx + cx, 0:cy] = q2
magI[0:cx, cy:cy + cy] = tmp

cv.normalize(magI, magI, 0, 1, cv.NORM_MINMAX)  # Transform the matrix with float values into a

cv.imshow("Input Image", img)  # Show the result
cv.imshow("spectrum magnitude", magI)
cv.waitKey()
