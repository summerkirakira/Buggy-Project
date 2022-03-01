#include <mbed.h>
#include <./components/DriveBoard.h>

typedef enum {initialisation, stop, straight, turn_left, turn_right} BuggyState;
BuggyState state = stop;
bool is_manul_stop = false;
DriveBoard my_drive_board(PA_5, PA_6, PA_7, PC_10, PC_12, PB_6, PA_9,PC_7, PC_3, PC_2, PA_8);

int main() {
  // DriveBoard my_drive_board(PA_5, PA_6, PA_7, PB_6, PA_8, PB_10, PC_7, PA_9, PB_4);
  // my_drive_board.set_left_motor_power(0.1);
  // my_drive_board.set_right_motor_power(0.1);
  // DigitalOut bipolar_1(PA_5);
  // DigitalOut bipolar_2(PA_8);
  // DigitalOut pwm_1(PA_6);
  // DigitalOut pwm_2(PB_10);
  // DigitalOut enable(PB_4);
  // bipolar_1 = 0;
  // bipolar_2 = 0;
  // pwm_1 = 0;
  // pwm_2 = 0;
  // enable = 1;


  // DriveBoard my_drive_board(PA_5, PA_6, PA_7, PA_7, PB_6, PA_8, PB_10, PB_6, PC_7, PA_9, PB_4);
  // ThisThread::sleep_for(3s);
  // // my_drive_board.set_left_motor_power(0.9f);
  // my_drive_board.set_right_motor_power(0.9f);
  // while(1) {
    
  //  }
  // DigitalOut enable(PA_8);
  // PwmOut pwm1(PA_5);
  // PwmOut pwm2(PA_9);
  // pwm1.period_ms(40);
  // pwm2.period_ms(40);
  // pwm1.write(0.57);
  // pwm2.write(0.46);
  // enable = 1;

  // my_drive_board.start_left_motor(0.72);
  // my_drive_board.start_right_motor(0.72);
  // ThisThread::sleep_for(3000ms);
  // my_drive_board.turn_left_90();
  // ThisThread::sleep_for(3000ms);
  // my_drive_board.turn_left_90();
  // ThisThread::sleep_for(3000ms);
  // my_drive_board.turn_left_90();
  // ThisThread::sleep_for(3000ms);

  my_drive_board.disable_all();

  // while(1) {
    // printf("left speed is: %d right speed is: %d\n", int(my_drive_board.get_left_motor_velocity()), int(my_drive_board.get_right_motor_velocity()));
    // ThisThread::sleep_for(2s);
  // }
  float base_power = 0.72;
  while(1) {
    switch (state)
    {
    case initialisation:
      ThisThread::sleep_for(5s);
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