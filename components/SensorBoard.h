#include <mbed.h>

class SensorBoard {

    private:
        AnalogIn  sensor_1, sensor_2, sensor_3, sensor_4, sensor_5, sensor_6;
        DigitalOut switch_1, switch_2, switch_3, switch_4, switch_5, switch_6;
        float threshold_value;
        float sensor_voltage[6];
        float white_line_position[6];
        Ticker my_ticker;
    public: 
        SensorBoard(PinName sensor_1, 
                    PinName sensor_2, 
                    PinName sensor_3, 
                    PinName sensor_4, 
                    PinName sensor_5, 
                    PinName sensor_6,
                    PinName switch_1,
                    PinName switch_2,
                    PinName switch_3,
                    PinName switch_4,
                    PinName switch_5,
                    PinName switch_6);
        void get_sensor_status();
        float get_sensor_1_value();
        float get_sensor_2_value();
        float get_sensor_3_value();
        float get_sensor_4_value();
        float get_sensor_5_value();
        float get_sensor_6_value();


};