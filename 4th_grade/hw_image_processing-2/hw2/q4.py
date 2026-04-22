import cv2
from src.contrast_stretching_helper import adaptive_gamma
from src.histogram_equal_helper import generate_histogram

if __name__ == "__main__":
    image = cv2.imread("dark.png", cv2.IMREAD_GRAYSCALE)

    if image is None:
        print(f"Error: Could not load the image. Please check the file path.")
    else:
        result_img_boost = adaptive_gamma(image, 0.5, plot_histogram=True)
        result_img_suppress = adaptive_gamma(image, 2, plot_histogram=True)

        generate_histogram(result_img_boost, plot_histogram=True)
        generate_histogram(result_img_suppress, plot_histogram=True)
        
        cv2.imwrite("result/q4/dark_adaptive_gamma_boost.png", result_img_boost)
        cv2.imwrite("result/q4/dark_adaptive_gamma_suppress.png", result_img_suppress)
        
        cv2.imshow("Question 4: Adaptive Gamma, alpha = 0.5 (Boost)", result_img_boost)
        cv2.imshow("Question 4: Adaptive Gamma, alpha = 2.0 (Suppress)", result_img_suppress)
        cv2.waitKey(0)
        cv2.destroyAllWindows() 