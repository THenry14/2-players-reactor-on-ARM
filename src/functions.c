#include "MKL46Z4.h"
#include "functions.h"
#include "lcd.h"
#include "buttons.h"
#include "main.h"

void winner(int tab[]) //determine who won
{
	SegLCD_Set(tab[0], 3);
	SegLCD_Set(tab[1], 2);
}

void count(int *time) //count down
{
    if (*time != 0) {
        *time = --(*time); 
    }
}


void game(int whoClicked){ //determine who gained points
	if(isCountdownFinished==1){	
		++user[whoClicked];
	}
	else{
			++user[!whoClicked];
	}	
	isGameEnded = 1;
	winner(user);
}
