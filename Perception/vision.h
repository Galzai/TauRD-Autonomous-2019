/*
 * vision.h
 *
 *  Created on: Dec 4, 2018
 *      Author: gal
 */

#ifndef VISION_H_
#define VISION_H_

/*
 * @brief initialize vision sensors
 * @param [input] testMode set to true to connect to simulator, otherwise connect to vehicle
 * @return SUCCESS if Initialized correctly
  */
uint8_t init_vision(bool testMode);

/*
* @brief detect cone bounding boxes via darknet
* @param [output] pResult_vec vector to hold all the bounding boxes (pixels)
 */
uint8_t detect_cones(vector<bbox_t> const *pResult_vec);

/*
* @brief detect cone bounding boxes via darknet
* @param [input] pResult_vec vector to hold all the bounding boxes
* @param [output] pResult_vec vector to hold all the cones
 */
uint8_t detect_cones_distance(vector<bbox_t> const *pResult_vec, vector<cone_t> const *pDist_vec);

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


#endif /* VISION_H_ */
