/*
 * data_logging.h
 *
 *  Created on: Mar 16, 2019
 *      Author: tau-rd
 */

#ifndef DATA_LOGGING_H_
#define DATA_LOGGING_H_
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "data_structs.h"

/*
 * @new class for file logging as csv
 */
class log_file{
private:
	std::string filename;
	std::string new_filename;
	std::vector <std::string> col_names;
	std::ofstream logfile;
public:

	/*
	 * @brief Initialize file
	 * @param [input] filename output file name
	 * @param [input] column names to write to file seperated by commas
	 */
	log_file(std::string filename, std::string col_names);

	log_file(bool  empty);

	/*
	 * @write row to file
	 * @param [input] string of lines to write by order
	 */

	//for distance vector data
	void write_rows_to_file(std::vector<cone_t> &rDist_vec);
	void write_rows_to_file(map_t &cone_map);

};

#endif /* DATA_LOGGING_H_ */
