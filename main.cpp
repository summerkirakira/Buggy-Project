#include <mbed.h>
#include <./components/BLE.h>
#include <./components/DriveBoard.h>
#include <./components/SensorBoard.h>
#include <./algorithm/algorithm.h>
#include <./algorithm/processor.h>
#include <./algorithm/buggy_state.h>

BLE hm10(PA_11, PA_12, LED1);
DriveBoard my_drive_board(PB_1, PC_6, PB_6, PC_10, PC_12, PA_9, PC_9,PC_7, PC_3, PC_2, PB_14);


SensorBoard my_sensor_board(PA_0, PA_1,PA_4, PB_0, PC_1, PC_0, PA_8, PB_10, PB_4, PB_5, PB_3, PA_10);

bool is_back_to_line = false;

bool has_turned_around = false;

void set_nomal_state() {
    is_back_to_line = true;
}

void state_machine() {
  BuggyState state = FORWARD;
  Processor my_processor(&my_drive_board, &my_sensor_board);
  Timeout timeout;
  while (true)
  {
    if (hm10.get_command() == start) {
      my_drive_board.enable_all();
      break;
    }
  }
  my_processor.set_gain(0.15, 100, 0.001, 0.08);
  my_processor.reset();
  while (true)
  {
    // if(hm10.get_command() == stop) {
    //   state = STOP;
    // } else if (hm10.get_command() == start) {
    //   state = FORWARD;
    //   my_drive_board.enable_all();
    // } else if (hm10.get_command() == pause) {
    //   state = STOP;
    // } else if (hm10.get_command() == resume) {
    //   state = FORWARD;
    // } else if (hm10.get_command() == speed_up) {
    //   state = FORWARD;
    // } else if (hm10.get_command() == speed_down) {
    //   state = FORWARD;
    // }
    switch(state) {
      case FORWARD:
        my_sensor_board.get_sensor_status();


        // printf("current_left_motor_power: %d  ", int(my_drive_board.get_left_motor_power()* 10000));
        // printf("current_right_motor_power: %d\n", int(my_drive_board.get_right_motor_power()* 10000));
        // printf("sensor_6: %d  \n", int(my_sensor_board.get_all_sensor_value()[0]));
        // printf("current left motor speed: %d\n", int((my_drive_board.get_current_speed()) * 10000));


        my_drive_board.set_left_motor_power(my_processor.get_left_recommend_power());
        my_drive_board.set_right_motor_power(my_processor.get_right_recommend_power());


        // ThisThread::sleep_for(10ms);
        break;
      case TURN_AROUND:
        if(has_turned_around) {
          state = STOP;
          break;
        }

        my_drive_board.set_left_motor_power(0.30);
        my_drive_board.set_right_motor_power(0.7);
        // ThisThread::sleep_for(100ms);
        my_processor.set_gain(0.15, 100, 0.000, 0.08);
        my_sensor_board.get_sensor_status();
        while (line_position(my_sensor_board.get_all_sensor_value()) > 5000) { my_sensor_board.get_sensor_status(); }
        state = FORWARD;
        // my_processor.set_gain(0.15, 100, 0.001, 0.08);
        // my_processor.soft_reset();
        // has_turned_around = true;
        break;
      case STOP:
        my_drive_board.disable_all();
        break;
    }
    state = my_processor.get_buggy_state();
    // ThisThread::sleep_for(0.0005);
    // ThisThread::sleep_for(5 * (1-(my_drive_board.get_current_speed() / 0.04) * (my_drive_board.get_current_speed() / 0.04)));
    if(state != TURN_AROUND && !is_back_to_line && 
      my_drive_board.get_current_speed() > -0.01 &&
      my_drive_board.get_current_speed() < 0.02) {
      my_drive_board.set_left_motor_power(1);
      my_drive_board.set_right_motor_power(1);
      ThisThread::sleep_for(10ms);
    } else {
      ThisThread::sleep_for(0.001);
    }
    
  }
  
}


int main() {
  my_drive_board.disable_all();
  ThisThread::sleep_for(1s);
  // my_drive_board.enable_all();
  // my_drive_board.start_left_motor(0.5);
  // my_drive_board.start_right_motor(0.5);
  // ThisThread::sleep_for(100ms);
  state_machine();
  while(true) {
  }
}




