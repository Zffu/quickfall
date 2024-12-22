/**
 * Quickfall PE Format Defintion.
 */

#include "../units.h"

#ifndef PE_FORMAT
#define PE_FORMAT

/**
 * Constants.
 */

#define PE_HEADER_SIGNATURE 0x00004550

/**
 * Structures.
 */

typdef struct PE_DOS_HEADER {
	WORD   e_magic;                     // Magic number
	WORD   e_cblp;                      // Bytes on last page of file
	WORD   e_cp;                        // Pages in file
	WORD   e_crlc;                      // Relocations
	WORD   e_cparhdr;                   // Size of header in paragraphs
	WORD   e_minalloc;                  // Minimum extra paragraphs needed
	WORD   e_maxalloc;                  // Maximum extra paragraphs needed
	WORD   e_ss;                        // Initial (relative) SS value
	WORD   e_sp;                        // Initial SP value
	WORD   e_csum;                      // Checksum
	WORD   e_ip;                        // Initial IP value
	WORD   e_cs;                        // Initial (relative) CS value
    	WORD   e_lfarlc;                    // File address of relocation table
    	WORD   e_ovno;                      // Overlay number
    	WORD   e_res[4];                    // Reserved words
    	WORD   e_oemid;                     // OEM identifier (for e_oeminfo)
    	WORD   e_oeminfo;                   // OEM information; e_oemid specific
    	WORD   e_res2[10];                  // Reserved words
    	long   e_lfanew;                    // File address of new exe header
} PE_DOS_HEADER;

typedef struct PE_FILE_HEADER {
	WORD machine;
	WORD sec_num;
	DWORD timestamp;
	DWORD symbolTablePtr;
	DWORD symbolCount;
	WORD optionalHeaderSize;
	WORD chrs;
} PE_FILE_HEADER;

typdef struct PE_OPTIONAL_HEADER {
	WORD                 Magic;
  	BYTE                 MajorLinkerVersion;
  	BYTE                 MinorLinkerVersion;
  	DWORD                SizeOfCode;
  	DWORD                SizeOfInitializedData;
  	DWORD                SizeOfUninitializedData;
  	DWORD                AddressOfEntryPoint;
  	DWORD                BaseOfCode;
  	DWORD                BaseOfData;
  	DWORD                ImageBase;
  	DWORD                SectionAlignment;
  	DWORD                FileAlignment;
  	WORD                 MajorOperatingSystemVersion;
  	WORD                 MinorOperatingSystemVersion;
  	WORD                 MajorImageVersion;
  	WORD                 MinorImageVersion;
  	WORD                 MajorSubsystemVersion;
  	WORD                 MinorSubsystemVersion;
  	DWORD                Win32VersionValue;
  	DWORD                SizeOfImage;
  	DWORD                SizeOfHeaders;
  	DWORD                CheckSum;
  	WORD                 Subsystem;
  	WORD                 DllCharacteristics;
	DWORD                SizeOfStackReserve;
 	DWORD                SizeOfStackCommit;
  	DWORD                SizeOfHeapReserve;
  	DWORD                SizeOfHeapCommit;
  	DWORD                LoaderFlags;
  	DWORD                NumberOfRvaAndSizes;
} PE_OPTIONAL_HEADER;

typedef struct PE_HEADER {
	DWORD signature;
	PE_FILE_HEADER file_header;
	PE_OPTIONAL_HEADER optional_header;
} PE_HEADER;


#endif
