#include <reg52.h>
//#include <stdio.h>
//#include <stdlib.h>

#define true 1
#define false 0

// for modular inverse
unsigned long idata t[6]={0,1};
unsigned long idata r[7];
unsigned long idata q[7]={0};

// for uart receive 
unsigned char buffer_Rx[11];
unsigned char index_Rx = 0;
bit inputComplete = 0;

// for main function
unsigned long idata n=1;
unsigned long idata phi=1;
unsigned long idata e;
unsigned long idata d;
	
void uint32ToAscii(unsigned long num,unsigned char *str) {
    unsigned char *ptr = str;
    unsigned char *start;
    unsigned char *end;
    unsigned char tempChar;

    // Convert the integer into ASCII in reverse order
    do {
        *ptr++ = (num % 10) + '0';  // Extract least significant digit
        num /= 10;                 // Remove the last digit
    } while (num);

    *ptr = '\0';  // Null-terminate the string

    // Reverse the string to correct the order
    start = str;
    end = ptr - 1;
    while (start < end) {
        tempChar = *start;
        *start++ = *end;
        *end-- = tempChar;
    }
}

unsigned long asciiToUint32(unsigned char *str) {
    unsigned long result = 0;

    // Loop through the string until null terminator is encountered
    while (*str != '\0') {
        if (*str < '0' || *str > '9') {
            break;  // Stop if a non-digit character is found
        }
        result = result * 10 + (*str - '0');  // Convert ASCII to digit and accumulate
        str++;
    }

    return result;
}

unsigned long mod_exp(unsigned long x,unsigned long e,unsigned long n)
  {
      unsigned long result=1;
      x = x % n;// to prevent overflow
      while(e>0)
      {
          if(e % 2==1) //if e is odd multiply x with the result
          {
              result=(result * x) % n;
          }
          // now e must be even , so we square x and halve e
          e=e>>1; // divide by 2
          x=(x*x) % n;
      }
      return result;
  }

unsigned long mod_inv(unsigned long idata ro,unsigned long idata rl)
{
    
    unsigned long mul;
    unsigned char z;
		r[0]=ro;
		r[1]=rl;
    for(z=2;z<=63;z++)
    {
        r[z]  =r[z-2] % r[z-1];
        q[z-1]=r[z-2] / r[z-1];
        mul=(q[z-1]*t[z-1]) % ro;
        if (mul>t[z-2])
        {
            t[z]=t[z-2]-mul+ro;
        }
        else if(mul<t[z-2])
        {
            t[z]  =t[z-2] - mul ;
        }
        if(r[z]==0)
        {
            return t[z-1];
        }
    }
    return 0;
}

unsigned long get_test_base(unsigned char index) {
    // First few prime numbers as test bases
    switch(index) {
        case 0: return 2;
        case 1: return 3;
        case 2: return 4;
        case 3: return 5;
			  case 4: return 7;
        default: return 11;
    }
	}


unsigned char primality_test(unsigned long idata p_tilt)
{
    unsigned char idata z;
    unsigned long idata a;
    
    // Basic checks first
    if (p_tilt <= 1) return false;
    if (p_tilt == 2 || p_tilt == 3 || p_tilt == 5 || p_tilt == 7) return true;
    if (p_tilt % 2 == 0) return false;
    
    // For ssmall primes (p < 100), test division by first few primes
    if (p_tilt < 100) {
        if (p_tilt % 3 == 0) return false;
        if (p_tilt % 5 == 0) return false;
        if (p_tilt % 7 == 0) return false;
        return true;  // If no small prime divides it, it's prime
    }
    
    // For larger numbers, use Fermat test
    for(z = 0; z < 5; z++)  // 5 tests are sufficient
    {
        a = get_test_base(z);
        //if(a >= p_tilt) continue;
        
        if(mod_exp(a, p_tilt-1, p_tilt) != 1)
        {
            return false;
        }
    }
    return true;
}

