
#include <string>
#include <string.h>
#include <iostream>
 #include <fstream>
#include <sstream>

using namespace std;

string filepath;
unsigned int READBLOCKSIZE = 1024*1024;
unsigned long long nFileLength = 0;

unsigned long long accumulator = 0; // assuming 32 bit OS running on X86-64
unsigned int seekIndex[8] = {};
unsigned int threadBlockSize = 0; 
unsigned long long acc[8] = {};



//time_t seconds1;
//time_t seconds2;

int main(int argc, char *argv[])
{
    if (argc < 2) 
    {
        std::cout << "Please enter a file path\n";
        return -1;
    }

    //seconds1 = time (NULL);
    //cout << "Start Time in seconds since January 1, 1970 -> " << seconds1 << "\n";

    string path(argv[1]);
    filepath = path;
    ifstream ifsReadFile(filepath.c_str(), ifstream::binary);  // Create FileStream for the file to be read
    if(0 == ifsReadFile.is_open()) 
    {
        std::cout << "Could not find/open input file\n";
        return -1;
    }

    ifsReadFile.seekg (0, ios::end);
    nFileLength = ifsReadFile.tellg();           // get file size
    ifsReadFile.seekg (0, ios::beg);

    if(nFileLength < 16*READBLOCKSIZE)
    {
        //cout << "Using One Thread\n"; //**
        char* readBuf = new char[READBLOCKSIZE];
        if(0 == readBuf) return -1;

        unsigned int startOffset = 0;   
        if(nFileLength >  READBLOCKSIZE)
        {
            while(startOffset + READBLOCKSIZE < nFileLength)
            {
                //ifsReadFile.flush();
                ifsReadFile.read(readBuf, READBLOCKSIZE);  // At this point ifsReadFile is open
                int* num = reinterpret_cast<int*>(readBuf);
                for(unsigned int i = 0 ; i < (READBLOCKSIZE/4) ; i++) 
                {
                    accumulator += *(num + i);  
                }
                startOffset += READBLOCKSIZE;
            }

        }

        if(nFileLength - (startOffset) > 0)
        {
            ifsReadFile.read(readBuf, nFileLength - (startOffset));  
            int* num = reinterpret_cast<int*>(readBuf);
            for(unsigned int i = 0 ; i < ((nFileLength - startOffset)/4) ; ++i) 
            {
                accumulator += *(num + i);  
            }
        }
        delete[] readBuf; readBuf = 0;
    }
    


    //seconds2 = time (NULL);
    //cout << "End Time in seconds since January 1, 1970 -> " << seconds2 << "\n";
    //cout << "Total time to add " << nFileLength/4 << " integers -> " << seconds2 - seconds1 << " seconds\n";

    std::cout << accumulator << "\n";      
    return 0;
}

