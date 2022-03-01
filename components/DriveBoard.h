#include <mbed.h>
#include <./components/Motor.h>

class DriveBoard {
    private:
        Motor left_motor;
        Motor right_motor;
        DigitalOut enable;
    public:
        DriveBoard(
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
        );
        float get_left_motor_velocity();
        float get_right_motor_velocity();
        float get_left_motor_power();
        float get_right_motor_power();
        void set_left_motor_power(float power);
        void set_right_motor_power(float power);
        int get_left_pulses();
        void stop_left_motor();
        void stop_right_motor();
        void start_left_motor(float power);
        void start_right_motor(float power);
        void disable_all();
        void enable_all();
};