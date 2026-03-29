import cv2
import numpy as np

def resize(image_path: str, target_ratio: float, isBilinear: bool = True):
    '''given the image path and the desired ratio, return the crop-to-fit rotated image'''
    img = cv2.imread(image_path)
    
    if img is None:
        print(f"Error: Could not load image at {image_path}")
        return None
    
    # Get original dimensions
    old_h, old_w = img.shape[:2]
    
    # Calculate new dimensions based on the target ratio
    new_h = int(old_h * target_ratio)
    new_w = int(old_w * target_ratio)
    
    # Create the grid of new coordinates   
    yy, xx = np.indices((new_h, new_w))
    
    # Map the NEW coordinates BACK to the OLD coordinates (Backward Warping)
    src_x = xx / target_ratio
    src_y = yy / target_ratio
    
    # Interpolation
    if isBilinear:
        # Get the integer coordinates for the 4 surrounding pixels
        x_floor = np.floor(src_x).astype(int)
        y_floor = np.floor(src_y).astype(int)
        x_ceil = x_floor + 1
        y_ceil = y_floor + 1
        
        # np.clip ensures that floating point rounding doesn't push us out of array bounds
        x_floor = np.clip(x_floor, 0, old_w - 1)
        x_ceil = np.clip(x_ceil, 0, old_w - 1)
        y_floor = np.clip(y_floor, 0, old_h - 1)
        y_ceil = np.clip(y_ceil, 0, old_h - 1)
        
        # Advanced NumPy indexing to fetch the pixel for all 4 corners
        Ia = img[y_floor, x_floor]   # Top-Left
        Ib = img[y_floor, x_ceil]  # Top-Right
        Ic = img[y_ceil, x_floor]  # Bottom-Left
        Id = img[y_ceil, x_ceil]  # Bottom-Right
        
        # Calculate the fractional distances
        dx = src_x - x_floor
        dy = src_y - y_floor
        
        # Add a third axis to the weights so they can broadcast across the RGB/BGR channels
        # shape goes from (new_h, new_w) to (new_h, new_w, 1)
        dx = np.expand_dims(dx, axis=2)
        dy = np.expand_dims(dy, axis=2)
        
        # Apply the bilinear interpolation equation
        # Multiply each corner pixel by its corresponding area weight
        out_img = (Ia * (1 - dx) * (1 - dy) +
                   Ib * dx * (1 - dy) +
                   Ic * (1 - dx) * dy +
                   Id * dx * dy)
        
        # Convert the resulting floats back to standard 8-bit color integers
        return out_img.astype(img.dtype)
    else:
        # np.round() ensures we actually get the nearest pixel before casting to int
        x_round = np.round(src_x).astype(int)
        y_round = np.round(src_y).astype(int)
    
        # np.clip ensures that floating point rounding doesn't push us out of array bounds
        x_round = np.clip(x_round, 0, old_w - 1)
        y_round = np.clip(y_round, 0, old_h - 1)
    
        # Advanced NumPy indexing to fetch all the mapped pixels
        return img[y_round, x_round]

def get_cubic_weight(x: np.ndarray, a: float = -0.5) -> np.ndarray:
    '''Calculates the bicubic weight for a given distance x.
    Refer to https://en.wikipedia.org/wiki/Bicubic_interpolation#Bicubic_convolution_algorithm'''
    # a = -0.5 is the standard constant defined by Keys
    abs_x = np.abs(x)
    abs_x2 = abs_x ** 2
    abs_x3 = abs_x ** 3
    
    # Initialize an array of zeros with the same shape as x
    w = np.zeros_like(x)
    
    # Condition 1: Distance is less than or equal to 1
    mask1 = abs_x <= 1
    w[mask1] = (a + 2) * abs_x3[mask1] - (a + 3) * abs_x2[mask1] + 1
    
    # Condition 2: Distance is between 1 and 2
    mask2 = (abs_x > 1) & (abs_x < 2)
    w[mask2] = a * abs_x3[mask2] - 5 * a * abs_x2[mask2] + 8 * a * abs_x[mask2] - 4 * a
    
    # Distances greater than 2 have a weight of 0 (already set by np.zeros_like)
    return w

