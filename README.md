# Birch.Cairo package

Birch language wrapper for the [Cairo](https://www.cairographics.org/)
2d graphics library. Currently provides a limited subset of the
functionality of the library.


## Installation

To build, use:

    birch build
    
To install system wide, use:

    birch install


## Usage

To use `Birch.Cairo` from another Birch package, firstly modify its `META.json` file as follows:

* `requires.header`: add `birch_cairo.bih` and `birch_cairo.hpp`,
* `requires.library`: add `birch_cairo`.

This will add checks for `Birch.Cairo` during build.

Basic usage then looks something like this:

    surface:Surface <- createPNG(file, width, height);
    cr:Context <- create(surface);

    /* paint a black background */
    cr.setSourceRGB(0.0, 0.0, 0.0);
    cr.paint();

    /* draw a white rectangle */
    cr.setSourceRGB(1.0, 1.0, 1.0);
    cr.rectangle(0.25*width, 0.25*height, 0.5*width, 0.5*height);
    cr.fill();
  
    /* clean up */
    cr.destroy();
    surface.destroy();

Usage idioms are preserved from Cairo itself. See the Cairo documentation for more details, and the `Birch.Cairo` package documentation (or code) for the subset of functionality provided.


## Version history

### v0.0.0

* First version.
