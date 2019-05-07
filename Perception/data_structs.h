/*
 * data_structs.h
 *
 *  Created on: Dec 13, 2018
 *      Author: gal
 */

#ifndef DATA_STRUCTS_H_
#define DATA_STRUCTS_H_

#include <stdint.h>
#include <vector>
#include <string>
/*
 * define success and failure codes
 */
#define FAILED -1
#define SUCCESS 0

/*
 * define cone types
 */
#define ORANGE_L 0 // large orange cone
#define ORANGE_S 1 // small orange cone
#define YELLOW 2 // yellow cone
#define BLUE 3 // blue cone

/*
 * @brief data type for holding coordinates
 */
struct coordinates_t{

	float x; // x coordinate [mm]
	float y; // y coordinate [mm]

};
struct abs_coordinates_t{

	float northing; //  northing [mm]
	float easting; //  easting [mm]

};
/*
 * @brief data type for holding cone information
 */
struct cone_t{

	uint8_t cone_type; /// cone type
	coordinates_t cone_cordinates; // cone x,y coordinates [mm]
	int tracking_id;  // cone tracking id
};

struct abs_cone_t{

	uint8_t cone_type; /// cone type
	abs_coordinates_t abs_cone_cordinates; // cone   latitude and  longitude coordinates [deg]
	coordinates_t cone_cordinates; // cone x,y coordinates [mm]
	int tracking_id;  // cone tracking id
};


/*
 * @brief data type for holding sensor data
 */
struct vehicle_state_t{

	float angular_acc_x; //x angular acceleration [radian/s^2]
	float angular_acc_y; //y angular acceleration [radian/s^2]
	float angular_acc_z; //z angular acceleration [radian/s^2]

	float angular_vel_x; //x angular velocity [radian/s]
	float angular_vel_y; //y angular velocity [radian/s]
	float angular_vel_z; //z angular velocity [radian/s]

	float linear_velocity_x; // vehicle velocity in [m/s]
	float linear_velocity_y; // vehicle velocity in [m/s]

	float linear_acc_x;  //x linear acceleration [meter/s^2]
	float linear_acc_y; //y linear acceleration [meter/s^2]

	coordinates_t coordinates; //coordinates retrieved from gps

	float heading; //heading angle [radian]
};

/*
 * @brief data type for cone mapping
 */
typedef std::vector <abs_cone_t> map_t;


#endif /* DATA_STRUCTS_H_ */
