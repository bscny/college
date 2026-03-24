import cv2
import numpy as np

def resize_nearest_neighbor(image_path: str, target_ratio: float):
    '''given the image path and the desired ratio, return the resized the original image'''
    # loads images in BGR format by default
    img = cv2.imread(image_path)
    
    if img is None:
        print(f"Error: Could not load image at {image_path}")
        return None
    
    # Get original dimensions
    old_h, old_w, channels = img.shape
    
    # Calculate new dimensions based on the target ratio
    new_h = int(old_h * target_ratio)
    new_w = int(old_w * target_ratio)
    
    # Backward Warping using Nearest Neighbor Interpolation
    # Generate arrays representing the x and y coordinates of the NEW image
    x_indices = np.arange(new_w)
    y_indices = np.arange(new_h)
    
    # Map the NEW coordinates BACK to the OLD coordinates
    # np.clip ensures that floating point rounding doesn't push us out of array bounds
    # np.round() ensures we actually get the nearest pixel before casting to int
    src_x = np.clip(np.round(x_indices / target_ratio).astype(int), 0, old_w - 1)
    src_y = np.clip(np.round(y_indices / target_ratio).astype(int), 0, old_h - 1)
    
    # Create a 2D coordinate grid from the 1D arrays
    # yy will hold the row indices, xx will hold the column indices
    xx, yy = np.meshgrid(src_x, src_y)
    
    # Use advanced NumPy indexing to fetch all the mapped pixels at once
    resized_img = img[yy, xx]
    
    return resized_img