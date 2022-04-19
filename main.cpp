#include <mbed.h>
#include <./components/BLE.h>
#include <./components/DriveBoard.h>
#include <./components/SensorBoard.h>
#include <./components/PID.h>

BLE hm10(PA_11, PA_12, LED1);
DriveBoard my_drive_board(PB_1, PB_15, PC_8, PC_10, PC_12, PA_9, PC_8,PC_7, PC_3, PC_2, PB_14);


SensorBoard my_sensor_board(PA_0, PA_1,PA_4, PB_0, PC_1, PC_0, PA_8, PB_10, PB_4, PB_5, PB_3, PA_10);
PID my_pid(&my_drive_board, &my_sensor_board);

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
  my_drive_board.start_left_motor(0.8);
  my_drive_board.start_right_motor(0.6);
  // while (true)
  // {
  //   // printf("%d\n", right_motor.get_bipolar());
  // }
  while(true) {
    printf("Sensor 1: %d ", int((my_sensor_board.get_sensor_1_value() * 10000)));
    printf("Sensor 2: %d  ", int((my_sensor_board.get_sensor_2_value() * 10000)));
    printf("Sensor 3: %d  ", int((my_sensor_board.get_sensor_3_value() * 10000)));
    printf("Sensor 4: %d  ", int((my_sensor_board.get_sensor_4_value() * 10000)));
    printf("Sensor 5: %d  ", int((my_sensor_board.get_sensor_5_value() * 10000)));
    printf("Sensor 6: %d\n", int((my_sensor_board.get_sensor_6_value() * 10000)));
    ThisThread::sleep_for(1s);

  }
}




