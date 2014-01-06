#ifndef _CLIENT_PROTO_H_
#define _CLIENT_PROTO_H_

/* This file is automatically generated with "make proto". DO NOT EDIT */


/* The following definitions come from client/client.c  */

void do_list(const char *mask,uint16 attribute,void (*fn)(file_info *),BOOL rec, BOOL dirs);

/* The following definitions come from client/clitar.c  */

int cmd_block(void);
int cmd_tarmode(void);
int cmd_setmode(void);
int cmd_tar(void);
int process_tar(void);
int tar_parseargs(int argc, char *argv[], const char *Optarg, int Optind);

#endif /*  _CLIENT_PROTO_H_  */
