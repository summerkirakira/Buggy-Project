#include <mbed.h>
#include <./components/DriveBoard.h>

DriveBoard::DriveBoard(
    PinName left_motor_bipolar,
    PinName left_motor_pwm,
    PinName left_motor_channel_a,
    PinName left_motor_channel_b,
    PinName right_motor_bipolar,
    PinName right_motor_pwm,
    PinName right_motor_channel_a,
    PinName right_motor_channel_b,
    PinName enable_pin
): left_motor(
        left_motor_bipolar,
        left_motor_pwm,
        left_motor_channel_a,
        left_motor_channel_b
    ),
    right_motor(
        right_motor_bipolar,
        right_motor_pwm,
        right_motor_channel_a,
        right_motor_channel_b
    ), enable(enable_pin) {
    enable = 1;
}

float DriveBoard::get_left_motor_power() {
    return left_motor.get_power();
}

float DriveBoard::get_right_motor_power() {
    return right_motor.get_power()
}

float DriveBoard::get_left_motor_velocity() {
    
}


    