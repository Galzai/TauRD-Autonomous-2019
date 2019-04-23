/*
 * utils.cpp
 *
 *  Created on: Apr 23, 2019
 *      Author: tau-rd
 */


#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <math.h>
#include <string>

//Overloaded functions for printing struct
void print_struct (coordinates_t coor){
	std::cout << "->Coordinate data:" << std::endl;
	std::cout << "  X: " << coor.x <<  " Y: " << coor.y << "[mm]" << std::endl;

}

void print_struct (cone_t cone){

	std::cout << "Cone data:" << std::endl;
	std::cout << "->Type: " << cone.cone_type << std::endl;
	std::cout << "->Tracking Id: " << cone.cone_type << std::endl;
	print_struct(cone.cone_cordinates);

}

void print_struct (vehicle_state_t vehicle_state){
	std::cout << "Vehicle State:" << std::endl;
	std::cout << "-> Angular acceleration:" << std::endl;
	std::cout << " X: " << vehicle_state.angular_acc_x <<
		" Y: " << vehicle_state.angular_acc_y <<
		" Z: " << vehicle_state.angular_acc_z << " [radian/s^2]" << std::endl;

	std::cout << "-> Angular velocity:" << std::endl;
	std::cout << " X: " << vehicle_state.angular_vel_x <<
		" Y: " << vehicle_state.angular_vel_y <<
		" Z: " << vehicle_state.angular_vel_z << " [radian/s]" << std::endl;

	std::cout << "-> Linear velocity:" << std::endl;
	std::cout << " X: " << vehicle_state.linear_velocity_x <<
		" Y: " << vehicle_state.linear_velocity_y <<
		" [m/s]" << std::endl;

	std::cout << "-> Linear acceleration:" << std::endl;
	std::cout << " X: " << vehicle_state.linear_acc_x <<
		" Y: " << vehicle_state.linear_acc_y <<
		" [m/s^2]" << std::endl;

	print_struct(vehicle_state.coordinates);
	std::cout << " ->Heading: " << vehicle_state.heading << " [radian]" <<std::endl;




}

void print_struct (map_t map);




