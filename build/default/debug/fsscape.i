# 1 "fsscape.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "fsscape.c" 2
# 14 "fsscape.c"
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdio.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\musl_xc8.h" 1 3
# 5 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdio.h" 2 3





# 1 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\features.h" 1 3
# 11 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdio.h" 2 3
# 24 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdio.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 1 3





typedef void * va_list[1];




typedef void * __isoc_va_list[1];
# 122 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned size_t;
# 137 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long ssize_t;
# 168 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __int24 int24_t;
# 204 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __uint24 uint24_t;
# 246 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long off_t;
# 399 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef struct _IO_FILE FILE;
# 25 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdio.h" 2 3
# 52 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdio.h" 3
typedef union _G_fpos64_t {
 char __opaque[16];
 double __align;
} fpos_t;

extern FILE *const stdin;
extern FILE *const stdout;
extern FILE *const stderr;





FILE *fopen(const char *restrict, const char *restrict);
FILE *freopen(const char *restrict, const char *restrict, FILE *restrict);
int fclose(FILE *);

int remove(const char *);
int rename(const char *, const char *);

int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
void clearerr(FILE *);

int fseek(FILE *, long, int);
long ftell(FILE *);
void rewind(FILE *);

int fgetpos(FILE *restrict, fpos_t *restrict);
int fsetpos(FILE *, const fpos_t *);

size_t fread(void *restrict, size_t, size_t, FILE *restrict);
size_t fwrite(const void *restrict, size_t, size_t, FILE *restrict);

int fgetc(FILE *);
int getc(FILE *);
int getchar(void);
int ungetc(int, FILE *);
int getch(void);

int fputc(int, FILE *);
int putc(int, FILE *);
int putchar(int);
void putch(char);

char *fgets(char *restrict, int, FILE *restrict);

char *gets(char *);


int fputs(const char *restrict, FILE *restrict);
int puts(const char *);

__attribute__((__format__(__printf__, 1, 2)))
int printf(const char *restrict, ...);
__attribute__((__format__(__printf__, 2, 3)))
int fprintf(FILE *restrict, const char *restrict, ...);
__attribute__((__format__(__printf__, 2, 3)))
int sprintf(char *restrict, const char *restrict, ...);
__attribute__((__format__(__printf__, 3, 4)))
int snprintf(char *restrict, size_t, const char *restrict, ...);

__attribute__((__format__(__printf__, 1, 0)))
int vprintf(const char *restrict, __isoc_va_list);
int vfprintf(FILE *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__printf__, 2, 0)))
int vsprintf(char *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__printf__, 3, 0)))
int vsnprintf(char *restrict, size_t, const char *restrict, __isoc_va_list);

__attribute__((__format__(__scanf__, 1, 2)))
int scanf(const char *restrict, ...);
__attribute__((__format__(__scanf__, 2, 3)))
int fscanf(FILE *restrict, const char *restrict, ...);
__attribute__((__format__(__scanf__, 2, 3)))
int sscanf(const char *restrict, const char *restrict, ...);

__attribute__((__format__(__scanf__, 1, 0)))
int vscanf(const char *restrict, __isoc_va_list);
int vfscanf(FILE *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__scanf__, 2, 0)))
int vsscanf(const char *restrict, const char *restrict, __isoc_va_list);

void perror(const char *);

int setvbuf(FILE *restrict, char *restrict, int, size_t);
void setbuf(FILE *restrict, char *restrict);

char *tmpnam(char *);
FILE *tmpfile(void);




FILE *fmemopen(void *restrict, size_t, const char *restrict);
FILE *open_memstream(char **, size_t *);
FILE *fdopen(int, const char *);
FILE *popen(const char *, const char *);
int pclose(FILE *);
int fileno(FILE *);
int fseeko(FILE *, off_t, int);
off_t ftello(FILE *);
int dprintf(int, const char *restrict, ...);
int vdprintf(int, const char *restrict, __isoc_va_list);
void flockfile(FILE *);
int ftrylockfile(FILE *);
void funlockfile(FILE *);
int getc_unlocked(FILE *);
int getchar_unlocked(void);
int putc_unlocked(int, FILE *);
int putchar_unlocked(int);
ssize_t getdelim(char **restrict, size_t *restrict, int, FILE *restrict);
ssize_t getline(char **restrict, size_t *restrict, FILE *restrict);
int renameat(int, const char *, int, const char *);
char *ctermid(char *);







char *tempnam(const char *, const char *);
# 14 "fsscape.c" 2

# 1 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdlib.h" 1 3
# 21 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdlib.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 18 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long int wchar_t;
# 22 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdlib.h" 2 3

int atoi (const char *);
long atol (const char *);
long long atoll (const char *);
double atof (const char *);

