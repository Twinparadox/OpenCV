import cv2 as cv2
import numpy as np
from matplotlib import pyplot as plt

src = cv2.imread("C:\\Users\\wonwoo\\Downloads\\leaves.jpg",cv2.IMREAD_GRAYSCALE)
print(type(src))
img = cv2.resize(src,dsize=(640,480),interpolation=cv2.INTER_AREA)
dst = cv2.dft(img)

f = np.fft.fft2(img)
magnitude_spectrum = 20*np.log(np.abs(f))
magnitude_spectrum = np.asarray(magnitude_spectrum,dtype=np.uint8)


cv2.imshow("src",img)
cv2.imshow("dst",dst)
cv2.waitKey(0)
cv2.destroyAllWindows()

'''
print(magnitude_spectrum)

plt.imshow(img, cmap = 'gray')
plt.title('Input Image'), plt.xticks([]), plt.yticks([])
plt.show()
plt.imshow(magnitude_spectrum, cmap = 'gray')
plt.title('Magnitude Spectrum'), plt.xticks([]), plt.yticks([])
plt.show()
'''
