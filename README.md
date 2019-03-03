# gnoise
GPU Accelerated C++ Noise Library. 

A modified version of [libnoise](http://libnoise.sourceforge.net/).

QuickNoise utilizes [OpenCL](https://www.khronos.org/opencl/) to paralellize and speed up computing of many noise values at once or multithreaded CPU computing if your computer does not have OpenCL compatible GPU or CPU.

### Features
- Perlin Noise 1D, 2D, 3D, 4D
- Billow Noise 1D, 2D, 3D, 4D
- RidgedMultifractal Noise 1D, 2D, 3D, 4D
- Voronoi Noise 1D, 2D, 3D, 4D
- Basic Noise Generators (Checkerboard, Spheres, Circles, Const)
- Modifiers (same as in libnoise)
