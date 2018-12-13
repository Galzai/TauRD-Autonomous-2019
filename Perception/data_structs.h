/*
 * data_structs.h
 *
 *  Created on: Dec 13, 2018
 *      Author: gal
 */

#ifndef DATA_STRUCTS_H_
#define DATA_STRUCTS_H_

/*
 * @brief data type for holding coordinates
 */
struct coordinates_t{

	float x; // x coordinate [mm]
	float y; // y coordinate [mm]

};

/*
 * @brief data type for holding cone information
 */
struct cone_t{

	uint8_t cone_type; /// cone type
	coordinates_t cone_cordinates; // cone x,y coordinates [mm]
	int tracking_id;  // cone tracking id
};


/*
 * @brief data type for holding imu data
 */
struct imu_data_t{

};


/*
 * @brief data type for holding sensor data
 */
struct sensor_data_t{

	coordinates_t gps_coordinates; //coordinates retrieved from gps
	imu_data_t imu_data;
	float wheel_rpm;
	float steering_angle; //[radian]
};

/*
 * @brief data type for cone mapping
 */
typedef vector <cone_t> map_t;


#endif /* DATA_STRUCTS_H_ */
