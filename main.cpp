#include <mbed.h>
#include <./components/BLE.h>
#include <./components/DriveBoard.h>
#include <./components/SensorBoard.h>
// #include <./components/PID.h>
#include <./algorithm/algorithm.h>
#include <./algorithm/processor.h>

BLE hm10(PA_11, PA_12, LED1);
DriveBoard my_drive_board(PB_1, PB_15, PC_8, PC_10, PC_12, PA_9, PC_8,PC_7, PC_3, PC_2, PB_14);


SensorBoard my_sensor_board(PA_0, PA_1,PA_4, PB_0, PC_1, PC_0, PA_8, PB_10, PB_4, PB_5, PB_3, PA_10);
// PID my_pid(&my_drive_board, &my_sensor_board);

enum BuggyState {
    FORWARD,
    LEFT,
    RIGHT,
    STOP,
    LEFT_TURN
};

float speed_control(float current_speed, float target_speed) {
  float speed_difference = target_speed - current_speed;
  float speed_control_output = 0;
  if(speed_difference > 0) {
    speed_control_output = 0.1;
  } else if (speed_difference < 0) {
    speed_control_output = -0.1;
  }
  return speed_control_output;
}

void state_machine() {
  BuggyState state = STOP;
  float current_buggy_speed = 0;
  float current_left_power = 0.5;
  float current_right_power = 0.7;
  float pid_output = 0;
  while (true)
  {
    current_buggy_speed = my_drive_board.get_current_speed();
    printf("current_buggy_speed: %d\n", int(current_buggy_speed*100));
    my_pid.calculate_error();
    pid_output = my_pid.get_output();
    // printf("Speed%d\n", int(current_buggy_speed* 1000));
    if(hm10.get_command() == stop) {
      state = STOP;
    } else if (hm10.get_command() == start) {
      state = FORWARD;
    } else if (hm10.get_command() == pause) {
      state = STOP;
    } else if (hm10.get_command() == resume) {
      state = FORWARD;
    } else if (hm10.get_command() == speed_up) {
      state = FORWARD;
    } else if (hm10.get_command() == speed_down) {
      state = FORWARD;
    }
    pid_output = my_pid.get_output();
    // printf("Output%d\n", int(pid_output* 1000));
    switch(state) {
      case FORWARD:
        my_drive_board.enable_all();
        printf("current right power: %d\n", int(current_right_power*100));
        current_left_power += speed_control(current_buggy_speed, 0.5);
        current_right_power += pid_output * 0.1;
        // my_drive_board.set_left_motor_power(current_left_power);
        my_drive_board.set_right_motor_power(current_right_power);
        break;
      case STOP:
        my_drive_board.disable_all();
        break;
    }
    ThisThread::sleep_for(1000ms);
  }
  
}

int main() {
  my_drive_board.disable_all();
  ThisThread::sleep_for(1000ms);
  my_drive_board.enable_all();
  my_drive_board.start_left_motor(0.66);
  my_drive_board.start_right_motor(0.66);

  Processor my_processor(&my_drive_board, &my_sensor_board);

  my_processor.reset();
  // my_drive_board.disable_all();
  while(true) {
    // my_processor.reset();
    my_sensor_board.get_sensor_status();
    // printf("current_speed: %d\n", int(my_drive_board.get_current_speed()*10000));
    // if(my_drive_board.get_left_motor_power() < 0.5) {
    //   printf("current_left_motor_power: %d  ", int(my_drive_board.get_left_motor_power()* 10000));
    // }
    // printf("current_left_motor_power: %d  ", int(my_drive_board.get_left_motor_power()* 10000));
    // printf("current_right_motor_power: %d\n", int(my_drive_board.get_right_motor_power()* 10000));
    my_drive_board.set_left_motor_power(my_processor.get_left_recommend_power());
    my_drive_board.set_right_motor_power(my_processor.get_right_recommend_power());
    // ThisThread::sleep_for(10ms);
    // printf("Line postion: %d\n", int(line_position(my_sensor_board.get_all_sensor_value()) * 10000));
  }
}




