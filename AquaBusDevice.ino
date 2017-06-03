#include <AquaBusLib.h>

// Setup code
void setup()
{
  eMBInit(MB_RTU, 0x00, 0, 19200, MB_PAR_EVEN);
  eMBEnable();
}

// Main code
void loop()
{
  eMBPoll();
}

// Callback function called to get or set the value of a Coil Register
eMBErrorCode eMBRegCoilsCB (UCHAR *pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode)
{  
}

// Callback function called to get the value of an Input Discrete Register
eMBErrorCode eMBRegDiscreteCB (UCHAR *pucRegBuffer, USHORT usAddress, USHORT usNDiscrete)
{  
}

// Callback function called to get or set the value of a Holding Register
eMBErrorCode eMBRegHoldingCB (UCHAR *pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode)
{  
}

// Callback function called to get the value of an Input Register
eMBErrorCode eMBRegInputCB (UCHAR *pucRegBuffer, USHORT usAddress, USHORT usNRegs)
{  
}
