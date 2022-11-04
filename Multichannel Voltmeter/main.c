#include <xc.h>
#define _XTAL_FREQ 4000000

void decoder_dec(char g)
    {
        switch (g)
        {
            case 0:
                LATD = ~191;
                break;
            case 1:
                LATD = ~134;
                break;
            case 2:
                LATD = ~219;
                break;
            case 3:
                LATD = ~207;
                break;
            case 4:
                LATD = ~230;
                break;
            case 5:
                LATD = ~237;
                break;
            case 6:
                LATD = ~253;
                break;
            case 7:
                LATD = ~167;
                break;
            case 8:
                LATD = ~255;
                break;
            case 9:
                LATD = ~239;
                break;
        }
    }     

void segment(char num)
{
    LATF = 0x00;
    switch(num)
    {//3210
        case 0:
            LATFbits.LATF4 = 1;
            __delay_ms(2);
            break;
        case 1:
            LATFbits.LATF5 = 1;
            __delay_ms(2);
            break;
        case 2:
            LATFbits.LATF6 = 1;
            __delay_ms(2);
            break;
        case 3:
            LATFbits.LATF7 = 1;
            __delay_ms(2);
            break;
    }
}

void four_digits(unsigned int h)               //Just For Fun (DECIMALS)
{
    unsigned char hundreds      = ((h / 100) % 10);
    unsigned char tens          = ((h / 10) % 10);
    unsigned char ones          = (h % 10);
    
    decoder_dec(ones);
    segment(0);
    
    decoder_dec(tens);
    segment(1);
    
    decoder_dec(hundreds);
    segment(2);
}
void main(void)
{
    TRISCbits.TRISC1 = 0;
    TRISD = 0x00;
    TRISFbits.TRISF4 = 0;
    TRISFbits.TRISF5 = 0;
    TRISFbits.TRISF6 = 0;
    TRISFbits.TRISF7 = 0;
    
    ANSELFbits.ANSELF0 = 0;         //Enable dipswitch 2 inputs
    TRISFbits.TRISF0 = 1;
    WPUFbits.WPUF0 = 0x1;
    ANSELFbits.ANSELF1 = 0;
    TRISFbits.TRISF1 = 1;
    WPUFbits.WPUF1 = 0x1;
    
    #pragma config JTAGEN = OFF
    
    ADCON0bits.FM = 1;              //ADC Configuration  RIGHT ALIGNED
    ADCON0bits.CS = 0;
    ADCON0bits.ON = 1;
    
    CCP2CONbits.MODE = 0x0c;
    CCP2CONbits.EN = 1;
    CCP2CONbits.FMT = 0;
    CCPR2H = 0x0;
    CCPR2L = 0x0;
    CCPTMRS0bits.C2TSEL = 0x1; //PWM TMR2
    
    T2CLKCON = 0x01;
    T2HLT = 0x00;
    T2RST = 0x00;
    T2PR = 0xFF;
    T2TMR = 0x00;
    PIR3bits.TMR2IF = 0;
    T2CONbits.ON = 1;
    T2CONbits.CKPS = 0;

   unsigned int total, total2, total3, duty; 
    
    while (1)
    {
//      Analog - CHANNEL 0
        if (PORTFbits.RF0 == 1 && PORTFbits.RF1 == 1)               //CHANNEL 0: 3.3v
        {
            decoder(0);
            segment(3);
            ADPCH=0x00; // set input ch0 - PORTA - bit0
            ADCON0bits.GO=1; // start the ADC
            while (ADCON0bits.GO); // wait here until the ADC is done
            
            total = (ADRESH*256 + ADRESL);        //12bits
            four_digits(total/ 12.4090909);   

        }
        //Analog - CHANNEL 1
        if(PORTFbits.RF0 == 0 && PORTFbits.RF1 == 1)               //CHANNEL 1: 5v
        {
            decoder(1);
            segment(3);

            ADPCH=0x01; // set input ch0 - PORTA - bit0
            ADCON0bits.GO=1; // start the ADC
            while (ADCON0bits.GO); // wait here until the ADC is done
            
            total2 = ADRESH*256 + ADRESL;
            four_digits(total2/8.19);                
        }
        //Analog - CHANNEL 2                                Dimmable Segment PWM
        if(PORTFbits.RF0 == 1 && PORTFbits.RF1 == 0)               
        {
            decoder(2);
            segment(0);
            LATD = ~64;
            segment(1);
            LATD = ~118;
            segment(2);
            decoder(12);
            segment(3);

            ADPCH=0x02; // set input ch0 - PORTA - bit0
            ADCON0bits.GO=1; // start the ADC
            while (ADCON0bits.GO); // wait here until the ADC is done
            
            duty = ADRESH*256 + ADRESL;
            
            duty &= 0x03FF;            
            duty = duty/4.002932551;
            CCPR2H = duty >> 8;
            CCPR2L = duty;
        }
    }    
}
/**
 End of File
*/
