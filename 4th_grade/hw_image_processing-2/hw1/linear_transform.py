import cv2
import numpy as np

from src.lib_2 import resize_nearest_neighbor

if __name__ == "__main__":
    resized = resize_nearest_neighbor("lena.bmp", 0.8)
    
    cv2.imwrite("result/80.bmp", resized)