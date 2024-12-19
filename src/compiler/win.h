/**
 * Windows related Quickfall compiling.
 */

#include <stdint.h>

#ifndef COMPILER_WIN
#define COMPILER_WIN

/**
 * Constants for Windows Executable Format.
 */

#define WIN_DOS_HDR_SZ 0x40
#define WIN_PE_SIG_SZ   0x4
#define WIN_COFF_HDR_SZ 0x14
#define WIN_OPT_HDR_SZ  0xe0
#define WIN_PE_HDR_SZ   (PE_SIG_SZ + COFF_HDR_SZ + OPT_HDR_SZ)
#define WIN_SEC_HDR_SZ  0x28

#define WIN_IAT_ENTRY_SZ               0x4
#define WIN_IMPORT_DIR_ENTRY_SZ        0x14
#define WIN_IMPORT_LOOKUP_TBL_ENTRY_SZ IAT_ENTRY_SZ
#define WIN_NAME_TABLE_ENTRY_SZ        0x12

#define WIN_IMAGE_BASE 0x00400000
#define WIN_SEC_ALIGN  0x1000
#define WIN_FILE_ALIGN 0x200

/**
 * Writing functions.
 */

/**
 * Writes the windows executable header.
 */
inline void writeWinExecutableHeader(FILE* fptr, int dosSize);

inline void writeWinPESignature(FILE* fptr, int dosSize);

inline void writeWinCoffHeader(FILE* fptr);

inline void writeWinSTDFields(FILE* fptr);

inline void writeWinSpecificFields(FILE* fptr);

inline void writeWinSection(FILE* fptr, char* secName, int virtualSize, uint32_t virtualAddress, uint32_t size, uint32_t pointer, uint32_t characteristics);

#endif
