/*
 * mapping.h
 *
 *  Created on: Dec 4, 2018
 *      Author: gal
 */

#ifndef MAPPING_H_
#define MAPPING_H_
#include "data_structs.h"

/*
 * @brief initialize sensors, cameras communication
 * @param [input] testMode set to true to connect to simulator, otherwise connect to vehicle
 * @return return SUCCESS if Initialized correctly
  */
uint8_t init_mapping();

/*
 * @brief write the local map to local map
 * @param [output] pLocal_map  adresss to write the map to
 * @return SUCCESS if local map returned succesfully
 * */
//uint8_t get_local_map(map_t *pLocal_map);

/*
 * @brief start mapping the track
 * @param [output] pGlobal_map address to write the map to
 * @return SUCCESS if mapping started correctly
 *
 */
void start_track_mappping(void);

/*
 * @brief stop mapping the track
 * @return return SUCCESS if track mapping cannot stop
 *
 */
uint8_t stop_track_mappping(void);

void init_zero_point();






#endif /* MAPPING_H_ */
