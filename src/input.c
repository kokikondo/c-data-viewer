#include "input.h"

#include <termios.h>
#include <unistd.h>

//gurobaru sengen
struct termios oldattr;

void initialize_input(){

	struct termios newattr;

	//ima no gamen no settei wo hozonn suru
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	
	//[enter wo osumade matu] settei to [nyuuryoku sita mozi wo gamen ni dasu] settei wo ohu ni suru
	newattr.c_lflag &= ~(ICANON | ECHO);

	//nyuuryoku wo matu settei ni henkou
	//0 = mozi ga kite inakutemo matazu ni susumu
	//1 = 0.5 byou dake matu
	newattr.c_cc[VMIN] = 1;
	newattr.c_cc[VTIME] = 0;

	//hennkou sita settei wo tekiou suru
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
}

void finalize_input(){

	//hozon site oita moto no settei ni modosu
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
}

int getch (){
	unsigned char ch;
	if(read(STDIN_FILENO, &ch, 1) == 1)
	{
			return (ch);
	}

	return (-1);
}
