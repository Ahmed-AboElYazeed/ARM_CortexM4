
#include <stdio.h>
#include <rcc/rcc.h>

int main (void)
{
    volatile int x=10;
    //Rcc_clkSource_t sysClkSource= HSI_CLK;
    //Rcc_setSystemClk(sysClkSource);
    //Rcc_getSystemClk(&sysClkSource);
    while (1)
    {
        printf("%d/n", x);
        
    }
    return 0;
}



//accedently ran one time
    // Rcc_clkSource_t sysClkSource= HSI_CLK;
    // pllCongfig_t pllConfig;
    // pllConfig.pllSource= HSI_CLK;
    // pllConfig.pllM= 10;
    // pllConfig.pllN= 10;
    // pllConfig.pllP= 10;
    // pllConfig.pllQ= 10;
    // while (1)
    // {
    //     printf("%d", 10);
    //     Rcc_setSystemClk(sysClkSource);
    //     Rcc_getSystemClk(&sysClkSource);
    //     Rcc_PllConfig(&pllConfig);

    // }
//when 

//void Rcc_PllConfig(pllCongfig_t* pllConfig)
// {
//     Rcc_clkSource_t currentClkSource;
//     // Get the current system clock source
//     Rcc_getSystemClk(&currentClkSource);

//     /*
//         OFF
//         HSI -> PLL

//         HSE -> PLL
//     */
//    if (HSI_CLK == pllConfig->pllSource)
//    {
    
//    }
// }
