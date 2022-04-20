#include <mbed.h>
#include <./components/DriveBoard.h>
#include <./components/SensorBoard.h>
#include <./algorithm/processor.h>
#include <./algorithm/algorithm.h>

#define SPEED_LIMIT 0.5

Processor::Processor(DriveBoard * drive_board, SensorBoard * sensor_board) {
    this->drive_board = drive_board;
    this->sensor_board = sensor_board;
    this->recommend_left_motor_power = 0.5;
    this->recommend_right_motor_power = 0.5;
    this->current_error = 0;
    this->perivious_error = 0;
    this->derivative_error = 0;
    this->integral_error = 0;

    this->period_count = 0;

    this->set_gain(0.01, 0.00000, 0.0000, 0.5);

    my_ticker.attach(callback(this, &Processor::trace_line), 1ms);
}

void Processor::trace_line() {
    float error = -1 * line_position(sensor_board->get_all_sensor_value());
    if (error > -2000) {
        period_count = 0;
        this->perivious_error = this->current_error;
        this->current_error = error;
        this->derivative_error = this->current_error - this->perivious_error;
        this->integral_error += this->current_error;
        // float speed_parameter = drive_board->get_current_speed() / 0.02 > 1 ? 1 : drive_board->get_current_speed() / 0.02;
        float turning_power = apply_pid_control();
        float current_left_motor_power = drive_board->get_left_motor_power();
        float current_right_motor_power = drive_board->get_right_motor_power();
        float speed_difference = SPEED_LIMIT - drive_board->get_current_speed() * this->speed_gain;
        this->recommend_left_motor_power = current_left_motor_power + turning_power / 2;
        this->recommend_right_motor_power = current_right_motor_power - turning_power / 2;
    } else {
        period_count += 1;
        if(period_count > 60) {
            this->recommend_left_motor_power = 0.5;
            this->recommend_right_motor_power = 0.5;
        }
        
    }
}

void Processor::set_gain(float proportional_gain, float derivative_gain, float integral_gain, float speed_gain) {
    this->proportional_gain = proportional_gain;
    this->derivative_gain = derivative_gain;
    this->integral_gain = integral_gain;
    this->speed_gain = speed_gain;
}

float Processor::apply_pid_control() {
    float pid = pid_control(this->current_error, 
                            this->derivative_error, 
                            this->integral_error, 
                            this->proportional_gain, 
                            this->integral_gain, 
                            this->derivative_gain);
    return pid;
}

float Processor::get_left_recommend_power() {
    return this->recommend_left_motor_power;
}

float Processor::get_right_recommend_power() {
    return this->recommend_right_motor_power;
}

void Processor::reset() {
    recommend_left_motor_power = 0.9;
    recommend_right_motor_power = 0.9;
    this->current_error = 0;
    this->perivious_error = 0;
    this->derivative_error = 0;
    this->integral_error = 0;
}