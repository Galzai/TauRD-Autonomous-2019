/****************************************************************/
/*                                                              */
/*          Advanced Navigation Packet Protocol Library         */
/*          C Language Dynamic Spatial SDK, Version 4.0         */
/*   Copyright 2014, Xavier Orr, Advanced Navigation Pty Ltd    */
/*                                                              */
/****************************************************************/
/*
 * Copyright (C) 2014 Advanced Navigation Pty Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Modified By Gal Zaidenstein, Tuval Jacob and Noam Dahan 2019 Tel-Aviv university.
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <math.h>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "libraries/gps/rs232/rs232.h"
#include "libraries/gps/an_packet_protocol.h"
#include "libraries/gps/spatial_packets.h"
#include "gps_funcs.h"

using namespace std;

int No_fix = 1;

bool loop_flag = false; // flag to indicate gps loops is running
vehicle_state_t cur_vehicle_state; //hold kinematic data


//Indicate if gps is fixed

int gps_fix(){
	return No_fix;
}
//get complete vehicle state packet
vehicle_state_t get_vehicle_state(){
	if(!loop_flag){
		std::cout << "Warning: Loop not initialized!" << std::endl;
	}

	return cur_vehicle_state;
}

//send packet to gps
int an_packet_transmit(an_packet_t *an_packet)
{
	an_packet_encode(an_packet);
	return SendBuf(an_packet_pointer(an_packet), an_packet_size(an_packet));
}

/*
 * This is an example of sending a configuration packet to Spatial.
 *
 * 1. First declare the structure for the packet, in this case sensor_ranges_packet_t.
 * 2. Set all the fields of the packet structure
 * 3. Encode the packet structure into an an_packet_t using the appropriate helper function
 * 4. Send the packet
 * 5. Free the packet
 */
void set_sensor_ranges()
{
	an_packet_t *an_packet;
	sensor_ranges_packet_t sensor_ranges_packet;

	sensor_ranges_packet.permanent = TRUE;
	sensor_ranges_packet.accelerometers_range = accelerometer_range_4g;
	sensor_ranges_packet.gyroscopes_range = gyroscope_range_500dps;
	sensor_ranges_packet.magnetometers_range = magnetometer_range_2g;

	an_packet = encode_sensor_ranges_packet(&sensor_ranges_packet);

	an_packet_transmit(an_packet);

	an_packet_free(&an_packet);
}

//get  cartesian position packet from gps
int get_position_packet_cartesian(an_packet_t *an_packet, ecef_position_packet_t *ecef_position_packet)
{

	if (decode_ecef_position_packet(ecef_position_packet, an_packet) == DECODE_SUCCES)
		return DECODE_SUCCES;
	else
		return DECODE_FAILURE;

}

//get angular acceleration packet from gps
int get_ang_accl_state_packet(an_packet_t *an_packet, angular_acceleration_packet_t *angular_acceleration_packet)
{

	if (decode_angular_acceleration_packet(angular_acceleration_packet, an_packet) == DECODE_SUCCES)
		return DECODE_SUCCES;
	else
		return DECODE_FAILURE;
}


//get  system state packet from gps
int get_system_state_packet(an_packet_t *an_packet, system_state_packet_t *system_state_packet)
{
	
	if (decode_system_state_packet(system_state_packet, an_packet) == DECODE_SUCCES)
		return DECODE_SUCCES;
	else
		return DECODE_FAILURE;
}

//set the desired rate for the ecef packets
void set_ecef_packet_rate()
{
	an_packet_t *an_packet;
	packet_periods_packet_t ecef_rate_packet;

	ecef_rate_packet.clear_existing_packets = 0;
	ecef_rate_packet.permanent = 1;
	ecef_rate_packet.packet_periods[0].packet_id = packet_id_ecef_position;
	ecef_rate_packet.packet_periods[0].period = MAXIMUM_PACKET_PERIODS;

	an_packet = encode_packet_periods_packet(&ecef_rate_packet);

	an_packet_transmit(an_packet);

	an_packet_free(&an_packet);
}


//set the desired rate for the angular acc packets
void set_angular_acc_packet_rate()
{
	an_packet_t *an_packet;
	packet_periods_packet_t acc_rate_packet;

	acc_rate_packet.clear_existing_packets = 0;
	acc_rate_packet.permanent = 1;
	acc_rate_packet.packet_periods[0].packet_id = packet_id_angular_acceleration;
	acc_rate_packet.packet_periods[0].period = MAXIMUM_PACKET_PERIODS;

	an_packet = encode_packet_periods_packet(&acc_rate_packet);

	an_packet_transmit(an_packet);

	an_packet_free(&an_packet);
}

