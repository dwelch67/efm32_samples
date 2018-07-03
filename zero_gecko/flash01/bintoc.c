

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fp;

#define CFG_DATA_SIZE 0x4000
unsigned int data[CFG_DATA_SIZE>>2];

int main ( int argc, char *argv[] )
{
    unsigned int ra;
    unsigned int len;
    unsigned short crc16;

    if(argc<2)
    {
        printf("binary file not specified\n");
        return(1);
    }

    memset(data,0xFF,sizeof(data));

    fp=fopen(argv[1],"rb");
    if(fp==NULL)
    {
        printf("error opening file [%s]\n",argv[1]);
        return(1);
    }
    len=fread(data,1,sizeof(data),fp);
    fclose(fp);
    printf("len %u\n",len);
    if(len>=0x2000)
    {
        printf("TOO MUCH DATA %u\n",len);
        return(1);
    }

    len=len+3;
    len>>=2;

    fp=fopen("flash.h","wt");
    if(fp==NULL) return(1);
    fprintf(fp,"\n");
    fprintf(fp,"const unsigned int flashlen=%u;\n",len);
    fprintf(fp,"const unsigned int flashrom[]=\n");
    fprintf(fp,"{\n");
    for(ra=0;ra<len;ra++)
    {
        fprintf(fp,"0x%08X,\n",data[ra]);
    }
    fprintf(fp,"};\n");
    fprintf(fp,"\n");
    fclose(fp);

    return(0);

}
