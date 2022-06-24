#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


void hm_import();

void lire_file_perimetre(){

    char *import_database;
    char table[TMP_MAX];
    char *x_char;
    char *y_char;
    int x[1000];
    int y[1000];
    int i=0;
    FILE *fid;
    fid=fopen("swiss.txt", "r");
    if(fid){
        while(1) {
            import_database=fgets(table,999, fid);
            if( import_database==NULL )
                break;
            x_char = strtok(table," ");
            y_char = strtok(NULL,"\n");
            x[i]=atoi(x_char);
            y[i]=atoi(y_char);
            printf("%d %d\n", x[i], y[i]);
            i++;
        }
    }else
        printf("\nErreur d’ouverture de fichier\n");

    fclose(fid);
    fflush(stdin);
}








int main(){
//   FILE *pf;
//   int a[1000];
//   int val;
//   int i = 0;
//   int j;

//   pf = fopen("swiss.txt", "r");
//   if (pf)
//   {
//     while (!feof(pf))
//     {
//       fscanf(pf, "%d", &val);
//       a[i] = val;
//       i++;
//     }
//     printf("Numero di elementi nel file di testo : %d\n", i);
//     for (j = 0; j < i; j++)
//     {
//       printf("%d\n", a[j]);
//     }
//     fclose(pf);
//   }
//   else
//     printf("errore durante l'apertura del file.");

hm_import();
  return 0;
}
