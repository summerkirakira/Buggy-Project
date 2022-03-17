#include <mbed.h>
#include <./components/DriveBoard.h>
#include <C12832.h>
#include <./components/BLE.h>

BLE hm10(PA_11, PA_12, LED1);
DriveBoard my_drive_board(PB_1, PB_15, PA_11, PC_10, PC_12, PB_13, PA_9,PC_7, PC_3, PC_2, PB_14);

int main() {
  float base_left_power = 0.72;
  float base_right_power = 0.32;
  while(true){
    switch(hm10.get_command()) {
        case stop:
            my_drive_board.disable_all();
            break;
        case start:
            my_drive_board.enable_all();
            my_drive_board.set_left_motor_power(base_left_power);
            my_drive_board.set_right_motor_power(base_right_power);
            break;
        default:
            break;
    }
  }
}