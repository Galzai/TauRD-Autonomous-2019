/*
 * vision.h
 *
 *  Created on: Dec 4, 2018
 *      Author: gal
 */

#ifndef VISION_H_
#define VISION_H_

#include "data_structs.h"
#include <vector>
/*
 * @brief initialize vision sensors
 * @param [input] testMode set to true to connect to simulator, otherwise connect to vehicle
 * @return SUCCESS if Initialized correctly
  */
uint8_t init_vision(bool testMode);

/*
 * @brief initialize zed camera
 * */
uint8_t init_zed_cam();

/*
* @brief detect cone bounding boxes via darknet
* @param [output] rResult_vec vector to hold all the bounding boxes
* @param [input] write_video - set to 1 if you would like to record detection video
 */
uint8_t detect_cones(bool write_video);

/*
* @brief handle case of flag start/stop cones
* @param [output] pLap_counter pointer to the lap counter
 */
uint8_t flag_cone_detected(uint8_t *pLap_counter);

/*
* @brief start cone detection
* @param [output] pCone_counter pointer to the cone counter
 */
uint8_t start_detection(uint8_t *pCone_counter);
/*
* @brief get current distance vector
* @return distance vector
 */
std::vector<cone_t> get_dist_vec(void);

#endif /* VISION_H_ */
