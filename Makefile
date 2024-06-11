UID := $(shell id -u)
GID := $(shell id -g)
DOCKERFILE ?= Dockerfile.u22

BUILD = build/${DOCKERFILE}/
IMAGE_NAME = cpu6502_$(shell echo ${DOCKERFILE} | cut -d'.' -f2)

help:
	@echo "make build	-	Build docker image"
	@echo "make test_gcc	-	Build with GCC and run cpu6502 unit/integration tests"
	@echo "make test_clang	-	Build with clang and run cpu6502 unit/integration tests"
	@echo "make clang_tidy	-	Run static code analysis"
	@echo "make check_format	-	Check code formatting"
	@echo "make format	-	Format code"
	@echo "make clear	-	Remove build folders"

build:
	mkdir -p ${BUILD}
	docker build --build-arg UID=${UID} --build-arg GID=${GID} -f ${DOCKERFILE} -t ${IMAGE_NAME} .

test_gcc: build
	mkdir -p ${BUILD}/build_test_gcc
	docker run --rm -v "${PWD}:/ws" --name ${IMAGE_NAME} ${IMAGE_NAME} /bin/bash -c \
		"cd /ws/${BUILD}/build_test_gcc &&\
		cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc /ws &&\
		make -j &&\
		./cpu_6502_test \
		"

test_clang: build
	mkdir -p ${BUILD}/build_test_clang
	docker run --rm -v "${PWD}:/ws" --name ${IMAGE_NAME} ${IMAGE_NAME} /bin/bash -c \
		"cd /ws/${BUILD}/build_test_clang &&\
		cmake -DCMAKE_BUILD_TYPE=Debug -D CMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang /ws &&\
		make -j &&\
		./cpu_6502_test \
		"

clang_tidy: build
	mkdir -p ${BUILD}/build_clang_tidy
	docker run --rm -v "${PWD}:/ws" --name ${IMAGE_NAME} ${IMAGE_NAME} /bin/bash -c \
		"cd /ws/${BUILD}/build_clang_tidy &&\
		cmake -DCMAKE_BUILD_TYPE=Debug \
		-DUSE_CLANG_TIDY=True /ws &&\
		make -j \
	 "

check_format: build
	docker run --rm -v "${PWD}:/ws" --name ${IMAGE_NAME} ${IMAGE_NAME} /bin/bash -c \
		"find cpu6502/ -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format --Werror --dry-run &&\
	   find gui/ -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format --Werror --dry-run &&\
	   find interpreter/ -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format --Werror --dry-run &&\
	   find tests/ -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format --Werror --dry-run\
	  "

format: build
	docker run --rm -v "${PWD}:/ws" --name ${IMAGE_NAME} ${IMAGE_NAME} /bin/bash -c \
	"clang-format -style=llvm -dump-config > .clang-format"
	docker run --rm -v "${PWD}:/ws" --name ${IMAGE_NAME} ${IMAGE_NAME} /bin/bash -c \
		"find cpu6502/ -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i &&\
	   find gui/ -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i &&\
	   find interpreter/ -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i &&\
	   find tests/ -iname '*.hpp' -o -iname '*.cpp' | xargs clang-format -i \
	  "

clear:
	rm -rf build || true

.PHONY: build check_format test clang_tidy clear
