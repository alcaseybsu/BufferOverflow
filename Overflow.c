/*
    To exploit the buffer overflow vulnerability, after this message appears:
    "Simulating a buffer overflow attack..."
    add more than 20 characters to the new name of any pet or owner.
    This can cause other data in the array to be incorrectly
    overwritten.
*/

#include <stdio.h>  // standard input-output header (print, scan, etc)
#include <string.h> // string header

// define pet structure
struct Pet
{
    char name[20];
    char owner[20];
};

// print all pets
void printPets(struct Pet pets[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("Pet %d - Name: %s, Owner: %s\n", i + 1, pets[i].name, pets[i].owner);
    }
    printf("\n");
}

int main()
{
    struct Pet pets[5] = {
        {"Buddy", "Elle"},
        {"Scarlet", "Eva"},
        {"Junebug", "Leah"},
        {"Fuzzy", "Lucas"},
        {"Coco", "Eleonor"}};

    // print original list of all pets
    printf("\nAll pets and their owners: \n");
    printPets(pets, 5);

    // allow user to change name and owner of pet by index
    int index;
    char input[100];

    printf("Enter index (Pet No.) you want to change (choose from 1, 2, 3, 4, or 5): ");
    if (fgets(input, sizeof(input), stdin) != NULL)
    {
        if (sscanf(input, "%d", &index) != 1)
        {
            // handle invalid input
            printf("Invalid input. Please enter a valid index.\n");
            return 1; // exit the program
        }
    }
    else
    {
        // handle input error
        printf("Error reading input.\n");
        return 1; // exit program
    }

    printf("\nIndex entered: %d\n", index); // debug statement

    if (index >= 1 && index <= 5)
    {
        printf("\nEnter the new name for pet %d: ", index);
        fflush(stdout); // flush the output buffer
        if (fgets(pets[index - 1].name, sizeof(pets[index - 1].name), stdin) == NULL)
        {
            // handle input error
            printf("Error reading input.\n");
            return 1; // exit program
        }
        pets[index - 1].name[strcspn(pets[index - 1].name, "\n")] = '\0';

        printf("\nEnter the new owner for pet %d: ", index);
        fflush(stdout); // flush the output buffer
        if (fgets(pets[index - 1].owner, sizeof(pets[index - 1].owner), stdin) == NULL)
        {
            // handle input error
            printf("Error reading input.\n");
            return 1; // exit program
        }
        pets[index - 1].owner[strcspn(pets[index - 1].owner, "\n")] = '\0';
    }
    else
    {
        printf("Invalid index (Pet No.)\n");
    }

    // print updated pets list
    printf("\n5Updated pets and their owners: \n");
    printPets(pets, 5);

    // simulate a buffer overflow attack: change name and
    // owner of pet with a different index by using too many
    // chars for the new name and owner (> 20 chars).
    printf("Simulating a buffer overflow attack...\n");
    printf("Enter the index (Pet No.) to overflow. Choose 1, 2, 3, 4, or 5: ");
    if (fgets(input, sizeof(input), stdin) != NULL)
    {
        if (sscanf(input, "%d", &index) != 1)
        {
            // handle invalid input
            printf("Invalid input. Please enter a valid index.\n");
            return 1; // exit program
        }
    }
    else
    {
        // handle input error
        printf("Error reading input.\n");
        return 1; // exit program
    }

    if (index >= 1 && index <= 5)
    {
        printf("Enter the new name and owner for Pet %d (format: Name Owner): ", index);
        fflush(stdout); // flush the output buffer

        // debug: use fgets with size checks
        if (fgets(pets[index - 1].name, sizeof(pets[index - 1].name), stdin) == NULL)
        {
            // handle input error
            printf("Error reading input.\n");
            return 1; // exit program
        }

        // remove trailing newline
        pets[index - 1].name[strcspn(pets[index - 1].name, "\n")] = '\0';

        // for owner
        if (fgets(pets[index - 1].owner, sizeof(pets[index - 1].owner), stdin) == NULL)
        {
            // handle input error
            printf("Error reading input.\n");
            return 1; // exit the program
        }
        pets[index - 1].owner[strcspn(pets[index - 1].owner, "\n")] = '\0';
    }
    else
    {
        printf("Invalid index.\n");
    }

    // print the updated list of all pets
    printf("After the buffer overflow attack:\n");
    printPets(pets, 5);

    return 0;
}
