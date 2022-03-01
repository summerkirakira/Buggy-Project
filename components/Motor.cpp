#include <mbed.h>
#include <./components/Motor.h>
#include <QEI.h>

Motor::Motor(PinName my_bipolar, PinName dircetion, PinName pwm, PinName channel_a, PinName channel_b, bool is_left): 
bipolar(my_bipolar), motor_dircetion(dircetion), motor_pwm(pwm), 
encoder(channel_a, channel_b, NC, 256), is_left_motor(is_left) {
    if (is_left_motor) {
        motor_dircetion = 1;
    } else {
        motor_dircetion = 0;
    }
    bipolar = 0;
    PWM_PERIOD = 10;
    motor_pwm.period_ms(PWM_PERIOD);
    measure_period_ms = 50;
    // motor_pwm.write(0.0f);
    stop();
    total_distance = 0;
    current_pulses = 0;
    last_pulses = 0;
    gear_ratio = 300;
    ticker.attach(callback(this, &Motor::measure_speed), 0.05);
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
    int encoder_pulses = encoder.getPulses();
    last_pulses = current_pulses;
    current_pulses = encoder_pulses;
    current_speed = (current_pulses - last_pulses) / measure_period_ms * 1000 * gear_ratio;
    if(!is_left_motor) {current_speed *= -1;}
    total_distance += measure_period_ms * current_speed / 1000;
}

int Motor::get_pulses() {
    return encoder.getPulses();
}

void Motor::stop() {
    if(is_left_motor) {
        bipolar = 0;
        set_power(0.0f);
    } else {
        set_power(0.5);
    }
}

void Motor::start(float power) {
    bipolar = 1;
    set_power(power);
}


