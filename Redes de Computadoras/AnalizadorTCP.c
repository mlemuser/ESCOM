#include<stdio.h>

void CheckSumIP(unsigned char Trama[]){
	int i;
	unsigned int CheckSum=0;
	for(i=14; i<(13+((Trama[14]&15)*4)); i++){
		if(i==24) i++;
		else CheckSum+=Trama[i++]<<8 | Trama[i];
	}
	CheckSum=((CheckSum>>16) + (CheckSum & 0xffff)) ^ 0xffff;
	
	if(((Trama[24]<<8) | Trama[25]) == (CheckSum)) printf("\nCheckSum: Correct -> 0x%x", CheckSum);
	else printf("\nCheckSum: Incorrect -> 0x%x", CheckSum);
}

void CheckSumTCP(unsigned char Trama[]){
	int i;
	unsigned int CheckSum=0;
	
	for(i=26; i<34; i++)
		CheckSum+=Trama[i++]<<8 | Trama[i];	
	CheckSum+=Trama[23];
	CheckSum+=(Trama[((Trama[14]&15)*4)+26]>>4)*4;
	
	for(i=((Trama[14]&15)*4)+14; i<((((Trama[14]&15)*4)+14)+(Trama[((Trama[14]&15)*4)+26]>>4)*4)-1; i++){ //for(i=Inicio Cabecera TCP; i<Fin Cabecera TCP; i++)
		if(i==((Trama[14]&15)*4)+30) i++;
		else CheckSum+=Trama[i++]<<8 | Trama[i];
	}
	CheckSum=((CheckSum>>16) + (CheckSum & 0xffff)) ^ 0xffff;
	
	if(((Trama[((Trama[14]&15)*4)+30]<<8) | Trama[((Trama[14]&15)*4)+31]) == (CheckSum)) printf("\nCheckSum: Correct -> 0x%x", CheckSum);
	else printf("\nCheckSum: Incorrect -> 0x%x", CheckSum);
}

void LLC(unsigned char Trama[]){
	unsigned char S[][5]={"RR","RNR", "REJ", "SREJ"};
	unsigned char UC[][6]={"UI","SIM", "-", "SARM", "UP", "-", "-", "SABM", "DISC", "-", "-", "SARME", "-", "-", "-", "SABME", "SNRM", "-", "-", "RSET", "-", "-", "XID", "-", "-", "-", "SNRME"};
	unsigned char UR[][6]={"UI","RIM", "-", "DM", "-", "-", "-", "SABM", "RD", "-", "-", "-", "UA", "-", "-", "-", "-", "FRMR", "-", "-", "-", "-", "XID", "-", "-", "-", "-"};
	
	printf("\n**********************\n");
	printf("\tLLC\n");
	printf("**********************");
	
	switch(Trama[16] & 3){
		case 0: //T-I
			printf("\nTrama-Informacion:\n\tN(s): %d\n\tN(r): %d", Trama[16]>>1, Trama[17]>>1);
			if(Trama[17] & 1){
				if(Trama[15] & 1)
					printf("\nf");
				else
					printf("\np");
			}
			break;
		case 1: //T-S
			printf("\nTrama-Supervision (%s):\n\tN(r): %d", S[(Trama[16]>>2) & 3], Trama[17]>>1);
			break;
		case 2: //T-I
			printf("\nTrama-Informacion:\n\tN(s): %d\n\tN(r): %d", Trama[16]>>1, Trama[17]>>1);
			if(Trama[17] & 1){
				if(Trama[15] & 1)
					printf("\nf");
				else
					printf("\np");
			}
			break;
		case 3: //T-U
			printf("\nTrama-No Numerada:");
			if(Trama[16] & 16){ //pf=1?
				if(Trama[15] & 1) //LSB SAPo=1, es respuesta
					printf("T-U (%s), f", UR[((Trama[16]>>2) & 3) | ((Trama[16]>>3) & 28)]);
				else //es comando
					printf("T-U (%s), p", UC[((Trama[16]>>2)&3) | ((Trama[16]>>3)&28)]);
			}
			break;
	}
}

