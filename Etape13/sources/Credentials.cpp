#include "Credentials.h"

void Credentials::crypt(){
	int i;

	for(i=0; login[i]!='\0'; i++){
	    login[i]=login[i]+9;
	    if(login[i]>255){
	    	login[i]=login[i]-255;
	    } 
	}

	for(i=0; password[i]!='\0'; i++){
	    password[i]=password[i]+5;
	    if(password[i]>255){
	    	password[i]=password[i]-255;
	    } 
	}
}


void Credentials::decrypt(){
	int i;

	for(i=0; login[i]!='\0'; i++){
	    login[i]=login[i]-9;
	    if(login[i]<0){
	    	login[i]=login[i]+255;
	    } 
	}

	for(i=0; password[i]!='\0'; i++){
	    password[i]=password[i]-5;
	    if(password[i]<0){
	    	password[i]=password[i]+255;
	    } 
	}
}