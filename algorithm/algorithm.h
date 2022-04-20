#pragma once
float line_position(float sensor_voltage[6]);
float pid_control(float current_error, float derivative_error, float integral_error, float kp, float ki, float kd);
