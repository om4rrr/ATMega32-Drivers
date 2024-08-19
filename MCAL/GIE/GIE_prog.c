#include "../../SERVICE/stdTypes.h"
#include "../../SERVICE/ErrorStates.h"
#include "../../SERVICE/Macro_To_Function.h"

#include "GIE_int.h"
#include "GIE_priv.h"


void GIE_VoidEnable (void) {

	Set_Bit(SREG , SREG_I) ;
}


void GIE_VoidDisable (void) {

	Clr_Bit(SREG , SREG_I) ;
}
