DOCS=$(shell pwd)/docs
BASE_IMAGE=grihabor/sphinx.latex:latest
IMAGE=grihabor/sphinx.latex.ru:latest

all: docs

docs: build
	docker run -it \
		-v "$(DOCS):/docs" \
		$(IMAGE) \
		sh -c "cd /docs; make latexpdf"

build:
	docker build . \
		-t $(IMAGE)

.PHONY: all docs
