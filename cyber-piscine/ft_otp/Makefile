.PHONY: all build test

all: build

build:
	go build -o ft_otp

test: build
	@echo "Running oathtool comparison test"
	@bash test/test_oathtool_compare.sh
