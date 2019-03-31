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
 * 2019 Tel-Aviv university formula student team, Gal Zaidenstein.
 */
#include "data_logging.h"
#include <chrono>
#include <string>
#include <ctime>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define GetCurrentDir getcwd

// get working directory
std::string GetCurrentWorkingDir( void ) {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}

// checks if file exists
inline bool exists (std::string filename) {
  struct stat buffer;
  return (stat (filename.c_str(), &buffer) == 0);
}

//Create a new log file
log_file::log_file(std::string filename, std::string col_names){

	// check if the logs directory exists, if not create it
	std::string path = GetCurrentWorkingDir();
	path.append("/logs/");
	struct stat st = {0};
	if (stat(path.c_str(), &st) == -1) {
	    mkdir(path.c_str(), 0700);
	}
	//set log file date
	auto cur_time = std::chrono::system_clock::now();
	std::time_t date = std::chrono::system_clock::to_time_t(cur_time);

	// create log file with name
	 new_filename = path;
	 new_filename.append(filename);
	 new_filename.append("-");
	 new_filename.append(std::ctime(&date));
	 new_filename.append(".csv");

	 //if log file name exists create B version
	 if(exists(new_filename)){
		 new_filename = path;
		 new_filename.append(filename);
		 new_filename.append("-");
		 new_filename.append(std::ctime(&date));
		 new_filename.append("B");
		 new_filename.append(".csv");
	 }
	 logfile.open(new_filename);
	 // set filename as title
	 logfile << (std::ctime(&date)) << "," << "\n";
	 logfile << col_names << "," << "\n";
	 logfile.close();

}

log_file::log_file(bool empty){

}

//TODO: create overloaded functions for different data types for logging

void log_file::write_rows_to_file(std::vector<cone_t> &rDist_vec){
	logfile.open(new_filename);
	struct timeval timestamp;
	gettimeofday(&timestamp, NULL);
	if(!rDist_vec.empty()){
		logfile << timestamp.tv_usec << " [ms] ," << "\n";
		for (auto &res : rDist_vec) {
			logfile << std::to_string(res.cone_type) << "," << res.tracking_id << "," <<
					res.cone_cordinates.x << "," << res.cone_cordinates.y << "," << "\n";
		}
	}
	logfile.close();
}
