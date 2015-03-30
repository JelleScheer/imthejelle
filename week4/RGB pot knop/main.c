#include <avr/io.h> // Laadt de IO library, deze bevat de poorten
#include <util/delay.h> // Laadt de util library en dan Delay onderdeel, deze is nodig voor de delay functie
#include <math.h> // Laadt de reken library, nu kunnen we rekenen.

int adc_value;        // Variabelen om het resultaat op te slaan
int adc_calc;
int knop = 0;

typedef struct // We willen wat dingen definiëren
{
    float rood; //0 of 1
    float groen; //0 of 1
    float blauw; //0 of 1
} SColorRGB; // We noemen deze define: SColorRGB omdat deze de kleuren bevat

void kleur(SColorRGB * __rgb)
{
	adc_value = ADCW;
	adc_calc = adc_value / 4;
	
	if(knop == 0)
	{
		__rgb->rood = adc_calc;
	}
	else if(knop == 1)
	{
		__rgb->groen = adc_calc;
	}
	else if(knop == 2)
	{
		__rgb->blauw = adc_calc;
	}
}

int main (void)
{
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)); // Prescaler is 128, dus een 125 kHz
	ADMUX |= (1<<REFS0); // Zeg dat hij 5 volt moet meten
	ADMUX &= ~(1<<REFS1); // Zet de maximum op 5 volt
	ADCSRB &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0)); // Zet de ADC in free-running mode
	ADCSRA |= (1<<ADATE); // Signaal bron om te meten
	ADCSRA |= (1<<ADEN); // Start de ADC
	ADCSRA |= (1<<ADSC); //Start de conversie
	
    DDRB  = 0b00001011; // PB3 output
    DDRD  = 0b01100000; // PD5 en PD6 outputs
	PORTB |= (1<<0); // Activeer de pull up op B1
 
    SColorRGB rgb; // Nemen de definitie over in een variabelen
 
    TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00); // Niet inverterende snelle PWM modus
    TCCR0B = _BV(CS00); // Geen prescaling
 
    TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20); // Niet inverterende snelle PWM modus
    TCCR2B = _BV(CS20); // Geen prescaling
 
    while (1) // Doet het voor altijd
    {
        OCR0A = (unsigned char)(255*rgb.rood); // Timer 1 is rood
        OCR0B = (unsigned char)(185*rgb.groen); // Timer 2 is groen
        OCR2A = (unsigned char)(150*rgb.blauw); // Timer 3 is blauw
				
		if(PINB & (1 << 0)) // Kijk als PB een input krijgt (digitaal, dus 0 of 1)
		{
			if(knop == 0)
			{
				knop = 1;
			}
			else if(knop == 1)
			{
				knop = 2;
			}
			else if(knop == 2)
			{
				knop = 0;
			}
			else
			{
				knop = 0;
			}
			_delay_ms(200);
		}
		_delay_ms(20);
		kleur(&rgb);
    }
 
    return(0); // geef 0 terug
}