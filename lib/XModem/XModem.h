#ifndef XMODEM_LIBRARY_H
#define XMODEM_LIBRARY_H

#include "Arduino.h"
#include "SPI.h"
#include "SD.h"

#define SOH 0x01
#define EOT 0x04
#define ACK 0x06
#define NAK 0x15
#define ETB 0x17
#define CAN 0x18
#define C 0x43

class XModemReceptor {
  public:
    XModemReceptor(HardwareSerial * ser);
    void (* onBlock)(byte *);
    void (* onAcknowledgement)();
    void (* onNonAcknowledgement)();
    void (* onCancel)();
    void (* onEndOfTransmition)();
    void xLoop();
  private:
    HardwareSerial * _serial;
    unsigned long ulTime;
    bool _isTransfering;
};

#endif
