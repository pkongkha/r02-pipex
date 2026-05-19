SRCS :=\
create_proc.c\
create_proc_exec.c\
create_proc_info_init.c\
err_cmdnotfound.c\
fake_eof.c\
ft_execvpe.c\
pipex.c\
stdin_hdoc_pipe.c\
wexitstatus.c

BO_SRCS :=\
create_proc.c\
create_proc_exec.c\
create_proc_info_init.c\
err_cmdnotfound.c\
fake_eof.c\
ft_execvpe.c\
pipex_bonus.c\
stdin_hdoc_pipe.c\
wexitstatus.c

OBJDIR ?= .obj
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)
BO_OBJS := $(BO_SRCS:%.c=$(OBJDIR)/%.o)
DEPS := $(OBJS:.o=.d)
BO_DEPS := $(BO_OBJS:.o=.d)

ORIG_CFLAGS := $(CFLAGS)
CFLAGS += -Wall -Wextra -Werror -pedantic
CFLAGS += -MMD -MP
CFLAGS += -Ilibft
LDFLAGS += -Llibft
LDLIBS := -lft
unexport CFLAGS LDFLAGS

CC ?= cc

NAME := pipex

.PHONY: bonus all clean fclean re
.NOTPARALLEL: re
all: $(NAME)
bonus: $(BO_OBJS) | libft/libft.a
	$(CC) $(LDFLAGS) -o $(NAME) $^ $(LDLIBS)
clean:
	$(MAKE) -C libft fclean
	$(RM) $(OBJS) $(DEPS)
	$(RM) $(BO_OBJS) $(BO_DEPS)
	rmdir --ignore-fail-on-nonempty -p $(OBJDIR) 2>/dev/null | true
fclean: clean
	$(RM) $(NAME)
re: fclean all
libft/libft.a:
	CFLAGS='$(ORIG_CFLAGS)' $(MAKE) -C libft all

$(OBJDIR):
	@mkdir -p $@
$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) -o $@ $<
$(NAME): $(OBJS) | libft/libft.a
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

-include $(DEPS)
