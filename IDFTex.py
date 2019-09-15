import cv2
import sys
import numpy as np
import matplotlib.pyplot as plt

img = cv2.imread("D:\\Downloads\\room.jpg",cv2.IMREAD_GRAYSCALE)
#maskbs = cv2.imread("",cv2.IMREAD_GRAYSCALE)

# PreProcess Image
img = cv2.resize(img,(640,480),img,0,0,cv2.INTER_AREA)
height, width = img.shape
print(height,width)

# Draw horizontal line every 5 pixels
for i in range(0,height,5):
    cv2.line(img,(0,i),(width-1,i),(0,0,0),1)

if img is None:
    print('Error opening image')

# DFT
dft2d = cv2.dft(np.float32(img), flags=cv2.DFT_COMPLEX_OUTPUT)

dftPS = np.abs(cv2.magnitude(dft2d[:,:,0],dft2d[:,:,1]))**2

'''
plt.subplot(131), plt.imshow(img, cmap='gray'), plt.xticks([]), plt.yticks([])
plt.subplot(132), plt.imshow(20*np.log(dftPS+1), cmap='gray'), plt.xticks([]), plt.yticks([]), plt.title("FFT without Shift")
plt.subplot(133), plt.imshow(20*np.log(np.fft.fftshift(dftPS)+1),cmap='gray'), plt.xticks([]), plt.yticks([]), plt.title("FFT after Shift")
plt.show()
'''

rs, cs = img.shape
rsh = int(rs/2)
csh = int(cs/2)
cross = int(rs/5)
crossHalf = cross*2
print(cross)
print(crossHalf)

# mask1 : Filter to Erase lines.
N = 20
mask1 = np.ones((rs,cs,2),np.uint8)
mask2 = np.zeros((rs,cs,2),np.uint8)

mask1[rsh-cross-N:rsh-cross+N,csh-N:csh+N]=0
mask1[rsh+cross-N:rsh+cross+N,csh-N:csh+N]=0
mask1[rsh-crossHalf-N:rsh-crossHalf+N,csh-N:csh+N]=0
mask1[rsh+crossHalf-N:rsh+crossHalf+N,csh-N:csh+N]=0

# Shift : DFT Power Spectrum
dft2d = np.fft.fftshift(dft2d)
dftFilt = mask1*dft2d
dftFiltPS = np.abs(cv2.magnitude(dftFilt[:,:,0],dftFilt[:,:,1])**2)

# 1. Filter, 2. Power Spectrum, 3. Power Spectrum + Filter
plt.subplot(231), plt.imshow(mask1[:,:,0],cmap='gray'), plt.xticks([]), plt.yticks([])
plt.subplot(232), plt.imshow(20*np.log(np.fft.fftshift(dftPS)+1),cmap='gray'), plt.xticks([]), plt.yticks([])
plt.subplot(233), plt.imshow(20*np.log(dftFiltPS+1),cmap='gray'), plt.xticks([]), plt.yticks([])
plt.show()

# Filter + Power Spectrum Shifting
dftFilt = np.fft.fftshift(dftFilt)

# IDFT : Filter + Power Spectrum
imgFilt = cv2.idft(dftFilt)
imgFilt = cv2.magnitude(imgFilt[:,:,0],imgFilt[:,:,1])

# 1. Original Image + Horizontal Lines
# 2. Filtering Image using Filter and IDFT
plt.subplot(121), plt.imshow(img,cmap='gray'), plt.xticks([]), plt.yticks([])
plt.subplot(122), plt.imshow(imgFilt,cmap='gray'), plt.xticks([]), plt.yticks([])
plt.show()