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
 * Based on the yolo example from AlexeyAB
 */
#include <atomic>
#include <mutex>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <vector>

#include <fstream>
#include <thread>
#include <time.h>
#include <sys/time.h>
#include <condition_variable>

//OpenCV Headers
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>

//Zed headers
#include <sl/Camera.hpp>

#define OPENCV  //Enable OpenCV for yolo
#include "libraries/yolo/yolo_v2_class.hpp" //yolo cpp wrapper

#include "vision.h"
#include "data_logging.h"

using namespace std;
//using namespace cv;

// Initialize the ZED Camera
sl::Camera zed;
sl::Mat cur_frame_zed;
sl::Mat cur_cloud;

// Initialize fps counter
struct timeval t1, t2;
int fps = 0;
unsigned int cone_num = 0;

//create a log file to hold cone dist
log_file cone_log_file(true);

cv::VideoWriter video_out;

//Convert sl mat to opencv mat (provided by stereolabs)
cv::Mat slMat2cvMat(sl::Mat &input) {
	// Mapping between MAT_TYPE and CV_TYPE
	int cv_type = -1;
	switch (input.getDataType()) {
	case sl::MAT_TYPE_32F_C1:
		cv_type = CV_32FC1;
		break;
	case sl::MAT_TYPE_32F_C2:
		cv_type = CV_32FC2;
		break;
	case sl::MAT_TYPE_32F_C3:
		cv_type = CV_32FC3;
		break;
	case sl::MAT_TYPE_32F_C4:
		cv_type = CV_32FC4;
		break;
	case sl::MAT_TYPE_8U_C1:
		cv_type = CV_8UC1;
		break;
	case sl::MAT_TYPE_8U_C2:
		cv_type = CV_8UC2;
		break;
	case sl::MAT_TYPE_8U_C3:
		cv_type = CV_8UC3;
		break;
	case sl::MAT_TYPE_8U_C4:
		cv_type = CV_8UC4;
		break;
	default:
		break;
	}
	return cv::Mat(input.getHeight(), input.getWidth(), cv_type, input.getPtr<sl::uchar1>(sl::MEM_CPU));
}

//draw an isosceles triangle on a using  x,y,w,h values
void triangle(cv::Mat mat_img,int x, int y, int w, int h , cv::Scalar color){

	cv::line(mat_img,cv::Point((x+w/2),(y)),cv::Point((x),(y+h)),color,3,8,0);
	cv::line(mat_img,cv::Point((x+w/2),(y)),cv::Point((x+w),(y+h)),color,3,8,0);
	cv::line(mat_img,cv::Point((x),(y+h)),cv::Point((x+w),(y+h)),color,3,8,0);
}

//draw the cones on the result and display it
void draw_cones(cv::Mat mat_img, vector<bbox_t> result_vec, vector<cone_t> &rDist_vec , vector<string> obj_names, unsigned int wait_msec = 0) {

	cv::Scalar color;
	cv::Scalar fpscolor(215, 20, 107);

	int cone_i = 0;
	for (auto &i : result_vec) {

		// check cone color
		if(rDist_vec[cone_i].cone_type == ORANGE_S){
			color = cv::Scalar(102, 178, 255);
		}
		else if(rDist_vec[cone_i].cone_type == ORANGE_L){
			color =  cv::Scalar(0, 128, 255);
		}
		else if(rDist_vec[cone_i].cone_type == YELLOW){
			color = cv::Scalar(0, 204, 204);
		}
		else if(rDist_vec[cone_i].cone_type == BLUE){
			color = cv::Scalar(255, 0, 0);
		}
		//basically counts cones
		if(i.track_id > cone_num){
			cone_num = i.track_id;
		}

		// Mark cone with triangle
		triangle(mat_img,i.x,i.y,i.w,i.h,color);

		//tracking id and distance
		if(i.track_id >= 0)
			cv::putText(mat_img, "x: " + to_string(int(rDist_vec[cone_i].cone_cordinates.x)) +
					"[mm]"
					, cv::Point2f(i.x+i.w+5, i.y + i.h), cv::FONT_HERSHEY_DUPLEX, 0.43, color);
		cv::putText(mat_img, "y: "  + to_string(int(rDist_vec[cone_i].cone_cordinates.y)) + "[mm]"
				, cv::Point2f(i.x+i.w+5, i.y + i.h-18), cv::FONT_HERSHEY_DUPLEX, 0.43, color);

		//only print up to 2 digits for probability
		stringstream stream;
		stream << fixed << setprecision(2) << i.prob;
		string probString = stream.str();
		cone_i++;
	}
	cv::putText(mat_img, "Cones: "+to_string(cone_num), cv::Point2f(mat_img.cols-220, 22), cv::FONT_HERSHEY_DUPLEX, 1, fpscolor,2);
	cv::putText(mat_img, "FPS: "+to_string(fps), cv::Point2f(0,22), cv::FONT_HERSHEY_DUPLEX , 1, fpscolor,2);
	cv::imshow("Detector View", mat_img);
	cv::waitKey(wait_msec);
}

