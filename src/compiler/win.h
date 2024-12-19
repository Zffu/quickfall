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
#define WIN_PE_HDR_SZ   (WIN_PE_SIG_SZ + WIN_COFF_HDR_SZ + WIN_OPT_HDR_SZ)
#define WIN_SEC_HDR_SZ  0x28

#define WIN_IAT_ENTRY_SZ               0x4
#define WIN_IMPORT_DIR_ENTRY_SZ        0x14
#define WIN_IMPORT_LOOKUP_TBL_ENTRY_SZ WIN_IAT_ENTRY_SZ
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
inline void writeWinExecutableHeader(FILE* fptr, int dosStubSZ, int peOffset);

/**
 * Writes the Windows PE Signature.
 */
inline void writeWinPESignature(FILE* fptr, int peOffset);

/**
 * Writes the Windows COFF Header.
 */
inline void writeWinCoffHeader(FILE* fptr, int numSections);

/**
 * Writes the Windows standart fields header.
 */
inline void writeWinSTDFields(FILE* fptr, int textSize, int rDataSize, int iDataSize, int bssSize, int textPtr, int rdataPtr);

/**
 * Writes the Windows-specific fields header.
 */
inline void writeWinSpecificFields(FILE* f, int bssPtr, int bssSize, int headersSize);

/**
 * Write Windows data fields.
 */
inline void writeWinDataFields(FILE* f, int importDirTablePtr, int importDirTableSize, int iatPtr, int iatSize);
/**
 * Writes a Windows section header.
 */
inline void writeWinSection(FILE* fptr, char* secName, int virtualSize, uint32_t virtualAddress, uint32_t size, uint32_t pointer, uint32_t characteristics);


/**
 * Writes a windows executable.
 */
inline void writeWinExecutable(FILE* fptr, uint32_t dos[], uint32_t program[], uint32_t table[]);

#endif
