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

void ICMP(unsigned char Trama[]){
	int i;
	printf("\n\n**********\n");
	printf("   ICMP");
	printf("\n**********");
	
	if((Trama[((Trama[14]&15)*4)+14]==8) && (Trama[((Trama[14]&15)*4)+15]==0)){
		printf("\nSolicitud ECO");
		printf("\nChecksum: 0x%x", Trama[((Trama[14]&15)*4)+16]<<8 | Trama[((Trama[14]&15)*4)+17]);
		printf("\nIdentificador: %d", Trama[((Trama[14]&15)*4)+18] + Trama[((Trama[14]&15)*4)+19]);
		printf("\nNo. Secuencia: %d", Trama[((Trama[14]&15)*4)+20] + Trama[((Trama[14]&15)*4)+21]);
		printf("\nDatos opcionales: ");
		for(i=((Trama[14]&15)*4)+22; i<74; i++)
			printf("0x%x, ", Trama[i]);
	}
	else if((Trama[((Trama[14]&15)*4)+14]==0) && (Trama[((Trama[14]&15)*4)+15]==0)){
		printf("\nRespuesta ECO");
		printf("\nChecksum: 0x%x", Trama[((Trama[14]&15)*4)+16]<<8 | Trama[((Trama[14]&15)*4)+17]);
		printf("\nIdentificador: %d", Trama[((Trama[14]&15)*4)+18] + Trama[((Trama[14]&15)*4)+19]);
		printf("\nNo. Secuencia: %d", Trama[((Trama[14]&15)*4)+20] + Trama[((Trama[14]&15)*4)+21]);
		printf("\nDatos opcionales: ");
		for(i=((Trama[14]&15)*4)+22; i<74; i++)
			printf("0x%x, ", Trama[i]);
	}
	else if((Trama[((Trama[14]&15)*4)+14]==3) && ((Trama[((Trama[14]&15)*4)+15]>=0) || (Trama[((Trama[14]&15)*4)+15]<=3))){
		if(Trama[((Trama[14]&15)*4)+15]==0) printf("\n0 -> Red Inalcanzable");
		else if(Trama[((Trama[14]&15)*4)+15]==0) printf("\n1 -> Host Inalcanzable");
		else if(Trama[((Trama[14]&15)*4)+15]==0) printf("\n2 -> Protocolo Inalcanzable");
		else if(Trama[((Trama[14]&15)*4)+15]==0) printf("\n3 -> Puerto Inalcanzable");
		printf("\nChecksum: 0x%x", Trama[((Trama[14]&15)*4)+16]<<8 | Trama[((Trama[14]&15)*4)+17]);
	}
	else if((Trama[((Trama[14]&15)*4)+14]==3) && ((Trama[((Trama[14]&15)*4)+15]>=4) || (Trama[((Trama[14]&15)*4)+15]<=13))){
		printf("\nDestino inalcanzable");
		printf("\nChecksum: 0x%x", Trama[((Trama[14]&15)*4)+16]<<8 | Trama[((Trama[14]&15)*4)+17]);
	}
	else if((Trama[((Trama[14]&15)*4)+14]==11) && ((Trama[((Trama[14]&15)*4)+15]==0) || (Trama[((Trama[14]&15)*4)+15]==1))){
		printf("\nTiempo extendido");
		printf("\nChecksum: 0x%x", Trama[((Trama[14]&15)*4)+16]<<8 | Trama[((Trama[14]&15)*4)+17]);
	}
	else printf("\nType & Code: Otro");
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
	
	if(Trama[23]==1) ICMP(Trama);
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
	
		{0x00,0x1f,0x45,0x9d,0x1e,0xa2,0x00,0x23,0x8b,0x46,0xe9,0xad,0x08,0x00,0x45,0x10,
		 0x00,0x3c,0x04,0x57,0x00,0x00,0x80,0x01,0x98,0x25,0x94,0xcc,0x39,0xcb,0x94,0xcc,
		 0x3a,0xe1,0x08,0x00,0x49,0x5c,0x03,0x00,0x01,0x00,0x61,0x62,0x63,0x64,0x65,0x66,
		 0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,
		 0x77,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69},
		
		{0x00,0x01,0xf4,0x43,0xc9,0x19,0x00,0x50,0xba,0xb2,0xf3,0x7b,0x08,0x00,0x45,0x00,
		 0x00,0x3c,0x09,0x0d,0x00,0x00,0x80,0x01,0x7b,0xfe,0x94,0xcc,0x19,0x1b,0x94,0xcc,
		 0x73,0x02,0x08,0x00,0x58,0x5a,0x02,0x00,0xf3,0x01,0x61,0x62,0x63,0x64,0x65,0x66,
		 0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,
		 0x77,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69},	
		 
		{0x00,0x50,0xba,0xb2,0xf3,0x7b,0x00,0x01,0xf4,0x43,0xc9,0x19,0x08,0x00,0x45,0x00,
		 0x00,0x3c,0xdf,0x5c,0x00,0x00,0x7c,0x01,0xa9,0xae,0x94,0xcc,0x73,0x02,0x94,0xcc,
		 0x19,0x1b,0x00,0x00,0x60,0x5a,0x02,0x00,0xf3,0x01,0x61,0x62,0x63,0x64,0x65,0x66,
		 0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,0x70,0x71,0x72,0x73,0x74,0x75,0x76,
		 0x77,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69},	
		
		{0x00,0x50,0xba,0xb2,0xf3,0x7b,0x00,0x02,0xd1,0x02,0xd4,0xca,0x08,0x00,0x45,0x00,
		 0x00,0x38,0x26,0x2d,0x00,0x00,0x40,0x01,0xf8,0x75,0x94,0xcc,0x19,0x6f,0x94,0xcc,
		 0x19,0x1b,0x03,0x03,0xaa,0x23,0x00,0x00,0x00,0x00,0x45,0x00,0x00,0x3f,0x07,0xdc,
		 0x00,0x00,0x80,0x11,0xd6,0xaf,0x94,0xcc,0x19,0x1b,0x94,0xcc,0x19,0x6f,0x04,0x0c,
		 0x00,0x35,0x00,0x2b,0x4e,0x6d},
	};
	printf("Equipo 8 \n");
	printf("Integrantes del Equipo: \n");
	printf("Cruz Lopez Adrian \n");
	printf("Lemus Ruiz Mariana Elizabeth \n\n");
	
	int Tam=sizeof(Trama)/sizeof(Trama[0]);
	for(i=0; i<Tam; i++)
		Analizador(Trama[i], i);
}
