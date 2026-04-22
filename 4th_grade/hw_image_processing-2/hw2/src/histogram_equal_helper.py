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
            pixel_intensity = image[y][x]
            
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
    
def reweight_histogram(histogram: list[int], alpha: float, plot_histogram: bool = False)-> tuple[list[float], float]:
    '''Return the re-weighted histogram (list) and summation of these probabilities'''
    # Get Total Pixel first
    total_pixels = sum(histogram)

    # Find the maximum and minimum values of the input PDF
    p_max = max(histogram) / total_pixels
    p_min = min(histogram) / total_pixels
    
    # Initialize a new histogram in float (for probability)
    reweighted_hist = []
    summation = 0.0

    if p_max == p_min:
        reweighted_hist = [float(p / total_pixels) for p in histogram]
        summation = 1.0
    else:    
        # For each intensity, apply the reweighting
        for pixels in histogram:
            p = pixels / total_pixels
            
            normalized_p = (p - p_min) / (p_max - p_min)
            weighted_p = p_max * (normalized_p ** alpha)
            reweighted_hist.append(weighted_p)
            
            summation += weighted_p
    
    if plot_histogram:
        # Reconstruct the original PDF for the visual comparison
        original_pdf = [p / total_pixels for p in histogram]
        
        plt.figure(figsize=(10, 5))
        # Using a step or line plot is usually best for viewing 256-bin image histograms
        plt.plot(original_pdf, label='Original PDF $P(l)$', color='blue', alpha=0.7)
        plt.plot(reweighted_hist, label=f'Reweighted PDF $P_w(l)$ ($\\alpha={alpha}$)', color='orange', alpha=0.9)
        
        plt.title('AGCWD Weighting (re)Distribution')
        plt.xlabel('Intensity Level ($l$)')
        plt.ylabel('Probability Density')
        plt.legend()
        plt.grid(True, linestyle='--', alpha=0.5)
        
        # Fill the area under the curves for better visual comparison
        plt.fill_between(range(len(original_pdf)), original_pdf, color='blue', alpha=0.1)
        plt.fill_between(range(len(reweighted_hist)), reweighted_hist, color='orange', alpha=0.1)
        
        plt.tight_layout()
        plt.show()
        
    return reweighted_hist, summation

def histogram_matching(image: np.ndarray, start_intensity: int = 0, end_intensity: int = 255, plot_histogram: bool = False) -> np.ndarray:
    height, width = image.shape
    
    # Get the original image's histogram
    histogram = generate_histogram(image, plot_histogram=plot_histogram)
    
    # Calculate the Cumulative Pixels (which is CDF * total_pixels)
    # notice that only the start ~ end intensity zone will be record
    cumulative_pixels = [0] * 256
    current_sum = 0
    for i in range(start_intensity, end_intensity + 1):
        current_sum += histogram[i]
        cumulative_pixels[i] = current_sum
    
    total_pixels = current_sum
    
    # Creating the intensity mapping lookup table
    # notice that only the start ~ end intensity zone will be record
    mapping = [0] * 256
    
    # Loop through targeted intensities
    for i in range(start_intensity, end_intensity + 1):
        # To match the 2 CDFs we want: CDF_input(i) = CDF_output(x) = x/255
        # Therefore, x = 255 * CDF_input(i)
        mapping[i] = round(255 * (cumulative_pixels[i] / total_pixels))
        
    # Apply the mapping to create the new image
    output_image = np.zeros((height, width), dtype=image.dtype)

    for y in range(height):
        for x in range(width):
            old_intensity = image[y][x]

            # Assign the new calculated intensity from our lookup table
            # Notice that the intensities outside the start ~ end will be map to 0
            output_image[y][x] = mapping[old_intensity]
            
    return output_image
