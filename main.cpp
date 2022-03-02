#include <mbed.h>
#include <./components/DriveBoard.h>

typedef enum {initialisation, stop, straight, turn_left, turn_right} BuggyState;
BuggyState state = initialisation;
bool is_manul_stop = false;
DriveBoard my_drive_board(PA_5, PA_6, PA_7, PC_10, PC_12, PB_6, PA_9,PC_7, PC_3, PC_2, PA_8);

int main() {
  // my_drive_board.stop_left_motor();
  // my_drive_board.start_right_motor(0.54);
  // my_drive_board.set_check_point();
  // while(1) {
  //   printf("angular is: %d line distance is: %d\n", int(my_drive_board.get_angular() * 1000), int(my_drive_board.get_line_distance()*1000));
  //   ThisThread::sleep_for(2s);
  // }


  float base_power = 0.72;
  while(1) {
    switch (state)
    {
    case initialisation:
      // ThisThread::sleep_for(5s);
      my_drive_board.set_left_motor_power(base_power);
      my_drive_board.set_right_motor_power(base_power);
      state = straight;
      my_drive_board.set_check_point();
      break;
    case straight:
      if(my_drive_board.get_line_distance() >= 0.5) {
        state = turn_left;
        my_drive_board.stop_left_motor();
        my_drive_board.set_check_point();
        break;
      }
      break;
    case turn_left:
      if(my_drive_board.get_angular() >= 1) {
        state = straight;
        my_drive_board.set_check_point();
        break;
      }
      break;
    default:
      state = stop;
      break;
    }
  }
}