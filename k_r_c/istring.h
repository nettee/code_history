/* ----------------------------------------
 * istring.h : simulate standard <string.h>
 * Auther: nettee
 * Version: 0.1.0
 * Date: 2013.11.28
 * -----------------------------------------
 */

void escape(char * s, char * t);
/* converts characters like newline and tab into
 * visible escape sequences line \n and \t as it
 * copies the string t to s.
 */

void istrcpy(char * s, char * t);
/* copy t to s 
 */

void istrcmp(char * s, char * t);
/* return <0 if s<t, 0 if s==t, >0 if s>t 
 */
