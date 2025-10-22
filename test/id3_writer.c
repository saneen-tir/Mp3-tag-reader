/**
 * @file id3_writer.c
 * @brief Implementation of functions for writing and editing ID3 tags in MP3 files.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "id3_writer.h"
#include "id3_reader.h"
#include "id3_utils.h"

/**
 * @brief Writes the ID3 tags to an MP3 file.
 * 
 * @param filename The name of the MP3 file.
 * @param data Pointer to the TagData structure containing the ID3 tags.
 * @return 0 on success, non-zero on failure.
 */

 
int write_id3_tags(const char *filename, const TagData *data,const char *tag) {
    // Implementation for writing ID3 tags
    

    FILE* fptr = fopen(filename,"rb+");
    
    if(fptr == NULL)
    {
        printf("Opening file has failed");
        return 1 ;
    }



    unsigned char mainheader[10];                          //array storing info about main header 
    fread(mainheader,1,10,fptr);


    int mainsize = mainheader[6] << 21 | mainheader[7] << 14 | mainheader[8] << 7 | mainheader[9] ;
    int pos = 0;                                         //denotes the number of bytes read

    unsigned char frame_header[10];                             //stores the 10 bytes of frame headers
                           
    int size;
    
     
    while(pos < mainsize)
    {      
        //printf("first - %lu\n",ftell(fptr));                                                 
        fread(frame_header,1,10,fptr);
        pos = pos + 10;
        
       // printf("pos- %d\n",pos);

        unsigned char frame_id[5];                                                           
        memcpy(frame_id,frame_header,4);
        frame_id[4] = '\0';

        int frame_size = frame_header[4] << 24 | frame_header[5] << 16 | frame_header[6]<<8 | frame_header[7];
        
        
       // printf("frame size - %d\n",frame_size);

        
        int stored_size;
        if((strcmp("TIT2",frame_id)==0 && strcmp("-t",tag)==0))
        { 
            /*here, we make all the bytes other than the value to '\0' (in the pointer) */
            stored_size = strlen(data->title);                           
            if(stored_size >= frame_size)                            
            {                                                        
                for(int i=frame_size-1; i<stored_size ;i++)               
                {
                    data->title[i]='\0';
                }
            }
            /*here , we write '\0' to the file if value is smaller than frame size(in the file)*/
            if(strlen(data->title) < frame_size)
            {
                for(int i=strlen(data->title);i<frame_size;i++)
                {
                    data->title[i] = '\0';
                }
            }
            
            fseek(fptr, 1, SEEK_CUR);                                //skip enc bit
            fwrite(data->title , 1 , frame_size - 1 ,fptr);
            pos = pos + frame_size;
            
        }
        else if((strcmp("TRCK",frame_id)==0 && strcmp("-T",tag)==0))
        { 
            stored_size = strlen(data->track);                          
            if(stored_size >= frame_size)                            
            {                                                        
                for(int i=frame_size-1; i<stored_size ;i++)
                {
                    data->track[i]='\0';
                }
            }
            //here , we write '\0' to the file if value is smaller than frame size
            if(strlen(data->track) < frame_size)
            {
                for(int i=strlen(data->track);i<frame_size;i++)
                {
                    data->track[i] = '\0';
                }
            }
            
            fseek(fptr, 1, SEEK_CUR);                                //skip enc bit
            fwrite(data->track , 1 , frame_size - 1 ,fptr);
            pos = pos + frame_size;
            
        }
        else if((strcmp("TPE1",frame_id)==0 && strcmp("-a",tag)==0))
        { 
            stored_size = strlen(data->artist);                           
            if(stored_size >= frame_size)                            
            {                                                        
                for(int i=frame_size-1; i<stored_size ;i++)
                {
                    data->artist[i]='\0';
                }
            }
            /*here , we write '\0' to the file if value is smaller than frame size*/
            if(strlen(data->artist) < frame_size)
            {
                for(int i=strlen(data->artist);i<frame_size;i++)
                {
                    data->artist[i] = '\0';
                }
            }
            fseek(fptr, 1, SEEK_CUR);                                //skip enc bit
            fwrite(data->artist , 1 , frame_size - 1 ,fptr);
            pos = pos + frame_size;
            
        }
        else if((strcmp("TALB",frame_id)==0 && strcmp("-A",tag)==0))
        { 
            stored_size = strlen(data->album);                           
            if(stored_size >= frame_size)                            
            {                                                        
                for(int i=frame_size-1; i<stored_size ;i++)
                {
                    data->album[i]='\0';
                }
            }
            /*here , we write '\0' to the file if value is smaller than frame size*/
            if(strlen(data->album) < frame_size)
            {
                for(int i=strlen(data->album);i<frame_size;i++)
                {
                    data->album[i] = '\0';
                }
            }
            fseek(fptr, 1, SEEK_CUR);                                //skip enc bit
            fwrite(data->album , 1 , frame_size - 1 ,fptr);
            pos = pos + frame_size;
            
        }
        else if((strcmp("TYER",frame_id)==0 && strcmp("-y",tag)==0))
        { 
            stored_size = strlen(data->year);                           
            if(stored_size >= frame_size)                            
            {                                                        
                for(int i=frame_size-1; i<stored_size ;i++)
                {
                    data->year[i]='\0';
                }
            }
            /*here , we write '\0' to the file if value is smaller than frame size*/
            if(strlen(data->year) < frame_size)
            {
                for(int i=strlen(data->year);i<frame_size;i++)
                {
                    data->year[i] = '\0';
                }
            }

            fseek(fptr, 1, SEEK_CUR);                                //skip enc bit
            fwrite(data->year , 1 , frame_size - 1 ,fptr);
            pos = pos + frame_size;
            
        }
        else if((strcmp("COMM",frame_id)==0 && strcmp("-c",tag)==0))
        {
            stored_size = strlen(data->comment);                           
            if(stored_size >= frame_size)                            
            {                                                        
                for(int i=frame_size-1; i<stored_size ;i++)
                {
                    data->comment[i]='\0';
                }
            }
            /*here , we write '\0' to the file if value is smaller than frame size*/
            if(strlen(data->comment) < frame_size)
            {
                for(int i=strlen(data->comment);i<frame_size;i++)
                {
                    data->comment[i] = '\0';
                }
            }
            
            fseek(fptr, 1, SEEK_CUR);                                //skip enc bit
            fwrite(data->comment , 1 , frame_size - 1 ,fptr);
            pos = pos + frame_size;
            
        }
        else if((strcmp("TCON",frame_id)==0 && strcmp("-g",tag)==0))
        { 
            
            stored_size = strlen(data->genre);                           
            if(stored_size >= frame_size-1)                            
            {                                                        
                for(int i=frame_size-1; i<stored_size ;i++)
                {
                    data->genre[i]='\0';
                }
            }
            /*here , we write '\0' to the file if value is smaller than frame size*/
            printf("len2=%ld\n",strlen(data->genre));
            if(strlen(data->genre) < frame_size-1)
            {
                for(int i=strlen(data->genre); i<frame_size-1;i++)
                {
                    data->genre[i] = '\0';
                }
            }
            fseek(fptr, 1, SEEK_CUR);                                //skip enc bit
            fwrite(data->genre , 1 , frame_size - 1 ,fptr);
            pos = pos + frame_size;
            
        }
        else
        {
            fseek(fptr, frame_size, SEEK_CUR);
            pos = pos + frame_size;
        }
        
    }
    display_metadata(data);
}
       
    


     







