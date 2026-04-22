import cv2
from src.contrast_stretching_helper import contrast_stretch

if __name__ == "__main__":
    image = cv2.imread("aerialview-washedout.tif", cv2.IMREAD_GRAYSCALE)

    if image is None:
        print(f"Error: Could not load the image. Please check the file path.")
    else:
        result_img = contrast_stretch(image)
        
        cv2.imwrite("result/q2/aerialView_contrast_stretch.tif", result_img)

        cv2.imshow("Question 2: Contrast Stretch", result_img)
        cv2.waitKey(0)
        cv2.destroyAllWindows() 