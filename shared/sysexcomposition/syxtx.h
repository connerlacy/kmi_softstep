
#ifndef SoftstepSyxDemo_syxtx_h
#define SoftstepSyxDemo_syxtx_h

extern int midi_sx_data_addr;


void midi_sx_header(int device_softstep,int device_12step,int device_qunexus);
void midi_sx_close(void);
void midi_sx_packet(unsigned short packet_type,void *source,unsigned short length);
void midi_sx_packet_preamble(unsigned short packet_type,unsigned short length);
void midi_sx_packet_data(void *source,unsigned short length);
void midi_sx_packet_data_close(unsigned short length);
long midi_sx_length(void);
unsigned char *midi_sx_buffer(void);
void midi_sx_flush(void);
void midi_sx_data_crc(void *data,unsigned short length);
#endif
