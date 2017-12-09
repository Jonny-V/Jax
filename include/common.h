#ifndef COMMON_H_
#define COMMON_H_

//端口读一个字节
unsigned char readByte(unsigned short port);

//端口写一个字节
void writeByte(unsigned short port,unsigned char value);

//端口读一个字
unsigned short readWord(unsigned short port);

//端口写一个字
void writeWord(unsigned short port, unsigned short value);



#endif //include COMMON_H_