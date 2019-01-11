#include <XModem.h>

XModemReceptor::XModemReceptor(HardwareSerial * ser){
  _serial = ser;
  ulTime = millis();
}

void XModemReceptor::xLoop(){
  HardwareSerial * ser = _serial;
  bool isTransfering = _isTransfering;

  if((millis() - 3000 < ulTime)&&!isTransfering){
    ulTime = millis();
    ser->write('C');
  }

  if(ser->available()){
    switch (ser->read()) {
      case SOH:
        isTransfering = true;
        bool message_is_correct;
        message_is_correct = true;

        byte * checksum;
        ser->readBytes(checksum,2);

        message_is_correct = (message_is_correct && ((checksum[0]+checksum[1])==0xFF)) ? true: false;

        byte * data;
        (* onBlock)(data); // Event on block
        ser->readBytes(data,128);
        byte * crc;
        ser->readBytes(crc,2);

        if(message_is_correct){
          ser->write(ACK);
        }
        else{
          ser->write(NAK);
        }

        break;
      case EOT:
        ser->write(ACK);
        break;
      case CAN:
        break;
      case ETB:
        ser->write(ACK);
        _isTransfering = false;
        break;
      default:
        // This is an error
        break;
    }
  }
}
