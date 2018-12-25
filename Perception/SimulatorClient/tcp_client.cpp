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

#include "tcp_client.h"

using namespace std;
string data_type = "";
int width;
int height;
size_t img_size;
size_t cur_buf_size = 0;
vector<uint8_t> img_data_f;
bool loop_flag = true;

int port = 54000;
string ipAddress = "10.0.0.7";
int sock;

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
//  Initialize connection to server
uint8_t init_connection(){

	//	Create a socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == FAILED)
	{
		return FAILED;
	}


	//	Create a hint structure for the server we're connecting with
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	//	Connect to the server on the socket
	int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connectRes == FAILED)
	{
		return FAILED;
	}

	return SUCCESS;
}


//  Send the data from the struct to the server
uint8_t send_control(control_cmd_t controls){

	float test_throttle = 0;
	cout <<"Press enter to send test command: ";
	cin >> test_throttle;
	controls.throttle = test_throttle;
	string buf =

			to_string(controls.throttle) + "," +
			to_string(controls.steering) + "," +
			to_string(controls.brake) + "," +
			to_string(controls.handbrake) + "," +
			to_string(controls.is_manual_gear) + "," +
			to_string(controls.manual_gear) + "," +
			to_string(controls.gear_immediate)
			;


	//	int sendRes = send(sock, controls_arr, sizeof(controls_arr), 0);
	int sendRes = send(sock, buf.c_str(), buf.size()+1, 0);
	if (sendRes == FAILED)
	{
		return FAILED;
	}
	return SUCCESS;
}

// receive data from the simulator
//TODO: GPS data etc..
void recieve_data(void){
	cv::namedWindow("ImageWindow", CV_WINDOW_AUTOSIZE);
	//loop over all the data
	while(1){
		// set a buffer
		char buf[16000];
		//memset(buf, 8192);
		int bytesReceived = recv(sock, buf, 16000, 0);

		if (bytesReceived == FAILED)
		{
			cout << "There was an error getting response from server\r\n";
		}
		else
		{
			size_t find_start = (string(buf)).find("cam");
			size_t find_end = (string(buf)).find("ENDL");
			char parse_data_buf[40];

			// if a tag is found parse it
			if(find_start != string::npos){
				memcpy(parse_data_buf,buf + find_start,find_end);
				vector <string> cur_data_buf = parse_buf(string(parse_data_buf), ",");
				data_type = cur_data_buf[0];
				cout << "SERVER> " << "Info bytes recieved:"<<bytesReceived << "\r\n";
				width = stoi(cur_data_buf[1]);
				height = stoi(cur_data_buf[2]);
				img_size = stoi(cur_data_buf[3]);
				cout << "SERVER> " << "Width: " << width << " Height: "<< height <<" Size: "<< img_size << " Bytes \r\n";
			}

			// find the tags

			// if the tag indicates we are receiving camera data
			if(data_type == "cam"){
				//find the start of the image file
				size_t find_PNG = (string(buf)).find("PNG");
				if(find_PNG != string::npos){
					int i = find_PNG -1;
					while(i < bytesReceived){
						img_data_f.push_back(buf[i]);
						i++;
						cur_buf_size++;

					}

					while(cur_buf_size < img_size ){
						char buf2[16000];
						//memset(buf2, 8192);
						bytesReceived = recv(sock, buf2, 16000, 0);

						if (bytesReceived == FAILED)
						{
							cout << "There was an error getting response from server\r\n";
						}
						else
						{
							int j = 0;
							while(j < bytesReceived){
								if(cur_buf_size < img_size){
									img_data_f.push_back(buf2[j]);
									cur_buf_size++;
									j++;
								}
								else{
									break;
								}

							}


							}
						}
					data_type = "";
					cv::Mat rcv_img = cv::Mat(height ,width ,CV_8UC3 );

					try{
						rcv_img = cv::imdecode(img_data_f,1);

						cv::imshow("ImageWindow", rcv_img);
					}
					catch(...){
						cout << "Exeption occured" << endl;
					}
					cv::waitKey(1);
					img_data_f.clear();
					cur_buf_size = 0;
				}

				size_t find_start = (string(buf)).find("cam");
				size_t find_end = (string(buf)).find("ENDL");
				char parse_data_buf[40];

				// if a tag is found parse it
				if(find_start != string::npos){
					memcpy(parse_data_buf,buf + find_start,find_end);
					vector <string> cur_data_buf = parse_buf(string(parse_data_buf), ",");
					data_type = cur_data_buf[0];
					cout << "SERVER> " << "Info bytes recieved:"<<bytesReceived << "\r\n";
					width = stoi(cur_data_buf[1]);
					height = stoi(cur_data_buf[2]);
					img_size = stoi(cur_data_buf[3]);
					cout << "SERVER> " << "Width: " << width << " Height: "<< height <<" Size: "<< img_size << " Bytes \r\n";

				}
			}


			}
		}
	}


