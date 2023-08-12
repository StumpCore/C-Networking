/*unix_list.c*/
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>


int main(){
	//declare variable, which stores the addresses
	struct ifaddrs *addresses;

	//call getifaddrs() to allocate memory and fill with linked list of addresses
	if(getifaddrs(&addresses)==-1){
		printf("getifaddrs call failed\n");
		return -1;
	}

	//address pointer should walk through the linked list of addresses
	
	struct ifaddrs *address = addresses;
	while(address){
		int family = address->ifa_addr->sa_family;
		if(family == AF_INET || family == AF_INET6){
			printf("%s\t", address->ifa_name);
			printf("%s\t",family==AF_INET ? "IPv4": "IPv6");
			char ap[100];
			const int family_size = family == AF_INET ?
				sizeof(struct sockaddr_in):sizeof(struct sockaddr_in6);
			getnameinfo(address->ifa_addr, family_size, ap,sizeof(ap),0,0,NI_NUMERICHOST);
			printf("\t%s\n",ap);
		}
		address = address->ifa_next;
	}
	freeifaddrs(addresses);
	return 0;
}
