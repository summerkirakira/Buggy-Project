#include <mbed.h>
#include <./components/DriveBoard.h>

DriveBoard::DriveBoard(
    PinName left_motor_bipolar,
    PinName left_motor_pwm,
    PinName left_dirction,
    PinName left_motor_channel_a,
    PinName left_motor_channel_b,
    PinName right_motor_bipolar,
    PinName right_motor_pwm,
    PinName right_dirction,
    PinName right_motor_channel_a,
    PinName right_motor_channel_b,
    PinName enable_pin
): left_motor(
        left_motor_bipolar,
        left_motor_pwm,
        left_dirction,
        left_motor_channel_a,
        left_motor_channel_b,
        true
    ),
    right_motor(
        right_motor_bipolar,
        right_motor_pwm,
        right_dirction,
        right_motor_channel_a,
        right_motor_channel_b,
        false
    ), enable(enable_pin) {
    enable = 1;
}

float DriveBoard::get_left_motor_power() {
    return left_motor.get_power();
}

float DriveBoard::get_right_motor_power() {
    return right_motor.get_power();
}

float DriveBoard::get_left_motor_velocity() {
    return left_motor.get_velocity();
}

float DriveBoard::get_right_motor_velocity() {
    return right_motor.get_velocity();
}

void DriveBoard::set_left_motor_power(float power) {
    left_motor.set_power(power);
}

void DriveBoard::set_right_motor_power(float power) {
    right_motor.set_power(power);
}

int DriveBoard::get_left_pulses() {
    return left_motor.get_pulses();
}

void DriveBoard::stop_left_motor() {
    left_motor.stop();
}

void DriveBoard::stop_right_motor() {
    right_motor.stop();
}

void DriveBoard::start_left_motor(float power) {
    left_motor.start(power);
}

void DriveBoard::start_right_motor(float power) {
    right_motor.start(power);
}

void DriveBoard::disable_all() {
    enable = 0;
}

void DriveBoard::enable_all() {
    enable = 1;
}