#include<stdio.h>

void checksum (unsigned char trama[],short size){
	unsigned int checksum=0,t,t2;
	short i;
	if(size%2==1){//verifica el tama�o de la trama para saber cu�ntos va a sumar para al final sumar la �ltima trama recorrida 8 bits
		for(i=0;i<size-2;i+=2){//suma todas menos la ultima
			t=trama[i]<<8;
			checksum=checksum+t+trama[i+1];
		}
		t=trama[size-1]<<8;
		checksum=checksum+t;//suma la �ltima
		printf("Checksum:%x\n",checksum);
		t=checksum>>16;//aqu� se quita el acarreo para sumarlo despues
		t2=checksum&0xFFFF;//aqu� deja el numero de la forma 0xFFFF
		printf("Acarreo:%x\n",t+t2);
		checksum=t+t2;//aqu� se suman
		checksum=~checksum;//aqu� se niega pero queda siempre FFFF y nuestro numero
		printf("Checksum negado:%x\n",checksum);
		checksum=checksum & 0xFFFF;//aqu� quitamos FFFF y dejamos lo dem�s
		printf("Complemento a 1:%x\n",checksum);
	}else{
		for(i=0;i<size;i+=2){//como el tama�o de la trama es par solo se hace el for
			t=trama[i]<<8;
			checksum=checksum+t+trama[i+1];
		}
		printf("Checksum:%x\n",checksum);
		t=checksum>>16;
		t2=checksum&0xFFFF;
		printf("Acarreo:%x\n",t+t2);
		checksum=t+t2;//aqu� se suman
		checksum=~checksum;//aqu� se niega pero queda siempre FFFF y nuestro numero
		printf("Checksum negado:%x\n",checksum);
		checksum=checksum & 0xFFFF;//aqu� quitamos FFFF y dejamos lo dem�s
		printf("Complemento a 1:%x\n",checksum);
	}

}

void main(){
	//unsigned char trama[]={0x00, 0x02, 0xb3, 0x9c, 0xae, 0xba, 0x00, 0x02, 0xb3, 0x9c, 0xdf, 0x1b, 0x00, 0x03,0xf0, 0xf0, 0x7f};
	//unsigned char trama1[]={0x45, 0x00, 0x00, 0x3c, 0x04, 0x57, 0x00, 0x00, 0x80, 0x01, 0x98, 0x25, 0x94, 0xcc, 0x39, 0xcb, 0x94, 0xcc, 0x30, 0xe1};
	unsigned char trama2[]={0x45, 0x00, 0x00, 0x42, 0x00, 0xe2, 0x00, 0x50, 0x80, 0x06, 0x48, 0xe3, 0x94, 0xcc, 0x3a, 0x11, 0x94, 0xcc, 0x3a, 0x1e};
	//unsigned char trama3[]={0x46, 0x00, 0x80, 0x42, 0x04, 0x55, 0x31, 0x11, 0xb0, 0x11, 0x00, 0x00, 0x94, 0xcc, 0xb7, 0xcf, 0xff, 0xff, 0xaa, 0xbb, 0xcc, 0xdd};
	checksum(trama2,sizeof(trama2));
	
}
