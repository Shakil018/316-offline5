/*
 * LED_matrix.c
 *
 * Created: 4/16/2021 2:17:30 PM
 * Author : Shakil
 */ 



#define F_CPU 1000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define STATIC 0
#define ROTATE 1

volatile unsigned char mode = STATIC;


ISR(INT2_vect)
{
	if(mode == STATIC){
		mode = ROTATE;
	}	
	else{
		mode = STATIC;
	}
}


int main(void)
{ 
    MCUCSR = (1<<JTD);
    MCUCSR = (1<<JTD);
   
   
	DDRC = 0b11111111;
	DDRD = 0b11111111;
	DDRA = 0b00000000;
	
	GICR = 1<<INT2;
	MCUCSR = MCUCSR & (0b10111111);
	sei();
	
	unsigned char cols[8], last_pos = 0;
	
	
	cols[0] = 0xFF;
	cols[1] = 0b11111011;
	cols[2] = 0b01111101;
	cols[3] = 0x00;
	cols[4] = 0x00;
	cols[5] = 0x7F;
	cols[6] = 0xFF;
	cols[7] = 0xFF;
	
	   
    while (1) 
    {
		if(mode == STATIC){
			
			int i = last_pos;
			
			int counter = 0;
			while(counter < 8)
			{
				PORTC = 1<<counter;
				PORTD = cols[i];
				
				i++;
				i = i % 8;
				counter++;
				
				_delay_ms(6);
				
			}	
			
		}
		else{
			while(1){
				int k = 0;
				for(k=0; k<20; k++)
				{
					int i = last_pos;
				
					int counter = 0;
					while(counter < 8)
					{
						PORTC = 1<<counter;
						PORTD = cols[i];
						
						i++;
						i = i % 8;
						counter++;
						
						_delay_ms(2);
					
					}
				
				}
				if(mode == STATIC) break;
				
				//_delay_ms(50);
				
				last_pos = (last_pos+1)%8;
				
			}
		}
		
    }
	
	
}

