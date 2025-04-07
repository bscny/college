# 2025 Computer Graphics HW4

Author: 111703040 游宗諺

## Table of content

- [Build Instruction](#build-instructions)
- [Progress](#progress)
- [Summary to the modified code](#summary-to-the-modified-code)
- [Issue](#issue)

## Build Instructions

1. `cd build`
2. `make`
3. `./rast`

## Progress

- [x] BresenhamLine
- [x] swTriangle
- [x] swInitZbuffer / swClearZbuffer
- [x] my bonus
    - [x] finish random Z value for each vertices
    - [x] finish `swgl.cpp`

## Summary to the Modified Code

1. `BresenhamLine`
2. `swTriangle`
    - `fill_topflat_triangle`
    - `fill_bottomflat_triangle`
3. `swInitZbuffer` / `swClearZbuffer`
    - modify `writepixel` to enable z-buffer
4. In `hw-rast.cpp`
    1. RANDOM_MODE:
        - toggle Global Variable `RANDOM_MODE` to enable random triangles and lines each display
        - if `RANDOM_MODE` == `false`, only print 3 triangles in the order of red(smallest z value), green(mid z value), blue(biggest z value). 
    2. RANDOM_Z:
        - toggle Global Variable `RANDOM_Z` to enable random Z value for each vertices
    3. USE_DEFAULT_LOOK_AT:
        - toggle Global Variable `USE_DEFAULT_LOOK_AT` to test different `gluLookAt` in order to see how Orthographic Projection affects Z-buffer
        - note that I do modify `glOrtho`'s left, right in order to have the correct clip space
        - I prepared 2 `gluLookAt` to show case:
            1. gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0) as default
            2. gluLookAt(0, 0, 0, 0, 0, 1, 0, 1, 0) as test case
    4. In `softPath1`, focus on line 308 ~ 310 and 319 ~ 321
        1. ProjectionMat, ViewMat and TransformMat are Identy Matrix, I didn't use them yet
        2. there's a multiplier "FLAG" before z values (I will explain it in issue 1)

## Issue

<details>
<summary>2025-04-07</summary>

### status

- [ ] solved
- [x] asked

### detail explanation

try the folloeing 2 situation:

1. `RANDOM_MODE = flase` && `RANDOM_Z = false` && `USE_DEFAULT_LOOK_AT = true`
2. `RANDOM_MODE = flase` && `RANDOM_Z = false` && `USE_DEFAULT_LOOK_AT = flase` (this one might take some time. I'm using RTX 3060ti, still took me about 3 seconds)

now, notice that on line 425 we switch signs, let's walk through why we can reder the triangles correctly in this way.

take a look at `swgl.cpp` line: 146 ~ 149 and 198 ~ 201. Now, if we use `gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0)` (default), we have ViewMatrix:
```
1 0 0 0
0 1 0 0
0 0 1 0
0 0 0 1
```
and ProjectionMatrix:
```
a 0 0 dx
0 b 0 dy
0 0 c 0
0 0 0 1
```
where a, b are some positive float numbers, and c is a **negative** float number. Since c makes the final z value negative, and I suppose OpenGL "draw" the pixals after clip space is achieved. Therefore, we can see this red under green under blue "Bizzard" situation.

Now, lets switch to `gluLookAt(0, 0, 0, 0, 0, 1, 0, 1, 0)` (test case), we have:

ViewMatrix:
```
-1 0 0  0
0  1 0  0
0  0 -1 0
0  0 0  1
```
and ProjectionMatrix:
```
a 0 0 dx
0 b 0 dy
0 0 c 0
0 0 0 1
```
where a, b are some positive float numbers, and c is a **negative** float number. However this time, c and the `-1` in ViewMatrix makes the final z value positive. Therefore, we can see this red above green above blue "Normal" situation.

After I observed this, I want to use custom ViewMatrix and custom ProjectionMatrix to generalize the usecase. Then, **Problem** occurs, notice that in `swgl-rast.cpp` `writepixel` function, we use the real (x, y) to draw. However, after the transformation, we are in clip space. In other words, (x, y) are all between -1 and 1.

Q: How to make the general expression of this?

### solution

TBD

### log

- 2025-04-08, asked

</details>