//Print the results
void show_result(vector<bbox_t> const result_vec, vector<cone_t> &rDist_vec , vector<string> const obj_names) {
	int cone_i = 0;
	for (auto &i : result_vec) {
		if (obj_names.size() > i.obj_id) cout << obj_names[i.obj_id] << " - ";
		cout <<"FPS: "<<fps<< ", obj_id = " << i.obj_id<< ", id = "<< i.track_id<< ",  x = " << i.x << ", y = " << i.y
				<< ", w = " << i.w << ", h = " << i.h
				<< setprecision(3) << ", prob = " << i.prob <<", dist x: " << rDist_vec[cone_i].cone_cordinates.x << " [mm]"
				<<", dist y: " << rDist_vec[cone_i].cone_cordinates.y << " [mm]"<< endl;
		cone_i++;
	}
}

//parse object names
vector<string> objects_names_from_file(string const filename) {
	ifstream file(filename);
	vector<string> file_lines;
	if (!file.is_open()) return file_lines;
	for(string line; file >> line;) file_lines.push_back(line);
	cout << "object names loaded \n";
	return file_lines;
}

// get median center distance coordinates from cone in [mm]
// note that ZED's Z is our X and zeds X is our Y
float4 dist_median(int x, int y, int k){

	vector<float> vals_x;
	vector<float> vals_y;

	vals_x.clear();
	vals_y.clear();

	sl::float4 point3D; ;
	int cur_x = x - k;
	int cur_y = y - k;

	//iterating to find the median
	while (cur_x != x + k){
		if (cur_x >= 0){
			while(cur_y != y+k){
				if (cur_y >= 0){
					cur_cloud.getValue(cur_x,cur_y,&point3D);
					if(std::isfinite(point3D.x)){
						vals_x.push_back(point3D.x);

					}
					if(std::isfinite(point3D.z)){
						vals_y.push_back(point3D.z);
					}
				}
				cur_y++;
			}
			cur_y = y - k;
			cur_x++;
		}

	}

	float4 median;
	if (!vals_x.empty() && !vals_y.empty()){
		sort(vals_x.begin(),vals_x.end());
		sort(vals_y.begin(),vals_y.end());
		median.x = vals_x[int((vals_x.size()/2))];
		median.y = vals_y[int((vals_y.size()/2))];
	}
	else{
		median.x = 0;
		median.y = 0;
	}

	return median;



}

// get distance from cones
void detect_cones_distance(vector<bbox_t> &rResult_vec, vector<cone_t> &rDist_vec , vector<string> const obj_names){
	rDist_vec.clear();
	for (auto &box : rResult_vec) {
		cone_t cur_cone;

		// set cone type
		cur_cone.cone_type = box.obj_id;
		//cone tracking id
		cur_cone.tracking_id = box.track_id;

		// Estimated cone midpoint in pixels
		int cone_x_pix = box.x + (box.w)/2;
		int cone_y_pix = box.y + 2*(box.h)/3; //The thickest part of the cone is at the base

		// get the median value for cone distance
		float4 cone_cor = dist_median(cone_x_pix, cone_y_pix, 10);
		cur_cone.cone_cordinates.x = cone_cor.x;
		cur_cone.cone_cordinates.y = cone_cor.y;


		//add the cone to our result vector
		rDist_vec.push_back(cur_cone);

	}
}

std::mutex data_lock;
cv::Mat cur_frame_cv;
std::vector<bbox_t> result_vect;
std::atomic<bool> exit_flag, new_data;
vector<bbox_t> result_vec;

//Paths
string cfg_path = "yolov3-tiny_3l-cones.cfg";
string weights_path = "yolov3-tiny_3l-cones_last.weights";
string names_path = "obj.names";


