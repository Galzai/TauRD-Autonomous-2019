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
#include <cmath>
#include "data_logging.h"

vehicle_state_t zero_state = { 0 }; //Starting vehicle data
log_file map_log_file(true);

//Start mapping
uint8_t init_mapping() {

	//Initialize ZED Camera
	init_zed_cam();
	//Initialize Camera thread
	std::thread detect_thread(detect_cones, true); //using the global dist_vec
	usleep(5000);
	std::string col_names = "Type, ID, easting [mm] , northing [mm]";
	map_log_file = log_file("map_log", col_names);
	sleep(2);
	//Initialize GPS thread
	std::thread gps_thread(run_gps_loop);
	usleep(5000);
	std::thread mapping_thread(start_track_mappping);

	//start_track_mappping();
	detect_thread.join();
	gps_thread.join();
	mapping_thread.join();

}

float get_radius(coordinates_t point) {
	float radius;
	radius = sqrt(point.x * point.x + point.y * point.y);
	return radius;
}

float get_radius(abs_coordinates_t point) {
	float radius;
	radius = sqrt(
			point.easting * point.easting + point.northing * point.northing);
	return radius;
}

float MIN_DIST_RL = 400.0; //minimum distance between cones [mm]
void start_track_mappping() {

	vehicle_state_t vehicle_state_buf;
	abs_cone_t abs_cone_pose;

	time_t time = clock();
	map_t right_cone_vector;
	map_t left_cone_vector;
	map_t complete_map;
	int left_flag = 0, right_flag = 0;
	init_zero_point();

	while (gps_fix() == 1) {
		std::cout << "Waiting for GPS fix" << std::endl;
	}
	usleep(5000);
	while (1) {
		complete_map.clear();
		//get the gps coordinate ;
		vehicle_state_buf = get_vehicle_state();
		std::vector<cone_t> cur_dist_vec = get_dist_vec();

		for (auto &cone : cur_dist_vec) {

			abs_cone_pose.cone_cordinates = cone.cone_cordinates;

			abs_cone_pose.abs_cone_cordinates.easting =
					vehicle_state_buf.coordinates.x
							+ cone.cone_cordinates.y
									* cos(vehicle_state_buf.heading)
							- cone.cone_cordinates.x
									* sin(vehicle_state_buf.heading)
							- zero_state.coordinates.x;

			abs_cone_pose.abs_cone_cordinates.northing =
					vehicle_state_buf.coordinates.y
							+ cone.cone_cordinates.y
									* sin(vehicle_state_buf.heading)
							+ cone.cone_cordinates.x
									* cos(vehicle_state_buf.heading)
							- zero_state.coordinates.y;

			abs_cone_pose.cone_type = cone.cone_type;

			abs_cone_pose.tracking_id = cone.tracking_id;

			if (abs_cone_pose.cone_type == BLUE) {
				for(auto &map_cone : left_cone_vector) {
					left_flag = 0;
					if (map_cone.tracking_id == cone.tracking_id) {
						left_flag = 1;
						if (get_radius(map_cone.cone_cordinates)
								> get_radius(cone.cone_cordinates)) {
							map_cone.abs_cone_cordinates.easting =
									0.3 * map_cone.abs_cone_cordinates.easting
											+ 0.7
													* abs_cone_pose.abs_cone_cordinates.easting;

							map_cone.abs_cone_cordinates.northing =
									0.3 * map_cone.abs_cone_cordinates.northing
											+ 0.7
													* abs_cone_pose.abs_cone_cordinates.northing;

							map_cone.cone_cordinates.x = 0.3
									* map_cone.cone_cordinates.x
									+ 0.7 * abs_cone_pose.cone_cordinates.x;

							map_cone.cone_cordinates.y = 0.3
									* map_cone.cone_cordinates.y
									+ 0.7 * abs_cone_pose.cone_cordinates.y;

						} else {
							map_cone.abs_cone_cordinates.easting =
									0.7 * map_cone.abs_cone_cordinates.easting
											+ 0.3
													* abs_cone_pose.abs_cone_cordinates.easting;

							map_cone.abs_cone_cordinates.northing =
									0.7 * map_cone.abs_cone_cordinates.northing
											+ 0.3
													* abs_cone_pose.abs_cone_cordinates.northing;

							map_cone.cone_cordinates.x = 0.7
									* map_cone.cone_cordinates.x
									+ 0.3 * abs_cone_pose.cone_cordinates.x;

							map_cone.cone_cordinates.y = 0.7
									* map_cone.cone_cordinates.y
									+ 0.3 * abs_cone_pose.cone_cordinates.y;
						}
						break;
					}
				}
				if (left_flag == 0) {
					//		second filter - we use the fact the left and right cones are separate and filter by distance
					for(int i = 0; i < left_cone_vector.size(); i++) {
						coordinates_t dist_cord;
						dist_cord.x =
								left_cone_vector[i].abs_cone_cordinates.easting
										- abs_cone_pose.abs_cone_cordinates.easting;
						dist_cord.y =
								left_cone_vector[i].abs_cone_cordinates.northing
										- abs_cone_pose.abs_cone_cordinates.northing;
						float dist = get_radius(dist_cord);
//						std::cout << dist << std::endl;
						if (dist < MIN_DIST_RL) {

								left_cone_vector.erase(
										left_cone_vector.begin() + i);
						}
					}

					left_cone_vector.push_back(abs_cone_pose);

				}

			}
			if (abs_cone_pose.cone_type == YELLOW) {
				for (auto &map_cone : right_cone_vector) {
					right_flag = 0;
					if (map_cone.tracking_id == cone.tracking_id) {
						right_flag = 1;
						if (get_radius(map_cone.cone_cordinates)
								> get_radius(cone.cone_cordinates)) {
							map_cone.abs_cone_cordinates.easting =
									0.3 * map_cone.abs_cone_cordinates.easting
											+ 0.7
													* abs_cone_pose.abs_cone_cordinates.easting;

							map_cone.abs_cone_cordinates.northing =
									0.3 * map_cone.abs_cone_cordinates.northing
											+ 0.7
													* abs_cone_pose.abs_cone_cordinates.northing;

							map_cone.cone_cordinates.x = 0.3
									* map_cone.cone_cordinates.x
									+ 0.7 * abs_cone_pose.cone_cordinates.x;

							map_cone.cone_cordinates.y = 0.3
									* map_cone.cone_cordinates.y
									+ 0.7 * abs_cone_pose.cone_cordinates.y;

						} else {
							map_cone.abs_cone_cordinates.easting =
									0.7 * map_cone.abs_cone_cordinates.easting
											+ 0.3
													* abs_cone_pose.abs_cone_cordinates.easting;

							map_cone.abs_cone_cordinates.northing =
									0.7 * map_cone.abs_cone_cordinates.northing
											+ 0.3
													* abs_cone_pose.abs_cone_cordinates.northing;

							map_cone.cone_cordinates.x = 0.7
									* map_cone.cone_cordinates.x
									+ 0.3 * abs_cone_pose.cone_cordinates.x;

							map_cone.cone_cordinates.y = 0.7
									* map_cone.cone_cordinates.y
									+ 0.3 * abs_cone_pose.cone_cordinates.y;
						}
						break;
					}
				}
				if (right_flag == 0) {
					for(int i = 0; i < right_cone_vector.size(); i++) {
						coordinates_t dist_cord;
						dist_cord.x =
								right_cone_vector[i].abs_cone_cordinates.easting
										- abs_cone_pose.abs_cone_cordinates.easting;
						dist_cord.y =
								right_cone_vector[i].abs_cone_cordinates.northing
										- abs_cone_pose.abs_cone_cordinates.northing;
						float dist = get_radius(dist_cord);

						if (dist < MIN_DIST_RL) {
//							std::cout << dist << std::endl;
								right_cone_vector.erase(
										right_cone_vector.begin() + i);


						}
					}

					right_cone_vector.push_back(abs_cone_pose);

				}
			}
		}
		complete_map.insert(complete_map.end(), right_cone_vector.begin(),
				right_cone_vector.end());
		complete_map.insert(complete_map.end(), left_cone_vector.begin(),
				left_cone_vector.end());
		print_struct(complete_map);
		map_log_file.write_rows_to_file(complete_map); // write the map to a log file
	}


}

//Get initial position
void init_zero_point() {
	while (gps_fix() == 1) {
		std::cout << "Waiting for GPS fix" << std::endl;
	}
	vehicle_state_t curr_state = { 0 };
	vehicle_state_t avg_state = { 0 };

	usleep(5000);
	time_t initial_time = clock();	//get initial time
	for (int i = 0; i < 1000; i++) {
		curr_state = get_vehicle_state();

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
