/*
 * cone_filter.h
 *
 *  Created on: Dec 4, 2018
 *      Author: gal
 */

#ifndef CONE_FILTER_H_
#define CONE_FILTER_H_

/*
 * @brief filter cone locations in track
 * @param pGlobal_map pointer to the global map
 * @param pLocal_map pointer to the local map
 * @param pCur_coordinates pointer to the local coordinates
 * @return SUCCESSS if filtering performed correctly
 */
uint8_t cone_filter(map_t *pGloal_map, map_t* pLocal_map, coordinates_t *pCur_coordinates);


#endif /* CONE_FILTER_H_ */
