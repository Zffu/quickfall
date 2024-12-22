/**
 * Quickfall PE executable compiling.
 */

#include <stdio.h>
#include <stdint.h>

#include "./format.h"

/**
 * Compiles into PE format.
 */
void compilePE(FILE* fptr, uint8_t program[], int programSize, uint8_t dos[], int dosSize) {

	uint8_t buff[512] = {0};

	PE_DOS_HEADER* dos_header = (PE_DOS_HEADER*) buff;
	dos_header->e_magic = 0x5A4D;
	
	dos_header->e_cblp = (PE_DOS_HDR_SZ + dosSize) % 512;
	dos_header->e_cp = (PE_DOS_HDR_SZ + dosSize) / 512;
	dos_header->e_crlc = 0;
	dos_header->e_cparhdr = PE_DOS_HDR_SZ / 16;
	dos_header->e_minalloc = 0;
	dos_header->e_maxalloc = 0;
	
	dos_header->e_ss = 0;
	dos_header->e_sp = 0;
	dos_header->e_csum = 0;
	dos_header->e_ip = 0;
	dos_header->e_cs = 0;
	dos_header->e_lfarlc = PE_DOS_HDR_SZ;
	dos_header->e_ovno = 0;

	for(int i = 0; i < 4; ++i) {
		dos_header->e_res[i] = 0;
	}

	dos_header->e_oemid = 0;
	dos_header->e_oeminfo = 0;

	for(int i = 0; i < 10; ++i) {
		dos_header->e_res2[i] = 0;
	}

	dos_header->e_lfanew = sizeof(dos_header);

	fwrite(buff, 1, sizeof(dos_header), fptr);

	fclose(fptr);
}
