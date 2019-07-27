
main:main.cc hello.pb.cc
	g++ $^ -o $@ -I ~/third_part/include -L ~/third_part/lib\
		-lprotobuf

.PHONY:clean
clean:
	rm main

hello.pb.cc:hello.proto
	~/third_part/bin/protoc hello.proto --cpp_out=.
