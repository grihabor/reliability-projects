all: generate

generate:
	dot -Tpng -o lts_m1.png ts_m1.txt
	dot -Tpng -o lts_m2.png ts_m2.txt
	dot -Tpng -o lts_m12.png build/lts_m12.dot
	dot -Tpng -o abstract_lts_m12.png build/abstract_lts_m12.dot

tar:
	tar -czvf task_2.tar.gz \
		abstract_lts_m12.png \
		lts_m12.png \
		lts_m1.png \
		lts_m2.png \
		CMakeLists.txt \
		task.txt \
		ts_m1.txt \
		ts_m2.txt \
		src \
		uppaal-4.0.14/420_borodin_2.xpml \
		uppaal-4.0.14/log.txt \
		uppaal-4.0.14/states.txt \
		abstract_lts_m12.dot \
		lts_m12.dot
