
#ifdef OR_SCCSID
static const char* sccsid = "@(#) OR_Matrix4x4.cpp (c) Gabriel Peyré & Antoine Bouthors 2001";
#endif // OR_SCCSID

#include "../stdafx.h"
#include "../misc/OR_Endian_Conv.h"
	
void ImportType(void *Type, FILE *file) {

	/*
	 * WARNING: size of Type is hardcoded to 4 here because it varies on the Mac and PC
	 * The PC sets the size to 4 bytes, whereas the mac to only 1 byte (since the enum
	 * only contains a few elements).
	 */
	#ifdef _MAC_OS_
		/*
		 * Note: By convention, we will always load the LAST byte in this enum.
		 * this convention must also be respected when WRITING a KSP/KRD on the mac
		 */
		char *tmp_s = (char *)malloc(sizeof(char)*4);	
		xfread(tmp_s,4,1,file);
		memcpy(Type,tmp_s+3, 1);
		free(tmp_s);
	#else
		xfread(Type,4,1,file);
	#endif

}

void convpath(char *path, char *base) {

	/* 
	 * prepend the base of the path if the path is not absolute 
	 */

	char *tmp_s;
	 
	/* win and unix */
	#ifndef _MAC_OS_
		/* if the path begins with a slash, then it's absolute */
		if(path[0] == OR_SLASH[0]) {
			#ifndef _UNIX_
				/* for windows, just return */
				return;
			#endif
		}
		else {
			/* prepend the path with relative path */
			tmp_s = (char *)malloc(sizeof(char)*(strlen(path)+strlen(base)+1));
			strcpy(tmp_s,base);
	
			strcat(tmp_s,path);
			strcpy(path,tmp_s);
		
			free(tmp_s);
		}
	#else /* mac os */
		/* prepend the path with relative path */
		tmp_s = (char *)malloc(sizeof(char)*(strlen(path)+strlen(base)+1));
		strcpy(tmp_s,base);
	
		strcat(tmp_s,path);
		strcpy(path,tmp_s);
		
		free(tmp_s);			
	#endif
	
	/* if windows, do nothing */
	#if !defined(_MAC_OS_) & !defined(_UNIX_)
		return;
	#else
	
		char *tmp_s2, *tmp_slash;
	
		tmp_slash = (char *)malloc(sizeof(char)*(strlen(PCSLASH)+1));
		strcpy(tmp_slash,PCSLASH);
	
		#ifdef _MAC_OS_
		        char *tmp_pcback;
			/* interpolate pc/unix '..' with the mac version of two dots ':' */
			tmp_pcback = (char *)malloc(sizeof(char)*(strlen(PCBACK)+strlen(PCSLASH)+1));
			strcpy(tmp_pcback,PCBACK);
			strcat(tmp_pcback,PCSLASH);
		
			while( (tmp_s2 = strstr(path, tmp_pcback)) ) {
				memcpy(tmp_s2, MACBACK, strlen(MACBACK));
			
				if(strlen(MACBACK) < strlen(tmp_pcback))
					strcpy(tmp_s2+strlen(MACBACK),tmp_s2+strlen(tmp_pcback));
			}
		
			free(tmp_pcback);
		#endif
					
		while( (tmp_s2 = strstr(path,tmp_slash)) )
			memcpy(tmp_s2, OR_SLASH, 1);
			
		free(tmp_slash);
	#endif /* if unix or mac */
}

size_t xfread(void *dest, size_t size, size_t nmemb, FILE *stream) {

	#if defined(_MAC_OS_) | defined(_UNIX_)
		
		char *element;
		void *element_loc;
		size_t i;
		size_t read_num, total_read;
		
		/* can't reverse anything that's smaller than 2 */
		if(size < 2)
			return fread(dest, size, nmemb, stream);
		
		element 	= (char *)malloc(sizeof(char)*size);
		element_loc = dest;
		total_read	= 0;
		
		for(i=0; i<nmemb; i++) {
			/* read one element from the stream */
			if( !(read_num = fread(element, size, 1, stream)) )
				goto done;
							
			/* reverse it */
			invs(element,(int)size);
			
			/* store it in the destination */
			memcpy(element_loc, element, size);
			
			/* point to the next element location */
			element_loc = (void *)((char *)element_loc + size);
			
			/* keep track of number of elements read */
			total_read += read_num;
		}

		done:		
		free(element);
		
		return total_read;
				
	#else /* windows */
		return fread(dest, size, nmemb, stream);
	#endif
}

#if defined(_MAC_OS_) | defined(_UNIX_)

	/* inverses the bytes in a 32bit float */
	float invf(float n) {
		char tmp[4], a,b,c,d;

		memcpy(tmp, &n, 4);
		
		a = tmp[0];
		b = tmp[1];
		c = tmp[2];
		d = tmp[3];
	
		tmp[0] = d;
		tmp[1] = c;
		tmp[2] = b;
		tmp[3] = a;

		memcpy(&n, tmp, 4);
				
		return n;
	}
	
	void invf(float n[], int len) {
		
		int i;
		
		for(i=0; i<len; i++)
			n[i] = invf(n[i]);
	}
	
	void invi(DWORD n[], DWORD len) {
	
		DWORD i;
		
		for(i=0; i<len; i++)
			n[i] = (long)INVI(n[i]);
	}
	
	void invs(char *s, int len) {

		char tmp;
		char *half1, *half2;
		int i;
	
		if(len < 2)
			return;
	
		if(len == 2) {
			tmp  = s[0];
			s[0] = s[1];
			s[1] = tmp;	
		
			return;
		}
	
		half1 = (char *)malloc((size_t)len);
		for(i=0; i<len/2; i++) half1[i] = s[i];
		half1[len/2] = '\0';
	
		half2 = (char *)malloc((size_t)len);
		for(i=len/2;i<len;i++) half2[i-len/2] = s[i];
	
		invs(half1,len/2);
		invs(half2,len-len/2);
	
		/* concatenate half1 to half2 */
		for(i=len-len/2; i<len; i++) half2[i] = half1[i-len+len/2];
	
		/* copy the new string to its original location */
		for(i=0;i<len;i++) s[i] = half2[i];

		free(half1);
		free(half2);
	}

#else 
	/* do nothing */
	float   invf(float n)              { return n; }
	void    invf(float n[], int   len) {           }
	void    invi(DWORD n[], DWORD len) {           }
	void    invs(char *s, int len)     {           }
#endif



///////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2000-2001 The Orion3D Rewiew Board                         // 
//---------------------------------------------------------------------------//
//	This file is under the Orion3D licence.                                  //
//  Refer to orion3d_licence.txt for more details about the Orion3D Licence. //
//---------------------------------------------------------------------------//
//  Ce fichier est soumis a la Licence Orion3D.                              //
//  Se reporter a orion3d_licence.txt pour plus de details sur cette licence.//
///////////////////////////////////////////////////////////////////////////////
//								END OF FILE								     //
///////////////////////////////////////////////////////////////////////////////