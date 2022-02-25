#include <mbed.h>
#include <./components/Motor.h>
#include <QEI.h>

Motor::Motor(PinName my_bipolar, PinName pwm, PinName channel_a, PinName channel_b): 
bipolar(my_bipolar), motor_pwm(pwm), 
channel_a(channel_a), channel_b(channel_b),
encoder(channel_a, channel_b, NC, 256) {
    bipolar = 1;
    PWM_PERIOD = 10;
    motor_pwm.period_ms(PWM_PERIOD);
    current_pulses = 0;
    last_pulses = 0;
    ticker.attach_us(callback(this, &Motor::measure_speed), 5000);
}

void Motor::set_power(float power) {
    current_power = power;
    motor_pwm.write(current_power);
}

float Motor::get_power() {
    return current_power;
}

float Motor::get_velocity() {
    return current_speed;
}

void Motor::measure_speed() {
    last_pulses = current_pulses;
    current_pulses = encoder.getPulses();
    current_speed = (current_pulses - last_pulses) / measure_period_ms * gear_ratio;
}
