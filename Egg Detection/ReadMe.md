# Egg Detection

## Assignment Context

This is the last assignment of the Fundamental Image Processing course.

## Project Overview

The goal is to estimate the number of eggs in a plate image (including partial eggs, such as `1.5`).

The assignment provides 10 plate images and expects a solution that generalizes beyond those exact examples (different egg positions, sizes, and colors).

## Requirements Summary

- First, segment the eggs from the input image.
- Segmentation can use any method covered in the course.
- Egg counting must be based on **morphology**.
- Implement the solution as a MATLAB script named `A3_StudentID.m`.

## Expected Output

Running the script should produce:
1. **Figure 1**: intermediate steps of the algorithm
2. **Figure 2**: final segmented image with the estimated egg count in the title

## Function Components

The submission should include:
- A segmentation function (input: original image, output: segmented image)
- A counting function (input: segmented image, output: estimated egg count)
