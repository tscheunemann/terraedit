#include <3ds.h>

class OpenArchiveFile {
    public:
        Handle fileHandle;
        OpenArchiveFile();
        void openSaveFile(const char *locationOfSave);
        void destroyArchive();
    private:
        FS_Archive extdata_archive;

};