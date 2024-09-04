;; Auto-generated. Do not edit!


(when (boundp 'opencv_services::box_and_target_position)
  (if (not (find-package "OPENCV_SERVICES"))
    (make-package "OPENCV_SERVICES"))
  (shadow 'box_and_target_position (find-package "OPENCV_SERVICES")))
(unless (find-package "OPENCV_SERVICES::BOX_AND_TARGET_POSITION")
  (make-package "OPENCV_SERVICES::BOX_AND_TARGET_POSITION"))
(unless (find-package "OPENCV_SERVICES::BOX_AND_TARGET_POSITIONREQUEST")
  (make-package "OPENCV_SERVICES::BOX_AND_TARGET_POSITIONREQUEST"))
(unless (find-package "OPENCV_SERVICES::BOX_AND_TARGET_POSITIONRESPONSE")
  (make-package "OPENCV_SERVICES::BOX_AND_TARGET_POSITIONRESPONSE"))

(in-package "ROS")



(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(defclass opencv_services::box_and_target_positionRequest
  :super ros::object
  :slots ())

(defmethod opencv_services::box_and_target_positionRequest
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass opencv_services::box_and_target_positionResponse
  :super ros::object
  :slots (_box_position _target_position ))

(defmethod opencv_services::box_and_target_positionResponse
  (:init
   (&key
    ((:box_position __box_position) (instance geometry_msgs::Point :init))
    ((:target_position __target_position) (instance geometry_msgs::Point :init))
    )
   (send-super :init)
   (setq _box_position __box_position)
   (setq _target_position __target_position)
   self)
  (:box_position
   (&rest __box_position)
   (if (keywordp (car __box_position))
       (send* _box_position __box_position)
     (progn
       (if __box_position (setq _box_position (car __box_position)))
       _box_position)))
  (:target_position
   (&rest __target_position)
   (if (keywordp (car __target_position))
       (send* _target_position __target_position)
     (progn
       (if __target_position (setq _target_position (car __target_position)))
       _target_position)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Point _box_position
    (send _box_position :serialization-length)
    ;; geometry_msgs/Point _target_position
    (send _target_position :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Point _box_position
       (send _box_position :serialize s)
     ;; geometry_msgs/Point _target_position
       (send _target_position :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Point _box_position
     (send _box_position :deserialize buf ptr-) (incf ptr- (send _box_position :serialization-length))
   ;; geometry_msgs/Point _target_position
     (send _target_position :deserialize buf ptr-) (incf ptr- (send _target_position :serialization-length))
   ;;
   self)
  )

(defclass opencv_services::box_and_target_position
  :super ros::object
  :slots ())

(setf (get opencv_services::box_and_target_position :md5sum-) "7e4dc1312c08dfa2b45c73a3b17d973d")
(setf (get opencv_services::box_and_target_position :datatype-) "opencv_services/box_and_target_position")
(setf (get opencv_services::box_and_target_position :request) opencv_services::box_and_target_positionRequest)
(setf (get opencv_services::box_and_target_position :response) opencv_services::box_and_target_positionResponse)

(defmethod opencv_services::box_and_target_positionRequest
  (:response () (instance opencv_services::box_and_target_positionResponse :init)))

(setf (get opencv_services::box_and_target_positionRequest :md5sum-) "7e4dc1312c08dfa2b45c73a3b17d973d")
(setf (get opencv_services::box_and_target_positionRequest :datatype-) "opencv_services/box_and_target_positionRequest")
(setf (get opencv_services::box_and_target_positionRequest :definition-)
      "---
geometry_msgs/Point box_position
geometry_msgs/Point target_position


================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
")

(setf (get opencv_services::box_and_target_positionResponse :md5sum-) "7e4dc1312c08dfa2b45c73a3b17d973d")
(setf (get opencv_services::box_and_target_positionResponse :datatype-) "opencv_services/box_and_target_positionResponse")
(setf (get opencv_services::box_and_target_positionResponse :definition-)
      "---
geometry_msgs/Point box_position
geometry_msgs/Point target_position


================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
")



(provide :opencv_services/box_and_target_position "7e4dc1312c08dfa2b45c73a3b17d973d")


