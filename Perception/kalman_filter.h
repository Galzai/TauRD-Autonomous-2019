/*
 * kalman_filter.h
 *
 *  Created on: Dec 4, 2018
 *      Author: gal
 */

#ifndef KALMAN_FILTER_H_
#define KALMAN_FILTER_H_


/*
 * @brief filter sensor data to retrieve cordinates
 *
 * @param [input] sensorData - pass the current sensor readings to the filter
 * @param [output] pCur_cordinates address of the value to update the coordinates to
 * @return SUCCESSS if filtering performed correctly
 * */
uint8_t kalman_filter(sensor_data_t sensorData, coordinates_t *pCur_coordinates);



#endif /* KALMAN_FILTER_H_ */
