#include "stm32f1xx.h"
#include <stdio.h>

#include "arm_math.h"
#include "arm_const_structs.h"

#define TEST_LENGTH_SAMPLES 2048

/* -------------------------------------------------------------------
* External Input and Output buffer Declarations for FFT Bin Example
* ------------------------------------------------------------------- */
extern q15_t sine_wave_10kz_q15[TEST_LENGTH_SAMPLES];
static q15_t testOutput[TEST_LENGTH_SAMPLES/2];

/* ------------------------------------------------------------------
* Global variables for FFT Bin Example
* ------------------------------------------------------------------- */
uint32_t fftSize = 1024;
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;

/* Index at which max energy of bin ocuurs */
uint32_t testIndex = 0;

/* ----------------------------------------------------------------------
* Max magnitude FFT Bin test
* ------------------------------------------------------------------- */
arm_rfft_instance_q15 my_arm_rfft_q15_instance;

int main(void)
{
  q15_t maxValue;

  /* Process the data through the RFFT/RIFFT module */
  arm_rfft_init_1024_q15(&my_arm_rfft_q15_instance, ifftFlag, doBitReverse);
  arm_rfft_q15(&my_arm_rfft_q15_instance, sine_wave_10kz_q15, testOutput);

  /* Calculates maxValue and returns corresponding BIN value */
  arm_max_q15(testOutput, fftSize, &maxValue, &testIndex);

  printf("Maximum value is %d at index %d\n", (int) maxValue, (int) testIndex);

  while (1);
}