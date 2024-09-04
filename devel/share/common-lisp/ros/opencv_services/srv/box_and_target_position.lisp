; Auto-generated. Do not edit!


(cl:in-package opencv_services-srv)


;//! \htmlinclude box_and_target_position-request.msg.html

(cl:defclass <box_and_target_position-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass box_and_target_position-request (<box_and_target_position-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <box_and_target_position-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'box_and_target_position-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name opencv_services-srv:<box_and_target_position-request> is deprecated: use opencv_services-srv:box_and_target_position-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <box_and_target_position-request>) ostream)
  "Serializes a message object of type '<box_and_target_position-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <box_and_target_position-request>) istream)
  "Deserializes a message object of type '<box_and_target_position-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<box_and_target_position-request>)))
  "Returns string type for a service object of type '<box_and_target_position-request>"
  "opencv_services/box_and_target_positionRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'box_and_target_position-request)))
  "Returns string type for a service object of type 'box_and_target_position-request"
  "opencv_services/box_and_target_positionRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<box_and_target_position-request>)))
  "Returns md5sum for a message object of type '<box_and_target_position-request>"
  "7e4dc1312c08dfa2b45c73a3b17d973d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'box_and_target_position-request)))
  "Returns md5sum for a message object of type 'box_and_target_position-request"
  "7e4dc1312c08dfa2b45c73a3b17d973d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<box_and_target_position-request>)))
  "Returns full string definition for message of type '<box_and_target_position-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'box_and_target_position-request)))
  "Returns full string definition for message of type 'box_and_target_position-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <box_and_target_position-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <box_and_target_position-request>))
  "Converts a ROS message object to a list"
  (cl:list 'box_and_target_position-request
))
;//! \htmlinclude box_and_target_position-response.msg.html

(cl:defclass <box_and_target_position-response> (roslisp-msg-protocol:ros-message)
  ((box_position
    :reader box_position
    :initarg :box_position
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point))
   (target_position
    :reader target_position
    :initarg :target_position
    :type geometry_msgs-msg:Point
    :initform (cl:make-instance 'geometry_msgs-msg:Point)))
)

(cl:defclass box_and_target_position-response (<box_and_target_position-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <box_and_target_position-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'box_and_target_position-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name opencv_services-srv:<box_and_target_position-response> is deprecated: use opencv_services-srv:box_and_target_position-response instead.")))

(cl:ensure-generic-function 'box_position-val :lambda-list '(m))
(cl:defmethod box_position-val ((m <box_and_target_position-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader opencv_services-srv:box_position-val is deprecated.  Use opencv_services-srv:box_position instead.")
  (box_position m))

(cl:ensure-generic-function 'target_position-val :lambda-list '(m))
(cl:defmethod target_position-val ((m <box_and_target_position-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader opencv_services-srv:target_position-val is deprecated.  Use opencv_services-srv:target_position instead.")
  (target_position m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <box_and_target_position-response>) ostream)
  "Serializes a message object of type '<box_and_target_position-response>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'box_position) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'target_position) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <box_and_target_position-response>) istream)
  "Deserializes a message object of type '<box_and_target_position-response>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'box_position) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'target_position) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<box_and_target_position-response>)))
  "Returns string type for a service object of type '<box_and_target_position-response>"
  "opencv_services/box_and_target_positionResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'box_and_target_position-response)))
  "Returns string type for a service object of type 'box_and_target_position-response"
  "opencv_services/box_and_target_positionResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<box_and_target_position-response>)))
  "Returns md5sum for a message object of type '<box_and_target_position-response>"
  "7e4dc1312c08dfa2b45c73a3b17d973d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'box_and_target_position-response)))
  "Returns md5sum for a message object of type 'box_and_target_position-response"
  "7e4dc1312c08dfa2b45c73a3b17d973d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<box_and_target_position-response>)))
  "Returns full string definition for message of type '<box_and_target_position-response>"
  (cl:format cl:nil "geometry_msgs/Point box_position~%geometry_msgs/Point target_position~%~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'box_and_target_position-response)))
  "Returns full string definition for message of type 'box_and_target_position-response"
  (cl:format cl:nil "geometry_msgs/Point box_position~%geometry_msgs/Point target_position~%~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <box_and_target_position-response>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'box_position))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'target_position))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <box_and_target_position-response>))
  "Converts a ROS message object to a list"
  (cl:list 'box_and_target_position-response
    (cl:cons ':box_position (box_position msg))
    (cl:cons ':target_position (target_position msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'box_and_target_position)))
  'box_and_target_position-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'box_and_target_position)))
  'box_and_target_position-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'box_and_target_position)))
  "Returns string type for a service object of type '<box_and_target_position>"
  "opencv_services/box_and_target_position")