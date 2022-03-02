#include <mbed.h>
#include <./components/DriveBoard.h>


typedef enum {initialisation, stop, straight, turn_left, turn_right, turn_around} BuggyState;
BuggyState state = initialisation;
bool is_manul_stop = false;
DriveBoard my_drive_board(PA_5, PA_6, PA_7, PC_10, PC_12, PB_6, PA_9,PC_7, PC_3, PC_2, PA_8);
int turn_left_num = 0;
int turn_right_num = 0;
bool is_turn_left = true;

int main() {
  // my_drive_board.stop_left_motor();
  // my_drive_board.start_right_motor(0.54);
  // my_drive_board.set_check_point();
  // while(1) {
  //   printf("angular is: %d line distance is: %d\n", int(my_drive_board.get_angular() * 1000), int(my_drive_board.get_line_distance()*1000));
  //   ThisThread::sleep_for(2s);
  // }


  float base_left_power = 0.56;
  float base_right_power = 0.70;
  while(1) {
    switch (state)
    {
    case initialisation:
      my_drive_board.start_left_motor(base_left_power);
      my_drive_board.start_right_motor(base_right_power);
      state = straight;
      my_drive_board.set_check_point();
      break;
    case straight:
    printf("Going straight...Line distance: %d - angular: %d\n",
        int(100*my_drive_board.get_line_distance()), int(100*my_drive_board.get_angular()));
      if(my_drive_board.get_line_distance() >= 0.5) {
        if(turn_left_num >= 3) {
          my_drive_board.set_check_point();
          state = turn_around;
          turn_left_num = 0;
          break;
        };
        if(turn_right_num >= 3) {
          my_drive_board.set_check_point();
          state = stop;
          turn_right_num = 0;
          break;
        };
        if(is_turn_left) {
          turn_left_num++;
          state = turn_left;
          my_drive_board.stop_left_motor();
          my_drive_board.set_check_point();
        } else {
          turn_right_num++;
          state = turn_right;
          my_drive_board.stop_right_motor();
          my_drive_board.set_check_point();
        }
        break;
      }
      break;
    case turn_left:
    printf("Turing left...Line distance: %d - angular: %d\n",
        int(100*my_drive_board.get_line_distance()), int(100*my_drive_board.get_angular()));
      if(my_drive_board.get_angular() >= 1) {
        state = straight;
        my_drive_board.set_check_point();
        my_drive_board.start_left_motor(base_left_power);
        break;
      }
      break;
    case turn_around:
    printf("Turing around...Line distance: %d - angular: %d\n",
        int(100*my_drive_board.get_line_distance()), int(100*my_drive_board.get_angular()));
      my_drive_board.start_left_motor(0.42);
      my_drive_board.start_right_motor(base_right_power);
      if(my_drive_board.get_angular() > 4) {
        state = straight;
        is_turn_left = false;
        my_drive_board.start_left_motor(base_left_power);
        my_drive_board.start_right_motor(base_right_power);
        my_drive_board.set_check_point();
      }
      break;
    case turn_right:
      printf("Turing right...Line distance: %d - angular: %d\n",
        int(100*my_drive_board.get_line_distance()), int(100*my_drive_board.get_angular()));
      if(my_drive_board.get_angular() <= -1) {
        state = straight;
        my_drive_board.set_check_point();
        my_drive_board.start_right_motor(base_right_power);
        break;
      }
      break;
    case stop:
      printf("*********************************Buggy stopped!!!*********************************\n");
      my_drive_board.disable_all();
      break;
    default:
      state = stop;
      break;
    }
  }
}