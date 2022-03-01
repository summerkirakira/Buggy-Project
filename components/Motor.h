#include <mbed.h>
#include <QEI.h>

class Motor {
    private:
        DigitalOut bipolar;
        DigitalOut motor_dircetion;
        PwmOut motor_pwm;
        float current_power;
        float PWM_PERIOD;
        Ticker ticker;
        int current_pulses;
        int last_pulses;
        float current_speed;
        float measure_period_ms;
        float gear_ratio;
        float total_distance;
        QEI encoder;
        bool is_left_motor;

    public:
        Motor(PinName bipolar, PinName dircetion, PinName pwm, PinName channel_a, PinName channel_b, bool is_left);
        float get_velocity(void);
        void set_power(float power);
        float get_power(void);
        void measure_speed(void);
        int get_pulses(void);
        void stop(void);
        void start(float power);
        float get_total_distance();
};