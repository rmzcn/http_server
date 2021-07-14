#include <stdio.h>
#include <stdlib.h>


struct person
{
    int age;
    char name[30];
};


int main(){

    struct person *personPointer;

    int numberOfPerson, i;

    printf("Enter the number of persons: ");
    scanf("%d",&numberOfPerson);

    // Pointer 'ın bir sonraki adresi kendi tipinin(örn: int struct Person) uzunluğu kadardır.
    // POinterın ileriye hareket edebilmesi için ya dizi ya da belirli bellek uzunluğu gerekir(malloc ile alınmış);
    // Eğer memory bizim ise. Yoksa seg hatası yersin.

    personPointer = (struct person*) malloc(numberOfPerson * sizeof(struct person));

    for (i = 0; i < numberOfPerson; ++i)
    {
        printf("Enter first name and age respectively:");
        scanf("%s %d", (personPointer+i)->name, &(personPointer+i)->age);
    }

    printf("List of person:\n");

    for (i = 0; i < numberOfPerson; ++i)
    {
        printf("%d Name: %s\tAge : %d \n", i, (personPointer + i)->name, (personPointer+i)->age);
    }
    
    return 0;

}