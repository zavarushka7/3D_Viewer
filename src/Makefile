CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -fprofile-arcs -ftest-coverage
LDFLAGS = -lgtest -lpthread -lgcov

MODEL_DIR = Model
TEST_DIR = tests
BUILD_TEST_DIR = test
COV_DIR = coverage

BUILD_DIR = build

###############################################################################
# Основные цели
###############################################################################
.PHONY: all install uninstall clean dvi dist test

all: run

install:
	mkdir -p $(BUILD_DIR)
	cd build && qmake ../View/untitled.pro
	$(MAKE) -C build
	@echo "Installed to $(BUILD_DIR)"

uninstall:
	rm -rf $(BUILD_DIR)

clean:
	find . -name '*.a' -delete
	find . -name '*.o' -delete
	find . -name '*.gcda' -delete
	find . -name '*.gcno' -delete
	find . -name '*.info' -delete
	find . -name '*.gz' -delete
	rm -rf test test.obj $(BUILD_DIR) $(BUILD_TEST_DIR) $(COV_DIR)

dvi:
	echo "Opening README.md..."; \
	xdg-open README.md; \
	
dist: clean
	mkdir -p 3dViewer_dist
	cp -r Makefile Controller Model Tests View 3dViewer_dist/
	tar -czvf 3dViewer_dist.tar.gz 3dViewer_dist
	rm -rf 3dViewer_dist

test:
	mkdir -p $(BUILD_TEST_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_DIR)/*.cpp $(MODEL_DIR)/*.cpp $(LDFLAGS) -o $(BUILD_TEST_DIR)/test
	./$(BUILD_TEST_DIR)/test

gcov_report: clean test
	@echo "Запуск тестов для сбора данных покрытия..."
	@-./$(BUILD_TEST_DIR)/test
	@mkdir -p $(COV_DIR)
	@gcovr -r . \
		--exclude "Tests/*" \
		--html --html-details -o $(COV_DIR)/index.html \
		--print-summary

###############################################################################
# Дополнительные цели
###############################################################################
format:
	cp ../materials/linters/.clang-format .clang-format
	find . -name "*.cpp" -o -name "*.h" -o -name "*.c" | xargs clang-format -i --Werror
	rm .clang-format
	@echo "Форматирование стиля завершено."

format-check:
	@echo "Стилевая проверка кода..."
	cp ../materials/linters/.clang-format .clang-format
	find . -name "*.cpp" -o -name "*.h" -o -name "*.c" | xargs clang-format -n --Werror
	rm .clang-format
	@echo "Стилевая проверка завершена."

run: install
	./build/untitled
