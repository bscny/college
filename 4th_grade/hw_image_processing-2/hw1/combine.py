import cv2
import numpy as np

from hw1.src.lib_1 import find_first_target_pixel

if __name__ == "__main__":
    x_orig, y_orig = find_first_target_pixel('lena_left.bmp', find_white=True)
    x_crop, y_crop = find_first_target_pixel('lena_cropped.bmp', find_white=False)

    # Merge lena_cropped and lena_left by matching x and y
    img_left = cv2.imread('lena_left.bmp')
    img_crop = cv2.imread('lena_cropped.bmp')

    # Calculate the offset to align the top-left of img_crop onto img_left
    offset_x = x_orig - x_crop
    offset_y = y_orig - y_crop

    # Create a mask of the actual content in the crop, ignoring its white space
    valid_pixels_mask = ~np.all(img_crop == [255, 255, 255], axis=-1)

    # Get the local (y, x) coordinates of the valid pixels in the crop
    local_y, local_x = np.where(valid_pixels_mask)

    # Perform the merge! Map the safe local pixels to the safe global coordinates
    img_left[local_y + offset_y, local_x + offset_x] = img_crop[local_y, local_x]

    cv2.imwrite("result/q1/lena_merged.bmp", img_left)