/** TODO: Add documentation as sample given above */
int edit_tag(const char *filename, const char *tag, const char *value) {
    TagData *data = read_id3_tags(filename);
    
    
    if (data== NULL) {
        printf("Reading the file has failed.\n");
        return 1;
    }

   // Implementation for writing ID3 tags to file

   
   if(strcmp("-t",tag)==0 ) 
    {

        if(data->title)
        {
            
            strcpy(data->title,value);
        }
        else
        {
            printf("Tag not found");
            return 1;
        }
    }
    if(strcmp("-T",tag)==0)
    {
        if(data->track)
        {
            strcpy(data->track,value);
            
        }
        else{
            printf("Tag not found");
            return 1;
        }
    }
    if(strcmp("-a",tag)==0)
    {
        if(data->artist)
        {
            strcpy(data->artist,value);
        }
        else{
            printf("Tag not found");
            return 1;
        }
    }
    if(strcmp("-A",tag)==0)
    {
        if(data->album)
        {
            strcpy(data->album,value);
        }
        else{
            printf("Tag not found");
            return 1;
        }
    }
    if(strcmp("-y",tag)==0)
    {
        if(data->year)
        {
            strcpy(data->year,value);
        }
        else{
            printf("Tag not found");
            return 1;
        }
    }
    if(strcmp("-c",tag)==0)
    {
        if(data->comment)
        {
            strcpy(data->comment,value);
        }
        else{
            printf("Tag not found");
            return 1;
        }
    }
    if(strcmp("-g",tag)==0)
    {
        if(data->genre)
        {
            strcpy(data->genre,value);
        }
        else{
            printf("Tag not found");
            return 1;
        }
    }


    write_id3_tags(filename, data,tag);
    free_tag_data(data);
    return 0;
}

