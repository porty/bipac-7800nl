#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <linux/netfilter.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <syslog.h>
#include "filter.h"

#define BUFSIZE 2048

typedef enum
{
	PKT_ACCEPT,
	PKT_DROP
}pkt_decision_enum;

struct nfq_handle *h;
struct nfq_q_handle *qh;
char listtype[8];

void add_entry(char *website, char *folder)
{
	PURL new_entry, current, prev;
	new_entry = (PURL) malloc (sizeof(URL));
	strcpy(new_entry->website, website);
	strcpy(new_entry->folder, folder);
	new_entry->next = NULL;

	if (purl == NULL)
	{
		purl = new_entry;
	}
	else 
	{
		current = purl;
		while (current) 
		{
			prev = current;
			current = current->next;
		}
		prev->next = new_entry;
	}
}

int get_url_info()
{
	char temp[MAX_WEB_LEN + MAX_FOLDER_LEN], *temp1, *temp2, web[MAX_WEB_LEN], folder[MAX_FOLDER_LEN];
			
	FILE *f = fopen("/var/url_list", "r");
	while (fgets(temp,96, f) != '\0')
	{
		if (temp[0]=='h' && temp[1]=='t' && temp[2]=='t' && 
			temp[3]=='p' && temp[4]==':' && temp[5]=='/' && temp[6]=='/')
		{
			temp1 = temp + 7;	
		}
		else
		{
			temp1 = temp;	
		}

		if ((*temp1=='w') && (*(temp1+1)=='w') && (*(temp1+2)=='w') && (*(temp1+3)=='.'))
		{
			temp1 = temp1 + 4;
		}

		if ((temp2 = strchr(temp1, '\n')))
		{
			*temp2 = '\0';
		}
		       
		sscanf(temp1, "%[^/]", web);		
		temp1 = strchr(temp1, '/');
		if (temp1 == NULL)
		{
			strcpy(folder, "\0");
		}
		else
		{
			strcpy(folder, ++temp1);		
		}
		add_entry(web, folder);
		list_count ++;
	}

	fclose(f);

	return 0;
}

static int pkt_decision(struct nfq_data * payload)
{
	char *data;
	char *match, *folder, *url;
	PURL current;
	int payload_offset, data_len;
	struct iphdr *iph;
	struct tcphdr *tcp;
	match = folder = url = NULL;

	data_len = nfq_get_payload(payload, &data);
	if( data_len == -1 )
	{
//printf("data_len == -1!!!!!!!!!!!!!!!, EXIT\n");
		exit(1);
	}
//printf("data_len=%d ", data_len);

	iph = (struct iphdr *)data;
	tcp = (struct tcphdr *)(data + (iph->ihl<<2));

	payload_offset = ((iph->ihl)<<2) + (tcp->doff<<2);
//   payload_len = (unsigned int)ntohs(iph->tot_len) - ((iph->ihl)<<2) - (tcp->doff<<2);
	match = (char *)(data + payload_offset);

	if(strstr(match, "GET ") == NULL && strstr(match, "POST ") == NULL && strstr(match, "HEAD ") == NULL)
	{
//printf("****NO HTTP INFORMATION!!!\n");
		return PKT_ACCEPT;
	}
//printf("####payload = %s\n\n", match);
	for (current = purl; current != NULL; current = current->next)
	{
		if (current->folder[0] != '\0')
		{
			folder = strstr(match, current->folder);
		}

		if ( (url = strstr(match, current->website)) != NULL ) 
		{
			if (strcmp(listtype, "Exclude") == 0) 
			{
				if ( (folder != NULL) || (current->folder[0] == '\0') )
				{
//printf("####This page is blocked by Exclude list!");
					return PKT_DROP;
				}
				else 
				{
//printf("###Website hits but folder no hit in Exclude list! packets pass\n");
					return PKT_ACCEPT;
				}
			}
			else 
			{
				if ( (folder != NULL) || (current->folder[0] == '\0') )
				{
//printf("####This page is accepted by Include list!");
					return PKT_ACCEPT;
				}
				else 
				{
//printf("####Website hits but folder no hit in Include list!, packets drop\n");
					return PKT_DROP;
				}
			}
		}
	}

	if (url == NULL) 
	{
		if (strcmp(listtype, "Exclude") == 0) 
		{
//printf("~~~~No Url hits!! This page is accepted by Exclude list!\n");
			return PKT_ACCEPT;
		}
		else 
		{
//printf("~~~~No Url hits!! This page is blocked by Include list!\n");
			return PKT_DROP;
		}
	}

//printf("~~~None of rules can be applied!! Traffic is allowed!!\n");
	return PKT_ACCEPT;
}


/*
 * callback function for handling packets
 */
static int cb(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg,
	      struct nfq_data *nfa, void *data)
{
	struct nfqnl_msg_packet_hdr *ph;
	int decision, id=0;

	ph = nfq_get_msg_packet_hdr(nfa);
	if (ph)
	{
		id = ntohl(ph->packet_id);
	}

   /* check if we should block this packet */
	decision = pkt_decision(nfa);
	if( decision == PKT_ACCEPT)
	{
		return nfq_set_verdict(qh, id, NF_ACCEPT, 0, NULL);
	}
	else
	{
		return nfq_set_verdict(qh, id, NF_DROP, 0, NULL);
	}
}


/*
 * Open a netlink connection and returns file descriptor
 */
int netlink_open_connection(void *data)
{
	struct nfnl_handle *nh;

//printf("opening library handle\n");
	h = nfq_open();
	if (!h) 
	{
		fprintf(stderr, "error during nfq_open()\n");
		exit(1);
	}

//printf("unbinding existing nf_queue handler for AF_INET (if any)\n");
	if (nfq_unbind_pf(h, AF_INET) < 0) 
	{
		fprintf(stderr, "error during nfq_unbind_pf()\n");
		exit(1);
	}

//printf("binding nfnetlink_queue as nf_queue handler for AF_INET\n");
	if (nfq_bind_pf(h, AF_INET) < 0) 
	{
		fprintf(stderr, "error during nfq_bind_pf()\n");
		exit(1);
	}

//printf("binding this socket to queue '0'\n");
	qh = nfq_create_queue(h,  0, &cb, NULL);
	if (!qh) 
	{
		fprintf(stderr, "error during nfq_create_queue()\n");
		exit(1);
	}

//printf("setting copy_packet mode\n");
	if (nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff) < 0) 
	{
		fprintf(stderr, "can't set packet_copy mode\n");
		exit(1);
	}

	nh = nfq_nfnlh(h);
	return nfnl_fd(nh);
}


int main(int argc, char **argv)
{
	int fd, rv;
	char buf[BUFSIZE]; 

	strcpy(listtype, argv[1]);
	get_url_info();
	memset(buf, 0, sizeof(buf));

	/* open a netlink connection to get packet from kernel */
	fd = netlink_open_connection(NULL);

	while ((rv = recv(fd, buf, sizeof(buf), 0)) && rv >= 0) 
	{
//printf("pkt received\n");
		nfq_handle_packet(h, buf, rv);
		memset(buf, 0, sizeof(buf));
	}

//printf("unbinding from queue 0\n");
	nfq_destroy_queue(qh);
	nfq_close(h);

	return 0;
}
