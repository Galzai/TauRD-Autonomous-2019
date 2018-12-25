/*
 * tcp_client.h
 *
 *  Created on: Nov 25, 2018
 *      Author: gal
 */

#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_

#define FAILED -1
#define SUCCESS 1

// Struct for holding control parameters
struct control_cmd_t{
    float throttle = 0; /* 1 to -1 */
    float steering = 0; /* 1 to -1 */
    float brake = 0;    /* 1 to -1 */
    bool handbrake = false;
    bool is_manual_gear = false;
    int manual_gear = 0;
    bool gear_immediate = true;

};
/*
 * @brief initialize connection to the simulation environment
 * @return SUCCESSS if filtering performed correctly
 * */
uint8_t init_connection();

/*
 * @brief send control signal
 * @param [input] values for the desired commnad (see struct)
 * @return SUCCESSS if filtering performed correctly
 * */
uint8_t send_control(control_cmd_t controls);

/*
 * @brief receive image ,gps , imu data etc
y
 * */
void recieve_data(void);



#endif /* TCP_CLIENT_H_ */
