dirs=$(shell find . -mindepth 1 -maxdepth 1 -type d -not -iwholename '*.git')

all:
	for d in $(dirs); do make -C $$d || exit 1; done

clean:
	for d in $(dirs); do make -C $$d $@; done
