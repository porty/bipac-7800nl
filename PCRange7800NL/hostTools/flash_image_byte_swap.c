#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<netinet/in.h>
#define default_max_total   (0X400000)

static int max_total;

int data_swap(char *input_file, char *output_file)
{
   int i_fd,o_fd,ii=0;
   unsigned int ops=0,tset=0;
   unsigned int index=0;
   char temp,odd,even;
   char data[max_total];
   memset(data,0xff,max_total);
   i_fd=open(input_file,O_RDONLY);
   o_fd=open(output_file,O_CREAT|O_TRUNC|O_WRONLY,S_IRWXO);
   read(i_fd,data,sizeof(data));

   while(ops < max_total)
      {
           odd=data[ops++];
      	   even=data[ops++];
       	   temp=odd;
	   odd=even;
	   even=temp;
	   data[index++]=odd;
	   data[index++]=even;
       }

   write(o_fd,data,sizeof(data));

   close(o_fd);
   close(i_fd);
   return 0;

}

int main(int argc, char *argv[])
{
 opterr=0;
 char *inname=NULL, *outname=NULL, *temp=".rom";
 int option,n;

  max_total = default_max_total; // sarah, 20091203
  while((option=getopt(argc,argv,"i:s:"))!=-1)
  {
        switch(option)
          {
                case 'i':
                         inname=optarg; //(char*)argv[optind];
                         outname=strdup(inname);
                         strncat(outname,temp,4);
                         printf("%s \n",outname);
                         break;
                // sarah add, 20091203
                case 's':
                         if (optarg && *optarg) {
                         	max_total = atoi (optarg);
                         	max_total *= 0X100000;
                         }
                         break;
                default :
                        printf("Argument Invalid \n");
                        printf("The correct command is -i [input file name] -s [flash size(MB)]\n");
                        exit(-1);
          }
  }
  if(inname == NULL)
  {
     printf("The correct command is -i [input file name] -s [flash size(MB)]\n");
     exit (-1);
  }

 data_swap(inname,outname);
  return 0;
}

