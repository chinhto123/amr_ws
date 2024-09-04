// Auto-generated. Do not edit!

// (in-package opencv_services.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

let geometry_msgs = _finder('geometry_msgs');

//-----------------------------------------------------------

class box_and_target_positionRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
    }
    else {
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type box_and_target_positionRequest
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type box_and_target_positionRequest
    let len;
    let data = new box_and_target_positionRequest(null);
    return data;
  }

  static getMessageSize(object) {
    return 0;
  }

  static datatype() {
    // Returns string type for a service object
    return 'opencv_services/box_and_target_positionRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd41d8cd98f00b204e9800998ecf8427e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new box_and_target_positionRequest(null);
    return resolved;
    }
};

class box_and_target_positionResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.box_position = null;
      this.target_position = null;
    }
    else {
      if (initObj.hasOwnProperty('box_position')) {
        this.box_position = initObj.box_position
      }
      else {
        this.box_position = new geometry_msgs.msg.Point();
      }
      if (initObj.hasOwnProperty('target_position')) {
        this.target_position = initObj.target_position
      }
      else {
        this.target_position = new geometry_msgs.msg.Point();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type box_and_target_positionResponse
    // Serialize message field [box_position]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.box_position, buffer, bufferOffset);
    // Serialize message field [target_position]
    bufferOffset = geometry_msgs.msg.Point.serialize(obj.target_position, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type box_and_target_positionResponse
    let len;
    let data = new box_and_target_positionResponse(null);
    // Deserialize message field [box_position]
    data.box_position = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    // Deserialize message field [target_position]
    data.target_position = geometry_msgs.msg.Point.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 48;
  }

  static datatype() {
    // Returns string type for a service object
    return 'opencv_services/box_and_target_positionResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '7e4dc1312c08dfa2b45c73a3b17d973d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    geometry_msgs/Point box_position
    geometry_msgs/Point target_position
    
    
    ================================================================================
    MSG: geometry_msgs/Point
    # This contains the position of a point in free space
    float64 x
    float64 y
    float64 z
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new box_and_target_positionResponse(null);
    if (msg.box_position !== undefined) {
      resolved.box_position = geometry_msgs.msg.Point.Resolve(msg.box_position)
    }
    else {
      resolved.box_position = new geometry_msgs.msg.Point()
    }

    if (msg.target_position !== undefined) {
      resolved.target_position = geometry_msgs.msg.Point.Resolve(msg.target_position)
    }
    else {
      resolved.target_position = new geometry_msgs.msg.Point()
    }

    return resolved;
    }
};

module.exports = {
  Request: box_and_target_positionRequest,
  Response: box_and_target_positionResponse,
  md5sum() { return '7e4dc1312c08dfa2b45c73a3b17d973d'; },
  datatype() { return 'opencv_services/box_and_target_position'; }
};
