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
inline void writeWinExecutableHeader(FILE* f, int dosSize) {
        uint32_t dos_stub_sz = WIN_DOS_HDR_SZ + dosSize;
        uint32_t pe_offset = align_to(dos_stub_sz, 8);

        write8(f, 'M');                /* Magic number (2 bytes) */
        write8(f, 'Z');
        write16(f, dos_stub_sz % 512); /* Last page size */
        write16(f, align_to(dos_stub_sz, 512) / 512); /* Pages in file */
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
        write32(f, pe_offset);         /* File offset of PE header. */
}

/**
 * Writes the Windows PE Signature.
 */
inline void writeWinPESignature(FILE* fptr, int dosSize) {
        uint32_t dos_stub_sz = WIN_DOS_HDR_SZ + dosSize;
        uint32_t pe_offset = align_to(dos_stub_sz, 8);

        seek(fptr, pe_offset);
        write8(fptr, 'P');
        write8(fptr, 'E');
        write8(fptr, 0);
        write8(fptr, 0);
}

/**
 * Writes a Windows executable.
 */
inline void writeWinExecutable(FILE* fptr, uint32_t dos[]) {
    int dosSize = sizeof(dos);

    writeWinExecutableHeader(fptr, dosSize);

    for(int i = 0; i < dosSize; ++i) {
        write8(fptr, dos[i]);
    }
}