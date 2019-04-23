/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 * Made by Gal Zaidenstein, Tuval Jacob and Noam Dahan 2019 Tel-Aviv university..
*/

#include "mapping.h"
#include "vision.h"
#include "gps_funcs.h"
#include <time.h>
#include <thread>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include "utils.h"

vehicle_state_t zero_state = { 0 }; //Starting vehicle data

//Start mapping
uint8_t init_mapping(){

	//Initialize ZED Camera
	init_zed_cam();

	//Initialize Camera thread
	std::vector<cone_t> dist_vec;

	std::thread detect_thread(detect_cones,std::ref(dist_vec),true);
	sleep(2);
	//Initialize GPS thread
	std::thread gps_thread(run_gps_loop);

	detect_thread.join();
	gps_thread.join();

}

//Get initial position
void init_zero_point()
{
	while(gps_fix() == 1){
		std::cout << "Waiting for GPS fix" <<std::endl;
	}
	vehicle_state_t curr_state = { 0 };
	vehicle_state_t avg_state = { 0 };

	sleep(1);
	time_t initial_time = clock();	//get initial time
	for(int i=0;i<1000;i++){
		curr_state=get_vehicle_state();

		avg_state.angular_acc_x += curr_state.angular_acc_x;
		avg_state.angular_acc_y += curr_state.angular_acc_y;
		avg_state.angular_acc_z += curr_state.angular_acc_z;

		avg_state.angular_vel_x += curr_state.angular_vel_x;
		avg_state.angular_vel_y += curr_state.angular_vel_y;
		avg_state.angular_vel_z += curr_state.angular_vel_z;

		avg_state.linear_velocity_x += curr_state.linear_velocity_x;
		avg_state.linear_velocity_y += curr_state.linear_velocity_y;

		avg_state.linear_acc_x += curr_state.linear_acc_x;
		avg_state.linear_acc_y += curr_state.linear_acc_y;

		avg_state.coordinates.x += curr_state.coordinates.x;
		avg_state.coordinates.y += curr_state.coordinates.y;

		avg_state.heading += curr_state.heading;
	}

	zero_state.angular_acc_x = (avg_state.angular_acc_x / 1000);
	zero_state.angular_acc_y = (avg_state.angular_acc_y / 1000);
	zero_state.angular_acc_z = (avg_state.angular_acc_z / 1000);

	zero_state.angular_vel_x = (avg_state.angular_vel_x / 1000);
	zero_state.angular_vel_y = (avg_state.angular_vel_y / 1000);
	zero_state.angular_vel_z = (avg_state.angular_vel_z / 1000);

	zero_state.linear_velocity_x = (avg_state.linear_velocity_x / 1000);
	zero_state.linear_velocity_y = (avg_state.linear_velocity_y / 1000);

	zero_state.linear_acc_x = (avg_state.linear_acc_x / 1000);
	zero_state.linear_acc_y = (avg_state.linear_acc_y / 1000);

	zero_state.coordinates.x = (avg_state.coordinates.x / 1000);
	zero_state.coordinates.y = (avg_state.coordinates.y / 1000);

	zero_state.heading = (avg_state.heading / 1000);

	print_struct(zero_state);


}
