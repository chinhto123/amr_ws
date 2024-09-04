#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose.h"

class LogicController {
public:
    LogicController() {
        // Initialize publishers
        pub_request = nh.advertise<std_msgs::String>("bt_request", 5);
        pub_tag_dest = nh.advertise<std_msgs::String>("tag_dest", 10);
        publisher = nh.advertise<geometry_msgs::Pose>("initial_pose", 1);

        // Initialize subscribers
        sub_navi_status = nh.subscribe("navi_status", 1000, &LogicController::messageCallbackNaviStatus, this);
        sub_external_input = nh.subscribe("external_input", 1000, &LogicController::messageCallbackExternalInput, this);
        sub_acs_msg = nh.subscribe("acs_msg", 1000, &LogicController::messageCallbackAcsMsg, this);
        sub_initial_position = nh.subscribe("initial_position", 1000, &LogicController::messageCallbackInitialPosition, this);
        sub_slim_status = nh.subscribe("slim_status", 1000, &LogicController::messageCallbackSlimStatus, this);
    }


    void run() {
        ros::Rate loop_rate(10);

        while (ros::ok()) {
            // Your logic here
            // turn on
            if (!TagPublished_ && received_STARTSLAM) {
                if (received_POSE) {
                    if (!received_TAG) {
                        std_msgs::String output_msg10;
                        output_msg10.data = "802";
                        pub5.publish(output_msg10);
                	if (!received_STANDBY && received_TAG && !received_SLIM ) {
                    	std_msgs::String output_msg2;
                    	output_msg2.data = "STOPSLAM";
                    	pub_request.publish(output_msg2);   
              	
                    	std_msgs::String output_msg1;
                    	output_msg1.data = "STARTSLAM";
                    	pub_request.publish(output_msg1);                
                	}      
                	              
                        received_SLAM = true;
                        received_STANDBY = true; 
                        
                        received_TAG = false; 
                        
                    }
                    
                
                TagPublished_ = true;
                                
                }
            }
            
            // mode slim                               
            if (received_SLIM) 
            {
                received_STARTSLAM = false;
                received_STOPSLAM = false;
                if (!messagePublished_ && !received_STANDBY) {
                    std_msgs::String output_msg1;
                    output_msg1.data = "STOPSLAM";
                    pub_request.publish(output_msg1);
                    std_msgs::String output_msg2;
                    output_msg2.data = "STARTSLIM";
                    pub_request.publish(output_msg2); 
                    messagePublished_ = true;
                    ROS_INFO("MODE SLIM");
                }
		//done job return to STANDBY
                if (received_FINISH && !messagePublished_F) {
                    std_msgs::String output_msg10;
                    output_msg10.data = "802";
                    pub5.publish(output_msg10);
                    std_msgs::String output_msg3;
                    output_msg3.data = "STOPSLIM";
                    pub_request.publish(output_msg3);  
                    ROS_INFO("%s", output_msg3.data.c_str());
                    received_SLIM = false; 
                    received_STANDBY=true;
                    
                    std_msgs::String output_msg4;
                    output_msg4.data = "STARTSLAM";
                    pub_request.publish(output_msg4);  
                    messagePublished_F = true;      
                    ROS_INFO("MODE SLAM");  
                }         
                
                if (received_STOPSLIM) {
                    std_msgs::String Msg1;
                    Msg1.data = "STOPSLIM";
                    pub_request.publish(Msg1);
                    ROS_INFO("%s", Msg1.data.c_str());
                    received_STOPSLIM = false;
                    received_STOPSLAM = false;                
                }
                
                if (received_STARTSLIM) {
                    std_msgs::String Msg2;
                    Msg2.data = "STARTSLIM";
                    pub_request.publish(Msg2);
                    ROS_INFO("%s", Msg2.data.c_str());    
                    received_STARTSLIM = false;
                    received_STARTSLAM = false;       
                }  
            }
            
            // mode slam        
            if (received_SLAM) {
                received_STARTSLIM = false;
                received_STOPSLIM = false;
 
                if (received_STARTSLAM && received_POSE) {
                    std_msgs::String Msg3;
                    Msg3.data = "STARTSLAM";
                    pub_request.publish(Msg3);
                    ROS_INFO("%s", Msg3.data.c_str()); 
                    received_STARTSLAM = false;
                    received_STARTSLIM = false;                
                }
                
                if (received_STOPSLAM) {
                    std_msgs::String Msg4;
                    Msg4.data = "STOPSLAM";
                    pub_request.publish(Msg4);
                    ROS_INFO("%s", Msg4.data.c_str()); 
                    received_STOPSLAM = false;
                    received_STOPSLIM = false;                
                }
            }
            
            ros::spinOnce();
            loop_rate.sleep();
        }
    }

private:
    ros::NodeHandle nh;
    ros::Publisher pub_request, pub_tag_dest, publisher;
    ros::Subscriber sub_navi_status, sub_external_input, sub_acs_msg, sub_initial_position, sub_slim_status;

    // Your variables here

    void messageCallbackNaviStatus(const std_msgs::String::ConstPtr& msg) {
        // Your callback logic here
    }

    void messageCallbackExternalInput(const std_msgs::String::ConstPtr& msg) {
        // Your callback logic here
    }

    void messageCallbackAcsMsg(const std_msgs::StringConstPtr& msg) {
        // Your callback logic here
    }

    void messageCallbackInitialPosition(const std_msgs::String::ConstPtr& msg) {
        // Your callback logic here
    }

    void messageCallbackSlimStatus(const std_msgs::String::ConstPtr& msg) {
        // Your callback logic here
    }
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "lOGIC");
    LogicController logicController;
    logicController.run();

    return 0;
}

