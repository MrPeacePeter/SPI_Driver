#define SPI_BUILD_MASTER   1
//#define SPI_BUILD_SLAVE  1

#if defined(SPI_BUILD_MASTER)
#include "main_master.c"
#elif defined(SPI_BUILD_SLAVE)
#include "main_slave.c"
#else
#error "Select MASTER or SLAVE build"
#endif
