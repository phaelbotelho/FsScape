# FsScape
# FsScape (File system Scape)

A lib to run out from the file systes when working with microcontrollers.

Inittialy developed for PICs but easy to port for other microcontroller.

FsScape [F]ile[s]ystem Scape
Independent file system, with ultra low RAM/ROM usage. Can be used in any microocntroller, since 8 bits small one until 32 bits bit micros.

Data integrety grantee on data and on memory pointer.

The system was pointer oriented, the pointer can be save on a SRAM memory, as the code was developed in this way. the pointer has an CRC32 check to enssure that is correct. This is not a complete file system, the main target here is save data with assymetrial size, in a flash memory with out waerleving, using the momory lineary (the pointer can be reseted automatically to 0 once the memory is empty).
