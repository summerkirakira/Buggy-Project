#include <mbed.h>
#include <Callback.h>

class BLE {
    private:
        UnbufferedSerial hm10;
    public:
        BLE(PinName hm1, PinName hm2);
        void set_command_handler(Callback< void()> func);
        int readable(void);
        int writable(void);

};