#pragma once
#include <mbed.h>
#include <./components/DriveBoard.h>
#include <./components/SensorBoard.h>
#include <./algorithm/buggy_state.h>

class Processor {
    private:
        DriveBoard * drive_board;
        SensorBoard * sensor_board;
        Ticker my_ticker;
        float current_error;
        float perivious_error;
        float derivative_error;
        float integral_error;
        float proportional_gain;
        float derivative_gain;
        float integral_gain;
        float speed_gain;

        int period_count;

        float apply_pid_control();
        void trace_line();

        BuggyState buggy_state;
    
    public:
        Processor(DriveBoard * drive_board, SensorBoard * sensor_board);
        float recommend_left_motor_power;
        float recommend_right_motor_power;
        void reset();
        float get_left_recommend_power();
        float get_right_recommend_power();
        BuggyState get_buggy_state();
        void set_gain(float proportional_gain, float derivative_gain, float integral_gain, float speed_gain);
};