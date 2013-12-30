# Nimble

## What is it?

An unfinished sprite engine (2d game engine) that was written partially for my uni classes, partially as a side project.

The goal was to devise a flexible, modular architecture which didn't get into the programmers way, letting him focus on the game mechanics.

It was written in a very short amount of time so it does not represent the quality of code that I am capable of producting.

It may be useful as an example. The code that retesellates polygons in order to divide them into convex ones may be of interest to some.

## Building the source

You need the `scons` build system as well as some libraries in dev version:
* SDL
* SDL_image
* GL
* GLEW

The scons targets are:
* lib - builds the library
* examples - builds the examples
* all - builds all of the aforementioned

By default the library is built as a shared library. If you want the static version use `--static-library` switch with scons.

The debug build (with debug symbols) can be obtained by using the `--debug-build' switch.

### tl;dr

Just type `scons all` in the project dir and examine the bin subdir.





