
TARGET = testbench
SRCS = testbench.v

VC = iverilog -Wall

$(TARGET): $(SRCS)
	$(VC)	$^

.PHONY: clean
clean:
	rm a.out
