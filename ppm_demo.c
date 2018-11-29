#include "ppm.h"
#include "msp430f5529.h"

int main(void) {
  WDTCTL = WDTPW | WDTHOLD;
  
  ppm_setup();
  _BIS_SR(GIE); // enable interrupts
  while (1);
  return 0;
}
