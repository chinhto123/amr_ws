#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Pose.h"

class LogicController {
public:
    LogicController() {
        // Initialize publishers
        pub1 = nh.advertise<std_msgs::String>("bt_request", 1);
        pub2 = nh.advertise<std_msgs::String>("bt_request", 1);
        pub3 = nh.advertise<std_msgs::String>("bt_request", 1);
        pub4 = nh.advertise<std_msgs::String>("bt_request", 1);
        pub  = nh.advertise<std_msgs::String>("bt_request", 1);
        pub5 = nh.advertise<std_msgs::String>("tag_dest", 10);
        
        publisher = nh.advertise<geometry_msgs::Pose>("initial_pose", 1);

        // Initialize subscribers
        sub1 = nh.subscribe("navi_status", 1000, &LogicController::messageCallback1, this);
        sub11 = nh.subscribe("agv_status", 1000, &LogicController::messageCallback111, this);
        sub2 = nh.subscribe("external_input", 1000, &LogicController::messageCallback2, this);
        sub3 = nh.subscribe("external_input", 1000, &LogicController::messageCallback3, this);
        sub4 = nh.subscribe("acs_msg", 1000, &LogicController::messageCallback4, this);
        sub5 = nh.subscribe("initial_position", 1000, &LogicController::messageCallback5, this);
        sub6 = nh.subscribe("slim_status", 1000, &LogicController::messageCallback6, this);
    }

