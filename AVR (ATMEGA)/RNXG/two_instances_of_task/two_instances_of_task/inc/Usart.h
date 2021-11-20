void usart_init(void)
{

	UCSRB = (1<<TXEN);
	UCSRC = (1<<UCSZ1) | (1<<UCSZ0) | (1<<URSEL);
	UBRRL = 0x33;
}

void usart_send(void *ch)
{
	char *ch1;
	
	ch1 = (char*) ch;
	
	 
		
		while(*ch1)
		{
 
			while(!(UCSRA & (1<<UDRE)));
			
			
			UDR = *ch1;
			
			ch1++;
		}
		 
		
	 
}

