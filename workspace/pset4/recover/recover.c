#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

typedef uint8_t  BYTE;

int main(int argc,char*argv[])
{
    //to check the correctness of commandline argument
    if(argc!=2)
    {
        fprintf(stderr,"Usage: ./recover image");
        return 1;

    }
    char *infile = argv[1];

    FILE *inptr = fopen(infile,"r");

    if( inptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr,"Could not open %s",infile);
        return 2;

    }
    //as each block is of 512 bytes

    uint8_t buffer[512];


    int i =0 ;
    int found=0;
    FILE *img;
    //loop till eof character
    while (fread(buffer,512,1,inptr)>0)
    {
        if(buffer[0]==0xff&&buffer[1]==0xd8&&buffer[2]&&(buffer[3]&0xf0)==0xe0)
        {
            char filename[8];
            sprintf(filename,"%03i.jpg",i);
            if(found==0)
            {
                img = fopen(filename,"w");
                fwrite(buffer,sizeof(buffer),1,img);
                found=1;
            }
            if(found==1)
            {
                fclose(img);
                img = fopen(filename,"w");
                fwrite(buffer,sizeof(buffer),1,img);
                i++;

            }

        }
        else
        {
            if(found==1)
            {
                fwrite(buffer,sizeof(buffer),1,img);
            }
        }


    }
    //to make sure we are not closing already closed file
    if(img)
    {
      fclose(img);
    }
fclose(inptr);

}
