/**
 * @file main.c
 * @brief Main entry point for the MP3 Tag Reader application.
 */

#include <stdio.h>
#include <string.h>
#include "main.h"
#include "id3_reader.h"
#include "id3_writer.h"
#include "error_handling.h"

/**
 * @brief Displays the help message for the MP3 Tag Reader application.
 */
void display_help() {
    printf("\nHelp menu for Mp3 Tag Reader and Editor:\n\n");
    printf("For viewing the tags-      ./a.out -v <.mp3 file>\n");
    printf("For editing the tags-      ./a.out -e <modifier> <.mp3 file> <new_tag> \n\n");
    printf("Modifier   Function\n");
    printf("-t         Modifies Title tag\n");
    printf("-T         Modifies Track tag\n");
    printf("-a         Modifies Artist tag\n");
    printf("-A         Modifies Album tag\n");
    printf("-y         Modifies Year tag\n");
    printf("-c         Modifies Comment tag\n");
    printf("-g         Modifies Genre tag\n");
}

/**
 * @brief Main function to handle command-line arguments and execute appropriate actions.
 * 
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on success, non-zero on failure.
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        display_help();
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0) {
        display_help();
        return 0;
    } else if (strcmp(argv[1], "-v") == 0 && argc == 3) {
        view_tags(argv[2]);
    } else if (strcmp(argv[1], "-e") == 0 && argc == 5) {
        char *tag = argv[2];
        char *filename = argv[3];
        char *value = argv[4];
        if (edit_tag(filename, tag, value) != 0) {
            printf("Failed to edit tag.\n");
            return 1;
        }
        printf("Tag edited successfully✅.\n");
    } else {
        display_help();
        return 1;
    }

    return 0;
}
