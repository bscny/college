# 2025 Computer Graphics HW3

Author: 111703040 游宗諺

## Table of content

- [Build Instruction](#build-instructions)
- [Requirements](#requirements)
- [Summary to the modified code](#summary-to-the-modified-code)
- [Issue](#issue)

## Build Instructions

1. `cd build`
2. `make`
3. `./trans`

## Requirements

basic OpenGL Libraries

[if no glut]
$ sudo apt install freeglut3-dev libglew-dev

[if no OpenGL Mathematics (GLM)]
$ sudo apt install libglm-dev

## Summary to the Modified Code

1. model matrix
    - swTranslate
    - swRotate
        - x
        - y
        - z
        - any
    - swScale
2. view matrix
3. projection matrix
4. In swTriangle, 3 steps can be chosen to use
5. In DrawGrid, modify each vertices so we can use our own custom matrix to draw grids (set boolean variable `USE_CUSTOM_MATRIX` to true)
6. In display:
    1. add `USE_CUSTOM_MATRIX` usecase to enable custom matrix on grids
    2. finish step 2 and 3
7. in KeyCallback, finish all key functions

## Issue

<details>
<summary>2025-03-25</summary>

### status

- [ ] solved
- [x] asked

### detail explanation

try the folloeing 3 situation:

1. `STEP2 = true` && `STEP3 = false` && `USE_CUSTOM_MATRIX = true`
2. `STEP2 = true` && `STEP3 = true` && `USE_CUSTOM_MATRIX = true`
3. `STEP2 = true` && `STEP3 = true` && `USE_CUSTOM_MATRIX = false`

From 1. we can see that until step 2, there are no issue, if want to try further, just make `USE_CUSTOM_MATRIX = false`, will be the same

Now **focus on** 2. and 3. We can see all functions are working normally except for the **size**....(建議按 E 12 次，讓四面體往上跑，會大一點方便觀察)

**Notice**: 四面體平移時也與 `gluPerspective` 不同，但是透過 3. 可以發現他依然是在正確座標點上(舉例來說，可以透過按 Q, A 來觀察，四面體雖然一直在 X 軸，但大小會變)，嚴格來說，還是 **size** 問題

### log

- 2025-03-25, asked

</details>
