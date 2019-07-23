
BUILD_DIR=build

all:
	rm -r ${BUILD_DIR}
	@mkdir ${BUILD_DIR} 1>&2 2>/dev/null || true
	cd ${BUILD_DIR}; cmake  -DPYTHON_EXECUTABLE=/usr/bin/python3.6 ..; make ; python3.6 -c "import snake_5_5"


	



