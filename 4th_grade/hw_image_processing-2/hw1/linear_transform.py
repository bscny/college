import cv2
import numpy as np

from src.lib_2 import resize, rotate, resize_bicubic

if __name__ == "__main__":
    base_folder = "result/q2/"
    
    img = resize("lena.bmp", 0.8, isBilinear=False)
    cv2.imwrite(base_folder + "shrink_80_nni.bmp", img)
    
    img = resize("lena.bmp", 0.8)
    cv2.imwrite(base_folder + "shrink_80_bi.bmp", img)

    img = resize("lena.bmp", 1.3, isBilinear=False)
    cv2.imwrite(base_folder + "enlarge_130_nni.bmp", img)
    
    img = resize("lena.bmp", 1.3)
    cv2.imwrite(base_folder + "enlarge_130_bi.bmp", img)
    
    img = rotate("lena.bmp", 30, isBilinear=False)
    cv2.imwrite(base_folder + "rotate_30_nni.bmp", img)
    
    img = rotate("lena.bmp", 30)
    cv2.imwrite(base_folder + "rotate_30_bi.bmp", img)
    
    img = resize_bicubic("lena.bmp", 0.6)
    cv2.imwrite(base_folder + "shrink_60_bci.bmp", img)