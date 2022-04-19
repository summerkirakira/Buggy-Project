#include <./components/DriveBoard.h>
#include <./components/SensorBoard.h>
#include <mbed.h>

class PID {
    private:
        float kp, ki, kd;
        float set_point;
        float process_value;
        float error;
        float integral;
        float derivative;
        float output;
        float previous_value;
        float previous_error;
        float error_3;
        float measurement_interval;
        DriveBoard * my_drive_board;
        SensorBoard * my_sensor_board;
        Ticker ticker;
        float get_position(float position_array[6]);
    public:
        PID(DriveBoard * my_drive_board, SensorBoard * my_sensor_board);
        void start();
        void stop();
        void set_measurement_interval(float interval);
        void set_set_point(float set_point);
        void set_process_value(float process_value);
        void calculate_error();
        float get_output();
        void update_PID();
        
};