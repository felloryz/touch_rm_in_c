#include <stdio.h>
#include <string.h>

typedef enum {
    E_ACTION_ERROR = -1,
    E_HELP,
    E_CREATE,
    E_DELETE
} e_actions;

void print_help(char *program_name);
void create_files(int number_of_files, char *file_names[]);
void delete_files(int number_of_files, char *file_names[]);

int main(int argc, char *argv[]) 
{
    // separate whole parse slgorithm into a function
    if (argc < 2)
    {
        printf("Missing file operand\n");
        print_help(argv[0]);
        return -1;
    }

    // rewrite parse algorithm
    if ((argv[1][0] == '-') && (strlen(argv[1]) == 2))
    {
        switch (argv[1][1])
        {
            case 'c':
                create_files(argc-2, &argv[2]);
                break;
            case 'd':
                delete_files(argc-2, &argv[2]);
                break;
            case 'h':
                print_help(argv[0]);
                return 0;                
            default:
                printf("Invalid option '%s'\n", argv[1]);
                print_help(argv[0]);
                return -1;
        }
    }
    else if ((argv[1][0] == '-') && (argv[1][1] == '-') && (strlen(argv[1]) > 2))
    {
        if ((strcmp(&argv[1][2], "create")) == 0)
            create_files(argc-2, &argv[2]);
        else if ((strcmp(&argv[1][2], "delete")) == 0)
            delete_files(argc-2, &argv[2]);
        else if ((strcmp(&argv[1][2], "help")) == 0)
        {
            print_help(argv[0]);
            return 0;            
        }
        else
        {
            printf("Invalid option '%s'\n", argv[1]);
            print_help(argv[0]);
            return -1;            
        }
    }
    else
    {
        printf("Invalid option '%s'\n", argv[1]);
        print_help(argv[0]);
        return -1;        
    }

    return 0;
}

void print_help(char *program_name)
{
    printf("Usage: %s [OPTION]... [FILE]...\n"
            "-c/--create        create file\n"
            "-d/--delete        delete file\n"
            "-h/--help          print help message\n", program_name);
}

void create_files(int number_of_files, char *file_names[])
{
    for (int i = 0; i < number_of_files; i++)
    {
        FILE *fptr;
        fptr = fopen(file_names[i], "w");

        if (fptr != NULL)
            fclose(fptr);
        else
            printf("'%s': No such file or directory\n", file_names[i]);
    }
}

void delete_files(int number_of_files, char *file_names[])
{
    for (int i = 0; i < number_of_files; i++)
    {
        if (remove(file_names[i]) != 0)
        {
            printf("'%s': No such file or directory\n", file_names[i]);
        }
    }
}
