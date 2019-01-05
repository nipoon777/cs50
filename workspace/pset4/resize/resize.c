#include<stdio.h>
#include<stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])

{
    //to check the number of arguments
    if(argc!=4)
    {
        fprintf(stderr,"./resize n infile outfile\n");
        return 1;


    }
    int n = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    FILE *inptr = fopen(infile,"r");
    if(inptr== NULL)
    {
        fprintf(stderr,"Could not open %s.",infile);
        return 2;
    }
    FILE *outptr = fopen(outfile,"w");
    if(outptr==NULL)
    {
        fclose(inptr);
        fprintf(stderr,"Could not create %s.",outfile);
        return 3;

    }
    BITMAPFILEHEADER bf,bfn;
    fread(&bf,sizeof(BITMAPFILEHEADER),1,inptr);
    BITMAPINFOHEADER bi,bin;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    if(bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(inptr);
        fclose(outptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    bin = bi;
    bfn = bf;
    bin.biWidth = bi.biWidth*n;
    bin.biHeight = bi.biHeight*n;
    int paddingo = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingn = (4 - (bin.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bin.biSizeImage=((sizeof(RGBTRIPLE)*bin.biWidth)+paddingn)*abs(bin.biHeight);
    bfn.bfSize= bin.biSizeImage + sizeof(BITMAPINFOHEADER)+sizeof(BITMAPFILEHEADER);

    fwrite(&bfn,sizeof(BITMAPFILEHEADER),1,outptr);
    fwrite(&bin,sizeof(BITMAPINFOHEADER),1,outptr);

    for(int i =0,biHeight= abs(bi.biHeight);i<biHeight;i++)
    {
        for(int l=0 ;l<n;l++)
        {
        for(int j=0; j<bi.biWidth;j++)
        {
            RGBTRIPLE triple;

            fread(&triple,sizeof(RGBTRIPLE),1,inptr);

            for(int m= 0 ;m<n ;m++)
            {
                fwrite(&triple,sizeof(RGBTRIPLE),1,outptr);
            }
        }
        // skip over padding in infile
		    	fseek(inptr,paddingo, SEEK_CUR);

		// then add it to outfile
				for (int k = 0; k <paddingn; k++)
					fputc(0x00, outptr);
        //starting address of scanline
	    fseek(inptr, -((bi.biWidth*3) + paddingo),SEEK_CUR);

        }
        //ending adddress of scanline for new line
		fseek(inptr, (bi.biWidth*3)+paddingo, SEEK_CUR);



    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}