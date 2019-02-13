/*
 * tcp_client.h
 *
 *  Created on: Nov 25, 2018
 *      Author: gal
 */

#ifndef TCP_CLIENT_H_
#define TCP_CLIENT_H_



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
 * @brief initialize connection to the simulation environment for receiving images
 * @return SUCCESSS if connected succesfully
 * */
uint8_t init_rcv_image_connection();

/*
 * @brief initialize connection to the simulation environment for sending commands
 * @return SUCCESSS if filtering performed correctly
 * */
uint8_t init_send_connection();

/*
 * @brief initialize connection to the simulation environment receiving sensor data
 * @return SUCCESSS if filtering performed correctly
 * */
uint8_t init_sensor_connection();

/*
 * @brief send control signal
 * @param [input] values for the desired commnad (see struct)
 * @return SUCCESSS if filtering performed correctly
 * */
uint8_t send_control(control_cmd_t controls);

/*
 * @brief capture an image from the simulator
 * */
cv::Mat sim_capture_image(void);

/*
 * @brief get gps coordinates
 * */
uint8_t sim_get_gps_data(void);

/*
 * @brief get imu data
 * */
uint8_t sim_get_imu_data(void);

/*
 * @brief get magnetometer
 * */
uint8_t sim_get_magnetometer_data(void);

/*
 * @brief get imu data
 * */
uint8_t sim_get_real_data(void);

/*
 * @brief used for testing the client function
 * */
int client_tester(void);




#endif /* TCP_CLIENT_H_ */
