#include <mbed.h>
#include <Callback.h>

enum command_set { start, stop, pause, resume, left, right, speed_up, speed_down};
class BLE {
    private:
        UnbufferedSerial hm10;
        void on_rx_interrupt(void);
        command_set command;
        DigitalOut status_led;

    public:
        BLE(PinName hm1, PinName hm2, PinName StatusLED);
        command_set get_command();
};