void TCP(unsigned char Trama[]){
	int i;
	printf("\n\n**********\n");
	printf("   TCP");
	printf("\n**********");
	
	printf("\nSource port: ");
	switch(Trama[((Trama[14]&15)*4)+14]<<8 | Trama[((Trama[14]&15)*4)+15]){
		case 7:
			printf("ECHO");
			break;
		case 19:
			printf("CHARGEN");
			break;
		case 20:
			printf("FTP-DATA");
			break;
		case 21:
			printf("FTP-CONTROL");
			break;
		case 22:
			printf("SSH");
			break;
		case 23:
			printf("TELNET");
			break;
		case 25:
			printf("SMTP");
			break;
		case 53:
			printf("DOMAIN");
			break;
		case 79:
			printf("FINGER");
			break;
		case 80:
			printf("HTTP");
			break;
		case 110:
			printf("POP3");
			break;
		case 111:
			printf("SUNRPC");
			break;
		case 119:
			printf("NNTP");
			break;
		case 139:
			printf("NETBIOS-SSN");
			break;
		case 143:
			printf("IMAP");
			break;
		case 179:
			printf("BGP");
			break;
		case 389:
			printf("LDAP");
			break;
		case 443:
			printf("HTTPS (SSL)");
			break;
		case 445:
			printf("MICROSOFT-DS");
			break;
		case 1080:
			printf("SOCKS");
			break;
		default:
			printf("OTHER");
			break;
	}
	
	printf("\nDestination port: ");
	switch(Trama[((Trama[14]&15)*4)+16]<<8 | Trama[((Trama[14]&15)*4)+17]){
		case 7:
			printf("ECHO");
			break;
		case 19:
			printf("CHARGEN");
			break;
		case 20:
			printf("FTP-DATA");
			break;
		case 21:
			printf("FTP-CONTROL");
			break;
		case 22:
			printf("SSH");
			break;
		case 23:
			printf("TELNET");
			break;
		case 25:
			printf("SMTP");
			break;
		case 53:
			printf("DOMAIN");
			break;
		case 79:
			printf("FINGER");
			break;
		case 80:
			printf("HTTP");
			break;
		case 110:
			printf("POP3");
			break;
		case 111:
			printf("SUNRPC");
			break;
		case 119:
			printf("NNTP");
			break;
		case 139:
			printf("NETBIOS-SSN");
			break;
		case 143:
			printf("IMAP");
			break;
		case 179:
			printf("BGP");
			break;
		case 389:
			printf("LDAP");
			break;
		case 443:
			printf("HTTPS (SSL)");
			break;
		case 445:
			printf("MICROSOFT-DS");
			break;
		case 1080:
			printf("SOCKS");
			break;
		default:
			printf("OTHER");
			break;
	}
	
	printf("\nSequence number: ");
	for(i=((Trama[14]&15)*4)+18; i<((Trama[14]&15)*4)+22;i++)
		printf("%d", Trama[i]);
	
	printf("\nAcknowledgement number: ");
	for(i=((Trama[14]&15)*4)+22; i<((Trama[14]&15)*4)+26;i++)
		printf("%d", Trama[i]);
	
	printf("\nOffset (Header lenght): %d bytes", (Trama[((Trama[14]&15)*4)+26]>>4)*4);
	
	if((((Trama[14]&15)*4)+27)&1) printf("\nFlags: NO MORE DATA...FINISHING CONNECTION)");
	else if((((Trama[14]&15)*4)+27)&2) printf("\nFlags: SYNCHRONIZE SEQUENCE NUMBER)");
	else if((((Trama[14]&15)*4)+27)&4) printf("\nFlags: RESET CONECCTION)");
	else if((((Trama[14]&15)*4)+27)&8) printf("\nFlags: PUSH DATA)");
	else if((((Trama[14]&15)*4)+27)&16) printf("\nFlags: CONSULT ACKNOWLEDGEMENT FIELD)");
	else if((((Trama[14]&15)*4)+27)&32) printf("\nFlags: CONSULT URGENT POINTER...NOTIFY SERVER APPLICATION OF URGENT DATA)");
	
	printf("\nWindow: 0x%x", Trama[((Trama[14]&15)*4)+28]<<8 | Trama[((Trama[14]&15)*4)+29]);
	
	CheckSumTCP(Trama);
	
	printf("\nUrgent pointer: 0x%x", Trama[((Trama[14]&15)*4)+32]<<8 | Trama[((Trama[14]&15)*4)+33]);
}

