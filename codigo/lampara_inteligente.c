 #include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include <math.h>

#include "lcd_i2c.h"

#define BETA	3900

int main () {


	stdio_init_all ();


	adc_init();
	adc_gpio_init (27);
	adc_gpio_init (28);
	adc_select_input (1);

	gpio_init (21);
	gpio_set_dir (21, true);

	printf("Antes i2c_init/n");
	
	gpio_set_function(18, GPIO_FUNC_I2C);
	gpio_set_function(19, GPIO_FUNC_I2C);
	gpio_pull_up(18);
	gpio_pull_up(19);

	printf("Antes del lcd_init/n);
	
	lcd_init();

	printf("Antes del lcd_init/n);
	
	// Elijo el GPIO20 como salida de PWM
	gpio_set_function(20, GPIO_FUNC_PWM);
	// Devuelve una configuracion estandar de PWM
	pwm_config config = pwm_get_default_config();
	// Obtengo el numero de slice que controla el GPIO20
	uint8_t slice = pwm_gpio_to_slice_num(20);
	// Habilito PWM
	pwm_init(slice, &config, true);
	// 50% de ancho de pulso
	pwm_set_gpio_level(20, 0x8000);

	printf("Despues del pwm_init/n);
	
	while (true) {

		(adc_get_selected_input() == 1)? adc_select_input(2) : adc_select_input(1);

		uint16_t adc_reading = adc_read();
		
		lcd_clear();

		// Todo lo del LDR lo hago cuando leo el canal 1
		if(adc_get_selected_input() == 1) {
		
			uint16_t ldr_value = adc_read();
			uint32_t Reglade3=40000*(ldr_value)/4095;
			uint16_t Referencia= 300;
			
			pwm_set_gpio_level(20, 0xffff * (uint32_t)ldr_value / 4095.0);

			printf("ADC LDR %d\n", ldr_value);
		}
		else if(adc_get_selected_input() == 2) {
			// Convierto valor de ADC a temperatura si estoy leyendo el canal 2
			float temperatura = 30.0 * adc_read() / 4095.0;
			printf("ADC pote %d\n", adc_reading);
			printf("Temperatura %.2f\n", temperatura);
			char str[16];
			//sprintf(str, "T=%.2f C", temperatura / 100.f);
			sprintf(str, "T=%.2f C", temperatura);
			lcd_string(str);
		}

		sleep_ms (300);

	}

	return 0;

}
