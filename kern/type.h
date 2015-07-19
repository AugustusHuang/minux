#ifndef KERN_TYPE_H
#define KERN_TYPE_H

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef int bool;

/* I don't know whether the host architecture will make effect. */
#ifndef uint32_t
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t; 
#if WORDSIZE_CONFIG == 32
typedef unsigned long long uint64_t;
#elif WORDSIZE_CONFIG == 64
typedef unsigned long int  uint64_t;
#else
#error word size doesn't supported.
#endif
#endif

#ifndef int32_t
typedef char      int8_t;
typedef short     int16_t;
typedef int       int32_t;
#if WORDSIZE_CONFIG == 32
typedef long long int64_t;
#elif WORDSIZE_CONFIG == 64
typedef long int  int64_t;
#else
#error word size doesn't supported.
#endif
#endif

typedef volatile uint8_t  vuint8_t;
typedef volatile uint16_t vuint16_t;
typedef volatile uint32_t vuint32_t;
typedef volatile uint64_t vuint64_t;
typedef volatile int8_t   vint8_t;
typedef volatile int16_t  vint16_t;
typedef volatile int32_t  vint32_t;
typedef volatile int64_t  vint64_t;

typedef char     *string;

/* TODO: We should make them change with word size or not? */
typedef int32_t   tm_t;
typedef uint32_t  pid_t;
typedef uint8_t   prio_t;
typedef uint8_t   reg_t; /* 1 - 16 */
typedef uint32_t  ts_t;
typedef int32_t   mode_t;
typedef uint32_t  key_t;

typedef char     *caddr_t;

/* Those C standard types depend on underlying architecture. */
#if WORDSIZE_CONFIG == 32
typedef uint32_t size_t;
typedef int32_t  ssize_t;
typedef int32_t  off_t; 
#elif WORDSIZE_CONFIG == 64
typedef uint64_t size_t;
typedef int64_t  ssize_t;
typedef int64_t  off_t;
#else
#error word size doesn't supported.
#endif

#ifdef UXXX_FS
typedef uint32_t  fd_t;
#endif

#endif
