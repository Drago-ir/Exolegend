

#ifndef GPIO_H
#define GPIO_H

#include "Arduino.h"

#include "const.h"
#include "data_utils.h"
#include "user_utils.h"


namespace hal {
    class Gpio {
        public:
            Gpio();
            void initGpio(GpioPin pin, GpioMode mode);
            void writeValue(GpioPin pin, uint8_t value);
            uint8_t readValue(GpioPin pin);             
        private:
            
            
    };
};

#endif
