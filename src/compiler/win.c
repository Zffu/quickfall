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

inline void writeWinSpecificFields(FILE* f, int bssPtr, int bssSize, int headersSize) {
    write32(f, WIN_IMAGE_BASE); /* ImageBase */
    write32(f, WIN_SEC_ALIGN); /* SectionAlignment */
    write32(f, WIN_FILE_ALIGN); /* FileAlignment */
    write16(f, 3); /* MajorOperatingSystemVersion */
    write16(f, 10); /* MinorOperatingSystemVersion*/
    write16(f, 0); /* MajorImageVersion */
    write16(f, 0); /* MinorImageVersion */
    write16(f, 3); /* MajorSubsystemVersion */
    write16(f, 10); /* MinorSubsystemVersion */
    write32(f, 0); /* Win32VersionValue*/
    write32(f, align_to(bssPtr + bssSize, WIN_SEC_ALIGN)); /* SizeOfImage */
    write32(f, align_to(headersSize, WIN_FILE_ALIGN)); /* SizeOfHeaders */
    write32(f, 0); /* Checksum */
    write16(f, 3); /* Subsystem: Console */
    write16(f, 0); /* DllCharacteristics */
    write32(f, 0x100000); /* SizeOfStackReserve */
    write32(f, 0x1000); /* SizeOfStackCommit */
    write32(f, 0x100000); /* SizeOfHeapReserve */
    write32(f, 0x1000); /* SizeOfHeapCommit */
    write32(f, 0); /* LoadFlags */
    write32(f, 16); /* NumberOfRvaAndSizes */
}

/**
 * Write Windows data fields.
 */
inline void writeWinDataFields(FILE* f, int importDirTablePtr, int importDirTableSize, int iatPtr, int iatSize) {
    write32(f, 0); write32(f, 0); /* Export Table. */
    write32(f, importDirTablePtr); /* Import Table. */
    write32(f, importDirTableSize);
    write32(f, 0); write32(f, 0); /* Resource Table. */
    write32(f, 0); write32(f, 0); /* Exception Table. */
    write32(f, 0); write32(f, 0); /* Certificate Table. */
    write32(f, 0); write32(f, 0); /* Base Relocation Table. */
    write32(f, 0); write32(f, 0); /* Debug. */
    write32(f, 0); write32(f, 0); /* Architecture. */
    write32(f, 0); write32(f, 0); /* Global Ptr. */
    write32(f, 0); write32(f, 0); /* TLS Table. */
    write32(f, 0); write32(f, 0); /* Load Config Table. */
    write32(f, 0); write32(f, 0); /* Bound Import. */
    write32(f, iatPtr); /* Import Address Table. */
    write32(f, iatSize);
    write32(f, 0); write32(f, 0); /* Delay Import Descriptor. */
    write32(f, 0); write32(f, 0); /* CLR Runtime Header. */
    write32(f, 0); write32(f, 0); /* (Reserved). */
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

    writeWinSTDFields(fptr, text_sz, rdata_sz, idata_sz, bss_sz, text_rva, rdata_rva);
    writeWinSpecificFields(fptr, bss_rva, bss_sz, headers_sz);
    writeWinDataFields(fptr, import_dir_table_rva, import_dir_table_sz, iat_rva, iat_sz);

    writeWinSection(fptr, ".text", text_sz, text_rva, align_to(text_sz, WIN_FILE_ALIGN), text_offset, 0x60000020);
    writeWinSection(fptr, ".rdata", rdata_sz, rdata_rva, align_to(rdata_sz, WIN_FILE_ALIGN), rdata_offset, 0x40000040);
    writeWinSection(fptr, ".idata", idata_sz, idata_rva, align_to(idata_sz, WIN_FILE_ALIGN), idata_offset, 0xc0000040);
    writeWinSection(fptr, ".bss", bss_sz, bss_rva, 0, 0, 0xc0000080);

    seek(fptr, text_offset);
    for (int i = 0; i < sizeof(program); i++) {
        write8(fptr, program[i]);
    }

    seek(fptr, rdata_offset);
    for (int i = 0; i < sizeof(table); i++) {
            write8(fptr, table[i]);
    }

    seek(fptr, idata_offset);

    write32(fptr, name_table_tva + 0 * WIN_NAME_TABLE_ENTRY_SZ);
    write32(fptr, name_table_rva + 1 * WIN_NAME_TABLE_ENTRY_SZ);
    write32(fptr, name_table_rva + 2 * WIN_NAME_TABLE_ENTRY_SZ);
    write32(fptr, name_table_rva + 3 * WIN_NAME_TABLE_ENTRY_SZ);
    write(fptr, 0);

    // Windows STD Imports

    // kernel32.dll
    write32(fptr, import_lookup_table_rva);
    write32(fptr, 0);
    write32(fptr, 0);
    write32(fptr, dll_name_rva);
    write32(fptr, iat_rva);

    // Null term
    write32(f, 0);
    write32(f, 0);
    write32(f, 0);
    write32(f, 0);
    write32(f, 0);

    write32(fptr, name_table_rva + 0 * WIN_NAME_TABLE_ENTRY_SZ);
    write32(fptr, name_table_rva + 1 * WIN_NAME_TABLE_ENTRY_SZ);
    write32(fptr, name_table_rva + 2 * WIN_NAME_TABLE_ENTRY_SZ);
    write32(fptr, name_table_rva + 3 * WIN_NAME_TABLE_ENTRY_SZ);
    write32(fptr, 0); // Null term

    // Hint table
    write16(fptr, 0);
    writestr16(fptr, "GetStdHandle");
    write16(fptr, 0);
    writestr16(fptr, "ReadFile");
    write16(fptr, 0);
    writestr16(fptr, "WriteFile");
    write16(fptr, 0);
    writestr16(fptr, "ExitProcess");
    
    // We need to put the dll name somewhere.
    writestr16(fptr, "kernel32.dll");
}
