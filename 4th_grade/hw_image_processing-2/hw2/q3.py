import cv2
from src.histogram_equal_helper import generate_histogram, histogram_matching

AERIAL_IMG = "aerialview-washedout.tif"
EINSTEIN_IMG = "einstein-low-contrast.tif"

# Comment This Section to Change the Target Image----------
TARGET_IMAGE = AERIAL_IMG
# TARGET_IMAGE = EINSTEIN_IMG
# ------------------------------------------------

if __name__ == "__main__":
    image = cv2.imread(TARGET_IMAGE, cv2.IMREAD_GRAYSCALE)

    if image is None:
        print(f"Error: Could not load the image. Please check the file path.")
    else:
        result_img = histogram_matching(image, plot_histogram=True)
        
        _, mmin, mmax = generate_histogram(result_img, get_min_max=True, plot_histogram=True)
        print(f"min: {mmin}, max: {mmax}")
        
        if TARGET_IMAGE == AERIAL_IMG:
            cv2.imwrite("result/q3/aerialView_GHE.tif", result_img)
        else:
            cv2.imwrite("result/q3/einstein_GHE.tif", result_img)
        
        # print(f"width: {width}, height: {height}")
        cv2.imshow("Question 3: GHE", result_img)
        cv2.waitKey(0)
        cv2.destroyAllWindows() 