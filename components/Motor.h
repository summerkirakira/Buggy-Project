#include <mbed.h>

class Motor {
    private:
        DigitalOut bipolar;
        PwmOut motor_pwm;
        DigitalIn channel_a;
        DigitalIn channel_b;
        float current_power;
        float PWM_PERIOD;
        Ticker ticker;
        int current_pulses;
        int last_pulses;
        float current_speed;
        float measure_period_ms;
        float gear_ratio;
        QEI encoder;

    public:
        Motor(PinName bipolar, PinName pwm, PinName channel_a, PinName channel_b);
        float get_velocity(void);
        void set_power(float power);
        float get_power(void);
        void measure_speed(void);
}