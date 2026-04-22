import cv2
import numpy as np

if __name__ == "__main__":
    # Load the binary image in grayscale first
    img = cv2.imread("text-broken.tif", cv2.IMREAD_GRAYSCALE)

    # Ensure the image is strictly binary (0 and 255)
    _, binary_img = cv2.threshold(img, 127, 255, cv2.THRESH_BINARY)

    # Define the structuring element for dilation
    kernel = np.ones((3, 3), np.uint8)

    # 1. Perform Closing
    closed_img = cv2.morphologyEx(binary_img, cv2.MORPH_CLOSE, kernel)

    # 2. Perform Boundary Extraction
    dilated_img = cv2.dilate(closed_img, kernel, iterations=1)

    # Subtract the original binary image from the dilated image
    boundary_img = cv2.subtract(dilated_img, closed_img)

    cv2.imwrite("result/q1/repaired.tif", closed_img)
    cv2.imwrite("result/q1/boundary.tif", boundary_img)

    cv2.imshow("Question 1 (1): Fix Broken", closed_img)
    cv2.imshow("Question 1 (2): Extracted Boundary", boundary_img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
