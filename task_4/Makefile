DOCS=$(shell pwd)/docs
BASE_IMAGE=grihabor/sphinx.latex:latest
IMAGE=grihabor/sphinx.latex.ru:latest

all: docs

docs:
	docker run -it \
		-v "$(DOCS):/docs" \
		$(IMAGE) \
		sh -c "cd /docs; make latexpdf"

pull:
	docker pull $(IMAGE)

push:
	docker push $(IMAGE)

build:
	docker build . \
		-t $(IMAGE)

.PHONY: all docs
