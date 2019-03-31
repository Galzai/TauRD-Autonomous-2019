# Tel-Aviv university's formula student driverless 
This is the repository for the initial version of Tel-Aviv university's formula student driverless vehicle.  
Currently work in progress and has not been fully tested.

## Requirements  
-Stereolabs ZED for vision related features  
-Advanced navigation's spatial for odometry

## Prerequesites  
Please make sure all the libraries are properly linked before building.   

### yolov3-tiny  
Install the [CUDA toolkit](https://developer.nvidia.com/cuda-downloads) and [cuDNN](https://developer.nvidia.com/cudnn).  
Install and build [darknet](https://github.com/AlexeyAB/darknet#how-to-compile-on-linux)  
Make sure you have OpenCV installed and properly linked in your build environment.  

Add libdarknet.so and the cuda libraries to your library path:  
export LD_LIBRARY_PATH=/usr/local/cuda-10.0/lib64:$LD_LIBRARY_PATH  
export LD_LIBRARY_PATH= "PATH-TO-YOUR-libdarknet.so"   

### Zed sdk
Install the [Stereolab's Zed sdk](https://www.stereolabs.com/developers/release/) for your platform.  

## Current features 
- Data retrieval from AirSim via TCP for alogrith testing:  
  Need to add distance from cone detection from AirSim  

- Cone detection:  
  Tested and working , neural detection net is currently not fully traind.  

- Cone distance estimation:   
  Implemented distance detection using zed camera (Tested and working, accuracy not yet tested) 
  Added data logging
  Added draw_cones (python script  to display cones relative to car)
  Need to add distance detection from AirSim.  

# TO-DO   
- Better documentation
- GPS Handing (In progress)
- IMU Handling (In progress)
- Data Filtering (In progress)
- Mapping(In progress)
- Controlller communication
- "Sensor thread manager"
- RaceLine functions

