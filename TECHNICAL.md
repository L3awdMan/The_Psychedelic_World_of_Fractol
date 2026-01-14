<p align="center">
  <em>"The Mandelbrot set is the most complex mathematical object known to mankind."</em>
  <br>
  — Arthur C. Clarke
</p>

# Fractol - Technical Documentation

**A deep dive into the mathematics and implementation behind the psychedelic fractal visualizer.**

This document details the architectural decisions, mathematical formulas, and rendering techniques used to generate the fractal imagery. It covers the coordinate systems, the continuous coloring algorithms, and the optimization strategies employed.

---

## Table of Contents

1. [The Zooming Mechanism](#the-zooming-mechanism)
   - [Coordinate System Mapping](#coordinate-system-mapping)
   - [The Point-Centered Zoom Algorithm](#the-point-centered-zoom-algorithm)
   - [Dynamic Detail Adjustment](#dynamic-detail-adjustment)

2. [Color Rendering System](#color-rendering-system)
   - [Continuous Coloring (Anti-Aliasing)](#continuous-coloring-anti-aliasing)
   - [Procedural Palette Generation](#procedural-palette-generation)
   - [Depth and Intensity](#depth-and-intensity)

3. [Project Architecture](#project-architecture)
   - [Core State Management](#core-state-management)
   - [The Rendering Pipeline](#the-rendering-pipeline)


---

## The Zooming Mechanism

The zooming system is the core interactive component of a fractal explorer. It allows users to traverse the mathematical structure from a macro view down to microscopic details. This implementation utilizes a **point-centered zoom** approach, ensuring that the specific point under the mouse cursor remains stationary on the screen while the world scales around it.

### Coordinate System Mapping

To render a fractal, we must map the **Pixel Grid** (screen space) to the **Complex Plane** (mathematical space).

- **Screen Space:** Defined by integer coordinates `(x, y)`, where `(0, 0)` is usually the top-left corner.
- **Complex Space:** Defined by continuous coordinates `(re, im)`, where the center is `(cx, cy)`.

The application uses a `t_view` structure to manage this translation:

```c
typedef struct s_view
{
    double  cx;     // Center X (Real component)
    double  cy;     // Center Y (Imaginary component)
    double  scale;  // Units per pixel (Distance in complex plane covered by 1 pixel)
    int     max_it; // Iteration limit (Quality/Depth)
}   t_view;
```

**The Mapping Formula**

To convert a screen pixel to a complex number, we calculate the offset of that pixel from the screen center, scale it to mathematical units, and add it to the current view center.

```
real      = cx + (x - WIDTH/2) * scale
imaginary = cy - (y - HEIGHT/2) * scale
```

*Note: The Y-axis is inverted (subtracted) because screen coordinates increase downward, while the Cartesian Y-axis increases upward.*

### The Point-Centered Zoom Algorithm

When the user scrolls the mouse wheel, the goal is to zoom in "towards" the mouse pointer. This requires three distinct steps performed in the `zoom_at_point()` function:

1. **Capture the Anchor:** Before any scaling occurs, we calculate the exact complex coordinate that lies beneath the mouse cursor. This point serves as the anchor.
2. **Apply the Scale:** We modify the `scale` value. Dividing the scale by a factor greater than 1.0 reduces the units-per-pixel, effectively "zooming in."
3. **Shift the Center:** To keep the anchor point stationary on the screen, the center of the view must move towards the mouse.

**The Mathematical Logic**

The new center is calculated by taking the vector from the mouse to the old center, scaling that vector down, and re-applying it to the mouse position:

```
new_scale  = old_scale / zoom_factor
new_center = mouse_point + (old_center - mouse_point) / zoom_factor
```

Visually, this causes the center of the screen to slide closer to the mouse cursor as you zoom in, maintaining the relative position of the fractal features.

### Dynamic Detail Adjustment

As the view zooms deeper, the boundary of the fractal becomes more complex. To resolve these fine details, the escape-time algorithms require more processing passes. The `calculate_optimal_iterations` function dynamically increases the iteration limit (`max_it`) based on the current zoom level. This balances performance at shallow zoom levels with visual fidelity at deep zoom levels.

```c
int calculate_optimal_iterations(double scale)
{
    double zoom_level = 1.0 / scale;
    
    if (zoom_level < 1.0)    return 50;
    if (zoom_level < 10.0)   return 80;
    if (zoom_level < 100.0)  return 120;
    if (zoom_level < 1000.0) return 200;
    return 300;
}
```

---

## Color Rendering System

The coloring pipeline transforms raw mathematical data (how many iterations it took for a point to escape) into aesthetic visuals. This project moves beyond basic integer banding to create smooth, gradient-based renderings.

### Continuous Coloring (Anti-Aliasing)

Standard fractal rendering counts iterations as integers (e.g., 50, 51, 52). This results in distinct "bands" of color with sharp edges. To achieve smooth gradients, we calculate a fractional iteration count.

This is achieved using a renormalization technique. By analyzing the magnitude of the complex number (`|z|`) after it escapes the threshold, we can mathematically estimate how far "past" the threshold it went.

The formula used is:

```
smooth_iter = iter + 1 - log₂(log₂(|z|))
```

In code:
```c
double calculate_smooth_iteration(double z_re, double z_im, int iter)
{
    double log_magnitude = log(z_re * z_re + z_im * z_im) / 2.0;
    double smoothed_value = log(log_magnitude / log(2.0)) / log(2.0);
    return (iter + 1 - smoothed_value);
}
```

This produces a continuous value (e.g., 50.45) rather than a discrete integer, allowing for smooth color interpolation.

### Procedural Palette Generation

Rather than using large static arrays of color data, the application generates colors mathematically using cosine waves. This allows for infinite, cyclic gradients that transition smoothly.

The "Cosine Palette" technique computes Red, Green, and Blue channels independently using the formula:

```
channel = 0.5 + 0.5 * cos(2π * (t + phase))
```

By offsetting the phases of the R, G, and B channels (typically by 0.0, 0.33, and 0.66), we create a rainbow-like spectrum that loops seamlessly. 

```c
unsigned int cosine_palette(double t, int mode)
{
    double phase = mode * 0.3;
    double r = 0.5 + 0.5 * cos(2.0 * M_PI * (t + phase));
    double g = 0.5 + 0.5 * cos(2.0 * M_PI * (t + phase + 1.0/3.0));
    double b = 0.5 + 0.5 * cos(2.0 * M_PI * (t + phase + 2.0/3.0));
    return (rgb_to_int(r, g, b));
}
```

The `psychedelic_palette` function increases the frequency of these waves (using `16.0 * M_PI` instead of `2.0 * M_PI`), causing the colors to cycle rapidly over short distances, creating an intense visual effect.

### Depth and Intensity

To give the 2D image a sense of 3D structure, an intensity curve is applied. Points that take longer to escape (closer to the fractal set) are rendered darker, while points that escape quickly are brighter.

```c
intensity = 1.0 - exp(-0.030 * smooth_iter);
```

This exponential decay creates a "glow" around the fractal edge and helps visually separate the complex structures from the background.

---

### Core State Management

The application state is encapsulated in the `t_app` structure. Key components include:

- **MLX Pointers:** Handles for the graphics library and window.
- **Image Buffer:** A pixel array where the fractal is drawn before being pushed to the window.
- **View State:** Stores the current zoom level (`scale`) and coordinates (`cx`, `cy`).
- **Fractal Parameters:** Stores variable inputs like the Julia set constants (`c_re`, `c_im`).
```

### The Rendering Pipeline

The rendering process follows a linear pipeline for every frame:

``` 
```
┌─────────────────────────────────────────────────────────────┐
│                    RENDERING PIPELINE                       │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  1. PIXEL ITERATION                                         │
│     └─> Loop through every (x, y) coordinate on canvas      │
│                                                             │
│  2. COORDINATE MAPPING                                      │
│     └─> Convert (x, y) to complex number (re, im)           │
│                                                             │
│  3. ESCAPE CALCULATION                                      │
│     └─> Run fractal algorithm → get smooth iteration count  │
│                                                             │
│  4. COLORIZATION                                            │
│     └─> Map iteration to RGB using palette + intensity      │
│                                                             │
│  5. BUFFERING                                               │
│     └─> Write color to image memory                         │
│                                                             │
│  6. PRESENTATION                                            │
│     └─> Push image buffer to window(mlx_put_image_to_window)│
│                                                             │
└─────────────────────────────────────────────────────────────┘
```
``` 

```
---
