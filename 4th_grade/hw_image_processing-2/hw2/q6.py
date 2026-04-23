import cv2
import numpy as np

from src.histogram_equal_helper import generate_histogram

def CVCE(image: np.ndarray, w: int) -> np.ndarray:
    H, W = image.shape
    half = w // 2
 
    # Step 1: Construct 2D Normalized Histogram
    h_x = np.zeros((256, 256), dtype=np.float64)

    for k in range(-half, half + 1):
        for l in range(-half, half + 1):
            # Determine valid pixel ranges after shift
            r0_c = max(0, -k);  r1_c = min(H, H - k)
            c0_c = max(0, -l);  c1_c = min(W, W - l)
            r0_n = r0_c + k;    r1_n = r1_c + k
            c0_n = c0_c + l;    c1_n = c1_c + l

            center_vals = image[r0_c:r1_c, c0_c:c1_c]
            neighbor_vals = image[r0_n:r1_n, c0_n:c1_n]

            # Weight = |x_m - x_n| + 1
            weights = np.abs(center_vals.astype(np.int32) - neighbor_vals.astype(np.int32)) + 1

            # Accumulate into h_x using np.add.at (handles repeated indices)
            np.add.at(h_x, (center_vals.ravel(), neighbor_vals.ravel()), weights.ravel())

    # Normalization
    total = h_x.sum()
    if total > 0:
        h_norm = h_x / total
    else:
        h_norm = h_x
        
    # Step 2: Construct 1D CDF
    row_marginal = h_norm.sum(axis=1)
    cdf_x = np.cumsum(row_marginal)
    
    # Step 3: Mapping, histogram specification
    # Create a [1/256, 2/256, ... 256/256] for uniform dist.
    cdf_t = np.arange(1, 256 + 1, dtype=np.float64) / 256
    
    # Create a look up table to map the intensity
    lut = np.arange(256, dtype=np.uint8)
        
    for intensity in range(256):
        # Find i that minimizes |CDF_x(m) - CDF_t(i)|
        diffs = np.abs(cdf_x[intensity] - cdf_t)
        best_i = int(np.argmin(diffs))
        lut[intensity] = best_i
 
    return lut[image]

if __name__ == "__main__":
    image = cv2.imread("aerialview-washedout.tif", cv2.IMREAD_GRAYSCALE)

    if image is None:
        print(f"Error: Could not load the image. Please check the file path.")
    else:
        result_img = CVCE(image, 7)

        generate_histogram(result_img, plot_histogram=True)

        cv2.imwrite("result/q6/CVCE.tif", result_img)
        
        cv2.imshow("Question 6: CVCE", result_img)
        cv2.waitKey(0)
        cv2.destroyAllWindows() 