float strtof (const char *restrict, char **restrict);
double strtod (const char *restrict, char **restrict);
long double strtold (const char *restrict, char **restrict);



long strtol (const char *restrict, char **restrict, int);
unsigned long strtoul (const char *restrict, char **restrict, int);
long long strtoll (const char *restrict, char **restrict, int);
unsigned long long strtoull (const char *restrict, char **restrict, int);

int rand (void);
void srand (unsigned);

void *malloc (size_t);
void *calloc (size_t, size_t);
void *realloc (void *, size_t);
void free (void *);

          void abort (void);
int atexit (void (*) (void));
          void exit (int);
          void _Exit (int);

void *bsearch (const void *, const void *, size_t, size_t, int (*)(const void *, const void *));







__attribute__((nonreentrant)) void qsort (void *, size_t, size_t, int (*)(const void *, const void *));

int abs (int);
long labs (long);
long long llabs (long long);

typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;
typedef struct { long long quot, rem; } lldiv_t;

div_t div (int, int);
ldiv_t ldiv (long, long);
lldiv_t lldiv (long long, long long);

typedef struct { unsigned int quot, rem; } udiv_t;
typedef struct { unsigned long quot, rem; } uldiv_t;
udiv_t udiv (unsigned int, unsigned int);
uldiv_t uldiv (unsigned long, unsigned long);
# 15 "fsscape.c" 2

# 1 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdint.h" 1 3
# 22 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 127 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long uintptr_t;
# 142 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long intptr_t;
# 158 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;
# 173 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long int32_t;





typedef long long int64_t;
# 188 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;
# 209 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 229 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 23 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdint.h" 2 3

typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;
typedef int24_t int_fast24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;
typedef uint24_t uint_fast24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 144 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\bits/stdint.h" 1 3
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 145 "C:\\Program Files\\Microchip\\xc8\\v2.41\\pic\\include\\c99\\stdint.h" 2 3
# 16 "fsscape.c" 2




# 1 "./fsscape.h" 1
# 57 "./fsscape.h"
typedef struct
{
    uint32_t ui32long_address;
    uint32_t ui8Page;
    uint16_t ui8ByteOffset;
}fsscape_Address_tag;


typedef struct
{
 uint8_t ui8FlashSize_MBit;
 uint16_t ui16PageSize;
 uint16_t ui16Pages;
 uint8_t ui8Shift;
}fsscape_MemoryStyle_tag;


typedef union {
    struct {
        uint8_t ui8flashSize;
        uint8_t ui8flashType;
        uint8_t ui8manufacturerID;
        uint8_t ui8dummy;
    };
    uint32_t ui32jedecID;
}fsscape_JEDECID_tag;

typedef union {
    uint8_t ui8addr[4];
    uint32_t ui32addr;
}fsscape_SRAM_index_addr_tag;
# 96 "./fsscape.h"
uint32_t olameu_mundo(uint32_t crc_value);
uint32_t FsScape_check_index_crc(uint32_t crc_value);
# 20 "fsscape.c" 2

# 1 "./my_i2c_pic18.h" 1
# 45 "./my_i2c_pic18.h"
extern void I2C_HWini(void);
extern void I2C_ModuleStart(uint32_t);
void I2C_ModuleStop();
extern void I2C_SWini(void);
extern int16_t I2C2_M_BusReset(void);
extern void I2C2_M_ClearErrors(void);
extern int16_t I2C2_M_Poll(uint8_t);
extern int16_t I2C2_M_Read(uint8_t, uint8_t, int16_t, char *);
extern int16_t I2C2_M_ReadByte(uint8_t);
extern int16_t I2C2_M_Read_Single(uint8_t DevAddr, uint8_t SubAddr, uint8_t* value);
extern int16_t I2C2_M_RecoverBus(void);
extern int16_t I2C2_M_Restart(void);
extern int16_t I2C2_M_Start(void);
extern int16_t I2C2_M_Stop(void);
extern int16_t I2C2_M_Write(uint8_t, uint8_t, int16_t, char *);
extern int16_t I2C2_M_Write24(uint8_t, uint8_t, int16_t, char *);
extern int16_t I2C2_M_WriteByte(char);
extern int16_t I2C2_M_Write_Single(uint8_t DevAddr, uint8_t SubAddr, uint8_t value);
extern void I2C2_M_ClearBus();

