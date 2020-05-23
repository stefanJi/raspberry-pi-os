#include "mini_uart.h"

void kernel_main(unsigned long processor_index)
{
	static unsigned int current_processor_index = 0;

	if (processor_index == 0) {
		uart_init();
	}

	while (processor_index != current_processor_index)
		;

	uart_send_string("Hello from processor ");
	uart_send(processor_index + '0');
	uart_send_string("!\r\n");

	current_processor_index++;

	if (processor_index == 0) {
		// if current_processor_index == 4 then all processors send message
		while (current_processor_index != 4)
			;
		for (;;) {
			uart_send(uart_recv());
		}
	}
}
