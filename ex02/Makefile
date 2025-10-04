NAME = find

#	Folders
SRC_DIR = ./src/
INC_DIR = ./include
OBJ_DIR = ./obj/

#	Compiler & flags
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
INC_FLAGS = -I$(INC_DIR)

#	source files
SRCS =	main.cpp
OBJS =	$(addprefix $(OBJ_DIR), $(SRCS:%.cpp=%.o))

# Rules
all: $(NAME)
	@echo "Compilation succesfull"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJS))

$(NAME): $(OBJS) 
	@$(CXX) $(CXXFLAGS) $(INC_FLAGS) -o $@ $^

# objet files
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp | $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) $(INC_FLAGS) -c $< -o $@

# Cleanning
clean :
	@rm -rf $(OBJ_DIR)
	@echo "$(NAME) executable files cleaned!"

fclean : clean
	@rm -f $(NAME)
	@echo "$(NAME) executable cleaned!"

re: fclean all

.PHONY: all clean fclean re

