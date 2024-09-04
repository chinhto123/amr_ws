#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <iostream>
 #include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

using namespace std;
 

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
 
int main(int argc, char** argv){
   
 
  ros::init(argc, argv, "simple_navigation_goals");
 
 //
  ros::NodeHandle n;
  
  // ROS spinning must be running for the MoveGroupInterface to get information
  // about the robot's state. One way to do this is to start an AsyncSpinner
  // beforehand.
  ros::AsyncSpinner spinner(1);
  spinner.start();

    // MoveIt operates on sets of joints called "planning groups" and stores them in an object called
  // the `JointModelGroup`. Throughout MoveIt the terms "planning group" and "joint model group"
  // are used interchangably.
    static const std::string PLANNING_GROUP_ARM = "ur5_e_controller";
    static const std::string PLANNING_GROUP_GRIPPER = "gripper_controller";
    
    // The :planning_interface:`MoveGroupInterface` class can be easily
    // setup using just the name of the planning group you would like to control and plan for.
    moveit::planning_interface::MoveGroupInterface move_group_interface_arm(PLANNING_GROUP_ARM);
    moveit::planning_interface::MoveGroupInterface move_group_interface_gripper(PLANNING_GROUP_GRIPPER);

    // We can get a list of all the groups in the robot:
    ROS_INFO_NAMED("tutorial", "Available Planning Groups:");
    std::copy(move_group_interface_arm.getJointModelGroupNames().begin(),
            move_group_interface_arm.getJointModelGroupNames().end(), std::ostream_iterator<std::string>(std::cout, ", "));

    moveit::planning_interface::MoveGroupInterface::Plan my_plan_arm;
    
    

  MoveBaseClient ac("move_base", true);
 
  
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
 
  int user_choice = 6;
  char choice_to_continue = 'Y';
  bool run = true;
     
  while(run) {
 
   // 1. Move to home position
    move_group_interface_arm.setJointValueTarget(move_group_interface_arm.getNamedTargetValues("home"));
    
    bool success = (move_group_interface_arm.plan(my_plan_arm) == moveit::planning_interface::MoveItErrorCode::SUCCESS);

    ROS_INFO_NAMED("tutorial", "Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");

    move_group_interface_arm.move();
    cout << "\nWait for robot to return to safe position" << endl;
    cout << "\nWhere do you want the robot to go?" << endl;
    cout << "\n1 = pos1" << endl;
    cout << "2 = pos2" << endl;
    cout << "3 = HOME" << endl;
    cout << "4 = pos4" << endl;
    cout << "5 = pos5" << endl;
    cout << "6 = pos6" << endl;
    cout << "\nEnter a number: ";
    cin >> user_choice;
 
    
    move_base_msgs::MoveBaseGoal goal;
 
    
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
         
    bool valid_selection = true;
 
  
    switch (user_choice) {
      case 1:
        cout << "\nGoal Location: pos1 \n" << endl;
        goal.target_pose.pose.position.x = 1.0;
    goal.target_pose.pose.position.y = 6.0;
        goal.target_pose.pose.orientation.w = 1.0;
        break;
      case 2:
        cout << "\nGoal Location: pos2 \n" << endl;
        goal.target_pose.pose.position.x = -7;
    goal.target_pose.pose.position.y = -8;
        goal.target_pose.pose.orientation.w = 1.0;
        break;
      case 3:
        cout << "\nGoal Location: HOME\n" << endl;
        goal.target_pose.pose.position.x = 0.0;
    goal.target_pose.pose.position.y = 0.05;
        goal.target_pose.pose.orientation.w = 1.0;
        //goal.target_pose.pose.orientation.z=1;
        break;
      case 4:
        cout << "\nGoal Location: pos4\n" << endl;
        goal.target_pose.pose.position.x = -8;
    goal.target_pose.pose.position.y = -3;
        goal.target_pose.pose.orientation.w = 1.0;
        break;
      case 5:
        cout << "\nGoal Location: pos5\n" << endl;
        goal.target_pose.pose.position.x = 12;
    goal.target_pose.pose.position.y = 8;
        goal.target_pose.pose.orientation.w = 1.0;
        break;
      case 6:
        cout << "\nGoal Location: pos6\n" << endl;
        goal.target_pose.pose.position.x = -11.0;
    goal.target_pose.pose.position.y = 8.0;
        goal.target_pose.pose.orientation.w = 1.0;
        break;
      default:
        cout << "\nInvalid selection. Please try again.\n" << endl;
        valid_selection = false;
    }       
         
 
    if(!valid_selection) {
      continue;
    }
 
    ROS_INFO("Sending goal");
    ac.sendGoal(goal);
 
   
    ac.waitForResult();
 
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
      
       // 1. react
       
       
    move_group_interface_arm.setJointValueTarget(move_group_interface_arm.getNamedTargetValues("home"));
    
    bool success = (move_group_interface_arm.plan(my_plan_arm) == moveit::planning_interface::MoveItErrorCode::SUCCESS);

    ROS_INFO_NAMED("tutorial", "Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");

    move_group_interface_arm.move();
    ROS_INFO("The robot has arrived at the goal location");
      }
    else
      ROS_INFO("The robot failed to reach the goal location for some reason");
         

    do {
      cout << "\nWould you like to go to another destination? (Y/N)" << endl;
      cin >> choice_to_continue;
      choice_to_continue = tolower(choice_to_continue); 
    } while (choice_to_continue != 'n' && choice_to_continue != 'y'); 
 
    if(choice_to_continue =='n') {
        run = false;
    }  
  }
   
  return 0;
}
