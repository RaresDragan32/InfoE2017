1.	#ifndef F_CPU
2.	#define F_CPU 8000000UL
3.	#endif
4.	 
5.	#include <AVR/IO.h>
6.	#include <AVR/interrupt.h>
7.	#include <math.h>
8.	#include <util/delay.h>
9.	#include <string.h>
10.	#include <stdio.h>
11.	#include <stdlib.h>
12.	 
13.	#define BAUD 9600
14.	#define ubrr 51
15.	const double pi = 3.14159265358979323846;
16.	int i=1,contor_led,u=0;
17.	volatile int j=1;
18.	long vit=0;
19.	long suma=0, suma1=0;
20.	//float y,z;
21.	unsigned char r,c;
22.	char buff[200];
23.	 
24.	 
25.	void initserial(void){
26.	SREG=SREG&127;
27.	UCSR0B=(1<<RXEN0)|(1<<TXEN0);//enable transmiter and reciever
28.	UBRR0H=(unsigned char) (ubrr>>8);//set transfer rate
29.	UBRR0L=(unsigned char) ubrr ;
30.	UCSR0C=0x86;//8 data bit+1 stop data
31.	UCSR0B=UCSR0B|192;//enable USART interupt TXCIE/RXCIE
32.	 
33.	//UCSRA=UCSRA|128;//activare recieve complete interupt
34.	SREG=SREG|128;
35.	}
36.	 
37.	int prints(char *string)
38.	{
39.	   
40.	   int count =0;
41.	   while ((string[count]) != '\0')
42.	   {
43.	      while ( !( UCSR0A & (1<<UDRE0)) );  // Wait for empty transmit buffer
44.	      UDR0 = (char)string[count++];
45.	         
46.	   }    
47.	   //TxByte('_');
48.	    UCSR0A=UCSR0A & 32;
49.	   return 0;
50.	 
51.	}
52.	 
53.	 
54.	 
55.	ISR (USART_TX_vect){
56.	 
57.	}
58.	 
59.	 
60.	//****************** INTRERUPERE RECIEVE COMPLETE************
61.	ISR (USART_RX_vect){
62.	//ISR(USART_RXC_vect ){
63.	 
64.	 
65.	 r=UDR0;
66.	 OCR1A=r;
67.	}
68.	int main(void)
69.	{
70.	 DDRD=DDRD|224; // pin 7,6,5 config ca iesiri
71.	 DDRB=DDRB|6; //pin pb1, pb2 ca iesiri
72.	 DDRC=DDRC|28;///pc2,pc3,pc4
73.	 DDRD=DDRD|8;//pd3
74.	 
75.	 TCCR1A=TCCR1A|160; //OC1A si OC1B ca pwm
76.	 TCCR1B=19;//setare frecventa clock timer 64 prescaler
77.	 ICR1=1250;//setare frecventa pwm
78.	 
79.	 //TCCR2A=TCCR2A|160;
80.	 
81.	 
82.	 
83.	 TCCR2A |= (1 << COM2B1);
84.	    // set none-inverting mode
85.	    TCCR2A |= (1 << WGM21) | (1 << WGM20);
86.	    // set fast PWM Mode
87.	 
88.	    TCCR2B |= (1 << CS21);
89.	    // set prescaler to 8 and starts PWM
90.	 OCR2B = 0;
91.	    // set PWM for 50% duty cycle
92.	 initserial();
93.	 
94.	 SREG=SREG|128;
95.	 
96.	 OCR1A=50;
97.	 //OCR1B=140;
98.	sprintf(buff," Buna ziua\n");
99.	                prints(buff);
100.	 
101.	ADMUX=1;
102.	ADCSRA= ADCSRA | 128; //ADC enable
103.	 
104.	PORTD=PORTD|32;
105.	 
106.	        while(1)
107.	        {
108.	   
109.	        ADMUX=0;
110.	        suma=0;
111.	        for(i=0;i<10;i++)
112.	            {
113.	            ADCSRA = ADCSRA | 64; // ADC start conversie
114.	            _delay_us(100);
115.	            suma=suma+ADC;
116.	            _delay_ms(1);
117.	            }
118.	    suma=suma/10.0;
119.	   
120.	    ADMUX=1;
121.	    suma1=0;
122.	        for(i=0;i<10;i++)
123.	            {
124.	            ADCSRA = ADCSRA | 64; // ADC start conversie
125.	            _delay_us(100);
126.	            suma1=suma1+ADC;
127.	            _delay_ms(1);
128.	            }
129.	    suma1=suma1/10.0;
130.	           
131.	//432 220
132.	//if(suma>425)
133.	vit=(suma1/4)*((suma-220)/212.0);
134.	//vit=(suma1+4*suma-1732)/4;
135.	if(vit>=255)
136.	vit=255;
137.	if(vit<=0)
138.	vit=0;
139.	 
140.	if(suma>425)
141.	PORTC=PORTC&227;
142.	if(suma<420)
143.	PORTC=PORTC|4;
144.	if(suma<370)
145.	PORTC=PORTC|8;
146.	if(suma<310)
147.	PORTC=PORTC|16;
148.	    if(suma<250)
149.	        {PORTC=PORTC|28;
150.	        _delay_ms(100);
151.	        PORTC=PORTC&227;
152.	        _delay_ms(100);
153.	}
154.	    OCR2B=(int)vit;
155.	    OCR1A=(int)vit*35/255.0+50;
156.	 
157.	           
158.	        sprintf(buff," %ld, %ld %ld\n",suma,suma1,vit);
159.	                prints(buff);
160.	        }
161.	return 0;
162.	}
