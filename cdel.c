#include <stdio.h>
#include <string.h>

typedef enum {
    E_ERROR = -1,
    E_HELP,
    E_CREATE,
    E_DELETE
} e_actions;

void print_help(char *program_name);
int arg_parse(int argc, char *argv[]);
void create_files(int number_of_files, char *file_names[]);
void delete_files(int number_of_files, char *file_names[]);

int main(int argc, char *argv[]) 
{
    int action = arg_parse(argc, argv);

    switch (action)
    {
        case E_ERROR:
            printf("Invalid option '%s'\n", argv[1]);
            break;
        case E_HELP:
            print_help(argv[0]);
            break;
        case E_CREATE:
            create_files(argc-2, &argv[2]);
            break;
        case E_DELETE:
            delete_files(argc-2, &argv[2]);
            break;
        default:
            break;
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

int arg_parse(int argc, char *argv[])
{
    if (argc < 2)
        return E_ERROR;
    
    if (argv[1][0] != '-')
        return E_ERROR;
    
    if (strlen(argv[1]) == 2)
    {
        if (argv[1][1] == 'h')
            return E_HELP;
        else if (argv[1][1] == 'c')
            return E_CREATE;
        else if (argv[1][1] == 'd')
            return E_DELETE;
        else
            return E_ERROR;
    }

    if (argv[1][1] != '-')
        return E_ERROR;
    
    if (strlen(argv[1]) > 2)
    {
        if (!(strcmp(&argv[1][2], "help")))
            return E_HELP;
        else if (!(strcmp(&argv[1][2], "create")))
            return E_CREATE;
        else if (!(strcmp(&argv[1][2], "delete")))
            return E_DELETE;
        else
            return E_ERROR;
    }

    return E_ERROR;
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
