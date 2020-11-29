/*  -*-  mode: c; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4; coding: utf-8  -*-  */
/************************************************************************************
 **                                                                                 **
 **                               mcHF QRP Transceiver                              **
 **                             K Atanassov - M0NKA 2014                            **
 **                                                                                 **
 **---------------------------------------------------------------------------------**
 **                                                                                 **
 **  File name:                                                                     **
 **  Description:                                                                   **
 **  Last Modified:                                                                 **
 **  Licence:       GNU GPLv3                                                      **
 ************************************************************************************/
#include "uhsdr_board.h"
#include "profiling.h"

/*
 * In order to read the counters here, you'll need to connect
 * using a real-time debugger, pause execution and read values.
 * Not a big deal with ST-Link and Eclipse or gdb.
 */
EventProfile_t eventProfile;

void profileEventsTracePrint()
{
#ifdef XPROFILE_EVENTS

            for (int i = 0;i < 10;i++)
            {
                ProfilingTimedEvent* ev_ptr = profileTimedEventGet(i);
                if (ev_ptr->count != 0)
                {
                    trace_printf("%d: %d uS per run\n",i, (ev_ptr->duration/(ev_ptr->count*168)));
                }
            }
#endif
}
