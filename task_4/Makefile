DOCS=$(shell pwd)/docs
IMAGE=grihabor/sphinx.latex:latest

all: docs

docs:
	docker run -it \
		-v "$(DOCS):/docs" \
		$(IMAGE) \
		sh -c "cd /docs; make latexpdf"

.PHONY: all docs
