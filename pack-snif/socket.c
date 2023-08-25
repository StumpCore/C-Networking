#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ifaddrs.h>


typedef struct {
    int i;
    char *netService;
    char *ip;
} NetworkData;


int get_socket(){
    if(socket(AF_INET, SOCK_STREAM, 6)==-1) //6=tcp
        return -1;
}


void start_scan(int socketfd, char *host, int start_port, int end_port,char *scan_time){
    int *port_numbers = NULL; //Pointer to port number array
    int num_ports = 0; //start value for array
    int scan_round;
    int check_port;

    struct addrinfo hints;

    //Pointer to save memory from returning getaddrinfo
    struct addrinfo *result;
    

                    
    port_numbers = (int *)realloc(port_numbers,0);
    
    if (strcmp(scan_time, "short") == 0){
        scan_round = 3; 
    } else {
        scan_round = 7;  
    }

    //setting the hints struct to interesting parameter
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;//IPv4
    hints.ai_socktype = SOCK_STREAM;//TCP
    hints.ai_protocol = 6; //tcp
    hints.ai_flags = 0;

    //for converting port int to string
    char port_s[6];
    sprintf(port_s,"%d",start_port);

    //check if IP is working, returning 0, else integer value of error message
    int address_info = getaddrinfo(host, port_s, &hints, &result);
    
    if(address_info != 0){
        puts("Failed to find host exiting.");
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(address_info));
        exit(0);
    }
    
    //sockaddr_in is a structure for IPb4 specific objects
    //the "double" cast is necessary to avoid misinterpretation by the compiler
    struct sockaddr_in *port_number = (struct sockaddr_in *) result->ai_addr;

    while(scan_round>0) {
        check_port = 1;

        for(int port = start_port; port<=end_port; port++){
            //konverting the port number from host to short (netzwerk byte reihenfolge)
            port_number->sin_port = htons(port);

            int connection = connect(socketfd,result->ai_addr, result->ai_addrlen);

            if(connection == 0){
                // Check if Connection is already part of array
                for (int i = 0; i < sizeof(port_numbers); i++){
                    if (port_numbers[i] == port){
                        check_port = 0;
                    };
                };
                
                if(check_port == 1){
                    printf("Port %d is open\n",port);
                    port_numbers = (int *)realloc(port_numbers,port);
                    //Close existing socket and create new one
                    close(socketfd);
                    socketfd = get_socket();
                };
            }       

        }
        scan_round -=1;
    }
    freeaddrinfo(result);

}

char *network_find()
{
    /* 
    Called, when no IP was provided to show the available networks in the area.
    */ 
    int family,s,index,ip_index,i;
    int chosen_index;
    int lengthOfNetworks; 
    int lengthOfAvailNet;
    char host[NI_MAXHOST];
    char *line;

    index = 0;
    ip_index = 0;

    printf("Network Search started...\n");

    struct ifaddrs *ifaddr;
    
    if (getifaddrs(&ifaddr) == -1){
        printf("No Networks available.");
        exit(EXIT_FAILURE);
    }
    
    printf("%-5s\t%-20s\t%-20s\t%-20s\n",
           "Index",
           "Name",
           "Family",
           "Service");

    lengthOfNetworks = 0;
    for (struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        lengthOfNetworks++;
    }

    NetworkData* networks_data = malloc(lengthOfNetworks * sizeof(*networks_data));

    for (struct ifaddrs *ifa = ifaddr; ifa != NULL;ifa = ifa->ifa_next){

        family = ifa->ifa_addr->sa_family;

        if(family==AF_INET || family == AF_INET6){
            s = getnameinfo(ifa->ifa_addr,
                            (family == AF_INET) ? sizeof(struct sockaddr_in):
                                                  sizeof(struct sockaddr_in6),
                            host, 
                            NI_MAXHOST,
                            NULL,
                            0,
                            NI_NUMERICHOST);
        } else{
            s = '-';
        }
        
        if (family != AF_PACKET){
            printf("%-5d\t%-20s\t%-10s\t%-20s\n",
                   index,
                   ifa->ifa_name,
                   (family == AF_PACKET) ? "AF_PACKET" :
                   (family == AF_INET) ? "AF_INET" :
                   (family == AF_INET6) ? "AF_INET6" : "???",
                   host);
            
            //Adding to network array
            if (family == AF_INET){
                char *final_host = strdup(host);
                networks_data[ip_index].i = ip_index;
                networks_data[ip_index].netService =ifa->ifa_name;
                networks_data[ip_index].ip = final_host;

                ip_index++;
            }
            //Increment index
            index++;
        }

    }

    printf("Network Search ended.\n");
    printf("Available Networs are:\n");

    for (long i=0; i<ip_index; i++) {
        printf("\t%-5d\t%-25s\t%s\n", 
               networks_data[i].i, 
               networks_data[i].netService,
               networks_data[i].ip);
    };

    printf("Please chose your Network of Interest: ");
    scanf("%d", &chosen_index); 
    printf("You've chosen: %s\n", networks_data[chosen_index].ip);

    freeifaddrs(ifaddr);
    char *return_value = strdup(networks_data[chosen_index].ip);

    return return_value;
}

int main(int argc, char *argv[]){
    unsigned int start_port = 0;
    unsigned int end_port = 0;
    char * host;
    char scan_time[10]; 
    
    if(argc < 2){
        printf("%s: use \"-h\" for help\n", argv[0]);
        host = network_find();
    }

    if(argc == 2){

        //handle user help
        if(strcmp(argv[1],"-h")==0){
            puts("Use: [target_ip] [start_port] [end_port] [scan_time]");
            puts("Min.Port: 0");
            puts("Max.Port: 65535");
            puts("Scan Time: [short; long]");
            puts("\tDefault: short");
            exit(1);
        }
    }


    //If user has specified a range of ports
    if(argc > 2 || host != NULL){
        
        start_port = 1;
        end_port = 65535;        
        
        if(host==NULL) {
            host = argv[1];
            start_port = atoi(argv[2]);
        } 

        if (argv[3] == NULL) {
            end_port = atoi(argv[3]);
        }

        if (argc < 4) {
            //set default scan time
            sprintf(scan_time,"short");
        } else {
            sprintf(scan_time,"%s",argv[4]);
        }
        
        printf("\n%s\n",scan_time);

        if(start_port>end_port){
            puts("Start port must be less than end port!");
            printf("Start Port: %-8d\n", start_port);
            printf("End Port: %-8d\n", end_port);
            exit(1);
        }
        
        printf("Port Scan started for %d-%d (%s):\n", start_port, end_port, scan_time);
    }
    else{
        puts("Invalid Input. Use -h for help");
        exit(1);
    }

    //Set up a socket to use.
    int socket = get_socket();

    //check that end port is < 65535
    if(start_port <= 0){
        puts("Invalid start_port");
        exit(1);
    }
    if(end_port > 65535){
        puts("Invalid end_port");
        exit(1);
    }


    //start scanning
    start_scan(socket,host,start_port,end_port,scan_time);
}



