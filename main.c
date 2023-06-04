#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 31
#define CH_LEN 8

struct Pet {
    char name [LEN];
    char chip [CH_LEN];
    float price;
};

struct Pet inputPet(void) {
    FILE *fp;
    struct Pet pet;
    printf("Enter owner name: ");
    fgets(pet.name,LEN,stdin);
    fflush(stdin);
    printf("Enter chip code: ");
    fgets(pet.chip,CH_LEN,stdin);
    fflush(stdin);
    printf("Enter price: ");
    scanf("%f",&pet.price);
    fp=fopen("animalsText.txt","w");
    if(fp==NULL) {
        printf("Error opening file!");
        exit(1);
    }
    fprintf("%s, %.2f",pet.name,pet.price);
    fclose(fp);
    return pet;
}

void printPetsByPrice(struct Pet pets[],int len,float price) {
    for (int i=0;i<len;i++) {
        if(price==pets[i].price) {
            printf("%s - %s\n",pets[i].name,pets[i].chip);
        }
        else {
            printf("No such data!");
        }
    }
    return;
}

void printPets(float price) {
    struct Pet pet;
    int len=strlen(pet.name);
    FILE *fp;
    fp=fopen("animalsBin.bin","wb");
    if (fp==NULL) {
        printf("Error opening file!");
        exit(2);
    }
    while (!feof(fp)) {
    if(fread(&len,sizeof(int),1,fp)!=1) {
        printf("Error reading bin!");
        exit(3);
    }
    if(fread(&pet.name,sizeof(char),len,fp)!=len) {
        printf("Error reading bin!");
        exit(4);
    }
    if(fread(&pet.chip,sizeof(char),CH_LEN-1,fp)!=CH_LEN-1) {
        printf("Error reading bin!");
        exit(5);
    }
    if(fread(&pet.price,sizeof(float),1,fp)!=1) {
        printf("Error reading bin!");
        exit(6);
    }
    if (pet.price>=price) {
        printf("Bin Owner Name: %s\n",pet.name);
        printf("Bin Chip: %s\n",pet.chip);
        printf("Bin Price: %.2f\n",pet.price);
    }
    }
    fclose(fp);
    return;
}

int main()
{
  struct Pet pets[LEN];
  inputPet();
}
