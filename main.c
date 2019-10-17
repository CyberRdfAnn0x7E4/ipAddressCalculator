#include <stdio.h>

void readAddress(unsigned int *address){
    int unsigned i = 0;
    int unsigned octet;
    *address = 0;

    while(++i < 5){
        printf("\t%d. Oktett : ", i);
        scanf("%d", &octet);
        *address <<= 8;
        *address |= octet;
    }
}

void printAddress(unsigned int *address){
    int unsigned octet = 3, octetValue = 0, temp;
    int bit;

    for(bit = 31; bit >= 0; bit--){

        temp = (1 << bit) & *address; //check if bit is set
        temp >>= (octet * 8); // shift bit to the the first octet
        octetValue |= temp; // save bit

        if(bit % 8 == 0){

            printf("%u", octetValue);
            if(bit != 0){
                printf(".");
            }
            octetValue = 0;
            octet--;
        }
    }
}

int main()
{
    unsigned int ipAddress, cidrSuffix, subnetmask, networkAddress, hostAddress, broadcastAddress;
    char input;

    if(sizeof(ipAddress) != 4){
        printf("Dieses Programm funktioniert nur mit 4 Bytes langen integers! Bye!");
        return 1;
    }

    do{

        printf("----------IP Adress Rechner----------\n\n");

        printf("Geben Sie zuerst die angefragten Informationen ein."
               "\nIP Adresse:\n");
        readAddress(&ipAddress);

        printf("\nCIDR Suffix: ");
        scanf("%u", &cidrSuffix);
        subnetmask = ~(0xFFFFFFFF >> cidrSuffix);

        networkAddress = ipAddress & subnetmask;
        hostAddress = ~subnetmask & ipAddress;
        broadcastAddress = ~subnetmask | ipAddress;

        printf("\n\n\n"
               "----------------Ergebnis------------------");
        printf("\nIP-Adresse:\t\t");
        printAddress(&ipAddress);
        printf("\nSubnetzmakse:\t\t");
        printAddress(&subnetmask);
        printf("\nNetzadresse:\t\t");
        printAddress(&networkAddress);
        printf("\nBroadcastaddresse:\t");
        printAddress(&broadcastAddress);
        printf("\nHostadresse:\t\t");
        printAddress(&hostAddress);
        printf("\n"
               "------------------------------------------"
               "\n\n\n");

        printf("Program beenden (x) oder weitere Berechnung? ");
        while((input = (char)getchar()) == '\n');

    }while(input != 'x' && input != 'X');

    printf("\nBye!\n\n");
    return 0;
}
