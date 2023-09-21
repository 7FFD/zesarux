/*
    ZEsarUX  ZX Second-Emulator And Released for UniX
    Copyright (C) 2013 Cesar Hernandez Bano

    This file is part of ZEsarUX.

    ZEsarUX is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef ZENG_ONLINE_CLIENT_H
#define ZENG_ONLINE_CLIENT_H

extern int zeng_online_client_list_rooms_thread_running;
extern int zeng_online_client_create_room_thread_running;
extern int zeng_online_client_join_room_thread_running;
extern void zeng_online_client_list_rooms(void);
extern void zeng_online_client_create_room(int room_number,char *room_name);
extern void zeng_online_client_join_room(int room_number);
extern void zoc_start_snapshot_sending(void);

extern z80_bit zeng_online_i_am_master;
extern z80_bit zeng_online_i_am_joined;
extern int zeng_online_joined_to_room_number;
extern z80_bit zeng_online_connected;

extern char zeng_online_server[];
extern int zeng_online_server_port;
extern char *zeng_remote_list_rooms_buffer;

#endif