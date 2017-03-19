/*
* =====================================================================================
*
*       Filename:  strlib.c
*
*    Description:  Function for string process.
*
*        Version:  0.01.1
*        Created:  11/11/2014 14:57:35 AM
*       Revision:  none
*
*         Author:  Lin Hui (Link), hui.lin@nufront.com
*   Organization:  Guangdong Nufront CSC Co., Ltd
*
*--------------------------------------------------------------------------------------          
* ChangLog:
*  version    Author      Date        Purpose
*  0.01.1     Lin Hui    11/11/2014   Create and initialize it.   
*     
* =====================================================================================
*/

#include "at_cmd.h"

#define in_range(c, lo, up)  ( ((uint8_t)c >= lo) && ((uint8_t)c <= up) )
#define is_digit(c)           in_range(c, '0', '9')


/*
* Judge the string input is number string.
* 0: is not a number, 1:is number string.
**/
int str_is_digit(const char * str, uint32_t max_num, uint32_t min_num)
{
  int i = 0;
  int str_len;
  int num;
  
  str_len = strlen(str);
  
  for (i = 0; i < str_len; i++) {
    if (!is_digit(str[i])) {
      return -1;
    }
  }
  
  num = atoi(str);
  
  if( (num < min_num) || (num > max_num) ) {
    return -1;
  }
  
  return 0;
}

/* Check the validable of ip string.
**/
int is_valid_ip(const char *ip) 
{ 
  int section = 0;
  int dot = 0;
  
  while (*ip) { 
    if (*ip == '.') { 
      dot++; 
      if (dot > 3) { 
        return -1; 
      } 
      
      if (section >= 0 && section <= 255) { 
        section = 0; 
      } else { 
        return -1; 
      } 
    } else if (*ip >= '0' && *ip <= '9') { 
      section = section * 10 + *ip - '0'; 
      
    } else { 
      return -1; 
    } 
    ip++;        
  }
  
  if (section >= 0 && section <= 255)	{ 
    if (3 == dot) {
      section = 0; 
      return 0;
    }
  }
  
  return -1; 	
}


/*
* Compare two string, if prefix is the sub string in line on the head, 
* then return 1, else return 0.
**/
int strStartsWith(const char *line, const char *prefix)
{
  for ( ; *line != '\0' && *prefix != '\0' ; line++, prefix++) {
    if (*line != *prefix) {
      return 0;
    }
  }
  
  return *prefix == '\0';
}

int replaceCRCF(char *src, char *drc)
{
  int i = 0;
  for( ; *src != '\0' ; src++, drc++) {
    if( *src == '\r' ) {
      *src = '\0';
      i++;
    } else if( *src == '\r' ) {
      *src = '\0';
      i++;
    }
    *drc = *src;
  }
  
  if(i == 0)
    return 0;
  else
    return 1;
} 

/*
* Get next token from string *stringp, where tokens are possibly-empty
* strings separated by characters from delim.
*
* Writes NULs into the string at *stringp to end tokens.
* delim need not remain constant from call to call.
* On return, *stringp points past the last NUL written (if there might
* be further tokens), or is NULL (if there are definitely no moretokens).
*
* If *stringp is NULL, strsep returns NULL.
*/
#ifndef RTL8711
char *strsep(char **stringp, const char *delim)
{
  char *s;
  const char *spanp;
  int c, sc;
  char *tok;
  if ((s = *stringp)== NULL)
    return (NULL);
  for (tok = s;;) {
    c = *s++;
    spanp = delim;
    do {
      if ((sc =*spanp++) == c) {
        if (c == 0)
          s = NULL;
        else
          s[-1] = 0;
        *stringp = s;
        return (tok);
      }
    } while (sc != 0);
  }
}
#endif
 
char *strrep(char *src, char* oldStr, char * newStr)
{
	if( src == NULL ){
		return (char *) NULL;
	}
	
	if( (oldStr == NULL) || (newStr == NULL) ){
		return src;
	}
		
	char * pOld=oldStr;//���ַ���ָ��
	char * pNew=newStr;//���ַ���ָ��
	
	int sLen=strlen(src);//Դ�ַ������ȣ����ߵ���ϵͳstrlen����
	int oLen=strlen(oldStr);//���ַ�������
	int nLen=strlen(newStr);;//���ַ�������
	
	//�洢������ַ���
	char * result=(char *)malloc( (int)(oLen < nLen ? (float) sLen/oLen*nLen :sLen) * sizeof(char) );//����ռ�
	char * pRes=result;//ָ�����ַ����׵�ַ
	
	while(*src)//����Դ�ַ���
	{
		pOld=oldStr;//ָ����ַ������ַ�
		while(*pOld && *src && (*pOld == *src))//��Դ�ַ�����ƥ����ַ���
		{
			pOld++;
			src++;
		}
		if('\0' == *pOld)//ƥ��ɹ�
		{
			pNew=newStr;//ָ�����ַ������ַ�
			while(*pNew)//�����ַ�������result
			*pRes++ = *pNew++;
		}else
		{ 
			*pRes++ = *src++;//��Դ�ַ������ַ�����result��������Դ�ַ���ָ��
		} 
	}
	*pRes='\0';//��ӽ����ַ�
	return result;//���ؽ���ַ��׵�ַ
}

