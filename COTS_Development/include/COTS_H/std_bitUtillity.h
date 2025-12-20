#ifndef STD_BITUTILITY_H
#define STD_BITUTILITY_H    

#include "std_int.h"

#define SET_BIT(REG,BIT)     (REG |= (1UL << BIT))
#define CLEAR_BIT(REG,BIT)   (REG &= ~(1UL << BIT))
#define TOGGLE_BIT(REG,BIT)  (REG ^= (1UL << BIT))
#define READ_BIT(REG,BIT)    ((REG >> BIT) & 1UL)
#define WRITE_BIT(REG,BIT,VAL)  (REG = (REG & ~(1UL << BIT)) | ((VAL & 1UL) << BIT)) 

#define SET_BITS(REG, MASK)     (REG |= (MASK))
#define CLEAR_BITS(REG, MASK)   (REG &= ~(MASK))
#define TOGGLE_BITS(REG, MASK)  (REG ^= (MASK))
#define READ_BITS(REG, MASK)    (REG & (MASK))
#define WRITE_BITS(REG, MASK, VAL)  (REG = (REG & ~(MASK)) | (VAL & (MASK)))

#endif // STD_BITUTILITY_H