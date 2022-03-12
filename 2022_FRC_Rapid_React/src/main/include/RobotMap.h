#define _USE_MATH_DEFINES
#include <math.h>

#ifndef ROBOTMAP_H
#define ROBOTMAP_H

class RobotMap{
public:
    RobotMap();

    //Controllers
    static const int
        PILOT_CONTROLLER = 0,
        COPILOT_CONTROLLER = 1;

    //Wheel Stuff
    static const inline double
        WHEEL_DIAMETER = 0.5, //ft
        WHEEL_CIRCUMFRENCE = WHEEL_DIAMETER * M_PI, //ft/rev
        ENCODER_UNITS_PER_REV = 3600, //units/rev 1250 maybe
        FEET_PER_UNIT_FT = WHEEL_CIRCUMFRENCE / ENCODER_UNITS_PER_REV,  //ft/unit

        CAN_TIME_OUT_MS = 25;

    //Climb Rotatio Stuff
    static const inline double
        HOOK_ENCODER_UNITS_PER_REV = 256;

    //Motor Values
    static const inline double
        RAKE_MOTOR_POWER = .65,

        LONG_MOTOR_POWER = .85,
        SHORT_MOTOR_POWER = .75,
        PUKE_MOTOR_POWER = .5,

        HOOK_ROTATION_MOTOR_POWER = .25,
        HOOK_EXTEND_MOTOR_POWER = .5,
        HOOK_RETRACT_MOTOR_POWER_CLIMB = 1,
        HOOK_RETRACT_MOTOR_POWER_RETURN = .5;

    //Talon CAN IDs
    static const int
        FRONT_LEFT_ID = 3,
        REAR_LEFT_ID = 1,
        FRONT_RIGHT_ID = 4,
        REAR_RIGHT_ID = 2,

        FRONT_HOOK_ROTATE_ID = 1,
        LEFT_HOOK_MOTOR_ID = 0,
        RIGHT_HOOK_MOTOR_ID = 0;

    //Spark Controllers
    static const int
        LEFT_LAUNCHER_MOTOR = 2,
        RIGHT_LAUNCHER_MOTOR = 1, 
        RAKE_MOTOR_ID = 3;

    //Solenoid IDs
    static const int
        PCM_ID = 2,

        RAKE_EXTEND_SOLENOID = 0,
        RAKE_RETRACT_SOLENOID = 1,

        BALL_STAGE_EXTEND_SOLENOID = 2,
        BALL_STAGE_RETRACT_SOLENOID = 3,

        BALL_SHOVER_EXTEND_SOLENOID = 4,
        BALL_SHOVER_RETRACT_SOLENOID = 5;

    //Limit Switch IDs
    static const int
        LEFT_LIMIT_SWITCH_ID = 4,
        RIGHT_LIMIT_SWITCH_ID = 5;
};

#endif