/**
  @file string.c
  Implementation of C string functions
*/

#include <system.h>
#include <string.h>

/* ************************************ *
 * Author:  Forrest Desjardins    	*
 * Creation Date:  2014           	*
 * 				  	*
 *   DISCLAIMER!!!!!:  		  	*
 *  The following methods are provided	*
 *  for your use as part of the MPX	*
 *  project. While we have tested these	*
 *  We make certification of 	 	*
 *  complete correctness.		*
 *   Additionally not all methods are 	*
 *  implemented :  See:  itoa		*
 * ************************************ */




/**
 Returns the length of a string.
  @param const char *s
*/
int strlen(const char *s)
{
  int r1 = 0;
  if (*s) while(*s++) r1++;
  return r1;//return length of string
}

/**
  Copy one string to another.
  @param char *s1-destination, char *s2-source
*/
char* strcpy(char *s1, const char *s2)
{
  char *rc = s1;
  while( (*s1++ = *s2++) );
  return rc; // return pointer to destination string
}

/**
  Convert an ASCII string to an integer
  @param const char *s
*/
int atoi(const char *s)
{
  int res=0;
   int charVal=0;
   char sign = ' ';
   char c = *s;


   while(isspace(&c)){ ++s; c = *s;} // advance past whitespace


   if (*s == '-' || *s == '+') sign = *(s++); // save the sign


   while(*s != '\0'){
        charVal = *s - 48;
 	res = res * 10 + charVal;
	s++;

   }


   if ( sign == '-') res=res * -1;

  return res; // return integer
}

/**
  Convert an integer to ASCII string
  @param int num, char *buffer, int base
*/

char* itoa(int num, char *buffer, int base)
{
  if (base < 2 || base > 32)
    return buffer;

  int i = 0;
  while (num)
  {
    int r = num % base;

    if (r >= 10)
      buffer[i++] = 65 + (r - 10);
    else
      buffer[i++] = 48 + r;

    num = num / base;
  }

  if (i == 0)
    buffer[i++] = '0';

  if (num < 0 && base == 10)
    buffer[i++] = '-';

  buffer[i] = '\0';

  return reverse(buffer, 0, i - 1);

}

/**
  reverses contents of string
  @param char *str, int i, int j
*/

char* reverse(char *str, int i, int j)
{
  while (i < j)
  {
    swap(&str[i++], &str[j--]);
  }
  return str;
}

/**
 swaps two char values
  @param char *x, char *y
*/

void swap(char *x, char *y)
{
  char t = *x;
  *x = *y;
  *y = t;
}


/**
  String comparison
  @param const char *s1-string, const char *s2-string
*/
int strcmp(const char *s1, const char *s2)
{

  // Remarks:
  // 1) If we made it to the end of both strings (i. e. our pointer points to a
  //    '\0' character), the function will return 0
  // 2) If we didn't make it to the end of both strings, the function will
  //    return the difference of the characters at the first index of
  //    indifference.
  while ( (*s1) && (*s1==*s2) ){
    ++s1;
    ++s2;
  }
  return ( *(unsigned char *)s1 - *(unsigned char *)s2 );
}

/**
  String comparison for a given number of characters
  @param const char *s1-string 1, const char *s2-string 2, n-size_t
*/

int strncmp(const char *s1, const char *s2, size_t n)
{
  while (n && *s1 && (*s1 == *s2))
  {
    ++s1;
    ++s2;
    --n;
  }
  if (n == 0)
    return 0;
  else
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}


/* ---------------------------------------
    Functions below this point are given.
    No need to tamper with these!
   --------------------------------------- */

/**
  Concatenate the contents of one string onto another.
  @param char *s1-destination, const char *s2-source
*/
char* strcat(char *s1, const char *s2)
{
  char *rc = s1;
  if (*s1) while(*++s1);
  while( (*s1++ = *s2++) );
  return rc;
}

/**
  Determine if a character is whitespace.
  @param const char *c-character to check
*/
int isspace(const char *c)
{
  if (*c == ' '  ||
      *c == '\n' ||
      *c == '\r' ||
      *c == '\f' ||
      *c == '\t' ||
      *c == '\b' ||
      *c == '\v'){
    return 1;
  }
  return 0;
}

/**
  Set a region of memory.
  @param void *s-destination, int c-byte to write, size_t n-count
*/
void* memset(void *s, int c, size_t n)
{
  unsigned char *p = (unsigned char *) s;
  while(n--){
    *p++ = (unsigned char) c;
  }
  return s;
}

/**
  Split string into tokens
  @param char *s1-string, s2-delimiter
*/
char* strtok(char *s1, const char *s2)
{
  static char *tok_tmp = NULL;
  const char *p = s2;

  //new string
  if (s1!=NULL){
    tok_tmp = s1;
  }
  //old string cont'd
  else {
    if (tok_tmp==NULL){
      return NULL;
    }
    s1 = tok_tmp;
  }

  //skip leading s2 characters
  while ( *p && *s1 ){
    if (*s1==*p){
      ++s1;
      p = s2;
      continue;
    }
    ++p;
  }

  //no more to parse
  if (!*s1){
    return (tok_tmp = NULL);
  }

  //skip non-s2 characters
  tok_tmp = s1;
  while (*tok_tmp){
    p = s2;
    while (*p){
      if (*tok_tmp==*p++){
	*tok_tmp++ = '\0';
	return s1;
      }
    }
    ++tok_tmp;
  }

  //end of string
  tok_tmp = NULL;
  return s1;
}



/* And finally....
   For the brave ones! (Note: you'll need to add a prototype to string.h)
   sprintf must work properly for the following types to receive extra credit:
     1) characters
     2) strings
     3) signed integers
     4) hexadecimal numbers may be useful
     ...
     \infty) Or feel free to completely implement sprintf
             (Read the man Page: $ man sprintf)
   int sprintf(char *str, const char *format, ...);
*/
