import cv2
import numpy as np

def find_first_target_pixel(image_path: str, find_white: bool) -> tuple | None:
    '''give a image path, find the (x, y) of the first find pure white (or non white) pixel from top'''
    # loads images in BGR format by default
    img = cv2.imread(image_path)

    if img is None:
        print(f"Error: Could not load image at {image_path}")
        return None
    
    # Create a mask for pure white pixels
    # np.all(..., axis=-1) ensures we only match pixels where ALL 3 channels are 255.
    white_mask = np.all(img == [255, 255, 255], axis=-1)

    # Find All Target pixels
    if find_white:
        y_coords, x_coords = np.where(white_mask)
    else:
        y_coords, x_coords = np.where(~white_mask)

    # Grab the first one
    if len(y_coords) > 0:
        # Since np.where scans top-to-bottom, the 0th index has the smallest y
        first_y = int(y_coords[0])
        first_x = int(x_coords[0])
        
        return (first_x, first_y)
    else:
        print("No target pixels found in the image.")
        return None