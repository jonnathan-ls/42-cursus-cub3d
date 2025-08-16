# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    functions.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlacerda <jlacerda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/09 12:02:46 by jlacerda          #+#    #+#              #
#    Updated: 2025/08/16 18:57:56 by jlacerda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

define compile_project
	if [ $(COMPILED_COUNT) -eq 0 ]; then \
		printf "\n$(CYAN)$(BOLD)📦  Building Project $(RESET)\n"; \
	fi; \
	$(eval COMPILED_COUNT=$(shell echo $$(($(COMPILED_COUNT)+1))))
	$(eval SHORT_PATH=$(shell echo $(1) | sed 's|^.*/||'))
	$(eval BAR_SIZE=20)
	$(eval PERCENT=$(shell if [ $(TOTAL_FILES) -gt 0 ]; then \
	echo $$(($(COMPILED_COUNT)*100/$(TOTAL_FILES))); else echo 0; fi))
	$(eval BARS=$(shell if [ $(TOTAL_FILES) -gt 0 ]; then \
	echo $$(($(COMPILED_COUNT)*$(BAR_SIZE)/$(TOTAL_FILES))); else echo 0; fi))
	$(eval REMAINING=$(shell if [ $(BARS) -ge $(BAR_SIZE) ]; then \
	echo 0; else echo $$(($(BAR_SIZE) - $(BARS))); fi))
	$(eval PROGRESS=$(shell printf '█%.0s' $$(seq 1 $(BARS))))
	$(eval EMPTY=$(shell if [ $(REMAINING) -gt 0 ]; then \
	printf '░%.0s' $$(seq 1 $(REMAINING)); fi))
	$(eval PROGRESS_BAR=$(RESET)$(GREEN)$(PROGRESS)$(WHITE)$(EMPTY)$(RESET))

	@if [ $(VERBOSE) -eq 1 ]; then \
		printf "$(CYAN)$(BOLD)📄  Compiling $(RESET)$(CYAN)$(SHORT_PATH)$(RESET) \
		($(COMPILED_COUNT)/$(TOTAL_FILES))\n"; \
		if [ $(COMPILED_COUNT) -eq $(TOTAL_FILES) ]; then \
			printf "$(GREEN)$(BOLD)✅  Files Compiled \
			Successfully!$(RESET)\n\n"; \
		fi \
	else \
		printf "\r\033[K$(YELLOW)$(BOLD)🔄  $(PROGRESS_BAR) \
		$(PERCENT)%% $(CYAN)$(SHORT_PATH)$(RESET)"; \
		if [ $(COMPILED_COUNT) -eq $(TOTAL_FILES) ]; then \
			printf "\n$(GREEN)$(BOLD)✅  Files \
			Compiled Successfully!$(RESET)\n\n"; \
		fi \
	fi
endef

define compile_library
	$(eval LIB_NAME=$(2))
	$(eval LIB_DIR=$(1))
	$(eval PROGRESS_MSG=🏗️   Building $(LIB_NAME) $(RESET))
	$(eval SUCCESS_MSG=✅  $(LIB_NAME) $(GREEN)$(BOLD)✓ Completed$(RESET))
	$(eval FINAL_BAR=$(shell printf '▓%.0s' $$(seq 1 $(BAR_SIZE))))

	@printf "$(BLUE)$(BOLD)$(PROGRESS_MSG)\n"
	@if [ -d "$(LIB_DIR)" ]; then \
		if [ $(VERBOSE) -eq 1 ]; then \
			echo "$(CYAN)$(BOLD)📦  Compiling library \
			$(RESET)$(CYAN)$(LIB_NAME)$(RESET) in $(LIB_DIR)"; \
			if [ "$(LIB_NAME)" = "MLX42" ]; then \
				printf "$(BLUE)$(BOLD)🏗️   Building $(LIB_NAME) $(RESET)\n"; \
				cd $(LIB_DIR); cmake -B build && cmake --build build -j4; \
			else \
				make -C $(LIB_DIR); \
			fi; \
			printf "$(BLUE)$(BOLD)$(SUCCESS_MSG)\n"; \
		else \
			echo -n "🔄  "; \
			if [ "$(LIB_NAME)" = "MLX42" ]; then \
				cd $(LIB_DIR); \
				cmake -B build > /dev/null 2>&1; \
				cmake --build build -j4 > /dev/null 2>&1 & \
			else \
				make --no-print-directory -C $(LIB_DIR) & \
			fi; \
			pid=$$!; \
			i=0; \
			while kill -0 $$pid 2>/dev/null; do \
				printf "$(YELLOW)▓$(RESET)"; \
				sleep 0.1; \
				i=$$((i+1)); \
				if [ $$i -gt $(BAR_SIZE) ]; then \
					break; \
				fi; \
			done; \
			wait $$pid; \
			printf "\033[1A\r"; \
			printf "$(BLUE)$(BOLD)$(SUCCESS_MSG)\n"; \
			printf "🔄  $(YELLOW)$(FINAL_BAR)$(RESET) \n"; \
		fi; \
	fi
endef

define clean_library
	@if [ -d "$(1)" ]; then \
		make --no-print-directory -C $(1) clean > /dev/null 2>&1; \
	fi
endef

define fclean_library
	@if [ -d "$(1)" ]; then \
		make --no-print-directory -C $(1) fclean > /dev/null 2>&1; \
	fi
endef
