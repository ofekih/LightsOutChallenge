all: src/LightsOutBoardWrapper.cpp
	mkdir -p build
	g++ -o build/LightsOutBoard.os src/LightsOutBoardWrapper.cpp -c -I /usr/include/python3.8/ -fPIC -shared -export-dynamic -lboost_python38 -lboost_system
	g++ -o LightsOutBoard.so -shared build/LightsOutBoard.os -lboost_python38

get_boost_python:
	cd /usr/src && \
	wget --no-verbose https://dl.bintray.com/boostorg/release/1.74.0/source/boost_1_74_0.tar.gz && \
	tar xzf boost_1_74_0.tar.gz && \
	rm boost_1_74_0.tar.gz && \
	cd boost_1_74_0 && \
	./bootstrap.sh --with-python=$(which python3) && \
	./b2 install && \
	ldconfig && \
	cd .. && rm -rf boost_1_74_0/ \