    void run() {
        messagePublished_ = false;
        messagePublished_F = false;
        TagPublished_ = false;
        ros::Rate loop_rate(10);


        while (ros::ok()) {
            ros::NodeHandle nh;

            // turn on
            if (!TagPublished_ && received_STARTSLAM) {
                if (received_POSE) {
                    if (!received_TAG) {
                        std_msgs::String output_msg10;
                        output_msg10.data = "802";
                        pub5.publish(output_msg10);
                     ros::Duration delay_duration(0.2);
              	       delay_duration.sleep(); // 2 seconds
                	if (!received_STANDBY && received_TAG && !received_SLIM ) {
                    	std_msgs::String output_msg2;
                    	output_msg2.data = "STOPSLAM";
                    	pub1.publish(output_msg2);   

                    	std_msgs::String output_msg1;
                    	output_msg1.data = "STARTSLAM";
                    	pub4.publish(output_msg1);                
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
                    //std_msgs::String output_msg1;
                    //output_msg1.data = "STOPSLAM";
                    //pub1.publish(output_msg1);
                    std_msgs::String output_msg2;
                    output_msg2.data = "STARTSLIM";
                    pub2.publish(output_msg2); 
                    messagePublished_ = true;
                    ROS_INFO("MODE SLIM");
                }
		//done job return to STANDBY
                if (received_FINISH && !messagePublished_F) {
                    std_msgs::String output_msg10;
                    output_msg10.data = "802";
                    pub5.publish(output_msg10);
                      ros::Duration delay_duration(0.2);
              	       delay_duration.sleep(); // 0.2 seconds                   
                    //std_msgs::String output_msg3;
                    //output_msg3.data = "STOPSLIM";
                    //pub3.publish(output_msg3);  
                    //ROS_INFO("%s", output_msg3.data.c_str());
                    received_SLIM = false; 
                    received_STANDBY=true;
                    
                    std_msgs::String output_msg4;
                    output_msg4.data = "STARTSLAM";
                    pub4.publish(output_msg4);  
                    messagePublished_F = true;      
                    ROS_INFO("MODE SLAM");  
                }         
                
                if (received_STOPSLIM) {
                    std_msgs::String Msg1;
                    Msg1.data = "STOPSLIM";
                    pub.publish(Msg1);
                    ROS_INFO("%s", Msg1.data.c_str());
                    received_STOPSLIM = false;
                    received_STOPSLAM = false;                
                }
                
                if (received_STARTSLIM) {
                    std_msgs::String Msg2;
                    Msg2.data = "STARTSLIM";
                    pub.publish(Msg2);
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
                    pub.publish(Msg3);
                    ROS_INFO("%s", Msg3.data.c_str()); 
                    received_STARTSLAM = false;
                    received_STARTSLIM = false;                
                }
                
                if (received_STOPSLAM) {
                    std_msgs::String Msg4;
                    Msg4.data = "STOPSLAM";
                    pub.publish(Msg4);
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
    ros::Publisher pub1, pub2, pub3, pub4, pub, pub5, publisher, dest_publisher, pose_publisher;
    ros::Subscriber sub1, sub11, sub2, sub3, sub4, sub5, sub6;

    bool received_SLIM = false;
    bool received_SLAM = false;   
    bool received_RUN = true;
    bool received_FINISH = false;
    bool received_STARTSLIM = false;
    bool received_STOPSLIM = false;
    bool received_STARTSLAM = false;
    bool received_STOPSLAM = false;
    bool received_TAG = false;
    bool received_POSE = false;
    bool messagePublished_;
    bool messagePublished_F;
    bool TagPublished_;
    bool received_STANDBY = false; 
    bool received_FIRSTSTART=false;
    bool  received_ABORT=false;

    void messageCallback1(const std_msgs::String::ConstPtr& msg) {
        if (msg->data == "SUCCESS") {
        if (!received_STANDBY) {
            received_SLIM = true;} 
            received_SLAM = false;     
            received_RUN = false;
        }
        if (msg->data == "PROCESSING" || msg->data == "ABORT") {
            received_SLAM = true;  
            received_SLIM = false;  
            messagePublished_ = false;
        }
    }

    void messageCallback111(const std_msgs::String::ConstPtr& msg) {     
        if (msg->data == "FINISH") {
            received_FINISH = true;
            messagePublished_F = false;  
        }
        else {
            received_RUN = false;    
        }
    }
       
    void messageCallback6(const std_msgs::String::ConstPtr& msg) {
        if (msg->data == "SUCCESS") {
            received_SLAM = true; 
            received_SLIM = false;     
            received_RUN = false;
        }
        if (msg->data == "PROCESSING" ) {
            received_SLIM = true;  
            received_SLAM = false;  
            messagePublished_ = false;
            received_ABORT=false;
        }
        if (msg->data == "ABORT") {
            received_SLIM = true;  
            received_SLAM = false;  
            messagePublished_ = false;
            received_ABORT=true;
        }        
    }    

    void messageCallback2(const std_msgs::String::ConstPtr& msg) {
        if (msg->data == "STOP" || msg->data == "EMERGENCYOFF" || msg->data == "KEYOFF" || msg->data == "SICKSAFE" || msg->data == "BUMPER" || msg->data == "SENSORERROR" || msg->data == "COLLISIONON") {
            received_STOPSLIM = true;
            received_STARTSLIM = false; 
        }
        if (msg->data == "START" || msg->data == "RESET"  || msg->data == "COLLISIONOFF") {
            received_STARTSLIM = true;        
            received_STOPSLIM = false;
        }
        if (msg->data == "KEYON") {
            received_STARTSLIM = false;  
        }          
    }

    void messageCallback3(const std_msgs::String::ConstPtr& msg) {
        if (msg->data == "STOP" || msg->data == "EMERGENCYOFF" || msg->data == "KEYOFF" || msg->data == "SICKSAFE" || msg->data == "BUMPER" || msg->data == "SENSORERROR" || msg->data == "COLLISIONON") {
            received_STOPSLAM = true;
            received_STARTSLAM = false;
        }
        if (msg->data == "START" || msg->data == "RESET"  || msg->data == "COLLISIONOFF") {
            received_FIRSTSTART=true;
            TagPublished_ = false;
            received_STARTSLAM = true;
            received_STOPSLAM = false;    
        }
        if (msg->data == "KEYON") {
            received_STARTSLAM = false; 
        }         
        if (msg->data == "RESET") {
            received_POSE = false; 
        } 
    }

    void messageCallback4(const std_msgs::StringConstPtr& msg) {
        if (msg->data =="802") {
           ros::Duration delay_duration(2.0); // 2 seconds		 
            
            std_msgs::String output_msg10;
            output_msg10.data = "802";
            pub5.publish(output_msg10);  
            

                //ros::Duration delay_duration(0.2);
              	 //delay_duration.sleep(); // 2 seconds
            std_msgs::String output_msg3;
            output_msg3.data = "STOPSLAM";
            pub3.publish(output_msg3);  
            ROS_INFO("%s", output_msg3.data.c_str());
        
            output_msg3.data = "STOPSLIM";
            pub3.publish(output_msg3);  
            ROS_INFO("%s", output_msg3.data.c_str());  
            
                     	 
            if (received_FIRSTSTART &&  received_ABORT) { 
                  
            std_msgs::String output_msg4;
            output_msg4.data = "STARTSLAM";
            pub4.publish(output_msg4);  
            ROS_INFO("%s", output_msg4.data.c_str());  
            } 	
            received_STANDBY = true;    
            received_STARTSLIM=false;
            received_SLIM=false; 	    
        }
        else { 
            ros::Duration delay_duration(2.0); // 2 seconds
            received_STANDBY = false;
            received_TAG = true;
            std_msgs::String output_msg;
            output_msg.data = msg->data;
            pub5.publish(output_msg);
            ROS_INFO("new tag: %s", output_msg.data.c_str());            


            std_msgs::String output_msg3;
            output_msg3.data = "STOPSLAM";
            pub3.publish(output_msg3);  
            ROS_INFO("%s", output_msg3.data.c_str());
            output_msg3.data = "STOPSLIM";
            pub3.publish(output_msg3);  
            ROS_INFO("%s", output_msg3.data.c_str());

            if (received_FIRSTSTART && received_ABORT) { 

            std_msgs::String output_msg4;
            output_msg4.data = "STARTSLAM";
            pub4.publish(output_msg4);  
            ROS_INFO("%s", output_msg4.data.c_str());             
        	}
    }
}
    void messageCallback5(const std_msgs::String::ConstPtr& msg) {
        received_POSE = true;
        received_STARTSLAM = false;
        ROS_INFO(" %s", msg->data.c_str());
        geometry_msgs::Pose pose_msg1;
        pose_msg1.position.x = 1.0;
        pose_msg1.position.y = 1.0;
        pose_msg1.position.z = 0.0;
        pose_msg1.orientation.x = 0.0;
        pose_msg1.orientation.y = 0.0;
        pose_msg1.orientation.z = 0.0;
        pose_msg1.orientation.w = 1.0;

        publisher.publish(pose_msg1);
    }
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "lOGIC");
    LogicController logicController;
    logicController.run();

    return 0;
}

