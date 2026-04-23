# Image Processing – HW2

Author: 11703040 游宗諺

Completion Date: 2026/04/24

[[The Report of the result in PDF]](https://github.com/bscny/college/blob/main/4th_grade/hw_image_processing-2/hw2/report.pdf)

## Table of Content

- [Set-up Steps](#set-up-steps)
- [File Structures](#file-structures)

## Set-up Steps

1. Install the requirements by `pip install -r requirements.txt`
2. For each question, refer to their corresponding python file. (for example, question 1 --> `q1.py`)
3. It's easy to see that except question 1 and 6, all logic is implemented in `/src`. Please refer to that together with the comments.
4. For all the result, refer to the `result` folder. Notice that in q4, there's no specific instruction on the value of `alpha`. Therefore, I tried both (alpha = 0.5 and 2). "boost" means that `alpha` is smaller than 1 (boosts low-probability bins) and vice versa.

## File Structures

```
.
├── result
│   ├── q1
│   │   ├── boundary.tif
│   │   └── repaired.tif
│   ├── q2
│   │   └── aerialView_contrast_stretch.tif
│   ├── q3
│   │   ├── aerialView_GHE.tif
│   │   └── einstein_GHE.tif
│   ├── q4
│   │   ├── dark_adaptive_gamma_boost.png
│   │   └── dark_adaptive_gamma_suppress.png
│   ├── q5
│   │   ├── mean_partition.tif
│   │   └── median_partition.tif
│   └── q6
│       └── CVCE.tif
├── src
│   ├── contrast_stretching_helper.py
│   └── histogram_equal_helper.py
├── q1.py
├── q2.py
├── q3.py
├── q4.py
├── q5.py
├── q6.py
├── README.md
├── requirements.txt
├── aerialview-washedout.tif
├── dark.png
├── einstein-low-contrast.tif
└── text-broken.tif
```