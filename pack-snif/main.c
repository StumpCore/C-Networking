#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdalign.h>
#include <libnet.h>

int main()
{   
    //Part of ifaddrs.h
    //ifaddrs 
    struct ifaddrs *addresses;
    
    //getifaddrs calls a linked list (dynamic list)
    //it contains pointer to memory
    //the pointer points to the next member until NULL
    if (getifaddrs(&addresses)== -1){
	printf("getifaddrs call failed\n");
	return -1;
    }
    
    //Pointer to first Item in list
    //the address -> points to the next item in list

    struct ifaddrs *address = addresses;

    while(address){
	int family = address->ifa_addr->sa_family;
	if (family==AF_INET || family == AF_INET6) {
	    printf("%-15s\t", address->ifa_name);
	    printf("%-10s\t", family == AF_INET ? "IPv4" : "IPv6");
	    
	    char ap[100];
	    const int family_size = family == AF_INET ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
	    getnameinfo(address->ifa_addr, 
			family_size,
			ap,
			sizeof(ap),
			0,
			0,
			NI_NUMERICHOST);
	    
	    printf("\t%s\n", ap);
	}

	//point to next item in struct list
	address = address->ifa_next;
    }

    //frees the getifaddrs addresses
    freeifaddrs(addresses);
    return(0);
}
