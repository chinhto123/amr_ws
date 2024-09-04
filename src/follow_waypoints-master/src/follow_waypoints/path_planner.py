#!/usr/bin/env python3
import rospy
import actionlib
import rospkg
import json
import tf
import math

from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import PoseWithCovarianceStamped, Vector3
from actionlib_msgs.msg import GoalID, GoalStatusArray, GoalStatus
from move_base_msgs.msg import MoveBaseAction, MoveBaseGoal
from std_msgs.msg import Empty, String
from tf import TransformListener
import tf2_msgs
from nav_msgs.msg import Odometry
import tf2_ros
node_loco_path = rospkg.RosPack().get_path('follow_waypoints')+"/depends/NODE.json"
node_rela_path = rospkg.RosPack().get_path('follow_waypoints')+"/depends/node_relation.json"
tag_2_node = rospkg.RosPack().get_path('follow_waypoints')+"/depends/tag2node.json"

class Node():
    """A node class for A* Pathfinding"""

    def __init__(self, parent=None, node_id=''):

        self.node_location = json.load(open(node_loco_path))

        self.id = node_id
        self.x = 0.0
        self.y = 0.0
        self.yaw = None
        self.distance = 0.0

        self.g = 0.0
        self.h = 0.0
        self.f = 0.0

        self.parent = parent

        for item_loco in self.node_location:
            if self.id == str(item_loco['id']):
                self.x = item_loco['x']
                self.y = item_loco['y']
                if item_loco['yaw'] != 'None':
                    self.yaw = item_loco['yaw']


def node_maker(node_location):
    marker = MarkerArray()
    for item in node_location:
        node = Marker()
        node.header.frame_id = "map"
        node.header.stamp = rospy.Time.now()

        # set shape, Arrow: 0; Cube: 1 ; Sphere: 2 ; Cylinder: 3
        node.type = 2
        node.id = int(item['id'])

        # Set the scale of the marker
        node.scale.x = 0.1
        node.scale.y = 0.1
        node.scale.z = 0.1

        # Set the color
        node.color.r = 0.0
        node.color.g = 0.0
        node.color.b = 1.0
        node.color.a = 1.0

        # Set the pose of the marker
        node.pose.position.x = item['x']
        node.pose.position.y = item['y']
        node.pose.position.z = 0.0
        node.pose.orientation.x = 0.0
        node.pose.orientation.y = 0.0
        node.pose.orientation.z = 0.0
        node.pose.orientation.w = 1.0

        marker.markers.append(node)

    return marker


def context_maker(node_location):
    marker = MarkerArray()
    for item in node_location:
        context = Marker()
        context.header.frame_id = "map"
        context.header.stamp = rospy.Time.now()

        # set shape, Arrow: 0; Cube: 1 ; Sphere: 2 ; Cylinder: 3
        context.type = 9
        context.id = int(item['id'])

        # Set the scale of the marker
        context.scale.x = 0.2
        context.scale.y = 0.2
        context.scale.z = 0.2

        # Set the color
        context.color.r = 0.0
        context.color.g = 0.0
        context.color.b = 1.0
        context.color.a = 1.0

        # Set the pose of the marker
        context.pose.position.x = item['x'] 
        context.pose.position.y = item['y'] + 0.1
        context.pose.position.z = 0.0
        context.pose.orientation.x = 0.0
        context.pose.orientation.y = 0.0
        context.pose.orientation.z = 0.0
        context.pose.orientation.w = 1.0

        context.text = item["id"]

        marker.markers.append(context)
    return marker