unsigned long gcd(unsigned long a, unsigned long b) {
	unsigned long temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

unsigned long public_exp(unsigned long phi)
{
	unsigned long i;
	for(i=2;i<phi;i++)
	{
		if(gcd(i,phi)==1)
			return i;
	}
	return 1;
}

void MSDelay(unsigned char itime)
{
	unsigned char i;
	unsigned int j;
	for(i=0;i<itime;i++)
	    for(j=0;j<1275;j++);
}

void Data_Uart(unsigned char data1)
{
	SBUF = data1 ;
	MSDelay(5);
}

void To_PC_String(unsigned char *pt)
{
	while(*pt != '\0')
	{
		Data_Uart(*pt);
		pt++;
	}
}

void serial_init()
{
	TMOD=0x20;
	TH1=-3;
  SCON=0x50;
  IE=0x90;
	PCON=PCON | 0x80;
	TR1=1;
}

unsigned long UART_ReceiveNumber() {
    unsigned long idata number = 0;

    if (inputComplete) {
        number = asciiToUint32(buffer_Rx);  // Convert ASCII string to unsigned long
        index_Rx = 0;              // Reset buffer index for the next input
        inputComplete = 0;         // Reset input complete flag
    }

    return number;
}

void serial0() interrupt 4 {
	if(TI==1)
	{
		TI=0;
	}
	else
	{
	  unsigned char receivedChar = SBUF;
		//RI=0;
		// Check for both \r and \n as line endings
        if (receivedChar == '\r' || receivedChar == '\n') {
            // Only process if we've received actual digits
            if (index_Rx > 0) {
                buffer_Rx[index_Rx] = '\0';  // Null-terminate the string
                inputComplete = 1;           // Set input complete flag
            }
        }
        // Only store digits
        else if (receivedChar >= '0' && receivedChar <= '9') {
            if (index_Rx < 11 - 1) {
                buffer_Rx[index_Rx++] = receivedChar;
            }    }
    RI=0;
	}
}
  
void main(void)
{
	bit choose = 0;
  unsigned char idata buffer_Tx[11];
	unsigned long idata p, q, PT, ct;
   serial_init();
	 while(1) {
        // Get p
        To_PC_String("p:\r\n");
        while(!inputComplete);  // Wait for complete input
        p = UART_ReceiveNumber();
        
		    // Add range check
        if(p > 65535) {  // Prevent overflow in n = p * q
            //To_PC_String("Too large\r\n");
            continue;
        }
				
        if(primality_test(p)) {
            n = p;
            phi = p - 1;
            
            // Get q
            To_PC_String("q:\r\n");
            while(!inputComplete);  // Wait for complete input
            q = UART_ReceiveNumber();
            
					  // Add range check
            if(q > 65535) {  // Prevent overflow in n = p * q
                //To_PC_String("Too large\r\n");
                //n = 1;
                //phi = 1;
                continue;
            }
					
            if(primality_test(q)) {
                n *= q;
                phi *= (q - 1);
                
                // Echo the values
                To_PC_String("n=");
                uint32ToAscii(n, buffer_Tx);
                To_PC_String(buffer_Tx);
                To_PC_String("\r\n");
                
                To_PC_String("phi=");
                uint32ToAscii(phi, buffer_Tx);
                To_PC_String(buffer_Tx);
                To_PC_String("\r\n");
							  e = public_exp(phi);
                d = mod_inv(phi,e);
		loop:			  To_PC_String("0)enc\r\n");
							  To_PC_String("1)dec\r\n");
							  while(!inputComplete);  // Wait for complete input
                choose = UART_ReceiveNumber();
							  if(choose==0) {
                // now we need to enter PT and calculate ct 
                // Get PT
                To_PC_String("x=\r\n");
                while(!inputComplete);  // Wait for complete input
                PT = UART_ReceiveNumber();
								ct = mod_exp(PT,e,n);   // y=x^e mod n
								// Echo the values
                To_PC_String("y=");
                uint32ToAscii(ct, buffer_Tx);
                To_PC_String(buffer_Tx);
                To_PC_String("\r\n");
								}
								else if(choose==1) {
								// we need to decrypt
								// Get ct
                To_PC_String("y=\r\n");
								while(!inputComplete);  // Wait for complete input
								ct = UART_ReceiveNumber();
							  PT = mod_exp(ct,d,n);  // x=y^d mod n
								To_PC_String("x=");
                uint32ToAscii(PT, buffer_Tx);
                To_PC_String(buffer_Tx);
                To_PC_String("\r\n");
								}
								else
								{
									goto loop;
								}
                break;  // Exit 
            } 
						else {
                //To_PC_String("not prime\r\n");
                //n = 1;
                //phi = 1;
                   }
        }
				else {
            //To_PC_String("not prime\r\n");
             }
    }
}
