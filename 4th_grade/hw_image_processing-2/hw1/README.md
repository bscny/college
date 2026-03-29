# Image Processing – HW1

Author: 11703040 游宗諺

Completion Date: 2026/3/29

[[The Report of the result in PDF]](https://github.com/bscny/college/blob/main/4th_grade/hw_image_processing-2/hw1/report.pdf)

## Table of Content

- [Set-up Steps](#set-up-steps)
- [File Structures](#file-structures)

## Set-up Steps

1. Install the requirements by `pip install -r requirements.txt`
2. For question 1, refer to `combine.py` and  `src/lib_1.py`. To get the result, simply `py combine.py`
3. For question 2, refer to `linear_transform.py` and  `src/lib_2.py`. To get the result, simply `py linear_transform.py`
4. For question 3, refer to `nonlinear_transform.py`. To get the result, simply `py nonlinear_transform.py`
5. For all the result, refer to the `result` folder. Note that in q2, "nni" stands for Nearest Neighbor Interpolation, "bi" stands for Bilinear Interpolation, and "bci" stands for Bicubic Interpolation

## File Structures

```
.
├── result
│   ├── q1
│   │   └── lena_merged.bmp
│   ├── q2
│   │   ├── enlarge_130_bi.bmp
│   │   ├── enlarge_130_nni.bmp
│   │   ├── rotate_30_bi.bmp
│   │   ├── rotate_30_nni.bmp
│   │   ├── shrink_60_bci.bmp
│   │   ├── shrink_80_bi.bmp
│   │   └── shrink_80_nni.bmp
│   └── q3
│       └── rectified.png
├── src
│   ├── lib_1.py
│   └── lib_2.py
├── combine.py
├── linear_transform.py
├── nonlinear_transform.py
├── README.md
├── lena.bmp
├── lena_cropped.bmp
├── lena_left.bmp
└── stop-sign.png
```