# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/13 20:16:23 by thallard          #+#    #+#              #
#    Updated: 2021/01/18 09:16:26 by thallard         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

GREEN='\033[1;32m'
RED='\033[0;31m'
BLANK='\033[0m'
YELLOW='\033[0;33m'
make all -C ..
cp ../minishell .

# ECHO PART
correct=0
i=1

cat tests/echo_tests.txt | while read line
    do
        BASH_RESULT=$(echo $line "; exit" | bash 2>&-)
        # BASH_RESULT=$(echo $line "; exit" | bash)
        BASH_EXIT=$?
        MINISHELL_RESULT=$(echo $line "; exit" | ./minishell 2>&-)
        # MINISHELL_RESULT=$(echo $line "; exit" | ./minishell)
        MINISHELL_EXIT=$?
        if [ "$line" == "Echo part without -n flag" ]; then
            printf "${GREEN}$line\n\n" 
        else
            if [ "$BASH_RESULT" == "$MINISHELL_RESULT" ]; then
                if [ "$BASH_EXIT" == "$MINISHELL_EXIT" ]; then
                    printf "${GREEN}$i: $line\n"
                    correct=$((correct + 1))
                fi
            else
                printf "\n"
                if [ "$BASH_EXIT" == "$MINISHELL_EXIT" ]; then
                    printf "${RED}$i: [$line]\nbash     : [$BASH_RESULT]${GREEN}[$BASH_EXIT]${RED}\nminishell: [$MINISHELL_RESULT]${GREEN}[$MINISHELL_EXIT]\n"
                else
                    printf "${RED}$i: [$line]\nbash     : [$BASH_RESULT][$BASH_EXIT]\n minishell: [$MINISHELL_RESULT][$MINISHELL_EXIT]\n"
                fi
                printf "\n"
            fi
        fi
        i=$(($i + 1))
		sleep 0.1
    done
printf "\n${GREEN}Conclusion : $correct/$i\n"