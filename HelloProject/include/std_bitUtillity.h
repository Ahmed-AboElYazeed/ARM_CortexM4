#ifndef STD_BITUTILITY_H
#define STD_BITUTILITY_H    

#include <stdint.h>
#define SET_BIT(REG,BIT)     (REG |= (1U << BIT))
#define CLEAR_BIT(REG,BIT)   (REG &= ~(1U << BIT))
#define TOGGLE_BIT(REG,BIT)  (REG ^= (1U << BIT))
#define READ_BIT(REG,BIT)    ((REG >> BIT) & 1U)
#define WRITE_BIT(REG,BIT,VAL)  (REG = (REG & ~(1U << BIT)) | ((VAL & 1U) << BIT)) 

#define SET_BITS(REG, MASK)     (REG |= (MASK))
#define CLEAR_BITS(REG, MASK)   (REG &= ~(MASK))
#define TOGGLE_BITS(REG, MASK)  (REG ^= (MASK))
#define READ_BITS(REG, MASK)    (REG & (MASK))
#define WRITE_BITS(REG, MASK, VAL)  (REG = (REG & ~(MASK)) | (VAL & (MASK)))

#endif // STD_BITUTILITY_H