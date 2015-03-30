#include <avr/io.h> // Laadt de IO library, deze bevat de poorten
#include <util/delay.h> // Laadt de util library en dan Delay onderdeel, deze is nodig voor de delay functie
#include <math.h> // Laadt de reken library, nu kunnen we rekenen.
 
typedef struct // We willen wat dingen definiëren
{
    float rood; //0 of 1
    float groen; //0 of 1
    float blauw; //0 of 1
} SColorRGB; // We noemen deze define: SColorRGB omdat deze de kleuren bevat
 
typedef struct // We willen wat dingen definiëren
{
    float hue; //0 tot en met 360, kleurverloop
    float saturation; //0 of 1
    float brightness; //0 of 1
}  SColorHSB; // We noemen deze define SColorHSB, omdat deze de licht bestuurt
 
void rgbFromHSB(SColorHSB __hsb,SColorRGB * __rgb) // functie rgb naar HSB
{
    if (__hsb.saturation==0)
    {
        __rgb->rood = __hsb.brightness; // Zet rood op de brightness
        __rgb->groen = __hsb.brightness; // Zet groen op de brightness
        __rgb->blauw = __hsb.brightness; // Zet blauw op de brightness
    }
    else
    {
		float max = __hsb.brightness; // Zet de maximale brightness
		float verschil = __hsb.brightness * __hsb.saturation; // Zet het verschil tussen de sat en de brightness
		float min = __hsb.brightness - verschil; // Zet het minimale brightness neer
		if (__hsb.hue < 60) // Als de hue minder is dan 60
		{
			__rgb->rood = max; // Rood wordt de wordt het maximum
			__rgb->groen = __hsb.hue * verschil / 60 + min; // Groen wordt de hue * het verschil gedeeld door 60 + het minimale
			__rgb->blauw = min; // Blauw wordt de minimum
		}
		else if (__hsb.hue < 120) // Als de hue minder is dan 120
		{
			__rgb->rood = -(__hsb.hue - 120) * verschil / 60 + min; // Rood wordt de negatieve kant van de hue-120 * het verschil gedeeld 60 + het minimale
			__rgb->groen = max; // Groen wordt het maximum
			__rgb->blauw = min; // Blauw wordt de minimum
		}
		else if (__hsb.hue < 180) // Als de hue minder is dan 180
		{
			__rgb->rood = min; // Rood wordt de minimum
			__rgb->groen = max; // Groen wordt het maximum
			__rgb->blauw = -(__hsb.hue - 120) * verschil / 60 + min; // Blauw wordt de negatieve kant van de hue - 120 * het verschil gedeeld 60 + het minimale
		}
		else if (__hsb.hue < 240) // Als de hue minder is dan 240
		{
			__rgb->rood = min; // Rood wordt de minimum
			__rgb->groen = -(__hsb.hue - 240) * verschil / 60 + min; // Groen wordt de negatieve kant van de hue - 240 * het verschil gedeeld 60 + het minimale
			__rgb->blauw = max; // Blauw wordt het maximum
		}
		else if (__hsb.hue < 300)// Als de hue minder is dan 300
		{
			__rgb->rood = -(__hsb.hue - 240) * verschil / 60 + min; // Rood wordt de negatieve kant van de hue - 240 * het verschil gedeeld 60 + het minimale
			__rgb->groen = min; // Groen wordt de minimum
			__rgb->blauw = max; // Blauw wordt het maximum
		}
		else if (__hsb.hue <= 360) // Als de hue minder is dan 360
		{
			__rgb->rood = max; // Rood wordt de wordt het maximum
			__rgb->groen = min; // Groen wordt de minimum
			__rgb->blauw = -(__hsb.hue - 360) * verschil / 60 + min; // Blauw wordt de negatieve kant van de hue - 360 * het verschil gedeeld 60 + het minimale
		}
		else
		{
			__rgb->rood = 0; // Zet rood op nul
			__rgb->groen = 0; // Zet groen op nul
			__rgb->blauw = 0; // Zet blauw op nul
		}
    }  
}
 
int main (void)
{
    DDRB  = 0b00001000; // PB3 output
    DDRD  = 0b01100000; // PD5 en PD6 outputs
 
    SColorHSB hsb; // Nemen de definitie over in een variabelen
    SColorRGB rgb; // Nemen de definitie over in een variabelen
    hsb.hue = 0; // Zetten hue op 0
    hsb.saturation = 1; // zetten saturation op 1
    hsb.brightness = .5; // zetten helderheid op 0.5
 
    TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00); // Niet inverterende snelle PWM modus
    TCCR0B = _BV(CS00); // Geen prescaling
 
    TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20); // Niet inverterende snelle PWM modus
    TCCR2B = _BV(CS20); // Geen prescaling
 
    while (1) // Doet het voor altijd
    {
        rgbFromHSB(hsb,&rgb); // Omrekenen van rood, blauw, groen naar hue, brightness en saturation
               
        OCR0A = (unsigned char)(255*rgb.rood); // Timer 1 is rood
        OCR0B = (unsigned char)(185*rgb.groen); // Timer 2 is groen
        OCR2A = (unsigned char)(150*rgb.blauw); // Timer 3 is blauw

 
        _delay_ms(10); // wacht 10 miliseconden
        if (hsb.hue==359) // Als de heu 359 is
            hsb.hue=0; // Zet de hue op 1
        else // anders
            hsb.hue++; // Hue = oude Hue + 1
    }
 
    return(0); // geef 0 terug
}
 
