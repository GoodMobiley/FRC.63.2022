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

        FRONT_ARM_ROTATE_ID = 0,

        COMPRESSOR_CAN_ID = 0;

    //Spark Controllers
    static const int
        LEFT_LAUNCHER_MOTOR = 1,
        RIGHT_LAUNCHER_MOTOR = 2, 
        RAKE_ID = 3;

    //Solenoid IDs
    static const int
        PCM_ID = 1,

        RAKE_EXTEND_SOLENOID = 0,
        RAKE_RETRACT_SOLENOID = 1,

        BALL_LOADER_EXTEND_SOLENOID = 2,
        BALL_LOADER_RETRACT_SOLENOID = 3,

        BALL_SHOVER_EXTEND_SOLENOID = 4,
        BALL_SHOVER_RETRACT_SOLENOID = 5;
};

#endif