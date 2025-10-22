/**
 * @file id3_reader.c
 * @brief Implementation of functions for reading ID3 tags from MP3 files.
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "id3_reader.h"
#include "error_handling.h"

/**
TODO: Add documention as sample given
 */
TagData* read_id3_tags(const char *filename) { //just a function which makes the pointers)(inside struct) to point to the the infos 
    // Implementation for reading ID3 tags
    TagData* data = create_tag_data();
    
    FILE* fptr = fopen(filename,"rb");

    if(fptr == NULL)
    {
        printf("Opening file has failed\n");
        return NULL ;
    }



    unsigned char mainheader[10]; //array storing info about main header 
    fread(mainheader,1,10,fptr);
    data->version = malloc(6);
    data->version[5]='\0';

    memcpy(data->version,mainheader,5);

    if(mainheader[0] != 'I' || mainheader[1] != 'D' || mainheader[2]!='3')
    {
        printf("Not an ID3 tag.");
        return NULL;
    }

    if(mainheader[3] != 3)
    {
        printf("Not version 3\n");
        return NULL;
    }
   

    //extracting the size of the metadata excluding the main header tag (synchsafe)
    int mainsize = mainheader[6] << 21 | mainheader[7] << 14 | mainheader[8] << 7 | mainheader[9] ;
    
    int pos=0;
    char* temp;
    while(pos < mainsize)                                                            //increments the pos according to the bytes we read until it equals main size
    { 
        unsigned char frame_header[10];                                                      //stores the 10 bytes of frame headers
        fread(frame_header,1,10,fptr);
        pos = pos + 10;

        unsigned char frame_id[5];                                                           //stores the id as string
        memcpy(frame_id,frame_header,4);
        frame_id[4] = '\0';
        //printf("id - %s\n",frame_id);
        //printf("%s\n",frame_id);
        //extracting size of contents of each frame
        int frame_size = frame_header[4] << 24 | frame_header[5] << 16 | frame_header[6]<<8 | frame_header[7];
        //printf("%s\n",frame_id);
        //printf("%d\n",frame_size);

        if(frame_size == 0)
        {
            
            break;
        }
        
        pos = pos + frame_size ;

        //allocating memory to store the contents
        
        temp = malloc(frame_size);
        fseek(fptr,1,SEEK_CUR);
        fread(temp,1,frame_size-1,fptr);
        temp[frame_size] = '\0';


        //after the 10 byte , first byte is the 'encoding bit' which is not considered when printing content(so temp+1)
        if(strcmp("TIT2",frame_id)==0)
        {
            data->title = temp;
        }
        if(strcmp("TPE1",frame_id)==0)
        {
            data->artist = temp;
        }
        if(strcmp("TALB",frame_id)==0)
        {
            data->album = temp;
        }
        if(strcmp("TYER",frame_id)==0)
        {
            data->year = temp;
        }
        if(strcmp("COMM",frame_id)==0)
        {
            data->comment = temp;
        }
        if(strcmp("TCON",frame_id)==0)
        {
            data->genre = temp;
        }
        if(strcmp("TRCK",frame_id)==0)
        {
            data->track = temp;
        }  
        
   }

    return data; 
}




/**
TODO: Add documention as sample given
 */
void display_metadata(const TagData *data) {
    // Implementation for displaying metadata
    printf("\nMP3 Tag reader & editor\n");
    printf("-------------------------\n");
    printf("Version ID : ID3v2.%d.%d\n",data->version[3],data->version[4]);
    if(data->title)
    printf("Title      : %s\n",data->title   );     //since the first byte is encoding bit
    if(data->album)
    printf("Album      : %s\n",data->album );
    if(data->year)
    printf("Year       : %s\n",data->year);
    if(data->genre)
    printf("Genre      : %s\n",data->genre);
    if(data->artist)
    printf("Artist     : %s\n",data->artist);
    if(data->comment)
    printf("Comment    : %s\n",data->comment);
    if(data->track)
    printf("Track      : %s\n",data->track);
    printf("-------------------------\n");

}




/**
TODO: Add documention as sample given
 */
void view_tags(const char *filename) {
    TagData *data = read_id3_tags(filename); //for reading the data and pointing
    if (!data) {
        //display_error("Failed to read ID3 tags.");
        printf("Failed to read ID3 tags.\n");
        return;
    }
    display_metadata(data);//to display the details on the terminal
    free_tag_data(data);
}
