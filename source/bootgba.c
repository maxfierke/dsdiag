#include <nds.h>
#include "bootgba.h"

void BootGBA(void) {

	if(PersonalData->_user_data.gbaScreen) {
			REG_POWERCNT &= ~POWER_SWAP_LCDS;
	}
	else {
			REG_POWERCNT |= POWER_SWAP_LCDS;
	}		
	

}

