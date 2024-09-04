from py_lib.pattern import Singleton
from py_lib.logger import Logger
from py_lib.thread import Worker
from pi_communication.tcp import Tcp_Handle

import rospy
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Point, Quaternion, Twist
from tf.transformations import quaternion_from_euler
from tf import TransformBroadcaster

from time import sleep

class Pi_Com(metaclass=Singleton):
    def __init__(self) -> None:
        ip = rospy.get_param(f"/{rospy.get_name()}/host/ip", "127.0.0.1")
        port = rospy.get_param(f"/{rospy.get_name()}/host/port", 8080)
        self.__tcp = Tcp_Handle(ip, port)
        self.__odom_pub = rospy.Publisher("odom", Odometry, queue_size=10)
        self.__odom_bc = TransformBroadcaster()
        self.__vel_sub = rospy.Subscriber("cmd_vel", Twist, self.__sendVel)
        self.__logger = Logger()

        self.__tcp.addCallback(self.__parseOdom)
        self.__tcp.listen()

    def __parseOdom(self, msg: str):
        """
        Parse odom data from pi (publish and broadcast)
        """
        print(f"Receive {msg}")
        try:
            data = msg.split(":")
            if data[0] == "ODOM":
                agv_pos = Point(float(data[1]), float(data[2]), 0)
                agv_ori = Quaternion(*quaternion_from_euler(0, 0, float(data[3])))
                print(type(agv_ori))
                agv_vel = Twist()
                agv_vel.linear.x = float(data[4])
                agv_vel.angular.z = float(data[5])
                print(f"Parse data {data[1:6]}")
                self.__publishOdom(agv_pos, agv_ori, agv_vel)
                self.__updateTfOdom(agv_pos, agv_ori)
        except Exception as e:
            self.__logger.error(f"Message error (Msg: {msg}) (Exception: {e})")

    def __publishOdom(self, pos: Point, ori: Quaternion, vel: Twist):
        """
        Args:
            pos: agv position
            ori: agv orientation
            vel: agv velocity
        """
        odom = Odometry()
        odom.header.frame_id = "odom"
        odom.header.stamp = rospy.Time.now()
        odom.child_frame_id = "base_footprint"
        odom.pose.pose.position = pos
        odom.pose.pose.orientation = ori
        odom.twist.twist = vel

        # set the covariance
        for i in range(36):
            if i == 0 or i == 7 or i == 14:
                odom.pose.covariance[i] = 0.001
            elif i == 21 or i == 28 or i == 35:
                odom.pose.covariance[i] = 0.01
            else:
                odom.pose.covariance[i] = 0

        self.__odom_pub.publish(odom)

    def __updateTfOdom(self, pos: Point, ori: Quaternion):
        """
        Args:
            pos: agv position
            ori: agv orientation
        """
        self.__odom_bc.sendTransform(
            (pos.x, pos.y, pos.z),
            (ori.x, ori.y, ori.z, ori.w),
            rospy.Time.now(),
            "base_footprint",
            "odom"
        )

    def __sendVel(self, vel: Twist):
        """
        Send speed command to pi

        Args:
            vel: agv velocity
        """
        self.__tcp.send(f"CMDVEL:{vel.linear.x}:{vel.angular.z}")

if __name__ == "__main__":
    rospy.init_node("pi_com")
    pi_com = Pi_Com()
    while not rospy.is_shutdown():
        sleep(1)