/**
 * Windows related compiling for Quickfall.
 */

#include <stdio.h>
#include <stdint.h>

#include "./utils.h"
#include "./win.h"

/**
 * Writes the windows executable header.
 */
inline void writeWinExecutableHeader(FILE* f, int dosStubSZ, int peOffset) {
        write8(f, 'M');                /* Magic number (2 bytes) */
        write8(f, 'Z');
        write16(f, dosStubSZ % 512); /* Last page size */
        write16(f, align_to(dosStubSZ, 512) / 512); /* Pages in file */
        write16(f, 0);                 /* Relocations */
        write16(f, WIN_DOS_HDR_SZ / 16);   /* Size of header in paragraphs */
        write16(f, 0);                 /* Minimum extra paragraphs needed */
        write16(f, 1);                 /* Maximum extra paragraphs needed */
        write16(f, 0);                 /* Initial (relative) SS value */
        write16(f, 0);                 /* Initial SP value */
        write16(f, 0);                 /* Checksum */
        write16(f, 0);                 /* Initial IP value */
        write16(f, 0);                 /* Initial (relative) CS value */
        write16(f, WIN_DOS_HDR_SZ);        /* File address of relocation table */
        write16(f, 0);                 /* Overlay number */
        write16(f, 0);                 /* Reserved0 */
        write16(f, 0);                 /* Reserved1 */
        write16(f, 0);                 /* Reserved2 */
        write16(f, 0);                 /* Reserved3 */
        write16(f, 0);                 /* OEM id */
        write16(f, 0);                 /* OEM info */
        for (int i = 0; i < 10; i++)
                write16(f, 0);         /* Reserved (10 words) */
        write32(f, peOffset);         /* File offset of PE header. */
}

/**
 * Writes the Windows PE Signature.
 */
inline void writeWinPESignature(FILE* fptr, int peOffset) {
        seek(fptr, peOffset);
        write8(fptr, 'P');
        write8(fptr, 'E');
        write8(fptr, 0);
        write8(fptr, 0);
}

/**
 * Writes the Windows COFF Header.
 */
inline void writeWinCoffHeader(FILE* fptr, int numSections) {
    write16(fptr, 0x14c); /* Machine: IMAGE_FILE_MACHINE_I386 */
    write16(fptr, numSections); /* NumberOfSections */
    write32(fptr, 0); /* TimeDateStamp */
    write32(fptr, 0); /* PointerToSymbolTable */
    write32(fptr, 0); /* NumberOfSymbols */
    write16(fptr, WIN_OPT_HDR_SZ); /* SizeOfOptionalHeader */
    write16(fptr, 0x103); /* Characteristics: no relocations, exec, 32-bit */
}

/**
 * Writes the Windows standart fields header.
 */
inline void writeWinSTDFields(FILE* fptr, int textSize, int rDataSize, int iDataSize, int bssSize, int textPtr, int rdataPtr) {
    write16(fptr, 0x10b); /* Magic: PE32 */
    write8(fptr, 0); /* MajorLinkerVersion */
    write8(fptr, 0); /* MinorLinkerVersion */
    write32(fptr, textSize); /* SizeOfCode */
    write32(fptr, rDataSize + iDataSize); /* SizeOfInitializedData */
    write32(fptr, bssSize); /* SizeOfUninitializedData */
    write32(fptr, textPtr); /* AddressOfEntryPoint */
    write32(fptr, textPtr); /* BaseOfCode */
    write32(fptr, rdataPtr); /* BaseOfData */
}

/**
 * Writes a Windows executable.
 */
inline void writeWinExecutable(FILE* fptr, uint32_t dos[], uint32_t program[], uint32_t table[]) {
    int dosSize = sizeof(dos);
    
    uint32_t dos_stub_sz = WIN_DOS_HDR_SZ + dosSize;
    uint32_t pe_offset = align_to(dos_stub_sz, 8);

    writeWinExecutableHeader(fptr, dosSize, pe_offset);
    writeWinPESignature(fptr, pe_offset);

    for(int i = 0; i < dosSize; ++i) {
        write8(fptr, dos[i]);
    }

    uint32_t num_sections = 4;

    uint32_t headers_sz = pe_offset + WIN_PE_HDR_SZ + num_sections * WIN_SEC_HDR_SZ;

    uint32_t text_rva = align_to(headers_sz, WIN_SEC_ALIGN);
    uint32_t text_offset = align_to(headers_sz, WIN_FILE_ALIGN);
    uint32_t text_sz = sizeof(program);

    uint32_t rdata_rva = align_to(text_rva + text_sz, WIN_SEC_ALIGN);
    uint32_t rdata_offset = align_to(text_offset + text_sz, WIN_FILE_ALIGN);
    uint32_t rdata_sz = sizeof(program);

    uint32_t idata_rva = align_to(rdata_rva + rdata_sz, WIN_SEC_ALIGN);
    uint32_t idata_offset = align_to(rdata_offset + rdata_sz, WIN_FILE_ALIGN);

    uint32_t num_imports = 4;
    uint32_t iat_rva = idata_rva;
    uint32_t iat_sz = (num_imports + 1) * WIN_IAT_ENTRY_SZ;
    uint32_t import_dir_table_rva = iat_rva + iat_sz;
    uint32_t import_dir_table_sz = 2 * WIN_IMPORT_DIR_ENTRY_SZ;
    uint32_t import_lookup_table_rva = import_dir_table_rva +
                                        import_dir_table_sz;
    uint32_t name_table_rva = import_lookup_table_rva +
                    (num_imports + 1) * WIN_IMPORT_LOOKUP_TBL_ENTRY_SZ;
    uint32_t dll_name_rva = name_table_rva +
                            num_imports * WIN_NAME_TABLE_ENTRY_SZ;
    uint32_t name_table_sz = num_imports * WIN_NAME_TABLE_ENTRY_SZ + 16;
    uint32_t idata_sz = name_table_rva + name_table_sz - idata_rva;

    uint32_t bss_rva = align_to(idata_rva + idata_sz, WIN_SEC_ALIGN);
    uint32_t bss_sz = 4096;
}