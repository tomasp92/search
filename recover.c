#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cs50.h>

typedef uint8_t BYTE;

//Give me an array of 512 BYTES to store info.
BYTE chunks[512];
// set a count for JPG Files
int JPG_count;

bool read_file(FILE *file);
bool check_JPG_header(void);
void create_new_JPG_file(void);
void apend_to_existing_JPG_file(void);


int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open file promted by the user in comand line
    FILE *card_raw = fopen(argv[1], "r");

    // Print this messege if file not found
    if (card_raw == NULL)
    {
        printf("Could not open %s. File not found\n", argv[1]);
        return 1;
    }

    //Set JPG_count to 0
    JPG_count = 0;

    // Do
    do
    {
        read_file(card_raw);
    }
    while (read_file(card_raw));

    fclose(card_raw);
    return 0;
}

bool read_file(FILE *file)
{
    // Read chunks of 512
    if (fread(chunks, sizeof(BYTE), 512, file) == 512)
    {
        // If its start of nwe JPG
        if (check_JPG_header())
        {
            JPG_count ++;
            // If its the first .JPG start writting the file
            if (JPG_count == 1)
            {
                create_new_JPG_file();
            }
            // If not first JPG
            else
            {
                // Close the file that we were writting to and open new file
                create_new_JPG_file();
            }

        }

        // If i was writting to a file already keep writting
        else if (JPG_count > 0)
        {
            apend_to_existing_JPG_file();
        }

        return true;
    }
    return false;
}


bool check_JPG_header(void)
{
    if (chunks[0] == 0xff && chunks[1] == 0xd8 && chunks[2] == 0xff && (chunks[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    return false;
}

void create_new_JPG_file (void)
{
    char *filename = malloc(sizeof(int) * 3);
    sprintf(filename, "%03i.jpg", JPG_count - 1);
    FILE *img = fopen(filename, "w");

    if (img == NULL)
    {
        printf("Could not open. File not found\n");

    }

    fwrite(chunks, sizeof(BYTE), 512, img);
    fclose(img);
    free(filename);
    return;
}

void apend_to_existing_JPG_file(void)
{
    char *filename = malloc(sizeof(int) * 3);
    sprintf(filename, "%03i.jpg", JPG_count - 1);
    FILE *img = fopen(filename, "a");
    free(filename);
    fwrite(chunks, sizeof(BYTE), 512, img);
    fclose(img);
}