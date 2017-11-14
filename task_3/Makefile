UPPAAL_DIR=../uppaal-4.0.14
UPPAAL_BIN_DIR=$(UPPAAL_DIR)/bin-Linux
VERIFYTA=$(UPPAAL_BIN_DIR)/verifyta

TRACE=-t 0
ORDER=-o 1

QUERY=$(find . | grep *_3.q)
SYSTEM=$(find . | grep *_3.xml)

all: verify

verify:
		$(VERIFYTA) $(ORDER) $(TRACE) $(SYSTEM) $(QUERY)
