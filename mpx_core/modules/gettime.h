#ifndef _GETTIME_H
#define _GETTIME_H




/*
  Procedure..: gettime
  Description..:Outputs the current time
  Params..:None
*/

void gettime();

/*
  Procedure..: BCDToDecimal
  Description..:converts from BCD format to decimal
  Params..:int BCD
*/

int BCDToDecimal(int BCD);

/*
  Procedure..: DecimalToBCD
  Description..:Converts from decimal to BCD
  Params..:int decimal
*/

int DecimalToBCD(int decimal);


#endif
