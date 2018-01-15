Test of reading and writing a structure byte per byte
By using pointers is possible to write byte per byte, just remind pointers' properties:
 byte val = byte(*((byte *)&datas+addr)); //This is to write into datas struct
 *((byte *)&test+i)=val; //This is to read flash and store in struct named test
