//#ifdef USER_PROGRAM

#ifndef FILETABLE_H
#define FILETABLE_H

#ifndef BITMAP_H
#include "bitmap.h"
#endif

class FileTable {
public:
    FileTable();                        // Initialize
    ~FileTable();                        // De-allocate

    int Open(int UnixHandle);                    // Register the file handle
    int Close(int NachosHandle);                    // Unregister the file handle
    bool isOpened(int NachosHandle);

    int getUnixHandle(int NachosHandle);

    void addThread();                            // If a user thread is using this table, add it
    int delThread();                            // If a user thread is using this table, delete it

    void Print();                                // Print contents

private:
    static constexpr int MAX_FILES{100};

    int *openFiles;                            // A vector with user opened files
    BitMap *openFilesMap;                        // A bitmap to control our vector
    int usage;                                    // How many threads are using this table
};

#endif // FILETABLE_H
//#endif // USER_PROGRAM