#ifndef CRC_H_
#define CRC_H_

#include "mbed.h"


#define CRC16_POLYNOMIAL        0x9EB2
#define CRC16_INITIAL_VALUE     0xFFFF

class CRC16{
    public:
        static uint16_t computeCRC16(uint8_t const *data_p, uint8_t len);

};

#endif /* CRC_H_ */