#ifndef KERN_TYPE_H
#define KERN_TYPE_H

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef int bool;

/* I don't know whether the host architecture will make effect.
 * I assume a 32-bit architecture. */
#ifndef uint32_t
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t; 
#endif

#ifndef int32_t
typedef char  int8_t;
typedef short int16_t;
typedef int   int32_t;
#endif

typedef volatile uint8_t  vuint8_t;
typedef volatile uint16_t vuint16_t;
typedef volatile uint32_t vuint32_t;
typedef volatile int8_t   vint8_t;
typedef volatile int16_t  vint16_t;
typedef volatile int32_t  vint32_t;

typedef int32_t   tm_t;
typedef char     *string;
typedef uint32_t  pid_t;
typedef uint8_t   prio_t;
typedef uint8_t   reg_t; /* 1 - 16 */
typedef uint32_t  ts_t;



#endif
