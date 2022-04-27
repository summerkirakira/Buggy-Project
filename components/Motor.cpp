#include <mbed.h>
#include <./components/Motor.h>
#include <QEI.h>

Motor::Motor(PinName my_bipolar, PinName dircetion, PinName pwm, PinName channel_a, PinName channel_b, bool is_left): 
bipolar(my_bipolar), motor_dircetion(dircetion), motor_pwm(pwm), 
encoder(channel_a, channel_b, NC, 256), is_left_motor(is_left) {
    motor_dircetion = 1;
    PWM_PERIOD = 10;
    motor_pwm.period_ms(PWM_PERIOD);
    measure_period_ms = 10;
    total_distance = 0;
    current_pulses = 0;
    last_pulses = 0;
    gear_ratio = 3 * 0.075 * 3.1415 * 100;
    total_distance = 0;
    bipolar = 1;
    ticker.attach(callback(this, &Motor::measure_speed), 0.01);
}

void Motor::set_power(float power) {
    // if (power < 0.5) return;
    if (power > 1) return;
    if(!(current_power - power < 0.0000001 && current_power - power > -0.000001)){
        current_power = power;
        motor_pwm.write(current_power);
    }
}

float Motor::get_power() {
    return current_power;
}

float Motor::get_velocity() {
    return current_speed;
}

void Motor::measure_speed() {
    int encoder_pulses = encoder.getPulses();
    last_pulses = current_pulses;
    current_pulses = encoder_pulses;
    current_speed = float(current_pulses - last_pulses) / 256 * measure_period_ms / 1000 * gear_ratio;
    if(!is_left_motor) {current_speed *= -1;}
    total_distance += measure_period_ms * current_speed / 1000;
}

int Motor::get_pulses() {
    return encoder.getPulses();
}

void Motor::stop() {
    set_power(0.5);
}

void Motor::start(float power) {
    set_power(power);
}

float Motor::get_total_distance() {
    return total_distance;
}

void Motor::set_bipolar(int bipolar) {
    this->bipolar = bipolar;
}

int Motor::get_bipolar() {
    return bipolar;
}

