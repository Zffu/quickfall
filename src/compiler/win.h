/**
 * Windows related Quickfall compiling.
 */

#ifndef COMPILER_WIN
#define COMPILER_WIN

/**
 * Constants for Windows Executable Format.
 */

#define DOS_HDR_SZ 0x40
#define PE_SIG_SZ   0x4
#define COFF_HDR_SZ 0x14
#define OPT_HDR_SZ  0xe0
#define PE_HDR_SZ   (PE_SIG_SZ + COFF_HDR_SZ + OPT_HDR_SZ)
#define SEC_HDR_SZ  0x28

#define IAT_ENTRY_SZ               0x4
#define IMPORT_DIR_ENTRY_SZ        0x14
#define IMPORT_LOOKUP_TBL_ENTRY_SZ IAT_ENTRY_SZ
#define NAME_TABLE_ENTRY_SZ        0x12

#define IMAGE_BASE 0x00400000
#define SEC_ALIGN  0x1000
#define FILE_ALIGN 0x200

#endif
