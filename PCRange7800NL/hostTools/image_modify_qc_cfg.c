#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<netinet/in.h>
#define max_total   (0X7ff000)
#define max_cfg	    (0X1E000)
#define cfg_start_addr_4 (0X3e2000)
#define cfg_start_addr_8 (0x7e2000)

int data_copy(char *input_file, char *output_file, char *cfg_file, char *flash_size)
{
   int i_fd,o_fd,c_fd;
   unsigned int ops=0,test=0;
   unsigned int index=0;
   char data[max_total];
   char cfg_data[max_cfg];

   memset(data,0xff,max_total);
   i_fd=open(input_file,O_RDONLY);
   c_fd=open(cfg_file,O_RDONLY);
   o_fd=open(output_file,O_CREAT|O_TRUNC|O_RDWR,S_IRWXU);
   read(i_fd,data,sizeof(data));
   read(c_fd,cfg_data,sizeof(cfg_data));

//   while(ops < max_total)
//          data[index++]=data[ops++];
   if(strstr(flash_size,"4M"))
      index=cfg_start_addr_4;
   else
      index=cfg_start_addr_8;

   while(index < max_total)
      data[index++]=cfg_data[test++];
   
   write(o_fd,data,sizeof(data));

   close(o_fd);   close(i_fd);   close(c_fd);
   return 0;
}

int main(int argc, char *argv[])
{
 opterr=0;
 char *inname=NULL, *outname=NULL, *temp="_tmp", *cfgname=NULL,*fsize=NULL;
 int option,n;

  while((option=getopt(argc,argv,"ics"))!=-1)
  {
        switch(option)
          {
                case 'i':
                         inname=(char*)argv[optind];
                         outname=strdup(inname);
                         strncat(outname,temp,4);
                         printf("%s \n",outname);
                         break;
                case 'c':
                         cfgname=(char*)argv[optind];              
                         printf("%s \n",cfgname);
                         break;
		case 's':
                         fsize=(char*)argv[optind];
                         printf("%s \n",fsize);
                         break; 
                default :
                        printf("Argument Invalid \n");
                        printf("The correct command is -i [input file name] -c [cfg file name] -s [flash size]\n");
                        exit(-1);
          }
  }
  if(inname == NULL || cfgname == NULL || fsize == NULL)
  {
     printf("The correct command is -i [input file name], -c [cfg file name] -s [flash size]\n");
     exit (-1);
  }
  
 data_copy(inname,outname,cfgname,fsize);
  return 0;
}