//start the the gps loop
int run_gps_loop()
{
	an_decoder_t an_decoder;
	an_packet_t *an_packet, *an_packet_request;

	system_state_packet_t system_state_packet;
	raw_sensors_packet_t raw_sensors_packet;

	ecef_position_packet_t ecef_position_packet;
	angular_acceleration_packet_t angular_acceleration_packet;

	vehicle_state_t vehicle_state_buf; //hold kinematic data

	int bytes_received;
	int loop_entered = 0;
	/* open the com port */
	if (OpenComport((char*)GPS_PORT, BAUD_RATE))
	{
		printf("Could not open serial port\n");
		exit(EXIT_FAILURE);
	}
	
	an_decoder_initialise(&an_decoder);


	while(No_fix == 1)
	{ 
		if ((bytes_received = PollComport(an_decoder_pointer(&an_decoder), an_decoder_size(&an_decoder))) > 0)
		{
			an_decoder_increment(&an_decoder, bytes_received);

			while ((an_packet = an_packet_decode(&an_decoder)) != NULL)
			{
				if (an_packet->id == packet_id_system_state) /* system state packet */
				{
					if (decode_system_state_packet(&system_state_packet, an_packet) == 0)
					{
					//printf("No fix yet:\n");
						if (system_state_packet.filter_status.b.gnss_fix_type == 2)
						{
							No_fix = 0;
						}
						//printf("GNSS FIX STATUS: %d\n", system_state_packet.filter_status.b.gnss_fix_type);
						an_packet_free(&an_packet);
					}
				}
			}
		}
	}

	//Initialize requests for desired packets
	set_angular_acc_packet_rate();
	loop_flag = true;
	while (1)
	{
		loop_entered = 1;

		if ((bytes_received = PollComport(an_decoder_pointer(&an_decoder), an_decoder_size(&an_decoder))) > 0)
		{
			/* increment the decode buffer length by the number of bytes received */
			an_decoder_increment(&an_decoder, bytes_received);
			
			/* decode all the packets in the buffer */
			while ((an_packet = an_packet_decode(&an_decoder)) != NULL)
			{
				if (an_packet->id == packet_id_system_state) /* system state packet */
				{

					if (get_system_state_packet(an_packet, &system_state_packet) == DECODE_SUCCES){
						//angular velocities
						vehicle_state_buf.angular_vel_x = system_state_packet.angular_velocity[0];
						vehicle_state_buf.angular_vel_y = system_state_packet.angular_velocity[1];
						vehicle_state_buf.angular_vel_z = system_state_packet.angular_velocity[2];
						//linear velocities
						vehicle_state_buf.linear_velocity_x = system_state_packet.velocity[0];
						vehicle_state_buf.linear_velocity_y = system_state_packet.velocity[1];

						//linear acceleration
						vehicle_state_buf.linear_acc_x = system_state_packet.body_acceleration[0];
						vehicle_state_buf.linear_acc_y = system_state_packet.body_acceleration[0];

						//heading
						vehicle_state_buf.heading = system_state_packet.orientation[2];

						 //position
						vehicle_state_buf.coordinates.x = system_state_packet.latitude * 1000; //coordinates in [mm]
						vehicle_state_buf.coordinates.y = system_state_packet.longitude * 1000; //coordinates in [mm]
						//printf("\tRoll = %f, Pitch = %f, Heading = %f\n", system_state_packet.orientation[0] * RADIANS_TO_DEGREES, system_state_packet.orientation[1] * RADIANS_TO_DEGREES, system_state_packet.orientation[2] * RADIANS_TO_DEGREES);
					}
					else{
						//printf("Couldn't decode system state packet\n");
					}
				}

				else if (an_packet->id == packet_id_angular_acceleration)
				{
					//write ecef data variable
					if (get_ang_accl_state_packet(an_packet, &angular_acceleration_packet) == DECODE_SUCCES){
						vehicle_state_buf.angular_acc_x = angular_acceleration_packet.angular_acceleration[0]; //hold kinematic data
						vehicle_state_buf.angular_acc_y = angular_acceleration_packet.angular_acceleration[1]; //hold kinematic data
						vehicle_state_buf.angular_acc_z = angular_acceleration_packet.angular_acceleration[2]; //hold kinematic data
						//printf("\tPosition X: %f Y: %f\n", ecef_position_packet.position[0], ecef_position_packet.position[1]);
					}
					else{
						//printf("Couldn't decode angular acceleration  packet\n");
					}
				}


				else
				{
					//printf("Packet ID %u of Length %u\n", an_packet->id, an_packet->length);
				}
				
				/* Ensure that you free the an_packet when your done with it or you will leak memory */
				an_packet_free(&an_packet);
				cur_vehicle_state = vehicle_state_buf;
			}
		}
#ifdef _WIN32
    Sleep(10);
#else
    usleep(10000);
#endif
	}
}
