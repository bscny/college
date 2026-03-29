import cv2
import numpy as np

# Load the original image
img = cv2.imread("stop-sign.png")

height, width = img.shape[:2] 

# Define the 4 source and 4 target points in a float32 numpy array
pts_src = np.array([
    [50, 154],  # Point 1
    [565, 314],  # Point 2
    [50, 432],  # Point 3
    [574, 560]   # Point 4
], dtype=np.float32)

pts_dst = np.array([
    [50, 154],  # Target Point 1
    [540, 154],  # Target Point 2
    [50, 432],  # Target Point 3
    [540, 432]   # Target Point 4
], dtype=np.float32)

# Calculate the perspective transformation matrix (3x3)
matrix = cv2.getPerspectiveTransform(pts_src, pts_dst)

# Apply the perspective warp
warped_img = cv2.warpPerspective(img, matrix, (width, height))

cv2.imwrite("result/q3/rectified.png", warped_img)