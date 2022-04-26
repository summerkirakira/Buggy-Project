#include <mbed.h>
#include <./components/BLE.h>

BLE::BLE(PinName hm1, PinName hm2, PinName status_led): hm10(hm1, hm2), status_led(status_led) {
    hm10.baud(9600);
    hm10.format(
        /* bits */ 8,
        /* parity */ SerialBase::None,
        /* stop bit */ 1
    );
    hm10.attach(callback(this, &BLE::on_rx_interrupt));
    command = stop;
}

void BLE::on_rx_interrupt(void) {
    char c;
    status_led = !status_led;
    if (hm10.read(&c, 1)) {
        if(c == 's') {
            command = stop;
        } else if (c == 'r') {
            command = start;
        } else if (c == 'p') {
            command = pause;
        } else if (c == 'e') {
            command = resume;
        } else if (c == 'h') {
            command = speed_up;
        } else if (c == 'o') {
            command = speed_down;
        } else if (c== 't') {
            command = turn_around;
        }
    }
}

command_set BLE::get_command() {
    return command;
}
