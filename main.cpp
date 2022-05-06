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

void state_machine() {
  Processor my_processor(&my_drive_board, &my_sensor_board);
   my_processor.set_gain(0.007, 1, 0.000 , 0.043);
  while (true)
  {
    if (hm10.get_command() == start) {
      my_drive_board.enable_all();
      break;
    }
  }
  my_processor.reset();
  my_drive_board.set_left_motor_power(0.65);
  my_drive_board.set_right_motor_power(0.65);
  while (true) {
    // my_drive_board.disable_all();
     my_sensor_board.get_sensor_status(); 

     if (hm10.get_command() == turn_around) {
       hm10.reset();
       my_processor.stop_tracing();
       my_drive_board.set_left_motor_power(0.5);
       my_drive_board.set_right_motor_power(0.5);
       ThisThread::sleep_for(400ms);
       my_drive_board.set_left_motor_power(0.2);
       my_drive_board.set_right_motor_power(0.75);
       ThisThread::sleep_for(500ms);
       my_sensor_board.get_sensor_status();
       while (line_position(my_sensor_board.get_all_sensor_value()) > 6000) { my_sensor_board.get_sensor_status(); }
       my_drive_board.set_left_motor_power(0.75);
       my_drive_board.set_right_motor_power(0.75);
       my_processor.reset();
       my_processor.start_tracing();
     }
    //  printf("%d ", int(line_position(my_sensor_board.get_all_sensor_value()) * 10000));
    //  printf("current speed%d ", int(my_drive_board.get_current_speed() * 10000));
    //  printf("left_motor_power: %d ", int(my_drive_board.get_left_motor_power() * 10000));
    //  printf("right_motor_power: %d\n", int(my_drive_board.get_right_motor_power() * 10000));

  
  }
}


int main() {
  my_drive_board.disable_all();
  ThisThread::sleep_for(1s);
  while(true) {
    state_machine();
  }
}




