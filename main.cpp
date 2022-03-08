#include <mbed.h>
#include <./components/DriveBoard.h>
#include <C12832.h>
// #define left right
// #define right left



typedef enum {initialisation, stop, straight, turn_left, turn_right, turn_around} BuggyState;
BuggyState state = initialisation;
bool is_manul_stop = false;
DriveBoard my_drive_board(PB_1, PB_15, PA_11, PC_10, PC_12, PB_13, PA_9,PC_7, PC_3, PC_2, PB_14);
int turn_left_num = 0;
int turn_right_num = 0;
bool is_turn_left = true;

void display_velocity() {
  
}

int main() {
  my_drive_board.disable_all();
  C12832 my_lcd(D11, D13, D12, D7, D10);
  // my_drive_board.stop_left_motor();
  // my_drive_board.start_right_motor(0.54);
  // my_drive_board.set_check_point();
  // while(1) {
  //   printf("angular is: %d line distance is: %d\n", int(my_drive_board.get_angular() * 1000), int(my_drive_board.get_line_distance()*1000));
  //   ThisThread::sleep_for(2s);
  // }
  Ticker my_ticker;
  // my_ticker.attach_us(&display_velocity, 2000000);
  display_velocity();
  my_drive_board.enable_all();
  float base_left_power = 0.62;
  float base_right_power = 0.62;
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
    my_lcd.locate(0, 0);
    my_lcd.printf("left motor spped: %04d\nright motor speed: %d", int(100*my_drive_board.get_left_motor_velocity()), int(100*my_drive_board.get_right_motor_velocity()));
    printf("Going straight...Line distance: %d - angular: %d\n",

        int(100*my_drive_board.get_line_distance()), int(100*my_drive_board.get_angular()));
      if(my_drive_board.get_line_distance() >= 0.68) {
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
          my_drive_board.start_left_motor(0.25);
          my_drive_board.start_right_motor(0.62);
          my_drive_board.set_check_point();
        } else {
          turn_right_num++;
          state = turn_right;
          my_drive_board.start_right_motor(0.32);
          my_drive_board.set_check_point();
        }
        break;
      }
      break;
    case turn_left:
    printf("Turing left...Line distance: %d - angular: %d\n",
        int(100*my_drive_board.get_line_distance()), int(100*my_drive_board.get_angular()));
      if(my_drive_board.get_angular() >= 1.44) {
        state = straight;
        my_drive_board.set_check_point();
        my_drive_board.start_left_motor(base_left_power);
        break;
      }
      break;
    case turn_around:
    printf("Turing around...Line distance: %d - angular: %d\n",
        int(100*my_drive_board.get_line_distance()), int(100*my_drive_board.get_angular()));
      my_drive_board.start_left_motor(0.28);
      my_drive_board.start_right_motor(base_right_power);
      if(my_drive_board.get_angular() > 2.6) {
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
      if(my_drive_board.get_angular() <= -1.5) {
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