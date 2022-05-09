#include <./algorithm/algorithm.h>
#include <mbed.h>

// float line_position(float sensor_voltage[6]){
//     int highest_position = 0;
//     int second_highest_position = 0;
//     float highest_voltage = -1;
//     float second_highest_voltage = -1;
//     float left_sensors_voltage_sum = 0;
//     for(int i=0; i<6; i++){
//         // printf("sensor_voltage[%d] = %d\n", i, int(sensor_voltage[i]*10000));
//         if(sensor_voltage[i] > highest_voltage){
//             second_highest_voltage = highest_voltage;
//             second_highest_position = highest_position;
//             highest_voltage = sensor_voltage[i];
//             highest_position = i;
//         }
//         else if(sensor_voltage[i] > second_highest_voltage){
//             second_highest_voltage = sensor_voltage[i];
//             second_highest_position = i;
//         }
//         left_sensors_voltage_sum += sensor_voltage[i];
//     }
//     left_sensors_voltage_sum = left_sensors_voltage_sum - highest_voltage - second_highest_voltage;

//     // printf("left_sensors_voltage_sum = %d\n", int(left_sensors_voltage_sum*10000));

//     if((highest_position - second_highest_position == 1)||(highest_position - second_highest_position == -1) ) {
//         highest_voltage -= left_sensors_voltage_sum / 4;
//         second_highest_voltage -= left_sensors_voltage_sum / 4;
//         // printf("highest_position = %d, second = %d\n", highest_position, second_highest_position);
//         // printf("highest_voltage = %d, second = %d\n", int(highest_voltage*10000), int(second_highest_voltage*10000));
//         float second_highest_position_weights = second_highest_position * 0.4 - 1;
//         // printf("second_highest_position_weights = %d\n", int(second_highest_position_weights*10000));
//         if (second_highest_position > highest_position) {
//             return second_highest_position_weights - (highest_voltage / (highest_voltage + second_highest_voltage)) * 0.4;
//         } else {
//             return second_highest_position_weights + (highest_voltage / (highest_voltage + second_highest_voltage)) * 0.4;
//         }
        
//     } else {
//         return 10000;
//     }
// }

float pid_control(float current_error, float derivative_error, float integral_error, float kp, float ki, float kd){
    float pid_output = kp * current_error + ki * integral_error + kd * derivative_error;
    return pid_output;
}

float line_position(float sensor_voltage[6]){
    int highest_position = 0;
    int second_highest_position = 0;
    float highest_voltage = -1;
    float second_highest_voltage = -1;
    float left_sensors_voltage_sum = 0;
    bool is_lost_track = true;
    for(int i=0; i<6; i++){
        // printf("sensor_voltage[%d] = %d\n", i, int(sensor_voltage[i]*10000));
        if (sensor_voltage[i] > 0.15) is_lost_track = false;
        if(sensor_voltage[i] > highest_voltage){
            second_highest_voltage = highest_voltage;
            second_highest_position = highest_position;
            highest_voltage = sensor_voltage[i];
            highest_position = i;
        }
        else if(sensor_voltage[i] > second_highest_voltage){
            second_highest_voltage = sensor_voltage[i];
            second_highest_position = i;
        }
        left_sensors_voltage_sum += sensor_voltage[i];
    }
    if(is_lost_track){
        return 10000;
    }
    left_sensors_voltage_sum = left_sensors_voltage_sum - highest_voltage - second_highest_voltage;

    // printf("left_sensors_voltage_sum = %d\n", int(left_sensors_voltage_sum*10000));

    if((highest_position - second_highest_position == 1)||(highest_position - second_highest_position == -1) ) {
        if (highest_position == 5 || highest_position == 0) {
            highest_voltage -= left_sensors_voltage_sum / 4;
            second_highest_voltage -= left_sensors_voltage_sum / 4;
            // printf("highest_position = %d, second = %d\n", highest_position, second_highest_position);
            // printf("highest_voltage = %d, second = %d\n", int(highest_voltage*10000), int(second_highest_voltage*10000));
            float second_highest_position_weights = second_highest_position * 0.4 - 1;
            // printf("second_highest_position_weights = %d\n", int(second_highest_position_weights*10000));
            if (second_highest_position > highest_position) {
                return second_highest_position_weights - (highest_voltage / (highest_voltage + second_highest_voltage)) * 0.4;
            } else {
                return second_highest_position_weights + (highest_voltage / (highest_voltage + second_highest_voltage)) * 0.4;
            }
        } else {
            float highest_position_weights = highest_position * 0.4 - 1;
            float left_positon_weights = (highest_position - 1) * 0.4 - 1;
            float right_position_weights = (highest_position + 1) * 0.4 - 1;
            // float left_total_voltage = sensor_voltage[highest_position - 1] + sensor_voltage[highest_position + 1] + sensor_voltage[highest_position];
            return left_positon_weights * sensor_voltage[highest_position - 1] + right_position_weights * sensor_voltage[highest_position + 1] + highest_position_weights * sensor_voltage[highest_position];
        }
        
    } else {
        return 10000;
    }
}

float speed_control(float current_speed, float target_speed, float speed_gain){
    float speed_output = speed_gain * (target_speed - current_speed);
    return speed_output;
}

float calculate_time_delay(float current_speed) {
    if (current_speed > 0.02) {
        return 0.05;
    } else {
        return 0.2 * (1-current_speed / 0.02);
    }
}