void detectorThread(vector<cone_t> &rDist_vec, bool write_video) {
	// prevent yolo thread from running
	data_lock.lock();
	//Confidence threshold
	float confThreshold = 0.6;

	//Initialize the detector
	auto obj_names = objects_names_from_file(names_path);
	Detector detector(cfg_path,weights_path);
	std::shared_ptr<image_t> det_image;
	cv::Size const frame_size = cur_frame_cv.size();

	//Create a capture session
	detector.nms = 0.02;
	data_lock.unlock();

	//detect objects in frames with threshold over confThreshold
	while (!exit_flag) {
		if (new_data) {
			data_lock.lock();
			det_image = detector.mat_to_image_resize(cur_frame_cv);

			result_vec = detector.detect_resized(*det_image, frame_size.width, frame_size.height, confThreshold, false);
			result_vec = detector.tracking_id(result_vec); // add tracking id to the vector
			detect_cones_distance(result_vec,rDist_vec, obj_names);
			cone_log_file.write_rows_to_file(rDist_vec);
			//stop timer
			gettimeofday(&t2, NULL);
			//calculate fps
			fps =1/((t2.tv_usec - t1.tv_usec)/pow(10,6)) ;
			// print results{
			show_result(result_vec,rDist_vec, obj_names);
			data_lock.unlock();
			new_data = false;
		} else sl::sleep_ms(1);
	}
}


//TODO: TESTING
//detect the cones and their distances each frame and update rDist_vec
uint8_t detect_cones(vector<cone_t> &rDist_vec, bool write_video){
	auto obj_names = objects_names_from_file(names_path);
	int wait_ms = 20; //How long to wait before previewing each frame in [ms]


	if (zed.grab() == SUCCESS) {
		// A new image is available if grab() returns SUCCESS
		zed.retrieveImage(cur_frame_zed,sl::VIEW_LEFT); // Retrieve the left image
		zed.retrieveMeasure(cur_cloud, sl::MEASURE_XYZRGBA,sl:: MEM_CPU); //Retrieve
		slMat2cvMat(cur_frame_zed).copyTo(cur_frame_cv);
		std::string col_names = "Type, ID, x [mm] , y [mm]";
		cone_log_file = log_file("cone_log", col_names);

		//Setup writing video if enabled
		if (write_video == true){
			//Open the output video
			string output_file_path = "yolo-zed.avi";
			cv::Size const frame_size = cur_frame_cv.size();
			video_out.open(output_file_path, cv::VideoWriter::fourcc('M','J','P','G'), 28, frame_size);
		}

		exit_flag = false;
		new_data = false;
		//cout << "Image grabbed!" << endl;

	}
	else{
		cout << "Error retrieving frame" << endl;
	}
	std::thread detect_thread(detectorThread,std::ref(rDist_vec), write_video);

	//Start processing the frames
	while(!exit_flag) {
		//start timer
		gettimeofday(&t1, NULL);
		if (zed.grab() == SUCCESS) {
			// A new image is available if grab() returns SUCCESS
			zed.retrieveImage(cur_frame_zed,sl::VIEW_LEFT); // Retrieve the left image
			data_lock.lock();
			cur_frame_cv = slMat2cvMat(cur_frame_zed);
			zed.retrieveMeasure(cur_cloud, sl:: MEASURE_XYZRGBA,sl:: MEM_CPU); //Retrieve distance
			data_lock.unlock();
			new_data = true;

			//record video
			if (write_video == true){
				//draw the cones
				draw_cones(cur_frame_cv, result_vec,rDist_vec , obj_names, wait_ms);
				//write out to file
				video_out.write(cur_frame_cv);
			}
			//cout << "Image grabbed!" << endl;

		}
		else{
			cout << "Error retrieving frame" << endl;
			break;
		}

		data_lock.unlock();
		new_data = true;
	}
	if (write_video == true){
		video_out.release();
	}

	detect_thread.join();
	zed.close();
	return SUCCESS;
}

// Initialize the ZED Camera
uint8_t init_zed_cam(){
	sl::InitParameters init_params;
	init_params.camera_resolution = sl::RESOLUTION_VGA;
	init_params.camera_fps = 0; // highest possible framerate
	init_params.depth_mode = sl::DEPTH_MODE_ULTRA; // Use ULTRA depth mode
	init_params.coordinate_units = sl::UNIT_MILLIMETER;// Coordinates in [mm]
	sl::ERROR_CODE err;
	err = zed.open(init_params);
	if (err != SUCCESS){
		cout <<"Cannot open ZED:" << sl::toString(err) << endl;
		return FAILED;

	}
	sl::Mat cur_frame_zed(zed.getResolution(), sl::MAT_TYPE_8U_C4);
	return SUCCESS;
}
