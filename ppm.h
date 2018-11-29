#ifndef PPM_H
#define PPM_H

#include "msp430f5529.h"
#include "settings.h"

extern int PPM[PPM_ARRAY_LEN];
extern int PPM_IND;

unsigned int rising_count;

int ppm_setup();
void PPM_ISR(void);


int ppm_setup(){
  
  TA0CTL = TASSEL_1 + MC_2 + ID_0; // timer config, continuous mode, 32768Hz
  TA0CCTL0 = CM_3 + CCIS_0 + SCS + CAP + CCIE; // timer capture ctl, capture on both edges, uses CCI0A (P1.2), synchronize capture signal, interrupt enabled
  P1SEL |= BIT2; // pin 1.2 in function mode
  PPM_IND = 0;
  
  return 0;

}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void PPM_ISR(void){
  if (TA0CCTL0 | CCI) { // if capture signal is currently high i.e. rising edge
    rising_count = TA0CCR0;
  } else { // else, falling edge
    PPM[PPM_IND] = TA0CCR0-rising_count; // compute difference and store
    PPM_IND++; // increment index
    PPM_IND = PPM_IND % PPM_ARRAY_LEN; // make circular
  }
}

#endif
