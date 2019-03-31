# Tel-Aviv university's formula student driverless 
This is the repository for the initial version of Tel-Aviv university's formula student driverless vehicle.  
Currently work in progress and has not been fully tested.

## CURRENT FEATURES 
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

