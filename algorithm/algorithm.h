#pragma once
float line_position(float sensor_voltage[6]);
float pid_control(float current_error, float derivative_error, float integral_error, float kp, float ki, float kd);
float speed_control(float current_speed, float target_speed, float speed_gain);
float calculate_time_delay(float current_speed);
