# HERE TO PROJECT NAME
NAME		:= convert

CXX		 := c++
CXXFLAGS	:= -Wall -Wextra -Werror -std=c++98 -pedantic
OPT		 := -O2
RM		  := rm -rf
DEFINE	  := -DDEBUG_MODE=DEBUG_NONE

ROOT_DIR	:= .
SRC_DIR	 := $(ROOT_DIR)
INC_DIR	 := $(ROOT_DIR)
OBJ_DIR	 := $(ROOT_DIR)/obj

IDFLAGS	 := -I$(INC_DIR)

# HERE TO SRC FILES
SRC :=	main.cpp\
		ScalarConverter.cpp\

OBJ := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC))

all:
	$(MAKE) __build -j $(shell nproc)

re:
	$(MAKE) fclean
	$(MAKE) __build -j $(shell nproc)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

__build: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OPT) $(OBJ) $(IDFLAGS) $(DEFINE) -o $(NAME)
	@echo "====================="
	@echo "== Build Complete! =="
	@echo "====================="

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(OPT) $(IDFLAGS) $(DEFINE) -fPIC -MMD -MP -c $< -o $@

# ============ DEBUG BUILDS ============
debug:
	$(MAKE) __debug -j $(shell nproc)

__debug: OPT	:= -g -fsanitize=address -O1 -fno-omit-frame-pointer
__debug: DEFINE := -DDEBUG_MODE=DEBUG_ALL
__debug: $(NAME)

# ============ CHECKS ============
valgrind: $(NAME)
	valgrind -q --leak-check=full --track-origins=yes ./$(NAME) $(ARGS)

forbidden:
	@echo "Checking for forbidden functions (malloc, free, printf)..."
	@find $(SRC_DIR) -type f \( -name "*.cpp" -o -name "*.h*" \) -exec grep -H --color -E '\b(malloc|calloc|realloc|free|printf|using|namespace|friend)\b' {} \; || true
check: forbidden valgrind

# テストケースの実行
test: $(NAME)
	@echo "Running tests with valgrind..."
	@echo "\n=== Basic Tests ==="
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) 0 || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) 42.42f || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) 42.42 || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) nan || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) 2147483647 || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) -2147483648 || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) a || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) 0 || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) a || true

	@echo "\n=== Precision Tests ==="
	@echo "Float vs Double precision differences:"
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) 0.123456789 || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) 0.123456789f || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) 999999.9 || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) 999999.9f || true

	@echo "\n=== Large Numbers ==="
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) 3.40282347e+38 || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) 3.40282347e+38f || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) 1.17549435e-38f || true

	@echo "\n=== Overflow Tests ==="
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) 1e+50 || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) -1e+50 || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) 1e+50f || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) -1e+50f || true

	@echo "\n=== String Tests ==="
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) "hello" || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) "world" || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) "z" || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) "A" || true

	@echo "\n=== Mixed String/Number Tests ==="
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) "42abc" || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) "abc42" || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) "a42b" || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) "42.5abc" || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) "abc42.5" || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) "42f" || true

	@echo "\n=== Special Values ==="
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) inf || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) -inf || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) nan || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) inff || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) -inff || true
	@valgrind -q --leak-check=full --track-origins=yes ./$(NAME) nanf || true

	@echo "\nTest completed."

.PHONY: test

.PHONY: all clean fclean re debug valgrind forbidden check norm