void IP(unsigned char Trama[]){
	int i;
	printf("\n**********************\n");
	printf("\tIP\n");
	printf("**********************");
	
	printf("\nVersion: %d", Trama[14]>>4);
	
	printf("\nIHL (Internet Header Lenght): %d bytes", (Trama[14]&15)*4);
	
	printf("\nToS (Type of Service): ");
	if(Trama[15]&16) printf("Minimize delay");
	else if(Trama[15]&8) printf("Maximize throughout");
	else if(Trama[15]&4) printf("Maximize reliability");
	else if(Trama[15]&2) printf("Minimize cost");
	else printf("None");
	
	printf("\nTotal lenght: %d bytes", Trama[16]<<8 | Trama[17]);
	
	printf("\nIndentification: 0x%x", Trama[18]<<8 | Trama[19]);
	
	printf("\nFlags: ");
	if((Trama[20]>>5) & 0) printf("000 -> ************** / *************");
	else if((Trama[20]>>5) & 1) printf("001 -> ************** / More Fragment");
	else if((Trama[20]>>5) & 2) printf("010 -> Don't Fragment / *************");
	else if((Trama[20]>>5) & 3) printf("011 -> Don't Fragment / More Fragment");
	
	printf("\nFragment offset: %d", ((Trama[20] & 31)<<8 | Trama[21])*8);
	
	printf("\nTime to live: %d jumps", Trama[22]);
	
	printf("\nProtocol: %d -> ", Trama[23]);
	switch(Trama[23]){
		case 1:
			printf("ICMP");
			break;
		case 2:
			printf("IGMP");
			break;
		case 6:
			printf("TCP");
			break;
		case 9:
			printf("IGRP");
			break;
		case 17:
			printf("UDP");
			break;
		case 47:
			printf("GRE");
			break;
		case 50:
			printf("ESP");
			break;
		case 51:
			printf("AH");
			break;
		case 57:
			printf("SKIP");
			break;
		case 88:
			printf("EIGRP");
			break;
		case 89:
			printf("OSPF");
			break;
		case 115:
			printf("L2TP");
			break;
		default:
			printf("Other");
			break;
	}

	CheckSumIP(Trama);
	
	printf("\nSource address: ");
	for(i=26; i<30; i++){
		printf("%d", Trama[i]);
		if(i!=29) printf(".");
	}
	
	printf("\nDestination address: ");
	for(i=30; i<34; i++){
		printf("%d", Trama[i]);
		if(i!=33) printf(".");
	}
	if(Trama[23]==6) TCP(Trama);
}

void ARP(unsigned char Trama[]){
	int i;
	printf("\n**********************\n");
	printf("\tARP\n");
	printf("**********************");
	
	if((Trama[14]<<8 | Trama[15]) == 1)
		printf("\nHardware Address Type (Ethernet): %d ", (Trama[14]<<8 | Trama[15]));
	else if((Trama[14]<<8 | Trama[15]) == 6)
		printf("\nHardware Address Type (IEEE 802 LAN): %d ", (Trama[14]<<8 | Trama[15]));
	
	if((Trama[16]<<8 | Trama[17]) == 2048) 
		printf("\nProtocol Address Type (IPv4): %d", (Trama[16]<<8 | Trama[17]));
	
	if(Trama[18] == 6)
		printf("\nHardware Address Lenght (Ethernet/IEEE 802): %d ", Trama[18]);
	
	if(Trama[19] == 4)
		printf("\nProtocol Address Lenght (IPv4): %d ", Trama[19]);
	
	switch(Trama[20]<<8 | Trama[21]){
		case 1:
			printf("\nOperation (Request): %d ", (Trama[20]<<8 | Trama[21]));
			break;
		case 2:
			printf("\nOperation (Reply): %d ", (Trama[20]<<8 | Trama[21]));
			break;
		case 3:
			printf("\nOperation (Request Inv): %d ", (Trama[20]<<8 | Trama[21]));
			break;
		case 4:
			printf("\nOperation (Reply Inv): %d ", (Trama[20]<<8 | Trama[21]));
			break;
	}		
	
	printf("\nSource Hardware Address: ");
	for(i=22; i<28; i++){
		printf("%.2x", Trama[i]);
		if(i!=27) printf(":");
	}
	
	printf("\nSource Protocol Address: ");
	for(i=28; i<32; i++){
		printf("%.2x", Trama[i]);
		if(i!=31) printf(":");
	}
	
	printf("\nTarget Hardware Address: ");
	for(i=32; i<38; i++){
		printf("%.2x", Trama[i]);
		if(i!=37) printf(":");
	}
	
	printf("\nTarget Protocol Address: ");
	for(i=38; i<42; i++){
		printf("%.2x", Trama[i]);
		if(i!=41) printf(":");
	}
}

