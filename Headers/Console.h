#include <cstdlib>
#include <chrono>
#include <thread>
using namespace std;

void clearScreen()
{
    #ifdef WINDOWS
        std::system("cls");
    #else
        std::system ("clear");
    #endif
}

void sleepTime(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void loadingbar(void){

	for (int i=15;i<=100;i+=5){

		clearScreen();

		printf("\n\n\n\n\n\n\n\t\t\t\t");
		printf("%d %% Loading...\n\n\t\t",i);

		printf("");

		for (int j=0; j<i;j+=2){
			cout << " ";
		}
		sleepTime(100);
		if(i==90 || i==50 || i==96 || i==83){
			sleepTime(100);
		}

	}

}

void waitForInput() {
	do {
		std::cout << '\n' << "Press a key to continue...";
		cin.get();
	} while (cin.get() != '\n');
}