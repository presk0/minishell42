#include <stdio.h>
int ft_strlen(char *str)
{
    int i;
    i = 0;
    while(str[i] != '\0')
        i++;
    return (i);
}

int	check_dquotes(char *str, int i) {

    int quotes;
    int dquotes;
    int end;
    quotes = 0;
    dquotes = 0;
    end = 0;
    while (str[i])
    {
        if (str[i] == '"')
        {
            quotes = 1;
            i += 1;
            while (str[i] !='\0' || str[i] == '"')
            {

                i++;
            }
            if( i < ft_strlen (str))
                end = i;

        }

        else if (str[i] == '\'') {

            while (str[i] || str[i] == '\'' )
            {

                i++;
            }
            if( i < ft_strlen (str))
                end = i;

            }
        else
            i++;

   }


    return(0);
}





int main(int argc, char **argv)
{

	char *s = "  \"  test || \"   ";
	//printf("%s\n", s);
    check_dquotes(s, 0);
	return (0);



}