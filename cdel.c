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
int create_file(char *filename);

int main(int argc, char *argv[]) 
{
    e_actions action = arg_parse(argc, argv);

    if (action == E_ERROR)
    {
        printf("Invalid option '%s'\n", argv[1]);
        return -1;
    }
    
    if (action == E_HELP)
    {
        print_help(argv[0]);
        return 0;
    }

    for (int i = 2; i < argc; i++)
    {
        if (action == E_CREATE)
        {
            if (create_file(argv[i]) != 0)
                printf("'%s': No such file or directory\n", argv[i]);
        }
        else if (action == E_DELETE)
        {
            if (remove(argv[i]) != 0)
                printf("'%s': No such file or directory\n", argv[i]);
        }
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
        return E_HELP;
    
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

int create_file(char *filename)
{
    FILE *fptr;
    fptr = fopen(filename, "w");

    if (fptr != NULL)
    {
        fclose(fptr);
        return 0;
    }
    else
        return -1;
}
