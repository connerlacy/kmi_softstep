//
//  query.h
//  SoftstepSyxDemo
//
//  Created by Chuck Carlson on 6/7/13.
//  Copyright (c) 2013 Chuck Carlson. All rights reserved.
//

#ifndef SoftstepSyxDemo_query_h
#define SoftstepSyxDemo_query_h

int fw_process_midi(int midiVal,int *buildNum,int *error,char *version);
void softstep_midi_process(t_softstep *x, VERSION *version,long n);
void send_fw_query(t_softstep *x);

#endif
