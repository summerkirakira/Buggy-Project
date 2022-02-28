#include <mbed.h>
#include <./components/DriveBoard.h>

int main() {
  DriveBoard my_drive_board(PA_5, PA_6, PA_7, PB_6, PA_8, PB_10, PC_7, PA_9, PB_4);
  my_drive_board.set_left_motor_power(0.6);
  my_drive_board.set_right_motor_power(0.6);
  while(true);
}