class PathPlanner():
    def __init__(self):
        rospy.init_node('path_planner')
        self.listener = TransformListener()
        self.path_ready_pub = rospy.Publisher("/path_ready",Empty,queue_size=1)
        self.path_reset_pub = rospy.Publisher("/path_reset",Empty,queue_size=1)
        self.start_slam_pub = rospy.Publisher("/start_journey",Empty,queue_size=1)
        self.cancel_follow_pub = rospy.Publisher("/cancel_follow",Empty,queue_size=1)
        self.navi_status_pub = rospy.Publisher("/navi_status",String,queue_size=1)
        self.current_tag_pub = rospy.Publisher("/current_tag_position",String,queue_size=1)
        self.node_visual_pub = rospy.Publisher("/node_visual", MarkerArray, queue_size = 2)
        self.node_context_pub = rospy.Publisher("/node_context", MarkerArray, queue_size = 2)
        self.client = actionlib.SimpleActionClient('move_base', MoveBaseAction)
        rospy.loginfo('Connecting to move_base...')
        self.client.wait_for_server()
        rospy.loginfo('Connected to move_base.')
        self.current_node = String()
        self.node_relation = json.load(open(node_rela_path))
        self.node_location = json.load(open(node_loco_path))
        self.tag_2_node = json.load(open(tag_2_node))
        self.output_file_path = rospkg.RosPack().get_path('follow_waypoints')+"/saved_path/pose.csv"
        self.waypoints = []
        self.tag_dest = ''
        self.dest_node = ''

        node_visual = node_maker(self.node_location)
        node_context = context_maker(self.node_location)
        self.node_visual_pub.publish(node_visual)
        self.node_context_pub.publish(node_context)
        rospy.Subscriber('/bt_request',String, self.bt_react)
        rospy.Subscriber('/move_base/status',GoalStatusArray, self.follow_status)
        rospy.Subscriber('/tf',tf2_msgs.msg.TFMessage, self.currentUpdate)
        rospy.Subscriber('/tag_dest',String, self.store_tag)

    def save_waypoint(self):
        with open(self.output_file_path, 'w') as file:
                for current_pose in self.waypoints:
                    file.write(str(current_pose.pose.pose.position.x) + ',' + str(current_pose.pose.pose.position.y) + ',' + str(current_pose.pose.pose.position.z) + ',' + str(current_pose.pose.pose.orientation.x) + ',' + str(current_pose.pose.pose.orientation.y) + ',' + str(current_pose.pose.pose.orientation.z) + ',' + str(current_pose.pose.pose.orientation.w)+ '\n')
        rospy.loginfo('poses written to '+ self.output_file_path)

    def navi_case(self,case):
        switcher={
            0:'SWITCH_NODE',
            1:'PROCESSING',
            2:'ABORT',
            3:'SUCCESS',
        }
        return switcher.get(case,"??????????")

    def follow_status(self, status: GoalStatusArray):
        if len(status.status_list) > 0:
            nav_stt = self.navi_case(status.status_list.pop().status)
            nav_stt_msg = String()
            nav_stt_msg.data = nav_stt
            self.navi_status_pub.publish(nav_stt_msg)

    def currentUpdate(self,data):   
        now = rospy.Time()  
        try:   
            self.listener.waitForTransform('map','base_footprint', now, rospy.Duration(0.5))
            trans,rot = self.listener.lookupTransform('map','base_footprint',now)
            distance = 999
            for item in self.node_location:
                dis = math.sqrt(pow(trans[0]-item['x'],2)+pow(trans[1]-item['y'],2))
                if dis < distance:
                    distance = dis
                    self.current_node.data = item['id']
            
            self.current_tag_pub.publish(self.current_node)
        except (tf2_ros.LookupException, tf2_ros.ConnectivityException, tf2_ros.ExtrapolationException, tf2_ros.TransformException) as e:
            print("Error look up transform", e)
            

    def bt_react(self, data: String):
        if data.data == "STARTSLAM":
            if self.tag_dest != '':
                self.path_planner()
            else:
                rospy.loginfo("%s" % "HAVE NOT RECIVE DESTINATION")
        elif data.data == "STOPSLAM":
            rospy.loginfo("%s" % data.data)
            self.path_reset_pub.publish()
            self.client.cancel_all_goals()
            self.cancel_follow_pub.publish()


    def path_planner(self):
        founded_node = False
        for item in self.tag_2_node:
            for tag in item['tags']:
                if self.tag_dest == str(tag):
                    self.dest_node = str(item['id'])
                    founded_node = True
        if founded_node == True:
            self.waypoint_planner(self.current_node.data,self.dest_node)
            self.save_waypoint()
            self.start_slam_pub.publish()
            rospy.loginfo("%s" % "START SLAM")
        else:
            rospy.loginfo("%s" % "TAG NOT CONFIG")


    def store_tag(self,data: String):
        rospy.loginfo("NEW TAG POSITION RECIVED %s",data.data)
        self.tag_dest = data.data

    def getRPY(self,v3):
        rad90=math.radians(90.0)
        done = False
        if v3.x == 0 and v3.y > 0.0: 
            rad = rad90
        if v3.x == 0 and v3.y < 0.0: 
            rad = rad90 * 3 # 270  
        if v3.x > 0.0 and v3.y == 0: 
            rad = 0
        if v3.x < 0.0 and v3.y == 0: 
            rad = rad90 * 2 # 180 
        if v3.x == 0 and v3.y == 0: 
            rad = 0
        if v3.x == 0 or v3.y == 0: 
            done = True  
        if not done: 
            tg = abs(v3.y/v3.x)
            rad = math.atan(tg)
            pi = math.pi
            if v3.x < 0 and v3.y > 0:
                rad = pi - rad # 180 - rad
            if v3.x < 0 and v3.y < 0:
                rad = pi + rad # 180 + rad
            if v3.x > 0 and v3.y < 0:
                rad = 2 * pi - rad
        yaw = rad   
        roll = 0
        pitch = 0
        return roll, pitch, yaw

    def calculate_poses(self,node_a: Node,node_b: Node):
        vector = Vector3()
        vector.x = node_b.x - node_a.x
        vector.y = node_b.y - node_a.y
        roll = 0.0
        pitch = 0.0
        yaw = self.getRPY(vector)[2]
        quaternion = tf.transformations.quaternion_from_euler(roll, pitch, yaw)

        pose = PoseWithCovarianceStamped()
        pose.pose.pose.position.x     =    node_a.x
        pose.pose.pose.position.y     =    node_a.y
        pose.pose.pose.position.z     =    0.0
        pose.pose.pose.orientation.x = quaternion[0]
        pose.pose.pose.orientation.y = quaternion[1]
        pose.pose.pose.orientation.z = quaternion[2]
        pose.pose.pose.orientation.w = quaternion[3]

        return pose
    
    def convert_poses(self,node: Node):
        roll = 0.0
        pitch = 0.0
        yaw = node.yaw
        quaternion = tf.transformations.quaternion_from_euler(roll, pitch, yaw)

        pose = PoseWithCovarianceStamped()
        pose.pose.pose.position.x     =    node.x
        pose.pose.pose.position.y     =    node.y
        pose.pose.pose.position.z     =    0.0
        pose.pose.pose.orientation.x = quaternion[0]
        pose.pose.pose.orientation.y = quaternion[1]
        pose.pose.pose.orientation.z = quaternion[2]
        pose.pose.pose.orientation.w = quaternion[3]

        return pose

    def waypoint_planner(self,source_node,destination_node):
        self.waypoints = []
        print("SOURCE , DEST: ",source_node,destination_node)
        path = self.astar(source_node,destination_node)
        print(path)
        total_node = len(path)

        for i in range(total_node):
            if i < total_node - 1:
                if path[i].yaw == None:
                    pose = self.calculate_poses(path[i],path[i+1])
                    self.waypoints.append(pose)
                elif path[i].yaw != None:
                    pose = self.convert_poses(path[i])
                    self.waypoints.append(pose)
            elif i == total_node - 1:
                if path[i].yaw == None:
                    path[i].yaw = 0.0
                    pose = self.convert_poses(path[i])
                    self.waypoints.append(pose)
                elif path[i].yaw != None:
                    pose = self.convert_poses(path[i])
                    self.waypoints.append(pose)
        
        print("COMPLETE WAYPOINTS PLANNER")


    def astar(self,start, end):
        
        # Create start and end node
        start_node = Node(None, start)
        start_node.g = start_node.h = start_node.f = 0
        end_node = Node(None, end)
        end_node.g = end_node.h = end_node.f = 0

        # Initialize both open and closed list
        open_list = []
        closed_list = []

        # Add the start node
        open_list.append(start_node)

        # Loop until you find the end
        while len(open_list) > 0:
            # Get the current node
            _current_node = open_list[0]
            current_index = 0
            for index, item in enumerate(open_list):
                if item.f < _current_node.f:
                    _current_node = item
                    current_index = index

            # Pop current off open list, add to closed list
            open_list.pop(current_index)
            closed_list.append(_current_node)

            # Found the goal
            if _current_node.id == end_node.id:
                path = []
                current = _current_node
                while current is not None:
                    path.append(current)
                    current = current.parent
                return path[::-1] # Return reversed path
            
            #Generate children
            children = []
            for item_rela in self.node_relation:
                if _current_node.id == str(item_rela['id']):
                    if item_rela['childs'] != 'None':
                        for child in item_rela['childs']:
                            c_node = Node(_current_node,str(child))
                            children.append(c_node)
            
            for child in children:
            # Child is on the closed list
                for closed_child in closed_list:
                    if child.id == closed_child.id:
                        continue

                # Create the f, g, and h values
                child.g = _current_node.g + pow((child.x - _current_node.x),2) + pow((child.y - _current_node.y),2)
                child.h = pow((child.x - end_node.x),2) + pow((child.y - end_node.y),2)
                child.f = child.g + child.h

                # Child is already in the open list
                for open_node in open_list:
                    if child == open_node and child.g > open_node.g:
                        continue

                # Add the child to the open list
                open_list.append(child)

    

def main():
    PP = PathPlanner()
    rospy.spin()
