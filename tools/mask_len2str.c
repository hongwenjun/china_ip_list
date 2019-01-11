// IP地址转换，masklen和maskstring之间转换
// http://blog.chinaunix.net/uid-18770639-id-2820132.html

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include <arpa/inet.h>

char *get_netmask_string(int32_t masklen)
{
    uint32_t mask=0;
    int32_t i=0;
    struct in_addr ip_addr;

    if(masklen < 0 || masklen > 32)
    {
        return NULL;
    }
    
    for(i=0;i<masklen;i++)
        mask |= 0x80000000>>i;
    
    ip_addr.s_addr = htonl(mask);
    
    return inet_ntoa(ip_addr);
}

int main(int argc, char* argv[])
{
        int32_t length = atoi (argv[1]);
        char *maskstring = NULL;
        maskstring = get_netmask_string(length);
        printf("%s\n",maskstring);
        return 0;
}
