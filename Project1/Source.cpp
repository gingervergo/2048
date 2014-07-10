#include <iostream>
#include "board.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
;
using namespace std;




int main()
{
		board main;
		main.clear();
		main.spawn();
		main.spawn();
		main.score = 0;
		while (!main.over())
		{
			main.move(10);
			main.spawn();
			main.printboard();
		}

		main.printboard();
		cout <<"\n Score:   " << main.score << "\n";
	

	system("pause");
	



		

		
	
}


