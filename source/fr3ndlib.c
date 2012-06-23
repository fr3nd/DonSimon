#include <PA9.h>

void Fsleep(int vblank) {
	int x;
	
	for (x=0; x<vblank; x++) {
		PA_WaitForVBL();
	}
}
