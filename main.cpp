#include <mbed.h>
#include <./components/DriveBoard.h>

int main() {
  DriveBoard my_drive_board(PB_6, PC_7, PC_8, PC_9, PA_8, PB_10, PA_11, PB_12, PB_4);
  my_drive_board.set_left_motor_power(0.6);
  my_drive_board.set_right_motor_power(0.6);
  while(true);
}