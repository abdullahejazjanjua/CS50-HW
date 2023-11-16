#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdbool.h>


#include "wav.h"

bool check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if(argc > 3)
    {
        printf("Invalid Usage\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *inptr = fopen(argv[1], "rb");
    {
        if(inptr == NULL)
        {
            printf("Could NOT open file\n");
            return 1;
        }
    }


    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    // TODO #4
    check_format(header);

    // Open output file for writing
    // TODO #5
    FILE *outptr = fopen(argv[2], "wb");
    {
        if(outptr == NULL)
        {
            printf("Could NOT open file\n");
            return 3;
        }
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, outptr);

    // Use get_block_size to calculate size of block
    // TODO #7
    int blockSize = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    fseek(inptr, 0, SEEK_END);
    long file_size = ftell(inptr);
    fseek(inptr, 0, SEEK_SET);

    long fileSize = file_size - sizeof(header);

    long NumofBlocks = fileSize / sizeof(blockSize);


    int16_t buffer[blockSize];

    fseek(inptr, - blockSize, SEEK_END);


    for (int i = 0; i < NumofBlocks; i++)
    {
        fread(&buffer, blockSize, 1, inptr);
        fwrite(&buffer, blockSize, 1, outptr);
        fseek(inptr, -2 * blockSize, SEEK_CUR);
    }

    fclose(inptr);
    fclose(outptr);
}

bool check_format(WAVHEADER header)
{
    // TODO #4
    char temp[5];
    memcpy(temp, header.format, 4);
    temp[4] = '\0';
    if(strcmp(temp, "WAVE") == 0)
    {
        return true;
    }
    return false;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int size = header.numChannels * (header.bitsPerSample/8);
    return size;
}
