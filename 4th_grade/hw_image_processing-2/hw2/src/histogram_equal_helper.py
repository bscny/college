import numpy as np  # IMPORTANT Note, I only import np for type expression, all functions are hand crafted
import matplotlib.pyplot as plt

def generate_histogram(image: np.ndarray,
                       get_min_max: bool = False,
                       plot_histogram: bool = False)-> list[int] | tuple[list[int], int, int]:
    '''Return the histogram (list) and min, max (if selected)'''
    # Get the dimensions of the image
    height, width = image.shape

    # Initialize the histogram (a list of 256 zeros) and min, max
    histogram = [0] * 256
    min_intensity = 255
    max_intensity = 0

    for y in range(height):
        for x in range(width):
            # Get the current pixel intensity
            pixel_intensity = image[y, x]
            
            # Increment the corresponding bucket
            histogram[pixel_intensity] += 1
            
            if get_min_max:
                max_intensity = max(max_intensity, pixel_intensity)
                min_intensity = min(min_intensity, pixel_intensity)
    
    if plot_histogram:
        plt.figure(figsize=(10, 5))
        plt.bar(range(256), histogram, color='gray', width=1)
        
        plt.title('Computed Grayscale Histogram')
        plt.xlabel('Pixel Intensity (0 - 255)')
        plt.ylabel('Number of Pixels')
        plt.xlim([0, 255])
        plt.grid(axis='y', alpha=0.75)
        
        plt.show()
                   
    if get_min_max:
        return histogram, min_intensity, max_intensity
    else:
        return histogram

def histogram_matching(image: np.ndarray, start_intensity: int = 0, end_intensity: int = 255) -> np.ndarray:
    height, width = image.shape
    total_pixels = height * width
    
    # Get the original image's histogram
    histogram = generate_histogram(image)
    
    # Calculate the CDF
    cdf = [0] * 256
    current_sum = 0
    for i in range(256):
        current_sum += histogram[i]
        cdf[i] = current_sum
    
    mapping = [0] * 256
    
    # Loop through targeted intensities
    for i in range(start_intensity, end_intensity + 1):
        # To match the 2 CDFs we want: CDF_input(i) = CDF_output(x) = x/255
        # Therefore, x = 255 * CDF_input(i)
        mapping[i] = round(255 * (cdf[i] / total_pixels))
        
    # Apply the mapping to create the new image
    output_image = np.zeros((height, width), dtype=image.dtype)

    for y in range(height):
        for x in range(width):
            old_intensity = image[y, x]

            # Assign the new calculated intensity from our lookup table
            # Notice that the intensities outside the start ~ end will be map to 0
            output_image[y, x] = mapping[old_intensity]
            
    return output_image
