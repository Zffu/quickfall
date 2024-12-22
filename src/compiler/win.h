/**
 * Quickfall Windows-Compiling (PE format).
 */

#ifndef COMPILER_WIN
#define COMPILER_WIN

/**
 * PE Format datatypes.
 */
typedef DWORD unsigned long
typedef WORD unsigned short

/**
 * PE Format Constants.
 */
//todo: we could use Windows bundled constants but that wouldn't be cross platform compiling.

#define PE_HEADER_SIGNATURE 0x00004550

/**
 * PE Format Structure Defintions.
 */
//todo: we could use Windows bundled structures but that wouldn't be cross platform compiling.

typedef struct PE_DOS_HEADER {
	WORD e_magic;
	WORD e_cblp;
	WORD e_cp;
	WORD e_crlc;
	WORD e_cpardhr;
	WORD e_minalloc;
	WORD e_maxalloc;
	WORD e_ss;
	WORD e_sp;
	WORD e_csum;
	WORD e_ip;
	WORD e_cs;
	WORD e_lfarlc;
	WORD e_ovno;
	WORD e_res[4];
	WORD e_oemid;
	WORD e_oeminfo;
	WORD e_res2[4];
	long e_lfanew;
} DOS_HEADER;

#endif