extern int16_t I2C_Mem_Write(uint8_t DevAddress, uint16_t MemAdress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
extern int16_t I2C_Mem_Read(uint8_t DevAddress, uint16_t MemAdress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
# 21 "fsscape.c" 2

# 1 "./crc32.h" 1
# 21 "./crc32.h"
uint32_t calculate_crc32(uint32_t state, uint8_t data);
uint32_t calculate_crc32_buffer(const uint8_t *buffer, uint8_t size);
# 22 "fsscape.c" 2





typedef enum
{
    I2C,
    SPI,
    SERIAL,
    PARALLEL,
}FsScape_interface_style_tag;







uint8_t FsScape_i2c_SRAM_addr = 0;
uint8_t FsScape_i2c_EEPROM_addr = 0;
uint8_t FsScape_i2c_FLASH_addr = 0;


const FsScape_interface_style_tag FsScape_SRAM_interface_style = I2C;
const FsScape_interface_style_tag FsScape_EEPROM_interface_style = I2C;
const FsScape_interface_style_tag FsScape_FLASH_interface_style = SPI;

fsscape_SRAM_index_addr_tag fsscape_SRAM_index_addr;





int16_t FsScape_get_index_SRAM(uint32_t *address);
int16_t FsScape_set_index_SRAM(uint32_t address_value);
int16_t FsScape_get_index_addr_SRAM();
int16_t FsScape_set_index_addr_SRAM(uint8_t address_value);
int16_t FsScape_get_index_crc_SRAM(uint32_t *crc);
int16_t FsScape_set_index_crc_SRAM(uint32_t crc_value);
uint32_t FsScape_check_index_crc(uint32_t crc_value);
uint32_t olameu_mundo(uint32_t crc_value);



int16_t FsScape_get_index_EEPROM(fsscape_Address_tag *address);
int16_t FsScape_set_index_EEPROM(fsscape_Address_tag address_value);
int16_t FsScape_get_index_addr_EEPROM(fsscape_Address_tag *address);
int16_t FsScape_set_index_addr_EEPROM(fsscape_Address_tag address_value);

int16_t FsScape_get_index_FLASH(fsscape_Address_tag *address);
int16_t FsScape_set_index_FLASH(fsscape_Address_tag address_value);
int16_t FsScape_get_index_addr_FLASH(fsscape_Address_tag *address);
int16_t FsScape_set_index_addr_FLASH(fsscape_Address_tag address_value);

int16_t FsScape_get_index_auto(fsscape_Address_tag *address);
# 105 "fsscape.c"
int16_t FsScape_get_index_SRAM(uint32_t *address)
{
    volatile uint32_t *data = address;
    int16_t value = 0;
    uint8_t _address[4];

    value = I2C_Mem_Read(0xDE, 0x20, 1, _address, 4, 0);

    if(value == 0)
    {

        *address = ((uint32_t)_address[3] << 24) | ((uint32_t)_address[2] << 16) | ((uint32_t)_address[1] << 8) | _address[0];
    }

    return value;
}

int16_t FsScape_set_index_SRAM(uint32_t address_value)
{
    uint8_t _address[4];

    _address[0] = (uint8_t)(address_value);
    _address[1] = (uint8_t)(address_value >> 8);
    _address[2] = (uint8_t)(address_value >> 16);
    _address[3] = (uint8_t)(address_value >> 24);

    return I2C_Mem_Write(0xDE, 0x20, 1, _address, 4, 0);
}

int16_t FsScape_get_index_addr_SRAM()
{

}

int16_t FsScape_set_index_addr_SRAM(uint8_t address_value)
{

}

int16_t FsScape_get_index_crc_SRAM(uint32_t *crc)
{
    volatile uint32_t *data = crc;
    int16_t value = 0;
    uint8_t _address[4];

    value = I2C_Mem_Read(0xDE, (0x20 + 4), 1, _address, 4, 0);

    if(value == 0)
    {

        *crc = ((uint32_t)_address[3] << 24) | ((uint32_t)_address[2] << 16) | ((uint32_t)_address[1] << 8) | _address[0];
    }

    return value;
}

int16_t FsScape_set_index_crc_SRAM(uint32_t crc_value)
{
    uint8_t _address[4];

    _address[0] = (uint8_t)(crc_value);
    _address[1] = (uint8_t)(crc_value >> 8);
    _address[2] = (uint8_t)(crc_value >> 16);
    _address[3] = (uint8_t)(crc_value >> 24);

    return I2C_Mem_Write(0xDE, (0x20 + 4), 1, _address, 4, 0);
}

uint32_t FsScape_check_index_crc(uint32_t crc_value)
{
    uint8_t _address[4];
    volatile uint32_t crc_computed;

    _address[3] = (uint8_t)(crc_value);
    _address[2] = (uint8_t)(crc_value >> 8);
    _address[1] = (uint8_t)(crc_value >> 16);
    _address[0] = (uint8_t)(crc_value >> 24);

    crc_computed = calculate_crc32_buffer(_address, 4);

    return crc_computed;
}

uint32_t olameu_mundo(uint32_t crc_value)
{
# 198 "fsscape.c"
    return 0;
}
