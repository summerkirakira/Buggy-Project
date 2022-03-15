#include <mbed.h>
#include <./components/BLE.h>

BLE::BLE(PinName hm1, PinName hm2): hm10(hm1, hm2) {
    hm10.baud(9600);
    hm10.format(
        /* bits */ 8,
        /* parity */ SerialBase::None,
        /* stop bit */ 1
    );
}

int BLE::readable(void) {
    return hm10.readable();
}

int BLE::writable(void) {
    return hm10.writable();
}

void BLE::set_command_handler(Callback< void()> func) {
    hm10.attach(func);
}