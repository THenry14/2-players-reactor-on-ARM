#include "MKL46Z4.h"
#include "main.h"
#include "lcd.h"
#include "functions.h"
#include "buttons.h"
#include "tpm.h"

int isCountdownFinished=0;
int time=7;
int user[2] = {0,0};
int isGameEnded=0;

int  main(){
	buttonsInitialize();
	lcd_init();
	tpm_init();
	SystemCoreClockUpdate();
	lcd_disp(time);
	
	while(1);
}
