#ifndef LCM_INTERFACE_H_
#define LCM_INTERFACE_H_

#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <math.h>

#include <lcm/lcm-cpp.hpp>
#include "lcm_msg/uav_status/uav_status_t.hpp"
using namespace std;
static string base_channel="uav_status_";

uint64_t lcm_get_time_usec();

void* start_lcm_interface_send_thread(void *args);
void* start_lcm_subscribe_thread(void *args);
class Lcm_Sub_Handler
{

public:
    Lcm_Sub_Handler();
    ~Lcm_Sub_Handler();
    uav_status::uav_status_t oth_uav_status;
    string sub_name_channel;
    bool init_flage;
    void lcm_subscrib_function(const lcm::ReceiveBuffer* rbuf, const std::string& chan, const uav_status::uav_status_t* msg);
};

class Lcm_Interface
{

public:
	Lcm_Interface();
	~Lcm_Interface();
	
	uint64_t send_count;
	uint64_t pos_receive_time;
	uint64_t att_receive_time;
	uint64_t send_time;
	
	int mav_sys_id;
    int max_num_quad;
	
    Lcm_Sub_Handler l_s_handler;

	string name_channel;
	uav_status::uav_status_t lcm_uav_status;
	
	bool has_init;

	int init(int mav_sys_id_);
	void send_lcm_messages();
	void receive_uav_pos(float x,float y,float z);
	void q_from_eular(float roll1,float pitch1,float yaw1);
   	void receive_uav_att(float roll2,float pitch2,float yaw2);
	
	void start();
	void stop();
	
	void send_thread();
	void start_send_thread();
    void subscrib_thread(int num_quad);
	float att_q_from_euler[4];// quaternion att from euler
	

private:
	
	bool time_to_exit;
	
	pthread_t send_tid;
	pthread_t subscrib_tid;
	lcm::LCM lcm;
	
};
#endif
