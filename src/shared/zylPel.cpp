/**
 * @file zylPel.cpp
 * @author  Bernhard Stoeffler
 * @brief 
 * @version 0.1
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "shared/zylPel.h"

zylPel& setARGB (uint8_t na, uint8_t nr, uint8_t ng, uint8_t nb){
	a = na; r = nr; g = ng; b = nb; 
	return *this;
}

zylPel& setAlpha (uint8_t na){
	a = na; 
	return *this;
}