def resize_bicubic(image_path: str, target_ratio: float):
    '''given the image path and the desired ratio, resize using bicubic interpolation'''
    img = cv2.imread(image_path)
    
    if img is None:
        print(f"Error: Could not load image at {image_path}")
        return None
    
    old_h, old_w, channels = img.shape
    
    # Calculate new dimensions based on the target ratio
    new_h = int(old_h * target_ratio)
    new_w = int(old_w * target_ratio)
    
    # Create the grid of new coordinates   
    yy, xx = np.indices((new_h, new_w))
    
    # Map the NEW coordinates BACK to the OLD coordinates (Backward Warping)
    src_x = xx / target_ratio
    src_y = yy / target_ratio
    
    # Get the integer base coordinates (top-left of the inner 2x2 grid)
    x_floor = np.floor(src_x).astype(int)
    y_floor = np.floor(src_y).astype(int)
    
    # Get the fractional distances
    dx = src_x - x_floor
    dy = src_y - y_floor
    
    # Add a third axis to the weights so they can broadcast across the RGB/BGR channels
    # shape goes from (new_h, new_w) to (new_h, new_w, 1)
    dx = np.expand_dims(dx, axis=2)
    dy = np.expand_dims(dy, axis=2)
    
    # Initialize the output image accumulator
    out_img = np.zeros((new_h, new_w, channels), dtype=np.float32)
    
    # Loop over the 4x4 neighborhood (-1, 0, 1, 2)
    for j in range(-1, 3):
        for i in range(-1, 3):
            # Calculate the cubic weights for X and Y axes
            # Distance from target decimal to this specific neighboring pixel
            wx = get_cubic_weight(dx - i)
            wy = get_cubic_weight(dy - j)
            
            # The final 2D weight is the product of the 1D X and Y weights
            weight = wx * wy
            
            # Get the coordinates of the neighboring pixel, clamping to image edges
            px = np.clip(x_floor + i, 0, old_w - 1)
            py = np.clip(y_floor + j, 0, old_h - 1)
            
            # Multiply the pixel color by its weight and add to the accumulator
            out_img += img[py, px] * weight
            
    # Bicubic interpolation can result in values slightly outside [0, 255] (overshoot/ringing)
    # We must clip the values back to the valid color range before casting
    out_img = np.clip(out_img, 0, 255)
    
    return out_img.astype(img.dtype)

def rotate(image_path: str, target_deg: float, isBilinear: bool = True):
    '''given the image path and the desired rotation degree (in clockwise), return the crop-to-fit rotated image'''
    img = cv2.imread(image_path)
    
    if img is None:
        print(f"Error: Could not load image at {image_path}")
        return None
    
    # Get image dimensions
    H, W = img.shape[:2]
    
    # Create an empty black canvas with the same dimensions
    out_img = np.zeros_like(img)
    
    # Convert degrees to radians for numpy trig functions
    theta = np.radians(target_deg)
    cos_theta = np.cos(theta)
    sin_theta = np.sin(theta)
    
    # Define the center of rotation
    cx, cy = W / 2.0, H / 2.0
    
    # Create a coordinate grid for the output image
    yy, xx = np.indices((H, W))
    
    # Now, Map the NEW coordinates BACK to the OLD coordinates (Backward Warping)
    # Shift output coordinates so the origin is at the center of the image
    src_xx = xx - cx
    src_yy = yy - cy
    
    # Rotation: originally, the inverse of clockwise is:
    # X' = Xcos - Ysin
    # Y' = Xsin - Ycos
    # But since the Y-axis in image space points downwards, ALL sin operation needs a minus sign
    src_x = src_xx * cos_theta + src_yy * sin_theta
    src_y = -src_xx * sin_theta + src_yy * cos_theta
    
    # Shift coordinates back to the top-left origin
    src_x = src_x + cx
    src_y = src_y + cy
    
    # interpolation
    if isBilinear:
        # Get the integer coordinates for the 4 surrounding pixels
        x_floor = np.floor(src_x).astype(int)
        y_floor = np.floor(src_y).astype(int)
        
        # Create a mask to filter out coordinates where the base point lands outside the image bounds
        valid_mask = (x_floor >= 0) & (x_floor < W) & (y_floor >= 0) & (y_floor < H)
        
        # Extract the valid floor coordinates
        x_floor = x_floor[valid_mask]
        y_floor = y_floor[valid_mask]
        
        # Calculate ceiling coordinates, clipping to max image boundaries to prevent out-of-bounds
        x_ceil = np.clip(x_floor + 1, 0, W - 1)
        y_ceil = np.clip(y_floor + 1, 0, H - 1)
        
        # Advanced NumPy indexing to fetch the pixel for all 4 corners
        Ia = img[y_floor, x_floor]   # Top-Left
        Ib = img[y_floor, x_ceil]  # Top-Right
        Ic = img[y_ceil, x_floor]  # Bottom-Left
        Id = img[y_ceil, x_ceil]  # Bottom-Right
        
        # Calculate the fractional distances for interpolation weights
        dx = src_x[valid_mask] - x_floor
        dy = src_y[valid_mask] - y_floor
        
        # Add a third axis to the weights so they can broadcast across the RGB/BGR channels
        # shape goes from (H, W) to (H, W, 1)
        dx = dx[:, np.newaxis]
        dy = dy[:, np.newaxis]
        
        # Apply the bilinear interpolation equation
        # Multiply each corner pixel by its corresponding area weight
        interpolated_pixels = (Ia * (1 - dx) * (1 - dy) +
                               Ib * dx * (1 - dy) +
                               Ic * (1 - dx) * dy +
                               Id * dx * dy)
        
        # Map the valid interpolated pixels to our output canvas
        out_img[yy[valid_mask], xx[valid_mask]] = interpolated_pixels
        
        return out_img
    else:
        src_x = np.round(src_x).astype(int)
        src_y = np.round(src_y).astype(int)
        
        # Create a mask to filter out coordinates that land outside the bounds of the original image
        valid_mask = (src_x >= 0) & (src_x < W) & (src_y >= 0) & (src_y < H)

        # Map the valid pixels from the source image to our output canvas
        out_img[yy[valid_mask], xx[valid_mask]] = img[src_y[valid_mask], src_x[valid_mask]]
    
        return out_img