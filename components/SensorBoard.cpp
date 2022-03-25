#include <mbed.h>
#include <./components/SensorBoard.h>

SensorBoard::SensorBoard(PinName sensor_1, PinName sensor_2, 
                        PinName sensor_3, PinName sensor_4, 
                        PinName sensor_5, PinName sensor_6,
                        PinName switch_1, PinName switch_2,
                        PinName switch_3, PinName switch_4,
                        PinName switch_5, PinName switch_6):
                        sensor_1(sensor_1), sensor_2(sensor_2), 
                        sensor_3(sensor_3), sensor_4(sensor_4), 
                        sensor_5(sensor_5), sensor_6(sensor_6),
                        switch_1(switch_1), switch_2(switch_2),
                        switch_3(switch_3), switch_4(switch_4),
                        switch_5(switch_5), switch_6(switch_6){
                            this->switch_1 = 1;
                            this->switch_2 = 1;
                            this->switch_3 = 1;
                            this->switch_4 = 1;
                            this->switch_5 = 1;
                            this->switch_6 = 1;
                            threshold_value = 0.1;
                            for(int i=0; i<6; i++){
                                sensor_voltage[i] = 0;
                                white_line_position[i] = false;
                            }
                            // my_ticker.attach(callback(this, &SensorBoard::get_sensor_status), 10ms);
                        }

void SensorBoard::get_sensor_status(){
    sensor_voltage[0] = get_sensor_1_value();
    sensor_voltage[1] = get_sensor_2_value();
    sensor_voltage[2] = get_sensor_3_value();
    sensor_voltage[3] = get_sensor_4_value();
    sensor_voltage[4] = get_sensor_5_value();
    sensor_voltage[5] = get_sensor_6_value();
    // for(int i=0;i<6;i++) {
    //     if(sensor_voltage[i] > threshold_value) {
    //         white_line_position[i] = true;
    //     } else {
    //         white_line_position[i] = false;
    //     }
    // }
}

float SensorBoard::get_sensor_1_value() {
    float value = sensor_1.read();
    return value;
}

float SensorBoard::get_sensor_2_value() {
    float value = sensor_2.read();
    return value;
}

float SensorBoard::get_sensor_3_value() {
    float value = sensor_3.read();
    return value;
}

float SensorBoard::get_sensor_4_value() {
    float value = sensor_4.read();
    return value;
}

float SensorBoard::get_sensor_5_value() {
    float value = sensor_5.read();
    return value;
}

float SensorBoard::get_sensor_6_value() {
    float value = sensor_6.read();
    if(value * 5000 > 300) {
        value = value * 3;
        
    }
    if(value > 1) {
        value = 1;
    }
    return value;
}

float Apply_PID(float error, float kp, float ki, float kd, float dt) {
    float output = 0;
    static float integral = 0;
    static float last_error = 0;
    static float derivative = 0;
    integral += error * dt;
    derivative = (error - last_error) / dt;
    output = kp * error + ki * integral + kd * derivative;
    last_error = error;
    return output;
}