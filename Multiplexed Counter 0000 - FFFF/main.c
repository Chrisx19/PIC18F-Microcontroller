#define _XTAL_FREQ 10000000

void decoder(char i)
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

void segment(char num)
{
    LATC = 0x00;
    switch(num)
    {//3210
        case 0:
            LATCbits.LATC0 = 1;
            __delay_ms(1);
            break;
        case 1:
            LATCbits.LATC1 = 1;
            __delay_ms(1);
            break;
        case 2:
            LATCbits.LATC2 = 1;
            __delay_ms(1);
            break;
        case 3:
            LATCbits.LATC3 = 1;
            __delay_ms(1);
            break;
    }
}

void four_digits2(unsigned char d3, unsigned char d2, unsigned char d1, unsigned char d0 )
{
    decoder(d0);
    segment(0);
    
    decoder(d1);
    segment(1);
    
    decoder(d2);
    segment(2);
    
    decoder(d3);
    segment(3);
}

void main(void) 
{
    ANSELAbits.ANSELA3 = 0;
    TRISAbits.TRISA3 = 1;
    WPUAbits.WPUA3 = 0x1;
    
    ANSELBbits.ANSELB0 = 0;
    TRISBbits.TRISB0 = 1;
    WPUBbits.WPUB0 = 0x1;
    ANSELBbits.ANSELB1 = 0;
    TRISBbits.TRISB1 = 1;
    WPUBbits.WPUB1 = 0x1;
    
    PORTC = 0x00;
    LATC = 0x00;
    ANSELC=0x00; 
    TRISC= 0x00; 
    
    ANSELF=0x00;  
    TRISF= 0xff;
    WPUF=0xff; 
    
    PORTD=0x00;
    LATD = ~0x00;
    ANSELD=0x00; 
    TRISD= 0x00; 
    
    signed char n3 = 0, n2 = 0, n1 = 0, n0 = 0;
    unsigned char total;
    
    while(1)
    {/*=================================LOADING VALUES=====================================*/
        if(PORTFbits.RF3 == 1 && PORTFbits.RF2 == 1 && PORTFbits.RF1 == 1 && PORTFbits.RF0 == 1)
        {
            total = 0;
        }
        if(PORTFbits.RF3 == 1 && PORTFbits.RF2 == 1 && PORTFbits.RF1 == 1 && PORTFbits.RF0 == 0)
        {
            total = 1;
        }
        if(PORTFbits.RF3 == 1 && PORTFbits.RF2 == 1 && PORTFbits.RF1 == 0 && PORTFbits.RF0 == 1)
        {
            total = 2;
        }
        if(PORTFbits.RF3 == 1 && PORTFbits.RF2 == 1 && PORTFbits.RF1 == 0 && PORTFbits.RF0 == 0)
        {
            total = 3;
        }
        if(PORTFbits.RF3 == 1 && PORTFbits.RF2 == 0 && PORTFbits.RF1 == 1 && PORTFbits.RF0 == 1)
        {
            total = 4;
        }
        if(PORTFbits.RF3 == 1 && PORTFbits.RF2 == 0 && PORTFbits.RF1 == 1 && PORTFbits.RF0 == 0)
        {
            total = 5;
        }
        if(PORTFbits.RF3 == 1 && PORTFbits.RF2 == 0 && PORTFbits.RF1 == 0 && PORTFbits.RF0 == 1)
        {
            total = 6;
        }
        if(PORTFbits.RF3 == 1 && PORTFbits.RF2 == 0 && PORTFbits.RF1 == 0 && PORTFbits.RF0 == 0)
        {
            total = 7;
        }
        if(PORTFbits.RF3 == 0 && PORTFbits.RF2 == 1 && PORTFbits.RF1 == 1 && PORTFbits.RF0 == 1)
        {
            total = 8;
        }
        if(PORTFbits.RF3 == 0 && PORTFbits.RF2 == 1 && PORTFbits.RF1 == 1 && PORTFbits.RF0 == 0)
        {
            total = 9;
        }
        if(PORTFbits.RF3 == 0 && PORTFbits.RF2 == 1 && PORTFbits.RF1 == 0 && PORTFbits.RF0 == 1)
        {
            total = 10;
        }
        if(PORTFbits.RF3 == 0 && PORTFbits.RF2 == 1 && PORTFbits.RF1 == 0 && PORTFbits.RF0 == 0)
        {
            total = 11;
        }
        if(PORTFbits.RF3 == 0 && PORTFbits.RF2 == 0 && PORTFbits.RF1 == 1 && PORTFbits.RF0 == 1)
        {
            total = 12;
        }
        if(PORTFbits.RF3 == 0 && PORTFbits.RF2 == 0 && PORTFbits.RF1 == 1 && PORTFbits.RF0 == 0)
        {
            total = 13;
        }
        if(PORTFbits.RF3 == 0 && PORTFbits.RF2 == 0 && PORTFbits.RF1 == 0 && PORTFbits.RF0 == 1)
        {
            total = 14;
        }
        if(PORTFbits.RF3 == 0 && PORTFbits.RF2 == 0 && PORTFbits.RF1 == 0 && PORTFbits.RF0 == 0)
        {
            total = 15;
        }
/*===================================PICKING SEGMENT DISPLAY=================================*/        
        if(PORTFbits.RF5 == 1 && PORTFbits.RF4 == 1)        
        {
            if(LOAD == 0)
            {
                n0 = total;
            }
        }
        if(PORTFbits.RF5 == 1 && PORTFbits.RF4 == 0)
        {
            if(LOAD == 0)
            {
                n1 = total;
            }
        }
        if(PORTFbits.RF5 == 0 && PORTFbits.RF4 == 1)
        {
            if(LOAD == 0)
            {
                n2 = total;
            }
        }
        if(PORTFbits.RF5 == 0 && PORTFbits.RF4 == 0)
        {
            if(LOAD == 0)
            {
                n3 = total;
            }
        }
        four_digits2(n3,n2,n1,n0);
/*===========================SPEED COUNT/RUN/PAUSED=========EXTRA CREDIT===================*/        
    while(PORTFbits.RF7 == 0)       //RUN or PAUSED
    {
        if (PORTBbits.RB0 == 1 && PORTBbits.RB1 == 1)
            for(int d = 0; d < 150; d++)                     //VERY SLOW = DELAY 600ms (4ms * 150 = 600ms)
            {
                four_digits2(n3,n2,n1,n0);
            }                                         
        if (PORTBbits.RB0 == 0 && PORTBbits.RB1 == 1)
            for(int d = 0; d < 100; d++)                     //SLOW = DELAY 400ms (4ms * 100 = 400ms)
            {
                four_digits2(n3,n2,n1,n0);
            }                                        
        if (PORTBbits.RB0 == 1 && PORTBbits.RB1 == 0)
            for(int d = 0; d < 50; d++)                     //FAST = DELAY 200ms (4ms * 50 = 200ms)
            {
                four_digits2(n3,n2,n1,n0);
            }                                          
        if (PORTBbits.RB0 == 0 && PORTBbits.RB1 == 0)       //VERY FAST = DELAY 1ms
        {
            four_digits2(n3,n2,n1,n0);
        }
/*==============================COUNTER==============EXTRA CREDIT============================*/              
        if (PORTFbits.RF6 == 1)      //COUNT UP
        {
            n0 += 1;      
            if(n0 == 16)
            { 
                n0 = 0;
                n1 += 1;
            }
            if(n1 == 16)
            {
                n1 = 0;
                n2 += 1;
            }
            if(n2 == 16)
            {
                n2 = 0;
                n3 += 1;
            }
            if(n3 == 16)
            {
                n3 = 0;
                n0 += 1;
            }   
        }
        else                       //COUNT DOWN
        {
            n0 -= 1;
            if(n0 == -1)
            { 
                n0 = 16;
                n1 -= 1;
            }
            if(n1 == -1)
            {
                n1 = 15;
                n2 -= 1;
            }
            if(n2 == -1)
            {
                n2 = 15;
                n3 -= 1;
            }
            if(n3 == -1)
            {
                n3 = 15;
                n0 -= 1;
            }
        }    
    }// 2nd While Loop
    }// Forever While Loop
}
