import numpy as np  # IMPORTANT Note, I only import np for type expression, all functions are hand crafted

from src.histogram_equal_helper import generate_histogram, reweight_histogram

def contrast_stretch(image: np.ndarray, minG: int = 0, maxG: int = 255) -> np.ndarray:
    # Get the dimensions of the image
    height, width = image.shape

    # Find the current minimum (m) and maximum (M) pixel values manually
    m = 255
    M = 0

    for i in range(height):
        for j in range(width):
            val = int(image[i][j])

            m = min(m, val)
            M = max(M, val)
                
    # Create an empty black canvas with the same dimensions
    out_img = np.zeros((height, width), dtype=image.dtype)

    # print(f"min: {m}, max: {M}")
    
    # Handle the edge case where the image is a solid, uniform color
    if M == m:
        return image
    
    # Apply the contrast stretching pixel by pixel
    for i in range(height):
        for j in range(width):
            val = int(image[i][j])
            
            new_val = ((maxG - minG) * (val - m) / (M - m)) + minG
            
            out_img[i][j] = round(new_val)
            
    return out_img

def adaptive_gamma(image: np.ndarray, alpha: float, plot_histogram: bool = True) -> np.ndarray:
    height, width = image.shape
    
    # Create the original histogram first
    orig_hist = generate_histogram(image, plot_histogram=plot_histogram)

    # Re-weight that histogram
    pw_hist, sum_pw = reweight_histogram(orig_hist, alpha, plot_histogram=plot_histogram)

    # Calculate the CDF_w
    cdf_w = [0.0] * 256
    current_sum = 0.0
    for i in range(256):
        current_sum += (pw_hist[i] / sum_pw)
        cdf_w[i] = current_sum

    # Create an empty black canvas with the same dimensions
    out_img = np.zeros((height, width), dtype=image.dtype)
    
    # Apply Gamma Correction to each pixel
    for i in range(height):
        for j in range(width):
            val = int(image[i][j])
            
            # The formula is I_max * (I / I_max) ^ gamma, where I_max is 255 for 8-bit image and gamma = 1 - CDF_w(I)
            new_val = 255.0 * ((val / 255.0) ** (1 - cdf_w[val]))
            
            out_img[i][j] = round(new_val)
            
    return out_img