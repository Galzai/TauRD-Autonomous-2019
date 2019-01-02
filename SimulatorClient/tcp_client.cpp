#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>

#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>

#include "data_structs.h"
#include "tcp_client.h"

using namespace std;

int rcv_sock;
int rcv_port = 54000;

int data_sock;
int data_port = 55000;

int send_sock;
int send_port = 58000;


string ipAddress = "192.168.1.101";


//Split the received data to parse it
vector <string> parse_buf(string buf, string delimiter){
	vector<string> list;
	size_t pos = 0;
	string token;
	while ((pos = buf.find(delimiter)) != string::npos){
		token = buf.substr(0, pos);
		list.push_back(token);
		buf.erase(0, pos+ delimiter.length());
	}
	list.push_back(buf);
	return list;
}
//  Initialize connection to data streaming server
uint8_t init_rcv_image_connection(){

	//	Create a socket
	rcv_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (rcv_sock == FAILED)
	{
		return FAILED;
	}


	//	Create a hint structure for the server we're connecting with
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(rcv_port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	//	Connect to the server on the socket
	int connectRes = connect(rcv_sock, (sockaddr*)&hint, sizeof(hint));
	if (connectRes == FAILED)
	{
		return FAILED;
	}
	//initial handshake
	char confirm_buf[1042];
	int bytesReceived = recv(rcv_sock, confirm_buf, 16192, 0);

	// If an error occurred return an empty cv:Mat
	if(bytesReceived == FAILED){
	}

	else{
		cout << "Connected to image server!" <<endl;
	return SUCCESS;
	}
	return FAILED;
}

//init connection for receiving sensor data
uint8_t init_sensor_connection(){

	//	Create a socket
	data_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (data_sock == FAILED)
	{
		return FAILED;
	}


	//	Create a hint structure for the server we're connecting with
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(data_port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	//	Connect to the server on the socket
	int connectRes = connect(data_sock, (sockaddr*)&hint, sizeof(hint));
	if (connectRes == FAILED)
	{
		return FAILED;
	}
	//initial handshake
	char confirm_buf[1042];
	int bytesReceived = recv(data_sock, confirm_buf, 16192, 0);

	// If an error occurred return an empty cv:Mat
	if(bytesReceived == FAILED){
	}

	else{
		cout << "Connected to sensor server!" <<endl;
	return SUCCESS;
	}
	return FAILED;
}



//  Initialize connection to data streaming server
uint8_t init_send_connection(){

	//	Create a socket
	send_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (send_sock == FAILED)
	{
		return FAILED;
	}


	//	Create a hint structure for the server we're connecting with
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(send_port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	//	Connect to the server on the socket
	int connectRes = connect(send_sock, (sockaddr*)&hint, sizeof(hint));
	if (connectRes == FAILED)
	{
		return FAILED;
	}
	//initial handshake
	char confirm_buf[1042];
	int bytesReceived = recv(send_sock, confirm_buf, 16192, 0);

	// If an error occurred return an empty cv:Mat
	if(bytesReceived == FAILED){
	}
	else{
		cout << "Connected to control server!" <<endl;

	return SUCCESS;
	}
	return FAILED;
}

// capture images from the simulator
cv::Mat sim_capture_image(void){

	cv::Mat rcv_img;
	string buf = "frame";
	int sendRes = send(rcv_sock, buf.c_str(), buf.size()+1, 0);

	// If an error occurred return an empty cv:Mat
	if (sendRes == FAILED)
	{
		cout << "Error requesting image" << endl;
		return rcv_img;
	}
	else{

		char data_buf[16192];
		int bytesReceived = recv(rcv_sock, data_buf, 16192, 0);

		// If an error occurred return an empty cv:Mat
		if(bytesReceived == FAILED){
			cout << "Error requesting image" << endl;
			return rcv_img;

		}
		//If image data was received correctly parse img data and send confirmation
		else{

			// parse the image data
			vector <string> im_data = parse_buf(string(data_buf), ",");
			int width = stoi(im_data[0]);
			int height = stoi(im_data[1]);
			size_t img_size = stoi(im_data[2]);
			//TODO: parse time stamp
			//time_t time_stamp = stol(im_data[3]);
			cout <<  " IMG " << " | Width: " << width << " | Height: "<< height <<" | Size: "<< img_size << " Bytes << endl;

			string ack_buf = "ok";
			sendRes = send(rcv_sock, ack_buf.c_str(), ack_buf.size()+1, 0);

			// If an error occurred return an empty cv:Mat
			if (sendRes == FAILED)
			{
				cout << "Error sending confirmation" << endl;
				return rcv_img;
			}

			// after sending the confirmation start assembling the frame data
			else{

				vector<uint8_t> img_data_f;
				size_t cur_data_size = 0; // hold the current amount of data assembled

				while(cur_data_size < img_size){
					//start receiving the bytes
					char im_buf[16192];
					bytesReceived = recv(rcv_sock, im_buf, 16192, 0);

					if(bytesReceived == FAILED){
						cout << "Error requesting image" << endl;
						return rcv_img;

					}
					else{
						for( int i = 0; i < bytesReceived; i++ ) {
							img_data_f.push_back(im_buf[i]);
							cur_data_size++;
						}
					}

				}

				try{
					rcv_img = cv::Mat(height ,width , CV_8UC4);
					rcv_img = cv::imdecode(img_data_f,cv::IMREAD_UNCHANGED);
				}
				catch(...){
					return rcv_img;

				}


			}

		}
	}


	return rcv_img;

}

// capture images from the simulator
std::vector <sensor_data_t> sim_capture_sensor_data(void){

	sensor_data_t sensorData;
	sensor_data_t realData;

	vector<sensor_data_t> resData = {};
	string buf = "sensor";
	int sendRes = send(data_sock, buf.c_str(), buf.size() +1 , 0);

	// If an error occurred return an empty cv:Mat
	if (sendRes == FAILED)
	{
		cout << "Error requesting sensor data" << endl;
		return resData;
	}
	else{
		char size_buf[1024];
		int bytesReceived = recv(data_sock, size_buf, 1024, 0);

		// If an error occurred return an empty vector
		if(bytesReceived == FAILED){
			cout << "Error requesting data" << endl;
			return resData;

		}
		//If sensor data was received correctly parse it
		else{
			size_t dataSize = stoi(string(size_buf));

			string ack_buf = "ok";
			sendRes = send(data_sock, ack_buf.c_str(), ack_buf.size()+1, 0);

			// If an error occurred return an empty vector
			if (sendRes == FAILED)
			{
				cout << "Error sending confirmation" << endl;
				return resData;
			}

			// after sending the confirmation start assembling the frame data
			else{
				size_t cur_data_size = 0; // hold the current amount of data assembled
				string data_buf_str = "";
				while(cur_data_size < dataSize){
					//start receiving the bytes
					char data_buf[1024];

					bytesReceived = recv(data_sock, data_buf, 1024, 0);

					if(bytesReceived == FAILED){
						cout << "Error requesting image" << endl;
						return resData;

					}
					else{
						for( int i = 0; i < bytesReceived; i++ ) {
							data_buf_str += data_buf[i];

							cur_data_size++;
						}
					}

				}
			// parse the image data
			vector <string> im_data = parse_buf(data_buf_str, ",");
			sensorData.coordinates.x = stof(im_data[0]);
			sensorData.coordinates.y = stof(im_data[2]);
			sensorData.kinematic_data.angular_acc_x = stof(im_data[3]);
			sensorData.kinematic_data.angular_acc_y  = stof(im_data[4]);
			sensorData.kinematic_data.angular_acc_z = stof(im_data[5]);
			sensorData.kinematic_data.linear_acc_x = stof(im_data[6]);
			sensorData.kinematic_data.linear_acc_x = stof(im_data[7]);
			sensorData.lin_velocity = stof(im_data[8]);

			realData.coordinates.x = stof(im_data[9]);
			realData.coordinates.y = stof(im_data[10]);
			realData.kinematic_data.angular_acc_x = stof(im_data[11]);
			realData.kinematic_data.angular_acc_y  = stof(im_data[12]);
			realData.kinematic_data.angular_acc_z = stof(im_data[13]);
			realData.kinematic_data.linear_acc_x = stof(im_data[14]);
			realData.kinematic_data.linear_acc_x = stof(im_data[15]);
			realData.lin_velocity = stof(im_data[16]);


			cout <<  " Sensors " << " | GPS [m]: [" << sensorData.coordinates.x << ", "<< sensorData.coordinates.y << "] " <<""
			"| Angular [radian/s^2]: ["<< sensorData.kinematic_data.angular_acc_x <<", "<< sensorData.kinematic_data.angular_acc_y <<
			", "<< sensorData.kinematic_data.angular_acc_z << "] " << "| Linear [m/s^2]: [" << sensorData.kinematic_data.linear_acc_x << ", "<<
			sensorData.kinematic_data.linear_acc_y <<"]" << "| Velocity [m/s]: "<< sensorData.lin_velocity << endl;
			;
			resData.push_back(sensorData);
			resData.push_back(realData);


			}
		}
	}


	return resData;

}


//  Send the data from the struct to the server
uint8_t send_control(control_cmd_t controls){


	string buf =

			to_string(controls.throttle) + "," +
			to_string(controls.steering) + "," +
			to_string(controls.brake) + "," +
			to_string(controls.handbrake) + "," +
			to_string(controls.is_manual_gear) + "," +
			to_string(controls.manual_gear) + "," +
			to_string(controls.gear_immediate)
			;


	int sendRes = send(send_sock, buf.c_str(), buf.size()+1, 0);
	if (sendRes == FAILED)
	{
		return FAILED;
	}
	return SUCCESS;
}

