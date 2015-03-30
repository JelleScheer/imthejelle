#define F_CPU 1000000 // Snelheid van de CPU, met dit kristal en deze waarde, is het precies 1 seconde
#include <avr/io.h> // Laadt de IO library, deze bevat de poorten
#include <util/delay.h> // // Laadt de Delay library, nu kan je een delay instellen
#include <stdio.h> // Laadt de stdio library, deze vat de meeste nodige onderdelen

int adc_value;        // Variabelen om het resultaat op te slaan
 
void nummerLinks() // Linker nummer functie
{
	PORTB = 0b00000010; // Zet alleen PB1 aan
}

void nummerRechts() // Rechter nummer functie
{
	PORTB = 0b00000001; // Zet alleen PB0 aan
} 
 
int main(void) // Hoofd functie
{
	DDRD = 0b11111111; // Alle poorten van D op output
	DDRB = 0b00000011; // B1, B2, B3 worden op output gezet
	
	PORTB = 0b00000000; // Zet alle poorten van B op laag

	// Poorten 13 en 14 zijn de common anode
	// Poort 4 en 9 zijn de dp en worden niet gebruikt
	// PD0 = linksonderin		|		Pin 1 en 5
	// PD1 = Midden				|		Pin 7 en 17
	// PD2 = rechtsonderin		|		Pin 3 en 8
	// PD3 = Beneden			|		Pin 2 en 6
	// PD4 = linksboven			|		Pin 18 en 12
	// PD5 = boven				|		Pin 16 en 11
	// PD6 = rechtsboven		|		Pin 15 en 10
	char cijfer[16]; // Array van 16 plaatsen voor de cijfers en letters
	cijfer[0] = 0b00000010; // Nul
	cijfer[1] = 0b00111011; // Een
	cijfer[2] = 0b00010100; // Twee
	cijfer[3] = 0b00010001; // Drie
	cijfer[4] = 0b00101001; // Vier
	cijfer[5] = 0b01000001; // Vijf
	cijfer[6] = 0b01000000; // Zes
	cijfer[7] = 0b00011011; // Zeven
	cijfer[8] = 0b00000000; // Acht
	cijfer[9] = 0b00000001; // Negen
	cijfer[10] = 0b00001000; // A
	cijfer[11] = 0b01100000; // B
	cijfer[12] = 0b01000110; // C
	cijfer[13] = 0b00110000; // D
	cijfer[14] = 0b01000100; // E
	cijfer[15] = 0b01001100; // F	
	
	int teller;
	
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)); // Prescaler is 128, dus een 125 kHz
	ADMUX |= (1<<REFS0); // Zeg dat hij 5 volt moet meten
	ADMUX &= ~(1<<REFS1); // Zet de maximum op 5 volt
	ADCSRB &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0)); // Zet de ADC in free-running mode
	ADCSRA |= (1<<ADATE); // Signaal bron om te meten
	ADCSRA |= (1<<ADEN); // Start de ADC
	ADCSRA |= (1<<ADSC); //Start de conversie
	 
	while(1) // doet iets voor altijd
	{ 
		adc_value = ADCW;    // Lees de ADC  
		if(adc_value >= 0 && adc_value < 127) // 1 bit / 1 decimaal
		{ // 1 hexidecimaal
			for(teller = 0; teller < 100; teller++) // Voor teller is kleiner dan 100, en elke keer als programma hier komt, teller + 1
			{
				PORTD = cijfer[0]; // Zet de portD poorten op 0
				nummerLinks(); // Voer functie nummerLinks uit
				_delay_ms(1); // Wacht 1 ms
				PORTD = cijfer[1]; // Zet portD poorten op 1
				nummerRechts(); // Voer functie nummerRechts uit
				_delay_ms(1); // Wacht 1 ms
			}
		}
		else if(adc_value >= 127 && adc_value < 254) // 2 bit / 2 decimaal
		{ // 2 hexidecimaal
			for(teller = 0; teller < 100; teller++) // Voor teller is kleiner dan 100, en elke keer als programma hier komt, teller + 1
			{
				PORTD = cijfer[0]; // Zet de portD poorten op 0
				nummerLinks(); // Voer functie nummerLinks uit
				_delay_ms(1); // Wacht 1 ms
				PORTD = cijfer[2]; // Zet portD poorten op 1
				nummerRechts(); // Voer functie nummerRechts uit
				_delay_ms(1); // Wacht 1 ms
			}
		}
		else if(adc_value >= 254 && adc_value < 381) // 3 bit / 4 decimaal
		{ // 4 hexidecimaal
			for(teller = 0; teller < 100; teller++) // Voor teller is kleiner dan 100, en elke keer als programma hier komt, teller + 1
			{
				PORTD = cijfer[0]; // Zet de portD poorten op 0
				nummerLinks(); // Voer functie nummerLinks uit
				_delay_ms(1); // Wacht 1 ms
				PORTD = cijfer[4]; // Zet portD poorten op 1
				nummerRechts(); // Voer functie nummerRechts uit
				_delay_ms(1); // Wacht 1 ms
			}
		}
		else if(adc_value >= 381 && adc_value < 508) // 4 bit / 8 decimaal
		{ // 8 hexidecimaal
			for(teller = 0; teller < 100; teller++) // Voor teller is kleiner dan 100, en elke keer als programma hier komt, teller + 1
			{
				PORTD = cijfer[0]; // Zet de portD poorten op 0
				nummerLinks(); // Voer functie nummerLinks uit
				_delay_ms(1); // Wacht 1 ms
				PORTD = cijfer[8]; // Zet portD poorten op 1
				nummerRechts(); // Voer functie nummerRechts uit
				_delay_ms(1); // Wacht 1 ms
			}
		}
		else if(adc_value >= 508 && adc_value < 635) // 5 bit / 16 decimaal
		{ // 10 hexidecimaal
			for(teller = 0; teller < 100; teller++) // Voor teller is kleiner dan 100, en elke keer als programma hier komt, teller + 1
			{
				PORTD = cijfer[1]; // Zet de portD poorten op 0
				nummerLinks(); // Voer functie nummerLinks uit
				_delay_ms(1); // Wacht 1 ms
				PORTD = cijfer[0]; // Zet portD poorten op 1
				nummerRechts(); // Voer functie nummerRechts uit
				_delay_ms(1); // Wacht 1 ms
			}
		}
		else if(adc_value >= 635 && adc_value < 762) // 6 bit / 32 decimaal
		{ // 20 hexidecimaal
			for(teller = 0; teller < 100; teller++) // Voor teller is kleiner dan 100, en elke keer als programma hier komt, teller + 1
			{
				PORTD = cijfer[2]; // Zet de portD poorten op 0
				nummerLinks(); // Voer functie nummerLinks uit
				_delay_ms(1); // Wacht 1 ms
				PORTD = cijfer[0]; // Zet portD poorten op 1
				nummerRechts(); // Voer functie nummerRechts uit
				_delay_ms(1); // Wacht 1 ms
			}
		}
		else if(adc_value >= 762 && adc_value < 889) // 7 bit / 64 decimaal
		{ // 40 hexidecimaal
			for(teller = 0; teller < 100; teller++) // Voor teller is kleiner dan 100, en elke keer als programma hier komt, teller + 1
			{
				PORTD = cijfer[4]; // Zet de portD poorten op 0
				nummerLinks(); // Voer functie nummerLinks uit
				_delay_ms(1); // Wacht 1 ms
				PORTD = cijfer[0]; // Zet portD poorten op 1
				nummerRechts(); // Voer functie nummerRechts uit
				_delay_ms(1); // Wacht 1 ms
			}
		}
		else if(adc_value >= 889 && adc_value < 1016) // 8 bit / 128 decimaal
		{ // 80 hexidecimaal
			for(teller = 0; teller < 100; teller++) // Voor teller is kleiner dan 100, en elke keer als programma hier komt, teller + 1
			{
				PORTD = cijfer[8]; // Zet de portD poorten op 0
				nummerLinks(); // Voer functie nummerLinks uit
				_delay_ms(1); // Wacht 1 ms
				PORTD = cijfer[0]; // Zet portD poorten op 1
				nummerRechts(); // Voer functie nummerRechts uit
				_delay_ms(1); // Wacht 1 ms
			}
		}
		else // Error catching, zet FF op de display (waardes tussen de 1016 en 1023)
		{
			for(teller = 0; teller < 100; teller++) // Voor teller is kleiner dan 100, en elke keer als programma hier komt, teller + 1
			{
				PORTD = cijfer[15]; // Zet de portD poorten op 0
				nummerLinks(); // Voer functie nummerLinks uit
				_delay_ms(1); // Wacht 1 ms
				PORTD = cijfer[15]; // Zet portD poorten op 1
				nummerRechts(); // Voer functie nummerRechts uit
				_delay_ms(1); // Wacht 1 ms
			}
		}
	}	 
	return 0; // geef 0 terug
}