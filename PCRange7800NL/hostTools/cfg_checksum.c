#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<netinet/in.h>
typedef unsigned long Uint32;

Uint32 fSize;
Uint32 checkSum2 = NULL;

int check_sum(char *input_file, char *output_file)
{
   FILE *cfPtr, *fp;
   int bufChar;

   if((cfPtr = fopen(input_file, "rb")) == NULL)
      return -1;

   if( ( fp = fopen( output_file, "w" ) ) == NULL )
      return -1;

   fseek(cfPtr, 0L, SEEK_END);
   fSize = ftell(cfPtr);
   fseek(cfPtr, 0L, SEEK_SET);
   while(!feof(cfPtr))
   {
       bufChar = fgetc(cfPtr);
       checkSum2+=(Uint32)bufChar;
    }
   fprintf( fp, "%d\n",(int)checkSum2 );
   
   fclose(cfPtr);
   fclose(fp);
   return 0;
}

int main(int argc, char *argv[])
{
 opterr=0;
 char *inname=NULL, *outname=NULL;
 int option,n;

  while((option=getopt(argc,argv,"io"))!=-1)
  {
        switch(option)
          {
                case 'i':
                         inname=(char*)argv[optind];
                         continue;
                case 'o':
                        outname=(char*)argv[optind];
                        continue;
                default :
                        printf("Argument Invalid \n");
                        printf("The correct command is -i [input file name] -o [named output file]\n");
                        exit(-1);
          }
  }
  if ((outname == NULL) || (inname == NULL) )
  {
     printf("The correct command is -i [input file name] -o [named output file]\n");
     exit (-1);
  }

 check_sum(inname,outname);
  return 0;
}


