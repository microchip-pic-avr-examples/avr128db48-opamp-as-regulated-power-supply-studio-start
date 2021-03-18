/**
 * \file main.c
 *
 * \brief Main source file.
 *
 (c) 2021 Microchip Technology Inc. and its subsidiaries.
    Subject to your compliance with these terms, you may use this software and
    any derivatives exclusively with Microchip products. It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

#include <atmel_start.h>

void op_amp_setup_int_resistors(uint8_t MUXWIP_gc);
uint16_t adc_sample();

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	
	op_amp_setup_int_resistors(OPAMP_OP0RESMUX_MUXWIP_WIP4_gc);
	/* Replace with your application code */
	while (1) {
		/*In this example we have output voltage of ~1.88V, check that we are within 0.1V of that, LSB of result is 1mV*/
		uint16_t OP_out = adc_sample();
		if ((1780<OP_out) & (OP_out<1980))
		{
			/*Your code goes here*/
		}
	}
}

void op_amp_setup_int_resistors(OPAMP_OP0RESMUX_MUXWIP_t MUXWIP_gc)
{
	OPAMP.OP0INMUX = OPAMP_OP0INMUX_MUXNEG_OUT_gc | OPAMP_OP0INMUX_MUXPOS_WIP_gc;
	/* MUXWIP is the bit field that decides the output voltage of the op amp
	   With VDD at 5V you will get: 
	   OPAMP_OP0RESMUX_MUXWIP_WIP4_gc -> ~1.88V
	   OPAMP_OP0RESMUX_MUXWIP_WIP3_gc -> ~2.5V
	   OPAMP_OP0RESMUX_MUXWIP_WIP2_gc -> ~3.75V */
	OPAMP.OP0RESMUX = OPAMP_OP0RESMUX_MUXTOP_VDD_gc|OPAMP_OP0RESMUX_MUXBOT_GND_gc|MUXWIP_gc;
}

uint16_t adc_sample()
{
	uint16_t res;
	ADC0.COMMAND = ADC_STCONV_bm;
	while(!(ADC0.INTFLAGS & ADC_RESRDY_bm));
	/*Right shift result by 4 due to 16 over samples*/
	res=ADC0.RES>>4;
	return res;
}