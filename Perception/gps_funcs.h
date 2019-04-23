/*
 * gps_funcs.h
 *
 *  Created on: Apr 11, 2019
 *      Author: tau-rd
 */

#ifndef GPS_FUNCS_H_
#define GPS_FUNCS_H_

#include "data_structs.h"

#define RADIANS_TO_DEGREES (180.0/M_PI)
#define GPS_PORT "/dev/ttyUSB0"
#define BAUD_RATE 115200
#define DECODE_SUCCES 0
#define DECODE_FAILURE 1

/*
 * @start the gps data gathering loop
 */
int run_gps_loop();

/*
 * @brief get complete vehicle state data from gps
 * @NOTE: GPS loops must be running in order to call function!
 */
vehicle_state_t get_vehicle_state();


//flag for indicating GPS fix (1 for not fixed, 0 for fixed)
int gps_fix();

#endif /* GPS_FUNCS_H_ */
