#include <mbed.h>
#include <./components/DriveBoard.h>
#include <./components/SensorBoard.h>
#include <C12832.h>
#include <./components/BLE.h>

BLE hm10(PA_11, PA_12, LED1);
DriveBoard my_drive_board(PB_1, PB_15, PA_11, PC_10, PC_12, PB_13, PA_9,PC_7, PC_3, PC_2, PB_14);
SensorBoard my_sensor_board(PA_0, PA_1,PA_4, PB_0, PC_1, PC_0, PA_8, PB_10, PB_4, PB_5, PB_3, PA_10);

int main() {
  while (true) {
    printf("---Sensor voltage---");
    printf("Sensor 1: %dmV  ", int(my_sensor_board.get_sensor_1_value() * 3300));
    printf("Sensor 2: %dmV  ", int(my_sensor_board.get_sensor_2_value() * 3300));
    printf("Sensor 3: %dmV  ", int(my_sensor_board.get_sensor_3_value() * 3300));
    printf("Sensor 4: %dmV  ", int(my_sensor_board.get_sensor_4_value() * 3300));
    printf("Sensor 5: %dmV  ", int(my_sensor_board.get_sensor_5_value() * 3300));
    printf("Sensor 6: %dmV\n", int(my_sensor_board.get_sensor_6_value() * 3300));
    ThisThread::sleep_for(1s);
  }
}