#ifndef BOOLEAN_VARIABLES_H
#define BOOLEAN_VARIABLES_H

class BooleanVariables {
public:
    static bool received_SLIM;
    static bool received_SLAM;
    static bool received_RUN;
    static bool received_FINISH;
    static bool received_STARTSLIM;
    static bool received_STOPSLIM;
    static bool received_STARTSLAM;
    static bool received_STOPSLAM;
    static bool received_TAG;
    static bool received_POSE;
    static bool messagePublished_;
    static bool messagePublished_F;
    static bool TagPublished_;
    static bool received_STANDBY;
    static bool received_FIRSTSTART;
};

#endif // BOOLEAN_VARIABLES_H