void Analizador(unsigned char Trama[], int n){
	int i;
	
	printf("___________________________________________________");
	printf("Trama No. %d", n+1);
		
	printf("\nMAC destino: ");
	for(i=0; i<6; i++){
		printf("%.2x", Trama[i]);
		if(i!=5) printf(":");
	}
	
	printf("\nMAC origen: ");
	for(i=6; i<12; i++){
		printf("%.2x", Trama[i]);
		if(i!=11) printf(":");
	}
	
	printf("\nTamanio: %d bytes\n", (Trama[12]<<8 | Trama[13]));
	
	if((Trama[12]<<8 | Trama[13]) < 1500) LLC(Trama);
	else if((Trama[12]<<8 | Trama[13]) == 2048) IP(Trama);
	else if((Trama[12]<<8 | Trama[13]) == 2054) ARP(Trama);
	else printf("\nOtro");
	printf("\n\n\n");
}

void main(){
	int i;
	unsigned char Trama[][84]={ 
		{0x02,0xFF,0x53,0xC3,0xE9,0xAB,0x00,0xFF,0x66,0x7F,0xD4,0x3C,0x08,0x00,0x45,0x02,
		 0x00,0x30,0x2C,0x00,0x40,0x00,0x80,0x06,0x4B,0x74,0xC0,0xA8,0x01,0x02,0xC0,0xA8,
		 0x01,0x01,0x04,0x03,0x00,0x15,0x00,0x3B,0xCF,0x44,0x00,0x00,0x00,0x00,0x70,0x02,
		 0x20,0x00,0x0C,0x34,0x00,0x00,0x02,0x04,0x05,0xB4,0x01,0x01,0x04,0x02}, 		 

		{0x00,0x14,0xd1,0xc2,0x38,0xbe,0x00,0x18,0xe7,0x33,0x3d,0xc3,0x08,0x00,0x45,0x00,
		 0x00,0x30,0x94,0x71,0x40,0x00,0x80,0x06,0xf9,0x8c,0xc0,0xa8,0x02,0x3c,0x4a,0x7d,
		 0x5f,0x68,0x10,0x52,0x00,0x50,0x03,0xc7,0x5a,0xa1,0x00,0x00,0x00,0x00,0x70,0x02,
		 0x40,0x00,0x67,0x4b,0x00,0x00,0x02,0x04,0x05,0xb4,0x01,0x01,0x04,0x02},		

		{0x00,0x01,0xf4,0x43,0xc9,0x19,0x00,0x18,0xe7,0x33,0x3d,0xc3,0x08,0x00,0x45,0x00,
		 0x00,0x28,0xf6,0x18,0x40,0x00,0x80,0x06,0x6b,0xa4,0x94,0xcc,0x19,0xf5,0x40,0xe9,
		 0xa9,0x68,0x08,0x3a,0x00,0x50,0x42,0xfe,0xd8,0x4a,0x6a,0x66,0xac,0xc8,0x50,0x10,
		 0x42,0x0e,0x00,0x00,0x00,0x00},												
		
		{0x00,0x01,0xf4,0x43,0xc9,0x19,0x00,0x18,0xe7,0x33,0x3d,0xc3,0x08,0x00,0x45,0x00,
		 0x00,0x28,0xf6,0x18,0x40,0x00,0x80,0x06,0x6b,0xa4,0x94,0xcc,0x19,0xf5,0x40,0xe9,
		 0xa9,0x68,0x08,0x3a,0x00,0x50,0x42,0xfe,0xd8,0x4a,0x6a,0x66,0xac,0xc8,0x50,0x10,
		 0x42,0x0e,0x00,0x00,0x00,0x00}};

	printf("Equipo 8 \n");
	printf("Integrantes del Equipo: \n");
	printf("Cruz Lopez Adrian \n");
	printf("Lemus Ruiz Mariana Elizabeth \n\n");
	
	int Tam=sizeof(Trama)/sizeof(Trama[0]);
	for(i=0; i<Tam; i++)
		Analizador(Trama[i], i);
}
