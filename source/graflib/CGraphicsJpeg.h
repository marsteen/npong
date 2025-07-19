//***************************************************************************
//
//
// @PROJECT  :	mvsnake
// @VERSION  :	1.0
// @FILENAME :	CGraphicsJpeg.h
// @DATE     :	24.8.2024
//
// @AUTHOR   :	Martin Steen
// @EMAIL    :	martin@martin-steen.de
//
//
//***************************************************************************

#ifndef CGraphicsJpeg_H
#define CGraphicsJpeg_H

#include <CDataRect.h>

class CGraphicsJpeg
{
    public:

        void* ReadJpeg(const char* fname, int* Width, int* Height, int* ByteProPixel);
        void* ReadJpeg(const char* fname, short* xko, short* yko, int TargetBitPerPixel);
        void* ReadJpeg(const char* Filename, int* Width, int* Height, int TargetBitPerPixel);
        bool ReadJpegHeap(char* fname, short* xko, short* yko, int TargetBitPerPixel, void* Heap);

        int WriteJpeg(const char* fname, short xw, short yw, unsigned char* buffer, int jq);
        int WriteJpeg(FILE* fp, short xw, short yw, unsigned char* buffer, int jq);



        bool OpenJpegRead(const char* filename, int* Width, int* Height, int* ByteProPixel);

        bool ReadJpegLine();
        void CloseJpeg();
        bool GetJpegSize(const char* fname, short* xsize, short* ysize, int* channels = NULL);

        void* OpenJpegFile(const char* filename);

        bool OpenJpegLines(char* Filename);
        bool ReadJpegLine(void* LineBuffer);
        void CloseJpegLines();

        bool OpenJpegWrite(const char* Filename, int Width, int Height, int JpegQuality);
        void WriteJpegLine(void* LineBuffer);
        void CloseJpegWrite();

        void SetAppendMode(bool b) { mAppendMode = b; }

        void SetFileOffset(unsigned int fo, int fs)
        {
            mFileOffset = fo;
            mFileSize = fs;
        }


        CGraphicsJpeg();
        ~CGraphicsJpeg();

    protected:


        bool InitJpegRead(int* Width, int* Height, int* ByteProPixel);


        int read_JPEG_file(const char* filename);
        int write_JPEG_file(const char* filename, int quality);
        int write_JPEG_file(FILE* outfile, int quality);

        void put_scanline(unsigned char* line_buffer, int line_size);

        int mByteProPixel;
        bool mAppendMode;
        char* mJparams;

        unsigned int mFileOffset;
        unsigned int mFileSize;

        //unsigned char* mLinePointer;
};

#endif
