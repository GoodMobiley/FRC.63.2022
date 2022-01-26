#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef ROBOTMAP_H
#define ROBOTMAP_H

class RobotMap{
public:
    RobotMap();

    //Controllers
    static const int
        XBOX_CONTROLLER = 0;

    //Wheel Stuff
    static const inline double
        WHEEL_DIAMETER = 0.5, //ft
        WHEEL_CIRCUMFRENCE = WHEEL_DIAMETER * M_PI, //ft/rev
        ENCODER_UNITS_PER_REV = 3600, //units/rev 1250 maybe
        FEET_PER_UNIT_FT = WHEEL_CIRCUMFRENCE / ENCODER_UNITS_PER_REV,  //ft/unit

        CAN_TIME_OUT_MS = 25;

    //Talon CAN IDs
    static const int
        FRONT_LEFT_ID = 3,
        REAR_LEFT_ID = 1,
        FRONT_RIGHT_ID = 4,
        REAR_RIGHT_ID = 2,

        LEFT_WINCH_ID = 0,

        COMPRESSOR_CAN_ID = 0;

    //Spark Controllers
    static const int
        BOTTOM_INTAKE_ID = 6,
        BALL_TRACKER_ID = 7, //Top Intake
        RAKE_ID = 9,

        COLOR_WHEEL_ID = 8;

    //Solenoid IDs
    static const int
        //PCM 1#
        PCM1_ID = 1,

        COLOR_WHEEL_EXTEND_SOLENOID = 0,
        COLOR_WHEEL_RETRACT_SOLENOID = 1,

        CLIMB_EXTEND_SOLENOID = 2,
        CLIMB_RETRACT_SOLENOID = 3,

        HOOK_EXTEND_SOLENOID = 4,
        HOOK_RETRACT_SOLENOID = 5,

        //PCM 2#
        PCM2_ID = 2,

        BALL_HATCH_EXTEND_SOLENOID = 0,
        BALL_HATCH_RETRACT_SOLENOID = 1,

        BALL_RAKE_EXTEND_SOLENOID = 2,
        BALL_RAKE_RETRACT_SOLENOID = 3,

        HOOK_RELEASE_EXTEND_SOLENOID = 4,
        HOOK_RELEASE_RETRACT_SOLENOID = 5;
};

#endif