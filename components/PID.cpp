#include <./components/PID.h>
#include <mbed.h>


PID::PID(DriveBoard * drive_board, SensorBoard * sensor_board)
{
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    set_point = 0;
    process_value = 0;
    my_drive_board = drive_board;
    my_sensor_board = sensor_board;
    error = 0;
    integral = 0;
    derivative = 0;
    output = 0;
    previous_value = 0;
    previous_error = 0;
    error_3 = 0;
    measurement_interval = 10000;
}

void PID::start() {
    ticker.attach_us(callback(this, &PID::calculate_error), measurement_interval);
}

void PID::stop() {
    ticker.detach();
}

void PID::calculate_error() {
    float sensor_array[6] = {
        (*my_sensor_board).get_sensor_1_value(),
        (*my_sensor_board).get_sensor_2_value(),
        (*my_sensor_board).get_sensor_3_value(),
        (*my_sensor_board).get_sensor_4_value(),
        (*my_sensor_board).get_sensor_5_value(),
        (*my_sensor_board).get_sensor_6_value()
    };
    for(int i=0; i<6; i++) {
        if(sensor_array[i] > 0.2) {
            sensor_array[i] = 1;
        } else {
            sensor_array[i] = 0;
        }
    }
    error = this->get_position(sensor_array);
    integral = (*my_drive_board).get_line_distance();
    derivative = (*my_drive_board).get_current_speed();
    // output = Apply_PID(previous_value, error, previous_error, e_3, );
    process_value = error;

}

float Apply_PID(float last_output, float e_1, float e_2, float e_3, float kp, float ki, float kd, float ts) {
    float output = 0;
    output = last_output + e_1 * (kp + ki * ts + kd / ts) - e_2 * (kp + 2 * kd / ts) + e_3 * (kd / ts);
    return output;
}

float PID::get_position(float position_array[6]) {
    float sum = 0;
    for (int i = 0; i < 6; i++) {
        sum += position_array[i];
    }
    float position = position_array[0] * -1 + 
        position_array[1] * -0.6 + position_array[2] * -0.2 + 
        position_array[3] * 0.2 + position_array[4] * 0.6 + 
        position_array[5] * 1;
    return position / sum;
}

float PID::get_output() {
    return process_value;
}
    