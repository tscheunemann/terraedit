#include <iostream>
#include <stdio.h>
#include <3ds.h>
#include "fs.h"

OpenArchiveFile::OpenArchiveFile(void) {
    u32 path[3];
	path[0] = MEDIATYPE_SD;
	path[1] = 0x000016a9;
	path[2] = 0x00000000;
    const char *saveDirectory = "/";

    FS_Path fs_path = {PATH_BINARY, 12, path};
	FS_Path dirPath = fsMakePath(PATH_ASCII, saveDirectory);

    Handle dirHandle;
    Result res;

    res = FSUSER_OpenArchive( &extdata_archive, ARCHIVE_EXTDATA, fs_path );
	if (R_FAILED(res)) {
		printf("Failed to open the archive! Check if Terraria is installed\n");
	}

    FSUSER_OpenDirectory( &dirHandle, extdata_archive, dirPath );
}

void OpenArchiveFile::openSaveFile(const char *locationOfSave) {
	FS_Path saveFilePath = fsMakePath(PATH_ASCII, locationOfSave);

	Result res2;
	
	res2 = FSUSER_OpenFile( &fileHandle, extdata_archive, saveFilePath, FS_OPEN_WRITE, NULL );
	if (R_FAILED(res2)) {
		printf("Failed!\n");
	}
}

void OpenArchiveFile::destroyArchive() {
	FSUSER_CloseArchive(extdata_archive);
	FSFILE_Close(fileHandle);
}