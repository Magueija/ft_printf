# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tosilva <tosilva@student.42lisboa.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/20 17:21:48 by tosilva           #+#    #+#              #
#    Updated: 2021/05/17 15:19:55 by tosilva          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##########################################################################################################################################
## Variables
##########################################################################################################################################

###########################################
## Target
###########################################

TARGET	=	libftprintf.a

###########################################
## Commands & Flags
###########################################

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra
DEBFLAGS	= -g -fsanitize=address

AR		= ar rcs

NORM	= norminette
NORM_COLORS	= sed -E "s/OK!/[32mOK!$/[0m/g;s/Warning(!|:)/[33mWarning\1$/[0m/g;s/Error(!|:)/[31mError\1$/[0m/g"

MKDIR	= mkdir -p
RM		= rm -fr

###########################################
## Folders & Files
###########################################

		# Current dir
CURRENT := ${shell pwd}/

			# Or with $(addprefix ${CURRENT}, bin/)
LIBFT_ROOT	= libft/
BIN_ROOT	= bin/
INC_ROOT	= include/
SRC_ROOT	= src/
OBJ_ROOT	= obj/
DEP_ROOT	= dep/

		# Path + Target
NAME	:= ${addprefix $(BIN_ROOT), $(TARGET)}

		# Libft path
LIBFT_FILE	= libft.a
LIBFT		:= ${addprefix $(LIBFT_ROOT)$(BIN_ROOT), $(LIBFT_FILE)}

DEBUG_FILES	= a.out a.out.dSYM/

			# Header files (INC_ROOT*.h) and *.c files
HFILES		:= ft_printf.h
CFILES		:= ft_filltempformats.c ft_floatneeds.c ft_ispformat.c ft_printf.c ft_printformat.c ft_removerightzeros_g.c ft_spec_g.c \
				ft_specchar.c ft_specciennotation.c ft_specdigit.c ft_specdigitbase.c ft_specfloat.c ft_specneeds.c ft_specspecial.c

			# Files with their path divided by their folders (INC_ROOT and SRC_ROOT)
HFILES_SRC	:= ${foreach file, $(INC_ROOT), ${addprefix $(INC_ROOT), $(HFILES)}}
CFILES_SRC	:= ${foreach file, $(SRC_ROOT), ${addprefix $(SRC_ROOT), $(CFILES)}}

		# All files in *_ROOT's
INCS	:= $(HFILES_SRC)
SRCS	:= $(CFILES_SRC)
OBJS	:= ${subst $(SRC_ROOT), $(OBJ_ROOT), $(SRCS:.c=.o)}
DEPS	:= ${subst $(SRC_ROOT), $(DEP_ROOT), $(SRCS:.c=.d)}

###########################################
## User input
###########################################

f	:=

##########################################################################################################################################
## Rules
##########################################################################################################################################

.DELETE_ON_ERROR:

###########################################
## Compile
###########################################

all: all_bin

all_bin: libft printf

libft: | $(LIBFT_ROOT)
	@$(MAKE) -C $(LIBFT_ROOT)

printf: $(NAME)

$(LIBFT):
	${error $(CURRENT)$(LIBFT) does not exist! Use `make libft`!}

$(NAME): $(LIBFT) $(OBJS) | $(BIN_ROOT)
	@cp $(LIBFT) $@
	$(AR) $@ $(OBJS)
# @cp $(LIBFT) $(BIN_ROOT)$(LIBFT_FILE)

$(OBJS): $(OBJ_ROOT)%.o: $(SRC_ROOT)%.c $(DEP_ROOT)%.d | $(OBJ_ROOT)
	$(CC) $(CFLAGS) -I./$(LIBFT_ROOT)$(INC_ROOT) -I./$(INC_ROOT) -c $< -o $@

$(DEPS): $(DEP_ROOT)%.d: $(SRC_ROOT)%.c | $(DEP_ROOT)
	@$(CC) $(CFLAGS) -I./$(LIBFT_ROOT)$(INC_ROOT) -I./$(INC_ROOT) -M \
		-MT '${patsubst $(SRC_ROOT)%.c,$(OBJ_ROOT)%.o,$<} ${patsubst $(SRC_ROOT)%.c,$(DEP_ROOT)%.d,$<}' $< \
		-MF ${patsubst $(SRC_ROOT)%.c,$(DEP_ROOT)%.d,$<}

###########################################
## Debug
###########################################

debug: CFLAGS += $(DEBFLAGS)
debug: debug_libft printf

debug_libft:
	@$(MAKE) debug -C $(LIBFT_ROOT)

###########################################
## Make dirs
###########################################

$(BIN_ROOT) $(OBJ_ROOT) $(DEP_ROOT):
	@$(MKDIR) $@

###########################################
## Norm
###########################################

norm:
	@echo "»»»»» HEADERS «««««"
	@$(NORM) $(INCS) | $(NORM_COLORS)
	@echo 
	@echo "»»»»» SOURCES  «««««"
	@$(NORM) $(SRCS) | $(NORM_COLORS)

norm_libft:
	@$(MAKE) norm f=$(f) -C $(LIBFT_ROOT)

###########################################
## Clear
###########################################

clean:
	@$(MAKE) clean -C $(LIBFT_ROOT)
	$(RM) $(OBJ_ROOT)

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_ROOT)
	$(RM) $(BIN_ROOT) $(NAME)

clean_dep:
	@$(MAKE) clean_dep -C $(LIBFT_ROOT)
	$(RM) $(DEP_ROOT)

clean_debug:
	$(RM) $(DEBUG_FILES)

clean_all: fclean clean_debug clean_dep

###########################################
## Reload
###########################################

re_debug: fclean debug

re: fclean all

bonus: all

##########################################################################################################################################
## Phony
##########################################################################################################################################

.PHONY: all all_bin printf libft debug norm norm_libft clean fclean clean_dep clean_debug clean_all re_debug re bonus

##########################################################################################################################################
# Includes
##########################################################################################################################################

-include ${shell find . -maxdepth 3 -type f -name '*.d'}
