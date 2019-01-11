#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include <arpa/inet.h>

int32_t get_netmask_length(char* mask)
{
    int32_t masklen=0, i=0;
    uint32_t netmask=0;

    if(mask == NULL)
    {
        return 0;
    }

    struct in_addr ip_addr;
    if( inet_aton(mask, &ip_addr) )
    {
        netmask = ntohl(ip_addr.s_addr);
    }else{
        netmask = 0;
        return 0;
    }
    
    while(0 == (netmask & 0x01) && i<32)
    {
        i++;
        netmask = netmask>>1;
    }
    masklen = 32-i;
    return masklen;
}

int main(int argc, char* argv[])
{
        char * str= argv[1] ;
        int32_t length;
        length = get_netmask_length(str);
        printf("%d\n",length);
        return 0;
}
