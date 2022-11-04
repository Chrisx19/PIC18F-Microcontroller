#define _XTAL_FREQ 10000000

void decoder(char i)					//Digits
    {
        switch (i)
        {
            case 0:
                LATD = ~63;
                break;
            case 1:
                LATD = ~6;
                break;
            case 2:
                LATD = ~91;
                break;
            case 3:
                LATD = ~79;
                break;
            case 4:
                LATD = ~102;
                break;
            case 5:
                LATD = ~109;
                break;
            case 6:
                LATD = ~125;
                break;
            case 7:
                LATD = ~39;
                break;
            case 8:
                LATD = ~127;
                break;
            case 9:
                LATD = ~111;
                break;
            case 10:
                LATD = ~119;
                break;
            case 11:
                LATD = ~124;
                break;
            case 12:
                LATD = ~57;
                break;
            case 13:
                LATD = ~94;
                break;
            case 14:
                LATD = ~121;
                break;
            case 15:
                LATD = ~113;
                break;
        }
    }

void decoder_dec(char g)					//Digits with decimal points
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

void segment(char num)							//Display Values
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

void four_digits1(unsigned int n)       				//HEX
{
    unsigned char hundreds      = ((n / 256) % 16);
    unsigned char tens          = ((n / 16) % 16);
    unsigned char ones          = (n % 16);
    
    decoder(ones);
    segment(0);
    
    decoder(tens);
    segment(1);
    
    decoder(hundreds);
    segment(2);
}

void four_digits3(unsigned int h)               			//Decimals
{
    unsigned char thousands     = (h / 1000);
    unsigned char hundreds      = ((h / 100) % 10);
    unsigned char tens          = ((h / 10) % 10);
    unsigned char ones          = (h % 10);
    
    decoder(ones);
    segment(0);
    
    decoder(tens);
    segment(1);
    
    decoder_dec(hundreds);
    segment(2);
}

int main(void)                      	    //ADC Configuration plus I/O Ports
{
    ADCON0bits.FM = 1;              	    //ADC Configuration
    ADCON0bits.CS = 0;
    ADCON0bits.ON = 1;
    
    TRISFbits.TRISF4 = 0;           	    //Output values to all segment 
    TRISFbits.TRISF5 = 0;
    TRISFbits.TRISF6 = 0;
    TRISFbits.TRISF7 = 0;
    ANSELF = 0x00;
    
    TRISD = 0x00;                   	    //Output Values
    ANSELD = 0x00;

    ANSELAbits.ANSELA3 = 0;         	    //Enable push button 
    TRISAbits.TRISA3 = 1;
    WPUAbits.WPUA3 = 0x1;
    
    ANSELFbits.ANSELF0 = 0;         	    //Enable dipswitch 2 inputs
    TRISFbits.TRISF0 = 1;
    WPUFbits.WPUF0 = 0x1;
    ANSELFbits.ANSELF1 = 0;
    TRISFbits.TRISF1 = 1;
    WPUFbits.WPUF1 = 0x1;

    unsigned int total, total2, total3;
    while(1)
    {
//      Analog - CHANNEL 0                               	         //3.30 Volts
        if (PORTFbits.RF0 == 1 && PORTFbits.RF1 == 1)               //CHANNEL 0
        {
            decoder(0);
            segment(3);
            if(PORTAbits.RA3 == 0)
            {
            ADPCH=0x00; // set input ch0 - PORTA - bit0
            ADCON0bits.GO=1; // start the ADC
            while (ADCON0bits.GO); // wait here until the ADC is done
            
            total = (ADRESH*256 + ADRESL)  ;        //12bits
            four_digits1(total);                
            }
            else
            {
               four_digits1(0); 
            }
        }
        //Analog - CHANNEL 1                               	   //5.00 Volts
        if(PORTFbits.RF0 == 0 && PORTFbits.RF1 == 1)               //CHANNEL 1
        {
            decoder(1);
            segment(3);
            if(PORTAbits.RA3 == 0)
            {
            ADPCH=0x01; // set input ch1 - PORTA - bit0
            ADCON0bits.GO=1; // start the ADC
            while (ADCON0bits.GO); // wait here until the ADC is done
            
            total2 = ADRESH*256 + ADRESL;
            four_digits1(total2);                
            }
            else
            {
               four_digits1(0); 
            }
        }
        
        //Analog - CHANNEL 2                                   //9.99 Volts
        if(PORTFbits.RF0 == 1 && PORTFbits.RF1 == 0)	   	    //CHANNEL 2               
        {
            decoder(2);
            segment(3);
            if(PORTAbits.RA3 == 0)
            {
            ADPCH=0x02; // set input ch2 - PORTA - bit0
            ADCON0bits.GO=1; // start the ADC
            while (ADCON0bits.GO); // wait here until the ADC is done

            
            total3 = ADRESH*256 + ADRESL;
            four_digits3(total3/4.0990991);                
            }
            else
            {
               four_digits1(0); 
            }
        }
        //OUT OF CHANNEL BOUND --- Just for Fun --- NON CHANNEL
        if(PORTFbits.RF0 == 0 && PORTFbits.RF1 == 0)               
        {
            decoder(14);
            segment(3);
            four_digits1(3822); 		//EEEE      
        }
    }    
}
