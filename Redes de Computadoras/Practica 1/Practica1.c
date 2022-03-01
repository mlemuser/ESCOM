	#include<stdio.h> 
	
	int main(){  
	    unsigned char mr[4]={0, 0, 0, 0};  
	    //unsigned char IP[4]= { 0x0A, 0xFA, 0x01, 0x01 };// 10.250.1.1  
	    //unsigned char IP[4]= { 0x96, 0x0A, 0x0F, 0x00 }; // 150.10.15.0  
	    //unsigned char IP[4]= { 0xC0, 0x0E, 0x02, 0x00 }; // 192.14.2.0  
	    //unsigned char IP[4]= { 0x94, 0x11, 0x09, 0x01 }; // 148.17.9.1  
	    //unsigned char IP[4]= { 0xC1, 0x00, 0x00, 0xFF }; // 193.0.0.255  
	    //unsigned char IP[4]= { 0xDC, 0xC8, 0x17, 0x01 }; // 220.200.23.1  
	    //unsigned char IP[4]= { 0xB1, 0x64, 0x12, 0x04 }; // 177.100.18.4  
	    //unsigned char IP[4]= { 0x5F, 0x00, 0x15, 0x00 }; // 95.0.21.0  
	    //unsigned char IP[4]= { 0x6F, 0x6F, 0x6F, 0x6F }; // 111.111.111.111  
	    //unsigned char IP[4]= { 0xDB, 0x1A, 0x33, 0x00 }; // 219.26.51.0  
	    //unsigned char IP[4]= { 0xA7, 0x00, 0x00, 0x00 }; // 167.0.0.0  
	    unsigned char IP[4]= { 0xF0, 0x01, 0x01, 0x01 }; // 240.1.1.1  
	    if(IP[0]&128){  
	        if(IP[0]&64){  
	            if(IP[0]&32){  
	                if(IP[0]&16){  
	                    if(IP[0]&8){  
	                    }  
	                    else 
	                    printf("IP: %d.%d.%d.%d\n", IP[0], IP[1], IP[2], IP[3] );  
	                    printf("Clase E\n");  
	                    printf("Ip de red: ----\n");  
	                    printf("Broadcast: ----\n");  
	                }  
	                else{  
	                printf("IP: %d.%d.%d.%d\n", IP[0], IP[1], IP[2], IP[3] );  
	                printf("Clase D\n");  
	                printf("Ip de red: ----\n");  
	                printf("Broadcast: ----\n");  
	                }  
	            }  
	            else{  
	            printf("IP: %d.%d.%d.%d\n", IP[0], IP[1], IP[2], IP[3] );  
	            printf("Clase C\n");  
	            mr[0]=255;  
	            mr[1]=255;  
	            mr[2]=255;  
	         printf("Ip de red: %d.%d.%d.%d\n", IP[0]&=mr[0],IP[1]&=mr[1],IP[2]&=mr[2],IP[3]&=mr[3]); 
	         printf("Broadcast: %d.%d.%d.%d\n", IP[0]|=~mr[0],IP[1]|=~mr[1],IP[2]|=~mr[2],IP[3]|=~mr[3]);
	            }  
	        }  
	        else{  
	        printf("IP: %d.%d.%d.%d\n", IP[0], IP[1], IP[2], IP[3] );  
	        printf("Clase B\n");  
	        mr[0]=255;  
	        mr[1]=255;  
	        printf("Ip de red: %d.%d.%d.%d\n", IP[0]&=mr[0],IP[1]&=mr[1],IP[2]&=mr[2],IP[3]&=mr[3]);  
	        printf("Broadcast: %d.%d.%d.%d\n", IP[0]|=~mr[0],IP[1]|=~mr[1],IP[2]|=~mr[2],IP[3]|=~mr[3]); 
	        }  
	    }  
	    else{  
	        printf("IP: %d.%d.%d.%d\n", IP[0], IP[1], IP[2], IP[3] );  
	        printf("Clase A\n");  
	        mr[0]=255;  
	        printf("Ip de red: %d.%d.%d.%d\n", IP[0]&=mr[0],IP[1]&=mr[1],IP[2]&=mr[2],IP[3]&=mr[3]);  
	        printf("Broadcast: %d.%d.%d.%d\n", IP[0]|=~mr[0],IP[1]|=~mr[1],IP[2]|=~mr[2],IP[3]|=~mr[3]); 
	        }  
	}  
