import cv2
from src.histogram_equal_helper import generate_histogram, histogram_matching

if __name__ == "__main__":
    image = cv2.imread("aerialview-washedout.tif", cv2.IMREAD_GRAYSCALE)

    if image is None:
        print(f"Error: Could not load the image. Please check the file path.")
    else:
        hist = generate_histogram(image, plot_histogram=True)

        total_pixels = sum(hist)

        # Get the mean and median for this image
        # For mean: (we round it so we can partition later)
        intensity_sum = sum(intensity * count for intensity, count in enumerate(hist))
        mean_intensity = round(intensity_sum / total_pixels)

        # For median: (we round it so we can partition later)
        cumulative_sum = 0
        median_intensity = 0
        half_pixels = total_pixels / 2.0

        for intensity, count in enumerate(hist):
            cumulative_sum += count
            if cumulative_sum >= half_pixels:
                median_intensity = intensity
                break
        
        print(f"Mean: {mean_intensity}")
        print(f"Median: {median_intensity}")
        
        # Using Median Partition
        dark_median_img = histogram_matching(image, 0, median_intensity, plot_histogram=False)
        light_median_img = histogram_matching(image, median_intensity + 1, 255, plot_histogram=False)

        # Since These 2 images are mutual exclusive, we can simply add them together
        result_median_img = dark_median_img + light_median_img
        
        # Using Mean Partition
        dark_mean_img = histogram_matching(image, 0, mean_intensity, plot_histogram=False)
        light_mean_img = histogram_matching(image, mean_intensity + 1, 255, plot_histogram=False)

        # Since These 2 images are mutual exclusive, we can simply add them together
        result_mean_img = dark_mean_img + light_mean_img
        
        cv2.imwrite("result/q5/median_partition.tif", result_median_img)
        cv2.imwrite("result/q5/mean_partition.tif", result_mean_img)
        
        cv2.imshow("Question 5: Partition HE, Median", result_median_img)
        cv2.imshow("Question 5: Partition HE, Mean", result_mean_img)
        cv2.waitKey(0)
        cv2.destroyAllWindows() 