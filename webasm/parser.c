#include <emscripten.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_LINE_NUM 100
#define DEFAULT_COL_NUM 20

char ** parseRow(char * line) {
   char ** columns = malloc(DEFAULT_COL_NUM * sizeof(char * ));
   char * col;
   col = strtok(line, ", ");
   int curr_col = 0;
   int curr_size = DEFAULT_COL_NUM;
   while(col != NULL) { 
      columns[curr_col] = col; //trim?
      curr_col++;
      if(curr_col > curr_size) {
            curr_size = curr_size * 2;
            int * err = realloc(columns, ((curr_size) * sizeof(char *)));
            if(err == NULL)
            {
               fprintf(stderr, "Problem with realloc");
               return -1;
            } 
      }
      col = strtok(NULL, ", "); 
   } 

   return columns;
}

char *** parseCSV(char * myCSV) {
  int curr_line = 0;
  char * save;
  int curr_size = DEFAULT_LINE_NUM;
  char *** lines = malloc(DEFAULT_LINE_NUM * sizeof(char ** ));
  char * line;

  line = strtok_r (myCSV,"\r\n", &save);
  while (line != NULL)
  {
    lines[curr_line] = parseRow(strdup(line));
    curr_line++;
    if(curr_line > curr_size) {
      curr_size = curr_size * 2;
      int * err = realloc(lines, ((curr_size) * sizeof(char **)));
      if(err == NULL)
      {
              fprintf(stderr, "Problem with realloc");
              return -1;
      }
       
    }
    line = strtok_r(NULL, "\r\n", &save);
  }
  return lines;
}

void printRow(char ** row) {
        int i = 0;
        char * temp = row[i];
        
         printf("[");

        while (temp != NULL) {
            printf("%s, ", temp);
            i++;
            temp = row[i];
        }
        printf("],");
}

void printCSV(char *** lines){
  char ** temp = lines[0];
  printf("[");
  for(int i = 1; i <= 3; i++) {
          if(temp != NULL) {
            printRow(temp);
          }
          temp = lines[i];
  }
  printf("]\n");
}

EMSCRIPTEN_KEEPALIVE
char *** csv_parse(char * csv) {
   char *** result = parseCSV(csv);
   return result;
}

EMSCRIPTEN_KEEPALIVE
void  csv_print(char * csv) {
   char *** result = parseCSV(csv);
   printCSV(result);
}
