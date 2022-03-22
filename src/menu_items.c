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

/*
   Menu entries
*/

//
// Archivo para entradas de menu, excluyendo funciones auxiliares de soporte de menu, y tampoco los menus de settings
// Las funciones auxiliares de menu estan en menu.c
//


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>
#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>


#include "zxvision.h"
#include "menu_items.h"
#include "menu_items_settings.h"
#include "menu_debug_cpu.h"
#include "menu_file_viewer_browser.h"
#include "menu_filesel.h"
#include "menu_bitmaps.h"
#include "screen.h"
#include "cpu.h"
#include "debug.h"
#include "zx8081.h"
#include "ay38912.h"
#include "tape.h"
#include "audio.h"
#include "timer.h"
#include "snap.h"
#include "operaciones.h"
#include "disassemble.h"
#include "utils.h"
#include "contend.h"
#include "joystick.h"
#include "ula.h"
#include "printers.h"
#include "realjoystick.h"
#include "scrstdout.h"
#include "z88.h"
#include "ulaplus.h"
#include "autoselectoptions.h"
#include "zxuno.h"
#include "charset.h"
#include "chardetect.h"
#include "textspeech.h"
#include "mmc.h"
#include "ide.h"
#include "divmmc.h"
#include "divide.h"
#include "diviface.h"
#include "zxpand.h"
#include "spectra.h"
#include "spritechip.h"
#include "jupiterace.h"
#include "timex.h"
#include "chloe.h"
#include "prism.h"
#include "cpc.h"
#include "sam.h"
#include "atomlite.h"
#include "if1.h"
#include "pd765.h"
#include "tbblue.h"
#include "dandanator.h"
#include "superupgrade.h"
#include "m68k.h"
#include "remote.h"
#include "snap_rzx.h"
#include "multiface.h"
#include "scmp.h"
#include "esxdos_handler.h"
#include "tsconf.h"
#include "kartusho.h"
#include "ifrom.h"
#include "spritefinder.h"
#include "snap_spg.h"
#include "betadisk.h"
#include "tape_tzx.h" 
#include "snap_zsf.h"
#include "compileoptions.h"
#include "settings.h"
#include "datagear.h"
#include "assemble.h"
#include "expression_parser.h"
#include "uartbridge.h"
#include "zeng.h"
#include "network.h"
#include "stats.h"
#include "vdp_9918a.h"
#include "msx.h"
#include "coleco.h"
#include "sg1000.h"
#include "sms.h"
#include "sn76489an.h"
#include "svi.h"
#include "ql_qdos_handler.h"
#include "ql_i8049.h"
#include "gs.h"
#include "zvfs.h"
#include "vdp_9918a_sms.h"
#include "snap_ram.h"
#include "sensors.h"
#include "samram.h"
#include "hilow.h"
#include "utils_text_adventure.h"
#include "salamanquesa.h"

#ifdef COMPILE_ALSA
#include "audioalsa.h"
#endif


#ifdef COMPILE_PCSPEAKER
#include "audiopcspeaker.h"
#endif

 
#if defined(__APPLE__)
	#include <sys/syslimits.h>

	#include <sys/resource.h>

#endif


#ifdef COMPILE_CURSES
	#include "scrcurses.h"
#endif

#ifdef COMPILE_AA
	#include "scraa.h"
#endif

#ifdef COMPILE_STDOUT
	#include "scrstdout.h"
#endif


#ifdef COMPILE_XWINDOWS
	#include "scrxwindows.h"
#endif

#ifdef COMPILE_CURSESW
	#include "cursesw_ext.h"
#endif



//Opciones seleccionadas para cada menu
int debug_pok_file_opcion_seleccionada=0;
int poke_opcion_seleccionada=0; 
int audio_new_waveform_opcion_seleccionada=0;
int debug_new_visualmem_opcion_seleccionada=0;
int audio_new_ayplayer_opcion_seleccionada=0;
int osd_adventure_keyboard_opcion_seleccionada=0;
int debug_tsconf_dma_opcion_seleccionada=0;
int tsconf_layer_settings_opcion_seleccionada=0;
int cpu_stats_opcion_seleccionada=0;
int menu_tbblue_hardware_id_opcion_seleccionada=0;

int cpu_transaction_log_opcion_seleccionada=0;
int watches_opcion_seleccionada=0;
int record_mid_opcion_seleccionada=0;
int record_mid_instrument_opcion_seleccionada=0;
int direct_midi_output_opcion_seleccionada=0;
int ay_mixer_opcion_seleccionada=0;
int uartbridge_opcion_seleccionada=0;
int network_opcion_seleccionada=0;
int zeng_opcion_seleccionada=0;
int zx81_online_browser_opcion_seleccionada=0;
int online_browse_zx81_letter_opcion_seleccionada=0;
int settings_statistics_opcion_seleccionada=0;
int mmc_divmmc_opcion_seleccionada=0;
int ide_divide_opcion_seleccionada=0;
int display_settings_opcion_seleccionada=0;
int debug_tsconf_opcion_seleccionada=0;
int windows_opcion_seleccionada=0;
int zxpand_opcion_seleccionada=0;
int ql_mdv_flp_opcion_seleccionada=0;
int i8049_mixer_opcion_seleccionada=0;
int fileselector_settings_opcion_seleccionada=0;
int midi_output_instrument_opcion_seleccionada=0;
int snapshot_rewind_opcion_seleccionada=0;
int find_opcion_seleccionada=0;
int find_bytes_opcion_seleccionada=0;
int find_lives_opcion_seleccionada=0;
int audio_visual_realtape_opcion_seleccionada=0;
int hotswap_machine_opcion_seleccionada=0;
int custom_machine_opcion_seleccionada=0;
int machine_selection_por_fabricante_opcion_seleccionada=0;
int machine_selection_opcion_seleccionada=0;
int menu_machine_selection_by_name_opcion_seleccionada=0;
int licenses_opcion_seleccionada=0;
int about_opcion_seleccionada=0;
int input_file_keyboard_opcion_seleccionada=0;
int audio_opcion_seleccionada=0;
int debug_opcion_seleccionada=0;
int snapshot_opcion_seleccionada=0;
int esxdos_traps_opcion_seleccionada=0;
int plusthreedisk_opcion_seleccionada=0;
int msxcart_opcion_seleccionada=0;
int z88_slots_opcion_seleccionada=0;
int z88_slot_insert_opcion_seleccionada=0;
int z88_eprom_size_opcion_seleccionada=0;
int z88_flash_intel_size_opcion_seleccionada=0;
int storage_tape_opcion_seleccionada=0;
int storage_opcion_seleccionada=0;
int timexcart_opcion_seleccionada=0;
int dandanator_opcion_seleccionada=0;
int kartusho_opcion_seleccionada=0;
int samram_opcion_seleccionada=0;
int ifrom_opcion_seleccionada=0;
int hilow_opcion_seleccionada=0;
int superupgrade_opcion_seleccionada=0;
int zxuno_spi_flash_opcion_seleccionada=0;
int betadisk_opcion_seleccionada=0;
int menu_inicio_opcion_seleccionada=0;


//Fin opciones seleccionadas para cada menu


//Ultima direccion pokeada
int last_debug_poke_dir=16384; 



char last_ay_file[PATH_MAX]="";




char last_msx_cart[PATH_MAX]="";

//cinta seleccionada. tapefile apuntara aqui
char tape_open_file[PATH_MAX];
//cinta seleccionada. tape_out_file apuntara aqui
char tape_out_open_file[PATH_MAX];

char last_timex_cart[PATH_MAX]="";


 
void menu_debug_poke(MENU_ITEM_PARAMETERS)
{

        int valor_poke,dir,veces;

        char string_poke[4];
        char string_dir[10];
	char string_veces[6];

        sprintf (string_dir,"%XH",last_debug_poke_dir);

        menu_ventana_scanf("Address",string_dir,10);

        dir=parse_string_to_number(string_dir);

        /*if ( (dir<0 || dir>65535) && MACHINE_IS_SPECTRUM) {
                debug_printf (VERBOSE_ERR,"Invalid address %d",dir);
                return;
        }*/

				last_debug_poke_dir=dir;

        sprintf (string_poke,"0");

        menu_ventana_scanf("Poke Value",string_poke,4);

        valor_poke=parse_string_to_number(string_poke);

        if (valor_poke<0 || valor_poke>255) {
                debug_printf (VERBOSE_ERR,"Invalid value %d",valor_poke);
                return;
        }


	sprintf (string_veces,"1");

	menu_ventana_scanf("How many bytes?",string_veces,6);

	veces=parse_string_to_number(string_veces);

	if (veces<1 || veces>65536) {
                debug_printf (VERBOSE_ERR,"Invalid quantity %d",veces);
		return;
	}


	for (;veces;veces--,dir++) {

	        //poke_byte_no_time(dir,valor_poke);
		//poke_byte_z80_moto(dir,valor_poke);
		menu_debug_write_mapped_byte(dir,valor_poke);

	}

}



void menu_debug_poke_pok_file(MENU_ITEM_PARAMETERS)
{

        char *filtros[2];

        filtros[0]="pok";
        filtros[1]=0;

	char pokfile[PATH_MAX];

        int ret;

        ret=menu_filesel("Select POK File",filtros,pokfile);

	
	//contenido
	//MAX_LINEAS_POK_FILE es maximo de lineas de pok file
	//normalmente la tabla de pokes sera menor que el numero de lineas en el archivo .pok
	//struct s_pokfile tabla_pokes[MAX_LINEAS_POK_FILE];
	struct s_pokfile *tabla_pokes;
	tabla_pokes=malloc(sizeof(struct s_pokfile)*MAX_LINEAS_POK_FILE);	

	//punteros
	//struct s_pokfile *punteros_pokes[MAX_LINEAS_POK_FILE];
	struct s_pokfile **punteros_pokes;
	punteros_pokes=malloc(sizeof(struct s_pokfile *)*MAX_LINEAS_POK_FILE);


	if (tabla_pokes==NULL || punteros_pokes==NULL) cpu_panic("Can not allocate memory for poke table");

	int i;
	for (i=0;i<MAX_LINEAS_POK_FILE;i++) punteros_pokes[i]=&tabla_pokes[i];


        if (ret==1) {

                //cls_menu_overlay();
		int total=util_parse_pok_file(pokfile,punteros_pokes);

		if (total<1) {
			debug_printf (VERBOSE_ERR,"Error parsing POK file");
			return;
		}

		int j;
		for (j=0;j<total;j++) {
			debug_printf (VERBOSE_DEBUG,"menu poke index %d text %s bank %d address %d value %d value_orig %d",
				punteros_pokes[j]->indice_accion,
				punteros_pokes[j]->texto,
				punteros_pokes[j]->banco,
				punteros_pokes[j]->direccion,
				punteros_pokes[j]->valor,
				punteros_pokes[j]->valor_orig);
		}


		//Meter cada poke en un menu




        menu_item *array_menu_debug_pok_file;
        menu_item item_seleccionado;
        int retorno_menu;
	//Resetear siempre ultima linea = 0
	debug_pok_file_opcion_seleccionada=0;

	//temporal para mostrar todos los caracteres 0-255
	//int temp_conta=1;

        do {



		//Meter primer item de menu
		//truncar texto a 28 caracteres si excede de eso
		if (strlen(punteros_pokes[0]->texto)>28) punteros_pokes[0]->texto[28]=0;
                menu_add_item_menu_inicial_format(&array_menu_debug_pok_file,MENU_OPCION_NORMAL,NULL,NULL,"%s", punteros_pokes[0]->texto);


		//Luego recorrer array de pokes y cuando el numero de poke se incrementa, agregar
		int poke_anterior=0;

		int total_elementos=1;

		for (j=1;j<total;j++) {
			if (punteros_pokes[j]->indice_accion!=poke_anterior) {

				//temp para mostrar todos los caracteres 0-255
				//int kk;
				//for (kk=0;kk<strlen(punteros_pokes[j]->texto);kk++) {
				//	punteros_pokes[j]->texto[kk]=temp_conta++;
				//	if (temp_conta==256) temp_conta=1;
				//}

				poke_anterior=punteros_pokes[j]->indice_accion;
				//truncar texto a 28 caracteres si excede de eso
				if (strlen(punteros_pokes[j]->texto)>28) punteros_pokes[j]->texto[28]=0;
				menu_add_item_menu_format(array_menu_debug_pok_file,MENU_OPCION_NORMAL,NULL,NULL,"%s", punteros_pokes[j]->texto);

				total_elementos++;
				if (total_elementos==20) {
					debug_printf (VERBOSE_DEBUG,"Too many pokes to show on Window. Showing only first 20");
					menu_warn_message("Too many pokes to show on Window. Showing only first 20");
					break;
				}


			}
		}



                menu_add_item_menu(array_menu_debug_pok_file,"",MENU_OPCION_SEPARADOR,NULL,NULL);


                //menu_add_item_menu(array_menu_debug_pok_file,"ESC Back",MENU_OPCION_NORMAL|MENU_OPCION_ESC,NULL,NULL);
                menu_add_ESC_item(array_menu_debug_pok_file);

                retorno_menu=menu_dibuja_menu(&debug_pok_file_opcion_seleccionada,&item_seleccionado,array_menu_debug_pok_file,"Select Poke" );

                

                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion

			//Hacer poke sabiendo la linea seleccionada. Desde ahi, ejecutar todos los pokes de dicha accion
			debug_printf (VERBOSE_DEBUG,"Doing poke/s from line %d",debug_pok_file_opcion_seleccionada);

			z80_byte banco;
			z80_int direccion;
			z80_byte valor;

			//buscar indice_accion
			int result_poke=0;
			for (j=0;j<total && result_poke==0;j++) {

				debug_printf (VERBOSE_DEBUG,"index %d looking %d current %d",j,debug_pok_file_opcion_seleccionada,punteros_pokes[j]->indice_accion);

				if (punteros_pokes[j]->indice_accion==debug_pok_file_opcion_seleccionada) {
					banco=punteros_pokes[j]->banco;
					direccion=punteros_pokes[j]->direccion;
					valor=punteros_pokes[j]->valor;
					debug_printf (VERBOSE_DEBUG,"Doing poke bank %d address %d value %d",banco,direccion,valor);
					result_poke=util_poke(banco,direccion,valor);
				}


                      

			}
			if (result_poke==0) menu_generic_message("Poke","OK. Poke applied");
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




        }

	free(tabla_pokes);
	free(punteros_pokes);

}





void menu_poke(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_poke;
        menu_item item_seleccionado;
        int retorno_menu;

        do {


                menu_add_item_menu_inicial_format(&array_menu_poke,MENU_OPCION_NORMAL,menu_debug_poke,NULL,"~~Poke");
                menu_add_item_menu_shortcut(array_menu_poke,'p');
                menu_add_item_menu_tooltip(array_menu_poke,"Poke address");
                menu_add_item_menu_ayuda(array_menu_poke,"Poke address for infinite lives, etc... This item follows active memory zone. "
					"You can also poke on read-only memory, depending on the current memory zone");

		//No tiene sentido pues se puede usar las memory zones para esto
		/*if (MACHINE_IS_SPECTRUM_128_P2_P2A_P3 || MACHINE_IS_ZXUNO_BOOTM_DISABLED) {
			menu_add_item_menu(array_menu_poke,"Poke 128~~k mode",MENU_OPCION_NORMAL,menu_debug_poke_128k,NULL);
			menu_add_item_menu_shortcut(array_menu_poke,'k');
			menu_add_item_menu_tooltip(array_menu_poke,"Poke bank & address");
			menu_add_item_menu_ayuda(array_menu_poke,"Poke bank & address");
		}*/

		if (MACHINE_IS_SPECTRUM) {
			menu_add_item_menu(array_menu_poke,"Poke from .POK ~~file",MENU_OPCION_NORMAL,menu_debug_poke_pok_file,NULL);
			menu_add_item_menu_shortcut(array_menu_poke,'f');
			menu_add_item_menu_tooltip(array_menu_poke,"Poke reading .POK file");
			menu_add_item_menu_ayuda(array_menu_poke,"Poke reading .POK file");
		}


                menu_add_item_menu(array_menu_poke,"",MENU_OPCION_SEPARADOR,NULL,NULL);


                //menu_add_item_menu(array_menu_poke,"ESC Back",MENU_OPCION_NORMAL|MENU_OPCION_ESC,NULL,NULL);
                menu_add_ESC_item(array_menu_poke);

                retorno_menu=menu_dibuja_menu(&poke_opcion_seleccionada,&item_seleccionado,array_menu_poke,"Poke" );

                

                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);
}


#ifdef EMULATE_CPU_STATS

void menu_debug_cpu_stats_clear_disassemble_array(void)
{
	int i;

	for (i=0;i<DISASSEMBLE_ARRAY_LENGTH;i++) disassemble_array[i]=0;
}

void menu_debug_cpu_stats_diss_no_print(z80_byte index,z80_byte opcode,char *dumpassembler)
{

        size_t longitud_opcode;

        disassemble_array[index]=opcode;

        debugger_disassemble_array(dumpassembler,31,&longitud_opcode,0);
}


/*
void menu_debug_cpu_stats_diss(z80_byte index,z80_byte opcode,int linea)
{

	char dumpassembler[32];

	//Empezar con espacio
	dumpassembler[0]=' ';

	menu_debug_cpu_stats_diss_no_print(index,opcode,&dumpassembler[1]);

	menu_escribe_linea_opcion(linea,-1,1,dumpassembler);
}
*/

void menu_debug_cpu_stats_diss_complete_no_print (z80_byte opcode,char *buffer,z80_byte preffix1,z80_byte preffix2)
{

	//Sin prefijo
	if (preffix1==0) {
                        menu_debug_cpu_stats_clear_disassemble_array();
                        menu_debug_cpu_stats_diss_no_print(0,opcode,buffer);
	}

	//Con 1 solo prefijo
	else if (preffix2==0) {
                        menu_debug_cpu_stats_clear_disassemble_array();
                        disassemble_array[0]=preffix1;
                        menu_debug_cpu_stats_diss_no_print(1,opcode,buffer);
	}

	//Con 2 prefijos (DD/FD + CB)
	else {
                        //Opcode
                        menu_debug_cpu_stats_clear_disassemble_array();
                        disassemble_array[0]=preffix1;
                        disassemble_array[1]=preffix2;
                        disassemble_array[2]=0;
                        menu_debug_cpu_stats_diss_no_print(3,opcode,buffer);
	}
}



void menu_cpu_full_stats(unsigned int *stats_table,char *title,z80_byte preffix1,z80_byte preffix2)
{

	int index_op,index_buffer;
	unsigned int counter;

    char *stats_buffer=util_malloc_max_texto_generic_message("Can not allocate memory for showing stats");

	char dumpassembler[32];

	//margen suficiente para que quepa una linea y un contador int de 32 bits...
	//aunque si pasa el ancho de linea, la rutina de generic_message lo troceara
	char buf_linea[64];

	index_buffer=0;

	for (index_op=0;index_op<256;index_op++) {
		counter=util_stats_get_counter(stats_table,index_op);

		menu_debug_cpu_stats_diss_complete_no_print(index_op,dumpassembler,preffix1,preffix2);

		sprintf (buf_linea,"%02X %-16s: %u \n",index_op,dumpassembler,counter);
		//16 ocupa la instruccion mas larga: LD B,RLC (IX+dd)

		sprintf (&stats_buffer[index_buffer],"%s\n",buf_linea);
		//sprintf (&stats_buffer[index_buffer],"%02X: %11d\n",index_op,counter);
		//index_buffer +=16;
		index_buffer +=strlen(buf_linea);
	}

	stats_buffer[index_buffer]=0;

	menu_generic_message(title,stats_buffer);
    
    free(stats_buffer);

}

void menu_cpu_full_stats_codsinpr(MENU_ITEM_PARAMETERS)
{
	menu_cpu_full_stats(stats_codsinpr,"Full statistic no preffix",0,0);
}

void menu_cpu_full_stats_codpred(MENU_ITEM_PARAMETERS)
{
        menu_cpu_full_stats(stats_codpred,"Full statistic pref ED",0xED,0);
}

void menu_cpu_full_stats_codprcb(MENU_ITEM_PARAMETERS)
{
        menu_cpu_full_stats(stats_codprcb,"Full statistic pref CB",0xCB,0);
}

void menu_cpu_full_stats_codprdd(MENU_ITEM_PARAMETERS)
{
        menu_cpu_full_stats(stats_codprdd,"Full statistic pref DD",0xDD,0);
}

void menu_cpu_full_stats_codprfd(MENU_ITEM_PARAMETERS)
{
        menu_cpu_full_stats(stats_codprfd,"Full statistic pref FD",0xFD,0);
}

void menu_cpu_full_stats_codprddcb(MENU_ITEM_PARAMETERS)
{
        menu_cpu_full_stats(stats_codprddcb,"Full statistic pref DDCB",0xDD,0xCB);
}

void menu_cpu_full_stats_codprfdcb(MENU_ITEM_PARAMETERS)
{
        menu_cpu_full_stats(stats_codprfdcb,"Full statistic pref FDCB",0xFD,0xCB);
}


void menu_cpu_full_stats_clear(MENU_ITEM_PARAMETERS)
{
	util_stats_init();

	menu_generic_message_splash("Clear CPU statistics","OK. Statistics cleared");
}


void menu_debug_cpu_stats(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_cpu_stats;
        menu_item item_seleccionado;
        int retorno_menu;
        do {
                menu_add_item_menu_inicial_format(&array_menu_cpu_stats,MENU_OPCION_NORMAL,menu_debug_cpu_resumen_stats,NULL,"Compact Statistics");
                menu_add_item_menu_tooltip(array_menu_cpu_stats,"Shows Compact CPU Statistics");
                menu_add_item_menu_ayuda(array_menu_cpu_stats,"Shows the most used opcode for every type: without preffix, with ED preffix, "
					"etc. CPU Statistics are reset when changing machine or resetting CPU.");


                menu_add_item_menu_format(array_menu_cpu_stats,MENU_OPCION_NORMAL,menu_cpu_full_stats_codsinpr,NULL,"Full Statistics No pref");
		menu_add_item_menu_format(array_menu_cpu_stats,MENU_OPCION_NORMAL,menu_cpu_full_stats_codpred,NULL,"Full Statistics Pref ED");
		menu_add_item_menu_format(array_menu_cpu_stats,MENU_OPCION_NORMAL,menu_cpu_full_stats_codprcb,NULL,"Full Statistics Pref CB");
		menu_add_item_menu_format(array_menu_cpu_stats,MENU_OPCION_NORMAL,menu_cpu_full_stats_codprdd,NULL,"Full Statistics Pref DD");
		menu_add_item_menu_format(array_menu_cpu_stats,MENU_OPCION_NORMAL,menu_cpu_full_stats_codprfd,NULL,"Full Statistics Pref FD");
		menu_add_item_menu_format(array_menu_cpu_stats,MENU_OPCION_NORMAL,menu_cpu_full_stats_codprddcb,NULL,"Full Statistics Pref DDCB");
		menu_add_item_menu_format(array_menu_cpu_stats,MENU_OPCION_NORMAL,menu_cpu_full_stats_codprfdcb,NULL,"Full Statistics Pref FDCB");
		menu_add_item_menu_format(array_menu_cpu_stats,MENU_OPCION_NORMAL,menu_cpu_full_stats_clear,NULL,"Clear Statistics");


                menu_add_item_menu(array_menu_cpu_stats,"",MENU_OPCION_SEPARADOR,NULL,NULL);
                //menu_add_item_menu(array_menu_cpu_stats,"ESC Back",MENU_OPCION_NORMAL|MENU_OPCION_ESC,NULL,NULL);
                menu_add_ESC_item(array_menu_cpu_stats);

                retorno_menu=menu_dibuja_menu(&cpu_stats_opcion_seleccionada,&item_seleccionado,array_menu_cpu_stats,"CPU Statistics" );
		

                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);
}

int cpu_stats_valor_contador_segundo_anterior;

zxvision_window *menu_debug_cpu_resumen_stats_overlay_window;

void menu_debug_cpu_resumen_stats_overlay(void)
{
	if (!zxvision_drawing_in_background) normal_overlay_texto_menu();


    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_debug_cpu_resumen_stats_overlay_window->is_minimized) return;

    //printf("Overlay cpu stats %d\n",contador_segundo);

    char textostats[32];
	zxvision_window *ventana;

	ventana=menu_debug_cpu_resumen_stats_overlay_window;


    char dumpassembler[32];

    //Empezar con espacio
    dumpassembler[0]=' ';



    //printf ("%d %d\n",contador_segundo,cpu_stats_valor_contador_segundo_anterior);
     

    //esto hara ejecutar esto 2 veces por segundo
    if ( ((contador_segundo%500) == 0 && cpu_stats_valor_contador_segundo_anterior!=contador_segundo) || menu_multitarea==0) {
											cpu_stats_valor_contador_segundo_anterior=contador_segundo;
        //printf ("Refrescando. contador_segundo=%d\n",contador_segundo);

        int linea=0;
        int opcode;

        unsigned int sumatotal; 
        sumatotal=util_stats_sum_all_counters();
        sprintf (textostats,"Total opcodes run: %u",sumatotal);
        //menu_escribe_linea_opcion(linea++,-1,1,textostats);
        zxvision_print_string_defaults(ventana,1,linea++,textostats);
        


        //menu_escribe_linea_opcion(linea++,-1,1,"Most used op. for each preffix");
        zxvision_print_string_defaults(ventana,1,linea++,"Most used op. for each preffix");

        opcode=util_stats_find_max_counter(stats_codsinpr);
        sprintf (textostats,"Op nopref:    %02XH: %u",opcode,util_stats_get_counter(stats_codsinpr,opcode) );
        //menu_escribe_linea_opcion(linea++,-1,1,textostats);
        zxvision_print_string_defaults(ventana,1,linea++,textostats);
        

        //Opcode
        menu_debug_cpu_stats_diss_complete_no_print(opcode,&dumpassembler[1],0,0);
        //menu_escribe_linea_opcion(linea++,-1,1,dumpassembler);
        zxvision_print_string_defaults(ventana,1,linea++,dumpassembler);
        



        opcode=util_stats_find_max_counter(stats_codpred);
        sprintf (textostats,"Op pref ED:   %02XH: %u",opcode,util_stats_get_counter(stats_codpred,opcode) );
        //menu_escribe_linea_opcion(linea++,-1,1,textostats);
        zxvision_print_string_defaults(ventana,1,linea++,textostats);
        

        //Opcode
        menu_debug_cpu_stats_diss_complete_no_print(opcode,&dumpassembler[1],237,0);
        //menu_escribe_linea_opcion(linea++,-1,1,dumpassembler);
        zxvision_print_string_defaults(ventana,1,linea++,dumpassembler);
        


        opcode=util_stats_find_max_counter(stats_codprcb);
        sprintf (textostats,"Op pref CB:   %02XH: %u",opcode,util_stats_get_counter(stats_codprcb,opcode) );
        //menu_escribe_linea_opcion(linea++,-1,1,textostats);
        zxvision_print_string_defaults(ventana,1,linea++,textostats);


        //Opcode
        menu_debug_cpu_stats_diss_complete_no_print(opcode,&dumpassembler[1],203,0);
        //menu_escribe_linea_opcion(linea++,-1,1,dumpassembler);
        zxvision_print_string_defaults(ventana,1,linea++,dumpassembler);




        opcode=util_stats_find_max_counter(stats_codprdd);
        sprintf (textostats,"Op pref DD:   %02XH: %u",opcode,util_stats_get_counter(stats_codprdd,opcode) );
        //menu_escribe_linea_opcion(linea++,-1,1,textostats);
        zxvision_print_string_defaults(ventana,1,linea++,textostats);

        //Opcode
        menu_debug_cpu_stats_diss_complete_no_print(opcode,&dumpassembler[1],221,0);
        //menu_escribe_linea_opcion(linea++,-1,1,dumpassembler);
        zxvision_print_string_defaults(ventana,1,linea++,dumpassembler);


        opcode=util_stats_find_max_counter(stats_codprfd);
        sprintf (textostats,"Op pref FD:   %02XH: %u",opcode,util_stats_get_counter(stats_codprfd,opcode) );
        //menu_escribe_linea_opcion(linea++,-1,1,textostats);
        zxvision_print_string_defaults(ventana,1,linea++,textostats);

        //Opcode
        menu_debug_cpu_stats_diss_complete_no_print(opcode,&dumpassembler[1],253,0);
        //menu_escribe_linea_opcion(linea++,-1,1,dumpassembler);
        zxvision_print_string_defaults(ventana,1,linea++,dumpassembler);


        opcode=util_stats_find_max_counter(stats_codprddcb);
        sprintf (textostats,"Op pref DDCB: %02XH: %u",opcode,util_stats_get_counter(stats_codprddcb,opcode) );
        //menu_escribe_linea_opcion(linea++,-1,1,textostats);
        zxvision_print_string_defaults(ventana,1,linea++,textostats);

        //Opcode
        menu_debug_cpu_stats_diss_complete_no_print(opcode,&dumpassembler[1],221,203);
        //menu_escribe_linea_opcion(linea++,-1,1,dumpassembler);
        zxvision_print_string_defaults(ventana,1,linea++,dumpassembler);



        opcode=util_stats_find_max_counter(stats_codprfdcb);
        sprintf (textostats,"Op pref FDCB: %02XH: %u",opcode,util_stats_get_counter(stats_codprfdcb,opcode) );
        //menu_escribe_linea_opcion(linea++,-1,1,textostats);
        zxvision_print_string_defaults(ventana,1,linea++,textostats);

        //Opcode
        menu_debug_cpu_stats_diss_complete_no_print(opcode,&dumpassembler[1],253,203);
        //menu_escribe_linea_opcion(linea++,-1,1,dumpassembler);
        zxvision_print_string_defaults(ventana,1,linea++,dumpassembler);


        //zxvision_draw_window_contents(ventana);


    }

    //Siempre hará el dibujado de contenido para evitar que cuando esta en background, otra ventana por debajo escriba algo,
    //y entonces como esta no redibuja siempre, al no escribir encima, se sobreescribe este contenido con el de otra ventana
    //En ventanas que no escriben siempre su contenido, siempre deberia estar zxvision_draw_window_contents que lo haga siempre
    zxvision_draw_window_contents(ventana);



}

zxvision_window menu_debug_cpu_resumen_stats_ventana;

void menu_debug_cpu_resumen_stats(MENU_ITEM_PARAMETERS)
{

    

	menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();		

    zxvision_window *ventana;
    
    ventana=&menu_debug_cpu_resumen_stats_ventana;

    //IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
    //si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
    //la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
    zxvision_delete_window_if_exists(ventana);

		
	int x,y,ancho,alto,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;

	if (!util_find_window_geometry("cpucompactstatistics",&x,&y,&ancho,&alto,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
		x=menu_origin_x();
		y=1;
		ancho=32;
		alto=18;
	}		

	//int originx=menu_origin_x();

	//zxvision_new_window(ventana,x,y,ancho,alto,ancho-1,alto-2,"CPU Compact Statistics");

    zxvision_new_window_gn_cim(ventana,x,y,ancho,alto,ancho-1,alto-2,"CPU Compact Statistics","cpucompactstatistics",
        is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);


	ventana->can_be_backgrounded=1;	
	//indicar nombre del grabado de geometria
	//strcpy(ventana->geometry_name,"cpucompactstatistics");
    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;  
    //Y dibujar la ventana
    zxvision_draw_window(ventana);  

	
		


    menu_debug_cpu_resumen_stats_overlay_window=ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui

    cpu_stats_valor_contador_segundo_anterior=contador_segundo;

    //Cambiamos funcion overlay de texto de menu
    //Se establece a la de funcion de onda + texto
    set_menu_overlay_function(menu_debug_cpu_resumen_stats_overlay);

    //Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
    //Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
    if (zxvision_currently_restoring_windows_on_start) {
        //printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
        return;
    }	

	

	z80_byte tecla;

	do {
		tecla=zxvision_common_getkey_refresh();		
		zxvision_handle_cursors_pgupdn(ventana,tecla);
		//printf ("tecla: %d\n",tecla);
	} while (tecla!=2 && tecla!=3);				

	//Gestionar salir con tecla background
 
	menu_espera_no_tecla(); //Si no, se va al menu anterior.
	//En AY Piano por ejemplo esto no pasa aunque el estilo del menu es el mismo...

	//Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
	zxvision_set_window_overlay_from_current(ventana);	

    //restauramos modo normal de texto de menu
    set_menu_overlay_function(normal_overlay_texto_menu);


    cls_menu_overlay();	

	//Grabar geometria ventana
	util_add_window_geometry_compact(ventana);		


	if (tecla==3) {
		zxvision_message_put_window_background();
	}

	else {
		zxvision_destroy_window(ventana);		
 	}


}

#endif

void zxvision_test_sleep_quarter(void)
{
	int previo_contador_segundo=contador_segundo;

	while (1) {
		menu_cpu_core_loop();
		if (previo_contador_segundo!=contador_segundo && (contador_segundo%250)==0) return;

		if (menu_get_pressed_key()!=0) return;
	
	}
}


void menu_zxvision_test(MENU_ITEM_PARAMETERS)
{

        //Desactivamos interlace - si esta. Con interlace la forma de onda se dibuja encima continuamente, sin borrar
        //z80_bit copia_video_interlaced_mode;
        //copia_video_interlaced_mode.v=video_interlaced_mode.v;

        //disable_interlace();


        menu_espera_no_tecla();


	//Prueba filesel
       /* char *filtros[2];

        filtros[0]="";
        filtros[1]=0;

        char nombredestino[PATH_MAX];
	nombredestino[0]=0;


	int retorno=menu_filesel("Select Target File",filtros,nombredestino);
	printf ("retorno: %d nombredestino: [%s]\n",retorno,nombredestino);
	return;*/



		//zxvision_generic_message_tooltip("pruebas", 30, 0, 0, generic_message_tooltip_return *retorno, const char * texto_format , ...)
		zxvision_generic_message_tooltip("Pruebas" , 0 , 0, 0, 0, NULL, 0, "Hola que tal como estas esto es una prueba de escribir texto. "
					"No se que mas poner pero me voy a empezar a repetir, " 
					"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore "
					"et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip"
					" ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore "
					" eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia "
					"deserunt mollit anim id est laborum. Adios");
        //z80_byte acumulado;



        //Cambiamos funcion overlay de texto de menu
        //Se establece a la de funcion de audio waveform
	//set_menu_overlay_function(menu_audio_draw_sound_wave);

	zxvision_window ventana;

#define SOUND_ZXVISION_WAVE_X 1
#define SOUND_ZXVISION_WAVE_Y 3
#define SOUND_ZXVISION_WAVE_ANCHO 27
#define SOUND_ZXVISION_WAVE_ALTO 14

	int ancho_visible=SOUND_ZXVISION_WAVE_ANCHO;
	int alto_visible=SOUND_ZXVISION_WAVE_ALTO+4;

	int ancho_total=20;
	int alto_total=alto_visible+2;

	//menu_item *array_menu_audio_new_waveform;
      //  menu_item item_seleccionado;
        //int retorno_menu;
        


	  //Hay que redibujar la ventana desde este bucle
	zxvision_new_window(&ventana,SOUND_ZXVISION_WAVE_X,SOUND_ZXVISION_WAVE_Y-2,ancho_visible,alto_visible,
							ancho_total,alto_total,"ZXVision Test");
	zxvision_draw_window(&ventana);

	printf ("Created window\n");

	menu_espera_tecla();
	menu_espera_no_tecla();

	zxvision_draw_window_contents(&ventana);

	printf ("Drawn window contents\n");

	menu_espera_tecla(); 
	menu_espera_no_tecla();


	overlay_screen caracter;



	caracter.tinta=ESTILO_GUI_TINTA_NORMAL;
	caracter.papel=ESTILO_GUI_PAPEL_NORMAL;
	caracter.parpadeo=0;

	//Relleno pantalla
	z80_byte caracter_print=32;



	int x,y;

	for (y=0;y<alto_total;y++) {
		for (x=0;x<ancho_total;x++) {
			caracter.caracter=caracter_print;
			zxvision_print_char(&ventana,x,y,&caracter);	

			caracter_print++;
			if (caracter_print>126) caracter_print=32;		
		}
	}

	caracter.caracter='A';

	zxvision_print_char(&ventana,0,0,&caracter);

	caracter.caracter='B';

	zxvision_print_char(&ventana,0,1,&caracter);

	zxvision_print_string(&ventana,0,0,ESTILO_GUI_TINTA_NORMAL,ESTILO_GUI_PAPEL_NORMAL,0," Texto leyenda 1 ");
	zxvision_print_string(&ventana,0,1,ESTILO_GUI_TINTA_NORMAL,ESTILO_GUI_PAPEL_NORMAL,0," Texto leyenda 2 ");
	zxvision_print_string(&ventana,0,2,ESTILO_GUI_TINTA_NORMAL,ESTILO_GUI_PAPEL_NORMAL,0," Texto leyenda 3 ");

	zxvision_print_string(&ventana,2,3,ESTILO_GUI_PAPEL_NORMAL,ESTILO_GUI_TINTA_NORMAL,1," This is a test ");

	zxvision_print_string(&ventana,2,4,ESTILO_GUI_PAPEL_NORMAL,ESTILO_GUI_TINTA_NORMAL,1," Press a key ");
	zxvision_print_string(&ventana,2,5,ESTILO_GUI_PAPEL_NORMAL,ESTILO_GUI_TINTA_NORMAL,1," to next step ");

	zxvision_print_string(&ventana,2,6,ESTILO_GUI_TINTA_NORMAL,ESTILO_GUI_PAPEL_NORMAL,0," --^^flash^^--");
	zxvision_print_string(&ventana,2,7,ESTILO_GUI_TINTA_NORMAL,ESTILO_GUI_PAPEL_NORMAL,0," --~~inverse--");
	zxvision_print_string(&ventana,2,8,ESTILO_GUI_TINTA_NORMAL,ESTILO_GUI_PAPEL_NORMAL,0," --$$2ink--");


                    /*    menu_add_item_menu_inicial_format(&array_menu_audio_new_waveform,MENU_OPCION_NORMAL,menu_audio_new_waveform_shape,NULL,"Change wave ~~Shape");
                        menu_add_item_menu_shortcut(array_menu_audio_new_waveform,'s');

                        //Evito tooltips en los menus tabulados que tienen overlay porque al salir el tooltip detiene el overlay
                        //menu_add_item_menu_tooltip(array_menu_audio_new_waveform,"Change wave Shape");
                        menu_add_item_menu_ayuda(array_menu_audio_new_waveform,"Change wave Shape: simple line or vertical fill");
						//0123456789
						// Change wave Shape
						
			menu_add_item_menu_tabulado(array_menu_audio_new_waveform,1,0);





		//Nombre de ventana solo aparece en el caso de stdout
                retorno_menu=menu_dibuja_menu(&audio_new_waveform_opcion_seleccionada,&item_seleccionado,array_menu_audio_new_waveform,"Waveform" );*/


	ventana.upper_margin=2;
	ventana.lower_margin=1;


	menu_espera_tecla();
	menu_espera_no_tecla();

	zxvision_draw_window_contents(&ventana);

	menu_espera_tecla(); 
	menu_espera_no_tecla();

	//Jugar con offset
/*	int i;

	for (i=0;i<7;i++) {
		zxvision_set_offset_x(&ventana,i);

		zxvision_draw_window_contents(&ventana);

		printf ("Offset x %d\n",i);

		menu_espera_tecla();
		menu_espera_no_tecla();		
	}


	for (i=0;i<7;i++) {
		zxvision_set_offset_y(&ventana,i);

		zxvision_draw_window_contents(&ventana);

		printf ("Offset y %d\n",i);

		menu_espera_tecla();
		menu_espera_no_tecla();		
	}



	for (i=0;i<10;i++) {
		zxvision_set_x_position(&ventana,i);

		printf ("Move x %d\n",i);

		menu_espera_tecla();
		menu_espera_no_tecla();		
	}

	for (i=0;i<10;i++) {
		zxvision_set_y_position(&ventana,i);

		printf ("Move y %d\n",i);

		menu_espera_tecla();
		menu_espera_no_tecla();		
	}

	zxvision_set_x_position(&ventana,0);
	zxvision_set_y_position(&ventana,0);

	for (i=25;i<35;i++) {
		zxvision_set_visible_width(&ventana,i);

		printf ("width %d\n",i);

		menu_espera_tecla();
		menu_espera_no_tecla();		
	}	

	for (i=18;i<28;i++) {
		zxvision_set_visible_height(&ventana,i);

		printf ("height %d\n",i);

		menu_espera_tecla();
		menu_espera_no_tecla();		
	}	


	for (i=5;i>=0;i--) {
		zxvision_set_visible_width(&ventana,i);

		printf ("width %d\n",i);

		menu_espera_tecla();
		menu_espera_no_tecla();		
	}	

	zxvision_set_visible_width(&ventana,20);

	for (i=5;i>=0;i--) {
		zxvision_set_visible_height(&ventana,i);

		printf ("height %d\n",i);

		menu_espera_tecla();
		menu_espera_no_tecla();		
	}	


*/
	zxvision_print_string(&ventana,2,3,ESTILO_GUI_PAPEL_NORMAL,ESTILO_GUI_TINTA_NORMAL,1," Use cursors ");
	zxvision_print_string(&ventana,2,4,ESTILO_GUI_PAPEL_NORMAL,ESTILO_GUI_TINTA_NORMAL,1," to move offset ");	
	zxvision_print_string(&ventana,2,5,ESTILO_GUI_PAPEL_NORMAL,ESTILO_GUI_TINTA_NORMAL,1," QAOP size");	
	zxvision_print_string(&ventana,2,6,ESTILO_GUI_PAPEL_NORMAL,ESTILO_GUI_TINTA_NORMAL,1," ESC exit ");	


	//Rebotar
	int contador=0;

	int xpos=0;
	int ypos=0;

	int incx=+1;
	int incy=+1;

	int offsetx=0;
	int offsety=0;	

	int ancho=22;
	int alto=10;

	zxvision_set_visible_height(&ventana,alto);
	zxvision_set_visible_width(&ventana,ancho);	

	z80_byte tecla=0;

	//Salir con ESC
	while (tecla!=2) {

		zxvision_set_offset_x(&ventana,offsetx);
		zxvision_set_offset_y(&ventana,offsety);

		zxvision_set_x_position(&ventana,xpos);
		zxvision_set_y_position(&ventana,ypos);		

		zxvision_test_sleep_quarter();

		tecla=menu_get_pressed_key();
		//Cambio offset con cursores
		if (tecla==8) {
			offsetx--;
			printf ("Decrement offset x to %d\n",offsetx);
		}

		if (tecla==9) {
			offsetx++;
			printf ("Increment offset x to %d\n",offsetx);
		}

		if (tecla==10) {
			offsety++;
			printf ("Increment offset y to %d\n",offsety);
		}

		if (tecla==11) {
			offsety--;
			printf ("Decrement offset y to %d\n",offsety);
		}

		//Cambio tamanyo
		if (tecla=='a' && ypos+alto<24) {
			alto++;
			printf ("Increment height to %d\n",alto);
			zxvision_set_visible_height(&ventana,alto);
		}

		if (tecla=='q' && alto>1) {
			alto--;
			printf ("Decrement height to %d\n",alto);
			zxvision_set_visible_height(&ventana,alto);
		}

		if (tecla=='p' && xpos+ancho<32) {
			ancho++;
			printf ("Increment width to %d\n",ancho);
			zxvision_set_visible_width(&ventana,ancho);
		}

		if (tecla=='o' && ancho>7) {
			ancho--;
			printf ("Decrement width to %d\n",ancho);
			zxvision_set_visible_width(&ventana,ancho);
		}

		xpos +=incx;
		if (xpos+ancho>=32 || xpos<=0) {
			incx=-incx;
		}

		ypos +=incy;
		if (ypos+alto>=24 || ypos<=0) {
			incy=-incy;
		}		
		
		contador++;

		if (tecla!=0) menu_espera_no_tecla();

	}


	zxvision_print_string(&ventana,1,5,ESTILO_GUI_PAPEL_NORMAL,ESTILO_GUI_TINTA_NORMAL,1," Use mouse    ");
	zxvision_print_string(&ventana,1,6,ESTILO_GUI_PAPEL_NORMAL,ESTILO_GUI_TINTA_NORMAL,1," to move and   ");	
	zxvision_print_string(&ventana,1,7,ESTILO_GUI_PAPEL_NORMAL,ESTILO_GUI_TINTA_NORMAL,1," resize window  ");	
	zxvision_print_string(&ventana,1,8,ESTILO_GUI_PAPEL_NORMAL,ESTILO_GUI_TINTA_NORMAL,1," Right button exits ");	

	zxvision_draw_window_contents(&ventana);

	tecla=0;

	while (!mouse_right) {
		//menu_espera_tecla();
		tecla=menu_get_pressed_key();
		//Comprobar eventos raton
		menu_cpu_core_loop();
		//zxvision_handle_mouse_events(&ventana);
	} 

    cls_menu_overlay();
	zxvision_destroy_window(&ventana);
            




}


//Indica a la funcion de overlay cual es la ventana
zxvision_window *menu_about_core_statistics_overlay_window;

//Contador de segundo para hacer que el overlay solo se redibuje un numero de veces por segundo y no siempre
int menu_core_statistics_contador_segundo_anterior;

int core_statistics_previo_audio_buffer=0;

int core_statistics_previo_cpu=0;

int core_statistics_last_perc_audio=0;

int core_statistics_last_perc_dropped=0;

int core_statistics_ultimo_cpu_use_mostrado=0;

//La funcion de overlay
void menu_about_core_statistics_overlay_window_overlay(void)
{
    if (!zxvision_drawing_in_background) normal_overlay_texto_menu();

    menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech

    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_about_core_statistics_overlay_window->is_minimized) return;

    //printf("overlay core statistics %d\n",contador_segundo);

    zxvision_window *ventana;

    ventana=menu_about_core_statistics_overlay_window;    



    //esto hara ejecutar esto 2 veces por segundo
    if ( ((contador_segundo%500) == 0 && menu_core_statistics_contador_segundo_anterior!=contador_segundo) ) {

        menu_core_statistics_contador_segundo_anterior=contador_segundo;
        //printf ("Refrescando. contador_segundo=%d\n",contador_segundo);

        int linea=0;
        char texto_buffer[100];


        //Empezar con espacio
        texto_buffer[0]=' ';                


/*

Nota: calcular el tiempo entre ejecuciones de cada opcode no penaliza mucho el uso de cpu real.
Ejemplo:
--vo null --machine 48k 

Sin calcular ese tiempo: 9% cpu
Calculando ese tiempo: 12% cpu

*/


//Ultimo intervalo de tiempo
//long core_cpu_timer_frame_difftime;
//Media de todos los intervalos
//long core_cpu_timer_frame_media=0;

        long valor_mostrar;
        valor_mostrar=core_cpu_timer_frame_difftime;
        //controlar maximos
        if (valor_mostrar>999999) valor_mostrar=999999;
            //01234567890123456789012345678901
            // Last core frame: 999999 us
        sprintf (texto_buffer,"Last core frame:     %6ld us",valor_mostrar);
        //menu_escribe_linea_opcion(linea++,-1,1,texto_buffer);	
        zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

        valor_mostrar=core_cpu_timer_frame_media;
        //controlar maximos
        if (valor_mostrar>999999) valor_mostrar=999999;
        //01234567890123456789012345678901
            // Last core frame: 999999 us
        sprintf (texto_buffer," Average:   %6ld us",valor_mostrar);
        //menu_escribe_linea_opcion(linea++,-1,1,texto_buffer);
        zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);


        valor_mostrar=core_cpu_timer_refresca_pantalla_difftime;
        //controlar maximos
        if (valor_mostrar>999999) valor_mostrar=999999;
        //01234567890123456789012345678901
        // Last render display: 999999 us
        sprintf (texto_buffer,"Last full render:    %6ld us",valor_mostrar);
        //menu_escribe_linea_opcion(linea++,-1,1,texto_buffer);
        zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

        valor_mostrar=core_cpu_timer_refresca_pantalla_media;
        //controlar maximos
        if (valor_mostrar>999999) valor_mostrar=999999;
        //01234567890123456789012345678901
            // Last core refresca_pantalla: 999999 us
        sprintf (texto_buffer," Average:   %6ld us",valor_mostrar);
        //menu_escribe_linea_opcion(linea++,-1,1,texto_buffer);
        zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);


        valor_mostrar=core_cpu_timer_each_frame_difftime;
        //controlar maximos
        if (valor_mostrar>999999) valor_mostrar=999999;
        //01234567890123456789012345678901
        // Time between frames: 999999 us
        sprintf (texto_buffer,"Time between frames: %6ld us",valor_mostrar);
        //menu_escribe_linea_opcion(linea++,-1,1,texto_buffer);
        zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

        valor_mostrar=core_cpu_timer_each_frame_media;
        //controlar maximos
        if (valor_mostrar>999999) valor_mostrar=999999;
        //01234567890123456789012345678901
            // Last core each_frame: 999999 us
        sprintf (texto_buffer," Average:   %6ld us",valor_mostrar);
        //menu_escribe_linea_opcion(linea++,-1,1,texto_buffer);
        zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

        //menu_escribe_linea_opcion(linea++,-1,1," (ideal):  20000 us");
        zxvision_print_string_defaults(ventana,1,linea++," (expected): 20000 us");

        sprintf (texto_buffer,"Total video frames: %d",stats_frames_total);
        zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

        sprintf (texto_buffer," Drawn: %d",stats_frames_total_drawn);
        zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

        int perc_dropped;

        //Evitar división por cero
        if (stats_frames_total==0) perc_dropped=0;

        else perc_dropped=(stats_frames_total_dropped*100)/stats_frames_total;

        sprintf (texto_buffer," Dropped: %d (%3d%%)",stats_frames_total_dropped,perc_dropped);
        core_statistics_last_perc_dropped=perc_dropped;
        zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

        /*int media_cpu=0;

        if (cpu_use_total_acumulado_medidas>0) {
            media_cpu=cpu_use_total_acumulado/cpu_use_total_acumulado_medidas;
        }*/

        int media_cpu=sensor_get_percentaje_value("instant_avg_cpu");

        int tamanyo_buffer_audio,posicion_buffer_audio;
		audio_get_buffer_info(&tamanyo_buffer_audio,&posicion_buffer_audio);

        int perc_audio;
        //mostrar una barra de llenado del buffer
        //usa las mismas funciones de volumen de AY chip donde el maximo es 15
        //int barra_volumen;

        if (tamanyo_buffer_audio==0) {
            perc_audio=0;
            //barra_volumen=15;
        }

        else {
            perc_audio=(posicion_buffer_audio*100)/tamanyo_buffer_audio;
            //barra_volumen=(posicion_buffer_audio*15)/tamanyo_buffer_audio;
        }

        char buf_volumen_canal[32];
        //menu_string_volumen(buf_volumen_canal,barra_volumen,core_statistics_previo_audio_buffer);

        //core_statistics_previo_audio_buffer=barra_volumen;

        core_statistics_previo_audio_buffer=menu_string_volumen_maxmin(buf_volumen_canal,posicion_buffer_audio,
                                                    core_statistics_previo_audio_buffer,tamanyo_buffer_audio);


        sprintf (texto_buffer,"Audio Buffer%s: %d/%d (%3d%%) [%s]",
                    (si_audio_silenced() ? " (Silenced)" : ""),
                    posicion_buffer_audio,tamanyo_buffer_audio,perc_audio,buf_volumen_canal);

        core_statistics_last_perc_audio=perc_audio;
        
        zxvision_print_string_defaults_fillspc(ventana,1,linea++,texto_buffer);     



		//Uso cpu no se ve en windows
#ifndef MINGW
        if (screen_show_cpu_usage.v && menu_footer) {

            //mostrar una barra de llenado del buffer
            //usa las mismas funciones de volumen de AY chip donde el maximo es 15
            char buf_barra_cpu[32];
            /*
            int barra_cpu;

            barra_cpu=(media_cpu*15)/100;

            
            menu_string_volumen(buf_barra_cpu,barra_cpu,core_statistics_previo_cpu);

            core_statistics_previo_cpu=barra_cpu;
            */

            core_statistics_previo_cpu=menu_string_volumen_maxmin(buf_barra_cpu,media_cpu,core_statistics_previo_cpu,100);
            core_statistics_ultimo_cpu_use_mostrado=media_cpu;



            sprintf(texto_buffer,"Average CPU Use: %d%% [%s]",media_cpu,buf_barra_cpu);
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);
        }
#endif
        

    }


    //Prueba medidores de rendimiento
    
    int fila_texto=14;
    int margen_horizontal=ZXVISION_WIDGET_TYPE_SPEEDOMETER_LINE_LENGTH;
    
    int longitud_linea=ZXVISION_WIDGET_TYPE_SPEEDOMETER_LINE_LENGTH;

    //char buffer_texto_meters[30];

    
    
    //int grados;
    //0 grados=0%
    //180 grados=100%

    
        
    int yorigen_linea=(fila_texto*8)+longitud_linea+16;        

    //CPU USE
    int pos_x=1;
    int xorigen_linea=menu_char_width+longitud_linea; //Para ajustarlo por la derecha
    
    int color=ESTILO_GUI_COLOR_WAVEFORM;
    if (core_statistics_ultimo_cpu_use_mostrado>=75) color=ESTILO_GUI_COLOR_AVISO;
    
    zxvision_print_string_defaults(ventana,pos_x,fila_texto,"CPU");
    zxvision_widgets_draw_speedometer_common(ventana,xorigen_linea,yorigen_linea,core_statistics_ultimo_cpu_use_mostrado,color,color);                   


    //AUDIO BUFFER
    pos_x += (longitud_linea*2+margen_horizontal)/menu_char_width;

    xorigen_linea=xorigen_linea+longitud_linea*2+margen_horizontal; //A la derecha del anterior

    color=ESTILO_GUI_COLOR_WAVEFORM;
    //es tan malo como que este lleno como vacio
    if (core_statistics_last_perc_audio>=90 || core_statistics_last_perc_audio<=10) color=ESTILO_GUI_COLOR_AVISO;        

    zxvision_print_string_defaults(ventana,pos_x,fila_texto,"Audio");
    zxvision_widgets_draw_speedometer_common(ventana,xorigen_linea,yorigen_linea,core_statistics_last_perc_audio,color,color);           


    //DROPPED FRAMES
    pos_x += (longitud_linea*2+margen_horizontal)/menu_char_width;

    xorigen_linea=xorigen_linea+longitud_linea*2+margen_horizontal; //A la derecha del anterior

    color=ESTILO_GUI_COLOR_WAVEFORM;
    if (core_statistics_last_perc_dropped>=75) color=ESTILO_GUI_COLOR_AVISO;              
    
    zxvision_print_string_defaults(ventana,pos_x,fila_texto,"Dropped");
    zxvision_widgets_draw_speedometer_common(ventana,xorigen_linea,yorigen_linea,core_statistics_last_perc_dropped,color,color);




    //Siempre hará el dibujado de contenido para evitar que cuando esta en background, otra ventana por debajo escriba algo,
    //y entonces como esta no redibuja siempre, al no escribir encima, se sobreescribe este contenido con el de otra ventana
    //En ventanas que no escriben siempre su contenido, siempre deberia estar zxvision_draw_window_contents que lo haga siempre
    zxvision_draw_window_contents(ventana);
}

//La ventana tal cual que creamos. Es la estructura, no un puntero
zxvision_window zxvision_window_core_statistics;

void menu_about_core_statistics(MENU_ITEM_PARAMETERS)
{

    menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();

    if (!menu_multitarea) {
        menu_warn_message("This window needs multitask enabled");
        return;
    }

    //Nuestro puntero apunta a la estructura que hay fuera, por comodidad de usar el nombre de puntero "ventana"
    zxvision_window *ventana;
    ventana=&zxvision_window_core_statistics;    

    //IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
    //si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
    //la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
    zxvision_delete_window_if_exists(ventana);    

    int x_ventana,y_ventana,ancho_ventana,alto_ventana,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;

    //Recuperar geometria
    if (!util_find_window_geometry("corestatistics",&x_ventana,&y_ventana,&ancho_ventana,&alto_ventana,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
        alto_ventana=14;
        ancho_ventana=32;

        x_ventana=menu_center_x()-ancho_ventana/2; 
        y_ventana=menu_center_y()-alto_ventana/2; 
    }    

    //Crear ventana
	//zxvision_new_window(ventana,x_ventana,y_ventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,"Core Statistics");

    zxvision_new_window_gn_cim(ventana,x_ventana,y_ventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,"Core Statistics","corestatistics",
        is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);                                

    //Se puede ir a background
    ventana->can_be_backgrounded=1;
    //indicar nombre del grabado de geometria
    //strcpy(ventana->geometry_name,"corestatistics");
    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;    
    //Y dibujar la ventana
    zxvision_draw_window(ventana);


    menu_about_core_statistics_overlay_window=ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui

    //Cambiamos funcion overlay de texto de menu
    set_menu_overlay_function(menu_about_core_statistics_overlay_window_overlay);

    //Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
    //Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
    if (zxvision_currently_restoring_windows_on_start) {
        //printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
        return;
    }    

    z80_byte tecla;

    //Y esperar escape (2) o tecla background (3)
    do {
            tecla=zxvision_common_getkey_refresh();
            zxvision_handle_cursors_pgupdn(ventana,tecla);
            //printf ("tecla: %d\n",tecla);
    } while (tecla!=2 && tecla!=3);

    //Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
    zxvision_set_window_overlay_from_current(ventana);

    //restauramos modo normal de texto de menu
    set_menu_overlay_function(normal_overlay_texto_menu);


    cls_menu_overlay();
    util_add_window_geometry_compact(ventana);

    if (tecla==3) {
            zxvision_message_put_window_background();
    }

    else {
            zxvision_destroy_window(ventana);
    }


}




int ayregisters_previo_valor_volume_A[MAX_AY_CHIPS];
int ayregisters_previo_valor_volume_B[MAX_AY_CHIPS];
int ayregisters_previo_valor_volume_C[MAX_AY_CHIPS];
int ayregisters_previo_valor_volume_noise;

	int menu_ayregisters_valor_contador_segundo_anterior;

zxvision_window *menu_ay_registers_overlay_window;

void menu_ay_registers_overlay(void)
{

	//NOTA: //Hemos de suponer que current window es esta de ay registers

    if (!zxvision_drawing_in_background) normal_overlay_texto_menu();


	menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech    


    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_ay_registers_overlay_window->is_minimized) return;    



	char volumen[32],textotono[32];
	char textovolumen[35]; //32+3 de posible color rojo del maximo


	int total_chips=ay_retorna_numero_chips();

	//Como maximo mostrarmos 3 canales ay
	if (total_chips>3) total_chips=3;

	int chip;

	int linea=0;


	int vol_A[MAX_AY_CHIPS],vol_B[MAX_AY_CHIPS],vol_C[MAX_AY_CHIPS],vol_noise;


	if (sn_chip_present.v) {

		//Para chip SN76489A de coleco y sg1000 y sms
		total_chips=1;



      		vol_A[0]=sn_chip_registers[6] & 15;
        	vol_B[0]=sn_chip_registers[7] & 15;
        	vol_C[0]=sn_chip_registers[8] & 15;
			vol_noise=sn_chip_registers[10] & 15;

			//Controlar limites, dado que las variables entran sin inicializar
			if (ayregisters_previo_valor_volume_A[0]>16) ayregisters_previo_valor_volume_A[0]=16;
			if (ayregisters_previo_valor_volume_B[0]>16) ayregisters_previo_valor_volume_B[0]=16;
			if (ayregisters_previo_valor_volume_C[0]>16) ayregisters_previo_valor_volume_C[0]=16;
			if (ayregisters_previo_valor_volume_noise>16) ayregisters_previo_valor_volume_noise=16;
			

			ayregisters_previo_valor_volume_A[0]=menu_decae_ajusta_valor_volumen(ayregisters_previo_valor_volume_A[0],vol_A[0]);
			ayregisters_previo_valor_volume_B[0]=menu_decae_ajusta_valor_volumen(ayregisters_previo_valor_volume_B[0],vol_B[0]);
			ayregisters_previo_valor_volume_C[0]=menu_decae_ajusta_valor_volumen(ayregisters_previo_valor_volume_C[0],vol_C[0]);
			ayregisters_previo_valor_volume_noise=menu_decae_ajusta_valor_volumen(ayregisters_previo_valor_volume_noise,vol_noise);


			z80_byte volumen_canal;

			volumen_canal=15 - (sn_chip_registers[6] & 15);
			menu_string_volumen(volumen,volumen_canal,ayregisters_previo_valor_volume_A[0]);
			sprintf (textovolumen,"Volume A: %s",volumen);
			//menu_escribe_linea_opcion(linea++,-1,1,textovolumen);
			zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textovolumen);

			volumen_canal=15 - (sn_chip_registers[7] & 15);
			menu_string_volumen(volumen,volumen_canal,ayregisters_previo_valor_volume_B[0]);
			sprintf (textovolumen,"Volume B: %s",volumen);
			//menu_escribe_linea_opcion(linea++,-1,1,textovolumen);
			zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textovolumen);

			volumen_canal=15 - (sn_chip_registers[8] & 15);
			menu_string_volumen(volumen,volumen_canal,ayregisters_previo_valor_volume_C[0]);
			sprintf (textovolumen,"Volume C: %s",volumen);
			//menu_escribe_linea_opcion(linea++,-1,1,textovolumen);
			zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textovolumen);


			volumen_canal=15 - (sn_chip_registers[10] & 15);
			menu_string_volumen(volumen,volumen_canal,ayregisters_previo_valor_volume_noise);
								//"Volume C: %s"
			sprintf (textovolumen,"V Noise:  %s",volumen);
			//menu_escribe_linea_opcion(linea++,-1,1,textovolumen);
			zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textovolumen);



			int freq_a=sn_retorna_frecuencia(0);
			int freq_b=sn_retorna_frecuencia(1);
			int freq_c=sn_retorna_frecuencia(2);
			sprintf (textotono,"Channel A:  %3s %7d Hz",get_note_name(freq_a),freq_a);
			//menu_escribe_linea_opcion(linea++,-1,1,textotono);
			zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textotono);

			sprintf (textotono,"Channel B:  %3s %7d Hz",get_note_name(freq_b),freq_b);
			//menu_escribe_linea_opcion(linea++,-1,1,textotono);
			zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textotono);

			sprintf (textotono,"Channel C:  %3s %7d Hz",get_note_name(freq_c),freq_c);
			zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textotono);


					                        //Tipo ruido
											/*
+--+--+--+--+--+--+--+--+
|1 |1 |1 |0 |xx|FB|M1|M0|
+--+--+--+--+--+--+--+--+

FB= Feedback:

0= 'Periodic' noise
1= 'white' noise 

The white noise sounds, well, like white noise.
The periodic noise is intresting.  Depending on the frequency, it can
sound very tonal and smooth.

M1-M0= mode bits:

00= Fosc/512  Very 'hissy'; like grease frying
01= Fosc/1024 Slightly lower
10= Fosc/2048 More of a high rumble
11= output of tone generator #3											
											*/

						z80_byte noise_control=sn_chip_registers[9];


						sprintf (textotono,"Noise Type: %s",(noise_control & 4 ? "White" : "Periodic"));
						zxvision_print_string_defaults_fillspc(menu_ay_registers_overlay_window,1,linea++,textotono);

						
						sprintf (textotono,"Noise Mode: %d",noise_control & 3);
						zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textotono);							
						
					

											/*
                        int freq_temp=ay_3_8912_registros[chip][6] & 31;
                        //printf ("Valor registros ruido : %d Hz\n",freq_temp);
                        freq_temp=freq_temp*16;

                        //controlamos divisiones por cero
                        if (!freq_temp) freq_temp++;

                        int freq_ruido=FRECUENCIA_NOISE/freq_temp;

                        sprintf (textotono,"Frequency Noise: %6d Hz",freq_ruido);
                        //menu_escribe_linea_opcion(linea++,-1,1,textotono);
						zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textotono);
							*/

						


	}

    else if (i8049_chip_present) {
        total_chips=1;

            int volumen_pitch1;

            if (ql_audio_playing) volumen_pitch1=15;
            else volumen_pitch1=0;

      		vol_A[0]=volumen_pitch1;


			//Controlar limites, dado que las variables entran sin inicializar
			if (ayregisters_previo_valor_volume_A[0]>16) ayregisters_previo_valor_volume_A[0]=16;

			

			ayregisters_previo_valor_volume_A[0]=menu_decae_ajusta_valor_volumen(ayregisters_previo_valor_volume_A[0],vol_A[0]);



			z80_byte volumen_canal;

			volumen_canal=volumen_pitch1;
			menu_string_volumen(volumen,volumen_canal,ayregisters_previo_valor_volume_A[0]);
			sprintf (textovolumen,"Volume: %s",volumen);
			//menu_escribe_linea_opcion(linea++,-1,1,textovolumen);
			zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textovolumen);


        int freq_a=ql_ipc_get_frecuency_sound_current_pitch();

        sprintf (textotono,"Frequency: %3s %7d Hz",get_note_name(freq_a),freq_a);
        //menu_escribe_linea_opcion(linea++,-1,1,textotono);
        zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textotono);   

        zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,(ql_audio_playing ? "Playing" : "Stopped") );

        
    /*
    Formato del mensaje ipc:

    8 bits pitch 1
    8 bits pitch 2
    16 bits  interval between steps (grad_x)
    16 bits duration
    4 bits step in pitch (grad_y)
    4 bits wrap
    4 bits randomness of step
    4 bits fuzziness


*/      

        zxvision_print_string_defaults_fillspc(menu_ay_registers_overlay_window,1,linea++,"");

        //Nota: imprimo todos con %5d para que esten alineados, independientemente si son valores de 4, 8 o 16 bis
        sprintf (textotono,"Pitch1:         %5d",ql_audio_pitch1);
        zxvision_print_string_defaults_fillspc(menu_ay_registers_overlay_window,1,linea++,textotono);       
        sprintf (textotono,"Pitch2:         %5d",ql_audio_pitch2);
        zxvision_print_string_defaults_fillspc(menu_ay_registers_overlay_window,1,linea++,textotono);  
        sprintf (textotono,"Interval steps: %5d",ql_audio_grad_x);
        zxvision_print_string_defaults_fillspc(menu_ay_registers_overlay_window,1,linea++,textotono);            
        sprintf (textotono,"Duration:       %5d",ql_audio_duration);
        zxvision_print_string_defaults_fillspc(menu_ay_registers_overlay_window,1,linea++,textotono);            
        sprintf (textotono,"Step in pitch:  %5d",ql_audio_grad_y);
        zxvision_print_string_defaults_fillspc(menu_ay_registers_overlay_window,1,linea++,textotono);
        sprintf (textotono,"Wrap:           %5d",ql_audio_wrap);
        zxvision_print_string_defaults_fillspc(menu_ay_registers_overlay_window,1,linea++,textotono);
        sprintf (textotono,"Randomness:     %5d",ql_audio_randomness_of_step);
        zxvision_print_string_defaults_fillspc(menu_ay_registers_overlay_window,1,linea++,textotono);
        sprintf (textotono,"Fuziness:       %5d",ql_audio_fuziness);
        zxvision_print_string_defaults_fillspc(menu_ay_registers_overlay_window,1,linea++,textotono);
            
    }

	else {

	for (chip=0;chip<total_chips;chip++) {


        	vol_A[chip]=ay_3_8912_registros[chip][8] & 15;
        	vol_B[chip]=ay_3_8912_registros[chip][9] & 15;
        	vol_C[chip]=ay_3_8912_registros[chip][10] & 15;

			//Controlar limites, dado que las variables entran sin inicializar
			if (ayregisters_previo_valor_volume_A[chip]>16) ayregisters_previo_valor_volume_A[chip]=16;
			if (ayregisters_previo_valor_volume_B[chip]>16) ayregisters_previo_valor_volume_B[chip]=16;
			if (ayregisters_previo_valor_volume_C[chip]>16) ayregisters_previo_valor_volume_C[chip]=16;
			

			ayregisters_previo_valor_volume_A[chip]=menu_decae_ajusta_valor_volumen(ayregisters_previo_valor_volume_A[chip],vol_A[chip]);
			ayregisters_previo_valor_volume_B[chip]=menu_decae_ajusta_valor_volumen(ayregisters_previo_valor_volume_B[chip],vol_B[chip]);
			ayregisters_previo_valor_volume_C[chip]=menu_decae_ajusta_valor_volumen(ayregisters_previo_valor_volume_C[chip],vol_C[chip]);



        		//if (ayregisters_previo_valor_volume_A[chip]<vol_A[chip]) ayregisters_previo_valor_volume_A[chip]=vol_A[chip];
        		//if (ayregisters_previo_valor_volume_B[chip]<vol_B[chip]) ayregisters_previo_valor_volume_B[chip]=vol_B[chip];
        		//if (ayregisters_previo_valor_volume_C[chip]<vol_C[chip]) ayregisters_previo_valor_volume_C[chip]=vol_C[chip];


			menu_string_volumen(volumen,ay_3_8912_registros[chip][8],ayregisters_previo_valor_volume_A[chip]);
			sprintf (textovolumen,"Volume A: %s",volumen);
			//menu_escribe_linea_opcion(linea++,-1,1,textovolumen);
			zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textovolumen);

			menu_string_volumen(volumen,ay_3_8912_registros[chip][9],ayregisters_previo_valor_volume_B[chip]);
			sprintf (textovolumen,"Volume B: %s",volumen);
			//menu_escribe_linea_opcion(linea++,-1,1,textovolumen);
			zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textovolumen);

			menu_string_volumen(volumen,ay_3_8912_registros[chip][10],ayregisters_previo_valor_volume_C[chip]);
			sprintf (textovolumen,"Volume C: %s",volumen);
			//menu_escribe_linea_opcion(linea++,-1,1,textovolumen);
			zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textovolumen);



			int freq_a=ay_retorna_frecuencia(0,chip);
			int freq_b=ay_retorna_frecuencia(1,chip);
			int freq_c=ay_retorna_frecuencia(2,chip);
			sprintf (textotono,"Channel A:  %3s %7d Hz",get_note_name(freq_a),freq_a);
			//menu_escribe_linea_opcion(linea++,-1,1,textotono);
			zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textotono);

			sprintf (textotono,"Channel B:  %3s %7d Hz",get_note_name(freq_b),freq_b);
			//menu_escribe_linea_opcion(linea++,-1,1,textotono);
			zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textotono);

			sprintf (textotono,"Channel C:  %3s %7d Hz",get_note_name(freq_c),freq_c);
			//menu_escribe_linea_opcion(linea++,-1,1,textotono);
			zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textotono);


			//Si hay 3 canales, los 3 siguientes items no se ven
			if (total_chips<3) {

			                        //Frecuencia ruido
                        int freq_temp=ay_3_8912_registros[chip][6] & 31;
                        //printf ("Valor registros ruido : %d Hz\n",freq_temp);
                        freq_temp=freq_temp*16;

                        //controlamos divisiones por cero
                        if (!freq_temp) freq_temp++;

                        int freq_ruido=FRECUENCIA_NOISE/freq_temp;

                        sprintf (textotono,"Frequency Noise: %6d Hz",freq_ruido);
                        //menu_escribe_linea_opcion(linea++,-1,1,textotono);
						zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textotono);


			//Envelope

                        freq_temp=ay_3_8912_registros[chip][11]+256*(ay_3_8912_registros[chip][12] & 0xFF);


                        //controlamos divisiones por cero
                        if (!freq_temp) freq_temp++;
                        int freq_envelope=FRECUENCIA_ENVELOPE/freq_temp;

                        //sprintf (textotono,"Freq Envelope(*10): %5d Hz",freq_envelope);

			int freq_env_10=freq_envelope/10;
			int freq_env_decimal=freq_envelope-(freq_env_10*10);

			sprintf (textotono,"Freq Envelope:   %4d.%1d Hz",freq_env_10,freq_env_decimal);
      		//menu_escribe_linea_opcion(linea++,-1,1,textotono);
			zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textotono);



			char envelope_name[32];
			z80_byte env_type=ay_3_8912_registros[chip][13] & 0x0F;
			return_envelope_name(env_type,envelope_name);
			sprintf (textotono,"Env.: %2d (%s)",env_type,envelope_name);
            //menu_escribe_linea_opcion(linea++,-1,1,textotono);
			zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textotono);


			}



			sprintf (textotono,"Tone Channels:  %c %c %c",
				( (ay_3_8912_registros[chip][7]&1)==0 ? 'A' : ' '),
				( (ay_3_8912_registros[chip][7]&2)==0 ? 'B' : ' '),
				( (ay_3_8912_registros[chip][7]&4)==0 ? 'C' : ' '));
			//menu_escribe_linea_opcion(linea++,-1,1,textotono);
			zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textotono);

			//Si hay 3 canales, los 3 siguientes items no se ven
			if (total_chips<3) {

                        sprintf (textotono,"Noise Channels: %c %c %c",
                                ( (ay_3_8912_registros[chip][7]&8)==0  ? 'A' : ' '),
                                ( (ay_3_8912_registros[chip][7]&16)==0 ? 'B' : ' '),
                                ( (ay_3_8912_registros[chip][7]&32)==0 ? 'C' : ' '));
                        //menu_escribe_linea_opcion(linea++,-1,1,textotono);
						zxvision_print_string_defaults(menu_ay_registers_overlay_window,1,linea++,textotono);
			}

            //Contadores graficos 
            //if (chip==0) {
                int margen_horizontal=30;
                
                int longitud_linea=ZXVISION_WIDGET_TYPE_SPEEDOMETER_LINE_LENGTH;

                //fila inicial segun total de chips
                int fila_texto=12;
                if (total_chips==2) fila_texto=23;
                if (total_chips==3) fila_texto=22;

                //Y desplazamiento vertical segun donde ubicamos el contador grafico segun el contador de chip
                fila_texto +=((longitud_linea/8)+4)*chip;

               //TODO: con 3 chips no cabe en vertical todo
                int yorigen_linea=(fila_texto*8)+longitud_linea+16;

                char buffer_texto_meter[100];
                

                //Volumen A
                int columna_texto=1;
                int xorigen_linea=40;
                int porcentaje; //=(valor_volumen*100)/15;
                //porcentaje=((ay_3_8912_registros[chip][8]&15)*100)/15;

                char sensor_name[SENSORS_MAX_SHORT_NAME];
                sprintf(sensor_name,"ay_vol_chip%d_chan_A",chip);
                porcentaje=sensor_get_percentaje_value(sensor_name);

                sprintf(buffer_texto_meter,"A[%d]",chip);
                int color=ESTILO_GUI_COLOR_WAVEFORM;
                if (porcentaje>=85) color=ESTILO_GUI_COLOR_AVISO;

                zxvision_print_string_defaults(menu_ay_registers_overlay_window,columna_texto,fila_texto,buffer_texto_meter);
                //borrar primero el espacio ocupado por el speedometer por el frame anterior. Si no lo hicieramos, quedaria "rastro"
                zxvision_widgets_erase_speedometer(menu_ay_registers_overlay_window,xorigen_linea,yorigen_linea);
                zxvision_widgets_draw_speedometer_common(menu_ay_registers_overlay_window,xorigen_linea,yorigen_linea,
                    porcentaje,color,color);    

                //Volumen B
                columna_texto += (longitud_linea*2+margen_horizontal)/menu_char_width;
                xorigen_linea=xorigen_linea+longitud_linea*2+margen_horizontal; //A la derecha del anterior
                //porcentaje=((ay_3_8912_registros[chip][9]&15)*100)/15;

                sprintf(sensor_name,"ay_vol_chip%d_chan_B",chip);
                porcentaje=sensor_get_percentaje_value(sensor_name);

                sprintf(buffer_texto_meter,"B[%d]",chip);
                color=ESTILO_GUI_COLOR_WAVEFORM;
                if (porcentaje>=85) color=ESTILO_GUI_COLOR_AVISO;                

                zxvision_print_string_defaults(menu_ay_registers_overlay_window,columna_texto,fila_texto,buffer_texto_meter);
                zxvision_widgets_erase_speedometer(menu_ay_registers_overlay_window,xorigen_linea,yorigen_linea);
                zxvision_widgets_draw_speedometer_common(menu_ay_registers_overlay_window,xorigen_linea,yorigen_linea,
                    porcentaje,color,color);              

                //Volumen C
                columna_texto += (longitud_linea*2+margen_horizontal)/menu_char_width;
                xorigen_linea=xorigen_linea+longitud_linea*2+margen_horizontal; //A la derecha del anterior
                //porcentaje=((ay_3_8912_registros[chip][10]&15)*100)/15;

                sprintf(sensor_name,"ay_vol_chip%d_chan_C",chip);
                porcentaje=sensor_get_percentaje_value(sensor_name);

                sprintf(buffer_texto_meter,"C[%d]",chip);
                color=ESTILO_GUI_COLOR_WAVEFORM;
                if (porcentaje>=85) color=ESTILO_GUI_COLOR_AVISO;                

                zxvision_print_string_defaults(menu_ay_registers_overlay_window,columna_texto,fila_texto,buffer_texto_meter);
                zxvision_widgets_erase_speedometer(menu_ay_registers_overlay_window,xorigen_linea,yorigen_linea);
                zxvision_widgets_draw_speedometer_common(menu_ay_registers_overlay_window,xorigen_linea,yorigen_linea,
                    porcentaje,color,color);                                          
            //}

	}

	}




	//Hacer decaer volumenes si multitarea off
                        //Decrementar volumenes que caen, pero hacerlo no siempre, sino 2 veces por segundo
            //esto hara ejecutar esto 2 veces por segundo
            if ( ((contador_segundo%500) == 0 && menu_ayregisters_valor_contador_segundo_anterior!=contador_segundo) || menu_multitarea==0) {

                                 menu_ayregisters_valor_contador_segundo_anterior=contador_segundo;
                                //printf ("Refrescando. contador_segundo=%d. chip: %d\n",contador_segundo,chip);

				for (chip=0;chip<total_chips;chip++) {

					ayregisters_previo_valor_volume_A[chip]=menu_decae_dec_valor_volumen(ayregisters_previo_valor_volume_A[chip],vol_A[chip]);
					ayregisters_previo_valor_volume_B[chip]=menu_decae_dec_valor_volumen(ayregisters_previo_valor_volume_B[chip],vol_B[chip]);
					ayregisters_previo_valor_volume_C[chip]=menu_decae_dec_valor_volumen(ayregisters_previo_valor_volume_C[chip],vol_C[chip]);


				}
				

				ayregisters_previo_valor_volume_noise=menu_decae_dec_valor_volumen(ayregisters_previo_valor_volume_noise,vol_noise);


        }


	zxvision_draw_window_contents(menu_ay_registers_overlay_window); 


}


//Ventana como variable global
zxvision_window zxvision_ay_registers_overlay;


void menu_ay_registers_crea_ventana(zxvision_window *ventana,int xventana,int yventana,int ancho_ventana,int alto_ventana,
    int is_minimized,int is_maximized,int ancho_antes_minimize,int alto_antes_minimize)
{
		//zxvision_new_window(ventana,xventana,yventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,"Audio Chip Registers");

        zxvision_new_window_gn_cim(ventana,xventana,yventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,"Audio Chip Registers",
            "ayregisters",is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);
		ventana->can_be_backgrounded=1;	
		//indicar nombre del grabado de geometria
		//strcpy(ventana->geometry_name,"ayregisters");
        //restaurar estado minimizado de ventana
        //ventana->is_minimized=is_minimized;
}

void menu_ay_registers(MENU_ITEM_PARAMETERS)
{
    menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();

		if (!menu_multitarea) {
			menu_warn_message("This window needs multitask enabled");
			return;
		}

		zxvision_window *ventana;
		ventana=&zxvision_ay_registers_overlay;		

    //IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
    //si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
    //la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
	zxvision_delete_window_if_exists(ventana);


    int total_chips=ay_retorna_numero_chips();
    if (total_chips>3) total_chips=3;

    int xventana,yventana,ancho_ventana,alto_ventana,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;

    if (!util_find_window_geometry("ayregisters",&xventana,&yventana,&ancho_ventana,&alto_ventana,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {

        if (total_chips==1) {
            yventana=5;
        }
        else {
            yventana=0;
        }

        xventana=menu_origin_x()+1;
        ancho_ventana=30;

        //El alto lo cambiamos segun el numero de chips
        if (total_chips==1) {
                alto_ventana=14;
        }
        else {
                alto_ventana=24;
        }					

    }


    //guardar tamanyo inicial para cuando se recrea la ventana indicarlo como tamanyo de antes minimizado
    //Ya NO hace falta esto, pues zxvision ya recrea la ventana al ampliarla
    //int ancho_ventana_inicial=ancho_ventana;
    //int alto_ventana_inicial=alto_ventana;




    //zxvision_new_window(ventana,xventana,yventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,"AY Registers");
    //ventana->can_be_backgrounded=1;	
    ////indicar nombre del grabado de geometria
    //strcpy(ventana->geometry_name,"ayregisters");

    //Para poder controlar redimensionamientos de ventana y recrearla de nuevo
    //No es necesario, pero es mas bonito... asi se recrea la ventana, si era muy pequeña, hacerla mas grande
    //garantiza que se podra leer todo el texto
    //int alto_anterior=alto_ventana;
    //int ancho_anterior=ancho_ventana;

    int alto_anterior;
    int ancho_anterior;		
    menu_ay_registers_crea_ventana(ventana,xventana,yventana,ancho_ventana,alto_ventana,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);

    zxvision_window_save_size(ventana,&ancho_anterior,&alto_anterior);

    zxvision_draw_window(ventana);		


    //Cambiamos funcion overlay de texto de menu
    //Se establece a la de funcion de onda + texto
    set_menu_overlay_function(menu_ay_registers_overlay);

    menu_ay_registers_overlay_window=ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui


	//Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
	//Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
	if (zxvision_currently_restoring_windows_on_start) {
		//printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
		return;
	}		


	z80_byte tecla;

	do {
		tecla=zxvision_common_getkey_refresh();		
		zxvision_handle_cursors_pgupdn(ventana,tecla);
		//printf ("tecla: %d\n",tecla);

		//Si ha cambiado el tamaño
        //Ya NO hace falta esto, pues zxvision ya recrea la ventana al ampliarla
        /*
		alto_ventana=ventana->visible_height;
		ancho_ventana=ventana->visible_width;
		xventana=ventana->x;
		yventana=ventana->y;
		if (alto_ventana!=alto_anterior || ancho_ventana!=ancho_anterior) {
			//printf ("recrear ventana ay registers\n");
			//Recrear ventana
            int is_minimized=ventana->is_minimized;

			zxvision_destroy_window(ventana);
			//alto_anterior=alto_ventana;
			//ancho_anterior=ancho_ventana;
			menu_ay_registers_crea_ventana(ventana,xventana,yventana,ancho_ventana,alto_ventana,is_minimized,ancho_antes_minimize,alto_antes_minimize);
			zxvision_window_save_size(ventana,&ancho_anterior,&alto_anterior);
            zxvision_draw_window(ventana);

            //Indicar tamanyo de antes minimizado, que es el que tenia al inicio
            //dado que se recrea la ventana siempre que cambia tamaño (y si se minimiza tambien),
            //queremos que se indique el tamaño que tenia antes de minimizar por si se deshace el minimizado
            //ventana->height_before_max_min_imize=alto_ventana_inicial;
            //ventana->width_before_max_min_imize=ancho_ventana_inicial;
            //printf ("despues ventana ay registers\n");
		}
        */


	} while (tecla!=2 && tecla!=3);				

	//Gestionar salir con tecla background
 
	menu_espera_no_tecla(); //Si no, se va al menu anterior.
	//En AY Piano por ejemplo esto no pasa aunque el estilo del menu es el mismo...

	//Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
	zxvision_set_window_overlay_from_current(ventana);	

    //restauramos modo normal de texto de menu
     set_menu_overlay_function(normal_overlay_texto_menu);


    cls_menu_overlay();	

	util_add_window_geometry_compact(ventana);	


	if (tecla==3) {
		zxvision_message_put_window_background();
	}

	else {
		
		zxvision_destroy_window(ventana);		
 	}
}





int menu_debug_tsconf_tbblue_msx_videoregisters_valor_contador_segundo_anterior;

zxvision_window *menu_debug_tsconf_tbblue_msx_videoregisters_overlay_window;

void menu_debug_tsconf_tbblue_msx_videoregisters_overlay(void)
{
	if (!zxvision_drawing_in_background) normal_overlay_texto_menu();

    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_debug_tsconf_tbblue_msx_videoregisters_overlay_window->is_minimized) return;

    //printf("overlay video info %d\n",contador_segundo);


	zxvision_window *ventana;

	ventana=menu_debug_tsconf_tbblue_msx_videoregisters_overlay_window;	

    //esto hara ejecutar esto 2 veces por segundo
    if ( ((contador_segundo%500) == 0 && menu_debug_tsconf_tbblue_msx_videoregisters_valor_contador_segundo_anterior!=contador_segundo) || menu_multitarea==0) {
        menu_debug_tsconf_tbblue_msx_videoregisters_valor_contador_segundo_anterior=contador_segundo;
        //printf ("Refrescando. contador_segundo=%d\n",contador_segundo);

        int linea=0;
        //int opcode;
        //int sumatotal;


        char texto_buffer[64];

        char texto_buffer2[64];

        //Empezar con espacio
        texto_buffer[0]=' ';				


        if (MACHINE_IS_TSCONF) {

            int vpage_addr=tsconf_get_vram_page()*16384;

            tsconf_get_current_video_mode(texto_buffer2);
            sprintf (texto_buffer,"Video mode: %s",texto_buffer2);
            //menu_escribe_linea_opcion(linea++,-1,1,texto_buffer);
            //zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

            //Con fillspc porque interesa borrar "restos" de modos de video anterior
            zxvision_print_string_defaults_fillspc(ventana,1,linea++,texto_buffer);

            //printf ("[%s] [%s]\n",texto_buffer,texto_buffer2);
            
            sprintf (texto_buffer,"Video addr: %06XH",vpage_addr);
            //menu_escribe_linea_opcion(linea++,-1,1,texto_buffer);
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

            sprintf (texto_buffer,"Tile Map Page: %06XH",tsconf_return_tilemappage() );
            //menu_escribe_linea_opcion(linea++,-1,1,texto_buffer);
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

            sprintf (texto_buffer,"Tile 0 Graphics addr: %06XH",tsconf_return_tilegraphicspage(0) );
            //menu_escribe_linea_opcion(linea++,-1,1,texto_buffer);
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

            sprintf (texto_buffer,"Tile 1 Graphics addr: %06XH",tsconf_return_tilegraphicspage(1) );
            //menu_escribe_linea_opcion(linea++,-1,1,texto_buffer);
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);


            sprintf (texto_buffer,"Sprite Graphics addr: %06XH",tsconf_return_spritesgraphicspage() );
            //menu_escribe_linea_opcion(linea++,-1,1,texto_buffer);
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

        }

        if (MACHINE_IS_TBBLUE) {

            //menu_escribe_linea_opcion(linea++,-1,1,"ULA Video mode:");		
            zxvision_print_string_defaults(ventana,1,linea++,"ULA Video mode:");

            //menu_escribe_linea_opcion(linea++,-1,1,get_spectrum_ula_string_video_mode() );
            zxvision_print_string_defaults(ventana,1,linea++,get_spectrum_ula_string_video_mode() );

            linea++;

            //menu_escribe_linea_opcion(linea++,-1,1,"Palette format:");
            //zxvision_print_string_defaults(&ventana,1,linea++,"Palette:");

            tbblue_get_string_palette_format(texto_buffer2);
            sprintf (texto_buffer,"Palette: %s",texto_buffer2);
            
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

            linea++;

            /*
            (R/W) 0x12 (18) => Layer 2 RAM page
bits 7-6 = Reserved, must be 0
bits 5-0 = SRAM page (point to page 8 after a Reset)

(R/W) 0x13 (19) => Layer 2 RAM shadow page
bits 7-6 = Reserved, must be 0
bits 5-0 = SRAM page (point to page 11 after a Reset)
            */

        //tbblue_get_offset_start_layer2_reg

            sprintf (texto_buffer,"Layer 2 mode:   %s",tbblue_get_layer2_mode_name() );
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

            sprintf (texto_buffer,"Layer 2 addr:        %06XH",tbblue_get_offset_start_layer2_reg(tbblue_registers[18]) );
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

            sprintf (texto_buffer,"Layer 2 shadow addr: %06XH",tbblue_get_offset_start_layer2_reg(tbblue_registers[19]) );					
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

            sprintf (texto_buffer,"Tilemap base addr:     %02X00H",0x40+tbblue_get_offset_start_tilemap() );					
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

            sprintf (texto_buffer,"Tile definitions addr: %02X00H",0x40+tbblue_get_offset_start_tiledef() );					
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);					

            sprintf (texto_buffer,"Tile width: %d columns",tbblue_get_tilemap_width() );					
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

            sprintf (texto_buffer,"Tile bpp: %d", (tbblue_tiles_are_monocrome() ? 1 : 4)  );
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);							

            /*
            z80_byte clip_windows[TBBLUE_CLIP_WINDOW_LAYER2][4];
z80_byte clip_windows[TBBLUE_CLIP_WINDOW_SPRITES][4];
z80_byte clip_windows[TBBLUE_CLIP_WINDOW_ULA][4];
z80_byte clip_windows[TBBLUE_CLIP_WINDOW_TILEMAP][4];
            */

            linea++;
            sprintf (texto_buffer,"Clip Windows:");
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

            sprintf (texto_buffer,"Layer2:  X=%3d-%3d Y=%3d-%3d",
            clip_windows[TBBLUE_CLIP_WINDOW_LAYER2][0],clip_windows[TBBLUE_CLIP_WINDOW_LAYER2][1],clip_windows[TBBLUE_CLIP_WINDOW_LAYER2][2],clip_windows[TBBLUE_CLIP_WINDOW_LAYER2][3]);
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);


            sprintf (texto_buffer,"Sprites: X=%3d-%3d Y=%3d-%3d",
            clip_windows[TBBLUE_CLIP_WINDOW_SPRITES][0],clip_windows[TBBLUE_CLIP_WINDOW_SPRITES][1],clip_windows[TBBLUE_CLIP_WINDOW_SPRITES][2],clip_windows[TBBLUE_CLIP_WINDOW_SPRITES][3]);
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);


            sprintf (texto_buffer,"ULA:     X=%3d-%3d Y=%3d-%3d",
            clip_windows[TBBLUE_CLIP_WINDOW_ULA][0],clip_windows[TBBLUE_CLIP_WINDOW_ULA][1],clip_windows[TBBLUE_CLIP_WINDOW_ULA][2],clip_windows[TBBLUE_CLIP_WINDOW_ULA][3]);
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);


            sprintf (texto_buffer,"Tilemap: X=%3d-%3d Y=%3d-%3d",
            clip_windows[TBBLUE_CLIP_WINDOW_TILEMAP][0]*2,clip_windows[TBBLUE_CLIP_WINDOW_TILEMAP][1]*2+1,clip_windows[TBBLUE_CLIP_WINDOW_TILEMAP][2],clip_windows[TBBLUE_CLIP_WINDOW_TILEMAP][3]);
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);



            linea++;
            sprintf (texto_buffer,"Offset Windows:");
            //menu_escribe_linea_opcion(linea++,-1,1,texto_buffer);	
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);


            int off_layer2_x=tbblue_registers[22] + (tbblue_registers[113]&1)*256;
            sprintf (texto_buffer,"Layer2:  X=%4d  Y=%3d",off_layer2_x,tbblue_registers[23]);
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);


            sprintf (texto_buffer,"LoRes:   X=%4d  Y=%3d",tbblue_registers[50],tbblue_registers[51]);
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);

            sprintf (texto_buffer,"ULA:     X=%4d  Y=%3d",tbblue_registers[38],tbblue_registers[39]);
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);


            //Offset X puede llegar hasta 1023. Por tanto 4 cifras. El resto X solo 3 cifras, pero los dejamos a 4 para que formato quede igual en pantalla
            sprintf (texto_buffer,"Tilemap: X=%4d  Y=%3d",tbblue_registers[48]+256*(tbblue_registers[47]&3),tbblue_registers[49]);
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);					

        }

        if (MACHINE_HAS_VDP_9918A) {

            sprintf (texto_buffer,"Video mode:%s",get_vdp_9918_string_video_mode() );
            zxvision_print_string_defaults_fillspc(ventana,1,linea++,texto_buffer);


            sprintf (texto_buffer,"Background Color: %2d",vdp_9918a_get_border_color());
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);		

            sprintf (texto_buffer,"Foreground Color: %2d",vdp_9918a_get_foreground_color());
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);						


            if (vdp_9918a_si_sms_video_mode4()) {
                sprintf (texto_buffer,"Sprite size: 8X%d",vdp_9918a_sms_get_sprite_height());
                zxvision_print_string_defaults_fillspc(ventana,1,linea++,texto_buffer);	
            }
            else {
                int sprite_size=vdp_9918a_get_sprite_size();
                sprintf (texto_buffer,"Sprite size: %dX%d",sprite_size,sprite_size);
                zxvision_print_string_defaults_fillspc(ventana,1,linea++,texto_buffer);		                        
            }

            sprintf (texto_buffer,"Magnification: %dX",vdp_9918a_get_sprite_double());
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);		

            sprintf (texto_buffer,"Name Table:           %04XH",vdp_9918a_get_pattern_name_table());
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);	

            sprintf (texto_buffer,"Color Table:          %04XH",vdp_9918a_get_pattern_color_table());
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);	

            sprintf (texto_buffer,"Pattern Generator:    %04XH",vdp_9918a_get_pattern_base_address());
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);						


            sprintf (texto_buffer,"Sprite Attr. Table:   %04XH",vdp_9918a_get_sprite_attribute_table());
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);		

            sprintf (texto_buffer,"Sprite Pattern Table: %04XH",vdp_9918a_get_sprite_pattern_table());
            zxvision_print_string_defaults(ventana,1,linea++,texto_buffer);		

            if (vdp_9918a_si_sms_video_mode4()) {
                sprintf (texto_buffer,"Scroll Horizontal:    %d",vdp_9918a_sms_get_scroll_horizontal());
                zxvision_print_string_defaults_fillspc(ventana,1,linea++,texto_buffer);	   

                sprintf (texto_buffer,"Scroll Vertical:      %d",vdp_9918a_sms_get_scroll_vertical());
                zxvision_print_string_defaults_fillspc(ventana,1,linea++,texto_buffer);	                                             
            }
                    				


        }

        if (MACHINE_IS_CPC) {
            z80_byte video_mode=cpc_gate_registers[2] &3;
            sprintf(texto_buffer,"Video mode: %d %s",video_mode,cpc_video_modes_strings[video_mode]);
            zxvision_print_string_defaults_fillspc(ventana,1,linea++,texto_buffer);

            sprintf(texto_buffer,"Full size:       %d X %d",
                cpc_crtc_get_total_horizontal(),cpc_crtc_get_total_vertical()
            );
            zxvision_print_string_defaults_fillspc(ventana,1,linea++,texto_buffer);

            sprintf(texto_buffer,"Pixel zone size: %d X %d",
                cpc_crtc_get_total_pixels_horizontal(),
                cpc_crtc_get_total_pixels_vertical()
            );
            zxvision_print_string_defaults_fillspc(ventana,1,linea++,texto_buffer);       

            //zxvision_print_string_defaults_fillspc(ventana,1,linea++,"Borders");    

            sprintf(texto_buffer,"Border Top:  %3d Bottom: %3d",
                cpc_crtc_get_top_border_height(),
                cpc_crtc_get_bottom_border_height()
            );
            zxvision_print_string_defaults_fillspc(ventana,1,linea++,texto_buffer);       

            sprintf(texto_buffer,"Border Left: %3d Right:  %3d",
                cpc_crtc_get_total_left_border(),
                cpc_crtc_get_total_right_border()
            );
            zxvision_print_string_defaults_fillspc(ventana,1,linea++,texto_buffer); 

            //zxvision_print_string_defaults_fillspc(ventana,1,linea++,"");      

            sprintf(texto_buffer,"Hsync width:     %d",cpc_crtc_get_total_hsync_width());
            zxvision_print_string_defaults_fillspc(ventana,1,linea++,texto_buffer);   

            sprintf(texto_buffer,"Vsync height:    %d",cpc_crtc_get_total_vsync_height_crtc());
            zxvision_print_string_defaults_fillspc(ventana,1,linea++,texto_buffer);   

        }


        zxvision_draw_window_contents(ventana);	
    }
}



zxvision_window menu_debug_tsconf_tbblue_msx_videoregisters_ventana;


void menu_debug_tsconf_tbblue_msx_videoregisters(MENU_ITEM_PARAMETERS)
{

	menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();

	zxvision_window *ventana;
		
	ventana=&menu_debug_tsconf_tbblue_msx_videoregisters_ventana;	

	//IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
	//si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
	//la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
	zxvision_delete_window_if_exists(ventana);		

	int xventana,yventana,ancho_ventana,alto_ventana,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;

	if (!util_find_window_geometry("videoinfo",&xventana,&yventana,&ancho_ventana,&alto_ventana,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {	

		ancho_ventana=32;
		xventana=menu_center_x()-ancho_ventana/2;

		if (MACHINE_IS_TBBLUE) {
			alto_ventana=24;
		}

		else if (MACHINE_HAS_VDP_9918A) {
			alto_ventana=12;
		}		

		else if (MACHINE_IS_CPC) {
			alto_ventana=9;
		}	        

		else {
			//yventana=7;
			alto_ventana=8;
		}

		yventana=menu_center_y()-alto_ventana/2;

	}



	//zxvision_new_window(ventana,xventana,yventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,"Video Info");

    zxvision_new_window_gn_cim(ventana,xventana,yventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,"Video Info",
        "videoinfo",is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);                        	

	ventana->can_be_backgrounded=1;	
	//indicar nombre del grabado de geometria
	//strcpy(ventana->geometry_name,"videoinfo");	
    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;    										

	zxvision_draw_window(ventana);


	menu_debug_tsconf_tbblue_msx_videoregisters_overlay_window=ventana;



	//Cambiamos funcion overlay de texto de menu
	//Se establece a la de funcion de onda + texto
	set_menu_overlay_function(menu_debug_tsconf_tbblue_msx_videoregisters_overlay);


    //Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
    //Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
    if (zxvision_currently_restoring_windows_on_start) {
        //printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
        return;
    }	

	z80_byte tecla;

	do {
		tecla=zxvision_common_getkey_refresh();		
		zxvision_handle_cursors_pgupdn(ventana,tecla);
		//printf ("tecla: %d\n",tecla);
	} while (tecla!=2 && tecla!=3);				

	//Gestionar salir con tecla background
 
	menu_espera_no_tecla(); //Si no, se va al menu anterior.
	//En AY Piano por ejemplo esto no pasa aunque el estilo del menu es el mismo...

	//Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
	zxvision_set_window_overlay_from_current(ventana);	

    //restauramos modo normal de texto de menu
	set_menu_overlay_function(normal_overlay_texto_menu);


    cls_menu_overlay();	
	util_add_window_geometry_compact(ventana);

	if (tecla==3) {
		zxvision_message_put_window_background();
	}

	else {	


		zxvision_destroy_window(ventana);

	}

}


#define TSCONF_SPRITENAV_WINDOW_ANCHO 32
#define TSCONF_SPRITENAV_WINDOW_ALTO 20
#define TSCONF_SPRITENAV_WINDOW_X (menu_center_x()-TSCONF_SPRITENAV_WINDOW_ANCHO/2 )
#define TSCONF_SPRITENAV_WINDOW_Y (menu_center_y()-TSCONF_SPRITENAV_WINDOW_ALTO/2)




//int menu_debug_tsconf_tbblue_msx_spritenav_current_palette=0;
int menu_debug_tsconf_tbblue_msx_spritenav_current_sprite=0;


zxvision_window *menu_debug_tsconf_tbblue_msx_spritenav_draw_sprites_window;

int menu_debug_tsconf_tbblue_msx_spritenav_get_total_sprites(void)
{
	int limite;

	limite=TSCONF_MAX_SPRITES; //85 sprites max

	if (MACHINE_IS_TBBLUE) limite=TBBLUE_MAX_SPRITES;
	else if (MACHINE_HAS_VDP_9918A) {
        if (vdp_9918a_si_sms_video_mode4() ) {
            limite=VDP_9918A_SMS_MODE4_MAX_SPRITES;
        }
        else limite=VDP_9918A_MAX_SPRITES;
    }

	return limite;
}

z80_bit menu_debug_spritenav_raw={0};

int menu_debug_tsconf_tbblue_msx_spritenav_get_total_height_win(void)
{

	//menu_debug_spritenav_raw.v
	
	int multiplicador;


	if (MACHINE_IS_TSCONF) multiplicador=2; 
	
	
	else if (MACHINE_HAS_VDP_9918A) multiplicador=2; 
	
	
	else multiplicador=3;
	
	
	if (menu_debug_spritenav_raw.v) multiplicador=1;
	
//+1 por la linea de leyenda
	return menu_debug_tsconf_tbblue_msx_spritenav_get_total_sprites()*multiplicador+1;

}




//Muestra lista de sprites
void menu_debug_tsconf_tbblue_msx_spritenav_lista_sprites(void)
{

	char dumpmemoria[64];

	int linea_color;
	int limite;

	int linea=0;


	limite=menu_debug_tsconf_tbblue_msx_spritenav_get_total_sprites();

	//z80_byte tbsprite_sprites[TBBLUE_MAX_SPRITES][4];
	/*
	1st: X position (bits 7-0).
2nd: Y position (0-255).
3rd: bits 7-4 is palette offset, bit 3 is X mirror, bit 2 is Y mirror, bit 1 is the rotate flag and bit 0 is X MSB.
4th: bit 7 is the visible flag, bit 6 is reserved, bits 5-0 is Name (pattern index, 0-63).
*/

	int current_sprite;
	
	
    //Forzar a mostrar atajos
    z80_bit antes_menu_writing_inverse_color;
    antes_menu_writing_inverse_color.v=menu_writing_inverse_color.v;
    menu_writing_inverse_color.v=1;		

    sprintf(dumpmemoria,"[%c] ~~Raw mode list",(menu_debug_spritenav_raw.v ? 'X' : ' '));
 zxvision_print_string_defaults(menu_debug_tsconf_tbblue_msx_spritenav_draw_sprites_window,1,linea++,dumpmemoria);	

    //Restaurar comportamiento atajos
    menu_writing_inverse_color.v=antes_menu_writing_inverse_color.v; 
	
	


		for (linea_color=0;linea_color<limite;linea_color++) {					

			current_sprite=menu_debug_tsconf_tbblue_msx_spritenav_current_sprite+linea_color;

			if (MACHINE_IS_TSCONF) {

				int offset=current_sprite*6;
				
				if (menu_debug_spritenav_raw.v) {
				
				int indice_string;
				
				sprintf (dumpmemoria,"%03d ",current_sprite);
				
				indice_string=4;
				
				int i;
				
				for (i=0;i<6;i++) {
				  sprintf(&dumpmemoria[indice_string],"%02X ",tsconf_fmaps[0x200+offset+i]);
				  indice_string +=3;
				}
				
				zxvision_print_string_defaults_fillspc(menu_debug_tsconf_tbblue_msx_spritenav_draw_sprites_window,1,linea++,dumpmemoria);	
				
				}
				
				else {
				
				
				z80_byte sprite_r0h=tsconf_fmaps[0x200+offset+1];

				z80_byte sprite_leap=sprite_r0h&64;

				int sprite_act=sprite_r0h&32;
				int y=tsconf_fmaps[0x200+offset]+256*(sprite_r0h&1);
				z80_byte ysize=8*(1+((sprite_r0h>>1)&7));
					

				z80_byte sprite_r1h=tsconf_fmaps[0x200+offset+3];
				int x=tsconf_fmaps[0x200+offset+2]+256*(sprite_r1h&1);
				z80_byte xsize=8*(1+((sprite_r1h>>1)&7));

				z80_byte sprite_r2h=tsconf_fmaps[0x200+offset+5];
				z80_int tnum=(tsconf_fmaps[0x200+offset+4])+256*(sprite_r2h&15);
						//Tile Number for upper left corner. Bits 0-5 are X Position in Graphics Bitmap, bits 6-11 - Y Position.
				z80_int tnum_x=tnum & 63;
				z80_int tnum_y=(tnum>>6)&63;

				z80_byte spal=(sprite_r2h>>4)&15;

				z80_byte sprite_xf=sprite_r1h&128;
				z80_byte sprite_yf=sprite_r0h&128;

				sprintf (dumpmemoria,"%02d X: %3d Y: %3d (%2dX%2d)",current_sprite,x,y,xsize,ysize);
				//menu_escribe_linea_opcion(linea++,-1,1,dumpmemoria);
				zxvision_print_string_defaults(menu_debug_tsconf_tbblue_msx_spritenav_draw_sprites_window,1,linea++,dumpmemoria);

				sprintf (dumpmemoria,"Tile:%2d,%2d %s %s %s %s P:%2d",tnum_x,tnum_y,
					(sprite_act ? "ACT" : "   "),(sprite_leap ? "LEAP": "    "),
					(sprite_xf ? "XF" : "  "),(sprite_yf ? "YF": "  "),
					spal );

				//menu_escribe_linea_opcion(linea++,-1,1,dumpmemoria);
				zxvision_print_string_defaults(menu_debug_tsconf_tbblue_msx_spritenav_draw_sprites_window,1,linea++,dumpmemoria);
				
				}
			}

			if (MACHINE_IS_TBBLUE) {
			
				if (menu_debug_spritenav_raw.v) {
				
				int indice_string;
				
				sprintf (dumpmemoria,"%03d ",current_sprite);
				
				indice_string=4;
				
				int i;
				
				for (i=0;i<TBBLUE_SPRITE_ATTRIBUTE_SIZE;i++) {
				  sprintf(&dumpmemoria[indice_string],"%02X ",tbsprite_new_sprites[current_sprite][i]);
				  indice_string +=3;
				}
				
				zxvision_print_string_defaults_fillspc(menu_debug_tsconf_tbblue_msx_spritenav_draw_sprites_window,1,linea++,dumpmemoria);	
				
				}
				
				else {
			
			
					//z80_byte tbsprite_sprites[TBBLUE_MAX_SPRITES][4];
	/*
	1st: X position (bits 7-0).
2nd: Y position (0-255).
3rd: bits 7-4 is palette offset, bit 3 is X mirror, bit 2 is Y mirror, bit 1 is the rotate flag and bit 0 is X MSB.
4th: bit 7 is the visible flag, bit 6 is reserved, bits 5-0 is Name (pattern index, 0-63).
*/

                //NOTA: puede que todas las caracteristicas de los sprites no esten reflejadas correctamente aqui


				z80_int x=tbsprite_new_sprites[current_sprite][0]; //
				z80_byte y=tbsprite_new_sprites[current_sprite][1];  //

				z80_byte byte_3=tbsprite_new_sprites[current_sprite][2];
				z80_byte paloff=byte_3 & 0xF0; //
				z80_byte mirror_x=byte_3 & 8; //
				z80_byte mirror_y=byte_3 & 4; //
				z80_byte rotate=byte_3 & 2; //
				z80_byte msb_x=byte_3 &1; //

				x +=msb_x*256;

				z80_byte byte_4=tbsprite_new_sprites[current_sprite][3];
				z80_byte byte_5=tbsprite_new_sprites[current_sprite][4];
				z80_byte visible=byte_4 & 128; //
				z80_byte pattern=byte_4 & 63; //

				int sprite_es_4bpp=0;
				int offset_4bpp_N6=0;
                //int sprite_es_relative=0; 

                //int sprite_es_relative_composite=0; 
                //int sprite_es_relative_unified=0;

				char buf_subindex_4_bit[10];

                char buf_relative_type[4]; //CMP (composite), UNI (unified)

                strcpy(buf_relative_type,"   ");

				int zoom_x=1;
				int zoom_y=1;

                if ((byte_4 & 64)==0) {
                    //Pattern de 4 bytes. Se comporta como uno de 5 bytes con ultimo byte a 0
                    byte_5=0;
                }

				
                //Byte 5
                //H N6 T X X Y Y Y8
                //{H,N6}  {0,1} -> relative sprite.

                if (byte_5 & 128) sprite_es_4bpp=1;
                if (byte_5 & 64) offset_4bpp_N6=1;

                if ((byte_5 & (128+64)) == 64) {
                    //sprite relative
                    //sprite_es_relative=1;
                    strcpy(buf_relative_type,"REL");
                }
                else {
                    //sprite es anchor
                    //H N6 T X X Y Y Y8
                    //T = 0 if relative sprites are composite type else 1 for unified type        
                    //El tipo de sprite relativo (unified o composite) se define en el anchor,
                    //no en los bits del sprite relativo                
                    if (byte_5 & 32) {
                        //sprite_es_relative_unified=1;
                        strcpy(buf_relative_type,"UNI");
                    }
                    else {
                        //sprite_es_relative_composite=1;
                        strcpy(buf_relative_type,"CMP");
                    }                        

                }

                z80_byte zoom_x_value=(byte_5>>3)&3;
                if (zoom_x_value) zoom_x <<=zoom_x_value;

                z80_byte zoom_y_value=(byte_5>>1)&3;
                if (zoom_y_value) zoom_y <<=zoom_y_value;


                //TODO: Y8

				

				if (sprite_es_4bpp) {
					sprintf(buf_subindex_4_bit,":%d",offset_4bpp_N6);
				}	
				else {
					strcpy(buf_subindex_4_bit,"  ");
				}			
								//012345678901234567890123456789012
								//123:1 X: 123 Y: 123 MIRX MIRY ROT
				sprintf (dumpmemoria,"%03d%s X: %3d Y: %3d %s %s %s",current_sprite,buf_subindex_4_bit,x,y,
						(mirror_x ? "MX" : "  "),(mirror_y ? "MY" : "  "),(rotate ? "ROT" : "   ")
				);				
				zxvision_print_string_defaults_fillspc(menu_debug_tsconf_tbblue_msx_spritenav_draw_sprites_window,1,linea++,dumpmemoria);


				sprintf (dumpmemoria," Pattn: %2d Palof: %3d Vis: %s"
					,pattern,paloff, (visible ? "Yes" : "No ") );
				zxvision_print_string_defaults_fillspc(menu_debug_tsconf_tbblue_msx_spritenav_draw_sprites_window,1,linea++,dumpmemoria);


				sprintf(dumpmemoria," %dbpp %s ZX: %d ZY: %d",(sprite_es_4bpp ? 4 : 8) ,
                //(sprite_es_relative ? buf_relative_type : "   "),
                buf_relative_type,
                zoom_x,zoom_y);
				zxvision_print_string_defaults_fillspc(menu_debug_tsconf_tbblue_msx_spritenav_draw_sprites_window,1,linea++,dumpmemoria);				

				}
				
			}

			if (MACHINE_HAS_VDP_9918A) {
				z80_int sprite_attribute_table=vdp_9918a_get_sprite_attribute_table();
                z80_int orig_sprite_attribute_table=sprite_attribute_table;


				int offset_sprite=current_sprite*4;


				sprite_attribute_table +=offset_sprite; 


				z80_byte (*vram_read_function_pointer)(z80_int address);


				if (MACHINE_IS_COLECO) vram_read_function_pointer=coleco_read_vram_byte;
				else if (MACHINE_IS_SG1000) vram_read_function_pointer=sg1000_read_vram_byte;
                else if (MACHINE_IS_SMS) vram_read_function_pointer=sms_read_vram_byte;
				else if (MACHINE_IS_SVI) vram_read_function_pointer=svi_read_vram_byte;
				else vram_read_function_pointer=msx_read_vram_byte;
								
				z80_byte vert_pos;
				z80_byte horiz_pos;
				z80_byte sprite_name;
				z80_byte attr_color_etc;

                if (vdp_9918a_si_sms_video_mode4() ) {
                    vert_pos=vram_read_function_pointer(orig_sprite_attribute_table+current_sprite);
                    horiz_pos=vram_read_function_pointer(orig_sprite_attribute_table+0x80+current_sprite*2);
                    sprite_name=vram_read_function_pointer(orig_sprite_attribute_table+0x80+current_sprite*2+1);
                }
                else {
				    vert_pos=vram_read_function_pointer(sprite_attribute_table);
				    horiz_pos=vram_read_function_pointer(sprite_attribute_table+1);
				    sprite_name=vram_read_function_pointer(sprite_attribute_table+2);
				    attr_color_etc=vram_read_function_pointer(sprite_attribute_table+3);
                }

				vert_pos++;
				
				if (menu_debug_spritenav_raw.v) {
				
                    if (vdp_9918a_si_sms_video_mode4() ) {
                        sprintf (dumpmemoria,"%03d %02X %02X %02X",current_sprite,vert_pos,horiz_pos,sprite_name);
                    }

                    else  {
				
				        sprintf (dumpmemoria,"%03d %02X %02X %02X %02X",current_sprite,vert_pos,horiz_pos,sprite_name,attr_color_etc);
                    }
				
				
				
				}
				
				else {
				

                    sprintf (dumpmemoria,"%02d X: %3d Y: %3d",
                        current_sprite,horiz_pos,vert_pos);

                    zxvision_print_string_defaults_fillspc(menu_debug_tsconf_tbblue_msx_spritenav_draw_sprites_window,1,linea++,dumpmemoria);


                    if (vdp_9918a_si_sms_video_mode4() ) {
                        sprintf (dumpmemoria," Name: %3d",sprite_name);
                    }
                    else {

                        sprintf (dumpmemoria," Name: %3d Color: %02d EC: %d",
                            sprite_name,attr_color_etc & 15,(attr_color_etc>>7) & 1);
                    }
                        
					
				}
				
				zxvision_print_string_defaults_fillspc(menu_debug_tsconf_tbblue_msx_spritenav_draw_sprites_window,1,linea++,dumpmemoria);

				
			}			
	
					
		}

	zxvision_draw_window_contents(menu_debug_tsconf_tbblue_msx_spritenav_draw_sprites_window); 


}

void menu_debug_tsconf_tbblue_msx_spritenav_draw_sprites(void)
{


    menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech
    if (!zxvision_drawing_in_background) normal_overlay_texto_menu();

    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_debug_tsconf_tbblue_msx_spritenav_draw_sprites_window->is_minimized) return;

    //printf("overlay sprites %d\n",contador_segundo);

    menu_debug_tsconf_tbblue_msx_spritenav_lista_sprites();



}

zxvision_window zxvision_window_tsconf_tbblue_spritenav;


void menu_debug_spritenav_new_window(zxvision_window *ventana)
{
    int xventana,yventana,ancho_ventana,alto_ventana,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;

	if (!util_find_window_geometry("tsconftbbluespritenav",&xventana,&yventana,&ancho_ventana,&alto_ventana,
            &is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
		xventana=TSCONF_SPRITENAV_WINDOW_X;
		yventana=TSCONF_SPRITENAV_WINDOW_Y;
		ancho_ventana=TSCONF_SPRITENAV_WINDOW_ANCHO;
		alto_ventana=TSCONF_SPRITENAV_WINDOW_ALTO;
	}


	//zxvision_new_window(ventana,xventana,yventana,ancho_ventana,alto_ventana,
	//						TSCONF_SPRITENAV_WINDOW_ANCHO-1,menu_debug_tsconf_tbblue_msx_spritenav_get_total_height_win(),"Sprite navigator");

    zxvision_new_window_gn_cim(ventana,xventana,yventana,ancho_ventana,alto_ventana,
							TSCONF_SPRITENAV_WINDOW_ANCHO-1,menu_debug_tsconf_tbblue_msx_spritenav_get_total_height_win(),"Sprite navigator",
                            "tsconftbbluespritenav",is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);                            

	ventana->can_be_backgrounded=1;
	ventana->upper_margin=1;
	//indicar nombre del grabado de geometria
	//strcpy(ventana->geometry_name,"tsconftbbluespritenav");
    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;    

	zxvision_draw_window(ventana);	
}



void menu_debug_spritenav_save_geometry(zxvision_window *ventana)
{

	util_add_window_geometry_compact(ventana);
}

void menu_debug_tsconf_tbblue_msx_spritenav(MENU_ITEM_PARAMETERS)
{
	menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();

	
	//zxvision_window ventana;
    zxvision_window *ventana;
    ventana=&zxvision_window_tsconf_tbblue_spritenav;	

	//IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
	//si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
	//la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
	zxvision_delete_window_if_exists(ventana);	

	menu_debug_spritenav_new_window(ventana);	

    set_menu_overlay_function(menu_debug_tsconf_tbblue_msx_spritenav_draw_sprites);

	menu_debug_tsconf_tbblue_msx_spritenav_draw_sprites_window=ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui


       //Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
       //Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
       if (zxvision_currently_restoring_windows_on_start) {
               //printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
               return;
       }	


	z80_byte tecla;

		//Si no esta multitarea, hacer un refresco inicial para que aparezca el contenido de la ventana sin tener que pulsar una tecla
		//dado que luego funciona como overlay, el overlay se aplica despues de hacer el render
		//esto solo es necesario para ventanas que usan overlay
	    if (!menu_multitarea) {
			//printf ("refresca pantalla inicial\n");
			menu_refresca_pantalla();
		}			

	
    do {
    	menu_speech_tecla_pulsada=0; //Que envie a speech
   		tecla=zxvision_common_getkey_refresh();
		zxvision_handle_cursors_pgupdn(ventana,tecla);
		
		 if (tecla=='r') {
		 	menu_debug_spritenav_save_geometry(ventana);
		 	zxvision_destroy_window(ventana);
		 	menu_debug_spritenav_raw.v ^=1;
		 	menu_debug_spritenav_new_window(ventana);
        }     
	} while (tecla!=2 && tecla!=3);  

	//Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
	zxvision_set_window_overlay_from_current(ventana);	

	//restauramos modo normal de texto de menu
    set_menu_overlay_function(normal_overlay_texto_menu);		

    cls_menu_overlay();
    
    menu_debug_spritenav_save_geometry(ventana);


	if (tecla==3) {
		zxvision_message_put_window_background();
	}

	else {

		zxvision_destroy_window(ventana);
	}

}




#define TSCONF_TILENAV_WINDOW_ANCHO 32
#define TSCONF_TILENAV_WINDOW_ALTO 24
#define TSCONF_TILENAV_WINDOW_X (menu_center_x()-TSCONF_TILENAV_WINDOW_ANCHO/2 )
#define TSCONF_TILENAV_WINDOW_Y (menu_center_y()-TSCONF_TILENAV_WINDOW_ALTO/2)
#define TSCONF_TILENAV_TILES_VERT_PER_WINDOW 64
#define TSCONF_TILENAV_TILES_HORIZ_PER_WINDOW 64





int menu_debug_tsconf_tbblue_msx_tilenav_current_tilelayer=0;

z80_bit menu_debug_tsconf_tbblue_msx_tilenav_showmap={0};

zxvision_window *menu_debug_tsconf_tbblue_msx_tilenav_lista_tiles_window;


#define DEBUG_TSCONF_TILENAV_MAX_TILES (64*64)
//#define DEBUG_TBBLUE_TILENAV_MAX_TILES_8032 (80*32)
//#define DEBUG_TBBLUE_TILENAV_MAX_TILES_4032 (40*32)


char menu_debug_tsconf_tbblue_msx_tiles_retorna_visualchar(int tnum)
{
	//Hacer un conjunto de 64 caracteres. Mismo set de caracteres que para Base64. Por que? Por que si :)
			   //0123456789012345678901234567890123456789012345678901234567890123
	char *caracter_list="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	int index=tnum % 64;
	return caracter_list[index];
}

int menu_debug_tsconf_tbblue_msx_tilenav_total_vert(void)
{

	int limite_vertical;

	if (MACHINE_IS_TSCONF) {
		limite_vertical=DEBUG_TSCONF_TILENAV_MAX_TILES;
		if (menu_debug_tsconf_tbblue_msx_tilenav_showmap.v) limite_vertical=TSCONF_TILENAV_TILES_VERT_PER_WINDOW;	
	}

	else if (MACHINE_HAS_VDP_9918A) { 
		limite_vertical=vdp_9918a_get_tile_heigth()*vdp_9918a_get_tile_width();

		if (menu_debug_tsconf_tbblue_msx_tilenav_showmap.v) limite_vertical=vdp_9918a_get_tile_heigth();	
	}	

	else  { //TBBLUE
		limite_vertical=tbblue_get_tilemap_width()*32;

		if (menu_debug_tsconf_tbblue_msx_tilenav_showmap.v) limite_vertical=32;	
	}

	return limite_vertical;
}

//Muestra lista de tiles
void menu_debug_tsconf_tbblue_msx_tilenav_lista_tiles(void)
{

	//Suficientemente grande para almacenar regla superior en modo visual
	//80 + 3 espacios izquierda + 0 final	
#define DEBUG_TILENAV_TEXTO_LINEA 84
	char dumpmemoria[DEBUG_TILENAV_TEXTO_LINEA]; 

	
	//int limite;

	int linea=0;
	//limite=DEBUG_TSCONF_TILENAV_MAX_TILES;

	int current_tile;

	z80_byte *puntero_tilemap;
	z80_byte *puntero_tilemap_orig;

	z80_int msx_pattern_name_table; 

	if (MACHINE_IS_TSCONF) {
		puntero_tilemap=tsconf_ram_mem_table[0]+tsconf_return_tilemappage();
	}

	else if (MACHINE_HAS_VDP_9918A) {
		msx_pattern_name_table=vdp_9918a_get_pattern_name_table();
		puntero_tilemap=NULL; //no se usa, pero para evitar warnings del compilador
	}	

	else {  //TBBLUE
		//puntero_tilemap=tbblue_ram_mem_table[5]+tbblue_get_offset_start_tilemap();
			//Siempre saldra de ram 5
		puntero_tilemap=tbblue_ram_memory_pages[5*2]+(256*tbblue_get_offset_start_tilemap());	
		//printf ("%XH\n",tbblue_get_offset_start_tilemap() );

	}

	z80_byte tbblue_tilemap_control;
	int tilemap_width;


	int tbblue_bytes_per_tile=2;

	if (MACHINE_IS_TBBLUE) {
					/*
					(R/W) 0x6B (107) => Tilemap Control
  bit 7    = 1 to enable the tilemap
  bit 6    = 0 for 40x32, 1 for 80x32
  bit 5    = 1 to eliminate the attribute entry in the tilemap
  bit 4    = palette select
  bits 3-0 = Reserved set to 0
					*/
					tbblue_tilemap_control=tbblue_registers[107];

					if (tbblue_tilemap_control&32) tbblue_bytes_per_tile=1;

					tilemap_width=tbblue_get_tilemap_width();

	}

	if (MACHINE_HAS_VDP_9918A) {
		tilemap_width=vdp_9918a_get_tile_width();
	}

	puntero_tilemap_orig=puntero_tilemap;

	int limite_vertical=menu_debug_tsconf_tbblue_msx_tilenav_total_vert();


	int offset_vertical=0;

	if (menu_debug_tsconf_tbblue_msx_tilenav_showmap.v) {
		if (MACHINE_IS_TSCONF) {
				  //0123456789012345678901234567890123456789012345678901234567890123
		strcpy(dumpmemoria,"   0    5    10   15   20   25   30   35   40   45   50   55   60  ");
		}

		else if (MACHINE_HAS_VDP_9918A) {
			if (tilemap_width==32) {
				  			 //01234567890123456789012345678901
		strcpy(dumpmemoria,"   0    5    10   15   20   25   30        ");
			}
			else {
				  			 //0123456789012345678901234567890123456789012345678901234567890123
		strcpy(dumpmemoria,"   0    5    10   15   20   25   30   35   ");
			}
		}		

		else { //TBBLUE
			if (tilemap_width==40) {
				             //0123456789012345678901234567890123456789012345678901234567890123
		strcpy(dumpmemoria,"   0    5    10   15   20   25   30   35                                           ");
			}
			else {
				             //01234567890123456789012345678901234567890123456789012345678901234567890123456789
		strcpy(dumpmemoria,"   0    5    10   15   20   25   30   35   40   45   50   55   60   65   70   75   ");
			}

		}

		//Indicar codigo 0 de final
		//dumpmemoria[current_tile_x+TSCONF_TILENAV_TILES_HORIZ_PER_WINDOW+3]=0;  //3 espacios al inicio

		//menu_escribe_linea_opcion(linea++,-1,1,&dumpmemoria[current_tile_x]); //Mostrar regla superior
		zxvision_print_string_defaults(menu_debug_tsconf_tbblue_msx_tilenav_lista_tiles_window,1,0,dumpmemoria);
	}
	else {
		//Aumentarlo en cuanto al offset que estamos (si modo lista)

		int offset_y=menu_debug_tsconf_tbblue_msx_tilenav_lista_tiles_window->offset_y;
		

		offset_vertical=offset_y/2;
		linea=offset_vertical*2;

        int ventana_alto_visible=menu_debug_tsconf_tbblue_msx_tilenav_lista_tiles_window->visible_height;

        int lineas_en_ventana=((ventana_alto_visible-2)/2)+1; //El maximo que cabe en pantalla, +1 para cuando se baja 1 posicion con cursor

		limite_vertical=offset_vertical+lineas_en_ventana;

	}

	//linea destino es +3, pues las tres primeras son de leyenda
	linea +=3;	



		for (;offset_vertical<limite_vertical;offset_vertical++) {

				//texto linea inicializarlo siempre con espacios
				//#define DEBUG_TILENAV_TEXTO_LINEA 84
				//char dumpmemoria[DEBUG_TILENAV_TEXTO_LINEA]; 
				int i;
				for (i=0;i<DEBUG_TILENAV_TEXTO_LINEA-1;i++) {
					dumpmemoria[i]=' ';
				}

				//Y 0 del final
				dumpmemoria[i]=0;			

			int repetir_ancho=1;
			int mapa_tile_x=3;
			if (menu_debug_tsconf_tbblue_msx_tilenav_showmap.v==0) {
				//Modo lista tiles
				current_tile=offset_vertical;
			}

			else {
				//Modo mapa tiles
				if (MACHINE_IS_TSCONF) {
					current_tile=offset_vertical*64;
					repetir_ancho=TSCONF_TILENAV_TILES_HORIZ_PER_WINDOW;

					//poner regla vertical
					int linea_tile=current_tile/64;
					if ( (linea_tile%5)==0) sprintf (dumpmemoria,"%2d ",linea_tile);
					else sprintf (dumpmemoria,"   ");
				}

				else if (MACHINE_HAS_VDP_9918A) {
					current_tile=offset_vertical*tilemap_width;
					repetir_ancho=tilemap_width;

					//poner regla vertical
					int linea_tile=current_tile/tilemap_width;
					if ( (linea_tile%5)==0) sprintf (dumpmemoria,"%2d ",linea_tile);
					else sprintf (dumpmemoria,"   ");
				}				

				else { //TBBLUE
					current_tile=offset_vertical*tilemap_width;
					repetir_ancho=tilemap_width;

					//poner regla vertical
					int linea_tile=current_tile/tilemap_width;
					if ( (linea_tile%5)==0) sprintf (dumpmemoria,"%2d ",linea_tile);
					else sprintf (dumpmemoria,"   ");				
				}
			}

			//printf ("linea: %3d current tile: %10d puntero: %10d\n",linea_color,current_tile,puntero_tilemap-tsconf_ram_mem_table[0]-tsconf_return_tilemappage()	);

			do {



				if (MACHINE_IS_TSCONF) {
					int y=current_tile/64;
					int x=current_tile%64; 

					//printf ("x: %d y: %d\n",x,y);
				

					int offset=(256*y)+(x*2);

					offset+=menu_debug_tsconf_tbblue_msx_tilenav_current_tilelayer*128;

					int tnum=puntero_tilemap[offset]+256*(puntero_tilemap[offset+1]&0xF);

					//printf ("Current tile: %d  x: %d y: %d  tnum: %d\n",current_tile,x,y,tnum);

					z80_byte tnum_x=tnum&63;
					z80_byte tnum_y=(tnum>>6)&63;

		    		z80_byte tpal=(puntero_tilemap[offset+1]>>4)&3;

					z80_byte tile_xf=puntero_tilemap[offset+1]&64;
					z80_byte tile_yf=puntero_tilemap[offset+1]&128;

					if (menu_debug_tsconf_tbblue_msx_tilenav_showmap.v==0) {
						//Modo lista tiles
						sprintf (dumpmemoria,"X: %3d Y: %3d                   ",x,y);

						zxvision_print_string_defaults(menu_debug_tsconf_tbblue_msx_tilenav_lista_tiles_window,1,linea++,dumpmemoria);

						sprintf (dumpmemoria," Tile: %2d,%2d %s %s P:%2d",tnum_x,tnum_y,
							(tile_xf ? "XF" : "  "),(tile_yf ? "YF": "  "),
							tpal );

						zxvision_print_string_defaults(menu_debug_tsconf_tbblue_msx_tilenav_lista_tiles_window,1,linea++,dumpmemoria);
					}
					else {
						//Modo mapa tiles
						z80_byte caracter_final;

						if (tnum==0) {
							caracter_final=' '; 
						}
						else {
							caracter_final=menu_debug_tsconf_tbblue_msx_tiles_retorna_visualchar(tnum);
						}

						dumpmemoria[mapa_tile_x++]=caracter_final;
					}
				}

				if (MACHINE_HAS_VDP_9918A) {
					int y=current_tile/tilemap_width;
					int x=current_tile%tilemap_width; 	

					int tnum;	

                    int sms_mirror_x;

                    int sms_mirror_y;

                    int sms_palette_offset;
                    
                    int sms_priority_tile_bit;


					if (MACHINE_IS_COLECO) {
						tnum=coleco_read_vram_byte(msx_pattern_name_table+current_tile);	
					}	

					else if (MACHINE_IS_SG1000) {
						tnum=sg1000_read_vram_byte(msx_pattern_name_table+current_tile);	
					}	

					else if (MACHINE_IS_SMS) {
                        if (vdp_9918a_si_sms_video_mode4()) {
                            int offset_tile=current_tile*2;

                            z80_int pattern_word=sms_read_vram_byte(msx_pattern_name_table+offset_tile)+256*sms_read_vram_byte(msx_pattern_name_table+offset_tile+1);

                            tnum=pattern_word & 511;

                            sms_mirror_x=(pattern_word & 0x0200);

                            sms_mirror_y=(pattern_word & 0x0400);

                            sms_palette_offset=(pattern_word & 0x0800 ? 16 : 0);
                            
                            sms_priority_tile_bit=(pattern_word & 0x1000);                            
                        }
						else tnum=sms_read_vram_byte(msx_pattern_name_table+current_tile);	
					}	                    

					else if (MACHINE_IS_SVI) {
						tnum=svi_read_vram_byte(msx_pattern_name_table+current_tile);	
					}						

					else {
						tnum=msx_read_vram_byte(msx_pattern_name_table+current_tile);	
					}
				

					if (menu_debug_tsconf_tbblue_msx_tilenav_showmap.v==0) {
						//Modo lista tiles
						sprintf (dumpmemoria,"X: %3d Y: %3d                   ",x,y);

						zxvision_print_string_defaults(menu_debug_tsconf_tbblue_msx_tilenav_lista_tiles_window,1,linea++,dumpmemoria);

                        if (vdp_9918a_si_sms_video_mode4()) {
                            sprintf (dumpmemoria," Tile: %3d %s %s %s Off: %2d",tnum,
                                    (sms_mirror_x ? "MX" : "  "),
                                    (sms_mirror_y ? "MY" : "  "),
                                    (sms_priority_tile_bit ? "PRI" : "   "),
                                    sms_palette_offset
                            );
                        }
                        else {
						    sprintf (dumpmemoria," Tile: %3d %c",tnum,(tnum>=33 && tnum<=126 ? tnum : ' ' ));
                        }

						zxvision_print_string_defaults(menu_debug_tsconf_tbblue_msx_tilenav_lista_tiles_window,1,linea++,dumpmemoria);						

					}
					else {
						//Modo mapa tiles
						int caracter_final;

						if (tnum==0) {
							caracter_final=' '; 
						}
						else {

							//Si caracter imprimible, mostramos. Si no, mostrar set alternativo
							if (tnum>=32 && tnum<=126) {
								caracter_final=tnum;
							}
							else {
								caracter_final=menu_debug_tsconf_tbblue_msx_tiles_retorna_visualchar(tnum);
							}
						}

						dumpmemoria[mapa_tile_x++]=caracter_final;
					}					

				}

				if (MACHINE_IS_TBBLUE) {

					int y=current_tile/tilemap_width;
					int x=current_tile%tilemap_width; 

					int offset=(tilemap_width*tbblue_bytes_per_tile*y)+(x*tbblue_bytes_per_tile);
					/*
					 bits 15-12 : palette offset
  bit     11 : x mirror
  bit     10 : y mirror
  bit      9 : rotate
  bit      8 : ULA over tilemap (if the ula is disabled, bit 8 of tile number)
  bits   7-0 : tile number
					*/

					int xmirror,ymirror,rotate;
					z80_byte tpal;

					z80_byte byte_first;
					z80_byte byte_second;

					byte_first=puntero_tilemap[offset];
					byte_second=puntero_tilemap[offset+1];					

					int tnum=byte_first;
					int ula_over_tilemap;

					z80_byte tbblue_default_tilemap_attr=tbblue_registers[108];

					if (tbblue_bytes_per_tile==1) {
						/*
						(R/W) 0x6C (108) => Default Tilemap Attribute
  bits 7-4 = Palette Offset
  bit 3    = X mirror
  bit 2    = Y mirror
  bit 1    = Rotate
  bit 0    = ULA over tilemap
             (bit 8 of tile id if the ULA is disabled)	
			 			*/
					 	tpal=(tbblue_default_tilemap_attr>>4)&15;
						xmirror=(tbblue_default_tilemap_attr>>3)&1;
						ymirror=(tbblue_default_tilemap_attr>>2)&1;
						rotate=(tbblue_default_tilemap_attr>>1)&1;

						if (tbblue_if_ula_is_enabled() ) {
						/*
						108
						  bit 0    = ULA over tilemap
             (bit 8 of tile id if the ULA is disabled)
						*/							
							ula_over_tilemap=tbblue_default_tilemap_attr &1;
						}

						else {
							tnum |=(tbblue_default_tilemap_attr&1)<<8; // bit      8 : ULA over tilemap (if the ula is disabled, bit 8 of tile number)
						}
						
					}

					else {
						/*
							
					 bits 15-12 : palette offset
  bit     11 : x mirror
  bit     10 : y mirror
  bit      9 : rotate
  bit      8 : ULA over tilemap (if the ula is disabled, bit 8 of tile number)
					*/	
					 	tpal=(byte_second>>4)&15;
						xmirror=(byte_second>>3)&1;
						ymirror=(byte_second>>2)&1;
						rotate=(byte_second>>1)&1;
						//ula_over_tilemap=byte_second &1;

					if (tbblue_if_ula_is_enabled() ) {
						/*
						  bit      8 : ULA over tilemap (if the ula is disabled, bit 8 of tile number)
						*/							
							ula_over_tilemap=byte_second &1;
						}

						else {
							tnum |=(byte_second&1)<<8; // bit      8 : ULA over tilemap (if the ula is disabled, bit 8 of tile number)
						}


					}

					//printf ("tnum: %d\n",tnum);


					if (menu_debug_tsconf_tbblue_msx_tilenav_showmap.v==0) {
						//Modo lista tiles
						sprintf (dumpmemoria,"X: %3d Y: %3d                   ",x,y);

						zxvision_print_string_defaults(menu_debug_tsconf_tbblue_msx_tilenav_lista_tiles_window,1,linea++,dumpmemoria);

						sprintf (dumpmemoria," Tile: %3d %s %s %s %s P:%2d ",tnum,
							(xmirror ? "MX" : "  "),(ymirror ? "MY": "  "),
							(rotate ? "R" : " "),(ula_over_tilemap ? "U": " "),
							tpal );

						zxvision_print_string_defaults(menu_debug_tsconf_tbblue_msx_tilenav_lista_tiles_window,1,linea++,dumpmemoria);
					}
					else {
						//Modo mapa tiles
						int caracter_final;

						if (tnum==0) {
							caracter_final=' '; 
						}
						else {
							caracter_final=menu_debug_tsconf_tbblue_msx_tiles_retorna_visualchar(tnum);
						}

						dumpmemoria[mapa_tile_x++]=caracter_final;
					}					


				}

				current_tile++;

				repetir_ancho--;
			} while (repetir_ancho);

			if (menu_debug_tsconf_tbblue_msx_tilenav_showmap.v) {
				zxvision_print_string_defaults(menu_debug_tsconf_tbblue_msx_tilenav_lista_tiles_window,1,linea++,dumpmemoria);
				puntero_tilemap=puntero_tilemap_orig;
			}
					
		}



	//return linea;

	zxvision_draw_window_contents(menu_debug_tsconf_tbblue_msx_tilenav_lista_tiles_window); 
}

void menu_debug_tsconf_tbblue_msx_tilenav_draw_tiles(void)
{
    
    menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech
    if (!zxvision_drawing_in_background) normal_overlay_texto_menu();


    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_debug_tsconf_tbblue_msx_tilenav_lista_tiles_window->is_minimized) return;

    //printf("overlay tiles %d\n",contador_segundo);

    menu_debug_tsconf_tbblue_msx_tilenav_lista_tiles();				

}



void menu_debug_tsconf_tbblue_msx_tilenav_new_window(zxvision_window *ventana)
{

    char titulo[33];
    
    char linea_leyenda[64];
    sprintf (titulo,"Tile Navigator");

    //Forzar a mostrar atajos
    z80_bit antes_menu_writing_inverse_color;
    antes_menu_writing_inverse_color.v=menu_writing_inverse_color.v;
    menu_writing_inverse_color.v=1;		

    int total_height=menu_debug_tsconf_tbblue_msx_tilenav_total_vert();
    int total_width=31;

    char texto_layer[32];

    //En caso de tbblue y msx, solo hay una capa
    if (MACHINE_IS_TBBLUE || MACHINE_HAS_VDP_9918A) texto_layer[0]=0;

    else sprintf (texto_layer,"~~Layer %d",menu_debug_tsconf_tbblue_msx_tilenav_current_tilelayer);

    if (menu_debug_tsconf_tbblue_msx_tilenav_showmap.v) {
        sprintf (linea_leyenda,"~~Mode: Visual %s",texto_layer);

        if (MACHINE_IS_TSCONF) {
        total_width=TSCONF_TILENAV_TILES_HORIZ_PER_WINDOW+4;
        }
        else if (MACHINE_HAS_VDP_9918A) {
            //Le ponemos siempre el maximo
            total_width=40+4; 
        }			
        else {
            //TBBLUE
            total_width=tbblue_get_tilemap_width()+4;
        }

    }

    else {
        sprintf (linea_leyenda,"~~Mode: List %s",texto_layer);
        total_height*=2;
    }

    //tres mas para ubicar las lineas de leyenda
    total_height+=3;

    //total_height+=2;


    int xventana,yventana,ancho_ventana,alto_ventana,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;

    if (!util_find_window_geometry("tsconftbbluetilenav",&xventana,&yventana,&ancho_ventana,&alto_ventana,
            &is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
        xventana=TSCONF_TILENAV_WINDOW_X;
        yventana=TSCONF_TILENAV_WINDOW_Y;
        ancho_ventana=TSCONF_TILENAV_WINDOW_ANCHO;
        alto_ventana=TSCONF_TILENAV_WINDOW_ALTO;
    }

    //zxvision_new_window(ventana,xventana,yventana,ancho_ventana,alto_ventana,total_width,total_height,titulo);

    zxvision_new_window_gn_cim(ventana,xventana,yventana,
                        ancho_ventana,alto_ventana,
                        total_width,total_height,titulo,"tsconftbbluetilenav",is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);                        


    //Establecer leyenda en la parte de abajo
    ventana->lower_margin=2;
    //Texto sera el de la primera linea
    ventana->upper_margin=1;

    ventana->can_be_backgrounded=1;
    //indicar nombre del grabado de geometria
    //strcpy(ventana->geometry_name,"tsconftbbluetilenav");
    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;        

    //Permitir hotkeys desde raton
    ventana->can_mouse_send_hotkeys=1;			
    
    //Leyenda inferior
    //zxvision_print_string_defaults_fillspc(ventana,1,1,"-----");
    zxvision_print_string_defaults_fillspc(ventana,1,2,linea_leyenda);

    zxvision_draw_window(ventana);	

    //Restaurar comportamiento atajos
    menu_writing_inverse_color.v=antes_menu_writing_inverse_color.v;
    //Nota: los atajos se "pintan" en la memoria de la ventana ya con el color inverso
    //por tanto con meter al principio la variable de inverse_color es suficiente
    //y no hay que activar inverse color cada vez que se redibuja ventana,
    //pues al redibujar ventana está leyendo el contenido de la memoria de la ventana, y ahí ya está con color inverso		

}


void menu_debug_tsconf_tbblue_msx_save_geometry(zxvision_window *ventana)
{
	util_add_window_geometry_compact(ventana);
}

zxvision_window zxvision_window_tsconf_tbblue_tilenav;

void menu_debug_tsconf_tbblue_msx_tilenav(MENU_ITEM_PARAMETERS)
{

	menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();

	
	zxvision_window *ventana;
	ventana=&zxvision_window_tsconf_tbblue_tilenav;

    //IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
    //si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
    //la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
    zxvision_delete_window_if_exists(ventana);	

	menu_debug_tsconf_tbblue_msx_tilenav_new_window(ventana);

	set_menu_overlay_function(menu_debug_tsconf_tbblue_msx_tilenav_draw_tiles);

	menu_debug_tsconf_tbblue_msx_tilenav_lista_tiles_window=ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui


       //Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
       //Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
       if (zxvision_currently_restoring_windows_on_start) {
               //printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
               return;
       }	


	z80_byte tecla;

	//Si no esta multitarea, hacer un refresco inicial para que aparezca el contenido de la ventana sin tener que pulsar una tecla
	//dado que luego funciona como overlay, el overlay se aplica despues de hacer el render
	//esto solo es necesario para ventanas que usan overlay
	if (!menu_multitarea) {
		//printf ("refresca pantalla inicial\n");
		menu_refresca_pantalla();
	}				


	do {
    	menu_speech_tecla_pulsada=0; //Que envie a speech

		tecla=zxvision_common_getkey_refresh();				

        
		switch (tecla) {

			case 'l':
				//En caso de tbblue, hay una sola capa
				if (!MACHINE_IS_TBBLUE) {			
					menu_debug_tsconf_tbblue_msx_save_geometry(ventana);		
					zxvision_destroy_window(ventana);	
					menu_debug_tsconf_tbblue_msx_tilenav_current_tilelayer ^=1;
					menu_debug_tsconf_tbblue_msx_tilenav_new_window(ventana);
				}
			break;

			case 'm':
				menu_debug_tsconf_tbblue_msx_save_geometry(ventana);
				zxvision_destroy_window(ventana);		
				menu_debug_tsconf_tbblue_msx_tilenav_showmap.v ^=1;
				menu_debug_tsconf_tbblue_msx_tilenav_new_window(ventana);

			break;


			default:
				zxvision_handle_cursors_pgupdn(ventana,tecla);
			break;
		}		

		

	} while (tecla!=2 && tecla!=3); 

	//Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
	zxvision_set_window_overlay_from_current(ventana);	

	//restauramos modo normal de texto de menu
    set_menu_overlay_function(normal_overlay_texto_menu);		

    cls_menu_overlay();

    //Grabar geometria ventana. Usamos funcion auxiliar pues la llamamos tambien al cambiar de modo y layer
	menu_debug_tsconf_tbblue_msx_save_geometry(ventana);


    if (tecla==3) {
		zxvision_message_put_window_background();
	}

	else {

		zxvision_destroy_window(ventana);
	}



}




#define SOUND_WAVE_X (menu_origin_x()+1)
#define SOUND_WAVE_Y 3
#define SOUND_WAVE_ANCHO 30
#define SOUND_WAVE_ALTO 15


//Tipo soundwave: 0=vacia, 1=llena, 2=scroll
int menu_sound_wave_llena=0;
int menu_audio_draw_sound_wave_ycentro;

char menu_audio_draw_sound_wave_valor_medio,menu_audio_draw_sound_wave_valor_max,menu_audio_draw_sound_wave_valor_min;
int menu_audio_draw_sound_wave_frecuencia_aproximada;

int menu_audio_draw_sound_wave_volumen=0;
int menu_audio_draw_sound_wave_volumen_escalado=0;


//Usado dentro del overlay de waveform, para mostrar dos veces por segundo el texto que average, etc
int menu_waveform_valor_contador_segundo_anterior;

int menu_waveform_previous_volume=0;

#define MAX_ALTO_WAVEFORM_PIXEL_ARRAY 512
#define MAX_ANCHO_WAVEFORM_PIXEL_ARRAY 1024

//usado para el tipo 2 que hace scroll
int *menu_waveform_pixel_array=NULL;

zxvision_window *menu_audio_draw_sound_wave_window;

z80_bit menu_waveform_separar_canales={0};

void menu_audio_draw_sound_wave(void)
{

	if (!zxvision_drawing_in_background) normal_overlay_texto_menu();


	char buffer_texto_medio[40]; //32+3+margen de posible color rojo del maximo

	menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech


    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_audio_draw_sound_wave_window->is_minimized) return;

	//Inicializar array waveform
	if (menu_waveform_pixel_array==NULL) {
		menu_waveform_pixel_array=malloc(sizeof(int)*MAX_ANCHO_WAVEFORM_PIXEL_ARRAY*MAX_ALTO_WAVEFORM_PIXEL_ARRAY);
		if (menu_waveform_pixel_array==NULL) cpu_panic("Cannot allocate memory for waveform");

		//Establecer array a 0
		int total;
		total=MAX_ANCHO_WAVEFORM_PIXEL_ARRAY*MAX_ALTO_WAVEFORM_PIXEL_ARRAY;
		 
		int i;
		for (i=0;i<total;i++) menu_waveform_pixel_array[i]=ESTILO_GUI_PAPEL_NORMAL;
	}




	//esto hara ejecutar esto 2 veces por segundo
	if ( ((contador_segundo%500) == 0 && menu_waveform_valor_contador_segundo_anterior!=contador_segundo) || menu_multitarea==0) {

		menu_waveform_valor_contador_segundo_anterior=contador_segundo;
		//printf ("Refrescando. contador_segundo=%d\n",contador_segundo);

            //printf("Item seleccionado: %d\n",audio_new_waveform_opcion_seleccionada);

		//menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech

			//Average, min, max    

			sprintf (buffer_texto_medio,"Av.: %d Min: %d Max: %d",
			menu_audio_draw_sound_wave_valor_medio,menu_audio_draw_sound_wave_valor_min,menu_audio_draw_sound_wave_valor_max);


			//menu_escribe_linea_opcion(1,-1,1,buffer_texto_medio);
			zxvision_print_string_defaults_fillspc(menu_audio_draw_sound_wave_window,1,1,buffer_texto_medio);


	

			//Hacer decaer el volumen
			menu_waveform_previous_volume=menu_decae_dec_valor_volumen(menu_waveform_previous_volume,menu_audio_draw_sound_wave_volumen_escalado);


			//Frecuency
			sprintf (buffer_texto_medio,"Average freq: %d Hz (%s)",
			menu_audio_draw_sound_wave_frecuencia_aproximada,get_note_name(menu_audio_draw_sound_wave_frecuencia_aproximada));
			
			zxvision_print_string_defaults_fillspc(menu_audio_draw_sound_wave_window,1,3,buffer_texto_medio);

			
	}


	int ancho;
	

	//Ancho de zona waveform variable segun el tamanyo de ventana
	ancho=menu_audio_draw_sound_wave_window->visible_width-2;

	//Por si acaso, no vayamos a provocar alguna division por cero
	if (ancho<1) ancho=1;

	int alto;

	int lineas_cabecera=4;

	alto=menu_audio_draw_sound_wave_window->visible_height-lineas_cabecera-2;

	//Por si acaso, no vayamos a provocar alguna division por cero
	if (alto<1) alto=1;



	int xorigen=1;
	int yorigen;



	yorigen=lineas_cabecera;


	if (si_complete_video_driver() ) {
        	ancho *=menu_char_width;
	        alto *=8;
        	xorigen *=menu_char_width;
	        yorigen *=8;
	}



	menu_audio_draw_sound_wave_ycentro=yorigen+alto/2;

	int x,y;


    //En teoria no se usa sin inicializar pero por si acaso
    int lasty=0;


	//Para drivers de texto, borrar zona

	if (!si_complete_video_driver() ) {
	        for (x=xorigen;x<xorigen+ancho;x++) {
        	        for (y=yorigen;y<yorigen+alto;y++) {
						zxvision_print_char_simple(menu_audio_draw_sound_wave_window,x,y,ESTILO_GUI_TINTA_NORMAL,ESTILO_GUI_PAPEL_NORMAL,0,' ');
	                }
        	}
	}


	

	audiobuffer_stats audiostats;
	audio_get_audiobuffer_stats(&audiostats);


	menu_audio_draw_sound_wave_valor_max=audiostats.maximo;
	menu_audio_draw_sound_wave_valor_min=audiostats.minimo;
	menu_audio_draw_sound_wave_frecuencia_aproximada=audiostats.frecuencia;
	menu_audio_draw_sound_wave_volumen=audiostats.volumen;
	menu_audio_draw_sound_wave_volumen_escalado=audiostats.volumen_escalado;

	int audiomedio=audiostats.medio;
	menu_audio_draw_sound_wave_valor_medio=audiomedio;
	audiomedio=audiomedio*alto/256;

	//Lo situamos en el centro. Negativo hacia abajo (Y positiva)
	audiomedio=menu_audio_draw_sound_wave_ycentro-audiomedio;



	//Scroll izquierda de array waveform
	//Sinceramente no me acuerdo realmente que efecto queria mostrar con esto...
	if (menu_sound_wave_llena==2) {
		int scroll_x,scroll_y;

		int max_x=MAX_ANCHO_WAVEFORM_PIXEL_ARRAY;
		int max_y=MAX_ALTO_WAVEFORM_PIXEL_ARRAY;

		//Solo hacemos scroll de lo que se vera
		if (ancho<max_x) max_x=ancho;
		if (alto<max_y) max_y=alto;

		//printf ("max scroll %d %d\n",max_x,max_y);

		for (scroll_y=0;scroll_y<max_y;scroll_y++) {
			for (scroll_x=0;scroll_x<max_x-1;scroll_x++) {

				int offset_dest=scroll_y*MAX_ANCHO_WAVEFORM_PIXEL_ARRAY+scroll_x;
				int offset_orig=offset_dest+1;
				menu_waveform_pixel_array[offset_dest]=menu_waveform_pixel_array[offset_orig];
			}
			//Llenar el ultimo en blanco
			int offset_dest=scroll_y*MAX_ANCHO_WAVEFORM_PIXEL_ARRAY+scroll_x;
			menu_waveform_pixel_array[offset_dest]=ESTILO_GUI_PAPEL_NORMAL;
		}
	

	


        //Indicar con linea vertical, el maximo y minimo
        int ydestino_min=alto/2-(menu_audio_draw_sound_wave_valor_min*alto)/256;
        int ydestino_max=alto/2-(menu_audio_draw_sound_wave_valor_max*alto)/256;


        int ydestino;

        //El valor minimo esta "mas abajo" en la pantalla, por eso en pixeles, es valor mas alto
        //El valor maximo esta mas arriba, es valor mas bajo (Y=0 esta arriba del todo)
        for (ydestino=ydestino_max;ydestino<=ydestino_min;ydestino++) {

            //Siempre que estemos en el rango
            if (ydestino>=0 && ydestino<MAX_ALTO_WAVEFORM_PIXEL_ARRAY && ancho>=0 && ancho<MAX_ANCHO_WAVEFORM_PIXEL_ARRAY) {
                int offset_destino=ydestino*MAX_ANCHO_WAVEFORM_PIXEL_ARRAY+ancho-1;
                menu_waveform_pixel_array[offset_destino]=ESTILO_GUI_COLOR_WAVEFORM;
            }

        }
	}


	int puntero_audio=0;
	char valor_audio;


	if (menu_sound_wave_llena<2) {

        int canal=0;
        int total_canales=1;

        if (menu_waveform_separar_canales.v) total_canales=2;

        for (canal=0;canal<total_canales;canal++) {

            puntero_audio=0;

        
            int xinicial_grafica;
            int ancho_grafica;

            if (menu_waveform_separar_canales.v) {
                ancho_grafica=ancho/2;
                xinicial_grafica=xorigen+ancho_grafica*canal;
            }

            else  {
                xinicial_grafica=xorigen;
                ancho_grafica=ancho;
            }



        //Total ancho para cada canal
        for (x=xinicial_grafica;x<xinicial_grafica+ancho_grafica;x++) {


			//Obtenemos valor medio de audio
			int valor_medio=0;

			//Calcular cuantos valores representa un pixel, teniendo en cuenta maximo buffer
			const int max_valores=AUDIO_BUFFER_SIZE/ancho_grafica;

			int valores=max_valores;
			for (;valores>0;valores--,puntero_audio++) {
				if (puntero_audio>=AUDIO_BUFFER_SIZE) {
					//por si el calculo no es correcto, salir.
					//esto no deberia suceder ya que el calculo de max_valores se hace en base al maximo
					cpu_panic("menu_audio_draw_sound_wave: pointer beyond AUDIO_BUFFER_SIZE");
				}


                int suma_canales;

                //Canales separados
                if (menu_waveform_separar_canales.v) {
                    suma_canales=audio_buffer[canal+puntero_audio*2];
                    valor_medio=valor_medio+suma_canales;
                }

                else {

                //Stereo junto
                
                    suma_canales=audio_buffer[puntero_audio*2]+audio_buffer[(puntero_audio*2)+1];
                    suma_canales /=2;
                    valor_medio=valor_medio+suma_canales;
                }
				


			}

			valor_medio=valor_medio/max_valores;


			valor_audio=valor_medio;

			//Lo escalamos a maximo alto

			//y=valor_audio;
			y=valor_audio*alto/256;

			//Lo situamos en el centro. Negativo hacia abajo (Y positiva)
			y=menu_audio_draw_sound_wave_ycentro-y;


			//unimos valor anterior con actual con una linea vertical	
            //Pero si no es el primer valor
			if (x!=xinicial_grafica) {
				if (si_complete_video_driver() ) {

					//Onda no llena
					if (!menu_sound_wave_llena) menu_linea_zxvision(menu_audio_draw_sound_wave_window,x,lasty,y,ESTILO_GUI_COLOR_WAVEFORM);

						//dibujar la onda "llena", es decir, siempre contar desde centro
						//el centro de la y de la onda es variable... se saca valor medio de todos los valores mostrados en pantalla

					//Onda llena
					else menu_linea_zxvision(menu_audio_draw_sound_wave_window,x,audiomedio,y,ESTILO_GUI_COLOR_WAVEFORM);



				}
			}

            //else {
            //    printf("NO unir x: %d\n",x);
            //}

			lasty=y;

			//dibujamos valor actual
			if (si_complete_video_driver() ) {
				zxvision_putpixel(menu_audio_draw_sound_wave_window,x,y,ESTILO_GUI_COLOR_WAVEFORM);
			}

			else {
				//putchar_menu_overlay(SOUND_WAVE_X+x,SOUND_WAVE_Y+y,'#',ESTILO_GUI_COLOR_WAVEFORM,ESTILO_GUI_PAPEL_NORMAL);
				zxvision_print_char_simple(menu_audio_draw_sound_wave_window,x,y,ESTILO_GUI_TINTA_NORMAL,ESTILO_GUI_PAPEL_NORMAL,0,'#');
			}		

		}

        //printf("canal: %d max_valores: %10d puntero_audio: %d\n",canal,AUDIO_BUFFER_SIZE/ancho_grafica,puntero_audio);

        }

        if (menu_waveform_separar_canales.v) {
            //dibujar linea separación
            if (si_complete_video_driver() ) {
                menu_linea_zxvision(menu_audio_draw_sound_wave_window,xorigen+ancho/2,yorigen,yorigen+alto-1,ESTILO_GUI_TINTA_NORMAL);
            }
        }

	}


	//Dibujar todo array de waveform en pantalla
	//Scroll izquierda de array waveform

	if (menu_sound_wave_llena==2) {

		for (y=0;y<alto;y++) {
			for (x=0;x<ancho;x++) {

				//Y siempre que estemos en rango
				if (x<MAX_ANCHO_WAVEFORM_PIXEL_ARRAY && y<MAX_ALTO_WAVEFORM_PIXEL_ARRAY) {

					int offset_destino=y*MAX_ANCHO_WAVEFORM_PIXEL_ARRAY+x;
					int valor=menu_waveform_pixel_array[offset_destino];

					//Dibujar pixel solo si no es blanco
					//Dado que esto es overlay de pixeles, continuamente se resetea a blanco al refrescar pantalla,
					//no hace falta dibujar esos pixeles que ya son blancos
					if (valor!=ESTILO_GUI_PAPEL_NORMAL) {
						zxvision_putpixel(menu_audio_draw_sound_wave_window,x+xorigen,y+yorigen,valor);
					}
				}
				else {
					//Si no, rellenar con color distinto. Rojo para avisar
					zxvision_putpixel(menu_audio_draw_sound_wave_window,x+xorigen,y+yorigen,ESTILO_GUI_TINTA_NO_DISPONIBLE);
				}
				
			}
		}
	}



	//printf ("%d ",puntero_audio);


	//Volume. Mostrarlo siempre, no solo dos veces por segundo, para que se actualice mas frecuentemente
	//if (menu_waveform_previous_volume<menu_audio_draw_sound_wave_volumen_escalado) menu_waveform_previous_volume=menu_audio_draw_sound_wave_volumen_escalado;
	menu_waveform_previous_volume=menu_decae_ajusta_valor_volumen(menu_waveform_previous_volume,menu_audio_draw_sound_wave_volumen_escalado);

	char texto_volumen[32]; 
    menu_string_volumen(texto_volumen,menu_audio_draw_sound_wave_volumen_escalado,menu_waveform_previous_volume);
                                                                //"Volume C: %s"

	sprintf (buffer_texto_medio,"Volume: %3d %s",menu_audio_draw_sound_wave_volumen,texto_volumen);

	zxvision_print_string_defaults_fillspc(menu_audio_draw_sound_wave_window,1,2,buffer_texto_medio);


	zxvision_draw_window_contents(menu_audio_draw_sound_wave_window); 

}




void menu_audio_new_waveform_shape(MENU_ITEM_PARAMETERS)
{
	//menu_sound_wave_llena ^=1;

	menu_sound_wave_llena++;
	if (menu_sound_wave_llena==3) menu_sound_wave_llena=0;

	//Modo scroll no se permite si no hay video driver completo
	if (!si_complete_video_driver() && menu_sound_wave_llena==2) menu_sound_wave_llena=0;
}

void menu_audio_waveform_sep_canales_setting(MENU_ITEM_PARAMETERS)
{
    menu_waveform_separar_canales.v ^=1;
}

zxvision_window zxvision_window_audio_waveform;

void menu_audio_new_waveform(MENU_ITEM_PARAMETERS)
{

 	menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();		

	//zxvision_window ventana;

		zxvision_window *ventana;
		ventana=&zxvision_window_audio_waveform;	


	//IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
	//si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
	//la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
	zxvision_delete_window_if_exists(ventana);

	int x,y,ancho,alto,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;

	if (!util_find_window_geometry("waveform",&x,&y,&ancho,&alto,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
		x=SOUND_WAVE_X;
		y=SOUND_WAVE_Y-2;
		ancho=SOUND_WAVE_ANCHO;
		alto=SOUND_WAVE_ALTO+4;    
	}


    //Crear nueva ventana, asignando ademas geometry name y gestionando si se crea minimizada
    zxvision_new_window_gn_cim(ventana,x,y,ancho,alto,ancho-1,alto-2,"Waveform","waveform",is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);


	//zxvision_new_window_nocheck_staticsize(ventana,x,y,ancho,alto,ancho-1,alto-2,"Waveform");

	ventana->can_be_backgrounded=1;	
	//indicar nombre del grabado de geometria
	//strcpy(ventana->geometry_name,"waveform");
    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;    

    //decimos que tiene que borrar fondo cada vez al redibujar
    //por tanto es como decirle que no use cache de putchar
    //dado que el fondo de texto es casi todo texto con caracter " " eso borra los pixeles que metemos con overlay del frame anterior
    ventana->must_clear_cache_on_draw=1;

	//printf("despues zxvision_new_window_nocheck_staticsize\n");
	zxvision_draw_window(ventana);		

    
    //Cambiamos funcion overlay de texto de menu
    //Se establece a la de funcion de audio waveform
	set_menu_overlay_function(menu_audio_draw_sound_wave);

	menu_audio_draw_sound_wave_window=ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui

	//Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
	//Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
	if (zxvision_currently_restoring_windows_on_start) {
		//printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
		return;
	}

	menu_item *array_menu_audio_new_waveform;
	menu_item item_seleccionado;
	int retorno_menu;
	do {

        //borrar primera linea, por si antes hay visible opcion de view stereo/mono
        zxvision_print_string_defaults_fillspc(ventana,1,0,"");

		//Agrego dos espacios al final para borrar restos de "Scroll" pues ocupa 2 caracteres mas que "Line" y "Fill"
		char *tipos_soundwave[3]={" Line "," Fill ","Scroll"};
	
		menu_add_item_menu_inicial_format(&array_menu_audio_new_waveform,MENU_OPCION_NORMAL,menu_audio_new_waveform_shape,NULL,"[%s] ~~Shape",
				(tipos_soundwave[menu_sound_wave_llena]) );
		menu_add_item_menu_shortcut(array_menu_audio_new_waveform,'s');


        

		//Evito tooltips en los menus tabulados que tienen overlay porque al salir el tooltip detiene el overlay
		//menu_add_item_menu_tooltip(array_menu_audio_new_waveform,"Change wave Shape");
		menu_add_item_menu_ayuda(array_menu_audio_new_waveform,"Change wave Shape: simple line or vertical fill");
						
		menu_add_item_menu_tabulado(array_menu_audio_new_waveform,1,0);


        //Vista stereo solo para line y fill, no con scroll
        if (menu_sound_wave_llena<2) {
            menu_add_item_menu_format(array_menu_audio_new_waveform,MENU_OPCION_NORMAL,menu_audio_waveform_sep_canales_setting,NULL,"[%s] ~~View",
                (menu_waveform_separar_canales.v ? "Stereo" : " Mono "));
            menu_add_item_menu_shortcut(array_menu_audio_new_waveform,'v');

            menu_add_item_menu_tabulado(array_menu_audio_new_waveform,16,0);
        }


		//Nombre de ventana solo aparece en el caso de stdout
		retorno_menu=menu_dibuja_menu(&audio_new_waveform_opcion_seleccionada,&item_seleccionado,array_menu_audio_new_waveform,"Waveform" );

		if (retorno_menu!=MENU_RETORNO_BACKGROUND) {

		
			//En caso de menus tabulados, es responsabilidad de este de borrar la ventana
			cls_menu_overlay();
			if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
				//llamamos por valor de funcion
				if (item_seleccionado.menu_funcion!=NULL) {
					//printf ("actuamos por funcion\n");
					item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
					//En caso de menus tabulados, es responsabilidad de este de borrar la ventana
				
				}
			}
		}

	} while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus && retorno_menu!=MENU_RETORNO_BACKGROUND);

	//Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
	zxvision_set_window_overlay_from_current(ventana);

	//restauramos modo normal de texto de menu
    set_menu_overlay_function(normal_overlay_texto_menu);

    //En caso de menus tabulados, suele ser necesario esto. Si no, la ventana se quedaria visible
    cls_menu_overlay();

	//Grabar geometria ventana
	util_add_window_geometry_compact(ventana);	


	if (retorno_menu==MENU_RETORNO_BACKGROUND) {
                zxvision_message_put_window_background();
	}

	else {	
		//En caso de menus tabulados, es responsabilidad de este de liberar ventana
		zxvision_destroy_window(ventana);
	}

}


zxvision_window *menu_debug_draw_visualmem_window;



#ifdef EMULATE_VISUALMEM


//#define visualmem_ancho_variable (menu_debug_draw_visualmem_window->visible_width-1)
//#define visualmem_alto_variable (menu_debug_draw_visualmem_window->visible_height-1)

#define VISUALMEM_MIN_X (menu_origin_x())
#define VISUALMEM_MIN_Y 0

#define VISUALMEM_DEFAULT_X (VISUALMEM_MIN_X+1)

//int visualmem_x_variable=VISUALMEM_DEFAULT_X;

#define VISUALMEM_DEFAULT_Y (VISUALMEM_MIN_Y+1)
int visualmem_y_variable=VISUALMEM_DEFAULT_Y;

#define VISUALMEM_ANCHO (menu_debug_draw_visualmem_window->visible_width)
#define VISUALMEM_ALTO (menu_debug_draw_visualmem_window->visible_height)

#define VISUALMEM_DEFAULT_WINDOW_ANCHO 30
#define VISUALMEM_DEFAULT_WINDOW_ALTO 22

//0=vemos visualmem write
//1=vemos visualmem read
//2=vemos visualmem opcode
//3=vemos visualmem write+read+opcode todos a la vez
//4=vemos mmc write
//5=vemos mmc read
//6=vemos mmc write+read
int menu_visualmem_donde=0;

int menu_visualmem_modo_defrag=1;


int visualmem_bright_multiplier=10;


//Dice si se muestra visualmem grafico o de texto.
//Si es un driver de solo texto, mostrar texto
//Si es un driver grafico y setting dice que lo mostremos en texto, mostrar texto
//Si nada de lo demas, mostrar grafico
int si_mostrar_visualmem_grafico(void)
{
	if (!si_complete_video_driver()) return 0;

	if (!setting_mostrar_visualmem_grafico.v) return 0;

	return 1;

}

//Dice inicio y final de visualmem
void menu_visualmem_get_start_end(int *inicio,int *final)
{
    int inicio_puntero_membuffer,final_puntero_membuffer;

	//Por defecto
	inicio_puntero_membuffer=16384;
	final_puntero_membuffer=65536;

	//printf ("ancho: %d alto: %d\n",ancho,alto);

	//En spectrum 16kb
	if (MACHINE_IS_SPECTRUM_16) {
		//printf ("spec 16kb\n");
		final_puntero_membuffer=32768;
	}

	if (MACHINE_IS_Z88) {
		        inicio_puntero_membuffer=0;
	}

	//En Inves, mostramos modificaciones a la RAM baja
	if (MACHINE_IS_INVES) {
                        inicio_puntero_membuffer=0;
        }



	//En zx80, zx81 mostrar desde 8192 por si tenemos expansion packs
	if (MACHINE_IS_ZX8081) {
		//por defecto
		//printf ("ramtop_zx8081: %d\n",ramtop_zx8081);
		final_puntero_membuffer=ramtop_zx8081+1;

		if (ram_in_8192.v) {
			//printf ("memoria en 8192\n");
			inicio_puntero_membuffer=8192;
		}

        	if (ram_in_32768.v) {
			//printf ("memoria en 32768\n");
			final_puntero_membuffer=49152;
		}

	        if (ram_in_49152.v) {
			//printf ("memoria en 49152\n");
			final_puntero_membuffer=65536;
		}

	}

        //En Jupiter Ace, desde 8192
        if (MACHINE_IS_ACE) {
                //por defecto
                final_puntero_membuffer=ramtop_ace+1;
                inicio_puntero_membuffer=8192;

        }


	//En CPC, desde 0
	if (MACHINE_IS_CPC) {
		inicio_puntero_membuffer=0;
	}

	if (MACHINE_IS_SAM) {
                inicio_puntero_membuffer=0;
        }



	//En modos de RAM en ROM de +2a en puntero apuntara a direccion 0
	if (MACHINE_IS_SPECTRUM_P2A_P3) {
		if ( (puerto_32765 & 32) == 0 ) {
			//paginacion habilitada

			if ( (puerto_8189 & 1) ) {
				//paginacion de ram en rom
				//printf ("paginacion de ram en rom\n");
				inicio_puntero_membuffer=0;
			}
		}
	}

	if (MACHINE_IS_QL) {
		//inicio_puntero_membuffer=0x18000;
		//la ram propiamente empieza en 20000H
		inicio_puntero_membuffer=0x20000;
		final_puntero_membuffer=QL_MEM_LIMIT+1;
	}

	//Si es de opcode o read, puede ser desde cualquier sitio desde la rom
	if (menu_visualmem_donde>0) {
		inicio_puntero_membuffer=0;
	}

	if (menu_visualmem_donde==4 || menu_visualmem_donde==5 || menu_visualmem_donde==6) {
		final_puntero_membuffer=VISUALMEM_MMC_BUFFER_SIZE;
	}


	*inicio=inicio_puntero_membuffer;
	*final=final_puntero_membuffer;
}

void menu_visualmem_get_accumulated_value(int puntero,int *acumulado,int *acumulado_written,int *acumulado_read,int *acumulado_opcode)
{

	//printf ("puntero: %d\n",inicio_puntero_membuffer);

	//0: written, 1: read, 2: opcode, 3: read+write+opcode, 4: read mmc, 5: write mmc

	switch(menu_visualmem_donde) {
		case 0:
			*acumulado +=visualmem_buffer[puntero];
			clear_visualmembuffer(puntero);
		break;

		case 1:
			*acumulado +=visualmem_read_buffer[puntero];
			clear_visualmemreadbuffer(puntero);
		break;

		case 2:
			*acumulado +=visualmem_opcode_buffer[puntero];
			clear_visualmemopcodebuffer(puntero);
		break;

		case 3:
			*acumulado_written +=visualmem_buffer[puntero];
			*acumulado_read +=visualmem_read_buffer[puntero];
			*acumulado_opcode +=visualmem_opcode_buffer[puntero];
			clear_visualmembuffer(puntero);
			clear_visualmemreadbuffer(puntero);
			clear_visualmemopcodebuffer(puntero);
		break;	

		case 4:
			*acumulado +=visualmem_mmc_write_buffer[puntero];
			clear_visualmemmmc_write_buffer(puntero);
		break;					

		case 5:
			*acumulado +=visualmem_mmc_read_buffer[puntero];
			clear_visualmemmmc_read_buffer(puntero);
		break;

		case 6:
			*acumulado_written +=visualmem_mmc_write_buffer[puntero];
			*acumulado_read +=visualmem_mmc_read_buffer[puntero];
			clear_visualmemmmc_write_buffer(puntero);
			clear_visualmemmmc_read_buffer(puntero);
		break;			


	}


}

void menu_visualmem_putpixel(zxvision_window *ventana,int x,int y,int color_pixel,int color_tinta,int color_papel,z80_byte caracter)
{

				
				if (si_mostrar_visualmem_grafico() ) {
					if (menu_visualmem_modo_defrag) {
						//Cuadradito de color
						int x2,y2;
						for (y2=0;y2<4;y2++) {
							for (x2=0;x2<4;x2++) {
								int color_final=color_pixel;
								if (x2==3 || y2==3) color_final=ESTILO_GUI_PAPEL_NORMAL;
								
								//if (x2==0 && x<30) printf("%d %d\n",x,x*4+x2);

								zxvision_putpixel(ventana,x*4+x2,y*4+y2,color_final);
							}
						}

					}
					else zxvision_putpixel(ventana,x,y,color_pixel);
				}
				else {
					zxvision_print_char_simple(ventana,x,y,color_tinta,color_papel,0,caracter);
				}

			
}

void menu_debug_draw_visualmem(void)
{

	if (!zxvision_drawing_in_background) normal_overlay_texto_menu();

    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_debug_draw_visualmem_window->is_minimized) return;


	int ancho=(VISUALMEM_ANCHO-2);
	int alto=(VISUALMEM_ALTO-5);

	if (ancho<1 || alto<1) return;

	int xorigen=1;
	int yorigen=3;



	if (si_mostrar_visualmem_grafico() ) {

		int multiplicar_ancho=menu_char_width;
		int multiplicar_alto=8;

		if (menu_visualmem_modo_defrag) {

			//Original
			//multiplicar_ancho /=4;
			
			//Para que con char width =8 resulte /2
			//multiplicar_ancho /=(menu_char_width/2); 
			//A/(A/2)=A/1  / A/2 = A*2 /A=2 -> simplificado
			//Nuevo calculo
			//multiplicar_ancho=2;



			//Antiguo calculo
			//TODO: ajustes segun char size 7,6,5 mejor que lo que hay ahora
			//multiplicar_ancho /=4;
			

			//ancho *=multiplicar_ancho;
			//en modo defrag cada cuadradito son 4 pixeles de anchoXalto

			
			ancho=((ancho*multiplicar_ancho)/4);  //-5 //Quitamos 5 para dar margen por la derecha

			multiplicar_alto /=4;
			alto *=multiplicar_alto;	

			//No alterar xorigen. Para que no quede tanto margen por la derecha
			//xorigen *=multiplicar_ancho;
			yorigen *=multiplicar_alto;					
		}

		else {

			ancho *=multiplicar_ancho;
			alto *=multiplicar_alto;

			xorigen *=multiplicar_ancho;
			yorigen *=multiplicar_alto;			
		}


	}


	int tamanyo_total=ancho*alto;

	int x,y;


	int inicio_puntero_membuffer,final_puntero_membuffer;

	menu_visualmem_get_start_end(&inicio_puntero_membuffer,&final_puntero_membuffer);

	//Valores entre 0 y 255: numero de veces byte modificado
	//Valor 65535 especial


	//Calcular cuantos bytes modificados representa un pixel, teniendo en cuenta maximo buffer
	int max_valores=(final_puntero_membuffer-inicio_puntero_membuffer)/tamanyo_total;

	//printf ("max_valores: %d\n",max_valores);
	//printf ("tamanyo total: %d\n",tamanyo_total);
	//le damos uno mas para poder llenar la ventana
	//printf ("inicio: %06XH final: %06XH\n",inicio_puntero_membuffer,final_puntero_membuffer);
	max_valores++;

	for (y=yorigen;y<yorigen+alto;y++) {
        for (x=xorigen;x<xorigen+ancho;x++) {

			//Obtenemos conjunto de bytes modificados

			int valores=max_valores;

			int acumulado=0;

			int acumulado_written,acumulado_read,acumulado_opcode;
			acumulado_written=acumulado_read=acumulado_opcode=0; //Estos usados al visualizar los 3 a la vez

			//si_modificado=0;
			for (;valores>0;valores--,inicio_puntero_membuffer++) {
				if (inicio_puntero_membuffer>=final_puntero_membuffer) {
					//printf ("llegado a final con x: %d y: %d ",x,y);
					//Fuera de memoria direccionable. Zona gris. Decrementamos valor
					//Como se lee a trozos de "max_valores" tamanyo, cuando este trozo empieza ya fuera de memoria
					//acumulado acabara siendo <0 y saldra gris. Si es a medias, si acaba restando mucho, saldra gris tambien
					//(eso solo pasara en el ultimo pixel de la zona direccionable)
					acumulado--;
				}
				else {
					//Es en memoria direccionable. Sumar valor de visualmem y luego haremos valor medio
					menu_visualmem_get_accumulated_value(inicio_puntero_membuffer,&acumulado,&acumulado_written,&acumulado_read,&acumulado_opcode);	
				}
       		}

			//dibujamos valor medio
			if (acumulado>0 || acumulado_written>0 || acumulado_read>0 || acumulado_opcode>0) {

				//Sacar valor medio
				int color_final=acumulado/max_valores;

				if (si_mostrar_visualmem_grafico() ) {

					//Solo calcular esto si tenemos driver grafico completo

					
					//int color_final=acumulado/max_valores;

					//printf ("color final: %d\n",color_final);

					//Aumentar el brillo del color
					color_final=color_final*visualmem_bright_multiplier;
					if (color_final>255) color_final=255;


					if (menu_visualmem_donde==3) {
						//Los 3 de ram a la vez. Combinamos color RGB sacando color de paleta tsconf (15 bits)
						//Paleta es RGB R: 5 bits altos, G: 5 bits medios, B:5 bits bajos


						//Sacar valor medio de los 3 componentes
						int color_final_written=acumulado_written/max_valores;
						color_final_written=color_final_written*visualmem_bright_multiplier;
						if (color_final_written>31) color_final_written=31;

						int color_final_read=acumulado_read/max_valores;
						color_final_read=color_final_read*visualmem_bright_multiplier;
						if (color_final_read>31) color_final_read=31;		

						int color_final_opcode=acumulado_opcode/max_valores;
						color_final_opcode=color_final_opcode*visualmem_bright_multiplier;
						if (color_final_opcode>31) color_final_opcode=31;	

						//Blue sera para los written
						//Green sera para los read
						//Red sera para los opcode
						color_final=(color_final_opcode<<10)|(color_final_read<<5)|color_final_written;		

						color_final +=TSCONF_INDEX_FIRST_COLOR;

					}

					else if (menu_visualmem_donde==6) {
						//Los 2 de MMC a la vez. Combinamos color RGB sacando color de paleta tsconf (15 bits)
						//Paleta es RGB R: 5 bits altos, G: 5 bits medios, B:5 bits bajos


						//Sacar valor medio de los 2 componentes
						int color_final_written=acumulado_written/max_valores;
						color_final_written=color_final_written*visualmem_bright_multiplier;
						if (color_final_written>31) color_final_written=31;

						int color_final_read=acumulado_read/max_valores;
						color_final_read=color_final_read*visualmem_bright_multiplier;
						if (color_final_read>31) color_final_read=31;		

						//Blue sera para los written
						//Green sera para los read

						color_final=(color_final_read<<5)|color_final_written;		

						color_final +=TSCONF_INDEX_FIRST_COLOR;

					}					

					else {
						color_final +=HEATMAP_INDEX_FIRST_COLOR;
					}


				}

				menu_visualmem_putpixel(menu_debug_draw_visualmem_window,x,y,color_final,ESTILO_GUI_TINTA_NORMAL,ESTILO_GUI_PAPEL_NORMAL,'#');
			}

			

			//color ficticio para indicar fuera de memoria y por tanto final de ventana... para saber donde acaba
			else if (acumulado<0) {
				if (menu_visualmem_modo_defrag) {
					//blancos
					menu_visualmem_putpixel(menu_debug_draw_visualmem_window,x,y,ESTILO_GUI_PAPEL_NORMAL,ESTILO_GUI_TINTA_NORMAL,ESTILO_GUI_PAPEL_NORMAL,'-');
				}
				else {
					menu_visualmem_putpixel(menu_debug_draw_visualmem_window,x,y,ESTILO_GUI_COLOR_UNUSED_VISUALMEM,ESTILO_GUI_TINTA_NORMAL,ESTILO_GUI_PAPEL_NORMAL,'-');
				}
			}

			//Valor 0
			else {
				if (menu_visualmem_modo_defrag) {
					//En este caso los cuadraditos de fondo se ven tambien
					menu_visualmem_putpixel(menu_debug_draw_visualmem_window,x,y,ESTILO_GUI_COLOR_UNUSED_VISUALMEM,ESTILO_GUI_TINTA_NORMAL,ESTILO_GUI_PAPEL_NORMAL,' ');
				}

				else {
					menu_visualmem_putpixel(menu_debug_draw_visualmem_window,x,y,ESTILO_GUI_PAPEL_NORMAL,ESTILO_GUI_TINTA_NORMAL,ESTILO_GUI_PAPEL_NORMAL,' ');
				}
				
			}

	    }
	}

	zxvision_draw_window_contents(menu_debug_draw_visualmem_window); 

}




void menu_debug_new_visualmem_looking(MENU_ITEM_PARAMETERS)
{
	menu_visualmem_donde++;
	if (menu_visualmem_donde==7) menu_visualmem_donde=0;
}

void menu_debug_new_visualmem_defrag_mode(MENU_ITEM_PARAMETERS)
{
	menu_visualmem_modo_defrag ^=1;
}

void menu_debug_new_visualmem_bright(MENU_ITEM_PARAMETERS)
{
	if (visualmem_bright_multiplier>=200) visualmem_bright_multiplier=1;
	else if (visualmem_bright_multiplier==1) visualmem_bright_multiplier=10;
	else visualmem_bright_multiplier +=10;
}


zxvision_window zxvision_window_visualmem;

void menu_debug_new_visualmem(MENU_ITEM_PARAMETERS)
{


 	menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();		

	zxvision_window *ventana;
	ventana=&zxvision_window_visualmem;


	//IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
	//si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
	//la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
	zxvision_delete_window_if_exists(ventana);	

	int x,y,ancho,alto,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;;


	if (!util_find_window_geometry("visualmem",&x,&y,&ancho,&alto,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
		x=VISUALMEM_DEFAULT_X;
		y=visualmem_y_variable;
		ancho=VISUALMEM_DEFAULT_WINDOW_ANCHO;
		alto=VISUALMEM_DEFAULT_WINDOW_ALTO;       
	}

    //Crear nueva ventana, asignando ademas geometry name y gestionando si se crea minimizada
    zxvision_new_window_gn_cim(ventana,x,y,ancho,alto,ancho-1,alto-2,"Visual memory","visualmem",is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);


	//zxvision_new_window_nocheck_staticsize(ventana,x,y,ancho,alto,ancho-1,alto-2,"Visual memory");
    
	ventana->can_be_backgrounded=1;	
	//indicar nombre del grabado de geometria
	//strcpy(ventana->geometry_name,"visualmem");
    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;

	zxvision_draw_window(ventana);				


	//Cambiamos funcion overlay de texto de menu
	//Se establece a la de funcion de visualmem + texto
	set_menu_overlay_function(menu_debug_draw_visualmem);


	menu_debug_draw_visualmem_window=ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui	


       //Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
       //Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
       if (zxvision_currently_restoring_windows_on_start) {
               //printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
               return;
       }		


	menu_dibuja_menu_permite_repeticiones_hotk=1;


	menu_item *array_menu_debug_new_visualmem;
	menu_item item_seleccionado;
	int retorno_menu;
	do {



		//Borrar las dos lineas donde van las opciones, por si hay "rastro" anterior
		zxvision_print_string_defaults_fillspc(ventana,1,0,"");
		zxvision_print_string_defaults_fillspc(ventana,1,1,"");


		menu_add_item_menu_inicial_format(&array_menu_debug_new_visualmem,MENU_OPCION_NORMAL,menu_debug_new_visualmem_bright,NULL,"~~Bright: %d",visualmem_bright_multiplier);
		menu_add_item_menu_shortcut(array_menu_debug_new_visualmem,'b');
		menu_add_item_menu_ayuda(array_menu_debug_new_visualmem,"Change bright value");
		menu_add_item_menu_tabulado(array_menu_debug_new_visualmem,1,0);


		//menu_debug_new_visualmem_defrag_mode
		if (si_mostrar_visualmem_grafico() ) {
			menu_add_item_menu_format(array_menu_debug_new_visualmem,MENU_OPCION_NORMAL,menu_debug_new_visualmem_defrag_mode,NULL,"[%c] ~~Defrag style",
		    							(menu_visualmem_modo_defrag ? 'X' : ' ' ));
			menu_add_item_menu_shortcut(array_menu_debug_new_visualmem,'d');
			menu_add_item_menu_ayuda(array_menu_debug_new_visualmem,"Defrag mode");
			menu_add_item_menu_tabulado(array_menu_debug_new_visualmem,14,0);		
		}


		char texto_looking[32];
		if (menu_visualmem_donde == 0) sprintf (texto_looking,"MEM Write");
		else if (menu_visualmem_donde == 1) sprintf (texto_looking,"MEM Read");
		else if (menu_visualmem_donde == 2) sprintf (texto_looking,"Opcode");
		else if (menu_visualmem_donde == 3) sprintf (texto_looking,"MEM W+R+Opcode");
		else if (menu_visualmem_donde == 4) sprintf (texto_looking,"MMC Write");
		else if (menu_visualmem_donde == 5) sprintf (texto_looking,"MMC Read");
		else sprintf (texto_looking,"MMC Write+Read");

		menu_add_item_menu_format(array_menu_debug_new_visualmem,MENU_OPCION_NORMAL,menu_debug_new_visualmem_looking,NULL,"~~Looking: %s",texto_looking);
		menu_add_item_menu_shortcut(array_menu_debug_new_visualmem,'l');

		menu_add_item_menu_ayuda(array_menu_debug_new_visualmem,"Which visualmem to look at.\n\nIf you select all MEM, the final color will be a RGB color result of:\n\n"
					"-Blue component por Written Mem\n-Green component for Read Mem\n-Red component for Opcode.\n\n"
					"Yellow for example is red+green, so opcode fetch+read memory. As an opcode fetch implies a read access,"
					" you won't ever see a red pixel (only opcode fetch) but all opcode fetch will always be yellow.\n"
					"Cyan is green+blue, so read+write\n\n"
					"If you select all MMC, the final color will be a RGB color result of:\n"
					"Blue component por Written MMC\nGreen component for Read MMC.\n"
					"Cyan for example is blue+green, so read+write MMC\n\n"
					
					);
		menu_add_item_menu_tabulado(array_menu_debug_new_visualmem,1,1);



		//Nombre de ventana solo aparece en el caso de stdout
		retorno_menu=menu_dibuja_menu(&debug_new_visualmem_opcion_seleccionada,&item_seleccionado,array_menu_debug_new_visualmem,"Visual memory" );

		if (retorno_menu!=MENU_RETORNO_BACKGROUND) {
		//En caso de menus tabulados, es responsabilidad de este de borrar la ventana
		cls_menu_overlay();

		if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
				//llamamos por valor de funcion
				if (item_seleccionado.menu_funcion!=NULL) {
						//printf ("actuamos por funcion\n");
						item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
		//En caso de menus tabulados, es responsabilidad de este de borrar la ventana
						
				}
		}
		}

	} while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus && retorno_menu!=MENU_RETORNO_BACKGROUND);



	menu_dibuja_menu_permite_repeticiones_hotk=0;


	//Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
	zxvision_set_window_overlay_from_current(ventana);

	//restauramos modo normal de texto de menu
	set_menu_overlay_function(normal_overlay_texto_menu);

    //En caso de menus tabulados, suele ser necesario esto. Si no, la ventana se quedaria visible
    cls_menu_overlay();

	util_add_window_geometry_compact(ventana);

	if (retorno_menu==MENU_RETORNO_BACKGROUND) {
                zxvision_message_put_window_background();
	}

	else {



		//En caso de menus tabulados, es responsabilidad de este de liberar ventana
		zxvision_destroy_window(ventana);		
	}


}





#endif




void menu_ay_player_load(MENU_ITEM_PARAMETERS)
{
	char *filtros[2];

	filtros[0]="ay";

	filtros[1]=0;

	//guardamos directorio actual
	char directorio_actual[PATH_MAX];
	getcwd(directorio_actual,PATH_MAX);

	//Obtenemos directorio de ultimo archivo
	//si no hay directorio, vamos a rutas predefinidas
	if (last_ay_file[0]==0) menu_chdir_sharedfiles();

	else {
					char directorio[PATH_MAX];
					util_get_dir(last_ay_file,directorio);
					//printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

					//cambiamos a ese directorio, siempre que no sea nulo
					if (directorio[0]!=0) {
									debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
									zvfs_chdir(directorio);
					}
	}


	int ret;

	ret=menu_filesel("Select AY File",filtros,last_ay_file);
	//volvemos a directorio inicial
	zvfs_chdir(directorio_actual);


	if (ret==1) {


		ay_player_load_and_play(last_ay_file);

	}
}

/*
void menu_ay_player_exit_tracker(MENU_ITEM_PARAMETERS)
{
	ay_player_stop_player();
}
*/

//Retorna indice a string teniendo en cuenta maximo en pantalla e incrementando en 1
int menu_ay_player_get_continuous_string(int indice_actual,int max_length,char *string,int *retardo)
{

	if ( (*retardo)<10 ) {
		(*retardo)++;
		return 0;
	}

	int longitud=strlen(&string[indice_actual]);
	if (longitud<=max_length) {
		indice_actual=0;
		*retardo=0;
	}
	else {
		indice_actual++;
	}

	return indice_actual;
}





int menu_audio_new_ayplayer_si_mostrar(void)
{
	int mostrar_player;


	mostrar_player=1;
	if (audio_ay_player_mem==NULL) mostrar_player=0;
	if (ay_player_playing.v==0) mostrar_player=0;

	return mostrar_player;
}


//Usado dentro del overlay de ayplayer
int menu_ayplayer_valor_contador_segundo_anterior;

int ayplayer_new_contador_string_author=0;
int ayplayer_new_contador_string_track_name=0;
int ayplayer_new_contador_string_misc=0;
int ayplayer_new_retardo_song_name=0;
int ayplayer_new_retardo_author=0;
int ayplayer_new_retardo_misc=0;


//Para hacer las barras de volumen con "caracter" que decae
int ayplayer_previo_valor_escalado=0;

int ayplayer_previo_valor_volume_A=0;
int ayplayer_previo_valor_volume_B=0;
int ayplayer_previo_valor_volume_C=0;

zxvision_window *menu_audio_new_ayplayer_overlay_window;	

void menu_audio_new_ayplayer_overlay(void)
{

    if (!zxvision_drawing_in_background) normal_overlay_texto_menu();

    menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech

    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_audio_new_ayplayer_overlay_window->is_minimized) return;
    
    //printf("overlay ay player %d\n",contador_segundo);

    int linea;


    linea=7;
	int valor_escalado; 

	int vol_A,vol_B,vol_C;

	


    if (menu_audio_new_ayplayer_si_mostrar()) {
    	//Los volumenes mostrarlos siempre a cada refresco
        char volumen[32];
        char textovolumen[35]; //32+3 de posible color rojo del maximo

        //repetido
        //menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech

        vol_A=ay_3_8912_registros[0][8] & 15;
        vol_B=ay_3_8912_registros[0][9] & 15;
        vol_C=ay_3_8912_registros[0][10] & 15;

        ayplayer_previo_valor_volume_A=menu_decae_ajusta_valor_volumen(ayplayer_previo_valor_volume_A,vol_A);
        ayplayer_previo_valor_volume_B=menu_decae_ajusta_valor_volumen(ayplayer_previo_valor_volume_B,vol_B);
        ayplayer_previo_valor_volume_C=menu_decae_ajusta_valor_volumen(ayplayer_previo_valor_volume_C,vol_C);



	    menu_string_volumen(volumen,ay_3_8912_registros[0][8],ayplayer_previo_valor_volume_A);
        sprintf (textovolumen,"Volume A: %s",volumen);
        //menu_escribe_linea_opcion(linea++,-1,1,textovolumen);
        zxvision_print_string_defaults_fillspc(menu_audio_new_ayplayer_overlay_window,1,linea++,textovolumen);

        menu_string_volumen(volumen,ay_3_8912_registros[0][9],ayplayer_previo_valor_volume_B);
        sprintf (textovolumen,"Volume B: %s",volumen);
        //menu_escribe_linea_opcion(linea++,-1,1,textovolumen);
        zxvision_print_string_defaults_fillspc(menu_audio_new_ayplayer_overlay_window,1,linea++,textovolumen);

        menu_string_volumen(volumen,ay_3_8912_registros[0][10],ayplayer_previo_valor_volume_C);
        sprintf (textovolumen,"Volume C: %s",volumen);
        //menu_escribe_linea_opcion(linea++,-1,1,textovolumen);
        zxvision_print_string_defaults_fillspc(menu_audio_new_ayplayer_overlay_window,1,linea++,textovolumen);



        //Obtenemos antes valor medio total y tambien maximo y minimo
        //Esto solo es necesario para dibujar onda llena



        audiobuffer_stats audiostats;
        audio_get_audiobuffer_stats(&audiostats);

        //int volumen_buffer=audiostats.volumen;

        //Ahora tenemos valor entre 0 y 128. Pasar a entre 0 y 15 
        //int valor_escalado=(mayor*16)/128;

        valor_escalado=audiostats.volumen_escalado;

        /*

        int valor_escalado=(volumen_buffer*16)/128;

        //Vigilar que no pase de 15
        if (valor_escalado>15) valor_escalado=15;
        */

        //printf ("audiomin: %d audiomax: %d maximo: %d valor_escalado: %d\n",audiomin,audiomax,mayor,valor_escalado);

        //Y mostramos indicador volumen
        /*
        Nota: realmente este calculo de volumen no es del todo cierto, estoy viendo el valor maximo de la onda, aunque se puede generar
        sonido muy bajo, por ejemplo, oscilando valores entre 100 y 120 (considerando signed 8 bits), es mas, hay juegos que, al usar beeper,
        "mueven" esa onda hacia arriba, y aunque el indicador de volumen diga que esta muy alto, realmente se oye a volumen normal
        Pero bueno, la mayoria de las veces si que coincide bien el valor de volumen
        */
	

        ayplayer_previo_valor_escalado=menu_decae_ajusta_valor_volumen(ayplayer_previo_valor_escalado,valor_escalado);
        //if (ayplayer_previo_valor_escalado<valor_escalado) ayplayer_previo_valor_escalado=valor_escalado;

        menu_string_volumen(volumen,valor_escalado,ayplayer_previo_valor_escalado);




                            //"Volume C: %s"
        sprintf (textovolumen,"Output:   %s",volumen);
        //menu_escribe_linea_opcion(linea++,-1,1,textovolumen);
        zxvision_print_string_defaults_fillspc(menu_audio_new_ayplayer_overlay_window,1,linea++,textovolumen);

	}

	else {
		//Borrar lineas
		int i;
		linea=0;
		for (i=0;i<11;i++) zxvision_print_string_defaults_fillspc(menu_audio_new_ayplayer_overlay_window,1,linea++,"");
	}

    //esto hara ejecutar esto 2 veces por segundo
    if ( ((contador_segundo%500) == 0 && menu_ayplayer_valor_contador_segundo_anterior!=contador_segundo) || menu_multitarea==0) {

        menu_ayplayer_valor_contador_segundo_anterior=contador_segundo;
        //printf ("Refrescando. contador_segundo=%d\n",contador_segundo);
       
    


        char textoplayer[40];

       


        int mostrar_player;



	    mostrar_player=menu_audio_new_ayplayer_si_mostrar();

       


		if (mostrar_player) {

			linea=0;

            //Indicadores de volumen que decaen
            ayplayer_previo_valor_escalado=menu_decae_dec_valor_volumen(ayplayer_previo_valor_escalado,valor_escalado);


            ayplayer_previo_valor_volume_A=menu_decae_dec_valor_volumen(ayplayer_previo_valor_volume_A,vol_A);
            ayplayer_previo_valor_volume_B=menu_decae_dec_valor_volumen(ayplayer_previo_valor_volume_B,vol_B);
            ayplayer_previo_valor_volume_C=menu_decae_dec_valor_volumen(ayplayer_previo_valor_volume_C,vol_C);




			//printf ("Dibujando player\n");

			z80_byte minutos,segundos,minutos_total,segundos_total;
			minutos=ay_song_length_counter/60/50;
			segundos=(ay_song_length_counter/50)%60;
			minutos_total=ay_song_length/60/50;
			segundos_total=(ay_song_length/50)%60;

            //printf ("segundo. contador segundo: %d\n",contador_segundo);

			sprintf (textoplayer,"Track: %03d/%03d  (%02d:%02d/%02d:%02d)",ay_player_pista_actual,ay_player_total_songs(),minutos,segundos,minutos_total,segundos_total);
			//menu_escribe_linea_opcion(linea++,-1,1,textoplayer);
			zxvision_print_string_defaults_fillspc(menu_audio_new_ayplayer_overlay_window,1,linea++,textoplayer);


			strncpy(textoplayer,&ay_player_file_song_name[ayplayer_new_contador_string_track_name],28);
			textoplayer[28]=0;
			//menu_escribe_linea_opcion(linea++,-1,1,textoplayer);
			zxvision_print_string_defaults_fillspc(menu_audio_new_ayplayer_overlay_window,1,linea++,textoplayer);
			ayplayer_new_contador_string_track_name=menu_ay_player_get_continuous_string(ayplayer_new_contador_string_track_name,28,ay_player_file_song_name,&ayplayer_new_retardo_song_name);

			//menu_escribe_linea_opcion(linea++,-1,1,"Author");
			zxvision_print_string_defaults_fillspc(menu_audio_new_ayplayer_overlay_window,1,linea++,"Author");
			strncpy(textoplayer,&ay_player_file_author[ayplayer_new_contador_string_author],28);
			textoplayer[28]=0;
			//menu_escribe_linea_opcion(linea++,-1,1,textoplayer);
			zxvision_print_string_defaults_fillspc(menu_audio_new_ayplayer_overlay_window,1,linea++,textoplayer);
			ayplayer_new_contador_string_author=menu_ay_player_get_continuous_string(ayplayer_new_contador_string_author,28,ay_player_file_author,&ayplayer_new_retardo_author);

			//menu_escribe_linea_opcion(linea++,-1,1,"Misc");
			zxvision_print_string_defaults_fillspc(menu_audio_new_ayplayer_overlay_window,1,linea++,"Misc");
			strncpy(textoplayer,&ay_player_file_misc[ayplayer_new_contador_string_misc],28);
			textoplayer[28]=0;
			//menu_escribe_linea_opcion(linea++,-1,1,textoplayer);
			zxvision_print_string_defaults_fillspc(menu_audio_new_ayplayer_overlay_window,1,linea++,textoplayer);
			ayplayer_new_contador_string_misc=menu_ay_player_get_continuous_string(ayplayer_new_contador_string_misc,28,ay_player_file_misc,&ayplayer_new_retardo_misc);



		}
	}

	zxvision_draw_window_contents(menu_audio_new_ayplayer_overlay_window);
}



void menu_audio_new_ayplayer_load(MENU_ITEM_PARAMETERS)
{

	//restauramos modo normal de texto de menu
        set_menu_overlay_function(normal_overlay_texto_menu);

	
	menu_ay_player_load(0);

	//Restauramos funcion de overlay
	set_menu_overlay_function(menu_audio_new_ayplayer_overlay);

}

void menu_audio_new_ayplayer_prev(MENU_ITEM_PARAMETERS)
{
	ay_player_previous_track();

}

void menu_audio_new_ayplayer_next(MENU_ITEM_PARAMETERS)
{
	ay_player_next_track();

}

void menu_audio_new_ayplayer_stop(MENU_ITEM_PARAMETERS)
{
	ay_player_stop_player();

}

void menu_audio_new_ayplayer_repeat(MENU_ITEM_PARAMETERS)
{
	ay_player_repeat_file.v ^=1;

}


void menu_audio_new_ayplayer_exitend(MENU_ITEM_PARAMETERS)
{
	ay_player_exit_emulator_when_finish.v ^=1;
}

void menu_audio_new_ayplayer_cpcmode(MENU_ITEM_PARAMETERS)
{
	ay_player_cpc_mode.v ^=1;
	audio_ay_player_play_song(ay_player_pista_actual);
}

												

void menu_audio_new_ayplayer_inftracks(MENU_ITEM_PARAMETERS)
{
	//restauramos modo normal de texto de menu
        set_menu_overlay_function(normal_overlay_texto_menu);

	
	char string_length[5];
	sprintf(string_length,"%d",ay_player_limit_infinite_tracks/50);

        menu_ventana_scanf("Length (0-1310)",string_length,5);
	int l=parse_string_to_number(string_length);

	if (l<0 || l>1310) {
		menu_error_message("Invalid length value");
	}

	else ay_player_limit_infinite_tracks=l*50;

	

	//Restauramos funcion de overlay
	set_menu_overlay_function(menu_audio_new_ayplayer_overlay);
}

void menu_audio_new_ayplayer_len_anytracks(MENU_ITEM_PARAMETERS)
{

	//restauramos modo normal de texto de menu
        set_menu_overlay_function(normal_overlay_texto_menu);

	char string_length[5];
	sprintf(string_length,"%d",ay_player_limit_any_track/50);

	menu_ventana_scanf("Length (0-1310)",string_length,5);
	int l=parse_string_to_number(string_length);

	if (l<0 || l>1310) {
		menu_error_message("Invalid length value");
	}

	else ay_player_limit_any_track=l*50;


	//Restauramos funcion de overlay
	set_menu_overlay_function(menu_audio_new_ayplayer_overlay);
}

zxvision_window zxvision_window_ayplayer;

void menu_audio_new_ayplayer(MENU_ITEM_PARAMETERS)
{


    if (!menu_multitarea) {
        menu_warn_message("This window needs multitask enabled");
        return;
    }

 	menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();		

	//zxvision_window ventana;
    zxvision_window *ventana;
    ventana=&zxvision_window_ayplayer;	

    //IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
    //si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
    //la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
    zxvision_delete_window_if_exists(ventana);	

	int xventana,yventana,ancho_ventana,alto_ventana,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;


	if (!util_find_window_geometry("ayplayer",&xventana,&yventana,&ancho_ventana,&alto_ventana,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
		ancho_ventana=32;
		alto_ventana=20;	 

		xventana=menu_center_x()-ancho_ventana/2;
		yventana=menu_center_y()-alto_ventana/2; 
	}	




	//zxvision_new_window(ventana,xventana,yventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,"AY Player");

    zxvision_new_window_gn_cim(ventana,xventana,yventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,"AY Player","ayplayer",
        is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);                            

	ventana->can_be_backgrounded=1;	
	//indicar nombre del grabado de geometria
	//strcpy(ventana->geometry_name,"ayplayer");
    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;    

	zxvision_draw_window(ventana);	

	

    //Cambiamos funcion overlay de texto de menu
    //Se establece a la de funcion de audio ay player
	set_menu_overlay_function(menu_audio_new_ayplayer_overlay);


	menu_audio_new_ayplayer_overlay_window=ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui		


    //Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
    //Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
    if (zxvision_currently_restoring_windows_on_start) {
            //printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
            return;
    }	



	menu_item *array_menu_audio_new_ayplayer;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

            ayplayer_new_contador_string_author=0;
            ayplayer_new_contador_string_track_name=0;
            ayplayer_new_contador_string_misc=0;

            ayplayer_new_retardo_song_name=0;
            ayplayer_new_retardo_author=0;
            ayplayer_new_retardo_misc=0;

        	char textoplayer[40];
            //Hay que redibujar la ventana desde este bucle
            //menu_audio_new_ayplayer_dibuja_ventana();



            menu_add_item_menu_inicial_format(&array_menu_audio_new_ayplayer,MENU_OPCION_NORMAL,menu_audio_new_ayplayer_load,NULL,"~~Load");
            menu_add_item_menu_shortcut(array_menu_audio_new_ayplayer,'l');
            menu_add_item_menu_ayuda(array_menu_audio_new_ayplayer,"Load AY file");

						
			

			int lin=12;

			menu_add_item_menu_tabulado(array_menu_audio_new_ayplayer,1,lin+5);

				//Vamos a borrar con espacios para que no quede rastro de opciones anteriores, como Yes/No 
				//Si no, pasaria que mostraria "Nos" como parte de la s final de Yes
				int i;
				for (i=12;i<=16;i++) {
					zxvision_fill_width_spaces(ventana,i);
				}			

			if (menu_audio_new_ayplayer_si_mostrar() ) {


				menu_add_item_menu_format(array_menu_audio_new_ayplayer,MENU_OPCION_NORMAL,menu_audio_new_ayplayer_prev,NULL,"~~Prev");
				menu_add_item_menu_shortcut(array_menu_audio_new_ayplayer,'p');
				menu_add_item_menu_ayuda(array_menu_audio_new_ayplayer,"Previous song");
				menu_add_item_menu_tabulado(array_menu_audio_new_ayplayer,1,lin);

				menu_add_item_menu_format(array_menu_audio_new_ayplayer,MENU_OPCION_NORMAL,menu_audio_new_ayplayer_stop,NULL,"~~Stop");
				menu_add_item_menu_shortcut(array_menu_audio_new_ayplayer,'s');
				menu_add_item_menu_ayuda(array_menu_audio_new_ayplayer,"Stop song");
				menu_add_item_menu_tabulado(array_menu_audio_new_ayplayer,6,lin);	

				menu_add_item_menu_format(array_menu_audio_new_ayplayer,MENU_OPCION_NORMAL,menu_audio_new_ayplayer_next,NULL,"~~Next");
				menu_add_item_menu_shortcut(array_menu_audio_new_ayplayer,'n');
				menu_add_item_menu_ayuda(array_menu_audio_new_ayplayer,"Next song");
				menu_add_item_menu_tabulado(array_menu_audio_new_ayplayer,11,lin);

				menu_add_item_menu_format(array_menu_audio_new_ayplayer,MENU_OPCION_NORMAL,menu_audio_new_ayplayer_repeat,NULL,"[%c] Repeat",
					(ay_player_repeat_file.v ? 'X' : ' '));

				menu_add_item_menu_shortcut(array_menu_audio_new_ayplayer,'r');
				menu_add_item_menu_ayuda(array_menu_audio_new_ayplayer,"Repeat from the beginning when finished all songs");
				menu_add_item_menu_tabulado(array_menu_audio_new_ayplayer,1,lin+1);	

				
				menu_add_item_menu_format(array_menu_audio_new_ayplayer,MENU_OPCION_NORMAL,menu_audio_new_ayplayer_exitend,NULL,"[%c] Exit end",
					(ay_player_exit_emulator_when_finish.v ? 'X' : ' ') );
				menu_add_item_menu_shortcut(array_menu_audio_new_ayplayer,'e');
				menu_add_item_menu_ayuda(array_menu_audio_new_ayplayer,"Exit emulator when finished all songs");
				menu_add_item_menu_tabulado(array_menu_audio_new_ayplayer,13,lin+1);	


				if (ay_player_limit_infinite_tracks==0) sprintf(textoplayer,"Length ~~infinite tracks: inf");
				else sprintf(textoplayer,"Length ~~infinite tracks: %d s",ay_player_limit_infinite_tracks/50);
				menu_add_item_menu_format(array_menu_audio_new_ayplayer,MENU_OPCION_NORMAL,menu_audio_new_ayplayer_inftracks,NULL,textoplayer);
				menu_add_item_menu_shortcut(array_menu_audio_new_ayplayer,'i');
				menu_add_item_menu_ayuda(array_menu_audio_new_ayplayer,"Time limit for songs which doesn't have time limit");
				menu_add_item_menu_tabulado(array_menu_audio_new_ayplayer,1,lin+2);			


				if (ay_player_limit_any_track==0) sprintf(textoplayer,"Length ~~any track: No limit");
				else sprintf(textoplayer,"Length ~~any track: %d s",ay_player_limit_any_track/50);
				menu_add_item_menu_format(array_menu_audio_new_ayplayer,MENU_OPCION_NORMAL,menu_audio_new_ayplayer_len_anytracks,NULL,textoplayer);
				menu_add_item_menu_shortcut(array_menu_audio_new_ayplayer,'a');
				menu_add_item_menu_ayuda(array_menu_audio_new_ayplayer,"Time limit for all songs");
				menu_add_item_menu_tabulado(array_menu_audio_new_ayplayer,1,lin+3);

				menu_add_item_menu_format(array_menu_audio_new_ayplayer,MENU_OPCION_NORMAL,menu_audio_new_ayplayer_cpcmode,NULL,"[%c] CPC mode",
					(ay_player_cpc_mode.v ? 'X' : ' '));
				menu_add_item_menu_shortcut(array_menu_audio_new_ayplayer,'c');
				menu_add_item_menu_ayuda(array_menu_audio_new_ayplayer,"Switch to AY CPC mode");
				menu_add_item_menu_tabulado(array_menu_audio_new_ayplayer,1,lin+4);		


			}			
/*


			sprintf(textoplayer,"~~CPC mode: %s",(ay_player_cpc_mode.v ? 'X' : ' '));
			menu_escribe_linea_opcion(linea++,-1,1,textoplayer);
*/



		//Nombre de ventana solo aparece en el caso de stdout
                retorno_menu=menu_dibuja_menu(&audio_new_ayplayer_opcion_seleccionada,&item_seleccionado,array_menu_audio_new_ayplayer,"AY Player" );

	if (retorno_menu!=MENU_RETORNO_BACKGROUND) {

	//En caso de menus tabulados, es responsabilidad de este de borrar la ventana
	cls_menu_overlay();
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
				//En caso de menus tabulados, es responsabilidad de este de borrar la ventana
                                
                        }
                }
			}	

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus && retorno_menu!=MENU_RETORNO_BACKGROUND);


	//Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
	zxvision_set_window_overlay_from_current(ventana);

    //restauramos modo normal de texto de menu
    set_menu_overlay_function(normal_overlay_texto_menu);

    //En caso de menus tabulados, suele ser necesario esto. Si no, la ventana se quedaria visible
    cls_menu_overlay();

	util_add_window_geometry_compact(ventana);


    if (retorno_menu==MENU_RETORNO_BACKGROUND) {
            zxvision_message_put_window_background();
    }

    else {

            //En caso de menus tabulados, es responsabilidad de este de liberar ventana
            zxvision_destroy_window(ventana);
    }

			

}





#define DEBUG_HEXDUMP_WINDOW_X (menu_origin_x() )
#define DEBUG_HEXDUMP_WINDOW_Y 1
#define DEBUG_HEXDUMP_WINDOW_ANCHO 32
#define DEBUG_HEXDUMP_WINDOW_ALTO 23



void menu_debug_hexdump_with_ascii(char *dumpmemoria,menu_z80_moto_int dir_leida,int bytes_por_linea,z80_byte valor_xor)
{
	//dir_leida=adjust_address_space_cpu(dir_leida);

	menu_debug_set_memory_zone_attr();


	int longitud_direccion=MAX_LENGTH_ADDRESS_MEMORY_ZONE;

	menu_debug_print_address_memory_zone(dumpmemoria,dir_leida);

	

	//cambiamos el 0 final por un espacio
	dumpmemoria[longitud_direccion]=' ';

	menu_debug_registers_dump_hex(&dumpmemoria[longitud_direccion+1],dir_leida,bytes_por_linea);

	//01234567890123456789012345678901
	//000FFF ABCDABCDABCDABCD 12345678

	//metemos espacio
	int offset=longitud_direccion+1+bytes_por_linea*2;

	dumpmemoria[offset]=' ';
	//dumpmemoria[offset]='X';

	//Tener en cuenta el valor xor

	menu_debug_registers_dump_ascii(&dumpmemoria[offset+1],dir_leida,bytes_por_linea,menu_debug_hexdump_with_ascii_modo_ascii,valor_xor);

	//printf ("%s\n",dumpmemoria);
}


menu_z80_moto_int menu_debug_hexdump_direccion=0;

int menu_hexdump_edit_position_x=0; //Posicion del cursor relativa al inicio del volcado hexa
int menu_hexdump_edit_position_y=0; //Posicion del cursor relativa al inicio del volcado hexa
int menu_hexdump_lineas_total=13;

//Donde esta el otro caracter que acompanya al nibble, en caso de cursor en zona hexa
int menu_hexdump_edit_position_x_nibble=1;

int menu_hexdump_edit_mode=0;
const int menu_hexdump_bytes_por_linea=8;

void menu_debug_hexdump_cursor_abajo(void);
void menu_debug_hexdump_cursor_arriba(void);

int menu_debug_hexdump_cursor_en_zona_ascii=0;



void menu_debug_hexdump_print_editcursor(zxvision_window *ventana,int x,int y,char caracter)
{


	//Inverso
	int papel=ESTILO_GUI_PAPEL_SELECCIONADO;
    int tinta=ESTILO_GUI_TINTA_SELECCIONADO;	

	//Si multitarea esta off, no se vera el parpadeo. Entonces cambiar el caracter por cursor '_'
	if (!menu_multitarea) caracter='_';

	//putchar_menu_overlay_parpadeo(x,y,caracter,tinta,papel,1);
	zxvision_print_char_simple(ventana,x,y,tinta,papel,1,caracter);

}

void menu_debug_hexdump_print_editcursor_nibble(zxvision_window *ventana,int x,int y,char caracter)
{


	//Inverso
	int papel=ESTILO_GUI_PAPEL_SELECCIONADO;
    int tinta=ESTILO_GUI_TINTA_SELECCIONADO;	

	//putchar_menu_overlay_parpadeo(x,y,caracter,tinta,papel,0);
	zxvision_print_char_simple(ventana,x,y,tinta,papel,0,caracter);

}

void menu_debug_hexdump_edit_cursor_izquierda(void)
{
	if (menu_hexdump_edit_position_x>0) {
		menu_hexdump_edit_position_x--;

		//Si en medio del espacio entre hexa y ascii
		if (menu_hexdump_edit_position_x==menu_hexdump_bytes_por_linea*2) menu_hexdump_edit_position_x--;
	}

	else {
		//Aparecer por la derecha
		menu_debug_hexdump_cursor_arriba();
		menu_hexdump_edit_position_x=menu_hexdump_bytes_por_linea*3;
	}

}

//escribiendo_memoria cursor indica que si estamos a la derecha de zona de edicion escribiendo,
//tiene que saltar a la zona izquierda de la zona ascii o hexa, al llegar a la derecha de dicha zona
void menu_debug_hexdump_edit_cursor_derecha(int escribiendo_memoria)
{

	//Hexdump. bytes_por_linea*2 espacio bytes_por_linea

	int ancho_linea=menu_hexdump_bytes_por_linea*3+1;

	if (menu_hexdump_edit_position_x<ancho_linea-1) {
		menu_hexdump_edit_position_x++;

		if (menu_hexdump_edit_position_x==menu_hexdump_bytes_por_linea*2) { //Fin zona derecha hexa
			if (escribiendo_memoria) {
				//Ponernos al inicio zona hexa de nuevo saltando siguiente linea
				menu_hexdump_edit_position_x=0;
				menu_debug_hexdump_cursor_abajo();
			}
			else {
				//Saltar a zona ascii
				menu_hexdump_edit_position_x++;
			}
		}
	}

	else {
		//Fin zona derecha ascii. 
		menu_debug_hexdump_cursor_abajo();

		if (escribiendo_memoria) {
			//Ponernos en el principio zona ascii
			menu_hexdump_edit_position_x=menu_hexdump_bytes_por_linea*2+1;
		}
		else {
			menu_hexdump_edit_position_x=0;
		}
	}

}

void menu_debug_hexdump_cursor_arriba(void)
{
	int alterar_ptr=0;
    //arriba
    if (menu_hexdump_edit_mode) {
        if (menu_hexdump_edit_position_y>0) menu_hexdump_edit_position_y--;
        else alterar_ptr=1;
    }

    else {
        alterar_ptr=1;
    }

    if (alterar_ptr) {
        menu_debug_hexdump_direccion -=menu_hexdump_bytes_por_linea;
        menu_debug_hexdump_direccion=menu_debug_hexdump_adjusta_en_negativo(menu_debug_hexdump_direccion,menu_hexdump_bytes_por_linea);
    }
}

void menu_debug_hexdump_cursor_abajo(void)
{
	int alterar_ptr=0;
    //abajo
    if (menu_hexdump_edit_mode) {
        if (menu_hexdump_edit_position_y<menu_hexdump_lineas_total-1) menu_hexdump_edit_position_y++;
        else alterar_ptr=1;
    }						
    else {
        alterar_ptr=1;
    }

    if (alterar_ptr) {
        menu_debug_hexdump_direccion +=menu_hexdump_bytes_por_linea;
    }
}

void menu_debug_hexdump_copy(void)
{


    char string_address[10];

    sprintf (string_address,"%XH",menu_debug_hexdump_direccion);
    menu_ventana_scanf("Source?",string_address,10);
	menu_z80_moto_int source=parse_string_to_number(string_address);

    sprintf (string_address,"%XH",source);
    menu_ventana_scanf("Destination?",string_address,10);
	menu_z80_moto_int destination=parse_string_to_number(string_address);
	
	int destzone=menu_change_memory_zone_list_title("Destination Zone");
	if (destzone==-2) return; //Pulsado ESC
	
	int origzone=menu_debug_memory_zone;
	

    strcpy (string_address,"1");
    menu_ventana_scanf("Length?",string_address,10);
	menu_z80_moto_int longitud=parse_string_to_number(string_address);	
	
	

	if (menu_confirm_yesno("Copy bytes")) {
		for (;longitud>0;source++,destination++,longitud--) {
			menu_set_memzone(origzone);
			//Antes de escribir o leer, normalizar zona memoria
			menu_debug_set_memory_zone_attr();
			source=adjust_address_memory_size(source);
			z80_byte valor=menu_debug_get_mapped_byte(source);
			
			
			menu_set_memzone(destzone);
			//Antes de escribir o leer, normalizar zona memoria
			menu_debug_set_memory_zone_attr();
			destination=adjust_address_memory_size(destination);
			menu_debug_write_mapped_byte(destination,valor);
		}
		
		//dejar la zona origen tal cual
		menu_set_memzone(origzone);
	}


}

void menu_debug_hexdump_aviso_edit_filezone(zxvision_window *w)
{
    menu_warn_message("Memory zone is File zone. Changes won't be saved to the file");
    //Volver a dibujar ventana, pues se ha borrado al aparecer el aviso
    //menu_debug_hexdump_ventana();	
	zxvision_draw_window(w);
}

void menu_debug_hexdump_info_subzones(void)
{
	
    int x=1;
    int y=1;
    int ancho=30;
    int alto=22;



    subzone_info *puntero;
    puntero=machine_get_memory_subzone_array(menu_debug_memory_zone,current_machine_type);
    if (puntero==NULL) return;

    zxvision_window ventana;

    zxvision_new_window(&ventana,x,y,ancho,alto,
                                            64,alto-2,"Memory subzones");

    zxvision_draw_window(&ventana);		

    int i;

    char buffer_linea[64];
    for (i=0;puntero[i].nombre[0]!=0;i++) {

        //printf ("inicio: %d fin: %d texto: %s\n",puntero[i].inicio,puntero[i].fin,puntero[i].nombre);
        sprintf (buffer_linea,"%06X-%06X %s",puntero[i].inicio,puntero[i].fin,puntero[i].nombre);
        zxvision_print_string_defaults_fillspc(&ventana,1,i,buffer_linea);
        
    }

    zxvision_draw_window_contents(&ventana);

    zxvision_wait_until_esc(&ventana);

    cls_menu_overlay();

    zxvision_destroy_window(&ventana);					


}

void menu_debug_hexdump_crea_ventana(zxvision_window *ventana,int x,int y,int ancho,int alto,
    int is_minimized,int is_maximized,int ancho_antes_minimize,int alto_antes_minimize)
{
	//asignamos mismo ancho visible que ancho total para poder usar la ultima columna de la derecha, donde se suele poner scroll vertical
    //en teoria ya no hace falta usar zxvision_new_window_nocheck_staticsize, desde hace tiempo que esto funciona correctamente
    //no da errores de tamaño al crear ventana
	//zxvision_new_window_nocheck_staticsize(ventana,x,y,ancho,alto,ancho,alto-2,"Hexadecimal Editor");

    //printf("hexdump crea ventana antes_minimize: %d X %d\n",ancho_antes_minimize,alto_antes_minimize);

    zxvision_new_window_gn_cim(ventana,x,y,ancho,alto,ancho,alto-2,"Hexadecimal Editor","hexeditor",is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);

    //printf("hexdump despues crea ventana antes_minimize: %d X %d\n",ventana->width_before_max_min_imize,ventana->height_before_max_min_imize);

	//printf ("ancho: %d alto: %d\n",ancho,alto);

	ventana->can_use_all_width=1; //Para poder usar la ultima columna de la derecha donde normalmente aparece linea scroll

	//indicar nombre del grabado de geometria
	//strcpy(ventana->geometry_name,"hexeditor");

    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;    

	//Permitir hotkeys desde raton
	ventana->can_mouse_send_hotkeys=1;	

    ventana->can_be_backgrounded=1;

	zxvision_draw_window(ventana);

}

menu_z80_moto_int menu_debug_hexdump_get_cursor_pointer(void)
{
    //Obtener direccion puntero
    menu_z80_moto_int direccion_cursor=menu_debug_hexdump_direccion;

    //int si_zona_hexa=0; //en zona hexa o ascii
    //if (menu_hexdump_edit_position_x<bytes_por_linea*2) si_zona_hexa=1;


    if (!menu_debug_hexdump_cursor_en_zona_ascii) {
        //Sumar x (cada dos, una posicion)
        direccion_cursor +=menu_hexdump_edit_position_x/2;
    }
    else {
        int indice_hasta_ascii=menu_hexdump_bytes_por_linea*2+1; //el hexa y el espacio
        direccion_cursor +=menu_hexdump_edit_position_x-indice_hasta_ascii;
    }

    //Sumar y. 
    direccion_cursor +=menu_hexdump_edit_position_y*menu_hexdump_bytes_por_linea;

    //Ajustar direccion a zona memoria
    direccion_cursor=adjust_address_memory_size(direccion_cursor);


    return direccion_cursor;
}


z80_byte menu_hexdump_valor_xor=0;

char menu_hexdump_nibble_char='X';	
char menu_hexdump_nibble_char_cursor='X';	

int menu_hexdump_editando_en_zona_ascii=0;

int menu_hexdump_print_hexa_ascii(zxvision_window *ventana,int linea)
{


    int lineas_hex;
    char dumpmemoria[33];

    //Hacer que texto ventana empiece pegado a la izquierda
    menu_escribe_linea_startx=0;        

    //No mostrar caracteres especiales
    menu_disable_special_chars.v=1;        

    for (lineas_hex=0;lineas_hex<menu_hexdump_lineas_total;lineas_hex++,linea++) {

        menu_z80_moto_int dir_leida=menu_debug_hexdump_direccion+lineas_hex*menu_hexdump_bytes_por_linea;
        menu_debug_hexdump_direccion=adjust_address_memory_size(menu_debug_hexdump_direccion);

        menu_debug_hexdump_with_ascii(dumpmemoria,dir_leida,menu_hexdump_bytes_por_linea,menu_hexdump_valor_xor);

        zxvision_print_string_defaults_fillspc(ventana,0,linea,dumpmemoria);

        //Meter el nibble_char si corresponde
        if (lineas_hex==menu_hexdump_edit_position_y) {
            menu_hexdump_nibble_char_cursor=dumpmemoria[7+menu_hexdump_edit_position_x];
            if (!menu_hexdump_editando_en_zona_ascii) menu_hexdump_nibble_char=dumpmemoria[7+menu_hexdump_edit_position_x_nibble];
        }
    }

    menu_escribe_linea_startx=1;

    //Volver a mostrar caracteres especiales
    menu_disable_special_chars.v=0;		

    return linea;
    
}

zxvision_window *menu_debug_hexdump_overlay_window;

void menu_debug_hexdump_overlay(void)
{
    if (!zxvision_drawing_in_background) normal_overlay_texto_menu();

    menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech

    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_debug_hexdump_overlay_window->is_minimized) return;

    //printf("Overlay hexdump %d\n",contador_segundo);

    zxvision_window *ventana;

    ventana=menu_debug_hexdump_overlay_window;    

    //Asumimos siempre empieza en linea 2
    menu_hexdump_print_hexa_ascii(ventana,2);

    zxvision_draw_window_contents(ventana);

    //printf("Redibujando en background\n");

}
int menu_debux_hexdump_leyenda(zxvision_window *ventana,int linea)
{
    char textoshow[33];

    //Guardar estado atajos
    z80_bit antes_menu_writing_inverse_color;
    antes_menu_writing_inverse_color.v=menu_writing_inverse_color.v;

            //Forzar a mostrar atajos
        menu_writing_inverse_color.v=1;


//printf ("zone size: %x dir: %x\n",menu_debug_memory_zone_size,menu_debug_hexdump_direccion);

        //menu_escribe_linea_opcion(linea++,-1,1,"");
		zxvision_print_string_defaults_fillspc(ventana,1,linea++,"");

		char buffer_linea[64]; //Por si acaso, entre negritas y demas

		char buffer_char_type[20];

		char string_atajos[3]="~~"; 
		//Si esta en edit mode y en zona de ascii, no hay atajos



		if (menu_hexdump_editando_en_zona_ascii) string_atajos[0]=0;

		if (menu_debug_hexdump_with_ascii_modo_ascii==0) {
			sprintf (buffer_char_type,"ASCII");
		}

		else if (menu_debug_hexdump_with_ascii_modo_ascii==1) {
			sprintf (buffer_char_type,"ZX80");
		}

		else sprintf (buffer_char_type,"ZX81");



		//Si esta editando, mostrar puntero en leyenda de memptr
		char buffer_puntero[32];
		if (menu_hexdump_edit_mode) {
			menu_z80_moto_int direccion_cursor=menu_debug_hexdump_get_cursor_pointer();
			char buf_temp_pointer[32];

			menu_debug_print_address_memory_zone(buf_temp_pointer,direccion_cursor);
			sprintf(buffer_puntero," (%s)",buf_temp_pointer);
		}
		else {
			buffer_puntero[0]=0;
		}

		sprintf (buffer_linea,"%smemptr%s C%sopy",string_atajos,buffer_puntero,string_atajos);


		//menu_escribe_linea_opcion(linea++,-1,1,buffer_linea);
		zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);

		sprintf (buffer_linea,"[%c] %sinvert [%c] Edi%st C%shar:%s",
			(menu_hexdump_valor_xor==0 ? ' ' : 'X'), 
			string_atajos,
			
			(menu_hexdump_edit_mode==0 ? ' ' : 'X' ),
			string_atajos,
			
			string_atajos,
			buffer_char_type
			);
		//menu_escribe_linea_opcion(linea++,-1,1,buffer_linea);
		zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);


		char memory_zone_text[64]; //espacio temporal mas grande por si acaso
		if (menu_debug_show_memory_zones==0) {
			sprintf (memory_zone_text,"Mem %szone (mapped memory)",string_atajos);
		}
		else {
			//printf ("Info zona %d\n",menu_debug_memory_zone);
			char buffer_name[MACHINE_MAX_MEMORY_ZONE_NAME_LENGHT+1];
			//int readwrite;
			machine_get_memory_zone_name(menu_debug_memory_zone,buffer_name);
			sprintf (memory_zone_text,"Mem %szone (%d %s)",string_atajos,menu_debug_memory_zone,buffer_name);
			//printf ("size: %X\n",menu_debug_memory_zone_size);
			//printf ("Despues zona %d\n",menu_debug_memory_zone);
		}

		//truncar texto a 32 por si acaso
		memory_zone_text[32]=0;
		//menu_escribe_linea_opcion(linea++,-1,1,memory_zone_text);
		zxvision_print_string_defaults_fillspc(ventana,1,linea++,memory_zone_text);

		sprintf (textoshow," Size: %d (%d KB)",menu_debug_memory_zone_size,menu_debug_memory_zone_size/1024);
		//menu_escribe_linea_opcion(linea++,-1,1,textoshow);
		zxvision_print_string_defaults_fillspc(ventana,1,linea++,textoshow);


		char subzone_info[33];
		machine_get_memory_subzone_name(menu_debug_memory_zone,current_machine_type, menu_debug_hexdump_direccion, subzone_info);
		if (subzone_info[0]!=0) {
			sprintf(buffer_linea," S~~ubzone info: %s",subzone_info);
			zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);
		}
		else {
			zxvision_print_string_defaults_fillspc(ventana,1,linea++,"");
		}


		//Restaurar comportamiento atajos
		menu_writing_inverse_color.v=antes_menu_writing_inverse_color.v;

    return linea;
}

void menu_debug_hexdump_mostrar_cursor(zxvision_window *ventana)
{
		//Mostrar cursor si en modo edicion
		
		//Al mostrar en cursor: si esta en parte ascii, hacer parpadear el caracter en esa zona, metiendo color de opcion seleccionada
		//Si esta en parte hexa, parpadeamos la parte del nibble que editamos, el otro nibble no parpadea. Ambos tienen color de opcion seleccionada
		//Si multitarea esta a off, no existe el parpadeo, y por tanto, para que se viera en que nibble edita, se mostrara el caracter _, logicamente
		//tapando el caracter de debajo
		//Para ver los caracteres de debajo, los asignamos antes, en el bucle que hace el volcado hexa, y lo guardo en las variables
		//nibble_char_cursor (que dice el caracter de debajo del cursor) y nibble_char (que dice el otro caracter que acompanya al nibble)
	
		
		if (menu_hexdump_edit_mode) {
			int xfinal=7+menu_hexdump_edit_position_x;
			int yfinal=2+menu_hexdump_edit_position_y;			

			menu_debug_hexdump_print_editcursor(ventana,xfinal,yfinal,menu_hexdump_nibble_char_cursor);

			//Indicar nibble entero. En caso de edit hexa
			if (!menu_hexdump_editando_en_zona_ascii) {
				xfinal=7+menu_hexdump_edit_position_x_nibble;
				menu_debug_hexdump_print_editcursor_nibble(ventana,xfinal,yfinal,menu_hexdump_nibble_char);
			}
		}
}

zxvision_window zxvision_window_debug_hexdump;

void menu_debug_hexdump(MENU_ITEM_PARAMETERS)
{
	menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();		

	zxvision_window *ventana;
    ventana=&zxvision_window_debug_hexdump;

    //IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
    //si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
    //la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
    zxvision_delete_window_if_exists(ventana);    

	int xventana,yventana,ancho_ventana,alto_ventana,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;
    //no usamos ancho_antes_minimize ni alto_antes_minimize porque usamos zxvision_new_window_nocheck_staticsize en vez de zxvision_new_window_gn_cim

	
	if (!util_find_window_geometry("hexeditor",&xventana,&yventana,&ancho_ventana,&alto_ventana,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
		xventana=DEBUG_HEXDUMP_WINDOW_X;
		yventana=DEBUG_HEXDUMP_WINDOW_Y;
		ancho_ventana=DEBUG_HEXDUMP_WINDOW_ANCHO;
		alto_ventana=DEBUG_HEXDUMP_WINDOW_ALTO;
	}

    //guardar tamanyo inicial para cuando se recrea la ventana indicarlo como tamanyo de antes minimizado
    //int ancho_ventana_inicial=ancho_ventana;
    //int alto_ventana_inicial=alto_ventana;    


	//asignamos mismo ancho visible que ancho total para poder usar la ultima columna de la derecha, donde se suele poner scroll vertical
	//zxvision_new_window_nocheck_staticsize(ventana,x,y,ancho,alto,ancho,alto-2,"Hexadecimal Editor");
	menu_debug_hexdump_crea_ventana(ventana,xventana,yventana,ancho_ventana,alto_ventana,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);


    //Esto es un poco diferente que otras ventanas, ya que solo hay overlay cuando la ventana esta en segundo plano
    //Ademas, cuando se crea la ventana al haber hecho restore al iniciar el emulador,
    //no se activa el overlay. Podria activarlo aqui, pero no tiene mucho sentido,
    //ya que al iniciar el emulador, el puntero por ejemplo del hex editor apunta a 0, y dudo
    //que el usuario quiera ver esa dirección al iniciar. Lo normal es que al arrancar el usuario
    //elija la ventana del hex editor y ya indique que direccion quiere ir
    
    if (zxvision_currently_restoring_windows_on_start) {
        //printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
        return;
    }

    //Mas info: al entrar en esta ventana por segunda vez, despues de tenerla en background, alguien podria pensar que 
    //la ventana se mostrara entonces dos veces: 1 por estar en background, y 2 por las propias rutinas que hay aqui para dibujarla
    //pero cuando estamos aqui, somos nosotros mismos los que deberíamos hacer el overlay aqui dentro (que no se hace). Las funciones
    //de redibujado de zxvision redibujan las ventanas que están en background, llamando a sus overlays, pero no llaman al overlay
    //de la propia ventana que está activa

	//Nos guardamos alto y ancho anterior. Si el usuario redimensiona la ventana, la redibujamos
	int alto_anterior=alto_ventana;
	int ancho_anterior=ancho_ventana;

	

	//ventana->can_use_all_width=1; //Para poder usar la ultima columna de la derecha donde normalmente aparece linea scroll

	//zxvision_draw_window(ventana);


    z80_byte tecla;

	int salir=0;

	menu_hexdump_valor_xor=0;



	if (MACHINE_IS_ZX80) menu_debug_hexdump_with_ascii_modo_ascii=1;
	else if (MACHINE_IS_ZX81) menu_debug_hexdump_with_ascii_modo_ascii=2;

	else menu_debug_hexdump_with_ascii_modo_ascii=0;


	int asked_about_writing_rom=0;


    int redibujar_ventana=1;


    do {
        //printf("bucle do %d\n",contador_segundo);

        int bytes_por_ventana=menu_hexdump_bytes_por_linea*menu_hexdump_lineas_total;

        /*
        IMPORTANTE: todo este bucle se repite continuamente si hay un evento de raton (mover raton, mover ventana, redimensionar...)
        por tanto, se ejecutaria continuamente esto, gastando monton de cpu, saturandola, y haciendo framedrop y no se veria
        ni la ventana moviendose ni nada de la interfaz
        Por tanto lo que hacemos es que solo se reescribe el contenido de la ventana y se redibuja cuando realmente hay un cambio 
        (pulsada tecla o redimensionado de ventana)
        Esto puede que suceda en alguna otra ventana (aunque creo que no)
        Si es asi, que no refresca casi la ventana en estos casos, el truco es el mismo que aqui
        Creo que esta es de las pocas (o casi ninguna) ventana que sucede pues se realiza mucha escritura de algo y no viene por funcion de overlay
        */

        if (redibujar_ventana) {

            //printf ("dibujar ventana. contador: %d\n",++temp_xxxx);

        //long tiempo_inicio_bucle=timer_get_current_useconds();

        //printf("bucle do. contador segundo %d\n",contador_segundo);
		menu_hexdump_lineas_total=ventana->visible_height-10;

        if (menu_hexdump_lineas_total<3) menu_hexdump_lineas_total=3;

			
        menu_debug_hexdump_cursor_en_zona_ascii=0;
        menu_hexdump_editando_en_zona_ascii=0;


        //Si maquina no es QL, direccion siempre entre 0 y 65535
        //menu_debug_hexdump_direccion=adjust_address_space_cpu(menu_debug_hexdump_direccion);
        menu_debug_hexdump_direccion=adjust_address_memory_size(menu_debug_hexdump_direccion);


		int linea=0;

		

		

		//Antes de escribir, normalizar zona memoria
		menu_debug_set_memory_zone_attr();

        char textoshow[33];

		sprintf (textoshow,"Showing %d bytes per page:",bytes_por_ventana);
        
		zxvision_print_string_defaults_fillspc(ventana,1,linea++,textoshow);
        
		zxvision_print_string_defaults_fillspc(ventana,1,linea++,"");




		//Donde esta el otro caracter que acompanya al nibble, en caso de cursor en zona hexa
		menu_hexdump_edit_position_x_nibble=menu_hexdump_edit_position_x^1;

		
		if (menu_hexdump_edit_position_x>menu_hexdump_bytes_por_linea*2) menu_debug_hexdump_cursor_en_zona_ascii=1;


		if (menu_hexdump_edit_mode && menu_debug_hexdump_cursor_en_zona_ascii) menu_hexdump_editando_en_zona_ascii=1;		

		menu_hexdump_nibble_char='X';	
		menu_hexdump_nibble_char_cursor='X';	



        //Inicio Render
    
        linea=menu_hexdump_print_hexa_ascii(ventana,linea);

        //Fin Render

        menu_debug_hexdump_mostrar_cursor(ventana);



        linea=menu_debux_hexdump_leyenda(ventana,linea);

                

        //printf ("dibujar ventana. contador_segundo: %d\n",contador_segundo);
        
        //
		zxvision_draw_window_contents(ventana);

        } 

		//NOTA: este menu no acostumbra a refrescar rapido la ventana cuando la redimensionamos con el raton
		//es una razon facil: el volcado de hexa usa relativamente mucha cpu,
		//cada vez que redimensionamos ventana, se llama al bucle continuamente, usando mucha cpu y si esta el autoframeskip,
		//hace saltar frames
		
        //printf("(%ld)\n",timer_get_current_useconds()-tiempo_inicio_bucle);
		tecla=zxvision_common_getkey_refresh();		
        //printf("(%ld)\n",timer_get_current_useconds()-tiempo_inicio_bucle);

        //menu_refresca_pantalla();


        //Aviso: hay que conseguir que las letras de accion no esten entre la a-f, porque asi,
        //podemos usar dichas letras para editar hexa

        if (!tecla) redibujar_ventana=0;
        else redibujar_ventana=1;

        switch (tecla) {

            case 11:
                menu_debug_hexdump_cursor_arriba();

            break;

            case 10:
                menu_debug_hexdump_cursor_abajo();

            break;

            case 8:
            case 12:
                //izquierda o delete
                if (menu_hexdump_edit_mode) {
                    //if (menu_hexdump_edit_position_x>0) menu_hexdump_edit_position_x--;
                    menu_debug_hexdump_edit_cursor_izquierda();
                }
            break;

            case 9:
                //derecha
                if (menu_hexdump_edit_mode) {
                    menu_debug_hexdump_edit_cursor_derecha(0);
                    //if (menu_hexdump_edit_position_x<(bytes_por_linea*2)-1) menu_hexdump_edit_position_x++;
                }
            break;					

            case 24:
                //PgUp
                menu_debug_hexdump_direccion -=bytes_por_ventana;
                menu_debug_hexdump_direccion=menu_debug_hexdump_adjusta_en_negativo(menu_debug_hexdump_direccion,bytes_por_ventana);
            break;

            case 25:
                //PgDn
                menu_debug_hexdump_direccion +=bytes_por_ventana;
            break;

            case 'm':
                if (!menu_hexdump_editando_en_zona_ascii)  {
                    menu_debug_hexdump_direccion=menu_debug_hexdump_change_pointer(menu_debug_hexdump_direccion);
                    //menu_debug_hexdump_ventana();
                    zxvision_draw_window(ventana);
                    //Y resetear cursor edicion
                    menu_hexdump_edit_position_x=0;
                    menu_hexdump_edit_position_y=0;
                }
            break;

            case 'o':
                if (!menu_hexdump_editando_en_zona_ascii)  {
                    menu_debug_hexdump_copy();
                    //menu_debug_hexdump_ventana();
                    zxvision_draw_window(ventana);
                }
            break;					

            case 'h':
                if (!menu_hexdump_editando_en_zona_ascii)  {
                    menu_debug_hexdump_with_ascii_modo_ascii++;
                    if (menu_debug_hexdump_with_ascii_modo_ascii==3) menu_debug_hexdump_with_ascii_modo_ascii=0;
                }
            break;

            case 'i':
                if (!menu_hexdump_editando_en_zona_ascii) menu_hexdump_valor_xor ^= 255;
            break;

            case 't':
                if (!menu_hexdump_editando_en_zona_ascii) {
                    menu_hexdump_edit_mode ^= 1;
                    menu_espera_no_tecla();
                    tecla=0; //para no enviar dicha tecla al editor
                }

                //Si zona de filemem
                if (menu_hexdump_edit_mode && menu_debug_memory_zone==MEMORY_ZONE_NUM_FILE_ZONE) {
                    menu_debug_hexdump_aviso_edit_filezone(ventana);				
                }
            break;	

            case 'u':
                //Ver info subzonas
                menu_debug_hexdump_info_subzones();
            break;				

            //case 'l':
            //	menu_debug_hex_shows_inves_low_ram.v ^=1;
            //break;

            case 'z':

                if (!menu_hexdump_editando_en_zona_ascii) {
                    menu_debug_change_memory_zone();
                    asked_about_writing_rom=0;
                }

                break;

            //Salir con ESC si no es modo edit
            case 2:
                if (menu_hexdump_edit_mode) {
                    menu_hexdump_edit_mode=0;
                }
                else salir=1;
            break;

            //salir con tecla background
            case 3:
                salir=1;
            break;

            //Enter tambien sale de modo edit
            case 13:
                if (menu_hexdump_edit_mode) menu_hexdump_edit_mode=0;
            break;



        }

        //Y ahora para el caso de edit_mode y pulsar tecla hexa o ascii segun la zona
        int editar_byte=0;
        if (menu_hexdump_edit_mode) {
            //Para la zona ascii
            if (menu_debug_hexdump_cursor_en_zona_ascii && tecla>=32 && tecla<=126) editar_byte=1; 

            //Para la zona hexa
            if (
                !menu_debug_hexdump_cursor_en_zona_ascii && 
                ( (tecla>='0' && tecla<='9') || (tecla>='a' && tecla<='f') )
                ) {
                editar_byte=1; 
            }
        }

        //Ver si vamos a editar en zona de rom
        if (editar_byte) {
            int attribute_zone;
            //Si zona por defecto mapped memory, asumimos lectura/escritura
            if (menu_debug_memory_zone==-1) attribute_zone=3;
            else machine_get_memory_zone_attrib(menu_debug_memory_zone, &attribute_zone);

            //printf ("Attrib zone %d asked %d\n",attribute_zone,asked_about_writing_rom);

            //Attrib: bit 0: read, bit 1: write
            //Si no tiene atributo de escritura y no se ha pedido antes si se quiere escribir en rom
            if ( (attribute_zone&2)==0 && !asked_about_writing_rom) {
                if (menu_confirm_yesno_texto("Memory zone is ROM","Sure you want to edit?")==0) {
                    editar_byte=0;
                }
                else {
                    asked_about_writing_rom=1;
                }

                //Volver a dibujar ventana, pues se ha borrado al pregutar confirmacion
                //menu_debug_hexdump_ventana();
                zxvision_draw_window(ventana);
            }


        }


        //asked_about_writing_rom

        if (editar_byte) {
                menu_z80_moto_int direccion_cursor=menu_debug_hexdump_get_cursor_pointer();
        

                //TODO: ver si se sale de tamanyo zona memoria

                //printf ("Direccion edicion: %X\n",direccion_cursor);

                //Obtenemos byte en esa posicion
                z80_byte valor_leido=menu_debug_get_mapped_byte(direccion_cursor);


                //Estamos en zona hexa o ascii

                if (!menu_debug_hexdump_cursor_en_zona_ascii) {
                    //printf ("Zona hexa\n");
                    //Zona hexa

                    //Obtener valor nibble
                    z80_byte valor_nibble;

                    if (tecla>='0' && tecla<='9') valor_nibble=tecla-'0';
                    else valor_nibble=tecla-'a'+10;

                    //Ver si par o impar
                    if ( (menu_hexdump_edit_position_x %2) ==0) {
                        //par. alterar nibble alto
                        valor_leido=(valor_leido&0x0F) | (valor_nibble<<4);
                    }

                    else {
                        //impar. alterar nibble bajo
                        valor_leido=(valor_leido&0xF0) | valor_nibble;
                    }
                }

                else {
                    //printf ("Zona ascii\n");
                    valor_leido=tecla;

                    //En el caso de zx80/81

                    if (menu_debug_hexdump_with_ascii_modo_ascii==1) valor_leido=ascii_to_zx80(valor_leido);
                    if (menu_debug_hexdump_with_ascii_modo_ascii==2) valor_leido=ascii_to_zx81(valor_leido);
                }



                //Escribimos valor
                menu_debug_write_mapped_byte(direccion_cursor,valor_leido);

                //Y mover cursor a la derecha
                menu_debug_hexdump_edit_cursor_derecha(1);

                //Si se llega a detecha de hexa o ascii, saltar linea

            
        }

		//Si ha cambiado el alto
        //Redibujar ventana, aunque no recrearla, pues zxvision ya recrea la ventana al ampliarla
        
		alto_ventana=ventana->visible_height;
		ancho_ventana=ventana->visible_width;
		//xventana=ventana->x;
		//yventana=ventana->y;
		if (alto_ventana!=alto_anterior || ancho_ventana!=ancho_anterior) {
			//printf ("recrear ventana. contador_segundo: %d\n",contador_segundo);
			//Recrear ventana
			//Cancelamos edicion si estaba ahi
			menu_hexdump_editando_en_zona_ascii=0;
			menu_hexdump_edit_mode=0;
			menu_hexdump_edit_position_x=0;
			menu_hexdump_edit_position_y=0;
            //int is_minimized=ventana->is_minimized;

			//zxvision_destroy_window(ventana);
			//menu_debug_hexdump_crea_ventana(ventana,xventana,yventana,ancho_ventana,alto_ventana,is_minimized,ancho_antes_minimize,alto_antes_minimize);

            //Indicar tamanyo de antes minimizado, que es el que tenia al inicio
            //dado que se recrea la ventana siempre que cambia tamaño (y si se minimiza tambien),
            //queremos que se indique el tamaño que tenia antes de minimizar por si se deshace el minimizado
            //printf("--menu_debug_hexdump: setting size before minimize: %d X %d\n",alto_ventana_inicial,ancho_ventana_inicial);
            //ventana->height_before_max_min_imize=alto_ventana_inicial;
            //ventana->width_before_max_min_imize=ancho_ventana_inicial;
            zxvision_window_save_size(ventana,&ancho_anterior,&alto_anterior);

			//alto_anterior=alto_ventana;
			//ancho_anterior=ancho_ventana;
            //printf ("ventana recreada. contador_segundo: %d\n",contador_segundo);

            redibujar_ventana=1;
		}
        
			


    } while (salir==0);

    //zxvision_set_window_overlay_from_current(ventana);
    //En este caso es un poco diferente, esta ventana tiene overlay solo cuando
    //esta en background
    ventana->overlay_function=menu_debug_hexdump_overlay;
    menu_debug_hexdump_overlay_window=ventana;



	cls_menu_overlay();

	//Grabar geometria ventana
	util_add_window_geometry_compact(ventana);

	//zxvision_destroy_window(ventana);


	if (tecla==3) {
		zxvision_message_put_window_background();
	}

	else {
		zxvision_destroy_window(ventana);		
 	}    
	

}



//Entrada seleccionada
int adventure_keyboard_selected_item=0;

//Posicion dentro del string
int adventure_keyboard_index_selected_item=0;

//z80_bit menu_osd_adventure_sending_keys={0};


//+1 para poder agregar espacio al final o no
char osd_adventure_palabra_enviada[MAX_OSD_ADV_KEYB_TEXT_LENGTH+1]="";



void menu_osd_adventure_kb_press_key_variable(char letra)
{
	if (letra==0) return; //pequenyo bug: si acaba texto con ~~ no se abrira luego de nuevo el menu. Bug???

	//printf ("Pulsar tecla entrada %d indice en entrada: %d letra: %c\n",adventure_keyboard_selected_item,adventure_keyboard_index_selected_item,letra);
	
	debug_printf (VERBOSE_DEBUG,"Pressing key %c of word %s",letra,osd_adventure_palabra_enviada);

	//Espacio no la gestiona esta funcion de convert_numeros_...
	if (letra==' ') util_set_reset_key(UTIL_KEY_SPACE,1);
	//else convert_numeros_letras_puerto_teclado_continue(letra,1);
	else ascii_to_keyboard_port(letra);

	//Lanzar pulsar tecla 
	timer_on_screen_adv_key=adventure_keyboard_key_length; 
}

void menu_osd_adventure_kb_press_key(void)
{

	//Aunque el usuario haya puesto alguna mayuscula, metemos minusculas
	char letra;

	//Ignorar ~~

	do {
		letra=letra_minuscula(osd_adventure_palabra_enviada[adventure_keyboard_index_selected_item]);
		if (letra=='~') adventure_keyboard_index_selected_item++;
	} while (letra=='~' && letra!=0);

	menu_osd_adventure_kb_press_key_variable(letra);

	/*if (letra==0) return; //pequenyo bug: si acaba texto con ~~ no se abrira luego de nuevo el menu. Bug???

	//printf ("Pulsar tecla entrada %d indice en entrada: %d letra: %c\n",adventure_keyboard_selected_item,adventure_keyboard_index_selected_item,letra);
	
	debug_printf (VERBOSE_DEBUG,"Pressing key %c of word %s",letra,osd_adv_kbd_list[adventure_keyboard_selected_item]);

	//Espacio no la gestiona esta funcion de convert_numeros_...
	if (letra==' ') util_set_reset_key(UTIL_KEY_SPACE,1);
	//else convert_numeros_letras_puerto_teclado_continue(letra,1);
	else ascii_to_keyboard_port(letra);

	//Lanzar pulsar tecla 
	timer_on_screen_adv_key=adventure_keyboard_key_length; */

}



void menu_osd_adventure_keyboard_action(MENU_ITEM_PARAMETERS)
{
	//printf ("opcion seleccionada: %d\n",valor_opcion);
	adventure_keyboard_selected_item=valor_opcion;
    adventure_keyboard_index_selected_item=0;


    //Si enviado enter, espacio o comillas
    if (adventure_keyboard_selected_item<0) {
        switch(adventure_keyboard_selected_item) {
            case -1:
                //printf("Enviamos enter\n");
                sprintf(osd_adventure_palabra_enviada,"%c",13);
            break;

            case -2:
                //printf("Enviamos espacio\n");
                sprintf(osd_adventure_palabra_enviada,"%c",32);
            break;

            case -3:
                //printf("Enviamos comillas\n");
                sprintf(osd_adventure_palabra_enviada,"%c",34);
            break;            
        }              
    }

	else {
	

        //Estamos enviando teclas
        //menu_osd_adventure_sending_keys.v=1;

        //Metemos texto en cadena temporal
        //Ver si habia que enviar un espacio al final
        if (adventure_keyboard_send_final_spc) {
            sprintf(osd_adventure_palabra_enviada,"%s ",osd_adv_kbd_list[adventure_keyboard_selected_item]);
        }
        else {
            strcpy(osd_adventure_palabra_enviada,osd_adv_kbd_list[adventure_keyboard_selected_item]);
        }

    }

	menu_osd_adventure_kb_press_key();
}

//Retorno desde el core
void menu_osd_adventure_keyboard_next(void)
{

    //printf("Caracter: %d\n",osd_adventure_palabra_enviada[adventure_keyboard_index_selected_item]);

    //Si final de string
    adventure_keyboard_index_selected_item++;

	if (osd_adventure_palabra_enviada[adventure_keyboard_index_selected_item]==0) {
		//printf ("Fin texto\n");
		
        //reabrir el menu
        menu_osd_adventure_keyboard(0);
        return;
		
	}

	//Siguiente tecla
	else menu_osd_adventure_kb_press_key();
}


#define ADVENTURE_KB_X (menu_origin_x() )
#define ADVENTURE_KB_Y 0

//Le ponemos maximo ancho 32 que es el mismo que gestiona la funcion de dibujar menu
#define ADVENTURE_KB_ANCHO 32

//Le ponemos maximo alto 24 que es el mismo que gestiona la funcion de dibujar menu
#define ADVENTURE_KB_ALTO 24

//maximo de alto total admitido para la ventana
#define ADVENTURE_KB_MAX_TOTAL_HEIGHT 500

//conservar valor de scroll ultimo para que cuando listado sea grande,
//poder conservar ultima posicion
int menu_osd_advkb_last_offset_y=0;

void menu_osd_adventure_keyboard(MENU_ITEM_PARAMETERS)
{

	//Si estamos enviando teclas
	//if (menu_osd_adventure_sending_keys.v) {
	//	menu_osd_adventure_keyboard_next();
	//	return;
	//}

	//Si lista vacia, error
	if (osd_adv_kbd_defined==0) {
		debug_printf (VERBOSE_ERR,"Empty list");
		return;
	}

	//Si estamos enviando teclas, desactivar
	timer_on_screen_adv_key=0;



 	menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();		

	zxvision_window ventana;

	zxvision_new_window(&ventana,ADVENTURE_KB_X,ADVENTURE_KB_Y,ADVENTURE_KB_ANCHO,ADVENTURE_KB_ALTO,
							ADVENTURE_KB_ANCHO-1,ADVENTURE_KB_MAX_TOTAL_HEIGHT,"OSD Adventure Keyboard");
	zxvision_draw_window(&ventana);		

//printf ("ancho: %d\n",ADVENTURE_KB_ANCHO);

       
        menu_item *array_menu_osd_adventure_keyboard;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

		int initial_test; //si es 1, haremos el calculo inicial del alto

		int alto_ventana=ADVENTURE_KB_ALTO;
		int y_ventana=ADVENTURE_KB_Y;

		for (initial_test=1;initial_test>=0;initial_test--) {


          //Hay que redibujar la ventana desde este bucle
          if (!initial_test) {
			  //menu_dibuja_ventana(ADVENTURE_KB_X,y_ventana,ADVENTURE_KB_ANCHO,alto_ventana,"OSD Adventure Keyboard");
			  zxvision_set_y_position(&ventana,y_ventana);
			  zxvision_set_visible_height(&ventana,alto_ventana);
			  
			  //Alteramos alto total para que coincida con alto ventana (siempre que sea menor que el alto actual)
			  //si fuese mayor el alto, estariamos necesitando mas memoria y seria un problema
			  //esto es un poco feo realmente, pero bueno, al reducir el tamaño no hay problema de que nos salgamos de la memoria
			  int current_height=ventana.total_height;
			  int desired_height=alto_ventana-2;

			  if (desired_height<current_height) {
				  ventana.total_height=desired_height;
			  }
		  }


        //Como no sabemos cual sera el item inicial, metemos este sin asignar, que se sobreescribe en el siguiente menu_add_item_menu
        menu_add_item_menu_inicial(&array_menu_osd_adventure_keyboard,"",MENU_OPCION_UNASSIGNED,NULL,NULL);

	//if (osd_adv_kbd_list[adventure_keyboard_selected_item][adventure_keyboard_index_selected_item]==0) {
	//osd_adv_kbd_defined


        //Metemos enter y espacio
        menu_add_item_menu_format(array_menu_osd_adventure_keyboard,MENU_OPCION_NORMAL,menu_osd_adventure_keyboard_action,NULL,"<Enter>");
        menu_add_item_menu_tabulado(array_menu_osd_adventure_keyboard,1,0);
        menu_add_item_menu_valor_opcion(array_menu_osd_adventure_keyboard,-1); //-1 identifica un enter

        menu_add_item_menu_format(array_menu_osd_adventure_keyboard,MENU_OPCION_NORMAL,menu_osd_adventure_keyboard_action,NULL,"<Space>");
        menu_add_item_menu_tabulado(array_menu_osd_adventure_keyboard,9,0);
        menu_add_item_menu_valor_opcion(array_menu_osd_adventure_keyboard,-2); //-2 identifica un space

        menu_add_item_menu_format(array_menu_osd_adventure_keyboard,MENU_OPCION_NORMAL,menu_osd_adventure_keyboard_action,NULL,"<\">");
        menu_add_item_menu_tabulado(array_menu_osd_adventure_keyboard,17,0);
        menu_add_item_menu_valor_opcion(array_menu_osd_adventure_keyboard,-3); //-3 identifica comillas

		int i;
		int last_x=1;
		int last_y=1;
		int salir=0;        
        

		//Asignar hotkeys, segun si se han asignado antes o no
		//int hotkeys_assigned[26]; //de la A a la Z
		//for (i=0;i<26;i++) hotkeys_assigned[i]=0;
		
		
		for (i=0;i<osd_adv_kbd_defined && !salir;i++) {
			int longitud_texto=strlen(osd_adv_kbd_list[i])+1; //Espacio para la entrada y 1 espacio
			if (last_x+longitud_texto>ADVENTURE_KB_ANCHO) {
				last_x=1;
				last_y++; 
			}

			//controlar maximo de alto
			if (last_y>=ADVENTURE_KB_MAX_TOTAL_HEIGHT) {
				debug_printf (VERBOSE_DEBUG,"Reached maximum window height");
				last_y--;
				salir=1;
			}

			else {
				//Si es cadena vacia, ignorarla. No deberia pasar pues se debe denegar desde donde se lee la configuracion, pero por si acaso
				if (osd_adv_kbd_list[i][0]==0) {
					debug_printf (VERBOSE_DEBUG,"Null string at %d",i);
				}

				else {

					int tiene_hotkey=0;

					char texto_opcion[64];
					strcpy(texto_opcion,osd_adv_kbd_list[i]);

					char hotkey;
					
					//Caracter de hotkey. Crearlo automaticamente
					//hotkey=letra_minuscula(osd_adv_kbd_list[i][0]);

					//Caracter de hotkey. Dejar que el usuario lo escriba en la cadena de texto. Ver si dicha cadena lo tiene

					int j;
					for (j=0;texto_opcion[j];j++) {
						if (texto_opcion[j]=='~' && texto_opcion[j+1]=='~') {
							//Si hay letra detras
							hotkey=letra_minuscula(texto_opcion[j+2]);
							if (hotkey) tiene_hotkey=1;
						}
					}
					

				    menu_add_item_menu_format(array_menu_osd_adventure_keyboard,MENU_OPCION_NORMAL,menu_osd_adventure_keyboard_action,NULL,texto_opcion);
        		    menu_add_item_menu_tabulado(array_menu_osd_adventure_keyboard,last_x,last_y);
					menu_add_item_menu_valor_opcion(array_menu_osd_adventure_keyboard,i);
					//printf ("Agregando palabra %s en %d,%d\n",texto_opcion,last_x,last_y);

					if (tiene_hotkey) {
						menu_add_item_menu_shortcut(array_menu_osd_adventure_keyboard,hotkey);
						longitud_texto -=2;
					}

				}

				last_x+=longitud_texto;
			}

		}

		//Recalcular alto, y_inivial
		//del alto, se pierden 2 siempre
		//si tuvieramos el maximo de y, valdria 21. Y el maximo de alto es 24
		//printf ("ultima y: %d\n",last_y);
		alto_ventana=last_y+3;
		y_ventana=menu_center_y()-alto_ventana/2;
		if (y_ventana<0) y_ventana=0;	


		}


		//Recuperamos antiguo offset de ventana
		zxvision_set_offset_y(&ventana,menu_osd_advkb_last_offset_y);


		//Nombre de ventana solo aparece en el caso de stdout
        retorno_menu=menu_dibuja_menu(&osd_adventure_keyboard_opcion_seleccionada,&item_seleccionado,array_menu_osd_adventure_keyboard,"OSD Adventure KB" );


	//En caso de menus tabulados, es responsabilidad de este de borrar la ventana
        cls_menu_overlay();
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
				//printf ("Item seleccionado: %d\n",item_seleccionado.valor_opcion);
                                //printf ("actuamos por funcion\n");

	                        salir_todos_menus=1;

                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
				//En caso de menus tabulados, es responsabilidad de este de borrar la ventana
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);


		//Guardamos offset de ventana actual
		menu_osd_advkb_last_offset_y=ventana.offset_y;

        cls_menu_overlay();
		//menu_espera_no_tecla();

		//menu_abierto=1;
		//Si con control de joystick se ha salido con tecla ESCMenu, esa tecla de joystick lo que hace es ESC
		//pero luego fuerza a abrir el menu de nuevo. Por tanto, decimos que no hay que abrir menu
		menu_event_open_menu.v=0;

		//printf ("en final de funcion\n");
		zxvision_destroy_window(&ventana);

}









//Usado dentro del overlay de tsconf_dma
//int menu_tsconf_dma_valor_contador_segundo_anterior;

zxvision_window *menu_debug_dma_tsconf_zxuno_overlay_window;


void menu_debug_dma_tsconf_zxuno_overlay(void)
{

    normal_overlay_texto_menu();

    int linea=0;
   

    
    	//mostrarlos siempre a cada refresco
    menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech

	char texto_dma[33];

	if (datagear_dma_emulation.v) {
		//NOTA: Si se activa datagear, no se vera si hay dma de tsconf o zxuno
		z80_int dma_port_a=value_8_to_16(datagear_port_a_start_addr_high,datagear_port_a_start_addr_low);
		z80_int dma_port_b=value_8_to_16(datagear_port_b_start_addr_high,datagear_port_b_start_addr_low);

		z80_int dma_len=value_8_to_16(datagear_block_length_high,datagear_block_length_low);	

		sprintf (texto_dma,"Port A:      %04XH",dma_port_a);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

		sprintf (texto_dma,"Port B:      %04XH",dma_port_b);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

		sprintf (texto_dma,"Length:      %5d",dma_len);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

		if (datagear_wr0 & 4) sprintf (texto_dma,"Port A->B");
		else sprintf (texto_dma,"Port B->A");

		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);



		char access_type[20];

        if (datagear_wr1 & 8) sprintf (access_type,"I/O"); 
		else sprintf (access_type,"Memory");

		if ( (datagear_wr1 & 32) == 0 ) {
            if (datagear_wr1 & 16) sprintf (texto_dma,"Port A++. %s",access_type);
            else sprintf (texto_dma,"Port A--. %s",access_type);
        }
		else sprintf (texto_dma,"Port A fixed. %s",access_type);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);


        if (datagear_wr2 & 8) sprintf (access_type,"I/O"); 
		else sprintf (access_type,"Memory");

		if ( (datagear_wr2 & 32) == 0 ) {
            if (datagear_wr2 & 16) sprintf (texto_dma,"Port B++. %s",access_type);
            else sprintf (texto_dma,"Port B--. %s",access_type);
        }
		else sprintf (texto_dma,"Port B fixed. %s",access_type);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);	
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

		//WR4. Bits D6 D5:
		//#       0   0 = Byte mode -> Do not use (Behaves like Continuous mode, Byte mode on Z80 DMA)
		//#       0   1 = Continuous mode
		//#       1   0 = Burst mode
		//#       1   1 = Do not use

		z80_byte modo_transferencia=(datagear_wr4>>5)&3;
		if (modo_transferencia==0) 		sprintf (texto_dma,"Mode: Byte mode");
		else if (modo_transferencia==1) sprintf (texto_dma,"Mode: Continuous");
		else if (modo_transferencia==2) sprintf (texto_dma,"Mode: Burst");
		else 							sprintf (texto_dma,"Mode: Do not use");

		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);	
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);



	}

	else {

	if (MACHINE_IS_TSCONF) {
		//Construimos 16 valores posibles segun rw (bit bajo) y ddev (bits altos)
		int dma_type=debug_tsconf_dma_ddev*2+debug_tsconf_dma_rw;
						//18 maximo el tipo
						//  012345678901234567890123
						//24. mas dos de margen banda y banda: 26
		sprintf (texto_dma,"Type: %s",tsconf_dma_types[dma_type]);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

		sprintf (texto_dma,"Source:      %06XH",debug_tsconf_dma_source);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

		sprintf (texto_dma,"Destination: %06XH",debug_tsconf_dma_destination);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

		sprintf (texto_dma,"Burst length: %3d",debug_tsconf_dma_burst_length);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

		sprintf (texto_dma,"Burst number: %3d",debug_tsconf_dma_burst_number);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

						//Maximo 25
		sprintf (texto_dma,"Align: %s %s",(debug_tsconf_dma_s_align ? "Source" : "      "),(debug_tsconf_dma_d_align ? "Destination" : "") );
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

		sprintf (texto_dma,"Align size: %d",(debug_tsconf_dma_addr_align_size+1)*256);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

	}

	if (MACHINE_IS_ZXUNO) {
		z80_byte dma_ctrl=zxuno_ports[0xa0];
		z80_byte dma_type=(dma_ctrl & (4+8))>>2;
		z80_byte dma_mode=dma_ctrl & 3;

		z80_int dma_src=value_8_to_16(zxuno_dmareg[0][1],zxuno_dmareg[0][0]);
		z80_int dma_dst=value_8_to_16(zxuno_dmareg[1][1],zxuno_dmareg[1][0]);
		z80_int dma_pre=value_8_to_16(zxuno_dmareg[2][1],zxuno_dmareg[2][0]);
		z80_int dma_len=value_8_to_16(zxuno_dmareg[3][1],zxuno_dmareg[3][0]);	
		z80_int dma_prob=value_8_to_16(zxuno_dmareg[4][1],zxuno_dmareg[4][0]);		
		z80_byte dma_stat=zxuno_ports[0xa6];

		sprintf (texto_dma,"Type: %s",zxuno_dma_types[dma_type]);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

		sprintf (texto_dma,"Mode: %s",zxuno_dma_modes[dma_mode]);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);		
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

		sprintf (texto_dma,"Source:      %04XH",dma_src);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

		sprintf (texto_dma,"Destination: %04XH",dma_dst);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

		sprintf (texto_dma,"Length:      %5d",dma_len);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

		sprintf (texto_dma,"Preescaler:  %5d",dma_pre);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

		char prob_type[10];
		if (dma_ctrl&16) strcpy(prob_type,"dst");
		else strcpy(prob_type,"src");

		sprintf (texto_dma,"Prob: (%s)  %04XH",prob_type,dma_prob);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);		
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

		sprintf (texto_dma,"Stat:          %02XH",dma_stat);
		//menu_escribe_linea_opcion(linea++,-1,1,texto_dma);			
		zxvision_print_string_defaults_fillspc(menu_debug_dma_tsconf_zxuno_overlay_window,1,linea++,texto_dma);

	}

	}

	zxvision_draw_window_contents(menu_debug_dma_tsconf_zxuno_overlay_window);
}






void menu_debug_dma_tsconf_zxuno_disable(MENU_ITEM_PARAMETERS)
{
	if (datagear_dma_emulation.v) datagear_dma_is_disabled.v ^=1;

	else {
		if (MACHINE_IS_TSCONF) tsconf_dma_disabled.v ^=1;
		if (MACHINE_IS_ZXUNO) zxuno_dma_disabled.v ^=1;
	}
}


void menu_debug_dma_tsconf_zxuno(MENU_ITEM_PARAMETERS)
{
 	menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();		





	char texto_ventana[33];
	//por defecto por si acaso
	strcpy(texto_ventana,"DMA");
	int alto_ventana=11;


	if (MACHINE_IS_ZXUNO) {
		strcpy(texto_ventana,"ZXUNO DMA");
		alto_ventana++;
	}

	if (MACHINE_IS_TSCONF) strcpy(texto_ventana,"TSConf DMA");

	if (datagear_dma_emulation.v) strcpy(texto_ventana,"Datagear DMA");	


	//menu_dibuja_ventana(2,6,27,alto,texto_ventana);
	zxvision_window ventana;

	//int posicionx=menu_origin_x()+2;
	int ancho_ventana=27;
	int posicionx=menu_center_x()-ancho_ventana/2;

	int posiciony=menu_center_y()-alto_ventana/2;

	zxvision_new_window(&ventana,posicionx,posiciony,ancho_ventana,alto_ventana,
							ancho_ventana-1,alto_ventana-2,texto_ventana);
	zxvision_draw_window(&ventana);			



    //Cambiamos funcion overlay de texto de menu
	set_menu_overlay_function(menu_debug_dma_tsconf_zxuno_overlay);

	menu_debug_dma_tsconf_zxuno_overlay_window=&ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui			



	menu_item *array_menu_debug_dma_tsconf_zxuno;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

        			
            //Hay que redibujar la ventana desde este bucle
            //menu_debug_dma_tsconf_zxuno_dibuja_ventana();

	

			int lin=8;

			

			int condicion_dma_disabled=tsconf_dma_disabled.v;


			if (MACHINE_IS_ZXUNO) {
				lin++;	
				condicion_dma_disabled=zxuno_dma_disabled.v;
			}

			if (datagear_dma_emulation.v) condicion_dma_disabled=datagear_dma_is_disabled.v;
		
				menu_add_item_menu_inicial_format(&array_menu_debug_dma_tsconf_zxuno,MENU_OPCION_NORMAL,menu_debug_dma_tsconf_zxuno_disable,NULL,"~~DMA: %s",
					(condicion_dma_disabled ? "Disabled" : "Enabled ") );  //Enabled acaba con espacio para borrar rastro de texto "Disabled"
				menu_add_item_menu_shortcut(array_menu_debug_dma_tsconf_zxuno,'d');
				menu_add_item_menu_ayuda(array_menu_debug_dma_tsconf_zxuno,"Disable DMA");
				menu_add_item_menu_tabulado(array_menu_debug_dma_tsconf_zxuno,1,lin);




		//Nombre de ventana solo aparece en el caso de stdout
                retorno_menu=menu_dibuja_menu(&debug_tsconf_dma_opcion_seleccionada,&item_seleccionado,array_menu_debug_dma_tsconf_zxuno,"TSConf DMA" );


	//En caso de menus tabulados, es responsabilidad de este de borrar la ventana
	cls_menu_overlay();
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
				//En caso de menus tabulados, es responsabilidad de este de borrar la ventana
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);



       //restauramos modo normal de texto de menu
       set_menu_overlay_function(normal_overlay_texto_menu);

        //En caso de menus tabulados, suele ser necesario esto. Si no, la ventana se quedaria visible
        cls_menu_overlay();

	//En caso de menus tabulados, es responsabilidad de este de liberar ventana
	zxvision_destroy_window(&ventana);				

}




int menu_tsconf_layer_valor_contador_segundo_anterior;

char *menu_tsconf_layer_aux_usedunused_used="In use";
char *menu_tsconf_layer_aux_usedunused_unused="Unused";

char *menu_tsconf_layer_aux_usedunused(int value)
{
	if (value) return menu_tsconf_layer_aux_usedunused_used;
	else return menu_tsconf_layer_aux_usedunused_unused;
}


zxvision_window *menu_tsconf_layer_overlay_window;

void menu_tsconf_layer_overlay_mostrar_texto(void)
{
 int linea;

    linea=0;

    
        //mostrarlos siempre a cada refresco

                char texto_layer[33];

				if (MACHINE_IS_TSCONF) {

					//menu_escribe_linea_opcion(linea,-1,1,"Border: ");
					zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea,"Border: ");
					linea +=3;

					sprintf (texto_layer,"ULA:       %s",menu_tsconf_layer_aux_usedunused(tsconf_if_ula_enabled()));
					//menu_escribe_linea_opcion(linea,-1,1,texto_layer);
					zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea,texto_layer);
					linea +=3;

					sprintf (texto_layer,"Sprites 0: %s",menu_tsconf_layer_aux_usedunused(tsconf_if_sprites_enabled()));
					//menu_escribe_linea_opcion(linea,-1,1,texto_layer);	
					zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea,texto_layer);
					linea +=3;		

					sprintf (texto_layer,"Tiles 0:   %s",menu_tsconf_layer_aux_usedunused(tsconf_if_tiles_zero_enabled()));
					//menu_escribe_linea_opcion(linea,-1,1,texto_layer);
					zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea,texto_layer);
					linea +=3;	

					sprintf (texto_layer,"Sprites 1: %s",menu_tsconf_layer_aux_usedunused(tsconf_if_sprites_enabled()));
					//menu_escribe_linea_opcion(linea,-1,1,texto_layer);	
					zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea,texto_layer);
					linea +=3;	

					sprintf (texto_layer,"Tiles 1:   %s",menu_tsconf_layer_aux_usedunused(tsconf_if_tiles_one_enabled()));
					//menu_escribe_linea_opcion(linea,-1,1,texto_layer);
					zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea,texto_layer);
					linea +=3;

					sprintf (texto_layer,"Sprites 2: %s",menu_tsconf_layer_aux_usedunused(tsconf_if_sprites_enabled()));
					//menu_escribe_linea_opcion(linea,-1,1,texto_layer);	
					zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea,texto_layer);
					linea +=3;		
				}

				if (MACHINE_IS_TBBLUE) {
	                sprintf (texto_layer,"ULA:       %s",menu_tsconf_layer_aux_usedunused(tbblue_if_ula_is_enabled()) ); 
    	            //menu_escribe_linea_opcion(linea,-1,1,texto_layer);
					zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea,texto_layer);
					linea +=3;

	                sprintf (texto_layer,"Tiles:     %s",menu_tsconf_layer_aux_usedunused(tbblue_if_tilemap_enabled()) ); 
    	            //menu_escribe_linea_opcion(linea,-1,1,texto_layer);
					zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea,texto_layer);
					linea +=3;			

					zxvision_print_string_defaults(menu_tsconf_layer_overlay_window,1,linea,"ULA&Tiles:");
					linea +=2;									

                	sprintf (texto_layer,"Sprites:   %s",menu_tsconf_layer_aux_usedunused(tbblue_if_sprites_enabled() ));
                	//menu_escribe_linea_opcion(linea,-1,1,texto_layer);	
					zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea,texto_layer);
					linea +=3;		

					sprintf (texto_layer,"Layer 2:   %s",menu_tsconf_layer_aux_usedunused(tbblue_is_active_layer2() ) );
    	            //menu_escribe_linea_opcion(linea,-1,1,texto_layer);
					zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea,texto_layer);
					linea +=3;						


					//Layer priorities

					z80_byte prio=tbblue_get_layers_priorities();
					sprintf (texto_layer,"Priorities: (%d)",prio);
					//menu_escribe_linea_opcion(linea++,-1,1,texto_layer);
					zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea++,texto_layer);

				
					int i;
					for (i=0;i<3;i++) {
						char nombre_capa[32];
						strcpy(nombre_capa,tbblue_get_string_layer_prio(i,prio) );
						//if (strcmp(nombre_capa,"ULA&Tiles")) strcpy(nombre_capa,"  ULA  "); //meter espacios para centrarlo
						//las otras capas son "Sprites" y "Layer 2" y ocupan lo mismo

													//     Sprites
													//    ULA&Tiles
						if (i!=2) strcpy (texto_layer,"|---------------|");
						else      strcpy (texto_layer,"v---------------v");

						//Centrar el nombre de capa
						int longitud_medio=strlen(nombre_capa)/2;
						int medio=strlen(texto_layer)/2;
						int pos=medio-longitud_medio;
						if (pos<0) pos=0;

						//Meter texto centrado y quitar 0 del final
						strcpy(&texto_layer[pos],nombre_capa);

						int final=strlen(texto_layer);
						texto_layer[final]='-';

						//menu_escribe_linea_opcion(linea++,-1,1,texto_layer);
						zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea++,texto_layer);

					}
				
				}		

                if (MACHINE_HAS_VDP_9918A) {

                    //if (!vdp_9918a_si_sms_video_mode4()) {
                    if (!MACHINE_IS_SMS) {

                        //menu_escribe_linea_opcion(linea,-1,1,"Border: ");
                        zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea,"Border: ");
                        linea +=3;

                        zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea,"Pixels:");
                        linea +=3;

                        zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea,"Sprites:");
                        linea +=3;	
        
                    }	

                    else {
                        //menu_escribe_linea_opcion(linea,-1,1,"Border: ");
                        zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea,"Border: ");
                        linea +=3;

                        zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea,"Tiles Background:");
                        linea +=3;


                            zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea,"Tiles Foreground:");
                            linea +=3;
                        


                        zxvision_print_string_defaults_fillspc(menu_tsconf_layer_overlay_window,1,linea,"Sprites:");
                        linea +=3;	

                        
                        linea++;
                        zxvision_print_string_defaults(menu_tsconf_layer_overlay_window,1,linea,"Force show column 0:");
                        linea +=2;                        

                        zxvision_print_string_defaults(menu_tsconf_layer_overlay_window,1,linea,"Lock scroll horiz.: ");
                        linea +=2;        

                        zxvision_print_string_defaults(menu_tsconf_layer_overlay_window,1,linea,"Lock scroll vert.:  ");
                        linea +=2;                                            

                                                
                    }				

                }



}



void menu_tsconf_layer_overlay(void)
{

    normal_overlay_texto_menu();

 	menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech

 
    //esto hara ejecutar esto 2 veces por segundo
    if ( ((contador_segundo%500) == 0 && menu_tsconf_layer_valor_contador_segundo_anterior!=contador_segundo) || menu_multitarea==0) {

        menu_tsconf_layer_valor_contador_segundo_anterior=contador_segundo;
        //printf ("Refrescando. contador_segundo=%d\n",contador_segundo);
       

		menu_tsconf_layer_overlay_mostrar_texto();
		zxvision_draw_window_contents(menu_tsconf_layer_overlay_window);

    }
}


void menu_tsconf_layer_settings_ula(MENU_ITEM_PARAMETERS)
{
	tsconf_force_disable_layer_ula.v ^=1;
}


void menu_tsconf_layer_settings_sprites_zero(MENU_ITEM_PARAMETERS)
{
	tsconf_force_disable_layer_sprites_zero.v ^=1;
}

void menu_tsconf_layer_settings_sprites_one(MENU_ITEM_PARAMETERS)
{
	tsconf_force_disable_layer_sprites_one.v ^=1;
}

void menu_tsconf_layer_settings_sprites_two(MENU_ITEM_PARAMETERS)
{
	tsconf_force_disable_layer_sprites_two.v ^=1;
}

void menu_tsconf_layer_settings_tiles_zero(MENU_ITEM_PARAMETERS)
{
	tsconf_force_disable_layer_tiles_zero.v ^=1;
}

void menu_tsconf_layer_settings_tiles_one(MENU_ITEM_PARAMETERS)
{
	tsconf_force_disable_layer_tiles_one.v ^=1;
}

void menu_tsconf_layer_settings_border(MENU_ITEM_PARAMETERS)
{
	tsconf_force_disable_layer_border.v ^=1;
}

/*
extern z80_bit tbblue_force_disable_layer_ula;
extern z80_bit tbblue_force_disable_layer_sprites;
extern z80_bit tbblue_force_disable_layer_layer_two;
*/

void menu_tbblue_layer_settings_sprites(MENU_ITEM_PARAMETERS)
{
	tbblue_force_disable_layer_sprites.v ^=1;
}

void menu_tbblue_layer_settings_ula(MENU_ITEM_PARAMETERS)
{
	tbblue_force_disable_layer_ula.v ^=1;
}

void menu_tbblue_layer_settings_tilemap(MENU_ITEM_PARAMETERS)
{
	tbblue_force_disable_layer_tilemap.v ^=1;
}

void menu_tbblue_layer_settings_layer_two(MENU_ITEM_PARAMETERS)
{
	tbblue_force_disable_layer_layer_two.v ^=1;
}

void menu_tbblue_layer_reveal_ula(MENU_ITEM_PARAMETERS)
{
	tbblue_reveal_layer_ula.v ^=1;
}

void menu_tbblue_layer_reveal_layer2(MENU_ITEM_PARAMETERS)
{
	tbblue_reveal_layer_layer2.v ^=1;
}

void menu_tbblue_layer_reveal_sprites(MENU_ITEM_PARAMETERS)
{
	tbblue_reveal_layer_sprites.v ^=1;
}



void menu_tsconf_layer_reveal_ula(MENU_ITEM_PARAMETERS)
{
	tsconf_reveal_layer_ula.v ^=1;
}

void menu_tsconf_layer_reveal_sprites_zero(MENU_ITEM_PARAMETERS)
{
	tsconf_reveal_layer_sprites_zero.v ^=1;
}

void menu_tsconf_layer_reveal_sprites_one(MENU_ITEM_PARAMETERS)
{
	tsconf_reveal_layer_sprites_one.v ^=1;
}


void menu_tsconf_layer_reveal_sprites_two(MENU_ITEM_PARAMETERS)
{
	tsconf_reveal_layer_sprites_two.v ^=1;
}


void menu_tsconf_layer_reveal_tiles_zero(MENU_ITEM_PARAMETERS)
{
	tsconf_reveal_layer_tiles_zero.v ^=1;
}

void menu_tsconf_layer_reveal_tiles_one(MENU_ITEM_PARAMETERS)
{
	tsconf_reveal_layer_tiles_one.v ^=1;
}



void menu_msx_layer_settings_border(MENU_ITEM_PARAMETERS)
{
	vdp_9918a_force_disable_layer_border.v ^=1;
}


void menu_msx_layer_settings_ula(MENU_ITEM_PARAMETERS)
{
	vdp_9918a_force_disable_layer_ula.v ^=1;
}

void menu_msx_layer_settings_sprites(MENU_ITEM_PARAMETERS)
{
	vdp_9918a_force_disable_layer_sprites.v ^=1;
}




void menu_msx_layer_reveal_ula(MENU_ITEM_PARAMETERS)
{
	vdp_9918a_reveal_layer_ula.v ^=1;
}

void menu_msx_layer_reveal_sprites(MENU_ITEM_PARAMETERS)
{
	vdp_9918a_reveal_layer_sprites.v ^=1;
}

void menu_sms_layer_settings_force_col0(MENU_ITEM_PARAMETERS)
{
    vdp_9918a_sms_force_show_column_zero.v ^=1;
}

void menu_sms_layer_settings_lock_scroll_horiz(MENU_ITEM_PARAMETERS)
{
    vdp_9918a_sms_lock_scroll_horizontal.v ^=1;
}

void menu_sms_layer_settings_lock_scroll_vert(MENU_ITEM_PARAMETERS)
{
    vdp_9918a_sms_lock_scroll_vertical.v ^=1;
}


void menu_sms_layer_settings_tile_fg(MENU_ITEM_PARAMETERS)
{
    vdp_9918a_force_disable_layer_tile_fg.v ^=1;
}

void menu_sms_layer_reveal_tile_fg(MENU_ITEM_PARAMETERS)
{
    vdp_9918a_reveal_layer_tile_fg.v ^=1;
}

void menu_sms_layer_settings_tile_bg(MENU_ITEM_PARAMETERS)
{
    vdp_9918a_force_disable_layer_tile_bg.v ^=1;

    //Para que tambien funcione en casos de SMS con modos no 4, en realvideo
    vdp_9918a_force_disable_layer_ula.v=vdp_9918a_force_disable_layer_tile_bg.v;    
}

void menu_sms_layer_reveal_tile_bg(MENU_ITEM_PARAMETERS)
{
    vdp_9918a_reveal_layer_tile_bg.v ^=1;

    //Para que tambien funcione en casos de SMS con modos no 4, en realvideo
    vdp_9918a_reveal_layer_ula.v=vdp_9918a_reveal_layer_tile_bg.v;    
}

void menu_sms_layer_force_bg_tiles(MENU_ITEM_PARAMETERS)
{
    vdp_9918a_force_bg_tiles.v ^=1;
}

void menu_tsconf_layer_settings(MENU_ITEM_PARAMETERS)
{

	menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();		

	int ancho=20;
	int alto=22;

	int x;
	int y;
	//y=1;	

	if (MACHINE_IS_TBBLUE) {
		alto=20;
		//y=1;
	}


	else if (MACHINE_HAS_VDP_9918A) {
		alto=11;

        if (MACHINE_IS_SMS) {
            //Para que quepa el show column 0, etc
            alto=21;
            ancho=32;
        }
	}

    x=menu_center_x()-ancho/2;
	y=menu_center_y()-alto/2;

	zxvision_window ventana;

	zxvision_new_window(&ventana,x,y,ancho,alto,
							ancho-1,alto-2,"Video Layers");
	zxvision_draw_window(&ventana);		





    //Cambiamos funcion overlay de texto de menu
    set_menu_overlay_function(menu_tsconf_layer_overlay);

	menu_tsconf_layer_overlay_window=&ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui	

    menu_item *array_menu_tsconf_layer_settings;
    menu_item item_seleccionado;
    int retorno_menu;						

    do {

		//Valido tanto para cuando multitarea es off y para que nada mas entrar aqui, se vea, sin tener que esperar el medio segundo 
		//que he definido en el overlay para que aparezca
		menu_tsconf_layer_overlay_mostrar_texto();

        int lin=1;

		if (MACHINE_IS_TSCONF) {

 			menu_add_item_menu_inicial_format(&array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tsconf_layer_settings_border,NULL,"%s",(tsconf_force_disable_layer_border.v ? "Disabled" : "Enabled "));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,1,lin);
			lin+=3;			

			menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tsconf_layer_settings_ula,NULL,"%s",(tsconf_force_disable_layer_ula.v ? "Disabled" : "Enabled "));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,1,lin);
			menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tsconf_layer_reveal_ula,NULL,"%s",(tsconf_reveal_layer_ula.v ? "Reveal" : "Normal"));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,12,lin);		
			lin+=3;

			menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tsconf_layer_settings_sprites_zero,NULL,"%s",(tsconf_force_disable_layer_sprites_zero.v ? "Disabled" : "Enabled "));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,1,lin);
			menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tsconf_layer_reveal_sprites_zero,NULL,"%s",(tsconf_reveal_layer_sprites_zero.v ? "Reveal" : "Normal"));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,12,lin);				
			lin+=3;

			menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tsconf_layer_settings_tiles_zero,NULL,"%s",(tsconf_force_disable_layer_tiles_zero.v ? "Disabled" : "Enabled "));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,1,lin);
			menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tsconf_layer_reveal_tiles_zero,NULL,"%s",(tsconf_reveal_layer_tiles_zero.v ? "Reveal" : "Normal"));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,12,lin);						
			lin+=3;

			menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tsconf_layer_settings_sprites_one,NULL,"%s",(tsconf_force_disable_layer_sprites_one.v ? "Disabled" : "Enabled "));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,1,lin);
			menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tsconf_layer_reveal_sprites_one,NULL,"%s",(tsconf_reveal_layer_sprites_one.v ? "Reveal" : "Normal"));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,12,lin);					
			lin+=3;

			menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tsconf_layer_settings_tiles_one,NULL,"%s",(tsconf_force_disable_layer_tiles_one.v ? "Disabled" : "Enabled "));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,1,lin);
			menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tsconf_layer_reveal_tiles_one,NULL,"%s",(tsconf_reveal_layer_tiles_one.v ? "Reveal" : "Normal"));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,12,lin);				
			lin+=3;

			menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tsconf_layer_settings_sprites_two,NULL,"%s",(tsconf_force_disable_layer_sprites_two.v ? "Disabled" : "Enabled "));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,1,lin);
			menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tsconf_layer_reveal_sprites_two,NULL,"%s",(tsconf_reveal_layer_sprites_two.v ? "Reveal" : "Normal"));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,12,lin);					
			lin+=3;

		}

		if (MACHINE_IS_TBBLUE) {
 			menu_add_item_menu_inicial_format(&array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tbblue_layer_settings_ula,NULL,"%s",(tbblue_force_disable_layer_ula.v ? "Disabled" : "Enabled "));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,1,lin);		
			lin+=3;			

 			menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tbblue_layer_settings_tilemap,NULL,"%s",(tbblue_force_disable_layer_tilemap.v ? "Disabled" : "Enabled "));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,1,lin);			
			lin+=2;

 			menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tbblue_layer_reveal_ula,NULL,"%s",(tbblue_reveal_layer_ula.v ? "Reveal" : "Normal"));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,12,lin);	

			lin+=3;					

			menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tbblue_layer_settings_sprites,NULL,"%s",(tbblue_force_disable_layer_sprites.v ? "Disabled" : "Enabled "));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,1,lin);
 			menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tbblue_layer_reveal_sprites,NULL,"%s",(tbblue_reveal_layer_sprites.v ? "Reveal" : "Normal"));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,12,lin);				
			lin+=3;

			menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tbblue_layer_settings_layer_two,NULL,"%s",(tbblue_force_disable_layer_layer_two.v ? "Disabled" : "Enabled "));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,1,lin);
 			menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_tbblue_layer_reveal_layer2,NULL,"%s",(tbblue_reveal_layer_layer2.v ? "Reveal" : "Normal"));
			menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,12,lin);				
			lin+=3;				
		}

        if (MACHINE_HAS_VDP_9918A) {

            //if (!vdp_9918a_si_sms_video_mode4()) {
            if (!MACHINE_IS_SMS) {

                menu_add_item_menu_inicial_format(&array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_msx_layer_settings_border,NULL,"%s",(vdp_9918a_force_disable_layer_border.v ? "Disabled" : "Enabled "));
                menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,1,lin);
                lin+=3;			

                menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_msx_layer_settings_ula,NULL,"%s",(vdp_9918a_force_disable_layer_ula.v ? "Disabled" : "Enabled "));
                menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,1,lin);
                menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_msx_layer_reveal_ula,NULL,"%s",(vdp_9918a_reveal_layer_ula.v ? "Reveal" : "Normal"));
                menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,12,lin);		
                lin+=3;

                menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_msx_layer_settings_sprites,NULL,"%s",(vdp_9918a_force_disable_layer_sprites.v ? "Disabled" : "Enabled "));
                menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,1,lin);
                menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_msx_layer_reveal_sprites,NULL,"%s",(vdp_9918a_reveal_layer_sprites.v ? "Reveal" : "Normal"));
                menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,12,lin);				
                lin+=3;

            }

            else {
                menu_add_item_menu_inicial_format(&array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_msx_layer_settings_border,NULL,"%s",(vdp_9918a_force_disable_layer_border.v ? "Disabled" : "Enabled "));
                menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,1,lin);
                lin+=3;			

                menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_sms_layer_settings_tile_bg,NULL,"%s",(vdp_9918a_force_disable_layer_tile_bg.v ? "Disabled" : "Enabled "));
                menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,1,lin);
                menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_sms_layer_reveal_tile_bg,NULL,"%s",(vdp_9918a_reveal_layer_tile_bg.v ? "Reveal" : "Normal"));
                menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,12,lin);		
                lin+=3;



                    menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_sms_layer_settings_tile_fg,NULL,"%s",(vdp_9918a_force_disable_layer_tile_fg.v ? "Disabled" : "Enabled "));
                    menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,1,lin);
                    menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_sms_layer_reveal_tile_fg,NULL,"%s",(vdp_9918a_reveal_layer_tile_fg.v ? "Reveal" : "Normal"));
                    menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,12,lin);	
                    menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_sms_layer_force_bg_tiles,NULL,"%s",(vdp_9918a_force_bg_tiles.v ? "AlwaysBack": "Normal    " ));
                    menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,20,lin);	
                    lin+=3;            
                

                menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_msx_layer_settings_sprites,NULL,"%s",(vdp_9918a_force_disable_layer_sprites.v ? "Disabled" : "Enabled "));
                menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,1,lin);
                menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_msx_layer_reveal_sprites,NULL,"%s",(vdp_9918a_reveal_layer_sprites.v ? "Reveal" : "Normal"));
                menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,12,lin);				
                lin+=3;


                //vdp_9918a_sms_force_show_column_zero
                menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_sms_layer_settings_force_col0,NULL,"%s",(vdp_9918a_sms_force_show_column_zero.v ? "Forced" : "Normal"));
                menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,22,lin);
                lin+=2;		                

                menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_sms_layer_settings_lock_scroll_horiz,NULL,"%s",(vdp_9918a_sms_lock_scroll_horizontal.v ? "Locked" : "Normal"));
                menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,22,lin);
                lin+=2;		   

                menu_add_item_menu_format(array_menu_tsconf_layer_settings,MENU_OPCION_NORMAL,menu_sms_layer_settings_lock_scroll_vert,NULL,"%s",(vdp_9918a_sms_lock_scroll_vertical.v ? "Locked" : "Normal"));
                menu_add_item_menu_tabulado(array_menu_tsconf_layer_settings,22,lin);
                lin+=2;	                             

                
            }

        }
				

        retorno_menu=menu_dibuja_menu(&tsconf_layer_settings_opcion_seleccionada,&item_seleccionado,array_menu_tsconf_layer_settings,"TSConf Layers" );

	//En caso de menus tabulados, es responsabilidad de este de borrar la ventana
        cls_menu_overlay();

				//Nombre de ventana solo aparece en el caso de stdout
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
				//En caso de menus tabulados, es responsabilidad de este de borrar la ventana
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);

       //restauramos modo normal de texto de menu
       set_menu_overlay_function(normal_overlay_texto_menu);

        //En caso de menus tabulados, suele ser necesario esto. Si no, la ventana se quedaria visible
	   cls_menu_overlay();

	//En caso de menus tabulados, es responsabilidad de este de liberar ventana
	zxvision_destroy_window(&ventana);			   


}







#define TOTAL_PALETTE_WINDOW_X (menu_origin_x() )
#define TOTAL_PALETTE_WINDOW_Y 0
#define TOTAL_PALETTE_WINDOW_ANCHO 32
#define TOTAL_PALETTE_WINDOW_ALTO 24
//#define TOTAL_PALETTE_COLORS_PER_WINDOW 16



int menu_display_total_palette_current_palette=0;
int menu_display_total_palette_current_colour=0;

//Si se muestra paleta total o paleta mapeada
int menu_display_total_palette_show_mapped=0;

//Retorna colores totales de una paleta ya sea total o mapeada
int menu_display_total_palette_get_total_colors(void)
{
	int limite;

	if (menu_display_total_palette_show_mapped==0) {
		limite=total_palette_colours_array[menu_display_total_palette_current_palette].total_colores;
	}
	else {
		limite=menu_debug_sprites_total_colors_mapped_palette(menu_display_total_palette_current_palette);
	}

	return limite;
}

zxvision_window *menu_display_total_palette_draw_barras_window;

//Indica si se esta pulsando boton de raton en ventana de Colour Palette
//esto indica posiblemente movimiento o redimensionado de dicha ventana
//en esos casos, mientras se redimensiona, no interesa redibujar todo el contenido
//pues consume mucha cpu y no acaba viendose como se redimensiona
//Esto logicamente no es perfecto pues simplemente pulsando con el raton dentro de la ventana,
//se pensara que se redimensiona y por tanto no dibujara el contenido
int window_colour_palette_left_mouse=0;

//Muestra lista de colores o barras de colores, para una paleta total, o para la paleta mapeada
int menu_display_total_palette_lista_colores(int linea,int si_barras)
{
    

    //Redibujar esto solo si no estamos redimensionando o arrastrando ventana
    //esto solo lo hago para evitar sobrecargar la cpu y provocaria que no muestra nada al redimensionar
    if (!window_colour_palette_left_mouse) {

	char dumpmemoria[33];

	int linea_color;
	int limite;


	limite=menu_display_total_palette_get_total_colors();

	int current_color;
	int indice_paleta;
	int indice_color_final_rgb;
	int color_final_rgb;

    int total_colores_mostrar;

    //total_colores_mostrar=TOTAL_PALETTE_COLORS_PER_WINDOW;

    //Con total visible 24, 16 colores 

    total_colores_mostrar=(menu_display_total_palette_draw_barras_window->visible_height)-8;

    //por si acaso
    if (total_colores_mostrar<1) total_colores_mostrar=1;    

		for (linea_color=0;linea_color<total_colores_mostrar &&
				menu_display_total_palette_current_colour+linea_color<limite;
				linea_color++) {

					current_color=menu_display_total_palette_current_colour+linea_color;

					int digitos_hexa;
					int digitos_dec;

					digitos_dec=menu_debug_get_total_digits_dec(limite-1);



					if (menu_display_total_palette_show_mapped==0) {

						indice_paleta=total_palette_colours_array[menu_display_total_palette_current_palette].indice_inicial;
						indice_color_final_rgb=indice_paleta+current_color;
						color_final_rgb=spectrum_colortable_normal[indice_color_final_rgb];



						sprintf (dumpmemoria,"%*d: RGB %06XH",digitos_dec,current_color,color_final_rgb);
					}

					else {
						indice_paleta=menu_debug_sprites_return_index_palette(menu_display_total_palette_current_palette, current_color);
						indice_color_final_rgb=menu_debug_sprites_return_color_palette(menu_display_total_palette_current_palette,current_color);
						color_final_rgb=spectrum_colortable_normal[indice_color_final_rgb];
						digitos_hexa=menu_debug_get_total_digits_hexa((menu_debug_sprites_max_value_mapped_palette(menu_display_total_palette_current_palette))-1);

						int no_mostrar_indice=0;

						//Spectra ni speccy base no usan tabla de paleta
						if (menu_display_total_palette_current_palette==2 || menu_display_total_palette_current_palette==0) no_mostrar_indice=1;

						if (no_mostrar_indice) {
							sprintf (dumpmemoria,"%*d: RGB %06XH",digitos_dec,indice_paleta,color_final_rgb);
						}
						else {
							sprintf (dumpmemoria,"%*d: %0*XH RGB %06XH",digitos_dec,current_color,digitos_hexa,indice_paleta,color_final_rgb);
						}

					}



					int longitud_texto=strlen(dumpmemoria);

					//int posicion_barra_color_x=TOTAL_PALETTE_WINDOW_X+longitud_texto+2;
					//int posicion_barra_color_y=TOTAL_PALETTE_WINDOW_Y+3+linea_color;
					int posicion_barra_color_x=longitud_texto+2;
					int posicion_barra_color_y=3+linea_color;					

					//dibujar la barra de color
					if (si_barras) {
                        int ancho_ventana;

                        ancho_ventana=menu_display_total_palette_draw_barras_window->visible_width;

                        //por si acaso
                        if (ancho_ventana<1) ancho_ventana=1;

                        //printf("ancho: %d\n",ancho_ventana);

						menu_dibuja_rectangulo_relleno(menu_display_total_palette_draw_barras_window,posicion_barra_color_x*menu_char_width,posicion_barra_color_y*8,
											menu_char_width*(ancho_ventana-longitud_texto-3),8,indice_color_final_rgb);
					}

			 		else {
						//menu_escribe_linea_opcion(linea++,-1,1,dumpmemoria);
						zxvision_print_string_defaults_fillspc(menu_display_total_palette_draw_barras_window,1,linea++,dumpmemoria);
					}
		}


    }


	zxvision_draw_window_contents(menu_display_total_palette_draw_barras_window);
 

	return linea;
}




void menu_display_total_palette_draw_barras(void)
{
    //printf("redibujando\n");
    //if (mouse_is_dragging) printf("arrastrando\n");


    menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech


    //Mostrar lista colores
    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (!menu_display_total_palette_draw_barras_window->is_minimized) {
        //printf("Overlay display palettes0 %d\n",contador_segundo); 
        menu_display_total_palette_lista_colores(TOTAL_PALETTE_WINDOW_Y+3,0);
    }

    //Esto tiene que estar despues de escribir la lista de colores, para que se refresque y se vea
    //Si estuviese antes, al mover el cursor hacia abajo dejándolo pulsado, el texto no se vería hasta que no se soltase la tecla
    if (!zxvision_drawing_in_background) normal_overlay_texto_menu();

    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_display_total_palette_draw_barras_window->is_minimized) return;  

    //printf("Overlay display palettes %d\n",contador_segundo);                                  

    if (si_complete_video_driver()) {
        //Mostrar colores
        menu_display_total_palette_lista_colores(0,1);
    }
}

void menu_display_total_palette_cursor_arriba(void)
{
	if (menu_display_total_palette_current_colour>0) {
		menu_display_total_palette_current_colour--;
	}
}

void menu_display_total_palette_cursor_abajo(void)
{

	int limite=menu_display_total_palette_get_total_colors();

	if (menu_display_total_palette_current_colour<limite-1) {
		menu_display_total_palette_current_colour++;
	}

}

void menu_display_total_palette_crea_ventana(zxvision_window *ventana,int xventana,int yventana,int ancho_ventana,int alto_ventana,
    int is_minimized,int is_maximized,int ancho_antes_minimize,int alto_antes_minimize)
{
    //zxvision_new_window(ventana,xventana,yventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,"Colour palettes");

    zxvision_new_window_gn_cim(ventana,xventana,yventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,"Colour palettes",
        "displaypalettes",is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);

	ventana->can_be_backgrounded=1;
    //Permitir hotkeys desde raton
    ventana->can_mouse_send_hotkeys=1;	    
	//indicar nombre del grabado de geometria
	//strcpy(ventana->geometry_name,"displaypalettes");
    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;    

    //decimos que tiene que borrar fondo cada vez al redibujar
    //por tanto es como decirle que no use cache de putchar
    //dado que el fondo de texto es casi todo texto con caracter " " eso borra los pixeles que metemos con overlay del frame anterior
    ventana->must_clear_cache_on_draw=1;        
}

zxvision_window zxvision_window_display_palettes;


void menu_display_total_palette(MENU_ITEM_PARAMETERS)
{
	menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();		

	//zxvision_window ventana;

    zxvision_window *ventana;
    ventana=&zxvision_window_display_palettes;	

	//IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
	//si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
	//la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
	zxvision_delete_window_if_exists(ventana);	


	int xventana,yventana,ancho_ventana,alto_ventana,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;

	if (!util_find_window_geometry("displaypalettes",&xventana,&yventana,&ancho_ventana,&alto_ventana,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
		xventana=TOTAL_PALETTE_WINDOW_X;
		yventana=TOTAL_PALETTE_WINDOW_Y;
		ancho_ventana=TOTAL_PALETTE_WINDOW_ANCHO;
		alto_ventana=TOTAL_PALETTE_WINDOW_ALTO;
	}

    //guardar tamanyo inicial para cuando se recrea la ventana indicarlo como tamanyo de antes minimizado
    //int ancho_ventana_inicial=ancho_ventana;
    //int alto_ventana_inicial=alto_ventana;


    menu_display_total_palette_crea_ventana(ventana,xventana,yventana,ancho_ventana,alto_ventana,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);
    

    //Para poder controlar redimensionamientos de ventana y recrearla de nuevo
    //No es necesario, pero es mas bonito... asi se recrea la ventana, si era muy pequeña, hacerla mas grande
    //garantiza que se podra leer todo el texto
    //int alto_anterior=alto_ventana;
    //int ancho_anterior=ancho_ventana;
    //Ya NO hace falta esto, pues zxvision ya recrea la ventana al ampliarla

    //int alto_anterior;
    //int ancho_anterior;

    //zxvision_window_save_size(ventana,&ancho_anterior,&alto_anterior);


	zxvision_draw_window(ventana);

	z80_byte tecla;


	int salir=0;


	set_menu_overlay_function(menu_display_total_palette_draw_barras);
	menu_display_total_palette_draw_barras_window=ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui


    //Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
    //Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
    if (zxvision_currently_restoring_windows_on_start) {
            //printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
            return;
    }	

    do {

        int total_colores_por_ventana=(ventana->visible_height)-8;

        //por si acaso
        if (total_colores_por_ventana<1) total_colores_por_ventana=1;

    //Redibujar esto solo si no estamos redimensionando o arrastrando ventana
    //esto solo lo hago para evitar sobrecargar la cpu y provocaria que no muestra nada al redimensionar
    if (!mouse_left) {
        window_colour_palette_left_mouse=0;

 		//Borramos lista de colores con espacios por si hay estos de antes

        //Forzar a mostrar atajos
        z80_bit antes_menu_writing_inverse_color;
        antes_menu_writing_inverse_color.v=menu_writing_inverse_color.v;
        menu_writing_inverse_color.v=1;		


		
		int i;
		for (i=0;i<total_colores_por_ventana;i++) zxvision_print_string_defaults_fillspc(ventana,0,TOTAL_PALETTE_WINDOW_Y+3+i,"");

        menu_speech_tecla_pulsada=0; //Que envie a speech

		int linea=0;

		char textoshow[64];

		char nombre_paleta[33];

		if (menu_display_total_palette_show_mapped==0) {
			strcpy(nombre_paleta,total_palette_colours_array[menu_display_total_palette_current_palette].nombre_paleta);
		}
		else {
			menu_debug_sprites_get_palette_name(menu_display_total_palette_current_palette,nombre_paleta);
		}

		sprintf (textoshow,"Palette %d: %s",menu_display_total_palette_current_palette,nombre_paleta);
       	
		zxvision_print_string_defaults_fillspc(ventana,1,linea++,textoshow);

		if (menu_display_total_palette_show_mapped==0) {
			sprintf (textoshow,"%s",total_palette_colours_array[menu_display_total_palette_current_palette].descripcion_paleta);
		}
		else {
			sprintf (textoshow,"Total colours in array: %d",menu_display_total_palette_get_total_colors() );
		}
		
		zxvision_print_string_defaults_fillspc(ventana,1,linea++,textoshow);

   		
		zxvision_print_string_defaults_fillspc(ventana,1,linea++,"");

		
		linea +=16;



		zxvision_print_string_defaults_fillspc(ventana,1,linea++,"");

		char buffer_linea[40];

        //Nos situamos justo despues de la lisa de colores
		linea=TOTAL_PALETTE_WINDOW_Y+total_colores_por_ventana+3;

        //Y meter una linea en blanco
        zxvision_print_string_defaults(ventana,1,linea++,"");

															// 01234567890123456789012345678901
		sprintf (buffer_linea,"Move: Cursors,Q,A,PgUp,PgDn");

		
		zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);

		sprintf (buffer_linea,"[%c] ~~Mapped palette",(menu_display_total_palette_show_mapped ? 'X' : ' ') );
		
		zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);

        //Restaurar comportamiento atajos
        menu_writing_inverse_color.v=antes_menu_writing_inverse_color.v;

		zxvision_draw_window_contents(ventana);

    }

    else {
        window_colour_palette_left_mouse=1;
    }


			
		tecla=zxvision_common_getkey_refresh();		

        //printf("lee tecla %d\n",contador_segundo);

		int aux_pgdnup;
		int limite;

				switch (tecla) {

					case 11:
						//arriba
						menu_display_total_palette_cursor_arriba();

						
					break;

					case 10:
						//abajo
						menu_display_total_palette_cursor_abajo();



					break;

					case 24:
						//PgUp
						for (aux_pgdnup=0;aux_pgdnup<total_colores_por_ventana;aux_pgdnup++) {
							menu_display_total_palette_cursor_arriba();
						}

					break;

					case 25:
						//PgDn
						for (aux_pgdnup=0;aux_pgdnup<total_colores_por_ventana;aux_pgdnup++) {
							menu_display_total_palette_cursor_abajo();
						}
					
					break;

					case 'q':
						if (menu_display_total_palette_current_palette>0) {
							menu_display_total_palette_current_palette--;
							menu_display_total_palette_current_colour=0;
						}

						
					break;

					case 'a':
						if (menu_display_total_palette_show_mapped==0) {
							limite=TOTAL_PALETAS_COLORES;
						}

						else {
							limite=MENU_TOTAL_MAPPED_PALETTES;
						}

						if (menu_display_total_palette_current_palette<limite-1) {
							menu_display_total_palette_current_palette++;
							menu_display_total_palette_current_colour=0;
						}


					break;

					case 'm':
						menu_display_total_palette_show_mapped ^=1;
						menu_display_total_palette_current_palette=0;
						menu_display_total_palette_current_colour=0;
					
					break;


					//Salir con ESC
					case 2:
						salir=1;
					break;

					//O tecla background
					case 3:
						salir=1;
					break;					
				}

                //Si ha cambiado el tamaño
                //Ya NO hace falta esto, pues zxvision ya recrea la ventana al ampliarla
                /*
                alto_ventana=ventana->visible_height;
                ancho_ventana=ventana->visible_width;
                xventana=ventana->x;
                yventana=ventana->y;
                if (alto_ventana!=alto_anterior || ancho_ventana!=ancho_anterior) {
                        //printf ("recrear ventana\n");
                        //Recrear ventana
                        int is_minimized=ventana->is_minimized;

                        //printf("is minimized: %d\n",is_minimized);
                        

                        zxvision_destroy_window(ventana);

                        alto_anterior=alto_ventana;
                        ancho_anterior=ancho_ventana;

                        menu_display_total_palette_crea_ventana(ventana,xventana,yventana,ancho_ventana,alto_ventana,is_minimized,ancho_antes_minimize,alto_antes_minimize);
                        

                        zxvision_window_save_size(ventana,&ancho_anterior,&alto_anterior);

                        zxvision_draw_window(ventana);

                        //Indicar tamanyo de antes minimizado, que es el que tenia al inicio
                        //dado que se recrea la ventana siempre que cambia tamaño (y si se minimiza tambien),
                        //queremos que se indique el tamaño que tenia antes de minimizar por si se deshace el minimizado
                        //ventana->height_before_max_min_imize=alto_ventana_inicial;
                        //ventana->width_before_max_min_imize=ancho_ventana_inicial;
                        
                }        
                */        


        } while (salir==0);

    //Asegurarnos que al salir esto no queda activado, si no, el overlay no dibujaria nada
    window_colour_palette_left_mouse=0;

	//Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
	zxvision_set_window_overlay_from_current(ventana);		

				//restauramos modo normal de texto de menu
    set_menu_overlay_function(normal_overlay_texto_menu);


	cls_menu_overlay();
	util_add_window_geometry_compact(ventana);

	if (tecla==3) {
		zxvision_message_put_window_background();
	}

	else {

		zxvision_destroy_window(ventana);
	}


}

void menu_debug_disassemble_export(int p)
{

	char string_address[10];
	sprintf (string_address,"%XH",p);


    menu_ventana_scanf("Start?",string_address,10);

	menu_z80_moto_int inicio=parse_string_to_number(string_address);

	menu_ventana_scanf("End?",string_address,10);
	menu_z80_moto_int final=parse_string_to_number(string_address);

	if (final<inicio){
		menu_warn_message("End address must be higher or equal than start address");
		return;
	}

	char file_save[PATH_MAX];	
	int ret=menu_ask_file_to_save("Destination file","asm",file_save);

	if (!ret) {
		menu_warn_message("Export cancelled");
		return;
	}


	FILE *ptr_asmfile;
    ptr_asmfile=fopen(file_save,"wb");
    if (!ptr_asmfile) {
		debug_printf (VERBOSE_ERR,"Unable to open asm file");
		return;
    }
                  
 
	char dumpassembler[65];


	int longitud_opcode;

	//ponemos un final de un numero maximo de instrucciones
	//sera igual al tamaño de la zona de memoria
	int limite_instrucciones=menu_debug_memory_zone_size;

	int instrucciones=0;

	for (;inicio<=final && instrucciones<limite_instrucciones;instrucciones++) {

		menu_debug_dissassemble_una_inst_sino_hexa(dumpassembler,inicio,&longitud_opcode,0,0);


		inicio +=longitud_opcode;
		debug_printf (VERBOSE_DEBUG,"Exporting asm: %s",dumpassembler);

		//Agregar salto de linea
		int longitud_linea=strlen(dumpassembler);
		dumpassembler[longitud_linea++]='\n';
		dumpassembler[longitud_linea]=0;
		fwrite(&dumpassembler,1,longitud_linea,ptr_asmfile);
		//zxvision_print_string_defaults_fillspc(&ventana,1,linea,dumpassembler);
	}	

	fclose(ptr_asmfile);

	menu_generic_message_splash("Export disassembly","Ok process finished");

}

z80_bit menu_debug_disassemble_hexa_view={0};

void menu_debug_disassemble(MENU_ITEM_PARAMETERS)
{

	//printf ("Opening disassemble menu\n");
 	menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();		

	zxvision_window ventana;

	int ancho_total=32-1;

	if (CPU_IS_MOTOROLA) ancho_total=64-1;

    int ancho_visible=32;
    int alto_visible=20;

    int xventana=menu_center_x()-ancho_visible/2;
    int yventana=menu_center_y()-alto_visible/2;    

	zxvision_new_window(&ventana,xventana,yventana,ancho_visible,alto_visible,
							ancho_total,alto_visible-2,"Disassemble");


	//Permitir hotkeys desde raton
	ventana.can_mouse_send_hotkeys=1;

	zxvision_draw_window(&ventana);			

    //Inicializar info de tamanyo zona
	menu_debug_set_memory_zone_attr();



	z80_byte tecla;

    
    menu_z80_moto_int direccion=menu_debug_disassemble_last_ptr;
		

	do {
		int linea=0;

		int lineas_disass=0;
		const int lineas_total=15;

		char dumpassembler[65];

		int longitud_opcode;
		int longitud_opcode_primera_linea;

		menu_z80_moto_int dir=direccion;

		for (;lineas_disass<lineas_total;lineas_disass++,linea++) {

			//Formato de texto en buffer:
			//0123456789012345678901234567890
			//DDDD AABBCCDD OPCODE-----------
			//DDDD: Direccion
			//AABBCCDD: Volcado hexa

			//Metemos 30 espacios
		


			//menu_debug_dissassemble_una_instruccion(dumpassembler,dir,&longitud_opcode);
			menu_debug_dissassemble_una_inst_sino_hexa(dumpassembler,dir,&longitud_opcode,menu_debug_disassemble_hexa_view.v,1);


			if (lineas_disass==0) longitud_opcode_primera_linea=longitud_opcode;

			dir +=longitud_opcode;
			zxvision_print_string_defaults_fillspc(&ventana,1,linea,dumpassembler);
		}


	//Forzar a mostrar atajos
	z80_bit antes_menu_writing_inverse_color;
	antes_menu_writing_inverse_color.v=menu_writing_inverse_color.v;
	menu_writing_inverse_color.v=1;



    zxvision_print_string_defaults_fillspc(&ventana,1,linea++,"");

    zxvision_print_string_defaults_fillspc(&ventana,1,linea++,"~~memptr ~~export");
    zxvision_print_string_defaults_fillspc(&ventana,1,linea++,"~~togglehexa");

    zxvision_draw_window_contents(&ventana);


	//Restaurar comportamiento atajos
	menu_writing_inverse_color.v=antes_menu_writing_inverse_color.v;




		tecla=zxvision_common_getkey_refresh();				

                     
		int i;

        switch (tecla) {

			case 11:
				//arriba
				direccion=menu_debug_disassemble_subir(direccion);
			break;

			case 10:
				//abajo
				direccion +=longitud_opcode_primera_linea;
			break;

			//No llamamos a zxvision_handle_cursors_pgupdn para solo poder gestionar scroll ventana en horizontal,
			//el resto de teclas (cursores, pgup, dn etc) las gestionamos desde aqui de manera diferente

            //izquierda
            case 8:
				/*
				//Decir que se ha pulsado tecla para que no se relea
				menu_speech_tecla_pulsada=1;*/
				zxvision_handle_cursors_pgupdn(&ventana,tecla);
            break;

            //derecha
            case 9:
				/*
				//Decir que se ha pulsado tecla para que no se relea
				menu_speech_tecla_pulsada=1;*/
				zxvision_handle_cursors_pgupdn(&ventana,tecla);
			break;					

			case 24:
				//PgUp
				for (i=0;i<lineas_total;i++) direccion=menu_debug_disassemble_subir(direccion);
			break;

			case 25:
				//PgDn
				direccion=dir;
			break;

			case 'm':
				//Usamos misma funcion de menu_debug_hexdump_change_pointer
				direccion=menu_debug_hexdump_change_pointer(direccion);
				zxvision_draw_window(&ventana);
			break;

			case 'e':
				menu_debug_disassemble_export(direccion);
				zxvision_draw_window(&ventana);
			break;

			case 't':
				menu_debug_disassemble_hexa_view.v ^=1;
			break;

		}


	} while (tecla!=2); 


    cls_menu_overlay();
	zxvision_destroy_window(&ventana);		

 

}


void menu_debug_assemble(MENU_ITEM_PARAMETERS)
{

	//printf ("Opening disassemble menu\n");
 	menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();		

	zxvision_window ventana;

	int ancho_total=32-1;

	if (CPU_IS_MOTOROLA) ancho_total=64-1;

    int ancho_visible=32;
    int alto_visible=20;

    int xventana=menu_center_x()-ancho_visible/2;
    int yventana=menu_center_y()-alto_visible/2;

	zxvision_new_window(&ventana,xventana,yventana,ancho_visible,alto_visible,
							ancho_total,alto_visible-2,"Assemble");
	zxvision_draw_window(&ventana);			

    //Inicializar info de tamanyo zona
	menu_debug_set_memory_zone_attr();


    
    menu_z80_moto_int direccion=menu_debug_disassemble_last_ptr;

	menu_z80_moto_int direccion_ensamblado=direccion;

	int salir=0;
	int lineas_ensambladas=0;
		

	do {
		int linea=0;

		int lineas_disass=0;
		const int lineas_total=15;

		char dumpassembler[65];

		int longitud_opcode;
		int longitud_opcode_primera_linea;

		menu_z80_moto_int dir=direccion;

		for (;lineas_disass<lineas_total;lineas_disass++,linea++) {

			//Formato de texto en buffer:
			//0123456789012345678901234567890
			//DDDD AABBCCDD OPCODE-----------
			//DDDD: Direccion
			//AABBCCDD: Volcado hexa

			//Metemos 30 espacios
		


			//menu_debug_dissassemble_una_instruccion(dumpassembler,dir,&longitud_opcode);
			menu_debug_dissassemble_una_inst_sino_hexa(dumpassembler,dir,&longitud_opcode,menu_debug_disassemble_hexa_view.v,1);


			if (lineas_disass==0) longitud_opcode_primera_linea=longitud_opcode;

			dir +=longitud_opcode;
			zxvision_print_string_defaults_fillspc(&ventana,1,linea,dumpassembler);
		}


		zxvision_draw_window_contents(&ventana);



		char string_opcode[256];
		string_opcode[0]=0;


		char texto_titulo[256];
		sprintf (texto_titulo,"Assemble at %XH",direccion_ensamblado);

    	menu_ventana_scanf(texto_titulo,string_opcode,256);
		zxvision_draw_window(&ventana);

		if (string_opcode[0]==0) salir=1;
		else {


				z80_byte destino_ensamblado[MAX_DESTINO_ENSAMBLADO];


				int longitud_destino=assemble_opcode(direccion_ensamblado,string_opcode,destino_ensamblado);

				if (longitud_destino==0) {
					menu_error_message("Error. Invalid opcode");
					//escribir_socket_format(misocket,"Error. Invalid opcode: %s\n",texto);
					salir=1;
				}

				else {
					menu_debug_set_memory_zone_attr();
					unsigned int direccion_escribir=direccion_ensamblado;
					int i;
					for (i=0;i<longitud_destino;i++) {
						menu_debug_write_mapped_byte(direccion_escribir++,destino_ensamblado[i]);
					}

				}

				direccion_ensamblado+=longitud_destino;

				lineas_ensambladas++;

				//Desensamblar desde la siguiente instruccion si conviene
				if (lineas_ensambladas>5) {
					direccion +=longitud_opcode_primera_linea;
				}

		}
	
	} while (!salir);


		

    cls_menu_overlay();
	zxvision_destroy_window(&ventana);		

 

}







void menu_tbblue_machine_id(MENU_ITEM_PARAMETERS)
{

	menu_warn_message("Changing the machine id may show the Spectrum Next boot logo, which is NOT allowed. "
		"Please read the License file: https://gitlab.com/thesmog358/tbblue/blob/master/LICENSE.md");

        menu_item *array_menu_tbblue_hardware_id;
        menu_item item_seleccionado;
        int retorno_menu;

		menu_add_item_menu_inicial(&array_menu_tbblue_hardware_id,"",MENU_OPCION_UNASSIGNED,NULL,NULL);

                char buffer_texto[40];

                int i;
				int salir=0;
                for (i=0;i<=255 && !salir;i++) {

					z80_byte machine_id=tbblue_machine_id_list[i].id;
					if (machine_id==255) salir=1;
					else {

                  		sprintf (buffer_texto,"%3d %s",machine_id,tbblue_machine_id_list[i].nombre);

                        menu_add_item_menu_format(array_menu_tbblue_hardware_id,MENU_OPCION_NORMAL,NULL,NULL,buffer_texto);

						//Decir que no es custom 
						menu_add_item_menu_valor_opcion(array_menu_tbblue_hardware_id,0);
					}

				}

				menu_add_item_menu(array_menu_tbblue_hardware_id,"",MENU_OPCION_SEPARADOR,NULL,NULL);

				menu_add_item_menu_format(array_menu_tbblue_hardware_id,MENU_OPCION_NORMAL,NULL,NULL,"Custom");
				//Decir que es custom 
				menu_add_item_menu_valor_opcion(array_menu_tbblue_hardware_id,1);				

                menu_add_item_menu(array_menu_tbblue_hardware_id,"",MENU_OPCION_SEPARADOR,NULL,NULL);
                //menu_add_item_menu(array_menu_tbblue_hardware_id,"ESC Back",MENU_OPCION_NORMAL|MENU_OPCION_ESC,NULL,NULL);
                menu_add_ESC_item(array_menu_tbblue_hardware_id);

                retorno_menu=menu_dibuja_menu(&menu_tbblue_hardware_id_opcion_seleccionada,&item_seleccionado,array_menu_tbblue_hardware_id,"TBBlue machine id" );

                


				if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {

					//Si se pulsa Enter
					//Detectar si es la opcion de custom
					if (item_seleccionado.valor_opcion) {
        				char string_valor[4];
						sprintf (string_valor,"%d",tbblue_machine_id);

		                menu_ventana_scanf("ID?",string_valor,4);

        				tbblue_machine_id=parse_string_to_number(string_valor);

					}

					else {
						tbblue_machine_id=tbblue_machine_id_list[menu_tbblue_hardware_id_opcion_seleccionada].id;
					}
											

												
                }

}






void menu_cpu_transaction_log_enable(MENU_ITEM_PARAMETERS)
{
	if (cpu_transaction_log_enabled.v) {
		reset_cpu_core_transaction_log();
	}
	else {

		if (menu_confirm_yesno_texto("May use a lot of disk space","Sure?")==1) {
			set_cpu_core_transaction_log();
        }
	}
}

void menu_cpu_transaction_log_truncate(MENU_ITEM_PARAMETERS)
{
	if (menu_confirm_yesno("Truncate log file")) {
		transaction_log_truncate();
		menu_generic_message("Truncate log file","OK. Log truncated");
	}
}

void menu_cpu_transaction_log_file(MENU_ITEM_PARAMETERS)
{

	if (cpu_transaction_log_enabled.v) reset_cpu_core_transaction_log();

        char *filtros[2];

        filtros[0]="log";
        filtros[1]=0;


        if (menu_filesel("Select Log File",filtros,transaction_log_filename)==1) {
                //Ver si archivo existe y preguntar
		if (si_existe_archivo(transaction_log_filename)) {
                        if (menu_confirm_yesno_texto("File exists","Append?")==0) {
				transaction_log_filename[0]=0;
				return;
			}
                }

        }

	else transaction_log_filename[0]=0;

}


void menu_cpu_transaction_log_enable_address(MENU_ITEM_PARAMETERS)
{
	cpu_transaction_log_store_address.v ^=1;
}

void menu_cpu_transaction_log_enable_datetime(MENU_ITEM_PARAMETERS)
{
        cpu_transaction_log_store_datetime.v ^=1;
}


void menu_cpu_transaction_log_enable_tstates(MENU_ITEM_PARAMETERS)
{
        cpu_transaction_log_store_tstates.v ^=1;
}

void menu_cpu_transaction_log_enable_opcode(MENU_ITEM_PARAMETERS)
{
        cpu_transaction_log_store_opcode.v ^=1;
}

void menu_cpu_transaction_log_enable_registers(MENU_ITEM_PARAMETERS)
{
        cpu_transaction_log_store_registers.v ^=1;
}


void menu_cpu_transaction_log_enable_rotate(MENU_ITEM_PARAMETERS)
{
	cpu_transaction_log_rotate_enabled.v ^=1;	
}

void menu_cpu_transaction_log_rotate_number(MENU_ITEM_PARAMETERS)
{

        char string_number[4];

        sprintf (string_number,"%d",cpu_transaction_log_rotated_files);

        menu_ventana_scanf("Number of files",string_number,4);

        int numero=parse_string_to_number(string_number);

		if (transaction_log_set_rotate_number(numero)) {
			debug_printf (VERBOSE_ERR,"Invalid rotation number");			
		}


}


void menu_cpu_transaction_log_rotate_size(MENU_ITEM_PARAMETERS)
{


        char string_number[5];

        sprintf (string_number,"%d",cpu_transaction_log_rotate_size);

        menu_ventana_scanf("Size in MB (0=no rot)",string_number,5);

        int numero=parse_string_to_number(string_number);

		if (transaction_log_set_rotate_size(numero)) {
			debug_printf (VERBOSE_ERR,"Invalid rotation size");
		}


}

void menu_cpu_transaction_log_rotate_lines(MENU_ITEM_PARAMETERS)
{


        char string_number[11];

        sprintf (string_number,"%d",cpu_transaction_log_rotate_lines);

        menu_ventana_scanf("Lines (0=no rotate)",string_number,11);

        int numero=parse_string_to_number(string_number);

		if (transaction_log_set_rotate_lines(numero)) {
			debug_printf (VERBOSE_ERR,"Invalid rotation lines");
		}


}

void menu_cpu_transaction_log_ignore_rep_halt(MENU_ITEM_PARAMETERS)
{
	cpu_trans_log_ignore_repeated_halt.v ^=1;
}

void menu_cpu_transaction_log(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_cpu_transaction_log;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

                char string_transactionlog_shown[18];
                menu_tape_settings_trunc_name(transaction_log_filename,string_transactionlog_shown,18);

                menu_add_item_menu_inicial_format(&array_menu_cpu_transaction_log,MENU_OPCION_NORMAL,menu_cpu_transaction_log_file,NULL,"Log file [%s]",string_transactionlog_shown );


                if (transaction_log_filename[0]!=0) {
                        menu_add_item_menu_format(array_menu_cpu_transaction_log,MENU_OPCION_NORMAL,menu_cpu_transaction_log_enable,NULL,"[%c] Transaction log enabled",(cpu_transaction_log_enabled.v ? 'X' : ' ' ) );
						
						menu_add_item_menu_format(array_menu_cpu_transaction_log,MENU_OPCION_NORMAL,menu_cpu_transaction_log_enable_rotate,NULL,"[%c] Autorotate files",(cpu_transaction_log_rotate_enabled.v ? 'X' : ' ' ) );
						menu_add_item_menu_tooltip(array_menu_cpu_transaction_log,"Enable automatic rotation of transaction log files");
						menu_add_item_menu_ayuda(array_menu_cpu_transaction_log,"Enable automatic rotation of transaction log files");
						if (cpu_transaction_log_rotate_enabled.v) {
							menu_add_item_menu_format(array_menu_cpu_transaction_log,MENU_OPCION_NORMAL,menu_cpu_transaction_log_rotate_number,NULL,"[%d] Rotate files",cpu_transaction_log_rotated_files);
							menu_add_item_menu_format(array_menu_cpu_transaction_log,MENU_OPCION_NORMAL,menu_cpu_transaction_log_rotate_size,NULL,"[%d] Rotate size (MB)",cpu_transaction_log_rotate_size);
							menu_add_item_menu_format(array_menu_cpu_transaction_log,MENU_OPCION_NORMAL,menu_cpu_transaction_log_rotate_lines,NULL,"[%d] Rotate lines",cpu_transaction_log_rotate_lines);
						}

						menu_add_item_menu_format(array_menu_cpu_transaction_log,MENU_OPCION_NORMAL,menu_cpu_transaction_log_truncate,NULL,"    Truncate log file");
                }

		menu_add_item_menu_format(array_menu_cpu_transaction_log,MENU_OPCION_NORMAL,menu_cpu_transaction_log_ignore_rep_halt,NULL,"[%c] Ignore repeated halt",(cpu_trans_log_ignore_repeated_halt.v ? 'X' : ' '));


		menu_add_item_menu_format(array_menu_cpu_transaction_log,MENU_OPCION_NORMAL,menu_cpu_transaction_log_enable_datetime,NULL,"[%c] Store Date & Time",(cpu_transaction_log_store_datetime.v ? 'X' : ' '));
		menu_add_item_menu_format(array_menu_cpu_transaction_log,MENU_OPCION_NORMAL,menu_cpu_transaction_log_enable_tstates,NULL,"[%c] Store T-States",(cpu_transaction_log_store_tstates.v ? 'X' : ' '));
		menu_add_item_menu_format(array_menu_cpu_transaction_log,MENU_OPCION_NORMAL,menu_cpu_transaction_log_enable_address,NULL,"[%c] Store Address",(cpu_transaction_log_store_address.v ? 'X' : ' '));
		menu_add_item_menu_format(array_menu_cpu_transaction_log,MENU_OPCION_NORMAL,menu_cpu_transaction_log_enable_opcode,NULL,"[%c] Store Opcode",(cpu_transaction_log_store_opcode.v ? 'X' : ' '));
		menu_add_item_menu_format(array_menu_cpu_transaction_log,MENU_OPCION_NORMAL,menu_cpu_transaction_log_enable_registers,NULL,"[%c] Store Registers",(cpu_transaction_log_store_registers.v ? 'X' : ' '));
		


               menu_add_item_menu(array_menu_cpu_transaction_log,"",MENU_OPCION_SEPARADOR,NULL,NULL);

                menu_add_ESC_item(array_menu_cpu_transaction_log);

                retorno_menu=menu_dibuja_menu(&cpu_transaction_log_opcion_seleccionada,&item_seleccionado,array_menu_cpu_transaction_log,"CPU Transaction Log" );

                

                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);

}



#define SPRITES_X ( menu_origin_x() )
#define SPRITES_Y 0
#define SPRITES_ANCHO 32
#define SPRITES_ALTO 14
//#define SPRITES_ALTO_VENTANA (SPRITES_ALTO+10)
#define SPRITES_ALTO_VENTANA 24

menu_z80_moto_int view_sprites_direccion=0;

//ancho en pixeles
z80_int view_sprites_ancho_sprite=8;

//alto en pixeles
z80_int view_sprites_alto_sprite=8*6;


int view_sprites_hardware=0;

z80_bit view_sprites_inverse={0};

//Incremento al moverse al siguiente byte
//Normalmente 1 , pero quiza poner a 2 para sprites que se guardan como:
//byte sprite, byte mascara, byte sprite, byte mascara
//Asi podemos saltar el byte de mascara
int view_sprite_incremento=1;

//z80_byte temp_pagina=0xF7;

//pixeles por cada byte. Puede ser 8, 4, 2 o 1
int view_sprites_ppb=8;
//en 8ppb (1 bpp), primer color rotar 7, luego 6, luego 5, .... 0 (8-(pos actual+1)*bpp). mascara 1
//en 4ppb (2 bpp), primer color rotar 6, luego 4, luego 2, luego 0 (8-(pos actual+1)*bpp). mascara 3
//en 2ppb (4 bpp), primer color rotar 4, luego 0  (8-(pos actual+1)*bpp). mascara 15
//en 1ppb (8 bpp), rotar 0 . mascara 255  (8-(pos actual+1)*bpp). mascara 255


//bits per pixel. Puede ser 1, 2, 4, 8
int view_sprites_bpp=1;


//Paletas:
//0: normal spectrum y en adelante
//1: la que esté mapeada en ulaplus
//2: la mapeada en tsconf
int view_sprites_palette=0;


//Sprite esta organizado como memoria de pantalla spectrum
int view_sprites_scr_sprite=0;

int view_sprites_offset_palette=0;

//Si leer color sprites y tiles como formato Master System
//Si vale 1 o 2, ordenan diferente el sprite en pantalla
int view_sprites_sms_tiles=0;


//Retorna total de colores de una paleta mapeada
int menu_debug_sprites_total_colors_mapped_palette(int paleta)
{


	switch (paleta) {

		//Speccy
		case 0:
			return 16;
		break;

		//ULAPLUS
		case 1:
			return 64;
		break;

		//Spectra
		case 2:
			return 64;
		break;

		//CPC
		case 3:
			return 16;
		break;

		//Prism zero
		case 4:
			return 256;
		break;

		//Prism two
		case 5:
			return 256;
		break;

		//Sam
		case 6:
			return 16;
		break;

		//RGB8 Tbblue
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
			return 256;
		break;

		//TSConf
		case 15:
			return 256;
		break;

		//msx
		case 16:
			return 16;
		break;		
        
		//zxuno prism (paleta de lo que el usuario ha establecido, que no son los colores finales)
		case 17:
			return 16;
		break;	 

		//zxuno prism (colores finales, a paleta reducida)
		case 18:
			return 16;
		break;	    

		//SMS
		case 19:
			return VDP_9918A_SMS_MODE4_MAPPED_PALETTE_COLOURS;
		break;            

         
	}

	return 16;
}

//Retorna maximo valor para una paleta mapeada, o sea, el total de colores definido en screen.h para esa paleta
int menu_debug_sprites_max_value_mapped_palette(int paleta)
{


	switch (paleta) {

		//Speccy
		case 0:
			return SPECCY_TOTAL_PALETTE_COLOURS;
		break;

		//ULAPLUS
		case 1:
			return ULAPLUS_TOTAL_PALETTE_COLOURS;
		break;

		//Spectra
		case 2:
			return SPECTRA_TOTAL_PALETTE_COLOURS;
		break;

		//CPC
		case 3:
			return CPC_TOTAL_PALETTE_COLOURS;
		break;

		//Prism zero
		case 4:
			return PRISM_TOTAL_PALETTE_COLOURS;
		break;

		//Prism two
		case 5:
			return PRISM_TOTAL_PALETTE_COLOURS;
		break;

		//Sam
		case 6:
			return SAM_TOTAL_PALETTE_COLOURS;
		break;

		//RGB9 Tbblue
		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
			return RGB9_TOTAL_PALETTE_COLOURS;
		break;

		//TSConf
		case 15:
			return TSCONF_TOTAL_PALETTE_COLOURS;
		break;

		//MSX
		case 16:
			return VDP_9918_TOTAL_PALETTE_COLOURS;
		break;		


        //zxuno prism (paleta de lo que el usuario ha establecido, que no son los colores finales)
		case 17:
			return 16777216;
		break;	

		//ZXuno prism (colores finales, a paleta reducida)
		case 18:
			return TSCONF_TOTAL_PALETTE_COLOURS;
		break;	

        case 19:
            return SMS_TOTAL_PALETTE_COLOURS;
        break;        

        

	}

	return 16;
}


//Retorna indice color asociado a la paleta indicada, que apuntara a la tabla spectrum_colortable_normal
int menu_debug_sprites_return_index_palette(int paleta, z80_byte color)
{

    z80_byte r,g,b;

	switch (paleta) {
		case 0:
			//Speccy
			return color;
		break;

		case 1:
			//ULAPlus
			return ulaplus_palette_table[color%64];

		break;

		case 2:
			//Spectra
			return color%64;
		break;

		case 3:
			//CPC
			return cpc_palette_table[color%16];
		break;

		case 4:
			//Prism zero
			return prism_palette_zero[color%256];
		break;

		case 5:
			//Prism two
			return prism_palette_two[color%256];
		break;

		case 6:
			//Sam
			return (  (sam_palette[color&15]) & 127) ;
		break;

		case 7:
			//TBBlue ula paleta 1
			return tbblue_palette_ula_first[color];
		break;

		case 8:
			//TBBlue ula paleta 2
			return tbblue_palette_ula_second[color];
		break;			

		case 9:
			//TBBlue layer2 paleta 1
			return tbblue_palette_layer2_first[color];
		break;

		case 10:
			//TBBlue layer2 paleta 2
			return tbblue_palette_layer2_second[color];
		break;		

		case 11:
			//TBBlue sprites paleta 1
			return tbblue_palette_sprite_first[color];
		break;

		case 12:
			//TBBlue sprites paleta 2
			return tbblue_palette_sprite_second[color];
		break;

		case 13:
			//TBBlue tilemap paleta 1
			return tbblue_palette_tilemap_first[color];
		break;		

		case 14:
			//TBBlue tilemap paleta 2
			return tbblue_palette_tilemap_second[color];
		break;	

		case 15:
			//TSConf
			return tsconf_return_cram_color(color);
		break;

		case 16:
			//MSX
			return color; //Dado que realmente no hay mapeo
		break;		

        //zxuno prism (paleta de lo que el usuario ha establecido, que no son los colores finales)
        case 17:
            r=zxuno_prism_current_palette[color].rgb[0];
            g=zxuno_prism_current_palette[color].rgb[1];
            b=zxuno_prism_current_palette[color].rgb[2];
			return (r<<16)|(g<<8)|b;
		break;	         

		case 18:
			//zxuno prism (colores finales, a paleta reducida)
			return zxuno_prism_current_palette[color].index_palette_15bit;
		break;       


        case 19:
            //SMS Mode 4
            return vdp_9918a_sms_cram[color];
        break; 

       


	}

	return color;
}

//Retorna valor de color asociado a la paleta actual mapeada
int menu_debug_sprites_return_color_palette(int paleta, z80_byte color)
{

	int index;

	index=menu_debug_sprites_return_index_palette(paleta, color);

	switch (paleta) {
		case 0:
			return index;
		break;

		case 1:
			return ULAPLUS_INDEX_FIRST_COLOR+index;
		break;

		case 2:
			return SPECTRA_INDEX_FIRST_COLOR+index;
		break;

		case 3:
			return CPC_INDEX_FIRST_COLOR+index;
		break;

		case 4:
			return PRISM_INDEX_FIRST_COLOR+index;
		break;

		case 5:
			return PRISM_INDEX_FIRST_COLOR+index;
		break;

		case 6:
			return SAM_INDEX_FIRST_COLOR+index;
		break;

		case 7:
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
			return RGB9_INDEX_FIRST_COLOR+index;
		break;

		case 15:
			return TSCONF_INDEX_FIRST_COLOR+index;
		break;

		case 16:
			return VDP_9918_INDEX_FIRST_COLOR+index;
		break;	


        //zxuno prism (paleta de lo que el usuario ha establecido, que no son los colores finales)
        case 17:
            return TSCONF_INDEX_FIRST_COLOR+zxuno_prism_current_palette[color].index_palette_15bit;
        break;

		case 18:
			//zxuno prism (colores finales, a paleta reducida)
			return TSCONF_INDEX_FIRST_COLOR+index;
		break;    

		case 19:
			return SMS_INDEX_FIRST_COLOR+index;
		break;            


	}

	return color;
}



void menu_debug_sprites_change_palette(void)
{
	view_sprites_palette++;
	if (view_sprites_palette==MENU_TOTAL_MAPPED_PALETTES) view_sprites_palette=0;
}

//Obtener nombre de una paleta mapeada
void menu_debug_sprites_get_palette_name(int paleta, char *s)
{
	switch (paleta) {
		case 0:
			strcpy(s,"Speccy");
		break;

		case 1:
			strcpy(s,"ULAPlus");
		break;

		case 2:
			strcpy(s,"Spectra");
		break;

		case 3:
			strcpy(s,"CPC");
		break;

		case 4:
			strcpy(s,"Prism Zero");
		break;

		case 5:
			strcpy(s,"Prism Two");
		break;

		case 6:
			strcpy(s,"Sam Coupe");
		break;

		case 7:
			strcpy(s,"TBBlue ULA 1");
		break;

		case 8:
			strcpy(s,"TBBlue ULA 2");
		break;	

		case 9:
			strcpy(s,"TBBlue Layer2 1");
		break;

		case 10:
			strcpy(s,"TBBlue Layer2 2");
		break;	

		case 11:
			strcpy(s,"TBBlue Sprites 1");
		break;

		case 12:
			strcpy(s,"TBBlue Sprites 2");
		break;			

		case 13:
			strcpy(s,"TBBlue Tilemap 1");
		break;

		case 14:
			strcpy(s,"TBBlue Tilemap 2");
		break;	

		case 15:
			strcpy(s,"TSConf");
		break;

		case 16:
			strcpy(s,"VDP9918A");
		break;


        //(paleta de lo que el usuario ha establecido, que no son los colores finales)
		case 17:
			strcpy(s,"ZX-Uno Prism");
		break;   

        //colores finales, a paleta reducida
		case 18:
			strcpy(s,"ZX-Uno Prism (final)");
		break;       

		case 19:
			strcpy(s,"SMS Mode 4");
		break;          

		default:
			strcpy(s,"UNKNOWN");
		break;



	}
}


void menu_debug_sprites_change_bpp(void)
{
//pixeles por cada byte. Puede ser 8, 4, 2 o 1
//int view_sprites_ppb=8;
//en 8ppb (1 bpp), primer color rotar 7, luego 6, luego 5, .... 0 (8-(pos actual+1)*bpp). mascara 1
//en 4ppb (2 bpp), primer color rotar 6, luego 4, luego 2, luego 0 (8-(pos actual+1)*bpp). mascara 3
//en 2ppb (4 bpp), primer color rotar 4, luego 0  (8-(pos actual+1)*bpp). mascara 15
//en 1ppb (8 bpp), rotar 0 . mascara 255  (8-(pos actual+1)*bpp). mascara 255


//bits per pixel. Puede ser 1, 2, 4, 8
//int view_sprites_bpp=1;
	view_sprites_bpp=view_sprites_bpp <<1;
	view_sprites_ppb=view_sprites_ppb >>1;

	if (view_sprites_bpp>8) {
		view_sprites_bpp=1;
		view_sprites_ppb=8;
	}

	//En algun caso, cambiando de maquina SG1000 a MSX, parece que este view_sprites_ppb llega a ser 0
	//Dado que es un parametro que se utiliza para dividir, hacer que nunca pueda ser cero
	if (view_sprites_ppb==0) view_sprites_ppb=1;

	//printf ("bpp: %d ppb: %d\n",view_sprites_bpp,view_sprites_ppb);
}


menu_z80_moto_int menu_debug_draw_sprites_get_pointer_offset(int direccion)
{

	menu_z80_moto_int puntero;

	puntero=direccion; //por defecto

	if (view_sprites_hardware) {

		if (MACHINE_IS_TSCONF) {
			//view_sprites_direccion-> numero sprite
			struct s_tsconf_debug_sprite spriteinfo;
		
			tsconf_get_debug_sprite(view_sprites_direccion,&spriteinfo);

		        int ancho_linea=256; //512 pixeles a 4bpp
			int tnum_x=spriteinfo.tnum_x;
			int tnum_y=spriteinfo.tnum_y;

	                tnum_x *=8;
        	        tnum_y *=8;

                	//a 4bpp
	                tnum_x /=2;



        	        puntero=(tnum_y*ancho_linea)+tnum_x;
	
		}

		if (MACHINE_IS_TBBLUE) {
			if (view_sprites_bpp==4) puntero=view_sprites_direccion*TBBLUE_SPRITE_4BPP_SIZE;
			else puntero=view_sprites_direccion*TBBLUE_SPRITE_8BPP_SIZE;
		}


		//if (MACHINE_HAS_VDP_9918A) {
		//	puntero=view_sprites_direccion+vdp_9918a_get_pattern_base_address();
		//}

	}


	return puntero;

}

zxvision_window *menu_debug_draw_sprites_window;

int view_sprites_bytes_por_linea=1;
int view_sprites_bytes_por_ventana=1;
int view_sprites_increment_cursor_vertical=1;

z80_bit view_sprites_zx81_pseudohires={0}; //Si utiliza puntero a tabla de la rom, como los usados en juegos hires de zx81 (ejemplo rocketman)

z80_byte menu_debug_draw_sprites_get_byte(menu_z80_moto_int puntero)
{

	//printf ("menu_debug_draw_sprites_get_byte 1\n");
	z80_byte byte_leido;

					puntero=adjust_address_memory_size(puntero);

					//printf ("menu_debug_draw_sprites_get_byte 2\n");
				byte_leido=menu_debug_get_mapped_byte(puntero);
					//printf ("menu_debug_draw_sprites_get_byte 3\n");
				

				//Si hay puntero a valores en rom como algunos juegos pseudo hires de zx81
				if (view_sprites_zx81_pseudohires.v) {
					int temp_inverse=0; //si se hace inverse derivado de juegos pseudo hires de zx81
					if (byte_leido&128) temp_inverse=1;

					z80_int temp_dir=reg_i*256+(8*(byte_leido&63));
					byte_leido=peek_byte_no_time(temp_dir);

					if (temp_inverse) byte_leido ^=255;
				}
	

				if (view_sprites_inverse.v) {
					byte_leido ^=255;
				}

	return byte_leido;
}


void menu_debug_draw_sprites(void)
{

	if (!zxvision_drawing_in_background) normal_overlay_texto_menu();


	menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech	


    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_debug_draw_sprites_window->is_minimized) return;


	//int sx=SPRITES_X+1;
	int sx=1;
	//int sy=SPRITES_Y+3;
	
	//Si es mas ancho, que ventana visible, mover coordenada x 1 posicion atrás
	//if (view_sprites_ancho_sprite/menu_char_width>=SPRITES_ANCHO-2) sx--;

	//Si es mas alto, mover coordenada sprite a 1, asi podemos mostrar sprites de hasta 192 de alto
	//if (view_sprites_alto_sprite>168) sy=1;

	//Si se pasa aun mas
	//if (view_sprites_alto_sprite>184) sy=0;

        int xorigen=sx*menu_char_width;
        
		int yorigen=16; //sy*8;


        int x,y,bit;
	z80_byte byte_leido;

	menu_z80_moto_int puntero;

	//puntero=view_sprites_direccion;

	//Ajustar valor puntero en caso de sprites tsconf por ejemplo
	puntero=menu_debug_draw_sprites_get_pointer_offset(view_sprites_direccion);


	int color;

	int finalx;

	menu_z80_moto_int puntero_inicio_linea;

	//int maximo_visible_x=32*menu_char_width;



		int tamanyo_linea=view_sprites_bytes_por_linea;

		for (y=0;y<view_sprites_alto_sprite;y++) {
			if (view_sprites_scr_sprite && y<192) {
				 puntero=view_sprites_direccion+screen_addr_table[(y<<5)];
			}

			puntero_inicio_linea=puntero;
			finalx=xorigen;

			menu_z80_moto_int puntero_final;            

            //Para sprites sms modo 4
            z80_byte byte_leido_sms_1,byte_leido_sms_2,byte_leido_sms_3,byte_leido_sms_4;



			for (x=0;x<view_sprites_ancho_sprite;) {
				//printf ("puntero: %d\n",puntero);
				puntero=adjust_address_memory_size(puntero);




				puntero_final=puntero;

                //Hacer esto a cada salto de x 0,8, etc
                if (view_sprites_sms_tiles && (x%8)==0) {
                    //Caso de sprites Master System modo 4

                    if (view_sprites_hardware) {                    
                        //Activado setting de hardware.

                        //Accedemos a la tabla de 64 sprites

                        //menu_z80_moto_int puntero_orig=menu_debug_draw_sprites_get_pointer_offset(view_sprites_direccion);

                        z80_int attribute_table=vdp_9918a_get_sprite_attribute_table();

                        int numero_sprite=menu_debug_draw_sprites_get_pointer_offset(view_sprites_direccion);

                        numero_sprite %=VDP_9918A_SMS_MODE4_MAX_SPRITES;

                        

                        attribute_table +=0x80+numero_sprite*2;

                        //printf ("tabla atributo sprite: %04XH\n",attribute_table);

                        //printf ("antes\n");
                        //Obtener byte 2, sprite name
                        z80_byte sprite_name=menu_debug_draw_sprites_get_byte(attribute_table+1);

                        //printf ("numero sprite: %d sprite name: %d\n",numero_sprite,sprite_name);

                        //Si ancho > 8, a la derecha mostramos el siguiente sprite

                        int offset_sprite=sprite_name;

                        int offset_pattern_table=offset_sprite*32+vdp_9918a_get_sprite_pattern_table_sms_mode4();
                        puntero_final=offset_pattern_table+y*4;
                    }

                    else {
                        //Ejemplo para sprite de ancho 32 y alto 16,
                        //Mostrar el sprite ordenado asi: (Modo "A"). En pantalla lo indica con ">" de flecha derecha
                        //Asi se ve bien en Streets of Rage
                        // 0 1 2 3
                        // 4 5 6 7 
                        //donde 0 es el primer sprite, 1 el segundo, etc

                        //a cada "salto" de columna salta 32 bytes (1 sprite)
                        //a cada "salto" de fila salta (en este ejemplo) 32*4

                        //Modo "B": En pantalla lo indica con "v" de flecha abajo
                        //Asi se ve bien en Sonic
                        // 0 2 4 6
                        // 1 3 5 7

                        //Nota: en caso de sprites de 8x8 sera:
                        // 0 

                        //Y en caso de 8x16 sera:
                        // 0
                        // 1

                        //Por tanto en esos casos no le afecta el modo A o B. En sprites por hardware es 8x8 o 8x16 por tanto da igual el modo A o B
                        //Lo que haremos en ese modo hardware es no mostrar > o v, simplemente activo (X)


                        int fila=y/8;
                        int columna=x/8;

                        int tamanyo_sprite=32;

                        
                        //Usado en modo "A"
                        int sprites_en_fila=view_sprites_ancho_sprite/8;        

                        //Usado en modo "B"
                        int sprites_en_columna=view_sprites_alto_sprite/8;   

                        int offset_sprite;                                     

                        if (view_sprites_sms_tiles==1) {
                            //Donde apunta el principio del sprite. modo A
                            offset_sprite=(fila*sprites_en_fila)+columna;
                        }

                        else {
                            //view_sprites_sms_tiles sera 2
                            //Donde apunta el principio del sprite. modo B
                            offset_sprite=(columna*sprites_en_columna)+fila;
                        }



                        offset_sprite *=tamanyo_sprite;

                        //Aqui estaremos siempre a principio de columna (x divisible entre 8)
                        //sumamos y
                        offset_sprite +=(y & 7)*4;


                        //int incremento_linea=(y/8)+
                        //int offset_linea=(view_sprites_ancho_sprite/8)*32;
                        puntero_final=view_sprites_direccion+offset_sprite;


                        
                    }

                    byte_leido_sms_1=menu_debug_draw_sprites_get_byte(puntero_final++);
                    byte_leido_sms_2=menu_debug_draw_sprites_get_byte(puntero_final++);
                    byte_leido_sms_3=menu_debug_draw_sprites_get_byte(puntero_final++);
                    byte_leido_sms_4=menu_debug_draw_sprites_get_byte(puntero_final++);                        
                    
                }                

				//Alterar en el caso de VDP9918A, que es un tanto particular (sobretodo 16x16)
				if (view_sprites_hardware && MACHINE_HAS_VDP_9918A) {

                    if (!view_sprites_sms_tiles) {

                        //Accedemos a la tabla de 32 sprites

                        //menu_z80_moto_int puntero_orig=menu_debug_draw_sprites_get_pointer_offset(view_sprites_direccion);

                        z80_int attribute_table=vdp_9918a_get_sprite_attribute_table();

                        int numero_sprite=menu_debug_draw_sprites_get_pointer_offset(view_sprites_direccion);

                        numero_sprite %=32;

                        //printf ("numero sprite: %d\n",numero_sprite);

                        attribute_table +=numero_sprite*4;

                        //printf ("tabla atributo sprite: %04XH\n",attribute_table);

                        //printf ("antes\n");
                        //Obtener byte 2, sprite name
                        z80_byte sprite_name=menu_debug_draw_sprites_get_byte(attribute_table+2);


                        //printf ("despues\n");

                        //TODO: asumimos sprites 16x16
                        //TODO: colores del sprite

                        menu_z80_moto_int puntero_orig=sprite_name *8;
                        /*
                        QUADRANT   AC
                                BD

                        Orden en memoria:
                        A   0
                        B   8
                        C   16 
                        D   24
                        */
                        //y<8

                        //Quad A
                        if (y<=7 && x<=7) {
                            puntero_final=puntero_orig+y;
                        }

                        //Quad B
                        else if (y>=8 && y<=15 && x<=7) {
                            puntero_final=puntero_orig+y;
                        }		

                        //Quad C
                        else if (y<=7 && x>=8 && x<=15) {
                            puntero_final=puntero_orig+16+y;
                        }	

                        //Quad D		
                        else  {
                            puntero_final=puntero_orig+16+y;
                        }												

            
                        puntero_final +=vdp_9918a_get_sprite_pattern_table();

                        //printf ("puntero final: %04XH\n",puntero_final);


                    }
		

				}

				byte_leido=menu_debug_draw_sprites_get_byte(puntero_final);

				/*byte_leido=menu_debug_get_mapped_byte(puntero);

				

				//Si hay puntero a valores en rom como algunos juegos pseudo hires de zx81
				if (view_sprites_zx81_pseudohires.v) {
					int temp_inverse=0; //si se hace inverse derivado de juegos pseudo hires de zx81
					if (byte_leido&128) temp_inverse=1;

					z80_int temp_dir=reg_i*256+(8*(byte_leido&63));
					byte_leido=peek_byte_no_time(temp_dir);

					if (temp_inverse) byte_leido ^=255;
				}
	

				if (view_sprites_inverse.v) {
					byte_leido ^=255;
				}
				*/

				puntero +=view_sprite_incremento;

				int incx=0;

                int total_bpp=view_sprites_bpp;

                //para sms, solo hacer este bucle 1 vez
                if (view_sprites_sms_tiles) total_bpp=8;

				for (bit=0;bit<8;bit+=total_bpp,incx++,finalx++,x++) {


				

					int dis=(8-(incx+1)*view_sprites_bpp);

					//printf ("incx: %d dis: %d\n",incx,dis);

					color=byte_leido >> dis;
					z80_byte mascara;
					switch (view_sprites_bpp) {
						case 1:
							mascara=1;
						break;

						case 2:
							mascara=3;
						break;

						case 4:
							mascara=15;
						break;

						case 8:
							mascara=255;
						break;
					}

					color=color & mascara;

				//en 8ppb (1 bpp), primer color rotar 7, luego 6, luego 5, .... 0 (8-(pos actual+1)*bpp). mascara 1
				//en 4ppb (2 bpp), primer color rotar 6, luego 4, luego 2, luego 0 (8-(pos actual+1)*bpp). mascara 3
				//en 2ppb (4 bpp), primer color rotar 4, luego 0  (8-(pos actual+1)*bpp). mascara 15
				//en 1ppb (8 bpp), rotar 0 . mascara 255  (8-(pos actual+1)*bpp). mascara 255

				//Caso 1 bpp
				if (view_sprites_bpp==1) {
                                        if ( color ==0 ) color=ESTILO_GUI_PAPEL_NORMAL;
                                        else color=ESTILO_GUI_TINTA_NORMAL;
				}
				else {
					color=menu_debug_sprites_return_color_palette(view_sprites_palette,color+view_sprites_offset_palette);

				}

                //En el caso de modo sms sprites modo 4, lo anterior realizado no sirve de mucho, pues vamos a sacar el color del pixel de otra manera
                //TODO: hacer que el código anterior no se ejecute si estamos en dicho modo, realmente no afecta pero es absurdo ejecutar eso
                //si el color lo recalculamos de otra manera
                if (view_sprites_sms_tiles) {
                    z80_byte byte_color=((byte_leido_sms_1>>7)&1) | ((byte_leido_sms_2>>6)&2) | ((byte_leido_sms_3>>5)&4) | ((byte_leido_sms_4>>4)&8);

                    
                    z80_byte color_sprite=vdp_9918a_sms_cram[view_sprites_offset_palette + (byte_color & 15)] & 63;
                    
                    color=SMS_INDEX_FIRST_COLOR+color_sprite;
                   
                }

	            
				zxvision_putpixel(menu_debug_draw_sprites_window,finalx,yorigen+y,color);
			   }

                byte_leido_sms_1=byte_leido_sms_1<<1;
                byte_leido_sms_2=byte_leido_sms_2<<1;
                byte_leido_sms_3=byte_leido_sms_3<<1;
                byte_leido_sms_4=byte_leido_sms_4<<1;
                                    
			}

			puntero=puntero_inicio_linea;
			puntero +=tamanyo_linea;

		}
	

	zxvision_draw_window_contents(menu_debug_draw_sprites_window);

}

menu_z80_moto_int menu_debug_view_sprites_change_pointer(menu_z80_moto_int p)
{

       //restauramos modo normal de texto de menu, porque sino, tendriamos la ventana
        //del cambio de direccion, y encima los sprites
       set_menu_overlay_function(normal_overlay_texto_menu);


        char string_address[10];



				if (view_sprites_hardware) {
					sprintf(string_address,"%d",p&63);
					menu_ventana_scanf("Sprite?",string_address,3);
				}
				else {
					util_sprintf_address_hex(p,string_address);
        	menu_ventana_scanf("Address?",string_address,10);
				}



        p=parse_string_to_number(string_address);



        set_menu_overlay_function(menu_debug_draw_sprites);


        return p;

}





//Retorna 0 si ok
int menu_debug_view_sprites_save(menu_z80_moto_int direccion,int ancho, int alto, int ppb, int incremento)
{

	char file_save[PATH_MAX];

	char *filtros[3];

						 filtros[0]="pbm";
						 filtros[1]="c";
						 filtros[2]=0;

		int ret;

		 ret=menu_filesel("Select PBM/C File",filtros,file_save);

		 if (ret==1) {

 		 		//Ver si archivo existe y preguntar
			 if (si_existe_archivo(file_save)) {

	 				if (menu_confirm_yesno_texto("File exists","Overwrite?")==0) return 0;

 				}


				char string_height[4];
				sprintf(string_height,"%d",alto);
				menu_ventana_scanf("Height?",string_height,4);
				alto=parse_string_to_number(string_height);


				//Asignar buffer temporal
				int longitud=ancho*alto;
				z80_byte *buf_temp=malloc(longitud);
				if (buf_temp==NULL) {
					debug_printf(VERBOSE_ERR,"Error allocating temporary buffer");
				}

				//Copiar de memoria emulador ahi
				int i;
				for (i=0;i<longitud;i++) {
					//buf_temp[i]=peek_byte_z80_moto(direccion);
					buf_temp[i]=menu_debug_draw_sprites_get_byte(direccion);
					direccion +=incremento;
				}


				if (!util_compare_file_extension(file_save,"pbm")) {
					util_write_pbm_file(file_save,ancho,alto,ppb,buf_temp);
				}

				else if (!util_compare_file_extension(file_save,"c")) {
					util_write_sprite_c_file(file_save,ancho,alto,ppb,buf_temp);
				}

				else {
					//debug_printf (VERBOSE_ERR,"Error. Unkown sprite file format");
					return 1;
				}

				free(buf_temp);
		}

	return 0;

}


void menu_debug_sprites_get_parameters_hardware(void)
{
	if (view_sprites_hardware) {
		if (MACHINE_IS_TBBLUE) {
			//Parametros que alteramos segun sprite activo


                	view_sprites_ancho_sprite=16;

	                view_sprites_alto_sprite=16;



			//offset paleta
			view_sprites_offset_palette=0;

			view_sprites_increment_cursor_vertical=1; //saltar de 1 en 1






			//Permitir 4 u 8 bpp
			if (view_sprites_bpp!=8 && view_sprites_bpp!=4) {
				view_sprites_bpp=4;
				view_sprites_ppb=2;
			}


            view_sprites_bytes_por_linea=16/view_sprites_ppb;


			view_sprites_bytes_por_ventana=8; 


			//Cambiar a zona memoria 14. TBBlue sprites
			//while (menu_debug_memory_zone!=14) menu_debug_change_memory_zone_non_interactive();

			menu_debug_set_memory_zone(14);

			//paleta 11 tbblue
			//view_sprites_palette=11;


		}

		if (MACHINE_IS_TSCONF) {

			//Parametros que alteramos segun sprite activo
	                struct s_tsconf_debug_sprite spriteinfo;

        	        tsconf_get_debug_sprite(view_sprites_direccion,&spriteinfo);

                	view_sprites_ancho_sprite=spriteinfo.xs;

	                view_sprites_alto_sprite=spriteinfo.ys;

			//offset paleta
			view_sprites_offset_palette=spriteinfo.spal*16;


			view_sprites_increment_cursor_vertical=1; //saltar de 1 en 1

                        view_sprites_bytes_por_linea=256;

			view_sprites_bytes_por_ventana=8; //saltar de 8 en 8 con pgdn/up


			view_sprites_bpp=4;
			view_sprites_ppb=2;




			//Cambiar a zona memoria 15. TSConf sprites
			//while (menu_debug_memory_zone!=15) menu_debug_change_memory_zone_non_interactive();

			menu_debug_set_memory_zone(15);


			//paleta 13 tsconf
			//view_sprites_palette=13;




		}

		if (MACHINE_HAS_VDP_9918A) {
//Parametros que alteramos segun sprite activo


                	view_sprites_ancho_sprite=16;

	                view_sprites_alto_sprite=16;



			//offset paleta
			view_sprites_offset_palette=0;

			view_sprites_increment_cursor_vertical=1; //saltar de 1 en 1


            if (view_sprites_sms_tiles) {
                //4 bpp en caso de modo 4 sms
			    view_sprites_bpp=4;
			    view_sprites_ppb=2;

                	view_sprites_ancho_sprite=8;

	                view_sprites_alto_sprite=vdp_9918a_sms_get_sprite_height();    

                //Indicamos el offset de la paleta a 16, el de sprites
                view_sprites_offset_palette=16;
            }

            else {
			    //Permitir solo 1bpp

			    view_sprites_bpp=1;
			    view_sprites_ppb=8;
            }
		


            view_sprites_bytes_por_linea=16/view_sprites_ppb;


			view_sprites_bytes_por_ventana=8; 


			if (MACHINE_IS_MSX) menu_debug_set_memory_zone(MEMORY_ZONE_MSX_VRAM);
			if (MACHINE_IS_COLECO) menu_debug_set_memory_zone(MEMORY_ZONE_COLECO_VRAM);
			if (MACHINE_IS_SG1000) menu_debug_set_memory_zone(MEMORY_ZONE_SG1000_VRAM);
            if (MACHINE_IS_SMS) menu_debug_set_memory_zone(MEMORY_ZONE_SMS_VRAM);
			if (MACHINE_IS_SVI) menu_debug_set_memory_zone(MEMORY_ZONE_SVI_VRAM);

		}
	}

	else {
        //En caso de sms video mode 4, cambiamos los bpp a 4. Esto es solo identificativo para el usuario
        //porque realmente no lo lee cuando muestra los sprites en ese modo
        if (MACHINE_IS_SMS && view_sprites_sms_tiles) {
            //4 bpp en caso de modo 4 sms
            view_sprites_bpp=4;
            view_sprites_ppb=2;
        }

		view_sprites_bytes_por_linea=view_sprites_ancho_sprite/view_sprites_ppb;
		view_sprites_bytes_por_ventana=view_sprites_bytes_por_linea*view_sprites_alto_sprite;
		view_sprites_increment_cursor_vertical=view_sprites_bytes_por_linea;
	}
}

void menu_debug_view_sprites_textinfo(zxvision_window *ventana)
{
	int linea=0;
		char buffer_texto[64];

		//Antes de escribir, normalizar zona memoria
		menu_debug_set_memory_zone_attr();

		int restoancho=view_sprites_ancho_sprite % view_sprites_ppb;
		if (view_sprites_ancho_sprite-restoancho>0) view_sprites_ancho_sprite-=restoancho;

		//esto antes que menu_debug_sprites_get_parameters_hardware
		view_sprites_direccion=adjust_address_memory_size(view_sprites_direccion);

		menu_debug_sprites_get_parameters_hardware();



		char texto_memptr[33];

		if (view_sprites_hardware) {

			char texto_sprite[32];
			strcpy(texto_sprite,"Sprite");
			int max_sprites;
			if (MACHINE_IS_TSCONF) {
				max_sprites=TSCONF_MAX_SPRITES;
			}

			if (MACHINE_IS_TBBLUE) {
				if (view_sprites_bpp==4) max_sprites=TBBLUE_MAX_PATTERNS*2;
				else max_sprites=TBBLUE_MAX_PATTERNS;

				strcpy(texto_sprite,"Pattern");
			}

			if (MACHINE_HAS_VDP_9918A) {
				max_sprites=VDP_9918A_MAX_SPRITES;
                if (view_sprites_sms_tiles) max_sprites=VDP_9918A_SMS_MODE4_MAX_SPRITES;
			}
			sprintf(texto_memptr,"%s: %3d",texto_sprite,view_sprites_direccion%max_sprites); //dos digitos, tsconf hace 85 y tbblue hace 64. suficiente
		}

		else {
            char buffer_direccion[MAX_LENGTH_ADDRESS_MEMORY_ZONE+1];
            menu_debug_print_address_memory_zone(buffer_direccion,view_sprites_direccion);
			sprintf(texto_memptr,"Memptr:%s",buffer_direccion);
		}


	


		if (CPU_IS_MOTOROLA) sprintf (buffer_texto,"%s Size:%dX%d %dBPP",texto_memptr,view_sprites_ancho_sprite,view_sprites_alto_sprite,view_sprites_bpp);
		else sprintf (buffer_texto,"%s Size:%dX%d %dBPP",texto_memptr,view_sprites_ancho_sprite,view_sprites_alto_sprite,view_sprites_bpp);

		zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_texto);

        //int alto_ventana=SPRITES_ALTO_VENTANA

		linea=(ventana->visible_height)-7;

    if (linea>=0) {

		char buffer_primera_linea[64]; //dar espacio de mas para poder alojar el ~de los atajos
		char buffer_segunda_linea[64];

		char buffer_tercera_linea[64];

		//Forzar a mostrar atajos
		z80_bit antes_menu_writing_inverse_color;
		antes_menu_writing_inverse_color.v=menu_writing_inverse_color.v;
		menu_writing_inverse_color.v=1;

		char nombre_paleta[33];
		menu_debug_sprites_get_palette_name(view_sprites_palette,nombre_paleta);

        //En el caso de usar modo sms sprites modo 4, paleta es siempre fija
        //Ademas indicar si offset es de Tiles o Sprites
        if (view_sprites_sms_tiles) {
            sprintf(buffer_tercera_linea,"Pa~~l.: SMS Mode 4. O~~ff:%d (%s)",view_sprites_offset_palette,
            (view_sprites_offset_palette == 0 ? "Tiles" : "Sprites"));
        }

		else sprintf(buffer_tercera_linea,"Pa~~l.: %s. O~~ff:%d",nombre_paleta,view_sprites_offset_palette);


		char mensaje_texto_hardware[64];

		//por defecto
		mensaje_texto_hardware[0]=0;

		if (MACHINE_IS_TSCONF || MACHINE_IS_TBBLUE || MACHINE_HAS_VDP_9918A) {
			sprintf(mensaje_texto_hardware,"[%c] ~~hardware",(view_sprites_hardware ? 'X' : ' ') );
		}

		char mensaje_texto_zx81_pseudohires[33];
		//por defecto
		mensaje_texto_zx81_pseudohires[0]=0;

		if (MACHINE_IS_ZX8081) {
			sprintf(mensaje_texto_zx81_pseudohires,"[%c] Ps~~eudohires",(view_sprites_zx81_pseudohires.v ? 'X' : ' ') );
		}
		
		sprintf(buffer_primera_linea,"~~memptr In~~c+%d ~~o~~p~~q~~a:Size ~~bpp %s",
		view_sprite_incremento,
		(view_sprites_bpp==1 && !view_sprites_scr_sprite ? "~~save " : ""));

        char mensaje_texto_sms[32];
		//por defecto
		mensaje_texto_sms[0]=0;   

        if (MACHINE_IS_SMS) {
            if (view_sprites_sms_tiles==0) sprintf(mensaje_texto_sms," [ ] SMS Mo~~de 4");

            //Con tipo hardware y habilitado view_sprites_sms_tiles, da igual el modo
            else if (view_sprites_hardware) sprintf(mensaje_texto_sms," [X] SMS Mo~~de 4");

            else sprintf(mensaje_texto_sms," [%c] SMS Mo~~de 4",(view_sprites_sms_tiles==1 ? '>' : 'v') );
        }


		sprintf(buffer_segunda_linea, "[%c] ~~inv [%c] Sc~~r %s%s%s",
					(view_sprites_inverse.v ? 'X' : ' '),
					(view_sprites_scr_sprite ? 'X' : ' '),
					mensaje_texto_hardware,mensaje_texto_sms,mensaje_texto_zx81_pseudohires);


		zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_primera_linea);
		zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_segunda_linea);
		zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_tercera_linea);

		//Mostrar zona memoria

		char textoshow[33];

		char memory_zone_text[64]; //espacio temporal mas grande por si acaso

		if (menu_debug_show_memory_zones==0) {
			sprintf (memory_zone_text,"Mem ~~zone (mapped memory)");
		}

		else {
			//printf ("Info zona %d\n",menu_debug_memory_zone);
			char buffer_name[MACHINE_MAX_MEMORY_ZONE_NAME_LENGHT+1];
			//int readwrite;
			machine_get_memory_zone_name(menu_debug_memory_zone,buffer_name);
			sprintf (memory_zone_text,"Mem ~~zone (%d %s)",menu_debug_memory_zone,buffer_name);
			//printf ("size: %X\n",menu_debug_memory_zone_size);
			//printf ("Despues zona %d\n",menu_debug_memory_zone);
		}

		//truncar texto a 32 por si acaso
		memory_zone_text[32]=0;


		zxvision_print_string_defaults_fillspc(ventana,1,linea++,memory_zone_text);

		sprintf (textoshow," Size: %d (%d KB)",menu_debug_memory_zone_size,menu_debug_memory_zone_size/1024);
		
		zxvision_print_string_defaults_fillspc(ventana,1,linea++,textoshow);

	

		//Restaurar comportamiento atajos
		menu_writing_inverse_color.v=antes_menu_writing_inverse_color.v;

    }


}


zxvision_window zxvision_window_view_sprites;

void menu_debug_view_sprites(MENU_ITEM_PARAMETERS)
{

    //Desactivamos interlace - si esta. Con interlace la forma de onda se dibuja encima continuamente, sin borrar
    //z80_bit copia_video_interlaced_mode;
    //copia_video_interlaced_mode.v=video_interlaced_mode.v;
	menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();



    //disable_interlace();

	zxvision_window *ventana;
	ventana=&zxvision_window_view_sprites;

    //IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
    //si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
    //la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
	zxvision_delete_window_if_exists(ventana);

	if (!MACHINE_IS_TBBLUE && !MACHINE_IS_TSCONF && !MACHINE_HAS_VDP_9918A) view_sprites_hardware=0;

	if (!MACHINE_IS_ZX8081) view_sprites_zx81_pseudohires.v=0;

	int x,y,ancho,alto,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;

	
    if (!util_find_window_geometry("sprites",&x,&y,&ancho,&alto,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
        x=SPRITES_X;
        y=SPRITES_Y;
        ancho=SPRITES_ANCHO;
        alto=SPRITES_ALTO_VENTANA;
    }


	//zxvision_new_window_nocheck_staticsize(ventana,x,y,ancho,alto,64,64+2,"Sprites");
    zxvision_new_window_gn_cim(ventana,x,y,ancho,alto,64,64+2,"Sprites","sprites",is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);


	ventana->can_be_backgrounded=1;
	//indicar nombre del grabado de geometria
	//strcpy(ventana->geometry_name,"sprites");
    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;    

	//Permitir hotkeys desde raton
	ventana->can_mouse_send_hotkeys=1;

    //decimos que tiene que borrar fondo cada vez al redibujar
    //por tanto es como decirle que no use cache de putchar
    //dado que el fondo de texto es casi todo texto con caracter " " eso borra los pixeles que metemos con overlay del frame anterior
    ventana->must_clear_cache_on_draw=1;        

	zxvision_draw_window(ventana);

	z80_byte tecla;


    //Cambiamos funcion overlay de texto de menu
    //Se establece a la de funcion de ver sprites
    set_menu_overlay_function(menu_debug_draw_sprites);

	menu_debug_draw_sprites_window=ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui	


    //Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
    //Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
    if (zxvision_currently_restoring_windows_on_start) {
            //printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
            return;
    }	

	int redibujar_texto=1;	

    int ancho_anterior,alto_anterior;
    zxvision_window_save_size(ventana,&ancho_anterior,&alto_anterior);

    do {


		//Solo redibujar el texto cuando alguna tecla pulsada sea de las validas,
		//y no con mouse moviendo la ventana
		//porque usa mucha cpu y por ejemplo en maquina tsconf se clava si arrastramos ventana
		if (redibujar_texto) {
			//printf ("redibujamos texto\n");


			menu_debug_view_sprites_textinfo(ventana);

		
			//Si no esta multitarea, mostrar el texto que acabamos de escribir
	    	if (!menu_multitarea) {
				zxvision_draw_window_contents(ventana);
			}			
		}

	
		tecla=zxvision_common_getkey_refresh();
		//printf ("tecla: %d\n",tecla);

		if (tecla) redibujar_texto=1;

        switch (tecla) {

					case 8:
						//izquierda
						view_sprites_direccion--;
					break;

					case 9:
						//derecha
						view_sprites_direccion++;
					break;

                    case 11:
                        //arriba
                        view_sprites_direccion -=view_sprites_increment_cursor_vertical;
                    break;

                    case 10:
                        //abajo
                        view_sprites_direccion +=view_sprites_increment_cursor_vertical;
                    break;

                    case 24:
                        //PgUp
                        view_sprites_direccion -=view_sprites_bytes_por_ventana;
                    break;

                    case 25:
                        //PgDn
                        view_sprites_direccion +=view_sprites_bytes_por_ventana;
                    break;

                    case 'm':
                        view_sprites_direccion=menu_debug_view_sprites_change_pointer(view_sprites_direccion);
							zxvision_draw_window(ventana);
                    break;

					case 'b':
						menu_debug_sprites_change_bpp();
					break;

					case 'd':
                        if (MACHINE_IS_SMS) {
                            view_sprites_sms_tiles++;
                            //En modo hardware solo tendra dos valores, 0 y 1
                            if (view_sprites_hardware) {
                                if (view_sprites_sms_tiles>=2) view_sprites_sms_tiles=0;
                            }

                            //Y en modo no hardware, se permiten valores 0, 1 y 2
                            else {
                                if (view_sprites_sms_tiles==3) view_sprites_sms_tiles=0;
                            }
                        }
					break;                    

					case 'f':
                        //En modo sms solo permitimos dos offset distintos, 0 y 16
                        if (view_sprites_sms_tiles) {
                            view_sprites_offset_palette +=16;
                            if (view_sprites_offset_palette>16) view_sprites_offset_palette=0;
                        }   
                        else {                 
						    view_sprites_offset_palette++;

						    if (view_sprites_offset_palette>=256) view_sprites_offset_palette=0;
                        }
					break;


					case 'l':
						menu_debug_sprites_change_palette();
					break;

					case 'h':
						if (MACHINE_IS_TBBLUE || MACHINE_IS_TSCONF || MACHINE_HAS_VDP_9918A) view_sprites_hardware ^=1;								
					break;

					case 'e':
						if (MACHINE_IS_ZX8081) view_sprites_zx81_pseudohires.v ^=1;
					break;

					case 'i':
						view_sprites_inverse.v ^=1;
					break;

					case 'z':
							//restauramos modo normal de texto de menu, sino, el selector de zona se vera
								//con el sprite encima
						set_menu_overlay_function(normal_overlay_texto_menu);

						menu_debug_change_memory_zone();

						set_menu_overlay_function(menu_debug_draw_sprites);

						break;

					case 's':


						if (view_sprites_hardware) {

						}

						else {

							//Solo graba sprites de 1bpp (monocromos)
							if (view_sprites_bpp==1 && !view_sprites_scr_sprite) {
								//restauramos modo normal de texto de menu, sino, el selector de archivos se vera
								//con el sprite encima
								set_menu_overlay_function(normal_overlay_texto_menu);


								if (menu_debug_view_sprites_save(view_sprites_direccion,view_sprites_ancho_sprite,view_sprites_alto_sprite,view_sprites_ppb,view_sprite_incremento)) {
									menu_error_message("Unknown file format");
								}

								//cls_menu_overlay();

								//menu_debug_view_sprites_ventana();
								set_menu_overlay_function(menu_debug_draw_sprites);
								zxvision_draw_window(ventana);
							}

						}
					break;

					case 'o':
						if (view_sprites_ancho_sprite>view_sprites_ppb) view_sprites_ancho_sprite -=view_sprites_ppb;
					break;

					case 'p':

						if (view_sprites_ancho_sprite<512) view_sprites_ancho_sprite +=view_sprites_ppb;
					break;

                    case 'q':
                        if (view_sprites_alto_sprite>1) view_sprites_alto_sprite--;
                    break;

                    case 'a':
						if (view_sprites_alto_sprite<512)  view_sprites_alto_sprite++;
                    break;

					case 'c':
							if (view_sprite_incremento==1) view_sprite_incremento=2;
							else view_sprite_incremento=1;
					break;

					case 'r':
							view_sprites_scr_sprite ^=1;
					break;

					default:
						//no es tecla valida, no redibujar texto
						redibujar_texto=0;
					break;

		}

		if (ventana->visible_height!=alto_anterior || ventana->visible_width!=ancho_anterior) {
            //printf("Reescribir texto porque ha cambiado tamanyo ventana\n");

			redibujar_texto=1;

            zxvision_window_save_size(ventana,&ancho_anterior,&alto_anterior);

            zxvision_cls(ventana);

		}


    } while (tecla!=2 && tecla!=3);



    //Restauramos modo interlace
    //if (copia_video_interlaced_mode.v) enable_interlace();

	//Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
	zxvision_set_window_overlay_from_current(ventana);

    //restauramos modo normal de texto de menu
    set_menu_overlay_function(normal_overlay_texto_menu);

    cls_menu_overlay();

    	//Grabar geometria ventana

		util_add_window_geometry_compact(ventana);	


	if (tecla==3) {
		zxvision_message_put_window_background();
	}	

	else {



		zxvision_destroy_window(ventana);		
	}



}



/*

Partitura



 --------------------------------

 --------------------------------

 --------------------------------
 
 --------------------------------
 
 --------------------------------



5 lineas de pentagrana -> 4 separaciones

8 pixeles de alto cada separacion -> 32 pixeles cada pentagrama

Si cogemos dos mas para subir hasta el Do, son 8x6=48 pixeles por pentagama

48 * 3 = 144 los 3 pentagramas


Dibujo de la nota:

     012345678901
0 -----------------------------------
1    ..XXX..
2    .X...X.            
3    X.....X
4    X.....X
5    X.....X
6    .X...X.
7    ..XXX..
8 ----------------------------------
*/

#define PENTAGRAMA_NOTA_ALTO 7
#define PENTAGRAMA_NOTA_ANCHO 7
#define PENTAGRAMA_NOTA_LARGO_PALITO 17

//donde empieza el palito
#define PENTAGRAMA_NOTA_OFFSET_PALITO 3

#define PENTAGRAMA_ESPACIO_LINEAS 8

#define PENTAGRAMA_SOST_ANCHO 8
#define PENTAGRAMA_SOST_ALTO 11

#define PENTAGRAMA_ANCHO_NOTA_TOTAL (PENTAGRAMA_SOST_ANCHO+PENTAGRAMA_NOTA_ANCHO+6)

#define PENTAGRAMA_MARGEN_SOSTENIDO (PENTAGRAMA_SOST_ANCHO+2)

#define PENTAGRAMA_TOTAL_ALTO (PENTAGRAMA_ESPACIO_LINEAS*7)

//#define PENTAGRAMA_MARGEN_SUPERIOR 8
//Si hay mas de un chip, meter margen superior
#define PENTAGRAMA_MARGEN_SUPERIOR (total_ay_chips>1 ? 8 : 0)

char *pentagrama_nota_negra[PENTAGRAMA_NOTA_ALTO]={
   //0123456
    "  XXX  ",  
	" XXXXX ",
	"XXXXXXX",
	"XXXXXXX",
	"XXXXXXX",
	" XXXXX ",
	"  XXX  "
};

char *pentagrama_nota_blanca[PENTAGRAMA_NOTA_ALTO]={
   //0123456
    "  XXX  ",  
	" X   X ",
	"X     X",
	"X     X",
	"X     X",
	" X   X ",
	"  XXX  "
};

#define PENTAGRAMA_PUNTILLO_ALTO 2
#define PENTAGRAMA_PUNTILLO_ANCHO 2

/* char *pentagrama_puntillo[PENTAGRAMA_PUNTILLO_ALTO]={
   //0123456
    " X ",  
	"XXX",
	" X "
};*/

char *pentagrama_puntillo[PENTAGRAMA_PUNTILLO_ALTO]={
   //0123456
    "XX",  
	"XX",
};


#define PENTAGRAMA_CLAVE_SOL_ALTO 44
#define PENTAGRAMA_CLAVE_SOL_ANCHO 30

char *pentagrama_clave_sol[PENTAGRAMA_CLAVE_SOL_ALTO]={
/*
 012345678901234567890123456789012345
*/

"                 XXXXX        ",
"               XXXXXXXX       ",
"              XXXXXXXXXX      ",
"             XXXXXXXXXXX      ",
"            XXXXX     XX      ",
"            XXXX      XX      ",
"            XXX       XX      ",
"            XX        XX      ",
"            XX      XXXX      ",
"            XX     XXXXX      ",
"            XX     XXXXX      ",
"            XX  XXXXXXX       ",
"            XXXXXXXXX         ",
"            XXXXXXXXX         ",
"          XXXXXXXXXX          ",
"        XXXXXXXXXX            ",
"       XXXXXXXXX              ",
"     XXXXXXXXXXX              ",
"    XXXXXXXXXX XX             ",
"   XXXXXXXXX   XX             ",
"  XXXXXXXX     XXXXXXX        ",
"  XXXXXXX    XXXXXXXXXXXX     ",
" XXXXX     XXXXXXXXXXXXXXXXX  ",
"XXXXX     XXXXXXXXXXXXXXXXXXX ",
"XXXXXX   XXXXXX   XX   XXXXXXX",
"XXXXXX   XXXXX     XX    XXXXX",
" XXXXX   XXXXX      XX     XXX",
"  XXXX    XXXX      XX     XXX",
"  XXXXX   XXXXX     XX     XX ",
"   XXXXX   XXXX      XX  XXXX ",
"    XXXXXX           XX XXXX  ",
"     XXXXXXX         XXXXX    ",
"          XXXXXXXXXXXXXXX     ",
"             XXXXXXXXXXX      ",
"                      XX      ",
"                      XX      ",
"          XXX         XX      ",
"        XXXXXX        XX      ",
"       XXXXXXXX       XX      ",
"       XXXXXXXX       XX      ",
"        XXXXXX       XX       ",
"          XXX       XX        ",
"          XXXXXXXXXXX          ",
"            XXXXXXXX          ",
};


char *pentagrama_sost[PENTAGRAMA_SOST_ALTO]={
  
//0123456789012
 "  X  X  ",    //0
 "  X  X  ",
 "  X  XXX",
 "  XXXX  ",
 "XXX  X  ",
 "  X  X  ",   //5
 "  X  XXX",
 "  XXXX  ",
 "XXX  X  ",
 "  X  X  ",    
 "  X  X  "     //10

};


//Clave de sol. 56 pixeles alto aprox

#define PIANO_PARTITURA_GRAPHIC_BASE_X (menu_origin_x() )
#define PIANO_PARTITURA_GRAPHIC_BASE_Y 0



#define PIANO_PARTITURA_ANCHO_VENTANA 32
#define PIANO_PARTITURA_ALTO_VENTANA 24

#define MENU_AY_PARTITURA_MAX_COLUMNS 30

zxvision_window *menu_ay_partitura_overlay_window;


//Lo que contiene cada pentagrama, de cada chip, de cada canal

//Chip, canal, columna, string de 4
char menu_ay_partitura_current_state[MAX_AY_CHIPS][3][MENU_AY_PARTITURA_MAX_COLUMNS][4];

//Chip, canal, columna, duracion de cada nota
int menu_ay_partitura_current_state_duraciones[MAX_AY_CHIPS][3][MENU_AY_PARTITURA_MAX_COLUMNS];

//Ultima columna de cada canal usada
int menu_ay_partitura_ultima_columna[3];

//Nota anterior de la ultima columna
//char menu_ay_partitura_last_state[MAX_AY_CHIPS][3][4];


//Hacer putpixel en pantalla de color indexado 16 bits. Usado en watermark para no rainbow
void menu_ay_partitura_putpixel_nota(z80_int *destino GCC_UNUSED,int x,int y,int ancho_destino GCC_UNUSED,int color GCC_UNUSED)
{
	//scr_putpixel(x,y,color);

	//zxvision_putpixel(menu_ay_partitura_overlay_window,x,y,color);
	zxvision_putpixel(menu_ay_partitura_overlay_window,x,y,ESTILO_GUI_TINTA_NORMAL);
}

void menu_ay_partitura_dibujar_sost(int x,int y)
{
	screen_put_asciibitmap_generic(pentagrama_sost,NULL,x,y,PENTAGRAMA_SOST_ANCHO,PENTAGRAMA_SOST_ALTO,0,menu_ay_partitura_putpixel_nota,1,0);
}

//duraciones notas
enum aysheet_tipo_nota_duracion {
	AYSHEET_NOTA_SEMIFUSA,
	AYSHEET_NOTA_SEMIFUSA_PUNTO,

	AYSHEET_NOTA_FUSA,
	AYSHEET_NOTA_FUSA_PUNTO,	

	AYSHEET_NOTA_SEMICORCHEA,
	AYSHEET_NOTA_SEMICORCHEA_PUNTO,	

	AYSHEET_NOTA_CORCHEA,
	AYSHEET_NOTA_CORCHEA_PUNTO,	

	AYSHEET_NOTA_NEGRA,
	AYSHEET_NOTA_NEGRA_PUNTO,	

	AYSHEET_NOTA_BLANCA,
	AYSHEET_NOTA_BLANCA_PUNTO,	

	AYSHEET_NOTA_REDONDA,
	AYSHEET_NOTA_REDONDA_PUNTO

};

//retorne el char * de donde esta la nota (blanca,redonda=pentagrama_nota_blanca. resto=pentagrama_nota_negra)
char **aysheet_tipo_nota_bitmap(enum aysheet_tipo_nota_duracion nota)
{
	switch (nota) {
		case AYSHEET_NOTA_BLANCA:
		case AYSHEET_NOTA_BLANCA_PUNTO:
		case AYSHEET_NOTA_REDONDA:
		case AYSHEET_NOTA_REDONDA_PUNTO:
			return pentagrama_nota_blanca;
		break;

		default:
			return pentagrama_nota_negra;
		break;
	}
}


//dice si nota tiene "palito", o sea, todos menos la redonda
int aysheet_tipo_nota_tienepalo(enum aysheet_tipo_nota_duracion nota)
{
	switch (nota) {
		case AYSHEET_NOTA_REDONDA:
		case AYSHEET_NOTA_REDONDA_PUNTO:
			return 0;
		break;

		default:
			return 1;
		break;
	}
}

//dice el numero de diagonales que tiene la nota (corchea, semicorchea, fusa, semifusa)
int aysheet_tipo_nota_diagonales(enum aysheet_tipo_nota_duracion nota)
{
	switch (nota) {
		case AYSHEET_NOTA_CORCHEA:
		case AYSHEET_NOTA_CORCHEA_PUNTO:
			return 1;
		break;

		case AYSHEET_NOTA_SEMICORCHEA:
		case AYSHEET_NOTA_SEMICORCHEA_PUNTO:
			return 2;
		break;

		case AYSHEET_NOTA_FUSA:
		case AYSHEET_NOTA_FUSA_PUNTO:
			return 3;
		break;

		case AYSHEET_NOTA_SEMIFUSA:
		case AYSHEET_NOTA_SEMIFUSA_PUNTO:
			return 4;
		break;				


		default:
			return 0;
		break;
	}
}

//dice si nota tiene puntillo
int aysheet_tipo_nota_tienepuntillo(enum aysheet_tipo_nota_duracion nota)
{
	switch (nota) {
		case AYSHEET_NOTA_SEMIFUSA_PUNTO:
		case AYSHEET_NOTA_FUSA_PUNTO:
		case AYSHEET_NOTA_SEMICORCHEA_PUNTO:
		case AYSHEET_NOTA_CORCHEA_PUNTO:
		case AYSHEET_NOTA_NEGRA_PUNTO:
		case AYSHEET_NOTA_BLANCA_PUNTO:	
		case AYSHEET_NOTA_REDONDA_PUNTO:
			return 1;
		break;

		default:
			return 0;
		break;
	}
}

//Devuelve tipo de nota segun su duracion en 1/50 de segundo
enum aysheet_tipo_nota_duracion menu_aysheet_get_length(int duracion)
{
/*
	Duraciones notas:


	3.125=0.0625 segundos=semifusa
	4.6875=0.09375 segundos=semifusa con punto
	
	6.25=0.125 segundos=fusa
	9.375=0.1875 segundos=fusa con punto

	12.5=0.25 segundos=semicorchea
	18.75=0.375 segundos=semicorchea con punto
	
	25=0.5 segundos=corchea
	37.5=0.75 segundos=corchea con punto

	50=1 segundo=negra
	75=1.5 segundos=negra con punto

	100=2 segundos=blanca
	150=3 segundos=blanca con punto

	200=4 segundos=redonda
	300=6 segundos=redonda con punto

	 */

	//Vemos duraciones segun si es menor o igual. Hacemos redondeos de duraciones: 4.6 es 5
	if (duracion<=3) return AYSHEET_NOTA_SEMIFUSA;
	if (duracion<=5) return AYSHEET_NOTA_SEMIFUSA_PUNTO;
	if (duracion<=6) return AYSHEET_NOTA_FUSA;
	if (duracion<=9) return AYSHEET_NOTA_FUSA_PUNTO;

	if (duracion<=12) return AYSHEET_NOTA_SEMICORCHEA;
	if (duracion<=19) return AYSHEET_NOTA_SEMICORCHEA_PUNTO;
	if (duracion<=25) return AYSHEET_NOTA_CORCHEA;
	if (duracion<=37) return AYSHEET_NOTA_CORCHEA_PUNTO;
	
	if (duracion<=50) return AYSHEET_NOTA_NEGRA;
	if (duracion<=75) return AYSHEET_NOTA_NEGRA_PUNTO;
	if (duracion<=100) return AYSHEET_NOTA_BLANCA;
	if (duracion<=150) return AYSHEET_NOTA_BLANCA_PUNTO;

	if (duracion<=200) return AYSHEET_NOTA_REDONDA;

	//Cualquier otra cosa
	return AYSHEET_NOTA_REDONDA_PUNTO;

}

//incremento_palito: +1 : palito hacia abajo
//incremento_palito: +1 : palito hacia arriba
//duracion en 1/50 de segundos. 50=negra
void menu_ay_partitura_dibujar_nota(int x,int y,int incremento_palito,int duracion)
{


	enum aysheet_tipo_nota_duracion tipo_nota_duracion=menu_aysheet_get_length(duracion);

	char **bitmap_nota=aysheet_tipo_nota_bitmap(tipo_nota_duracion);

	bitmap_nota=aysheet_tipo_nota_bitmap(tipo_nota_duracion);




	screen_put_asciibitmap_generic(bitmap_nota,NULL,x,y,PENTAGRAMA_NOTA_ANCHO,PENTAGRAMA_NOTA_ALTO,0,menu_ay_partitura_putpixel_nota,1,0);
	

	//PENTAGRAMA_NOTA_LARGO_PALITO
	if (aysheet_tipo_nota_tienepalo(tipo_nota_duracion)) {
		int yorig=y+PENTAGRAMA_NOTA_OFFSET_PALITO;

		int xorig=x;

		//Si palito hacia arriba
		if (incremento_palito<0) xorig=x+PENTAGRAMA_NOTA_ANCHO-1;

		int alto=PENTAGRAMA_NOTA_LARGO_PALITO;

		for (;alto>0;alto--,yorig +=incremento_palito) {
			zxvision_putpixel(menu_ay_partitura_overlay_window,xorig,yorig,ESTILO_GUI_TINTA_NORMAL); 
		}


		//Diagonales de la nota. corchea, semi, etc
		int diagonales=aysheet_tipo_nota_diagonales(tipo_nota_duracion);
		int i;
		int largo_diagonal=5;

		
		for (i=0;i<diagonales;i++) {
			int l;
			yorig=y+PENTAGRAMA_NOTA_OFFSET_PALITO+((PENTAGRAMA_NOTA_LARGO_PALITO-i*3)*incremento_palito);
			for (l=0;l<largo_diagonal;l++) {
				zxvision_putpixel(menu_ay_partitura_overlay_window,xorig+l,yorig-(l*incremento_palito),ESTILO_GUI_TINTA_NORMAL); 
			}
		}		
	}

	//Si hay que dibujar puntillo
	if (aysheet_tipo_nota_tienepuntillo(tipo_nota_duracion)) {
		screen_put_asciibitmap_generic(pentagrama_puntillo,NULL,x+PENTAGRAMA_NOTA_ANCHO+1,y+PENTAGRAMA_NOTA_ALTO/2+1,
				PENTAGRAMA_PUNTILLO_ANCHO,PENTAGRAMA_PUNTILLO_ALTO,0,menu_ay_partitura_putpixel_nota,1,0);
	}




}

void meny_ay_partitura_dibujar_clavesol(int x,int y)
{
	screen_put_asciibitmap_generic(pentagrama_clave_sol,NULL,x,y,PENTAGRAMA_CLAVE_SOL_ANCHO,PENTAGRAMA_CLAVE_SOL_ALTO,0,menu_ay_partitura_putpixel_nota,1,0);	
}




void menu_ay_partitura_linea(int x,int y,int ancho)
{

		for (;ancho>0;ancho--,x++) {
			zxvision_putpixel(menu_ay_partitura_overlay_window,x,y,ESTILO_GUI_TINTA_NORMAL);
		}	
}

void menu_ay_partitura_lineas_pentagrama(int x,int y,int ancho,int separacion_alto)
{
	int lineas;

	int y_clavesol=y-7;

	for (lineas=0;lineas<5;lineas++) {
		menu_ay_partitura_linea(x,y,ancho);

		y +=separacion_alto;
	}


	meny_ay_partitura_dibujar_clavesol(x,y_clavesol);
}

//nota puede ser:  do, re, mi, fa, sol, la, si, do, re... si (0...13)
void menu_ay_partitura_nota_pentagrama(int x,int y,int nota,int si_sostenido,int duracion)
{
	//origen y=fa (10)

	int diferencia_nota=10-nota;

	int incremento_alto=diferencia_nota*(PENTAGRAMA_ESPACIO_LINEAS/2);

	//Y el punto inicial y
	int ynota=y+incremento_alto-PENTAGRAMA_NOTA_OFFSET_PALITO;

	//A partir del do, palito para abajo
	int incremento_palito=-1;

	if (nota>=6) incremento_palito=+1; //A partir del Si , palito para abajo


	menu_ay_partitura_dibujar_nota(x,ynota,incremento_palito,duracion);

	//Si hay que poner palito de linea pentagrama (en do (0), la (12), si(12))
	if (nota==0 || nota==12 || nota==13) {
		int ypalito;
		if (nota==0 || nota==12) ypalito=ynota+PENTAGRAMA_NOTA_OFFSET_PALITO;
		else ypalito=ynota+PENTAGRAMA_NOTA_ALTO; //si (12)

		menu_ay_partitura_linea(x-2,ypalito,PENTAGRAMA_NOTA_ANCHO+4);	
	}

	if (si_sostenido) {
		x=x-PENTAGRAMA_MARGEN_SOSTENIDO;
		ynota -=2; //un poquito mas para arriba
		menu_ay_partitura_dibujar_sost(x,ynota);
	}


}

//nota puede ser:  do, re, mi, fa, sol, la, si, do, re... si (0...13)
void menu_ay_partitura_nota_pentagrama_pos(int xorig,int yorig,int columna,int nota,int si_sostenido,int duracion)
{
	int ancho_columna=PENTAGRAMA_ANCHO_NOTA_TOTAL;

	int posx=(columna*ancho_columna)+xorig;

	//Y darle margen por la izquierda pos si hay sostenido
	posx +=PENTAGRAMA_MARGEN_SOSTENIDO;

	//darle margen de la clave de sol
	posx +=PENTAGRAMA_CLAVE_SOL_ANCHO;

	menu_ay_partitura_nota_pentagrama(posx,yorig,nota,si_sostenido,duracion);
}



int menu_ay_partitura_ancho_col_texto(void)
{
	return menu_char_width;
}

int menu_ay_partitura_total_columns(void)
{
	int ancho_columna=menu_ay_partitura_ancho_col_texto();
	int ancho_nota=PENTAGRAMA_ANCHO_NOTA_TOTAL;
	int total_columnas=(((menu_ay_partitura_overlay_window->visible_width)*ancho_columna)-PENTAGRAMA_MARGEN_SOSTENIDO*2)/ancho_nota;

	total_columnas--; //1 menos

	//de la clave de sol
	total_columnas--;


	if (total_columnas>MENU_AY_PARTITURA_MAX_COLUMNS) total_columnas=MENU_AY_PARTITURA_MAX_COLUMNS;

	//control minimos
	if (total_columnas<2) total_columnas=2;

	return total_columnas;	
}




//Scroll de un chip entero
void menu_ay_partitura_scroll(int chip)
{

		//Meter valor actual

	int total_columnas=menu_ay_partitura_total_columns();
	int i;

	for (i=0;i<total_columnas-1;i++) {
		int canal;
		for (canal=0;canal<3;canal++) {
			strcpy(menu_ay_partitura_current_state[chip][canal][i],menu_ay_partitura_current_state[chip][canal][i+1]);
			menu_ay_partitura_current_state_duraciones[chip][canal][i]=menu_ay_partitura_current_state_duraciones[chip][canal][i+1];
		}
	}

	//La ultima columna ponerla a vacia
		int canal;
		for (canal=0;canal<3;canal++) {
			menu_ay_partitura_current_state[chip][canal][i][0]=0;
			menu_ay_partitura_current_state_duraciones[chip][canal][i]=0;
		}	

	//Desplazar indices de ultima columna a la izquierda
		
	for (i=0;i<3;i++) {
		int c=menu_ay_partitura_ultima_columna[i];
		if (c>0) {
			menu_ay_partitura_ultima_columna[i]=c-1;
		}
	}		
}





void menu_ay_partitura_draw_state(int chip,int canal)
{

	int x=0;
	int y=PENTAGRAMA_ESPACIO_LINEAS*2;
	int duracion;


	y +=canal*(PENTAGRAMA_TOTAL_ALTO+1); //+1 para dejar 1 pixelillo de margen


	y +=PENTAGRAMA_MARGEN_SUPERIOR;


	int ancho_columna=menu_ay_partitura_ancho_col_texto();

	//Las lineas de pentagrama que dejen espacio a la izquierda y derecha, de ancho=ancho_columna
	menu_ay_partitura_lineas_pentagrama(x+ancho_columna,y,((menu_ay_partitura_overlay_window->visible_width)-2)*ancho_columna,PENTAGRAMA_ESPACIO_LINEAS);



	int ancho_nota=PENTAGRAMA_ANCHO_NOTA_TOTAL;
	int total_columnas;


	int i;


	total_columnas=menu_ay_partitura_total_columns();
	//printf ("total columnas: %d\n",total_columnas);

	for (i=0;i<total_columnas;i++) {
		char *string_nota;
		string_nota=menu_ay_partitura_current_state[chip][canal][i];
		//if (canal==0) printf ("%d [%s]\n",i,string_nota);

		//Nota leida canal 0

		int nota_final=-1;
		int octava;
		int sostenido;

		get_note_values(string_nota,&nota_final,&sostenido,&octava);
		if (nota_final>=0) {

			//Si octava impar, va hacia arriba
			if (octava & 1) nota_final +=7;

			duracion=menu_ay_partitura_current_state_duraciones[chip][canal][i];

			menu_ay_partitura_nota_pentagrama_pos(x+ancho_nota,y,i,nota_final,sostenido,duracion);
		}
	}



}

int menu_ay_partitura_chip=0;

void menu_ay_partitura_overlay(void)
{


	if (!zxvision_drawing_in_background) normal_overlay_texto_menu();


	menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech, en el caso que se habilite piano de tipo texto


    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_ay_partitura_overlay_window->is_minimized) return;

    //printf("Overlay ay sheet %d\n",contador_segundo);



    char nota_a[4];
    char nota_b[4];
    char nota_c[4];


    int freq_a,freq_b,freq_c;

    freq_a=audio_retorna_frecuencia_canal(0,menu_ay_partitura_chip);
    freq_b=audio_retorna_frecuencia_canal(1,menu_ay_partitura_chip);
    freq_c=audio_retorna_frecuencia_canal(2,menu_ay_partitura_chip);        




    sprintf(nota_a,"%s",get_note_name(freq_a) );

    
    sprintf(nota_b,"%s",get_note_name(freq_b) );

    
    sprintf(nota_c,"%s",get_note_name(freq_c) );

    //Si canales no suenan como tono, o volumen 0 meter cadena vacia en nota
    if (!audio_si_canal_tono(menu_ay_partitura_chip,0)) {
        nota_a[0]=0;
    }
    if (!audio_si_canal_tono(menu_ay_partitura_chip,1)) {
        nota_b[0]=0;
    }
    if (!audio_si_canal_tono(menu_ay_partitura_chip,2)) {
        nota_c[0]=0;
    }


	


	//Si notas anteriores distintas de las actuales, scroll izquierda


	//printf ("a [%s] [%s]\n",nota_a,menu_ay_partitura_last_state[0][0]);
	//printf ("b [%s] [%s]\n",nota_b,menu_ay_partitura_last_state[0][1]);
	//printf ("c [%s] [%s]\n",nota_c,menu_ay_partitura_last_state[0][2]);

	int columna_estado_anterior;
	//columna_estado_anterior=menu_ay_partitura_total_columns()-1;

	int hayscroll=0;
	int modificado_canal1=0;
	int modificado_canal2=0;
	int modificado_canal3=0;

	//Si alguno de los 3 canales es diferente del estado anterior
	columna_estado_anterior=menu_ay_partitura_ultima_columna[0];
	if (strcasecmp(nota_a,menu_ay_partitura_current_state[menu_ay_partitura_chip][0][columna_estado_anterior])) {
		hayscroll=1;
		modificado_canal1=1;
	}
	else {
		//se mantiene igual. aumentar duracion
		menu_ay_partitura_current_state_duraciones[menu_ay_partitura_chip][0][columna_estado_anterior]++;
	}


	columna_estado_anterior=menu_ay_partitura_ultima_columna[1];
	if (strcasecmp(nota_b,menu_ay_partitura_current_state[menu_ay_partitura_chip][1][columna_estado_anterior])) {
		hayscroll=1;
		modificado_canal2=1;
	}
	else {
		//se mantiene igual. aumentar duracion
		menu_ay_partitura_current_state_duraciones[menu_ay_partitura_chip][1][columna_estado_anterior]++;
	}	


	columna_estado_anterior=menu_ay_partitura_ultima_columna[2];
	if (strcasecmp(nota_c,menu_ay_partitura_current_state[menu_ay_partitura_chip][2][columna_estado_anterior])) {
		hayscroll=1;
		modificado_canal3=1;
	}
	else {
		//se mantiene igual. aumentar duracion
		menu_ay_partitura_current_state_duraciones[menu_ay_partitura_chip][2][columna_estado_anterior]++;
	}	




	if (hayscroll) {
		menu_ay_partitura_scroll(menu_ay_partitura_chip);

		//Meter valor actual los que se han modificado
		if (modificado_canal1) {
			//Y decir que ultima columna es la de mas a la derecha
			columna_estado_anterior=menu_ay_partitura_total_columns()-1;
			menu_ay_partitura_ultima_columna[0]=columna_estado_anterior;

			strcpy(menu_ay_partitura_current_state[menu_ay_partitura_chip][0][columna_estado_anterior],nota_a);
			menu_ay_partitura_current_state_duraciones[menu_ay_partitura_chip][0][columna_estado_anterior]=1;
		}

		if (modificado_canal2) {
			//Y decir que ultima columna es la de mas a la derecha
			columna_estado_anterior=menu_ay_partitura_total_columns()-1;
			menu_ay_partitura_ultima_columna[1]=columna_estado_anterior;

			strcpy(menu_ay_partitura_current_state[menu_ay_partitura_chip][1][columna_estado_anterior],nota_b);
			menu_ay_partitura_current_state_duraciones[menu_ay_partitura_chip][1][columna_estado_anterior]=1;
		}

		if (modificado_canal3) {
			//Y decir que ultima columna es la de mas a la derecha
			columna_estado_anterior=menu_ay_partitura_total_columns()-1;
			menu_ay_partitura_ultima_columna[2]=columna_estado_anterior;

			strcpy(menu_ay_partitura_current_state[menu_ay_partitura_chip][2][columna_estado_anterior],nota_c);
			menu_ay_partitura_current_state_duraciones[menu_ay_partitura_chip][2][columna_estado_anterior]=1;
		}				
		


	}

	//Dibujar estado de los 3 canales
	menu_ay_partitura_draw_state(menu_ay_partitura_chip,0);
	menu_ay_partitura_draw_state(menu_ay_partitura_chip,1);
	menu_ay_partitura_draw_state(menu_ay_partitura_chip,2);

	


	zxvision_draw_window_contents(menu_ay_partitura_overlay_window); 

}


void menu_ay_partitura_init_state(void)
{
			

    //Inicializar estado con string "" y duraciones 0

    

    int chip;
    for (chip=0;chip<MAX_AY_CHIPS;chip++) {
        int canal;
        for (canal=0;canal<3;canal++) {
            int col;

            for (col=0;col<MENU_AY_PARTITURA_MAX_COLUMNS;col++) {
                menu_ay_partitura_current_state[chip][canal][col][0]=0;
                menu_ay_partitura_current_state_duraciones[chip][canal][col]=0;

            }
        }
    }


}

void menu_ay_partitura_init_state_last_column(void)
{
			
    //printf ("ultima col %d\n",menu_ay_partitura_total_columns());
    menu_ay_partitura_ultima_columna[0]=menu_ay_partitura_total_columns()-1;
    menu_ay_partitura_ultima_columna[1]=menu_ay_partitura_total_columns()-1;
    menu_ay_partitura_ultima_columna[2]=menu_ay_partitura_total_columns()-1;
}

void menu_aysheet_change_chip(MENU_ITEM_PARAMETERS)
{
	menu_ay_partitura_chip++;
	if (menu_ay_partitura_chip==total_ay_chips) menu_ay_partitura_chip=0;
}

zxvision_window zxvision_window_ay_partitura;


void menu_ay_partitura(MENU_ITEM_PARAMETERS)
{



    menu_espera_no_tecla();

    if (!menu_multitarea) {
        menu_warn_message("This window needs multitask enabled");
        return;
    }		

    zxvision_window *ventana;
    ventana=&zxvision_window_ay_partitura;


    //IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
    //si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
    //la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
	zxvision_delete_window_if_exists(ventana);


    int xventana,yventana,ancho_ventana,alto_ventana,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;



    //Inicializar array de estado
    menu_ay_partitura_init_state();

    char *titulo_ventana="Au. Chip Sheet (60 BPM)";


    if (!util_find_window_geometry("aysheet",&xventana,&yventana,&ancho_ventana,&alto_ventana,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
                    
        xventana=PIANO_PARTITURA_GRAPHIC_BASE_X;
        yventana=PIANO_PARTITURA_GRAPHIC_BASE_Y;
        ancho_ventana=PIANO_PARTITURA_ANCHO_VENTANA;
        alto_ventana=PIANO_PARTITURA_ALTO_VENTANA;	

        int ancho_titulo=menu_da_ancho_titulo(titulo_ventana);

        //Para que se lea el titulo de la ventana en tamaño por defecto
        if (ancho_ventana<ancho_titulo) ancho_ventana=ancho_titulo;											

    }
				


		
    //int ancho_titulo=menu_da_ancho_titulo(titulo_ventana);

    //Para que siempre se lea el titulo de la ventana
    //No alteramos el ancho, que sea el que tenga por geometria
    //if (ancho_ventana<ancho_titulo) ancho_ventana=ancho_titulo;

    //printf ("ancho %d\n",ancho_ventana);

    zxvision_new_window_gn_cim(ventana,xventana,yventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,titulo_ventana,
        "aysheet",is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);

    //zxvision_new_window_nocheck_staticsize(ventana,xventana,yventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,titulo_ventana);


    ventana->can_be_backgrounded=1;	
    //indicar nombre del grabado de geometria
    //strcpy(ventana->geometry_name,"aysheet");
    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;        

    //decimos que tiene que borrar fondo cada vez al redibujar
    //por tanto es como decirle que no use cache de putchar
    //dado que el fondo de texto es casi todo texto con caracter " " eso borra los pixeles que metemos con overlay del frame anterior
    ventana->must_clear_cache_on_draw=1;      

    zxvision_draw_window(ventana);	


		
    //Comprobacion inicial de que el chip seleccionado no es mayor que los disponibles
    if (menu_ay_partitura_chip>=total_ay_chips) menu_ay_partitura_chip=0;


    //printf ("ancho creada %d\n",ventana->visible_width);	

    menu_ay_partitura_overlay_window=ventana;	

    menu_ay_partitura_init_state_last_column();	


    //Cambiamos funcion overlay de texto de menu
    //Se establece a la de funcion de piano + texto
    set_menu_overlay_function(menu_ay_partitura_overlay);


    //Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
    //Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
    if (zxvision_currently_restoring_windows_on_start) {
        //printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
        return;
    }		

	
    int retorno_menu=MENU_RETORNO_NORMAL; 
    //Inicializado aqui a MENU_RETORNO_NORMAL en particular pues si solo hay 1 chip, no muestra selector de chip
    //y por tanto esta variable tiene que tener algo diferente de MENU_RETORNO_BACKGROUND

    
    //Si solo hay 1 chip, no mostrar selector de chip
    if (total_ay_chips==1) {
        int tecla=zxvision_wait_until_esc(ventana);
        if (tecla==3) {
            //Truco para decir que nos vamos a background
            retorno_menu=MENU_RETORNO_BACKGROUND;
        }
    }

    else {
    
        //Los array de menu_item no tienen porque cambiar el nombre en cada sitio que se usen
        menu_item *array_menu_nonamed;
        menu_item item_seleccionado;

        int nonamed_opcion_seleccionada=0; //Solo 1 item de menu, no tiene sentido guardar posicion
    
        
        do {

        
            menu_add_item_menu_inicial_format(&array_menu_nonamed,MENU_OPCION_NORMAL,menu_aysheet_change_chip,NULL,"[%d] Selected ~~Chip",menu_ay_partitura_chip+1);
            menu_add_item_menu_shortcut(array_menu_nonamed,'c');

            //Evito tooltips en los menus tabulados que tienen overlay porque al salir el tooltip detiene el overlay
            //menu_add_item_menu_tooltip(array_menu_nonamed,"Change wave Shape");
            menu_add_item_menu_ayuda(array_menu_nonamed,"Change selected chip");
            menu_add_item_menu_tabulado(array_menu_nonamed,1,0);
        


            //Nombre de ventana solo aparece en el caso de stdout
            retorno_menu=menu_dibuja_menu(&nonamed_opcion_seleccionada,&item_seleccionado,array_menu_nonamed,"Audio Chip Sheet (60 BPM)" );


            if (retorno_menu!=MENU_RETORNO_BACKGROUND) {

                //En caso de menus tabulados, es responsabilidad de este de borrar la ventana
                cls_menu_overlay();
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                    //llamamos por valor de funcion
                    if (item_seleccionado.menu_funcion!=NULL) {
                        //printf ("actuamos por funcion\n");
                        item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                        //En caso de menus tabulados, es responsabilidad de este de borrar la ventana
                    }
                }
            }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus && retorno_menu!=MENU_RETORNO_BACKGROUND);		
    }



	//Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
	zxvision_set_window_overlay_from_current(ventana);				

	//restauramos modo normal de texto de menu
	set_menu_overlay_function(normal_overlay_texto_menu);


    cls_menu_overlay();

    util_add_window_geometry_compact(ventana);	


	if (retorno_menu==MENU_RETORNO_BACKGROUND) {
        zxvision_message_put_window_background();
	}

	else {
		zxvision_destroy_window(ventana);			
	}
	

}







void menu_record_mid_start(MENU_ITEM_PARAMETERS)
{
	
	if (mid_has_been_initialized()) {
		if (!menu_confirm_yesno_texto("Will empty buffer","Sure?")) return;
	}

	mid_initialize_export();
	mid_is_recording.v=1;
}



void menu_record_mid_stop(MENU_ITEM_PARAMETERS)
{
	if (mid_has_been_initialized()) {
		if (!menu_confirm_yesno_texto("Stop recording","Sure?")) return;
	}	
	mid_is_recording.v=0;
}


void menu_record_mid_pause_unpause(MENU_ITEM_PARAMETERS)
{
	mid_is_paused.v ^=1;
}

void menu_record_mid_save(MENU_ITEM_PARAMETERS)
{
        char file_save[PATH_MAX];

        char *filtros[2];

        filtros[0]="mid";
    filtros[1]=0;


    //guardamos directorio actual
    char directorio_actual[PATH_MAX];
    getcwd(directorio_actual,PATH_MAX);	

	//Obtenemos ultimo directorio visitado
        if (mid_export_file[0]!=0) {
                char directorio[PATH_MAX];
                util_get_dir(mid_export_file,directorio);
                //printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

                //cambiamos a ese directorio, siempre que no sea nulo
                if (directorio[0]!=0) {
                        debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
                        zvfs_chdir(directorio);
                }
        }	

    int ret;

        ret=menu_filesel("Mid file",filtros,file_save);

        //volvemos a directorio inicial
        zvfs_chdir(directorio_actual);		

        if (ret==1) {

                //Ver si archivo existe y preguntar
                if (si_existe_archivo(file_save)) {

                        if (menu_confirm_yesno_texto("File exists","Overwrite?")==0) return;

       			}

			strcpy(mid_export_file,file_save);
			mid_flush_file();

	        menu_generic_message_splash("Save MID","OK File saved");

 
        }
}

void menu_record_mid_noisetone(MENU_ITEM_PARAMETERS)
{
	mid_record_noisetone.v ^=1;	
}


void menu_record_mid_instrument(MENU_ITEM_PARAMETERS)
{


    //Dado que es una variable local, siempre podemos usar este nombre array_menu_common
    menu_item *array_menu_common;
    menu_item item_seleccionado;
    int retorno_menu;


    do {
                
        menu_add_item_menu_inicial(&array_menu_common,"",MENU_OPCION_UNASSIGNED,NULL,NULL);

        int i;

        for (i=0;i<128;i++) {                

            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,NULL,NULL,midi_instrument_list[i]);

        }



        menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

        menu_add_ESC_item(array_menu_common);

        retorno_menu=menu_dibuja_menu(&record_mid_instrument_opcion_seleccionada,&item_seleccionado,array_menu_common,"Instrument");

        if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
            //Cambiar instrumento y salir
            mid_instrument=record_mid_instrument_opcion_seleccionada;
            mid_set_cambio_instrumento();
            menu_generic_message_splash("Change instrument","OK. Instrument changed");
            return;
        }

    } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);


}

int menu_cond_ay_or_sn_chip(void)
{
	if (ay_chip_present.v || sn_chip_present.v || i8049_chip_present ) return 1;
	else return 0;
}

void menu_record_mid(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_record_mid;
	menu_item item_seleccionado;
	int retorno_menu;

        do {

                    menu_add_item_menu_inicial(&array_menu_record_mid,"",MENU_OPCION_UNASSIGNED,NULL,NULL);

					if (mid_is_recording.v==0) {
						menu_add_item_menu_en_es_ca(array_menu_record_mid,MENU_OPCION_NORMAL,menu_record_mid_start,menu_cond_ay_or_sn_chip,
                            "Start Recording","Iniciar Grabacion","Iniciar Gravacio");
					}

					else {
						menu_add_item_menu_en_es_ca(array_menu_record_mid,MENU_OPCION_NORMAL,menu_record_mid_stop,menu_cond_ay_or_sn_chip,
                            "Stop Recording","Detener Grabacion","Aturar Gravacio");
					}

				




					if (mid_is_recording.v) {

						if (mid_is_paused.v==0) {
							menu_add_item_menu_en_es_ca(array_menu_record_mid,MENU_OPCION_NORMAL,menu_record_mid_pause_unpause,menu_cond_ay_or_sn_chip,
                                "Pause Recording","Pausar Grabacion","Pausar Gravacio");
						}

						else {
							menu_add_item_menu_en_es_ca(array_menu_record_mid,MENU_OPCION_NORMAL,menu_record_mid_pause_unpause,menu_cond_ay_or_sn_chip,
                                "Resume Recording","Continuar Grabacion","Continuar Gravacio");
						}		


                        
					}

					//No dejamos grabar hasta que no se haga stop
					//porque el flush del final mete cabeceras de final de pistas y ya no se puede reaprovechar
					if (mid_has_been_initialized() && mid_notes_recorded && mid_is_recording.v==0) {
						menu_add_item_menu_en_es_ca(array_menu_record_mid,MENU_OPCION_NORMAL,menu_record_mid_save,menu_cond_ay_or_sn_chip,
                            "Save .MID file","Grabar archivo .MID","Gravar arxiu .MID");
					}


					menu_add_item_menu_format(array_menu_record_mid,MENU_OPCION_SEPARADOR,NULL,NULL,"");
					menu_add_item_menu_format(array_menu_record_mid,MENU_OPCION_NORMAL,menu_record_mid_noisetone,NULL,"[%c] Allow tone+noise",
						(mid_record_noisetone.v ? 'X' : ' ') );
					menu_add_item_menu_tooltip(array_menu_record_mid,"Record also channels enabled as tone+noise");
					menu_add_item_menu_ayuda(array_menu_record_mid,"Record also channels enabled as tone+noise");


                    menu_add_item_menu_en_es_ca(array_menu_record_mid,MENU_OPCION_NORMAL,menu_record_mid_instrument,NULL,
                        "Change Instrument","Cambiar Instrumento","Canviar Instrument");
                    menu_add_item_menu_tiene_submenu(array_menu_record_mid);

					if (mid_notes_recorded) {

						int max_buffer=mid_max_buffer();
						

						int max_buffer_perc=(max_buffer*100)/MAX_MID_EXPORT_BUFFER;

						//printf ("%d %d\n",max_buffer,max_buffer_perc);


						menu_add_item_menu_format(array_menu_record_mid,MENU_OPCION_SEPARADOR,NULL,NULL,"");
						menu_add_item_menu_format(array_menu_record_mid,MENU_OPCION_SEPARADOR,NULL,NULL,"Info:");
						menu_add_item_menu_format(array_menu_record_mid,MENU_OPCION_SEPARADOR,NULL,NULL,"Buffer used: %d%%",max_buffer_perc);
						menu_add_item_menu_format(array_menu_record_mid,MENU_OPCION_SEPARADOR,NULL,NULL,"Voices: %d",3*mid_chips_al_start);
						menu_add_item_menu_format(array_menu_record_mid,MENU_OPCION_SEPARADOR,NULL,NULL,"Notes recorded: %d",mid_notes_recorded);
						

					}					
		
					



                menu_add_item_menu(array_menu_record_mid,"",MENU_OPCION_SEPARADOR,NULL,NULL);


                //menu_add_item_menu(array_menu_record_mid,"ESC Back",MENU_OPCION_NORMAL|MENU_OPCION_ESC,NULL,NULL);
		menu_add_ESC_item(array_menu_record_mid);

                retorno_menu=menu_dibuja_menu(&record_mid_opcion_seleccionada,&item_seleccionado,array_menu_record_mid,"Audio Chip to .mid" );

                

		if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
	                //llamamos por valor de funcion
        	        if (item_seleccionado.menu_funcion!=NULL) {
                	        //printf ("actuamos por funcion\n");
	                        item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
							
        	        }
		}

	} while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);
}



//Funcion comun de midi output de alsa y coreaudio
void menu_midi_output_noisetone(MENU_ITEM_PARAMETERS)
{
	midi_output_record_noisetone.v ^=1;
}

//Funcion comun de midi output de alsa y coreaudio
void menu_midi_output_initialize(MENU_ITEM_PARAMETERS)
{
	


	if (audio_midi_output_initialized==0) {
		if (audio_midi_output_init() ) {
			menu_error_message("Error initializing midi device");
		}
	}
	else {
		audio_midi_output_finish();
		audio_midi_output_initialized=0;
	}	
}

int menu_midi_output_initialized_cond(void)
{
	return !audio_midi_output_initialized;
}


void menu_midi_output_client(MENU_ITEM_PARAMETERS)
{
        char string_valor[4];
        int valor;


        sprintf (string_valor,"%d",audio_midi_client);


        menu_ventana_scanf("Client value",string_valor,4);

        valor=parse_string_to_number(string_valor);
	if (valor<0 || valor>255) {
		menu_error_message("Invalid client value");
	}


	audio_midi_client=valor;

}

void menu_midi_output_port(MENU_ITEM_PARAMETERS)
{
        char string_valor[4];
        int valor;


        sprintf (string_valor,"%d",audio_midi_port);


        menu_ventana_scanf("Port value",string_valor,4);

        valor=parse_string_to_number(string_valor);
        if (valor<0 || valor>255) {
                menu_error_message("Invalid client value");
        }


        audio_midi_port=valor;

}



//Listar dispositivos midi. Solo tiene sentido esto en Linux
void menu_direct_alsa_midi_output_list_devices(MENU_ITEM_PARAMETERS) 
{

	char *device_list="/proc/asound/seq/clients";

	if (!si_existe_archivo(device_list)) {
		menu_error_message("Can not find device list");
		return;
	}

	//Abrir archivo y mostrarlo en ventana
	//Usamos esta funcion generica de mostrar archivos de ayuda
	menu_about_read_file("Sequencer devices",device_list,1);

}


void menu_direct_midi_output_rawmode(MENU_ITEM_PARAMETERS)
{
	audio_midi_raw_mode ^=1;
}

#ifdef COMPILE_ALSA
void menu_direct_alsa_midi_device_raw(MENU_ITEM_PARAMETERS)
{
    menu_ventana_scanf("MIDI device name",audio_raw_midi_device_out,MAX_AUDIO_RAW_MIDI_DEVICE_OUT);

}
#endif


void menu_midi_output_test(MENU_ITEM_PARAMETERS)
{
	//audio_midi_output_note_on(0, 60); //60=central DO

	// Does it sound familiar? ;)
	audio_midi_output_note_on(0, 61); //61=C#

	audio_midi_output_note_on(0, 58); //58=A#

	audio_midi_output_note_on(0, 54); //54=F#
}


void menu_midi_output_reset(MENU_ITEM_PARAMETERS)
{
	audio_midi_output_reset();

}


void menu_midi_output_instrument(MENU_ITEM_PARAMETERS)
{


    //Dado que es una variable local, siempre podemos usar este nombre array_menu_common
    menu_item *array_menu_common;
    menu_item item_seleccionado;
    int retorno_menu;


    do {
                
        menu_add_item_menu_inicial(&array_menu_common,"",MENU_OPCION_UNASSIGNED,NULL,NULL);

        int i;

        for (i=0;i<128;i++) {                

            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,NULL,NULL,midi_instrument_list[i]);

        }



        menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

        menu_add_ESC_item(array_menu_common);

        retorno_menu=menu_dibuja_menu(&midi_output_instrument_opcion_seleccionada,&item_seleccionado,array_menu_common,"Instrument");

        if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
            //Cambiar instrumento y salir
            audio_midi_set_instrument(midi_output_instrument_opcion_seleccionada);
            return;
        }

    } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);


}


void menu_direct_midi_output(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_direct_midi_output;
	menu_item item_seleccionado;
	int retorno_menu;

        do {


		menu_add_item_menu_inicial(&array_menu_direct_midi_output,"",MENU_OPCION_UNASSIGNED,NULL,NULL);



#ifdef COMPILE_ALSA
		//En Alsa Linux
		menu_add_item_menu_format(array_menu_direct_midi_output,MENU_OPCION_NORMAL,menu_direct_midi_output_rawmode,menu_midi_output_initialized_cond,"[%c] MIDI Raw mode",(audio_midi_raw_mode ? 'X' : ' ' ));
		menu_add_item_menu_tooltip(array_menu_direct_midi_output,"RAW mode is needed to emulate AY MIDI registers");
		menu_add_item_menu_ayuda(array_menu_direct_midi_output,"RAW mode is needed to emulate AY MIDI registers");

		if (audio_midi_raw_mode) {


                char string_device_shown[10];
                menu_tape_settings_trunc_name(audio_raw_midi_device_out,string_device_shown,10);

			menu_add_item_menu_format(array_menu_direct_midi_output,MENU_OPCION_NORMAL,menu_direct_alsa_midi_device_raw,menu_midi_output_initialized_cond,"Device: %s",string_device_shown);
		}

		else {
			menu_add_item_menu_format(array_menu_direct_midi_output,MENU_OPCION_NORMAL,menu_direct_alsa_midi_output_list_devices,NULL,"List midi devices");
			menu_add_item_menu_format(array_menu_direct_midi_output,MENU_OPCION_NORMAL,menu_midi_output_client,menu_midi_output_initialized_cond,"[%d] Midi client",audio_midi_client);
			menu_add_item_menu_format(array_menu_direct_midi_output,MENU_OPCION_NORMAL,menu_midi_output_port,menu_midi_output_initialized_cond,"[%d] Midi port",audio_midi_port);
		}
#endif

#ifdef MINGW
		//en Windows
		menu_add_item_menu_format(array_menu_direct_midi_output,MENU_OPCION_NORMAL,menu_midi_output_port,menu_midi_output_initialized_cond,"[%d] Midi port",audio_midi_port);
#endif

 
	
		/*if (audio_midi_output_initialized==0) {
			menu_add_item_menu_format(array_menu_direct_midi_output,MENU_OPCION_NORMAL,menu_midi_output_initialize,NULL,"Initialize midi");
		}
		else {
			menu_add_item_menu_format(array_menu_direct_midi_output,MENU_OPCION_NORMAL,menu_midi_output_initialize,NULL,"Disable midi");
		}*/

		menu_add_item_menu_format(array_menu_direct_midi_output,MENU_OPCION_NORMAL,menu_midi_output_initialize,NULL,"[%c] Initialized",
			(audio_midi_output_initialized ? 'X' : ' ' ) );


		if (audio_midi_output_initialized) {
			menu_add_item_menu_format(array_menu_direct_midi_output,MENU_OPCION_NORMAL,menu_midi_output_test,NULL,"Test MIDI");

            menu_add_item_menu_format(array_menu_direct_midi_output,MENU_OPCION_NORMAL,menu_midi_output_instrument,NULL,"Change instrument");


			menu_add_item_menu_format(array_menu_direct_midi_output,MENU_OPCION_NORMAL,menu_midi_output_reset,NULL,"Reset channels");
		}

		//Parece que no funciona la gestion de volumen
		//menu_add_item_menu_format(array_menu_direct_alsa_midi_output,MENU_OPCION_NORMAL,menu_direct_alsa_midi_output_volume,NULL,"Volume: %d%%",alsa_midi_volume);



					menu_add_item_menu_format(array_menu_direct_midi_output,MENU_OPCION_SEPARADOR,NULL,NULL,"");
					menu_add_item_menu_format(array_menu_direct_midi_output,MENU_OPCION_NORMAL,menu_midi_output_noisetone,NULL,"[%c] Allow tone+noise",
						(midi_output_record_noisetone.v ? 'X' : ' ') );
					menu_add_item_menu_tooltip(array_menu_direct_midi_output,"Send also channels enabled as tone+noise");
					menu_add_item_menu_ayuda(array_menu_direct_midi_output,"Send also channels enabled as tone+noise");


                menu_add_item_menu(array_menu_direct_midi_output,"",MENU_OPCION_SEPARADOR,NULL,NULL);


                //menu_add_item_menu(array_menu_direct_midi_output,"ESC Back",MENU_OPCION_NORMAL|MENU_OPCION_ESC,NULL,NULL);
		menu_add_ESC_item(array_menu_direct_midi_output);

                retorno_menu=menu_dibuja_menu(&direct_midi_output_opcion_seleccionada,&item_seleccionado,array_menu_direct_midi_output,"Audio Chip to MIDI output" );



		if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
	                //llamamos por valor de funcion
        	        if (item_seleccionado.menu_funcion!=NULL) {
                	        //printf ("actuamos por funcion\n");
	                        item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);

        	        }
		}

	} while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);
}







//cambia filtro
void menu_ay_mixer_cambia_filtro(MENU_ITEM_PARAMETERS)
{

	int chip=valor_opcion/3;
	int canal=valor_opcion % 3;

	//printf ("chip %d canal %d\n",chip,canal);

	z80_byte valor_filtro=ay_filtros[chip];
	z80_byte mascara=1|8; //bits xxxx1xx1

	z80_byte mascara_ceros=1|8;

	if (canal>0) {
		mascara=mascara<<canal;
		mascara_ceros=mascara_ceros<<canal;
	}

	//aplicar mascara
	valor_filtro &=mascara;

	//Normalizar
	if (canal>0) valor_filtro=valor_filtro>>canal;


	//Valores posibles 0,1,8,9
	if (valor_filtro==0) valor_filtro=1;
	else if (valor_filtro==1) valor_filtro=8;
	else if (valor_filtro==8) valor_filtro=9;
	else valor_filtro=0;

	//Volver a meter donde estaba
	if (canal>0) {
		valor_filtro=valor_filtro<<canal;
	}

	mascara_ceros=255-mascara_ceros;

	//Poner a ceros los que habia
	ay_filtros[chip] &=mascara_ceros;

	//Poner filtro actual
	ay_filtros[chip] |=valor_filtro;
	
}

//Muestra cadena filtro
void menu_ay_mixer_retorna_filtro(int chip,int canal,char *destino)
{
	z80_byte valor_filtro=ay_filtros[chip];
	z80_byte mascara=1|8; //bits xxxx1xx1

	if (canal>0) mascara=mascara<<canal;

	//aplicar mascara
	valor_filtro &=mascara;

	//Normalizar
	if (canal>0) valor_filtro=valor_filtro>>canal;

	//Posibles valores: 0,1,8,9
	switch (valor_filtro) {
		case 0:
			strcpy(destino,"No filter");
		break;

		case 1:
			strcpy(destino,"No tone  ");
		break;

		case 8:
			strcpy(destino,"No noise ");
		break;		

		//case 9:
		default:
			strcpy(destino,"Silence  ");
		break;			

	}

	return;
}


void menu_audio_envelopes(MENU_ITEM_PARAMETERS)
{
	ay_envelopes_enabled.v^=1;
}

void menu_audio_speech(MENU_ITEM_PARAMETERS)
{
        ay_speech_enabled.v^=1;
}

void menu_audio_aymid_rs232(MENU_ITEM_PARAMETERS)
{
        aymidi_rs232_enabled.v^=1;
}

void menu_audio_ay_stereo_custom_A(MENU_ITEM_PARAMETERS)
{
	ay3_custom_stereo_A++;
	if (ay3_custom_stereo_A==3) ay3_custom_stereo_A=0;
}

void menu_audio_ay_stereo_custom_B(MENU_ITEM_PARAMETERS)
{
	ay3_custom_stereo_B++;
	if (ay3_custom_stereo_B==3) ay3_custom_stereo_B=0;
}

void menu_audio_ay_stereo_custom_C(MENU_ITEM_PARAMETERS)
{
	ay3_custom_stereo_C++;
	if (ay3_custom_stereo_C==3) ay3_custom_stereo_C=0;
}

void menu_audio_ay_stereo(MENU_ITEM_PARAMETERS)
{
	ay3_stereo_mode++;

	if (ay3_stereo_mode==6) ay3_stereo_mode=0;
}


char *menu_stereo_positions[]={
	"Left",
	"    Center",
	"          Right"
};

void menu_ay_mixer(MENU_ITEM_PARAMETERS)
{
menu_item *array_menu_ay_mixer;
	menu_item item_seleccionado;
	int retorno_menu;

	char buffer_filtro[33];
	

        do {


		menu_add_item_menu_inicial_format(&array_menu_ay_mixer,MENU_OPCION_NORMAL,menu_audio_envelopes,menu_cond_ay_chip,"[%c] AY ~~Envelopes", (ay_envelopes_enabled.v==1 ? 'X' : ' '));
		menu_add_item_menu_shortcut(array_menu_ay_mixer,'e');
		menu_add_item_menu_tooltip(array_menu_ay_mixer,"Enable or disable volume envelopes for the AY Chip");
		menu_add_item_menu_ayuda(array_menu_ay_mixer,"Enable or disable volume envelopes for the AY Chip");

		menu_add_item_menu_format(array_menu_ay_mixer,MENU_OPCION_NORMAL,menu_audio_speech,menu_cond_ay_chip,"[%c] AY ~~Speech", (ay_speech_enabled.v==1 ? 'X' : ' '));
		menu_add_item_menu_shortcut(array_menu_ay_mixer,'s');
		menu_add_item_menu_tooltip(array_menu_ay_mixer,"Enable or disable AY Speech effects");
		menu_add_item_menu_ayuda(array_menu_ay_mixer,"These effects are used, for example, in Chase H.Q.");


		menu_add_item_menu_format(array_menu_ay_mixer,MENU_OPCION_NORMAL,menu_audio_aymid_rs232,menu_cond_ay_chip,"[%c] AY ~~MIDI registers", (aymidi_rs232_enabled.v==1 ? 'X' : ' '));
		menu_add_item_menu_shortcut(array_menu_ay_mixer,'m');
		menu_add_item_menu_tooltip(array_menu_ay_mixer,"Enable or disable AY MIDI registers");
		menu_add_item_menu_ayuda(array_menu_ay_mixer,"It handles values sent to register 14 and 15");


		if (MACHINE_IS_SPECTRUM || MACHINE_IS_MSX || MACHINE_IS_SVI || MACHINE_IS_CPC) {


			char ay3_stereo_string[16];
			if (ay3_stereo_mode==1) strcpy(ay3_stereo_string,"ACB");
			else if (ay3_stereo_mode==2) strcpy(ay3_stereo_string,"ABC");
			else if (ay3_stereo_mode==3) strcpy(ay3_stereo_string,"BAC");
			else if (ay3_stereo_mode==4) strcpy(ay3_stereo_string,"CBA");
            else if (ay3_stereo_mode==5) strcpy(ay3_stereo_string,"Custom");
			else strcpy(ay3_stereo_string,"Mono");
            /*
            CBA Es para Amstrad CPC:
            Mono and Stereo Output
            When using the CPC's external stereo jack, 
            channel A is output to the right, channel C is output left, 
            and channel B is output to both left and right,   
            in that case channel B is output through a bigger resistor to prevent that this channel appears loader than the others.

            Otherwise (when using the built-in speaker), all three channels are mixed at the same intensity. 
            This signal appears to be also sent to the Tape output line also, so a connected Data Recorder could be used to record CPC music also.

            */

			menu_add_item_menu_format(array_menu_ay_mixer,MENU_OPCION_NORMAL,menu_audio_ay_stereo,menu_cond_ay_chip,"    AY S~~tereo: %s",
				ay3_stereo_string);
			menu_add_item_menu_shortcut(array_menu_ay_mixer,'t');

			if (ay3_stereo_mode==5) {	

				menu_add_item_menu_format(array_menu_ay_mixer,MENU_OPCION_NORMAL,menu_audio_ay_stereo_custom_A,menu_cond_ay_chip,
					"    Ch. A: %s",menu_stereo_positions[ay3_custom_stereo_A]);

				menu_add_item_menu_format(array_menu_ay_mixer,MENU_OPCION_NORMAL,menu_audio_ay_stereo_custom_B,menu_cond_ay_chip,
					"    Ch. B: %s",menu_stereo_positions[ay3_custom_stereo_B]);

				menu_add_item_menu_format(array_menu_ay_mixer,MENU_OPCION_NORMAL,menu_audio_ay_stereo_custom_C,menu_cond_ay_chip,
					"    Ch. C: %s",menu_stereo_positions[ay3_custom_stereo_C]);								


			}

		}		



			int chip;

			for (chip=0;chip<ay_retorna_numero_chips();chip++) {
				int canal;
				menu_add_item_menu_format(array_menu_ay_mixer,MENU_OPCION_SEPARADOR,NULL,NULL,"---Chip %d---",chip+1);

				for (canal=0;canal<3;canal++) {
					menu_ay_mixer_retorna_filtro(chip,canal,buffer_filtro);
					menu_add_item_menu_format(array_menu_ay_mixer,MENU_OPCION_NORMAL,menu_ay_mixer_cambia_filtro,NULL,"[%s] Channel %c",buffer_filtro,'A'+canal);

					menu_add_item_menu_valor_opcion(array_menu_ay_mixer,chip*3+canal);

				}
			}

		


                menu_add_item_menu(array_menu_ay_mixer,"",MENU_OPCION_SEPARADOR,NULL,NULL);


                //menu_add_item_menu(array_menu_ay_mixer,"ESC Back",MENU_OPCION_NORMAL|MENU_OPCION_ESC,NULL,NULL);
		menu_add_ESC_item(array_menu_ay_mixer);

                retorno_menu=menu_dibuja_menu(&ay_mixer_opcion_seleccionada,&item_seleccionado,array_menu_ay_mixer,"AY mixer" );



		if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
	                //llamamos por valor de funcion
        	        if (item_seleccionado.menu_funcion!=NULL) {
                	        //printf ("actuamos por funcion\n");
	                        item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);

        	        }
		}

	} while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);	
}


void menu_i8049_mixer_pitch2(MENU_ITEM_PARAMETERS)
{
    ql_sound_feature_pitch2_enabled ^=1; 
}

void menu_i8049_mixer_grad_x(MENU_ITEM_PARAMETERS)
{
    ql_sound_feature_grad_x_enabled ^=1; 
}

void menu_i8049_mixer_grad_y(MENU_ITEM_PARAMETERS)
{
    ql_sound_feature_grad_y_enabled ^=1; 
}

void menu_i8049_mixer_wrap(MENU_ITEM_PARAMETERS)
{
    ql_sound_feature_wrap_enabled ^=1; 
}


void menu_i8049_mixer_fuzzy(MENU_ITEM_PARAMETERS)
{
    ql_sound_feature_fuzzy_enabled ^=1; 
}


void menu_i8049_mixer_random(MENU_ITEM_PARAMETERS)
{
    ql_sound_feature_random_enabled ^=1; 
}

void menu_i8049_mixer_stop_sound(MENU_ITEM_PARAMETERS)
{
    ql_stop_sound();
}

void menu_i8049_mixer(MENU_ITEM_PARAMETERS)
{
    menu_item *array_menu_common;
    menu_item item_seleccionado;
    int retorno_menu;




    do {
/*
    if (!ql_sound_feature_pitch2_enabled) ql_audio_pitch2=0;
    if (!ql_sound_feature_grad_x_enabled) ql_audio_grad_x=0;
    if (!ql_sound_feature_grad_y_enabled) ql_audio_grad_y=0;

    if (!ql_sound_feature_wrap_enabled) ql_audio_wrap=0;
    if (!ql_sound_feature_fuzzy_enabled) ql_audio_fuziness=0;
    if (!ql_sound_feature_random_enabled) ql_audio_randomness_of_step=0;
    */

        menu_add_item_menu_inicial_format(&array_menu_common,MENU_OPCION_NORMAL,menu_i8049_mixer_pitch2,NULL,"[%c] Pitch 2", (ql_sound_feature_pitch2_enabled ? 'X' : ' '));

        menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_i8049_mixer_grad_x,NULL,"[%c] Grad_x", (ql_sound_feature_grad_x_enabled ? 'X' : ' '));

        menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_i8049_mixer_grad_y,NULL,"[%c] Grad_y", (ql_sound_feature_grad_y_enabled ? 'X' : ' '));

        menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_i8049_mixer_wrap,NULL,"[%c] Wrap", (ql_sound_feature_wrap_enabled ? 'X' : ' '));

        menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_i8049_mixer_fuzzy,NULL,"[%c] Fuzzy", (ql_sound_feature_fuzzy_enabled ? 'X' : ' '));

        menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_i8049_mixer_random,NULL,"[%c] Random", (ql_sound_feature_random_enabled ? 'X' : ' '));

        menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

        menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_i8049_mixer_stop_sound,NULL,"    Stop sound");


        menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);



        menu_add_ESC_item(array_menu_common);

        retorno_menu=menu_dibuja_menu(&i8049_mixer_opcion_seleccionada,&item_seleccionado,array_menu_common,"i8049 mixer" );



        if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
            //llamamos por valor de funcion
            if (item_seleccionado.menu_funcion!=NULL) {
                //printf ("actuamos por funcion\n");
                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);

            }
        }

    } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);	
}


void menu_audio_chip_info(MENU_ITEM_PARAMETERS)
{

	int chip_frequency;
	int max_freq,min_freq;

	if (sn_chip_present.v) {
		//Chip SN
		chip_frequency=sn_chip_frequency;
		max_freq=sn_retorna_frecuencia_valor_registro(0,0);
		min_freq=sn_retorna_frecuencia_valor_registro(255,255);
	}

	else if (i8049_chip_present) {
		//Chip 8049 del QL
		chip_frequency=ql_i8049_sound_chip_frequency;
		max_freq=ql_ipc_get_frecuency_sound_value(1);
		min_freq=ql_ipc_get_frecuency_sound_value(255);
	}

	else {
		//Chip AY
		chip_frequency=ay_chip_frequency;
		max_freq=ay_retorna_frecuencia_valor_registro(0,0);
		min_freq=ay_retorna_frecuencia_valor_registro(255,255);		
	}

	
	if (sn_chip_present.v) {
		//SN
		menu_generic_message_format("Audio Chip Info","Audio Chip: Texas Instruments SN76489AN\nFrequency: %d Hz\n"
									"Min Tone Frequency: %d Hz\nMax Tone Frequency: %d Hz\n"
									"3 Tone Channels, 1 Noise Channel",
			chip_frequency,min_freq,max_freq
		);
	}

	else if (i8049_chip_present) {
		//8049 del QL
		menu_generic_message_format("Audio Chip Info","Audio Chip: Intel 8049\nFrequency: %d MHz\n"
									"Min Tone Frequency: %d Hz\nMax Tone Frequency: %d Hz\n"
									"2 PseudoTone Channels, Noise Effects",
			chip_frequency/1000000,min_freq,max_freq
		);
	}

	else {
		//AY
		menu_generic_message_format("Audio Chip Info","Audio Chip: General Instrument AY-3-8910\nFrequency: %d Hz\n"
									"Min Tone Frequency: %d Hz\nMax Tone Frequency: %d Hz\n"
									"3 Noise/Tone Channels, 1 Envelope Generator",
			chip_frequency,min_freq,max_freq
		);		
	}


}


void menu_uartbridge_file(MENU_ITEM_PARAMETERS)
{
	uartbridge_disable();

        char *filtros[2];

        filtros[0]="";
        filtros[1]=0;


        if (menu_filesel("Select Device File",filtros,uartbridge_name)==1) {
                if (!si_existe_archivo(uartbridge_name)) {
                        menu_error_message("File does not exist");
                        uartbridge_name[0]=0;
                        return;
                }


        }
        //Sale con ESC
        else {
                //Quitar nombre
                uartbridge_name[0]=0;


        }

}


void menu_uartbridge_enable(MENU_ITEM_PARAMETERS)
{
	if (uartbridge_enabled.v) uartbridge_disable();
	else uartbridge_enable();
}


int menu_uartbridge_cond(void)
{
	if (uartbridge_name[0]==0) return 0;

	else return 1;

}


int menu_uartbridge_speed_cond(void)
{
	if (uartbridge_enabled.v) return 0;

	else return 1;

}

void menu_uartbridge_speed(MENU_ITEM_PARAMETERS)
{
	if (uartbridge_speed==CHDEV_SPEED_115200) uartbridge_speed=CHDEV_SPEED_DEFAULT;
	else uartbridge_speed++;
}



void menu_uartbridge(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_uartbridge;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

                char string_uartbridge_file_shown[13];

			
                        menu_tape_settings_trunc_name(uartbridge_name,string_uartbridge_file_shown,13);
                        menu_add_item_menu_inicial_format(&array_menu_uartbridge,MENU_OPCION_NORMAL,menu_uartbridge_file,NULL,"~~File [%s]",string_uartbridge_file_shown);
                        menu_add_item_menu_shortcut(array_menu_uartbridge,'f');
                        menu_add_item_menu_tooltip(array_menu_uartbridge,"Path to the serial device");
                        menu_add_item_menu_ayuda(array_menu_uartbridge,"Path to the serial device");


						//Lo separamos en dos pues cuando no esta habilitado, tiene que comprobar que el path no sea nulo
						if (uartbridge_enabled.v) {
							menu_add_item_menu_format(array_menu_uartbridge,MENU_OPCION_NORMAL,menu_uartbridge_enable,NULL,"[X] ~~Enabled");
						}
						else {
							menu_add_item_menu_format(array_menu_uartbridge,MENU_OPCION_NORMAL,menu_uartbridge_enable,menu_uartbridge_cond,"[ ] ~~Enabled");
						}	
						menu_add_item_menu_shortcut(array_menu_uartbridge,'e');


#ifndef MINGW

						if (uartbridge_speed==CHDEV_SPEED_DEFAULT) {
							menu_add_item_menu_format(array_menu_uartbridge,MENU_OPCION_NORMAL,menu_uartbridge_speed,menu_uartbridge_speed_cond,"[Default] Speed");
						}
						else {
							menu_add_item_menu_format(array_menu_uartbridge,MENU_OPCION_NORMAL,menu_uartbridge_speed,menu_uartbridge_speed_cond,"[%d] Speed",
							chardevice_getspeed_enum_int(uartbridge_speed));
						}

#endif
					

                        menu_add_item_menu(array_menu_uartbridge,"",MENU_OPCION_SEPARADOR,NULL,NULL);

                menu_add_ESC_item(array_menu_uartbridge);

                retorno_menu=menu_dibuja_menu(&uartbridge_opcion_seleccionada,&item_seleccionado,array_menu_uartbridge,"UART Bridge" );

                
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




}



int menu_network_uartbridge_cond(void)
{
	if (MACHINE_IS_ZXUNO || MACHINE_IS_TBBLUE || MACHINE_IS_TSCONF) return 1;
	else return 0;
}



int contador_menu_zeng_connect_print=0;



void menu_common_connect_print(zxvision_window *w,char *texto)
{
	char *mensaje="|/-\\";

	int max=strlen(mensaje);
    //Suficiente para que quepa el texto
	char mensaje_dest[NETWORK_MAX_URL+256];

	int pos=contador_menu_zeng_connect_print % max;

	sprintf(mensaje_dest,"%s %c",texto,mensaje[pos]);
	//printf ("pos: %d\n",pos);

	//zxvision_print_string_defaults_fillspc(w,1,0,mensaje_dest);	

    //Escribir el texto troceado
    //en el caso de haber llamado aqui desde menu_download_file_connect_print,
    //igual no tiene mucho sentido trocear pues ya estamos cortando el texto para que quepa en una sola linea
    zxvision_print_mensaje_lineas_troceado(w,mensaje_dest);

	zxvision_draw_window_contents(w);

	contador_menu_zeng_connect_print++;

}

//Para indicar desde que host se hace conexion
char menu_zeng_connect_print_host[NETWORK_MAX_URL]="";
void menu_zeng_connect_print(zxvision_window *w)
{
    char buf_temp[NETWORK_MAX_URL+256];
    sprintf(buf_temp,"Connecting to %s",menu_zeng_connect_print_host);    
	//menu_common_connect_print(w,"Connecting");
    menu_common_connect_print(w,buf_temp);
}

//Para indicar desde que host se hace descarga
char menu_download_file_connect_print_host[NETWORK_MAX_URL]="";
void menu_download_file_connect_print(zxvision_window *w)
{
    char buf_temp[NETWORK_MAX_URL+256];
    sprintf(buf_temp,"Downloading from %s",menu_download_file_connect_print_host);

    //darle espacio para meter el caracter de progreso al final
    //-2 de lo habitual en ancho visible y -2 para poder agregar un espacio y el caracter de progreso
    int max_visible_width=w->visible_width-4;

    int longitud_texto=strlen(buf_temp);
    if (longitud_texto>max_visible_width) {
        buf_temp[max_visible_width]=0;
    }

	//menu_common_connect_print(w,"Downloading");
    menu_common_connect_print(w,buf_temp);
}

int menu_zeng_connect_cond(zxvision_window *w GCC_UNUSED)
{
	return !zeng_enable_thread_running;
}

void menu_zeng_enable_disable(MENU_ITEM_PARAMETERS)
{
	if (zeng_enabled.v) {
		zeng_disable();
	}
	else {

		//Activamos ZRCP, que es lo logico, si es que no esta habilitado ya
		if (remote_protocol_enabled.v==0) enable_and_init_remote_protocol();		



		//Lanzar el thread de activacion
		zeng_enable();
		 
		contador_menu_zeng_connect_print=0;

        
        strcpy(menu_zeng_connect_print_host,zeng_remote_hostname);
		zxvision_simple_progress_window("ZENG connection", menu_zeng_connect_cond,menu_zeng_connect_print );


		
		//menu_footer_bottom_line();
	}
}

int menu_zeng_enable_disable_cond(void)
{
	

	
	//Si esta habilitado, opcion siempre disponible para desactivar
	if (zeng_enabled.v) return 1;



	else {
		//Si esta hostname vacio
		if (zeng_remote_hostname[0]==0) return 0;
	}

	return 1;
}


//Si esta habilitado, no se puede cambiar parametro
int menu_zeng_host_cond(void)
{
	if (zeng_enabled.v) return 0;
	else return 1;
}

void menu_zeng_host(MENU_ITEM_PARAMETERS)
{

	menu_ventana_scanf("Remote host",zeng_remote_hostname,MAX_ZENG_HOSTNAME);
	
}


void menu_zeng_port(MENU_ITEM_PARAMETERS)
{


        char string_port[6];


        sprintf (string_port,"%d",zeng_remote_port);


	menu_ventana_scanf("Remote port",string_port,6);
	int numero=parse_string_to_number(string_port);
	if (numero<1 || numero>65535) {
		menu_error_message("Invalid port number");
		return;
	}

	zeng_remote_port=numero;

	
}

void menu_zeng_master(MENU_ITEM_PARAMETERS)
{
	zeng_i_am_master ^=1;	
}


void menu_zeng_snapshot_seconds(MENU_ITEM_PARAMETERS)
{

		char string_seconds[2];

		sprintf (string_seconds,"%d",zeng_segundos_cada_snapshot);


		menu_ventana_scanf("Snapshot seconds?",string_seconds,2);
		int numero=parse_string_to_number(string_seconds);

		if (numero<1 || numero>9) {
			menu_error_message("Invalid interval");
			return;
		}


		zeng_segundos_cada_snapshot=numero;

}


void menu_zeng_send_message(MENU_ITEM_PARAMETERS)
{
	char string_mensaje[AUTOSELECTOPTIONS_MAX_FOOTER_LENGTH];
	string_mensaje[0]=0;

	menu_ventana_scanf("Message?",string_mensaje,AUTOSELECTOPTIONS_MAX_FOOTER_LENGTH);	

	zeng_add_pending_send_message_footer(string_mensaje);
}


int menu_zeng_send_message_cond(void)
{
	//Si hay un mensaje pendiente de enviar, no permitir aun
	//Comprobamos tambien que zeng_enabled.v, esto no se usa en menu pero si en tecla directa F
	if (zeng_enabled.v==0) return 0;
	if (pending_zeng_send_message_footer) return 0;

	return 1;
}

void menu_zeng_cancel_connect(MENU_ITEM_PARAMETERS)
{
	if (menu_confirm_yesno_texto("Still connecting","Cancel?")) {
		//printf ("cancelling zeng connect\n");
		zeng_cancel_connect();
	}
}


void menu_zeng_snapshot_force_reconnect(MENU_ITEM_PARAMETERS)
{
    zeng_force_reconnect_failed_retries.v ^=1;
}

void menu_zeng(MENU_ITEM_PARAMETERS)
{
        //Dado que es una variable local, siempre podemos usar este nombre array_menu_common
        menu_item *array_menu_common;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

			menu_add_item_menu_inicial(&array_menu_common,"",MENU_OPCION_UNASSIGNED,NULL,NULL);

			//Si esta thread de conexion ejecutandose, mostrar otra opcion
			if (zeng_enable_thread_running) {
				menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_zeng_cancel_connect,NULL,"Connecting...");
			}

            else {
            	menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_zeng_enable_disable,menu_zeng_enable_disable_cond,"[%c] ~~Enabled",(zeng_enabled.v ? 'X' : ' ') );
				menu_add_item_menu_shortcut(array_menu_common,'e');
			}

			char string_host_shown[16]; 
			menu_tape_settings_trunc_name(zeng_remote_hostname,string_host_shown,16);
			menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_zeng_host,menu_zeng_host_cond,"~~Host [%s]",string_host_shown);
			menu_add_item_menu_shortcut(array_menu_common,'h');


			menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_zeng_port,menu_zeng_host_cond,"[%d] Remote Port",zeng_remote_port);
			menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_zeng_master,menu_zeng_host_cond,"[%c] ~~Master",(zeng_i_am_master ? 'X' : ' ') );
			menu_add_item_menu_shortcut(array_menu_common,'m');

			if (zeng_i_am_master) {
				menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_zeng_snapshot_seconds,NULL,"[%d] Snapshot seconds",zeng_segundos_cada_snapshot);

                menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_zeng_snapshot_force_reconnect,NULL,"[%c] Force reconnect",
                (zeng_force_reconnect_failed_retries.v ? 'X' : ' ' ));
                menu_add_item_menu_tooltip(array_menu_common,"Force reconnect when sending snapshot fails 3 times");
                menu_add_item_menu_ayuda(array_menu_common,"Force reconnect when sending snapshot fails 3 times");
			}

			if (zeng_enabled.v) {
				menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_zeng_send_message,menu_zeng_send_message_cond,"Send message");
			}
                       
						
			menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

            menu_add_ESC_item(array_menu_common);

            retorno_menu=menu_dibuja_menu(&zeng_opcion_seleccionada,&item_seleccionado,array_menu_common,"ZENG" );

                
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




}

int menu_online_zx81_letra(char filtro,char letra)
{
	letra=letra_minuscula(letra);
	filtro=letra_minuscula(filtro);
	if (filtro>='a' && filtro<='z') {
		if (letra==filtro) return 1;
		else return 0;
	}
	else {
		//todo lo que no son letras
		if (letra<'a' || letra>'z') return 1;
		else return 0;
	}
}

char online_browse_zx81_ultima_letra='a';

char menu_online_browse_zx81_letter(void)
{

	menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();		

	zxvision_window ventana;
	
	int ancho_ventana=23;
	int alto_ventana=8;
	
	int xventana=menu_center_x()-ancho_ventana/2; 
	int yventana=menu_center_y()-alto_ventana/2; 
	
	char letra_seleccionada=0;

	zxvision_new_window(&ventana,xventana,yventana,ancho_ventana,alto_ventana,
							ancho_ventana-1,alto_ventana-2,"Initial letter");
	zxvision_draw_window(&ventana);		

       
    menu_item *array_menu_osd_adventure_keyboard;
    menu_item item_seleccionado;
    int retorno_menu;
    int salir=0;
    do {

		


        //Como no sabemos cual sera el item inicial, metemos este sin asignar
        menu_add_item_menu_inicial(&array_menu_osd_adventure_keyboard,"",MENU_OPCION_UNASSIGNED,NULL,NULL);

	//if (osd_adv_kbd_list[adventure_keyboard_selected_item][adventure_keyboard_index_selected_item]==0) {
	//osd_adv_kbd_defined
		//int i;
		int last_x=4;
		int last_y=0;
		char letra='a';
        int nletra=0;
		
		
		for (;letra<='z'+1;letra++) {
			char letra_mostrar=letra;
			if (letra=='z'+1) letra_mostrar='#';
		    menu_add_item_menu_format(array_menu_osd_adventure_keyboard,MENU_OPCION_NORMAL,menu_osd_adventure_keyboard_action,NULL,"%c",letra_mostrar);
            menu_add_item_menu_tabulado(array_menu_osd_adventure_keyboard,last_x,last_y);
            menu_add_item_menu_valor_opcion(array_menu_osd_adventure_keyboard,letra_mostrar);
				
            menu_add_item_menu_shortcut(array_menu_osd_adventure_keyboard,letra_mostrar);

			last_x +=3;
            nletra++;
			if (nletra==5) {
				last_x=4;
				last_y++; 
                nletra=0;
			}
		}



		//Nombre de ventana solo aparece en el caso de stdout
        retorno_menu=menu_dibuja_menu(&online_browse_zx81_letter_opcion_seleccionada,&item_seleccionado,array_menu_osd_adventure_keyboard,"Initial letter" );


	    //En caso de menus tabulados, es responsabilidad de este de borrar la ventana
        cls_menu_overlay();
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
				//printf ("Item seleccionado: %d\n",item_seleccionado.valor_opcion);
                                //printf ("actuamos por funcion\n");

	                        

                                letra_seleccionada=item_seleccionado.valor_opcion;
				//En caso de menus tabulados, es responsabilidad de este de borrar la ventana
				salir=1;
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus && !salir);



        cls_menu_overlay();
		

		//printf ("en final de funcion\n");
		zxvision_destroy_window(&ventana);

	return letra_seleccionada;


}

void menu_online_browse_zx81_create_menu(char *mem, char *mem_after_headers,int total_leidos,char letra,char *juego,char *url_juego)
{

	//Por defecto
	url_juego[0]=0;
	juego[0]=0;

	//Dado que es una variable local, siempre podemos usar este nombre array_menu_common
    menu_item *array_menu_common;
    menu_item item_seleccionado;
    int retorno_menu;

	menu_add_item_menu_inicial(&array_menu_common,"",MENU_OPCION_UNASSIGNED,NULL,NULL);

	//temp limite
	char texto_final[30000];

	int total_items=0;
		
			int indice_destino=0;
		
			int dif_header=mem_after_headers-mem;
			total_leidos -=dif_header;
			mem=mem_after_headers;
	
			//leer linea a linea 
			char buffer_linea[1024];
			int i=0;
			int salir=0;
			do {
				int leidos;
				char *next_mem;
		
				next_mem=util_read_line(mem,buffer_linea,total_leidos,1024,&leidos);
				total_leidos -=leidos;
		
				if (buffer_linea[0]==0) {
					salir=1;
					//printf ("salir con linea vacia final\n");
					mem=next_mem;
				}
				else {
					//printf ("cabecera %d: %s\n",i,buffer_linea);
					//ver si contine texto de juego
				
					char *existe;
					existe=strstr(buffer_linea,"/files/");
					if (existe!=NULL) {
						if (menu_online_zx81_letra(letra,existe[7])) {
						//if (existe[7]==letra) {
							//quitar desde comilla derecha
							char *comilla;
							comilla=strstr(&existe[7],"\"");
							if (comilla!=NULL) *comilla=0;
							debug_printf (VERBOSE_PARANOID,"Adding raw html line %s",buffer_linea);
							//Todo controlar maximo buffer y maximo que puede mostrar ventana
							sprintf(&texto_final[indice_destino],"%s\n",&existe[7]);
							indice_destino +=strlen(&existe[7])+1;

							menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,NULL,NULL,&existe[7]);
							debug_printf (VERBOSE_DEBUG,"Adding menu entry %s",&existe[7]);
							total_items++;
						}
					}
					i++;
					mem=next_mem;
				}

				if (total_leidos<=0) salir=1;
		
			} while (!salir);
	
			texto_final[indice_destino]=0;
			
	                      
						
			menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

            menu_add_ESC_item(array_menu_common);

			if (total_items) {
				//Si hay resultados con esa letra, normalmente si..
            	retorno_menu=menu_dibuja_menu(&zx81_online_browser_opcion_seleccionada,&item_seleccionado,array_menu_common,"ZX81 Games" );

                
            	if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                	//que juego se ha seleccionado

                	//item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                	//char *juego;
                	strcpy(juego,item_seleccionado.texto_opcion);
                	debug_printf (VERBOSE_INFO,"Selected game: %s",juego);
                
                	sprintf(url_juego,"/files/%s",juego);
				}
			}

			else {
				menu_error_message("No results found");
			}


}

void menu_online_browse_zx81(MENU_ITEM_PARAMETERS)
{


	do {
		//char oldletra=s_online_browse_zx81_letra[0];
	
		//menu_ventana_scanf("Letter",s_online_browse_zx81_letra,2);
	
		//char letra=s_online_browse_zx81_letra[0];
	
		char letra=menu_online_browse_zx81_letter();
		if (letra==0) return;
		
	    stats_total_zx81_browser_queries++;

		//printf ("old letra %c new letra %c\n",online_browse_zx81_ultima_letra,letra);
	
		//si cambia letra, poner cursor arriba
		if (letra!=online_browse_zx81_ultima_letra) zx81_online_browser_opcion_seleccionada=0;

		online_browse_zx81_ultima_letra=letra;
		

		int http_code;
		char *mem;
		char *orig_mem;
		char *mem_after_headers;
		int total_leidos;
		char redirect_url[NETWORK_MAX_URL];
		

		int retorno=menu_zsock_http("www.zx81.nl","/files.html",&http_code,&mem,&total_leidos,&mem_after_headers,1,"",0,redirect_url,"");
		orig_mem=mem;
	
		//printf("%s\n",mem);

		if (mem_after_headers!=NULL && http_code==200) {
				char url_juego[1024];
				char juego[MAX_TEXTO_OPCION];
			
				menu_online_browse_zx81_create_menu(mem, mem_after_headers,total_leidos,letra,juego,url_juego);

				if (url_juego[0]!=0) {

                	//cargar
                	char archivo_temp[PATH_MAX];
					//sprintf (archivo_temp,"/tmp/%s",juego);
					sprintf (archivo_temp,"%s/%s",get_tmpdir_base(),juego);
		
                	
					//usamos misma funcion thread que usa download wos y otros
					int ret=menu_download_file("www.zx81.nl",url_juego,archivo_temp,0,1024*1024,"");  //1 MB mas que suficiente

					if (ret==200) {
                                
  						//y cargar
  						strcpy(quickload_file,archivo_temp);
 
						quickfile=quickload_file;
        
						if (quickload(quickload_file)) {
							debug_printf (VERBOSE_ERR,"Unknown file format");
						}

						//Agregar a ultimos archivos usados
						last_filesused_insert(quickload_file);

						//Y salir todos menus
						salir_todos_menus=1;  
					}
			
  					
					else {		
						//debug_printf(VERBOSE_ERR,"Error downloading game. Return code: %d",ret);

						if (ret<0) {	
							//printf ("Error: %d %s\n",retorno,z_sock_get_error(retorno));
							menu_network_error(ret);
						}
						else {
							debug_printf(VERBOSE_ERR,"Error downloading. Return code: %d",ret);
						}

					}	
				}                      
                        
		}
		//Fin resultado http correcto
		else {	
			if (retorno<0) {	
				debug_printf (VERBOSE_DEBUG,"Error: %d %s",retorno,z_sock_get_error(retorno));
				menu_network_error(retorno);
			}
			else {
				debug_printf(VERBOSE_ERR,"Error downloading. Return code: %d",http_code);
			}
		}			
		

		if (orig_mem!=NULL) free(orig_mem);

	} while (!salir_todos_menus);
	//Se saldra al seleccionar juego o al pulsar ESC desde seleccion letra (ahi se sale con return tal cual)
	
}




struct menu_zsock_http_struct
{

	char *host;
	char *url;
	int *http_code;
	char **mem;
	int *t_leidos;
	char **mem_after_headers;
	int skip_headers;
	char *add_headers;
	int use_ssl;
	char *redirect_url;
    char *ssl_sni_host_name;


	int return_code;
    
};

int menu_zsock_http_thread_running=0;

int menu_menu_zsock_http_cond(zxvision_window *w GCC_UNUSED)
{
	return !menu_zsock_http_thread_running;
}



void *menu_menu_zsock_http_thread_function(void *entrada)
{

	//menu_zsock_http_thread_running=1; 

#ifndef NETWORKING_DISABLED

	debug_printf (VERBOSE_DEBUG,"Starting zsock http thread. Host=%s Url=%s",
								((struct menu_zsock_http_struct *)entrada)->host,
								((struct menu_zsock_http_struct *)entrada)->url);

//((struct menu_zsock_http_struct *)entrada)->return_code=-1;


	((struct menu_zsock_http_struct *)entrada)->return_code=
			zsock_http( 
								((struct menu_zsock_http_struct *)entrada)->host,
								((struct menu_zsock_http_struct *)entrada)->url,
								((struct menu_zsock_http_struct *)entrada)->http_code,
								((struct menu_zsock_http_struct *)entrada)->mem,
								((struct menu_zsock_http_struct *)entrada)->t_leidos,
								((struct menu_zsock_http_struct *)entrada)->mem_after_headers,
								((struct menu_zsock_http_struct *)entrada)->skip_headers,
								((struct menu_zsock_http_struct *)entrada)->add_headers,
								((struct menu_zsock_http_struct *)entrada)->use_ssl,
								((struct menu_zsock_http_struct *)entrada)->redirect_url,
								0,
                                ((struct menu_zsock_http_struct *)entrada)->ssl_sni_host_name
							); 



	debug_printf (VERBOSE_DEBUG,"Finishing zsock http thread");

#endif
	menu_zsock_http_thread_running=0;

	return 0;

}

#ifdef USE_PTHREADS
pthread_t menu_zsock_http_thread;
#endif

int menu_zsock_http(char *host, char *url,int *http_code,char **mem,int *t_leidos, char **mem_after_headers,
            int skip_headers,char *add_headers,int use_ssl,char *redirect_url,char *ssl_sni_host_name)
{
	
	 
	//Lanzar el thread de descarga
	struct menu_zsock_http_struct parametros;

	parametros.host=host;
	parametros.url=url;
	parametros.http_code=http_code;
	parametros.mem=mem;
	parametros.t_leidos=t_leidos;
	parametros.mem_after_headers=mem_after_headers;
	parametros.skip_headers=skip_headers;
	parametros.add_headers=add_headers;
	parametros.use_ssl=use_ssl;
	parametros.redirect_url=redirect_url;
    parametros.ssl_sni_host_name=ssl_sni_host_name;

	//de momento not found y error, y mem a null
	parametros.return_code=-1;
	*(parametros.http_code)=404;
	*(parametros.mem)=NULL;
	*(parametros.mem_after_headers)=NULL;
	*(parametros.t_leidos)=0;
	parametros.redirect_url[0]=0;	


#ifndef NETWORKING_DISABLED

	//Inicializar thread
	debug_printf (VERBOSE_DEBUG,"Initializing thread menu_menu_zsock_http_thread_function");
	

	//Antes de lanzarlo, decir que se ejecuta, por si el usuario le da enter rapido a la ventana de progreso y el thread aun no se ha lanzado
	menu_zsock_http_thread_running=1;
	
	if (pthread_create( &menu_zsock_http_thread, NULL, &menu_menu_zsock_http_thread_function, (void *)&parametros) ) {
		debug_printf(VERBOSE_ERR,"Can not create zsock http thread");
		return -1;
	}

#endif

		 
	contador_menu_zeng_connect_print=0;

	//Usamos misma ventana de progreso que zeng. TODO: si se lanzan los dos a la vez (cosa poco probable) se moverian uno con el otro
    strcpy(menu_zeng_connect_print_host,host);
	zxvision_simple_progress_window("Downloading", menu_menu_zsock_http_cond,menu_zeng_connect_print );

	//TODO Si antes de finalizar la descarga se vuelve atras y se vuelve a realizar otra busqueda, puede dar problemas
	//ya que la variable menu_zsock_http_thread_running es global y única
	
	if (menu_zsock_http_thread_running) menu_warn_message("Download has not ended yet");

	//despues de mostrar el aviso, si la tarea sigue en ejecucion, retornamos error 404
	if (menu_zsock_http_thread_running) return 404;	

	return parametros.return_code;

}


struct download_wos_struct
{
	char *host;
	char *url;
	char *archivo_temp;
	int ssl_use;
	int return_code;
	int estimated_maximum_size;
    char *ssl_sni_host_name;
};

int download_wos_thread_running=0;

int menu_download_file_cond(zxvision_window *w GCC_UNUSED)
{
	return !download_wos_thread_running;
}



void *menu_download_file_thread_function(void *entrada)
{

	//download_wos_thread_running=1; 

#ifndef NETWORKING_DISABLED

	debug_printf (VERBOSE_DEBUG,"Starting download content thread. Host=%s Url=%s",
	((struct download_wos_struct *)entrada)->host,
								((struct download_wos_struct *)entrada)->url);

	((struct download_wos_struct *)entrada)->return_code=util_download_file( ((struct download_wos_struct *)entrada)->host,
								((struct download_wos_struct *)entrada)->url,
								((struct download_wos_struct *)entrada)->archivo_temp,
								((struct download_wos_struct *)entrada)->ssl_use,
								((struct download_wos_struct *)entrada)->estimated_maximum_size,
                                ((struct download_wos_struct *)entrada)->ssl_sni_host_name);

	debug_printf (VERBOSE_DEBUG,"Finishing download content thread");

#endif
	download_wos_thread_running=0;

	return 0;

}

#ifdef USE_PTHREADS
pthread_t download_wos_thread;
#endif





//antes llamado menu_download_wos
int menu_download_file(char *host,char *url,char *archivo_temp,int ssl_use,int estimated_maximum_size,char *ssl_sni_host_name)
{
	
	
	//Lanzar el thread de descarga
	struct download_wos_struct parametros;

	parametros.host=host;
	parametros.url=url;
	parametros.archivo_temp=archivo_temp;
	parametros.ssl_use=ssl_use;
	parametros.estimated_maximum_size=estimated_maximum_size;
    parametros.ssl_sni_host_name=ssl_sni_host_name;

	//de momento not found
	parametros.return_code=404;


#ifndef NETWORKING_DISABLED

	//Inicializar thread

	//Antes de lanzarlo, decir que se ejecuta, por si el usuario le da enter rapido a la ventana de progreso y el thread aun no se ha lanzado
	download_wos_thread_running=1;	
	
	if (pthread_create( &download_wos_thread, NULL, &menu_download_file_thread_function, (void *)&parametros) ) {
		debug_printf(VERBOSE_ERR,"Can not create download wos thread");
		return -1;
	}

#endif

		 
	contador_menu_zeng_connect_print=0;

	//Usamos misma ventana de progreso que zeng. TODO: si se lanzan los dos a la vez (cosa poco probable) se moverian uno con el otro
    strcpy(menu_download_file_connect_print_host,host);
	zxvision_simple_progress_window("Downloading software", menu_download_file_cond,menu_download_file_connect_print );

	//TODO Si antes de finalizar la descarga se vuelve atras y se vuelve a realizar otra busqueda, puede dar problemas
	//ya que la variable download_wos_thread_running es global y única
	
	if (download_wos_thread_running) menu_warn_message("Download has not ended yet");

	//despues de mostrar el aviso, si la tarea sigue en ejecucion, retornamos error 404
	if (download_wos_thread_running) return 404;

	return parametros.return_code;

}
/*
Obtiene nombre de juego de manera inteligente, segun su nombre de archivo
Se trata de quitar extension conocida
Ejemplo: ChaseH.Q..tzx.zip
Debe obtener: ChaseH.Q.
*/
void menu_online_browse_intelli_get_name(char *nombre_origen,char *nombre_final)
{
    //util_get_file_without_extension(nombre_sin_dir,nombre_sin_ext);
    //Si nombre acaba en cualquiera de:
    //tap.zip
    //dsk.zip
    //tzx.zip
    //Quitar esa doble extension
    //Cualquier otra, dejar tal cual
    char *posibles_extensiones[]={
        ".tap.zip",
        ".dsk.zip",
        ".tzx.zip",
        ".z80.zip",
        ".sna.zip",
        ".rom.zip",
        ".trd.zip",
        
        //hay otras extensiones pero como no las soporta smartload, mejor mostrar extension
        //.mgt.zip
        //.slt.zip
        //.mdr.zip

        //Indica final de array
        ""
    };

    int i;
    char *encontrado=NULL;


    for (i=0;posibles_extensiones[i][0] && encontrado==NULL;i++) {
        encontrado=strstr(nombre_origen,posibles_extensiones[i]);
    }

    //de momento copiar tal cual
    strcpy(nombre_final,nombre_origen);

    if (encontrado!=NULL) {
        //longitud hasta encontrada coincidencia. Restamos los dos punteros
        int longitud_nombre_sin_extension=encontrado-nombre_origen;
        //Acortar el texto
        nombre_final[longitud_nombre_sin_extension]=0;
    }

    
}


//showindex dice si muestra contenido texto variable index en el item->usado para mostrar el archivo de la url 
//en las diferentes descargas de un mismo juego
void menu_online_browse_zxinfowos_query(char *query_result,char *hostname,char *query_url,char *preffix,
    char *string_index,char *string_display,
     char *add_headers,int showindex,char *windowtitle,char *error_not_found_message)
{
	
	//Por defecto
	query_result[0]=0;
	
	//Dado que es una variable local, siempre podemos usar este nombre array_menu_common
	menu_item *array_menu_common;
	menu_item item_seleccionado;
	int retorno_menu;

	int zxinfo_wos_opcion_seleccionada=0;
	do {

		menu_add_item_menu_inicial(&array_menu_common,"",MENU_OPCION_UNASSIGNED,NULL,NULL);

		
		int http_code;
		char *mem;
		char *orig_mem;
		char *mem_after_headers;
		int total_leidos;

		
		char redirect_url[NETWORK_MAX_URL];
		
		
		int retorno=menu_zsock_http(hostname,query_url,&http_code,&mem,&total_leidos,&mem_after_headers,1,add_headers,0,redirect_url,"");



		orig_mem=mem;
	
		if (mem_after_headers!=NULL && http_code==200) {
			
			int dif_header=mem_after_headers-mem;
			total_leidos -=dif_header;
			mem=mem_after_headers;
		
			//leer linea a linea 
			char buffer_linea[1024];
			int i=0;
			int salir=0;

			int existe_id;
			int existe_fulltitle;
			int ultimo_indice_id;
			int ultimo_indice_fulltitle;

			char ultimo_id[1024];
			char ultimo_fulltitle[1024];

			existe_id=0;
			existe_fulltitle=0;
			ultimo_id[0]=0;
			ultimo_fulltitle[0]=0;
			ultimo_indice_id=0;
			ultimo_indice_fulltitle=0;	

			int total_items=0;

			//Leer linea a linea la respuesta http, y meterlo en items de menu
			do {
				int leidos;
				char *next_mem;
			
				next_mem=util_read_line(mem,buffer_linea,total_leidos,1024,&leidos);
				total_leidos -=leidos;
			
				if (buffer_linea[0]==0) {
					salir=1;
					//printf ("salir con linea vacia final\n");
					mem=next_mem;
				}
				else {
					//printf ("cabecera %d: %s\n",i,buffer_linea);
					//ver si contine texto de juego

					/*
					Campos a buscar:

	hits.0._id=0002258
	hits.0.title=Headcoach

	Pueden salir antes id o antes title. En bucle leer los dos y cuando estén los dos y tengan mismo .n., agregar a menu
					*/
					
					//filtrar antes los que tienen prefijo
					char *existe_prefijo;
					
					existe_prefijo=strstr(buffer_linea,preffix);
					if (existe_prefijo!=NULL) {
					
						char *existe;
						existe=strstr(buffer_linea,string_index); //"_id=");
						if (existe!=NULL) {
								int pos=strlen(string_index);
                                //printf("id: existe_id %d existe_fulltitle %d buffer_linea: %s\n",existe_id,existe_fulltitle,buffer_linea);
								strcpy(ultimo_id,&existe[pos]);
								existe_id=1;
								char *existe_indice;
								existe_indice=strstr(buffer_linea,preffix);
								if (existe_indice!=NULL) {
									//saltar el prefijo para obtener el numero
									int l=strlen(preffix);
									ultimo_indice_id=parse_string_to_number(&existe_indice[l]);
								}
						}

						existe=strstr(buffer_linea,string_display); //"fulltitle=");
						if (existe!=NULL) {
                                //hay que descartar entradas tipo hits.0.screens.1.title=null
                                //que hacen confundir y pensar que son entradas de title
                                //TODO: esta exclusion realmente solo haria falta en la primera llamada aqui, 
                                //en la busqueda de juegos. En cambio en la de game details no hace falta,
                                //pero bueno tampoco molesta y por no complicar mas el código, lo dejamos
                                char *existe_screen=strstr(buffer_linea,".screens.");
                                if (existe_screen==NULL) {

								int pos=strlen(string_display);
                                //printf("ti: existe_id %d existe_fulltitle %d buffer_linea: %s\n",existe_id,existe_fulltitle,buffer_linea);
								strcpy(ultimo_fulltitle,&existe[pos]);
								existe_fulltitle=1;
								char *existe_indice;
								existe_indice=strstr(buffer_linea,preffix);
								if (existe_indice!=NULL) {
									//saltar el prefijo para obtener el numero
									int l=strlen(preffix);
									ultimo_indice_fulltitle=parse_string_to_number(&existe_indice[l]);
								}						

                                }
						}				
							
						if (existe_id && existe_fulltitle) {
                            //printf("ultimo_indice_id %d ultimo_indice_fulltitle %d\n",ultimo_indice_id,ultimo_indice_fulltitle);
							if (ultimo_indice_id==ultimo_indice_fulltitle) {
								
								//printf ("Adding menu item [%s] id [%s]\n",ultimo_fulltitle,ultimo_id);
								debug_printf (VERBOSE_DEBUG,"Adding menu item [%s] id [%s]",ultimo_fulltitle,ultimo_id);
								
								//meter en entrada linea indice. Realmente para que la queremos?
								//solo la muestro en la busqueda inicial, en la seleccion del formato de archivo ya no
								if (!showindex) {
									//Remodificamos ultimo_fulltitle para meterle el indice delante
									char buf[1024];
									sprintf (buf,"%d %s",ultimo_indice_id,ultimo_fulltitle);
									strcpy(ultimo_fulltitle,buf);
								}
								
								
								//controlar maximo 30 caracteres
								//TODO: si hacemos que se guarde geometria de ventana, teniendo ancho mayor que 32, esta maximo podria ser el ancho 
								//maximo que permite un item de menu (MAX_TEXTO_OPCION)
								ultimo_fulltitle[30]=0;
								
								
								//TODO controlar maximo items en menu. De momento esta limitado por la query a la api (100)
								//Porque? realmente no hay un limite como tal en items de menu, no?

								if (!showindex) {
									menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,NULL,NULL,ultimo_fulltitle);
									menu_add_item_menu_misc(array_menu_common,ultimo_id);
								}
								else {
									//printf ("%s\n",ultimo_id);
									//obtener archivo sin extension de la descarga
									char nombre_sin_dir[PATH_MAX];
									char nombre_sin_ext[PATH_MAX];

									util_get_file_no_directory(ultimo_id,nombre_sin_dir);

									//Pillamos el nombre sin extension 
                                    menu_online_browse_intelli_get_name(nombre_sin_dir,nombre_sin_ext);

									//Acortar el nombre por si acaso
									char nombre_shown[28];

									//strcpy(nombre_sin_ext,"01234567890123456789012345678901234567890123456789");

									menu_tape_settings_trunc_name(nombre_sin_ext,nombre_shown,28);
									//printf ("%s\n",nombre_sin_ext);

									menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,NULL,NULL,nombre_shown);
									menu_add_item_menu_misc(array_menu_common,ultimo_id);

									menu_add_item_menu_format(array_menu_common,MENU_OPCION_SEPARADOR,NULL,NULL," %s",ultimo_fulltitle);							
								}

								total_items++;
							}

							existe_id=0;
							existe_fulltitle=0;
							ultimo_id[0]=0;
							ultimo_fulltitle[0]=0;
							ultimo_indice_id=0;
							ultimo_indice_fulltitle=0;	

						}
					}
												
					i++;
					mem=next_mem;
				}
			
				if (total_leidos<=0) salir=1;
			
			} while (!salir);
		
			//texto_final[indice_destino]=0;
			if (orig_mem!=NULL) free(orig_mem);
				
						
							
			menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

			menu_add_ESC_item(array_menu_common);

			if (total_items) {

				retorno_menu=menu_dibuja_menu(&zxinfo_wos_opcion_seleccionada,&item_seleccionado,array_menu_common,windowtitle );

				
				if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {

					//printf ("actuamos por funcion\n");
					//item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
					char *juego;
					juego=item_seleccionado.texto_opcion;

					char *url;
					url=item_seleccionado.texto_misc;
					debug_printf (VERBOSE_INFO,"Game [%s] url/id [%s]",juego,url);

					strcpy(query_result,url);
					return;
										
				}
			}

			else {
				//menu_error_message("No results found");
				menu_error_message(error_not_found_message);
				return;
			}
		}  //Aqui cierra mem_after_headers!=NULL && http_code==200

			//Fin resultado http correcto
		else {	
			if (retorno<0) {	
				//printf ("Error: %d %s\n",retorno,z_sock_get_error(retorno));
				menu_network_error(retorno);
				return;
			}
			else {
				debug_printf(VERBOSE_ERR,"Error downloading. Return code: %d",http_code);
				return;
			}
		}	
	

    } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);

	

}

void menu_zxinfo_get_final_url(char *url_orig,char *host_final,char *url_final,int *ssl_use)
{
	    /*  Local file links starting with /zxdb/sinclair/ refer to content added afterwards. 
		These files are currently stored at https://spectrumcomputing.co.uk/zxdb/sinclair/  */

		/*
		Local file links starting with /pub/sinclair/ refer to content previously available at the original WorldOfSpectrum archive. 
		These files are currently accessible from Archive.org mirror at 
		https://archive.org/download/World_of_Spectrum_June_2017_Mirror/World%20of%20Spectrum%20June%202017%20Mirror.zip/World%20of%20Spectrum%20June%202017%20Mirror/sinclair/
		Local file links starting with /zxdb/sinclair/ refer to content added afterwards. 
		These files are currently stored at https://spectrumcomputing.co.uk/zxdb/sinclair/


		https://github.com/zxdb/ZXDB/blob/master/README.md
		*/

		
#ifdef COMPILE_SSL
		*ssl_use=1;
		char *pref_wos="/pub/sinclair/";
		//char *pref_zxdb="/zxdb/sinclair/";

		if (strstr(url_orig,pref_wos)!=NULL) {
			debug_printf (VERBOSE_DEBUG,"WOS preffix");

			//Quitar /pub/sinclair
			char url_modif[NETWORK_MAX_URL];
			strcpy(url_modif,url_orig);

			int longitud_pref=strlen(pref_wos);
			//int longitud_url=strlen(url_orig);

			//longitud_url -=longitud_pref;
			//url_modif[longitud_url]=0;

			char *puntero_url;
			puntero_url=&url_modif[longitud_pref];

			//printf ("url modificada primero: %s\n",puntero_url);

			strcpy(host_final,"archive.org");
			sprintf(url_final,"/download/World_of_Spectrum_June_2017_Mirror/World%%20of%%20Spectrum%%20June%%202017%%20Mirror.zip/World%%20of%%20Spectrum%%20June%%202017%%20Mirror/sinclair/%s",puntero_url);
			debug_printf (VERBOSE_DEBUG,"Final URL: %s",url_final);

		}

		else {
			debug_printf (VERBOSE_DEBUG,"Spectrumcomputing preffix");
			//Asumimos que es zxdb
			strcpy(host_final,"spectrumcomputing.co.uk");
			strcpy(url_final,url_orig);
		}
#else
		//Si no tenemos ssl, solo podemos descargar contenido de wos tal cual
		debug_printf (VERBOSE_DEBUG,"Trying to download from WOS using HTTP as we don't have SSL support compiled in");
		*ssl_use=0;
		strcpy(host_final,"www.worldofspectrum.org");
		strcpy(url_final,url_orig);
#endif
		
		
	
}

char zxinfowos_query_search[256]="";

void menu_online_browse_zxinfowos(MENU_ITEM_PARAMETERS)
{

#ifndef COMPILE_SSL
	menu_first_aid("no_ssl_wos");	
#endif
	
    menu_first_aid("search_zxinfo");

	menu_ventana_scanf("Query",zxinfowos_query_search,256);
	if (zxinfowos_query_search[0]==0) return;
	
    stats_total_speccy_browser_queries++;
	
	
	
	//TODO podria pasar que al normalizar ocupe mas de 1024, pero la cadena de entrada tendria que ser muy grande
	char query_search_normalized[1024];
	
	util_normalize_query_http(zxinfowos_query_search,query_search_normalized);
	

	//http://a.zxinfo.dk/api/zxinfo/v2/search?query=head%20over%20heels&mode=compact&sort=rel_desc&size=10&offset=0

	do {
		char query_url[1024];

        //Old V2
		//sprintf (query_url,"/api/zxinfo/v2/search?query=%s&mode=compact&sort=rel_desc&size=100&offset=0&contenttype=SOFTWARE",query_search_normalized);

        //New V3
        sprintf (query_url,"/v3/search?query=%s&mode=compact&sort=rel_desc&size=100&offset=0&contenttype=SOFTWARE&output=flat",query_search_normalized);
        

		char query_id[256];

        //Old V2
		//menu_online_browse_zxinfowos_query(query_id,"a.zxinfo.dk",query_url,"hits.","_id=","fulltitle=","",0,"Spectrum games","No results found");
        //New V3 http://v3.zxinfo.dk
        menu_online_browse_zxinfowos_query(query_id,"v3.zxinfo.dk",query_url,"hits.","_id=","title=","",0,"Spectrum games","No results found");
        
		//gestionar resultado vacio
		if (query_id[0]==0) {
			//TODO resultado con ESC
			return;
		}

		debug_printf (VERBOSE_DEBUG,"Entry id result: %s",query_id);
		
		
		//http://a.zxinfo.dk/api/zxinfo/games/0002259?mode=compact
		
		/*
		releases.1.as_title=Foot and Mouth
	releases.1.releaseprice=£7.95
	releases.1.url=/pub/sinclair/games/h/HeadOverHeels.tap.zip
	releases.1.type=Tape image
		*/
		
        //Old V2
		//sprintf (query_url,"/api/zxinfo/games/%s?mode=compact",query_id);

        //New V3
		sprintf (query_url,"/v3/games/%s?mode=compact&output=flat",query_id);


        //New v3 http://v3.zxinfo.dk/v3/games/0000438?mode=compact&output=flat

		//Old V2
		//menu_online_browse_zxinfowos_query(query_id,"a.zxinfo.dk",query_url,"releases.","url=","format=","",1,"Releases",
		//									"No results found. Maybe there are no releases available or the game is copyright protected");

		//New V3
		menu_online_browse_zxinfowos_query(query_id,"v3.zxinfo.dk",query_url,"releases.","path=","format=","",1,"Releases",
											"No results found. Maybe there are no releases available or the game is copyright protected");


		//gestionar resultado vacio
		if (query_id[0]==0) {
			//TODO resultado con ESC
			return;
		}	
		
		//gestionar resultado no vacio
		if (query_id[0]!=0) {
			// resultado no ESC
			

			debug_printf (VERBOSE_DEBUG,"Entry url result: %s",query_id);
		
			char url_juego[1024];
			sprintf(url_juego,"%s",query_id);
			//cargar
			char archivo_temp[PATH_MAX];
									
									
			/* Local file links starting with /zxdb/sinclair/ refer to content added afterwards. 
			These files are currently stored at https://spectrumcomputing.co.uk/zxdb/sinclair/  */

			/*
			Local file links starting with /pub/sinclair/ refer to content previously available at the original WorldOfSpectrum archive. 
			These files are currently accessible from Archive.org mirror at 
			https://archive.org/download/World_of_Spectrum_June_2017_Mirror/World%20of%20Spectrum%20June%202017%20Mirror.zip/World%20of%20Spectrum%20June%202017%20Mirror/sinclair/
			Local file links starting with /zxdb/sinclair/ refer to content added afterwards. 
			These files are currently stored at https://spectrumcomputing.co.uk/zxdb/sinclair/


			https://github.com/zxdb/ZXDB/blob/master/README.md
			*/
			
			
			char juego[PATH_MAX];
			util_get_file_no_directory(query_id,juego);
			util_normalize_name(juego);
			
			char tempdir[PATH_MAX];
			sprintf (tempdir,"%s/download",get_tmpdir_base() );
			menu_filesel_mkdir(tempdir);
			sprintf (archivo_temp,"%s/%s",tempdir,juego);
			

			char url_juego_final[PATH_MAX];
			char host_final[PATH_MAX];

			int ssl_use;

			menu_zxinfo_get_final_url(url_juego,host_final,url_juego_final,&ssl_use);

			debug_printf (VERBOSE_DEBUG,"Downloading file from host %s (SSL=%d) url %s",host_final,ssl_use,url_juego_final);

            char ssl_sni_host_name[NETWORK_MAX_URL]="";
            int descargando_spectrumcomputing=0;

                if (!strcmp(host_final,"spectrumcomputing.co.uk")) {
                    descargando_spectrumcomputing=1;
                    //Descargas desde spectrum computing requieren SNI cuando hay activado su proteccion de cloudflare
                    strcpy(ssl_sni_host_name,"spectrumcomputing.co.uk");
                }            

			int ret=menu_download_file(host_final,url_juego_final,archivo_temp,ssl_use,1024*1024,ssl_sni_host_name);  //1 MB mas que suficiente

			if (ret==200) {      
                //Si descarga de spectrumcomputing
                if (descargando_spectrumcomputing) {
                    menu_first_aid("download_spectrumcomputing");
                }

				//y abrimos menu de smartload
				strcpy(quickload_file,archivo_temp);
	
				quickfile=quickload_file;
				menu_smartload(0);
		
				return;
			}
			else {
				if (ret<0) {	
					menu_network_error(ret);
				}
				else {
					debug_printf(VERBOSE_ERR,"Error downloading. Return code: %d",ret);
				}

			}
		} 
	} while (1);
}


char menu_network_http_request_url[NETWORK_MAX_URL]="";

void menu_network_http_request(MENU_ITEM_PARAMETERS)
{
	int http_code;
	char *mem;
	char *mem_after_headers;
	char host[100];
	//char url[100];
	char s_skip_headers[2];
	char s_add_headers[200];

	host[0]=0;
	//url[0]=0;

	strcpy(s_skip_headers,"0");
	//s_skip_headers[0]='0';
	s_add_headers[0]=0;
	
	menu_ventana_scanf("host?",host,100);
	menu_ventana_scanf("url?",menu_network_http_request_url,NETWORK_MAX_URL);
	menu_ventana_scanf("add headers",s_add_headers,200);
	
	int l=strlen(s_add_headers);
	if (l>0) {
		s_add_headers[l++]='\r';
		s_add_headers[l++]='\n';
		s_add_headers[l++]=0;

	}
	
	menu_ventana_scanf("skip ret headers?(0/1)",s_skip_headers,2);
	int skip_headers=parse_string_to_number(s_skip_headers);
	int total_leidos;
	char redirect_url[NETWORK_MAX_URL];

	int use_ssl=0;
    char ssl_sni_host_name[NETWORK_MAX_URL]="";

#ifdef COMPILE_SSL
	char s_use_ssl[2];
	strcpy(s_use_ssl,"0");
	menu_ventana_scanf("use ssl? (0/1)",s_use_ssl,2);
	use_ssl=parse_string_to_number(s_use_ssl);

    if (use_ssl) {
        menu_ventana_scanf("ssl sni host name?",ssl_sni_host_name,NETWORK_MAX_URL);
    }
#endif

	

	char *mem_mensaje;

	int retorno=menu_zsock_http(host,menu_network_http_request_url,&http_code,&mem,&total_leidos,&mem_after_headers,skip_headers,s_add_headers,use_ssl,redirect_url,ssl_sni_host_name);
	if (retorno==0 && mem!=NULL) {
		if (skip_headers) {
			if (mem_after_headers) {
				menu_generic_message_format("Http code","%d",http_code);
				mem_mensaje=mem_after_headers;
				//menu_generic_message("Response",mem_after_headers);
			}
		}
		else {
			mem_mensaje=mem;
			//menu_generic_message("Response",mem);
		}
	}

	if (retorno>=0) {

		//Controlar maximo mensaje

		int longitud_mensaje=strlen(mem_mensaje);

		int max_longitud=MAX_TEXTO_GENERIC_MESSAGE-1024;
		//Asumimos el maximo restando 1024, de los posibles altos de linea

		if (longitud_mensaje>max_longitud) {
			//TODO: realmente habria que trocear aqui el mensaje en lineas y ver si el resultado excede el maximo de lineas o el maximo de bytes
			debug_printf (VERBOSE_ERR,"Response too long. Showing only the first %d bytes",max_longitud);
			mem_mensaje[max_longitud]=0;
		}

		menu_generic_message("Response",mem_mensaje);

	}

	else {
		menu_network_error(retorno);
	}



	if (mem!=NULL) free (mem);
}


void menu_online_download_extras(MENU_ITEM_PARAMETERS)
{


	//printf("URL: %s\n",ZESARUX_EXTRAS_URL);



	char host_final[NETWORK_MAX_URL];
	strcpy(host_final,ZESARUX_EXTRAS_HOST);


	char url[NETWORK_MAX_URL];

	strcpy(url,ZESARUX_EXTRAS_URL);


	//200 MB. En versión 9.0 son 100 MB. Mas que suficiente para el futuro
	int estimated_size=200*1024*1024;



	debug_printf(VERBOSE_DEBUG,"Selected url %s",url);

	char archivo_zip[PATH_MAX];

	//Ruta destino en el home
	char dest_dir[PATH_MAX];



//Aunque en Windows no le acaba de gustar, por alguna razón, la ruta al unzip. En Windows lo metemos en la ruta actual
#ifdef MINGW
	dest_dir[0]=0; //Cadena vacia -> carpeta actual
#else
	util_get_home_dir(dest_dir);
#endif

	


	char zipfilename[PATH_MAX];
	util_get_file_no_directory(url,zipfilename);

	sprintf(archivo_zip,"%s%s",dest_dir,zipfilename);

	int ssl_use=1;


	int ret=menu_download_file(host_final,url,archivo_zip,ssl_use,estimated_size,"");  

	if (ret==200) {       
		//descomprimimos zip
		char final_mmc_dir[PATH_MAX];
		sprintf(final_mmc_dir,"%s.dir",archivo_zip);

		//Descomprimir con ventana de progreso y pthread aparte de descompresion
		menu_uncompress_zip_progress(archivo_zip,final_mmc_dir);

		if (dest_dir[0]==0) menu_generic_message_format("File downloaded","File has been downloaded and uncompressed to current folder");

		else menu_generic_message_format("File downloaded","File has been downloaded and uncompressed to %s",dest_dir);

		//y abrimos menu de smartload
		strcpy(quickload_file,final_mmc_dir);

		quickfile=quickload_file;
		menu_smartload(0);		


		return;
	}
	else {
		if (ret<0) {	
			menu_network_error(ret);
		}
		else {
			debug_printf(VERBOSE_ERR,"Error downloading software. Return code: %d",ret);
		}

	}


}


void menu_network(MENU_ITEM_PARAMETERS)
{
        //Dado que es una variable local, siempre podemos usar este nombre array_menu_common
        menu_item *array_menu_common;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

                
            menu_add_item_menu_inicial_format(&array_menu_common,MENU_OPCION_NORMAL,menu_uartbridge,menu_network_uartbridge_cond,"~~UART Bridge emulation");
            menu_add_item_menu_spanish_catalan(array_menu_common,"Emulacion Puente ~~UART","Emulacio Pont ~~UART");
			menu_add_item_menu_shortcut(array_menu_common,'u');
                        
			menu_add_item_menu_tooltip(array_menu_common,"Bridge from emulated machine uart ports to a local serial uart device");
			menu_add_item_menu_ayuda(array_menu_common,"Bridge from emulated machine uart ports to a local serial uart device\n"
				"It does NOT emulate a full uart device, just links from the emulated machine ports to a physical local device\n"
				"Available for ZX-Uno, TBBlue and ZX Evolution TSConf");
            menu_add_item_menu_tiene_submenu(array_menu_common);
			

#ifndef NETWORKING_DISABLED
			menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_zeng,NULL,"Z~~ENG");
			menu_add_item_menu_shortcut(array_menu_common,'e');
			menu_add_item_menu_tooltip(array_menu_common,"Setup ZEsarUX Network Gaming");
			menu_add_item_menu_ayuda(array_menu_common,"ZEsarUX Network Gaming protocol (ZENG) allows you to play to any emulated game, using two ZEsarUX instances, "
			  "located each one on any part of the world or in a local network.\n"
			  "Games doesn't have to be modified, you can use any existing game. "
			  "ZENG works by sending special commands through the ZRCP protocol, so in order to use ZENG you must enable ZRCP protocol on menu settings-debug. "
			  "This protocol listens on tcp port 10000 so you should open your firewall/router to use it. "
			  "One ZEsarUX instance will be the master node and the other instance will be the slave node.\n"
			  "Please do NOT set both nodes as master\n"
			  "When you enable ZENG on both nodes:\n"
			  "-all key/joystick presses will be sent between the two nodes\n"
			  "-every two seconds a snapshot will be sent from the master to the slave node\n\n"
			  "Note about using joystick: real joystick (and cursors on keyboard) are sent to the other node as "
			  "the direction/button (left,right,up,down or fire) but not the type of joystick emulated (kempston, fuller, etc). "
			  "So you must configure same joystick emulation on both nodes. Also, real joystick to keys events are not sent by ZENG, just the joystick event"
			);
            menu_add_item_menu_tiene_submenu(array_menu_common);

                     
             
            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_online_browse_zx81,NULL,"~~ZX81 online browser");
            menu_add_item_menu_spanish(array_menu_common,"Navegador online ~~ZX81");
			menu_add_item_menu_shortcut(array_menu_common,'z'); 
            menu_add_item_menu_tooltip(array_menu_common,"Connects to the www.zx81.nl site to download ZX81 games. Many thanks to ZXwebmaster for allowing it"); 
            menu_add_item_menu_ayuda(array_menu_common,"Connects to the www.zx81.nl site to download ZX81 games. Many thanks to ZXwebmaster for allowing it"); 


//online browser ya solo es accesible con ssl

#ifdef COMPILE_SSL
			menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_online_browse_zxinfowos,NULL,"~~Speccy online browser");
            menu_add_item_menu_spanish(array_menu_common,"Navegador online ~~Speccy");
			menu_add_item_menu_shortcut(array_menu_common,'s');  


			//Versión con SSL usa zxinfo, spectrum computing y mirror archive.org
			menu_add_item_menu_tooltip(array_menu_common,"It uses zxinfo, spectrum computing and archive.org to download the software. Thanks to Thomas Heckmann and Peter Jones for allowing it");
			menu_add_item_menu_ayuda(array_menu_common,  "It uses zxinfo, spectrum computing and archive.org to download the software. Thanks to Thomas Heckmann and Peter Jones for allowing it");
			
			
//#else
			//Versión sin SSL usa zxinfo, servidor WOS
			//menu_add_item_menu_tooltip(array_menu_common,"It uses zxinfo and WOS to download the software. Thanks to Thomas Heckmann and Lee Fogarty for allowing it");
			//menu_add_item_menu_ayuda(array_menu_common,  "It uses zxinfo and WOS to download the software. Thanks to Thomas Heckmann and Lee Fogarty for allowing it");



			menu_add_item_menu_en_es_ca(array_menu_common,MENU_OPCION_NORMAL,menu_online_download_extras,NULL,
                "Download ZEsarUX e~~xtras","Descargar e~~xtras ZEsarUX","Descarregar e~~xtres ZEsarUX");
			menu_add_item_menu_shortcut(array_menu_common,'x');   
			menu_add_item_menu_tooltip(array_menu_common,"Download ZEsarUX extras package");
			menu_add_item_menu_ayuda(array_menu_common,"ZEsarUX extras package contains lots of documentation, sample games, demos, etc");
			
#endif    


			menu_add_item_menu_en_es_ca(array_menu_common,MENU_OPCION_NORMAL,menu_network_http_request,NULL,
                "Test Http request","Test peticion Http","Test peticio Http");

//Fin de condicion si hay pthreads
#endif

						
			menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

            menu_add_ESC_item(array_menu_common);

            retorno_menu=menu_dibuja_menu(&network_opcion_seleccionada,&item_seleccionado,array_menu_common,"Network" );

                
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




}

void menu_settings_enable_statistics(MENU_ITEM_PARAMETERS)
{
	if (stats_enabled.v) stats_disable();
	else stats_enable();
}

void menu_settings_enable_check_updates(MENU_ITEM_PARAMETERS)
{
	stats_check_updates_enabled.v ^=1;	
}

void menu_settings_enable_check_yesterday_users(MENU_ITEM_PARAMETERS)
{
	stats_check_yesterday_users_enabled.v ^=1;
}

void menu_settings_statistics(MENU_ITEM_PARAMETERS)
{
        //Dado que es una variable local, siempre podemos usar este nombre array_menu_common
        menu_item *array_menu_common;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

			menu_add_item_menu_inicial_format(&array_menu_common,MENU_OPCION_NORMAL,menu_settings_enable_check_updates,NULL,"[%c] Check updates",
					(stats_check_updates_enabled.v ? 'X' : ' ') );


			menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_settings_enable_check_yesterday_users,NULL,"[%c] Check yesterday users",
					(stats_check_yesterday_users_enabled.v ? 'X' : ' ') );  

			menu_add_item_menu_tooltip(array_menu_common,"Retrieve ZEsarUX yesterday users");
			menu_add_item_menu_ayuda(array_menu_common,"Retrieve ZEsarUX yesterday users");


                
            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_settings_enable_statistics,NULL,"[%c] Send Statistics",
					(stats_enabled.v ? 'X' : ' ') );
			
                        
			menu_add_item_menu_tooltip(array_menu_common,"Send anonymous statistics to a remote server, every time ZEsarUX starts");
			menu_add_item_menu_ayuda(array_menu_common,"Send anonymous statistics to a remote server, every time ZEsarUX starts");

			if (stats_enabled.v) {
				menu_add_item_menu_format(array_menu_common,MENU_OPCION_SEPARADOR,NULL,NULL,"The following data is sent:");
				//menu_add_item_menu_tooltip(array_menu_common,"This data is sent every time ZEsarUX starts");
				//menu_add_item_menu_ayuda(array_menu_common,"This data is sent every time ZEsarUX starts");
	
	menu_add_item_menu_format(array_menu_common,MENU_OPCION_SEPARADOR,NULL,NULL,"    Public IP address");
				
				menu_add_item_menu_format(array_menu_common,MENU_OPCION_SEPARADOR,NULL,NULL,"    UUID: %s",stats_uuid);
				menu_add_item_menu_format(array_menu_common,MENU_OPCION_SEPARADOR,NULL,NULL,"    System: %s",COMPILATION_SYSTEM);
				menu_add_item_menu_format(array_menu_common,MENU_OPCION_SEPARADOR,NULL,NULL,"    Minutes: %d",stats_get_current_total_minutes_use() );
				
				menu_add_item_menu_format(array_menu_common,MENU_OPCION_SEPARADOR,NULL,NULL,"    Speccy queries: %d",stats_total_speccy_browser_queries);
				
				menu_add_item_menu_format(array_menu_common,MENU_OPCION_SEPARADOR,NULL,NULL,"    ZX81 queries: %d",stats_total_zx81_browser_queries);
				
				menu_add_item_menu_format(array_menu_common,MENU_OPCION_SEPARADOR,NULL,NULL,"    Emulator version: %s",EMULATOR_VERSION);
				
				menu_add_item_menu_format(array_menu_common,MENU_OPCION_SEPARADOR,NULL,NULL,"    Build Number: %s",BUILDNUMBER);
				

			}

              
						
			menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

            menu_add_ESC_item(array_menu_common);

            retorno_menu=menu_dibuja_menu(&settings_statistics_opcion_seleccionada,&item_seleccionado,array_menu_common,"Statistics Settings" );

                
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




}










void menu_storage_mmc_reload(MENU_ITEM_PARAMETERS)
{
	if (mmc_read_file_to_memory()==0) {
		menu_generic_message_splash("Reload MMC","OK. MMC file reloaded");
	}
}

void menu_divmmc_rom_file(MENU_ITEM_PARAMETERS)
{


	//desactivamos diviface divmmc. Así obligamos que el usuario tenga que activarlo de nuevo, recargando del firmware
	divmmc_diviface_disable();


        char *filtros[3];

        filtros[0]="rom";
				filtros[1]="bin";
        filtros[2]=0;


        if (menu_filesel("Select ROM File",filtros, divmmc_rom_name)==1) {
				//Nada

        }
        //Sale con ESC
        else {
                //Quitar nombre
                divmmc_rom_name[0]=0;


        }

				menu_generic_message("Change DIVMMC ROM","OK. Remember to enable DIVMMC paging to load the firmware");
}

void menu_storage_diviface_eprom_write_jumper(MENU_ITEM_PARAMETERS)
{
	diviface_eprom_write_jumper.v ^=1;
}

void menu_storage_mmc_write_protect(MENU_ITEM_PARAMETERS)
{
	mmc_write_protection.v ^=1;
}


void menu_storage_mmc_persistent_writes(MENU_ITEM_PARAMETERS)
{
	mmc_persistent_writes.v ^=1;
}

void menu_storage_mmc_browser(MENU_ITEM_PARAMETERS)
{
	//menu_file_mmc_browser_show(mmc_file_name,"MMC");
	menu_file_viewer_read_file("MMC file viewer",mmc_file_name);
}

void menu_storage_mmc_emulation(MENU_ITEM_PARAMETERS)
{
	if (mmc_enabled.v) mmc_disable();
	else mmc_enable();
}


int menu_storage_mmc_emulation_cond(void)
{
        if (mmc_file_name[0]==0) return 0;
        else return 1;
}

int menu_storage_mmc_if_enabled_cond(void)
{
	return mmc_enabled.v;
}

void menu_storage_zxmmc_emulation(MENU_ITEM_PARAMETERS)
{
	zxmmc_emulation.v ^=1;
}

void menu_storage_divmmc_mmc_ports_emulation(MENU_ITEM_PARAMETERS)
{
        if (divmmc_mmc_ports_enabled.v) divmmc_mmc_ports_disable();
        else divmmc_mmc_ports_enable();
}

void menu_storage_divmmc_diviface(MENU_ITEM_PARAMETERS)
{
	if (divmmc_diviface_enabled.v) divmmc_diviface_disable();
	else {
		divmmc_diviface_enable();
                //Tambien activamos puertos si esta mmc activado. Luego si quiere el usuario que los desactive
                if (mmc_enabled.v) divmmc_mmc_ports_enable();
	}
}


void menu_storage_mmc_file_after_select_ask_configure_tbblue(void)
{
		if (MACHINE_IS_TBBLUE) {
				if (menu_confirm_yesno("Configure MMC settings?")) {

					//Repetir sentencia de usuario:
					//1) Habilitar MMC
					//2) Desactivar DIVMMC paging
					//3) Habilitar divmmc ports
					//4) Hard reset
					
					//Sabemos que esto estara desactivado pero bueno, mejor lo chequeamos para que no conmute en caso que ya estuviera
					if (mmc_enabled.v==0) menu_storage_mmc_emulation(0);

					if (divmmc_diviface_enabled.v) menu_storage_divmmc_diviface(0);

					if (divmmc_mmc_ports_enabled.v==0) menu_storage_divmmc_mmc_ports_emulation(0);

					hard_reset_cpu();

					salir_todos_menus=1;
				}
			}
}

void menu_storage_mmc_file(MENU_ITEM_PARAMETERS)
{

	mmc_disable();

        char *filtros[5];

        filtros[0]="mmc";
		filtros[1]="mmcide";
		filtros[2]="hdf";
		filtros[3]="img";
		
        filtros[4]=0;


	   //guardamos directorio actual
        char directorio_actual[PATH_MAX];
        getcwd(directorio_actual,PATH_MAX);

              //Obtenemos directorio de trd
        //si no hay directorio, vamos a rutas predefinidas
        if (mmc_file_name[0]==0) menu_chdir_sharedfiles();

        else {
                char directorio[PATH_MAX];
                util_get_dir(mmc_file_name,directorio);
                //printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

                //cambiamos a ese directorio, siempre que no sea nulo
                if (directorio[0]!=0) {
                        debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
                        zvfs_chdir(directorio);
                }
        }


        
		int ret=menu_filesel("Select MMC File",filtros,mmc_file_name);
		//volvemos a directorio inicial
        zvfs_chdir(directorio_actual);


        if (ret==1) {
		if (!si_existe_archivo(mmc_file_name)) {
			if (menu_confirm_yesno_texto("File does not exist","Create?")==0) {
                                mmc_file_name[0]=0;
                                return;
                        }

			//Preguntar tamanyo en MB
			char string_tamanyo[5];
			sprintf (string_tamanyo,"32");
			menu_ventana_scanf("Size (in MB)",string_tamanyo,5);
			int size=parse_string_to_number(string_tamanyo);
			if (size<1) {
				debug_printf (VERBOSE_ERR,"Invalid file size");
				mmc_file_name[0]=0;
                                return;
			}

			if (size>=1024) {
				menu_warn_message("Using MMC bigger than 1 GB can be very slow");
			}


			//Crear archivo vacio
		        FILE *ptr_mmcfile;
			ptr_mmcfile=fopen(mmc_file_name,"wb");

		        long int totalsize=size;
			totalsize=totalsize*1024*1024;
			z80_byte valor_grabar=0;

		        if (ptr_mmcfile!=NULL) {
				while (totalsize) {
					fwrite(&valor_grabar,1,1,ptr_mmcfile);
					totalsize--;
				}
		                fclose(ptr_mmcfile);
		        }

		}

		else {
			//Comprobar aqui tambien el tamanyo
			long int size=get_file_size(mmc_file_name);
			if (size>1073741824L) {
				menu_warn_message("Using MMC bigger than 1 GB can be very slow");
            }


			//Y pedir si configurar automaticamente en caso de TBBLUE
			menu_storage_mmc_file_after_select_ask_configure_tbblue();
			
		}


        }
        //Sale con ESC
        else {
                //Quitar nombre
                mmc_file_name[0]=0;


        }
}

void menu_storage_divmmc_diviface_total_ram(MENU_ITEM_PARAMETERS)
{
	diviface_current_ram_memory_bits++;
	if (diviface_current_ram_memory_bits==7) diviface_current_ram_memory_bits=2;
}


//Descargar imagen MMC oficial de tbblue
void menu_storage_mmc_download_tbblue(void)
{

	menu_first_aid("tbblue_download_sd_bug");

	//http://zxspectrumnext.online/cspect/tbbluemmc-32mb.zip

	char *host_final="zxspectrumnext.online";

	//char *url="/cspect/tbbluemmc-32mb.zip";

	char url[NETWORK_MAX_URL];


	int opcion_tamanyo_imagen=menu_simple_four_choices("Image type","Which size?",
														"Small   32 MB",	
														"Medium 128 MB",
														"Big    512 MB",
														"Large    2 GB");

	int estimated_size=64*1024*1024;

	switch (opcion_tamanyo_imagen) {
		case 1:
			strcpy(url,"/cspect/tbbluemmc-32mb.zip");
			estimated_size=64*1024*1024;
		break;

		case 2:
			strcpy(url,"/cspect/tbbluemmc-128mb.zip");
			estimated_size=128*1024*1024;
		break;

		case 3:
			strcpy(url,"/cspect/tbbluemmc-512mb.zip");
			estimated_size=512*1024*1024;
		break;		

		case 4:
			strcpy(url,"/cspect/cspect-next-2gb.zip");
			estimated_size=512*1024*1024; //Pensamos que esa SD esta comprimida de 2 GB a 512 MB
		break;


		default:
			return;
		break;
	}


	debug_printf(VERBOSE_DEBUG,"Selected url %s",url);

	char archivo_zip[PATH_MAX];

	//Ruta destino en el home
	char dest_dir[PATH_MAX];



//Aunque en Windows no le acaba de gustar, por alguna razón, la ruta al unzip. En Windows lo metemos en la ruta actual
#ifdef MINGW
	dest_dir[0]=0; //Cadena vacia -> carpeta actual
#else
	util_get_home_dir(dest_dir);
#endif

	


	char zipfilename[PATH_MAX];
	util_get_file_no_directory(url,zipfilename);

	//sprintf(archivo_zip,"%s%s",dest_dir,"tbbluemmc-32mb.zip");
	sprintf(archivo_zip,"%s%s",dest_dir,zipfilename);

	int ssl_use=0;


	int ret=menu_download_file(host_final,url,archivo_zip,ssl_use,estimated_size,"");  

	if (ret==200) {       
		//descomprimimos zip
		char final_mmc_dir[PATH_MAX];
		sprintf(final_mmc_dir,"%s.dir",archivo_zip);

		//Descomprimir con ventana de progreso y pthread aparte de descompresion
		menu_uncompress_zip_progress(archivo_zip,final_mmc_dir);

		//y abrimos menu de mmc. Deducimos archivo final "tbblue.mmc". TODO: en el caso de imagen 2gb de cspect esto no es asi
		//char guessed_mmc_file[PATH_MAX];
		sprintf(mmc_file_name,"%s/tbblue.mmc",final_mmc_dir);
	
		//strcpy(mmc_file_name,guessed_mmc_file);

		menu_storage_mmc_file(0);

		return;
	}
	else {
		if (ret<0) {	
			menu_network_error(ret);
		}
		else {
			debug_printf(VERBOSE_ERR,"Error downloading software. Return code: %d",ret);
		}

	}






}

void menu_storage_mmc_use_local_tbblue(void)
{
	char buffer_nombre[PATH_MAX];

	if (find_sharedfile("tbblue.mmc",buffer_nombre)) {
		//Asignar la MMC
		//TODO: esto mete ruta relativa (en caso de . o ../Resources). Se podria meter ruta absoluta
		strcpy(mmc_file_name,buffer_nombre);


		//Luego preguntar si aplicar divmmc etc
		menu_storage_mmc_file_after_select_ask_configure_tbblue();
	}

	else {
		menu_error_message("tbblue.mmc image not found");
	}

}


void menu_storage_mmc_autoconfigure_tbblue(MENU_ITEM_PARAMETERS)
{

	int tipo_imagen;
	
//Si no hay phreads, solo se puede usar la opcion local
#ifdef NETWORKING_DISABLED
	tipo_imagen=1;
#else
	tipo_imagen=menu_simple_two_choices("SD Image type","Included or download?","Use included in ZEsarUX","Download from official repo");
#endif
	
	switch(tipo_imagen) {
		case 1:
			//Usar imagen local
			menu_storage_mmc_use_local_tbblue();
		break;

		case 2:
			//Usar repo remoto
			menu_storage_mmc_download_tbblue();
		break;
	}

}


//menu MMC/Divmmc
void menu_mmc_divmmc(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_mmc_divmmc;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

                char string_mmc_file_shown[17];
								char string_divmmc_rom_file_shown[10];


                        menu_tape_settings_trunc_name(mmc_file_name,string_mmc_file_shown,17);
                        menu_add_item_menu_inicial_format(&array_menu_mmc_divmmc,MENU_OPCION_NORMAL,menu_storage_mmc_file,NULL,"~~MMC File [%s]",string_mmc_file_shown);
                        menu_add_item_menu_shortcut(array_menu_mmc_divmmc,'m');
                        menu_add_item_menu_tooltip(array_menu_mmc_divmmc,"MMC Emulation file");
                        menu_add_item_menu_ayuda(array_menu_mmc_divmmc,"MMC Emulation file");


  if (MACHINE_IS_TBBLUE) {
  
  menu_add_item_menu_format(array_menu_mmc_divmmc,MENU_OPCION_NORMAL,menu_storage_mmc_autoconfigure_tbblue,NULL,"Autoconfigure Next SD");
  
  }



                        menu_add_item_menu_format(array_menu_mmc_divmmc,MENU_OPCION_NORMAL,menu_storage_mmc_emulation,menu_storage_mmc_emulation_cond,"[%c] MMC ~~Emulation", (mmc_enabled.v ? 'X' : ' '));
                        menu_add_item_menu_shortcut(array_menu_mmc_divmmc,'e');
                        menu_add_item_menu_tooltip(array_menu_mmc_divmmc,"MMC Emulation");
                        menu_add_item_menu_ayuda(array_menu_mmc_divmmc,"MMC Emulation");




                        menu_add_item_menu_format(array_menu_mmc_divmmc,MENU_OPCION_NORMAL,menu_storage_mmc_write_protect,NULL,"[%c] ~~Write protect", (mmc_write_protection.v ? 'X' : ' '));
			menu_add_item_menu_shortcut(array_menu_mmc_divmmc,'w');
                        menu_add_item_menu_tooltip(array_menu_mmc_divmmc,"If MMC disk is write protected");
                        menu_add_item_menu_ayuda(array_menu_mmc_divmmc,"If MMC disk is write protected");


			menu_add_item_menu_format(array_menu_mmc_divmmc,MENU_OPCION_NORMAL,menu_storage_mmc_persistent_writes,NULL,"[%c] Persistent Writes",(mmc_persistent_writes.v ? 'X' : ' ') );
			menu_add_item_menu_tooltip(array_menu_mmc_divmmc,"Tells if MMC writes are saved to disk");
			menu_add_item_menu_ayuda(array_menu_mmc_divmmc,"Tells if MMC writes are saved to disk. "
			"Note: all writing operations to MMC are always saved to internal memory (unless you disable write permission), but this setting "
			"tells if these changes are written to disk or not."
			);

  			menu_add_item_menu_format(array_menu_mmc_divmmc,MENU_OPCION_NORMAL,menu_storage_mmc_browser,menu_storage_mmc_emulation_cond,"MMC ~~Viewer");
                        menu_add_item_menu_shortcut(array_menu_mmc_divmmc,'v');
                        menu_add_item_menu_tooltip(array_menu_mmc_divmmc,"MMC Viewer");
                        menu_add_item_menu_ayuda(array_menu_mmc_divmmc,"MMC Viewer");


			if (mmc_enabled.v) {
				menu_add_item_menu_format(array_menu_mmc_divmmc,MENU_OPCION_NORMAL,menu_storage_mmc_reload,NULL,"Reload MMC file");
				menu_add_item_menu_tooltip(array_menu_mmc_divmmc,"Reload MMC contents from MMC file to emulator memory");
				menu_add_item_menu_ayuda(array_menu_mmc_divmmc,"Reload MMC contents from MMC file to emulator memory. You can modify the MMC file "
																								"outside the emulator, and reload its contents without having to disable and enable MM.");
			}


			menu_add_item_menu(array_menu_mmc_divmmc,"",MENU_OPCION_SEPARADOR,NULL,NULL);

			menu_add_item_menu_format(array_menu_mmc_divmmc,MENU_OPCION_NORMAL,menu_storage_divmmc_diviface,NULL,"[%c] ~~DIVMMC paging",(divmmc_diviface_enabled.v ? 'X' : ' ') );
                        menu_add_item_menu_shortcut(array_menu_mmc_divmmc,'d');
			menu_add_item_menu_tooltip(array_menu_mmc_divmmc,"Enables DIVMMC paging and firmware, and DIVMMC access ports if MMC emulation is enabled");
			menu_add_item_menu_ayuda(array_menu_mmc_divmmc,"Enables DIVMMC paging and firmware, and DIVMMC access ports if MMC emulation is enabled");

			if (divmmc_diviface_enabled.v) {
				menu_add_item_menu_format(array_menu_mmc_divmmc,MENU_OPCION_NORMAL,menu_storage_divmmc_diviface_total_ram,NULL,"DIVMMC RAM [%d KB]",get_diviface_total_ram() );
				menu_add_item_menu_tooltip(array_menu_mmc_divmmc,"Changes DIVMMC RAM");
				menu_add_item_menu_ayuda(array_menu_mmc_divmmc,"Changes DIVMMC RAM");


			}

            //En tbblue y zxuno no tiene sentido mostrar estas opciones, no las usa
            //incluso la anterior de divmmc ram, las dos maquinas tienen 128kb de divmmc ram por defecto,
            //esta opcion si que la leen esas máquinas aunque alterar ese valor puede tener efectos indeseados
            if (!MACHINE_IS_ZXUNO && !MACHINE_IS_TBBLUE) {            

                if (divmmc_rom_name[0]==0) sprintf (string_divmmc_rom_file_shown,"Default");
                else menu_tape_settings_trunc_name(divmmc_rom_name, string_divmmc_rom_file_shown,10);
                menu_add_item_menu_format(array_menu_mmc_divmmc,MENU_OPCION_NORMAL,menu_divmmc_rom_file,NULL,"DIVMMC EPROM File [%s]", string_divmmc_rom_file_shown);

                menu_add_item_menu_tooltip(array_menu_mmc_divmmc,"Changes DIVMMC firmware eprom file");
                menu_add_item_menu_ayuda(array_menu_mmc_divmmc,"Changes DIVMMC firmware eprom file");


                if (divmmc_diviface_enabled.v) {
                    menu_add_item_menu_format(array_menu_mmc_divmmc,MENU_OPCION_NORMAL,menu_storage_diviface_eprom_write_jumper,NULL,"[%c] Firmware writeable",
                    (diviface_eprom_write_jumper.v ? 'X' : ' ') );
                    menu_add_item_menu_tooltip(array_menu_mmc_divmmc,"Allows writing to DivIDE/DivMMC eprom");
                    menu_add_item_menu_ayuda(array_menu_mmc_divmmc,"Allows writing to DivIDE/DivMMC eprom. Changes are lost when you exit the emulator");
                }

            }




                        menu_add_item_menu_format(array_menu_mmc_divmmc,MENU_OPCION_NORMAL,menu_storage_divmmc_mmc_ports_emulation,menu_storage_mmc_if_enabled_cond,"[%c] DIVMMC ~~ports",(divmmc_mmc_ports_enabled.v ? 'X' : ' ') );
                        menu_add_item_menu_shortcut(array_menu_mmc_divmmc,'p');
                        menu_add_item_menu_tooltip(array_menu_mmc_divmmc,"Enables DIVMMC access ports");
                        menu_add_item_menu_ayuda(array_menu_mmc_divmmc,"Enables DIVMMC access ports. Requires enabling MMC Emulation");


                        menu_add_item_menu(array_menu_mmc_divmmc,"",MENU_OPCION_SEPARADOR,NULL,NULL);


                        menu_add_item_menu_format(array_menu_mmc_divmmc,MENU_OPCION_NORMAL,menu_storage_zxmmc_emulation,menu_storage_mmc_if_enabled_cond,"[%c] ~~ZXMMC Enabled",(zxmmc_emulation.v ? 'X' : ' ') );
                        menu_add_item_menu_shortcut(array_menu_mmc_divmmc,'z');
                        menu_add_item_menu_tooltip(array_menu_mmc_divmmc,"Access MMC using ZXMMC");
                        menu_add_item_menu_ayuda(array_menu_mmc_divmmc,"Enables ZXMMC ports to access MMC");



				menu_add_item_menu(array_menu_mmc_divmmc,"",MENU_OPCION_SEPARADOR,NULL,NULL);
                //menu_add_item_menu(array_menu_mmc_divmmc,"ESC Back",MENU_OPCION_NORMAL|MENU_OPCION_ESC,NULL,NULL);
                menu_add_ESC_item(array_menu_mmc_divmmc);

                retorno_menu=menu_dibuja_menu(&mmc_divmmc_opcion_seleccionada,&item_seleccionado,array_menu_mmc_divmmc,"MMC" );

                
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




}





void menu_storage_ide_emulation(MENU_ITEM_PARAMETERS)
{
        if (ide_enabled.v) ide_disable();
        else ide_enable();
}


int menu_storage_ide_emulation_cond(void)
{
        if (ide_file_name[0]==0) return 0;
        else return 1;
}

/*
void menu_storage_divide_emulation(MENU_ITEM_PARAMETERS)
{
        if (divide_enabled.v) divide_disable();
        else divide_enable();
}
*/


void menu_storage_divide_ide_ports_emulation(MENU_ITEM_PARAMETERS)
{
        if (divide_ide_ports_enabled.v) divide_ide_ports_disable();
        else divide_ide_ports_enable();
}

void menu_storage_divide_diviface(MENU_ITEM_PARAMETERS)
{
        if (divide_diviface_enabled.v) divide_diviface_disable();
        else {
                divide_diviface_enable();
                //Tambien activamos puertos si esta ide activado. Luego si quiere el usuario que los desactive
		if (ide_enabled.v) divide_ide_ports_enable();
        }
}



void menu_storage_ide_file(MENU_ITEM_PARAMETERS)
{

        ide_disable();

        char *filtros[3];

        filtros[0]="ide";
		filtros[1]="mmcide";
        filtros[2]=0;


        if (menu_filesel("Select IDE File",filtros,ide_file_name)==1) {
                if (!si_existe_archivo(ide_file_name)) {
                        if (menu_confirm_yesno_texto("File does not exist","Create?")==0) {
                                ide_file_name[0]=0;
                                return;
                        }

                        //Preguntar tamanyo en MB
                        char string_tamanyo[5];
                        sprintf (string_tamanyo,"32");
                        menu_ventana_scanf("Size (in MB)",string_tamanyo,5);
                        int size=parse_string_to_number(string_tamanyo);
                        if (size<1) {
                                debug_printf (VERBOSE_ERR,"Invalid file size");
                                ide_file_name[0]=0;
                                return;
                        }

                        if (size>=1024) {
                                menu_warn_message("Using IDE bigger than 1 GB can be very slow");
                        }


                        //Crear archivo vacio
                        FILE *ptr_idefile;
                        ptr_idefile=fopen(ide_file_name,"wb");

   long int totalsize=size;
                        totalsize=totalsize*1024*1024;
                        z80_byte valor_grabar=0;

                        if (ptr_idefile!=NULL) {
                                while (totalsize) {
                                        fwrite(&valor_grabar,1,1,ptr_idefile);
                                        totalsize--;
                                }
                                fclose(ptr_idefile);
                        }

                }

                else {
                        //Comprobar aqui tambien el tamanyo
                        long int size=get_file_size(ide_file_name);
                        if (size>1073741824L) {
                                menu_warn_message("Using IDE bigger than 1 GB can be very slow");
                        }
                }


        }
        //Sale con ESC
        else {
                //Quitar nombre
                ide_file_name[0]=0;


        }
}


int menu_storage_ide_if_enabled_cond(void)
{
	return ide_enabled.v;
}

void menu_eightbitsimple_enable(MENU_ITEM_PARAMETERS)
{
	if (eight_bit_simple_ide_enabled.v) eight_bit_simple_ide_disable();
	else eight_bit_simple_ide_enable();
}

void menu_atomlite_enable(MENU_ITEM_PARAMETERS)
{
        int reset=0;

        if (atomlite_enabled.v) {

                reset=menu_confirm_yesno_texto("Confirm reset","Load normal rom and reset?");

                atomlite_enabled.v=0;
        }

        else {
                reset=menu_confirm_yesno_texto("Confirm reset","Load atomlite rom and reset?");
                atomlite_enabled.v=1;
        }

        if (reset) {
                set_machine(NULL);
                cold_start_cpu_registers();
                reset_cpu();
		salir_todos_menus=1;
        }

}

void menu_storage_ide_reload(MENU_ITEM_PARAMETERS)
{
	if (ide_read_file_to_memory()==0) {
		menu_generic_message_splash("Reload IDE","OK. IDE file reloaded");
	}
}


void menu_divide_rom_file(MENU_ITEM_PARAMETERS)
{


	//desactivamos diviface divide. Así obligamos que el usuario tenga que activarlo de nuevo, recargando del firmware
	divide_diviface_disable();


        char *filtros[3];

        filtros[0]="rom";
				filtros[1]="bin";
        filtros[2]=0;


        if (menu_filesel("Select ROM File",filtros, divide_rom_name)==1) {
				//Nada

        }
        //Sale con ESC
        else {
                //Quitar nombre
                divide_rom_name[0]=0;


        }

				menu_generic_message("Change DIVIDE ROM","OK. Remember to enable DIVIDE paging to load the firmware");
}

void menu_storage_ide_write_protect(MENU_ITEM_PARAMETERS)
{
	ide_write_protection.v ^=1;
}

void menu_storage_ide_persistent_writes(MENU_ITEM_PARAMETERS)
{
	ide_persistent_writes.v ^=1;
}


void menu_storage_ide_browser(MENU_ITEM_PARAMETERS)
{
	//menu_file_mmc_browser_show(ide_file_name,"IDE");
	menu_file_viewer_read_file("IDE file viewer",ide_file_name);
}

//menu IDE/Divide
void menu_ide_divide(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_ide_divide;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

                char string_ide_file_shown[17];
								char string_divide_rom_file_shown[10];





                        menu_tape_settings_trunc_name(ide_file_name,string_ide_file_shown,17);
                        menu_add_item_menu_inicial_format(&array_menu_ide_divide,MENU_OPCION_NORMAL,menu_storage_ide_file,NULL,"~~IDE File [%s]",string_ide_file_shown);
                        menu_add_item_menu_shortcut(array_menu_ide_divide,'i');
                        menu_add_item_menu_tooltip(array_menu_ide_divide,"IDE Emulation file");
                        menu_add_item_menu_ayuda(array_menu_ide_divide,"IDE Emulation file");


                        menu_add_item_menu_format(array_menu_ide_divide,MENU_OPCION_NORMAL,menu_storage_ide_emulation,menu_storage_ide_emulation_cond,"[%c] IDE ~~Emulation", (ide_enabled.v ? 'X' : ' '));
                        menu_add_item_menu_shortcut(array_menu_ide_divide,'e');
                        menu_add_item_menu_tooltip(array_menu_ide_divide,"IDE Emulation");
                        menu_add_item_menu_ayuda(array_menu_ide_divide,"IDE Emulation");


                        menu_add_item_menu_format(array_menu_ide_divide,MENU_OPCION_NORMAL,menu_storage_ide_write_protect,NULL,"[%c] ~~Write protect", (ide_write_protection.v ? 'X' : ' '));
			menu_add_item_menu_shortcut(array_menu_ide_divide,'w');
                        menu_add_item_menu_tooltip(array_menu_ide_divide,"If IDE disk is write protected");
                        menu_add_item_menu_ayuda(array_menu_ide_divide,"If IDE disk is write protected");


			menu_add_item_menu_format(array_menu_ide_divide,MENU_OPCION_NORMAL,menu_storage_ide_persistent_writes,NULL,"[%c] Persistent Writes",(ide_persistent_writes.v ? 'X' : ' ') );
			menu_add_item_menu_tooltip(array_menu_ide_divide,"Tells if IDE writes are saved to disk");
			menu_add_item_menu_ayuda(array_menu_ide_divide,"Tells if IDE writes are saved to disk. "
			"Note: all writing operations to IDE are always saved to internal memory (unless you disable write permission), but this setting "
			"tells if these changes are written to disk or not."
			);


			menu_add_item_menu_format(array_menu_ide_divide,MENU_OPCION_NORMAL,menu_storage_ide_browser,menu_storage_ide_emulation_cond,"IDE ~~Viewer");
                        menu_add_item_menu_shortcut(array_menu_ide_divide,'v');
                        menu_add_item_menu_tooltip(array_menu_ide_divide,"IDE Viewer");
                        menu_add_item_menu_ayuda(array_menu_ide_divide,"IDE Viewer");


												if (ide_enabled.v) {
												menu_add_item_menu_format(array_menu_ide_divide,MENU_OPCION_NORMAL,menu_storage_ide_reload,NULL,"Reload IDE file");
												menu_add_item_menu_tooltip(array_menu_ide_divide,"Reload IDE contents from IDE file to emulator memory");
												menu_add_item_menu_ayuda(array_menu_ide_divide,"Reload IDE contents from IDE file to emulator memory. You can modify the IDE file "
												                        "outside the emulator, and reload its contents without having to disable and enable IDE");
												}

			


			if (MACHINE_IS_SPECTRUM) {

				menu_add_item_menu(array_menu_ide_divide,"",MENU_OPCION_SEPARADOR,NULL,NULL);

	                       menu_add_item_menu_format(array_menu_ide_divide,MENU_OPCION_NORMAL,menu_storage_divide_diviface,NULL,"[%c] ~~DIVIDE paging",(divide_diviface_enabled.v ? 'X' : ' ') );
        	                menu_add_item_menu_shortcut(array_menu_ide_divide,'d');
        	                menu_add_item_menu_tooltip(array_menu_ide_divide,"Enables DIVIDE paging and firmware, and DIVIDE access ports if IDE emulation is enabled");
        	                menu_add_item_menu_ayuda(array_menu_ide_divide,"Enables DIVIDE paging and firmware, and DIVIDE access ports if IDE emulation is enabled");

	                        if (divide_diviface_enabled.v) {
	                                menu_add_item_menu_format(array_menu_ide_divide,MENU_OPCION_NORMAL,menu_storage_divmmc_diviface_total_ram,NULL,"DIVIDE RAM [%d KB]",get_diviface_total_ram() );
        	                        menu_add_item_menu_tooltip(array_menu_ide_divide,"Changes DIVIDE RAM");
                	                menu_add_item_menu_ayuda(array_menu_ide_divide,"Changes DIVIDE RAM");



               		         }
													 if (divide_rom_name[0]==0) sprintf (string_divide_rom_file_shown,"Default");
													 else menu_tape_settings_trunc_name(divide_rom_name, string_divide_rom_file_shown,10);
													 menu_add_item_menu_format(array_menu_ide_divide,MENU_OPCION_NORMAL,menu_divide_rom_file,NULL,"DIVIDE EPROM File [%s]", string_divide_rom_file_shown);

													 menu_add_item_menu_tooltip(array_menu_ide_divide,"Changes DIVIDE firmware eprom file");
													 menu_add_item_menu_ayuda(array_menu_ide_divide,"Changes DIVIDE firmware eprom file");

													 if (divide_diviface_enabled.v) {
										 				menu_add_item_menu_format(array_menu_ide_divide,MENU_OPCION_NORMAL,menu_storage_diviface_eprom_write_jumper,NULL,"[%c] Firmware writeable",
										 				(diviface_eprom_write_jumper.v ? 'X' : ' ') );
										 				menu_add_item_menu_tooltip(array_menu_ide_divide,"Allows writing to DivIDE/DivMMC eprom");
										 				menu_add_item_menu_ayuda(array_menu_ide_divide,"Allows writing to DivIDE/DivMMC eprom. Changes are lost when you exit the emulator");
										 			}



	                        menu_add_item_menu_format(array_menu_ide_divide,MENU_OPCION_NORMAL,menu_storage_divide_ide_ports_emulation,menu_storage_ide_if_enabled_cond,"[%c] DIVIDE ~~ports",(divide_ide_ports_enabled.v ? 'X' : ' ') );
        	                menu_add_item_menu_shortcut(array_menu_ide_divide,'p');
                	        menu_add_item_menu_tooltip(array_menu_ide_divide,"Enables DIVIDE access ports");
                        	menu_add_item_menu_ayuda(array_menu_ide_divide,"Enables DIVIDE access ports. Requires enabling IDE Emulation");


			}

			if (MACHINE_IS_SPECTRUM) {
				menu_add_item_menu(array_menu_ide_divide,"",MENU_OPCION_SEPARADOR,NULL,NULL);
				
				menu_add_item_menu_format(array_menu_ide_divide,MENU_OPCION_NORMAL,menu_eightbitsimple_enable,menu_storage_ide_if_enabled_cond,"[%c] 8-bit simple IDE",(eight_bit_simple_ide_enabled.v ? 'X' : ' ') );
			}


        if (MACHINE_IS_SAM) {
        		menu_add_item_menu(array_menu_ide_divide,"",MENU_OPCION_SEPARADOR,NULL,NULL);

                        menu_add_item_menu_format(array_menu_ide_divide,MENU_OPCION_NORMAL,menu_atomlite_enable,NULL,"[%c] ~~Atom Lite",(atomlite_enabled.v ? 'X' : ' ' ) );
                        menu_add_item_menu_shortcut(array_menu_ide_divide,'a');
                        menu_add_item_menu_tooltip(array_menu_ide_divide,"Enable Atom Lite");
                        menu_add_item_menu_ayuda(array_menu_ide_divide,"Enable Atom Lite");
                }



                                menu_add_item_menu(array_menu_ide_divide,"",MENU_OPCION_SEPARADOR,NULL,NULL);
                //menu_add_item_menu(array_menu_ide_divide,"ESC Back",MENU_OPCION_NORMAL|MENU_OPCION_ESC,NULL,NULL);
                menu_add_ESC_item(array_menu_ide_divide);

                retorno_menu=menu_dibuja_menu(&ide_divide_opcion_seleccionada,&item_seleccionado,array_menu_ide_divide,"IDE" );

                
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




}

void menu_view_screen(MENU_ITEM_PARAMETERS)
{
        menu_espera_no_tecla();

	//para que no se vea oscuro
	menu_set_menu_abierto(0);
	//modificado_border.v=1;

	menu_cls_refresh_emulated_screen();

	//menu_refresca_pantalla();
        menu_espera_tecla();
	menu_set_menu_abierto(1);
	menu_espera_no_tecla();
	modificado_border.v=1;
}

void menu_display_load_screen(MENU_ITEM_PARAMETERS)
{

char screen_load_file[PATH_MAX];

  char *filtros[2];

        filtros[0]="scr";
        filtros[1]=0;


        if (menu_filesel("Select Screen File",filtros,screen_load_file)==1) {
		load_screen(screen_load_file);
                //Y salimos de todos los menus
                salir_todos_menus=1;

        }

}

void menu_display_save_screen(MENU_ITEM_PARAMETERS)
{

	char screen_save_file[PATH_MAX];

	char *filtros[4];


	if (MACHINE_IS_SPECTRUM) {
		filtros[0]="scr";
		filtros[1]="pbm";
		filtros[2]="bmp";
		filtros[3]=0;
	}

	else {
		filtros[0]="bmp";
		filtros[1]=0;			
	}


	if (menu_filesel("Select Screen File",filtros,screen_save_file)==1) {

		//Ver si archivo existe y preguntar
		struct stat buf_stat;

		if (stat(screen_save_file, &buf_stat)==0) {

			if (menu_confirm_yesno_texto("File exists","Overwrite?")==0) return;

		}

		save_screen(screen_save_file);

        //Si ha ido bien la grabacion
		if (!if_pending_error_message) menu_generic_message_splash("Save Screen","OK. Screen saved");

		//Y salimos de todos los menus
		salir_todos_menus=1;

	}

}


void menu_unpaws_ungac(MENU_ITEM_PARAMETERS)
{

	char mensaje[1024];

	int retorno=util_unpawsetc_dump_words(mensaje);

	if (retorno>=0) {
		menu_generic_message_format("Extract Words",mensaje);
	}

	else {
		debug_printf (VERBOSE_ERR,mensaje);
	}


}

void menu_display_window_list_item(MENU_ITEM_PARAMETERS)
{
	//en valor_opcion, numero entrada

    int tipo=menu_simple_two_choices("Action","Do you want to","Move to top","Close");

    if (tipo==0) return; //ESC	


	zxvision_window *ventana;

	ventana=zxvision_return_n_window_from_top(valor_opcion);

	if (ventana==NULL) {
		menu_error_message("Can not find that window");
		return;
	}

	if (tipo==1) zxvision_window_move_this_window_on_top(ventana);
	else zxvision_window_delete_this_window(ventana);
}

void menu_display_window_close_all(MENU_ITEM_PARAMETERS)
{
	if (menu_confirm_yesno("Close all windows")) {
		zxvision_window_delete_all_windows();
		cls_menu_overlay();
        menu_generic_message_splash("Close all windows","OK. All windows closed");
	}
}

void menu_display_window_list(MENU_ITEM_PARAMETERS)
{
        //Dado que es una variable local, siempre podemos usar este nombre array_menu_common
        menu_item *array_menu_common;
        menu_item item_seleccionado;
        int retorno_menu;

		int comun_opcion_seleccionada=0;

	do {


		//menu_add_item_menu_inicial(&array_menu_common,"",MENU_OPCION_UNASSIGNED,NULL,NULL);
		menu_add_item_menu_inicial_format(&array_menu_common,MENU_OPCION_NORMAL,NULL,NULL,"-Top-");

		zxvision_window *ventana=zxvision_current_window;

		int total_ventanas=0;

		while (ventana!=NULL) {

			menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_display_window_list_item,NULL,"%s",ventana->window_title);
			menu_add_item_menu_valor_opcion(array_menu_common,total_ventanas);

			total_ventanas++;

			ventana=ventana->previous_window;
			
		}

		menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,NULL,NULL,"-Bottom-");

		//if (!total_ventanas) menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,NULL,NULL,"(Empty)");

		menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

		menu_add_ESC_item(array_menu_common);

		retorno_menu=menu_dibuja_menu(&comun_opcion_seleccionada,&item_seleccionado,array_menu_common,"Window management");

			
			if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
					//llamamos por valor de funcion
					if (item_seleccionado.menu_funcion!=NULL) {
							//printf ("actuamos por funcion\n");
							item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
							
					}
			}

    } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);

}

//Minimizar todas las ventanas
void menu_display_window_minimize_all_common(void)
{
	//Podemos empezar desde la de arriba por ejemplo, da igual
	zxvision_window *ventana;

	ventana=zxvision_current_window;


	while (ventana!=NULL) {

		//Primero decimos que no esta minimizada
        ventana->is_minimized=0;

        //Luego simulamos accion de pulsar boton de minimizar ventana
        zxvision_handle_click_minimize(ventana);


		//Y guardar la geometria
		util_add_window_geometry_compact(ventana);

		ventana=ventana->previous_window;
	}	

	cls_menu_overlay();

    
}

//Reducir todas las ventanas a un tamaño pequeño "razonable" de 20x10, si es que no eran ya asi de pequeñas
void menu_display_window_reduce_all_common(void)
{
	//Podemos empezar desde la de arriba por ejemplo, da igual
	zxvision_window *ventana;

	ventana=zxvision_current_window;

	int ancho_maximo=20;
	int alto_maximo=10;


	while (ventana!=NULL) {

		//La hacemos mas pequeña si es que es mas grande
		//if (ventana->visible_width>ancho_maximo) ventana->visible_width=ancho_maximo;
		//if (ventana->visible_height>alto_maximo) ventana->visible_height=alto_maximo;

        //decir que no esta minimizada
        ventana->is_minimized=0;

		//Siempre la hacemos al tamaño indicado
		//ventana->visible_width=ancho_maximo;
		//ventana->visible_height=alto_maximo;
        //Usar siempre estas dos funciones para cambiar tamaño visible
        zxvision_set_visible_width(ventana,ancho_maximo);
        zxvision_set_visible_height(ventana,alto_maximo);




		//Y guardar la geometria
		util_add_window_geometry_compact(ventana);

		ventana=ventana->previous_window;
	}	

	cls_menu_overlay();
}


void menu_display_window_rearrange_all_common(void)
{
	zxvision_rearrange_background_windows();
}

void menu_display_window_rearrange_all(MENU_ITEM_PARAMETERS)
{
    menu_display_window_rearrange_all_common();

    menu_generic_message_splash("Rearrange all","OK. All windows rearranged");
}

void menu_display_window_reduce_all(MENU_ITEM_PARAMETERS)
{
    menu_display_window_reduce_all_common();

    menu_generic_message_splash("Reduce all","OK. All windows reduced");    
}

void menu_display_window_reduce_all_rearrange(MENU_ITEM_PARAMETERS)
{
    menu_display_window_reduce_all_common();
    menu_display_window_rearrange_all_common();

    menu_generic_message_splash("Reduce+rearrange all","OK. All windows reduced+rearranged");
}

void menu_display_window_minimize_all(MENU_ITEM_PARAMETERS)
{
    menu_display_window_minimize_all_common();

    menu_generic_message_splash("Minimize all","OK. All windows minimized");
}

void menu_display_window_minimize_all_rearrange(MENU_ITEM_PARAMETERS)
{
    menu_display_window_minimize_all_common();
    menu_display_window_rearrange_all_common();

    menu_generic_message_splash("Minimize+rearrange all","OK. All windows minimized+rearranged");
}

void menu_windows(MENU_ITEM_PARAMETERS)
{

	if (!menu_allow_background_windows) {
		menu_warn_message("Background windows setting is not enabled. You can enable it on Settings-> ZX Vision-> Background windows");
		return;
	}

    //Dado que es una variable local, siempre podemos usar este nombre array_menu_common
    menu_item *array_menu_common;
    menu_item item_seleccionado;
    int retorno_menu;
    do {

                
        menu_add_item_menu_inicial_format(&array_menu_common,MENU_OPCION_NORMAL,menu_display_window_list,NULL,"Window management");
        menu_add_item_menu_spanish_catalan(array_menu_common,"Gestión ventanas","Gestió finestres");
        menu_add_item_menu_tooltip(array_menu_common,"Move to top or close individual windows");
        menu_add_item_menu_ayuda(array_menu_common,"Move to top or close individual windows");

        menu_add_item_menu_en_es_ca(array_menu_common,MENU_OPCION_NORMAL,menu_display_window_reduce_all,NULL,
            "Reduce all windows","Reducir todas las ventanas","Reduir totes les finestres");
        menu_add_item_menu_tooltip(array_menu_common,"Reduce windows to maximum size 20x10");
        menu_add_item_menu_ayuda(array_menu_common,"Reduce windows to maximum size 20x10");

        menu_add_item_menu_en_es_ca(array_menu_common,MENU_OPCION_NORMAL,menu_display_window_minimize_all,NULL,
            "Minimize all windows","Minimizar todas las ventanas","Minimitzar totes les finestres");        

        menu_add_item_menu_en_es_ca(array_menu_common,MENU_OPCION_NORMAL,menu_display_window_rearrange_all,NULL,
            "Rearrange all windows","Reubicar todas ventanas","Reubicar totes les finestres");
        menu_add_item_menu_tooltip(array_menu_common,"Rearrange all windows on the ZX Desktop");
        menu_add_item_menu_ayuda(array_menu_common,"Rearrange all windows on the ZX Desktop");

        menu_add_item_menu_en_es_ca(array_menu_common,MENU_OPCION_NORMAL,menu_display_window_reduce_all_rearrange,NULL,
            "Reduce+rearrange all windows","Reducir+reubicar todas las ventanas","Reduir+reubicar totes les finestres");

        menu_add_item_menu_en_es_ca(array_menu_common,MENU_OPCION_NORMAL,menu_display_window_minimize_all_rearrange,NULL,
            "Minimize+rearrange all windows","Minimizar+reubicar todas ventanas","Minimitzar+reubicar totes les finestres");
                    
        

        menu_add_item_menu_en_es_ca(array_menu_common,MENU_OPCION_NORMAL,menu_display_window_close_all,NULL,
            "Close all windows","Cerrar todas las ventanas","Tancar totes les finestres");


        menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

        menu_add_ESC_item(array_menu_common);

        retorno_menu=menu_dibuja_menu(&windows_opcion_seleccionada,&item_seleccionado,array_menu_common,"Windows" );

                
        if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
            //llamamos por valor de funcion
            if (item_seleccionado.menu_funcion!=NULL) {
                    //printf ("actuamos por funcion\n");
                    item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                    
            }
        }

    } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




}

//menu display settings
void menu_display_settings(MENU_ITEM_PARAMETERS)
{

	menu_item *array_menu_display_settings;
	menu_item item_seleccionado;
	int retorno_menu;
	do {



        //Como no sabemos cual sera el item inicial, metemos este sin asignar, que se sobreescribe en el siguiente menu_add_item_menu
		menu_add_item_menu_inicial(&array_menu_display_settings,"",MENU_OPCION_UNASSIGNED,NULL,NULL);

		if (MACHINE_IS_SPECTRUM) {
			menu_add_item_menu_en_es_ca(array_menu_display_settings,MENU_OPCION_NORMAL,menu_display_load_screen,NULL,
                "~~Load Screen","~~Load Pantalla","~~Load Pantalla");
			menu_add_item_menu_shortcut(array_menu_display_settings,'l');
		}

		if (MACHINE_IS_SPECTRUM || MACHINE_IS_ZX8081 || MACHINE_IS_CPC) {
		menu_add_item_menu_en_es_ca(array_menu_display_settings,MENU_OPCION_NORMAL,menu_display_save_screen,NULL,
            "~~Save Screen","~~Salvar Pantalla","~~Salvar Pantalla");
		menu_add_item_menu_shortcut(array_menu_display_settings,'s');
		menu_add_item_menu_tooltip(array_menu_display_settings,"Save screen to disk. BMP format requires to enable real video first");
		menu_add_item_menu_ayuda(array_menu_display_settings,"Save screen to disk. BMP format requires to enable real video first");
		}


		menu_add_item_menu_en_es_ca(array_menu_display_settings,MENU_OPCION_NORMAL,menu_view_screen,NULL,
            "~~View Screen","~~Ver Pantalla","~~Veure Pantalla");
		menu_add_item_menu_shortcut(array_menu_display_settings,'v');


        menu_add_item_menu_en_es_ca(array_menu_display_settings,MENU_OPCION_NORMAL,menu_display_total_palette,NULL,
            "View ~~Colour Palettes","Ver Paletas de ~~Colores","Veure Paletes de ~~Colors");
        menu_add_item_menu_shortcut(array_menu_display_settings,'c');
        menu_add_item_menu_tooltip(array_menu_display_settings,"View full palettes or mapped palettes");
        menu_add_item_menu_ayuda(array_menu_display_settings,"You can see in this menu full colour palettes or mapped colour palettes. \n"
                                            "Full colour palettes means all the colours available for a mode, for example 256 colours on ULAPlus.\n"
                                            "Mapped colour palettes means the active palette for a mode, for example 64 colours on ULAPlus.");


       //Teclados en pantalla
        if (MACHINE_IS_SPECTRUM || MACHINE_IS_ZX8081) {
            menu_add_item_menu(array_menu_display_settings,"",MENU_OPCION_SEPARADOR,NULL,NULL);

            menu_add_item_menu_en_es_ca(array_menu_display_settings,MENU_OPCION_NORMAL,menu_onscreen_keyboard,NULL,
                "On Screen ~~Keyboard","Te~~klado en pantalla","Te~~klat a pantalla");
            menu_add_item_menu_shortcut(array_menu_display_settings,'k');
            menu_add_item_menu_tooltip(array_menu_display_settings,"Open on screen keyboard");
            menu_add_item_menu_ayuda(array_menu_display_settings,"You can also get this pressing F8, only for Spectrum and ZX80/81 machines");
        }

        if (MACHINE_IS_SPECTRUM || MACHINE_IS_ZX8081 || MACHINE_IS_CPC) {

            menu_add_item_menu_en_es_ca(array_menu_display_settings,MENU_OPCION_NORMAL,menu_osd_adventure_keyboard,NULL,
                "On Screen ~~Adventure Keyboard","Teclado de ~~Aventura en Pantalla","Teclat d'~~Aventura a Pantalla");
            menu_add_item_menu_shortcut(array_menu_display_settings,'a');
            menu_add_item_menu_tooltip(array_menu_display_settings,"Open On Screen Adventure Keyboard");
            menu_add_item_menu_ayuda(array_menu_display_settings,"Here you have an on screen keyboard but uses words instead of just letters. "
                "It's useful to play Text Adventures, you can redefine your own words");

        }


        if (MACHINE_IS_SPECTRUM || MACHINE_IS_CPC) {
            menu_add_item_menu_en_es_ca(array_menu_display_settings,MENU_OPCION_NORMAL,menu_unpaws_ungac,NULL,
                " ~~Extract words to Adv. Keyb."," ~~Extraer palabras a Tecl. Av."," ~~Extreure paraules a Tecl. Av.");
            menu_add_item_menu_spanish(array_menu_display_settings," ~~Extraer palabras a tecl. aven.");
            menu_add_item_menu_shortcut(array_menu_display_settings,'e');
            menu_add_item_menu_tooltip(array_menu_display_settings,"Runs the word extractor tool for adventure text games");
            menu_add_item_menu_ayuda(array_menu_display_settings,"It runs the word extractor tool and insert these words on the On Screen Adventure Keyboard. "
                "It can detect words on games written with Quill, Paws, DAAD, and GAC");
        }


			


 

        menu_add_item_menu(array_menu_display_settings,"",MENU_OPCION_SEPARADOR,NULL,NULL);
        //menu_add_item_menu(array_menu_display_settings,"ESC Back",MENU_OPCION_NORMAL|MENU_OPCION_ESC,NULL,NULL);
		menu_add_ESC_item(array_menu_display_settings);

        retorno_menu=menu_dibuja_menu(&display_settings_opcion_seleccionada,&item_seleccionado,array_menu_display_settings,"Display" );

                

		//NOTA: no llamar por numero de opcion dado que hay opciones que ocultamos (relacionadas con real video)

		if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {

			//llamamos por valor de funcion
        	        if (item_seleccionado.menu_funcion!=NULL) {
                	        //printf ("actuamos por funcion\n");
	                        item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
				
        	        }
		}

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);



}




void menu_ay_pianokeyboard_insert_inverse(char *origen_orig, int indice)
{
	char cadena_temporal[40];

	char *destino;

	destino=cadena_temporal;

	char *origen;
	origen=origen_orig;

	int i;

    //metemos un ~^ que indica siempre inverso sin bajar letra a minusculas
	for (i=0;*origen;origen++,i++) {
			if (i==indice) {
				*destino++='~';
				*destino++='^';
			}

			*destino++=*origen;
	}

	*destino=0;

	//copiar a cadena original
	strcpy(origen_orig,cadena_temporal);
}

//#define PIANO_GRAPHIC_BASE_X 9
#define PIANO_GRAPHIC_BASE_X (menu_center_x()-7)

int piano_graphic_base_y=0;

#define PIANO_ZOOM_X ( menu_char_width>=7 ? 3 : 2 )
#define PIANO_ZOOM_Y 3

#define AY_PIANO_ANCHO_VENTANA ( menu_char_width==8 || menu_char_width==6 ? 14 : 15 )

z80_bit menu_ay_piano_drawing_wavepiano={0};

//Escala alto en vertical teclado piano segun si ay chip>2, para que el teclado sea mas pequeñito
int scale_y_chip(int y)
{
	if (ay_retorna_numero_chips()<3) return y;

	//Si venimos de un Wave Piano, no hay que hacerlo pequeño , aunque tengamos 3 chips de audio, a ese menu no le tiene que afectar
	if (menu_ay_piano_drawing_wavepiano.v) return y;

	//Casos:
	//3,4,7,8
	if (y==3) y=1;
	else if (y==4) y=2;
	else if (y==7) y=5;
	else if (y==8) y=6;

	//temp
	return y;
}




void menu_ay_pianokeyboard_draw_graphical_piano_draw_pixel_zoom(zxvision_window *ventana,int x,int y,int color)
{
	//#define PIANO_ZOOM 3

	int offsetx=12;
	int offsety=scale_y_chip(8)+0;

	x=offsetx+x*PIANO_ZOOM_X;
	y=offsety+y*PIANO_ZOOM_Y;

	int xorig=x;
	int zx=0;
	int zy=0;

	for (zy=0;zy<PIANO_ZOOM_Y;zy++) {
		x=xorig;
		for (zx=0;zx<PIANO_ZOOM_X;zx++) {
			//No deberia ser null , pero por si acaso
			if (zxvision_current_window!=NULL) zxvision_putpixel(ventana,x,y,color);

			x++;

		}
		y++;
	}

}



//Basandome en coordenadas basicas sin zoom
void menu_ay_pianokeyboard_draw_graphical_piano_draw_line(zxvision_window *ventana,int x, int y, int stepx, int stepy, int length, int color)
{

	for (;length>0;length--) {
			menu_ay_pianokeyboard_draw_graphical_piano_draw_pixel_zoom(ventana,x,y,color);
			x +=stepx;
			y +=stepy;
	}

}

void menu_ay_piano_graph_dibujar_negra(zxvision_window *ventana,int x, int y,int color)
{
 int alto=4;

	for (alto=0;alto<4;alto++) {
		menu_ay_pianokeyboard_draw_graphical_piano_draw_line(ventana,x, y, +1, 0, 3, color);
		y++;
	}
}


//Como C, F
void menu_ay_piano_graph_dibujar_blanca_izquierda(zxvision_window *ventana,int x, int y,int color)
{
	menu_ay_pianokeyboard_draw_graphical_piano_draw_line(ventana,x, y, 0, +1, scale_y_chip(7), color);
	menu_ay_pianokeyboard_draw_graphical_piano_draw_line(ventana,x+1, y, 0, +1, scale_y_chip(7), color);
	menu_ay_pianokeyboard_draw_graphical_piano_draw_line(ventana,x+2, y+4, 0, +1, scale_y_chip(3), color);
}

//Como D, G, A
void menu_ay_piano_graph_dibujar_blanca_media(zxvision_window *ventana,int x, int y,int color)
{

	menu_ay_pianokeyboard_draw_graphical_piano_draw_line(ventana,x, y+4, 0, +1, scale_y_chip(3), color);
	menu_ay_pianokeyboard_draw_graphical_piano_draw_line(ventana,x+1, y, 0, +1, scale_y_chip(7), color);
	menu_ay_pianokeyboard_draw_graphical_piano_draw_line(ventana,x+2, y+4, 0, +1, scale_y_chip(3), color);
}


//Como E, B
void menu_ay_piano_graph_dibujar_blanca_derecha(zxvision_window *ventana,int x, int y,int color)
{
	menu_ay_pianokeyboard_draw_graphical_piano_draw_line(ventana,x, y+4, 0, +1, scale_y_chip(3), color);
	menu_ay_pianokeyboard_draw_graphical_piano_draw_line(ventana,x+1, y, 0, +1, scale_y_chip(7), color);
	menu_ay_pianokeyboard_draw_graphical_piano_draw_line(ventana,x+2, y, 0, +1, scale_y_chip(7), color);
}

void menu_ay_pianokeyboard_draw_graphical_piano(zxvision_window *ventana,int linea GCC_UNUSED,int canal,char *note)
{
	/*
	Teclado:
	0123456789012345678901234567890

	xxxxxxxxxxxxxxxxxxxxxxxxxxxxx         0
	x  xxx xxx  x  xxx xxx xxx  x         1
	x  xxx xxx  x  xxx xxx xxx  x         2
	x  xxx xxx  x  xxx xxx xxx  x         3
	x  xxx xxx  x  xxx xxx xxx  x         4
	x   x   x   x   x   x   x   x         5
	x   x   x   x   x   x   x   x         6
	x   x   x   x   x   x   x   x         7

	0123456789012345678901234567890

    C   D   E   F   G   A   B
Altura, para 2 chips de sonido (6 canales), tenemos maximo 192/6=32
32 de alto maximo, podemos hacer zoom x3 del esquema basico, por tanto tendriamos 8x3x6=144 de alto con 2 chips de sonido


	*/

	//scr_putpixel_zoom(x,y,ESTILO_GUI_TINTA_NORMAL);

	int ybase=0; //TODO: depende de linea de entrada

	//printf ("linea: %d\n",linea);

	//temp
	ybase +=scale_y_chip(8)*canal;

	//Recuadro en blanco
	int x,y;
	for (x=0;x<29;x++) {
		for (y=ybase;y<ybase+scale_y_chip(8);y++) {
			menu_ay_pianokeyboard_draw_graphical_piano_draw_pixel_zoom(ventana,x,y,7);
		}
	}

	//Linea superior
	menu_ay_pianokeyboard_draw_graphical_piano_draw_line(ventana,0, ybase+0, +1, 0, 29, 0);

	//Linea vertical izquierda
	menu_ay_pianokeyboard_draw_graphical_piano_draw_line(ventana,0, ybase+0, 0, +1, scale_y_chip(8), 0);

	//Linea vertical derecha
	menu_ay_pianokeyboard_draw_graphical_piano_draw_line(ventana,28, ybase+0, 0, +1, scale_y_chip(8), 0);

	//6 separaciones verticales pequeñas
	int i;
	x=4;
	for (i=0;i<6;i++) {
		menu_ay_pianokeyboard_draw_graphical_piano_draw_line(ventana,x, ybase+5, 0, +1, scale_y_chip(3), 0);
		x+=4;
	}

	//Linea vertical central
	menu_ay_pianokeyboard_draw_graphical_piano_draw_line(ventana,12, ybase+0, 0, +1, scale_y_chip(8), 0);

	//Y ahora las 5 negras
	x=3;
	for (i=0;i<5;i++) {
		menu_ay_piano_graph_dibujar_negra(ventana,x,ybase+1,0);
		/*
		for (y=1;y<=4;y++) {
			menu_ay_pianokeyboard_draw_graphical_piano_draw_line(x, y, +1, 0, 3, 0);
		}
		*/

		x+=4;
		if (i==1) x+=4;  //Saltar posicion donde iria la "tercera" negra
	}


	//Dibujar la linea inferior. Realmente la linea inferior es siempre la linea superior del siguiente canal, excepto en el ultimo canal
	menu_ay_pianokeyboard_draw_graphical_piano_draw_line(ventana,0, ybase+scale_y_chip(8), +1, 0, 29, 0);

	//Y ahora destacar la que se pulsa
	char letra_nota=note[0];
	int es_negra=0;
	if (note[1]=='#') es_negra=1;

	if (es_negra) {

		//determinar posicion x
		switch (letra_nota)
		{
			case 'C':
				x=3;
			break;

			case 'D':
				x=7;
			break;

			case 'F':
				x=15;
			break;

			case 'G':
				x=19;
			break;

			case 'A':
				x=23;
			break;

			default:
				//por si acaso
				x=-1;
			break;
		}
		if (x!=-1) menu_ay_piano_graph_dibujar_negra(ventana,x,ybase+1,1); //Color 1 para probar
	}

	else {
		//blancas
		switch (letra_nota)
		{
			case 'C':
			 menu_ay_piano_graph_dibujar_blanca_izquierda(ventana,1, ybase+1,1);
			break;

			case 'D':
			//Como D, G, A
			 menu_ay_piano_graph_dibujar_blanca_media(ventana,5, ybase+1,1);
			break;

			case 'E':
				menu_ay_piano_graph_dibujar_blanca_derecha(ventana,9, ybase+1,1);
			break;

			case 'F':
			 menu_ay_piano_graph_dibujar_blanca_izquierda(ventana,13, ybase+1,1);
			break;

			case 'G':
			//Como D, G, A
			 menu_ay_piano_graph_dibujar_blanca_media(ventana,17, ybase+1,1);
			break;

			case 'A':
			//Como D, G, A
			 menu_ay_piano_graph_dibujar_blanca_media(ventana,21, ybase+1,1);
			break;

			case 'B':
				menu_ay_piano_graph_dibujar_blanca_derecha(ventana,25, ybase+1,1);
			break;
		}

	}


}

void menu_ay_pianokeyboard_draw_text_piano(zxvision_window *w,int linea,int canal GCC_UNUSED,char *note)
{

	//Forzar a mostrar atajos
	z80_bit antes_menu_writing_inverse_color;
	antes_menu_writing_inverse_color.v=menu_writing_inverse_color.v;

	menu_writing_inverse_color.v=1;

	char linea_negras[40];
	char linea_blancas[40];
												//012345678901
	sprintf (linea_negras, " # #  # # #");
	sprintf (linea_blancas,"C D EF G A B");

	if (note==NULL || note[0]==0) {
	}

	else {
		//Marcar tecla piano pulsada con ~~
		//Interpretar Nota viene como C#4 o C4 por ejemplo
		char letra_nota=note[0];
		int es_negra=0;
		if (note[1]=='#') es_negra=1;

		//TODO: mostramos la octava?

		//Linea negras
		if (es_negra) {
				int indice_negra_marcar=0;
				switch (letra_nota)
				{
					case 'C':
						indice_negra_marcar=1;
					break;

					case 'D':
						indice_negra_marcar=3;
					break;

					case 'F':
						indice_negra_marcar=6;
					break;

					case 'G':
						indice_negra_marcar=8;
					break;

					case 'A':
						indice_negra_marcar=10;
					break;
				}

				//Reconstruimos la cadena introduciendo ~~donde indique el indice
				menu_ay_pianokeyboard_insert_inverse(linea_negras,indice_negra_marcar);
		}

		//Linea blancas
		else {
			int indice_blanca_marcar=0;
			//												//012345678901
			//	sprintf (linea_negras, " # #  # # #");
			//	sprintf (linea_blancas,"C D EF G A B");
			switch (letra_nota)
			{
			  case 'C':
			    indice_blanca_marcar=0;
			  break;

			  case 'D':
			    indice_blanca_marcar=2;
			  break;

			  case 'E':
			    indice_blanca_marcar=4;
			  break;

			  case 'F':
			    indice_blanca_marcar=5;
			  break;

			  case 'G':
			    indice_blanca_marcar=7;
			  break;

			  case 'A':
			    indice_blanca_marcar=9;
			  break;

			  case 'B':
			    indice_blanca_marcar=11;
			  break;
			}

			//Reconstruimos la cadena introduciendo ~~donde indique el indice
			menu_ay_pianokeyboard_insert_inverse(linea_blancas,indice_blanca_marcar);
		}
	}

	//menu_escribe_linea_opcion(linea++,-1,1,linea_negras);
	//menu_escribe_linea_opcion(linea++,-1,1,linea_blancas);

	zxvision_print_string_defaults(w,1,linea++,linea_negras);
	zxvision_print_string_defaults(w,1,linea++,linea_blancas);


	menu_writing_inverse_color.v=antes_menu_writing_inverse_color.v;

}





//Dice si se muestra piano grafico o de texto.
//Si es un driver de solo texto, mostrar texto
//Si es un driver grafico y setting dice que lo mostremos en texto, mostrar texto
//Si nada de lo demas, mostrar grafico
int si_mostrar_ay_piano_grafico(void)
{
	if (!si_complete_video_driver()) return 0;

	if (!setting_mostrar_ay_piano_grafico.v) return 0;

	return 1;

}

void menu_ay_pianokeyboard_draw_piano(zxvision_window *w,int linea,int canal,char *note)
{
	if (!si_mostrar_ay_piano_grafico()) {
		menu_ay_pianokeyboard_draw_text_piano(w,linea,canal,note);
	}
	else {
		menu_ay_pianokeyboard_draw_graphical_piano(w,linea,canal,note);
	}
}


zxvision_window *menu_ay_pianokeyboard_overlay_window;

//int temp_zzzz;

void menu_ay_pianokeyboard_overlay(void)
{


    if (!zxvision_drawing_in_background) normal_overlay_texto_menu();

	//workaround_pentagon_clear_putpixel_cache();

	menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech, en el caso que se habilite piano de tipo texto

	//char volumen[16],textovolumen[32],textotono[32];

    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_ay_pianokeyboard_overlay_window->is_minimized) return;

    //printf ("overlay de menu_ay_pianokeyboard_overlay %d\n",temp_zzzz++);


    int total_chips=audio_get_total_chips();
	//Max 3 ay chips
	if (total_chips>3) total_chips=3;    



	//if (total_chips>2) total_chips=2;

	int chip;

	int linea=1;

	int canal=0;

	for (chip=0;chip<total_chips;chip++) {


			int freq_a,freq_b,freq_c;


            freq_a=audio_retorna_frecuencia_canal(0,chip);
            freq_b=audio_retorna_frecuencia_canal(1,chip);
            freq_c=audio_retorna_frecuencia_canal(2,chip);

			char nota_a[4];
			sprintf(nota_a,"%s",get_note_name(freq_a) );

			char nota_b[4];
			sprintf(nota_b,"%s",get_note_name(freq_b) );

			char nota_c[4];
			sprintf(nota_c,"%s",get_note_name(freq_c) );

			//Si canales no suenan como tono, o volumen 0 meter cadena vacia en nota
            /*
			if (sn_chip_present.v) {
				if ((sn_chip_registers[6] & 15)==15) nota_a[0]=0;
				if ((sn_chip_registers[7] & 15)==15) nota_b[0]=0;
				if ((sn_chip_registers[8] & 15)==15) nota_c[0]=0;				
			}

			else if (i8049_chip_present) {
                if (!ql_audio_playing) {
                    nota_a[0]=0;
                }

                //Los otros dos canales, nada
                nota_b[0]=0;
                nota_c[0]=0;                               
			}            

			else {
				if (ay_3_8912_registros[chip][7]&1 || ay_3_8912_registros[chip][8]==0) nota_a[0]=0;
				if (ay_3_8912_registros[chip][7]&2 || ay_3_8912_registros[chip][9]==0) nota_b[0]=0;
				if (ay_3_8912_registros[chip][7]&4 || ay_3_8912_registros[chip][10]==0) nota_c[0]=0;
			}
            */

            if (!audio_si_canal_tono(chip,0)) {
                nota_a[0]=0;
                //printf("audio piano canal 0 silencio\n");
            }
            if (!audio_si_canal_tono(chip,1)) {
                nota_b[0]=0;
                //printf("audio piano canal 1 silencio\n");
            }
            if (!audio_si_canal_tono(chip,2)) {
                nota_c[0]=0;
                //printf("audio piano canal 2 silencio\n");
            }

			int incremento_linea=3;

			if (!si_mostrar_ay_piano_grafico()) {
				//Dibujar ay piano con texto. Comprimir el texto (quitar linea de entre medio) cuando hay 3 chips
				if (total_chips>2) incremento_linea=2;
			}


			menu_ay_pianokeyboard_draw_piano(menu_ay_pianokeyboard_overlay_window,linea,canal,nota_a);
			linea+=incremento_linea;
			canal++;

			menu_ay_pianokeyboard_draw_piano(menu_ay_pianokeyboard_overlay_window,linea,canal,nota_b);
			linea+=incremento_linea;
			canal++;

			menu_ay_pianokeyboard_draw_piano(menu_ay_pianokeyboard_overlay_window,linea,canal,nota_c);
			linea+=incremento_linea;
			canal++;

	}

	zxvision_draw_window_contents(menu_ay_pianokeyboard_overlay_window); 

}


zxvision_window zxvision_window_ay_piano;


void menu_ay_pianokeyboard(MENU_ITEM_PARAMETERS)
{
        menu_espera_no_tecla();

		if (!menu_multitarea) {
			menu_warn_message("This window needs multitask enabled");
			return;
		}		

		zxvision_window *ventana;
		ventana=&zxvision_window_ay_piano;		

    //IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
    //si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
    //la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
	zxvision_delete_window_if_exists(ventana);


		int xventana,yventana,ancho_ventana,alto_ventana;



		int  total_chips=ay_retorna_numero_chips();
		//Max 3 ay chips
		if (total_chips>3) total_chips=3;

		char *titulo_ventana="Audio Chip Piano";

        int is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;


		if (!util_find_window_geometry("aypiano",&xventana,&yventana,&ancho_ventana,&alto_ventana,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {

				if (!si_mostrar_ay_piano_grafico()) {

					ancho_ventana=14;

					if (total_chips==1) {
						xventana=9;
						yventana=7;					
					}
          			else if (total_chips==2) {
						xventana=9;
						yventana=2;						  					  
					}

					else {
						xventana=9;
						yventana=1;					
					}

				}

				else {
					//Dibujar ay piano con grafico. Ajustar segun ancho de caracter (de ahi que use AY_PIANO_ANCHO_VENTANA en vez de valor fijo 14)
					if (total_chips==1) {
						xventana=PIANO_GRAPHIC_BASE_X;
						yventana=piano_graphic_base_y;
						ancho_ventana=AY_PIANO_ANCHO_VENTANA;					
					}
					else if (total_chips==2) {
						xventana=PIANO_GRAPHIC_BASE_X;
						yventana=piano_graphic_base_y;
						ancho_ventana=AY_PIANO_ANCHO_VENTANA;							
					}

					else {
						xventana=PIANO_GRAPHIC_BASE_X;
						yventana=piano_graphic_base_y;
						ancho_ventana=AY_PIANO_ANCHO_VENTANA;						
					}
				}



				//El alto ventana lo calculamos segun el numero de chips
				if (!si_mostrar_ay_piano_grafico()) {

					if (total_chips==1) {			
						alto_ventana=11;
					}
          			else if (total_chips==2) {
						alto_ventana=20;						  						  
					}

					else {
						alto_ventana=22;						
					}

				}

				else {
					//Dibujar ay piano con grafico. Ajustar segun ancho de caracter (de ahi que use AY_PIANO_ANCHO_VENTANA en vez de valor fijo 14)
					if (total_chips==1) {
						piano_graphic_base_y=5;						
						alto_ventana=13;						
					}
					else if (total_chips==2) {
						piano_graphic_base_y=1;
						alto_ventana=22;							
					}

					else {
						piano_graphic_base_y=0;						
						alto_ventana=24;							
					}
				}


			int ancho_titulo=menu_da_ancho_titulo(titulo_ventana);

			//Para que se lea el titulo de la ventana en tamaño por defecto
			
			if (ancho_ventana<ancho_titulo) ancho_ventana=ancho_titulo;


			}

		


		
		//int ancho_titulo=menu_da_ancho_titulo(titulo_ventana);

		//Para que siempre se lea el titulo de la ventana
		//No alteramos el ancho, que sea el que tenga por geometria
		//if (ancho_ventana<ancho_titulo) ancho_ventana=ancho_titulo;



		//zxvision_new_window(ventana,xventana,yventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,titulo_ventana);

        zxvision_new_window_gn_cim(ventana,xventana,yventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,titulo_ventana,"aypiano",
            is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);

		ventana->can_be_backgrounded=1;	
		//indicar nombre del grabado de geometria
		//strcpy(ventana->geometry_name,"aypiano");
        //restaurar estado minimizado de ventana
        //ventana->is_minimized=is_minimized;

		zxvision_draw_window(ventana);						

        //z80_byte acumulado;

        menu_ay_pianokeyboard_overlay_window=ventana;

/*
		//Metemos todo el contenido de la ventana con caracter transparente, para que no haya parpadeo
		//en caso de drivers xwindows por ejemplo, pues continuamente redibuja el texto (espacios) y encima el overlay
		//Al meter caracter transparente, el normal_overlay lo ignora y no dibuja ese caracter
		int x,y;
		for (y=0;y<alto_ventana-2;y++) {
			for (x=1;x<ancho_ventana-1;x++) {
				zxvision_print_string_defaults(ventana,x,y,"\xff");
			}
		}
*/

        //Cambiamos funcion overlay de texto de menu
        //Se establece a la de funcion de piano + texto
        set_menu_overlay_function(menu_ay_pianokeyboard_overlay);





        int valor_contador_segundo_anterior;

        valor_contador_segundo_anterior=contador_segundo;


       //Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
       //Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
       if (zxvision_currently_restoring_windows_on_start) {
               //printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
               return;
       }



	    z80_byte tecla=0;

        do {

                //esto hara ejecutar esto 2 veces por segundo
                //if ( (contador_segundo%500) == 0 || menu_multitarea==0) {
                if ( ((contador_segundo%500) == 0 && valor_contador_segundo_anterior!=contador_segundo) || menu_multitarea==0) {
										valor_contador_segundo_anterior=contador_segundo;

										//printf ("Refrescando. contador_segundo=%d\n",contador_segundo);
				    if (menu_multitarea==0) menu_refresca_pantalla();


                }


				menu_cpu_core_loop();
                //acumulado=menu_da_todas_teclas();

                //si no hay multitarea, esperar tecla y salir
                if (menu_multitarea==0) {
                        menu_espera_tecla();

                        //acumulado=0;
                }

				//tecla=menu_get_pressed_key();
				tecla=zxvision_read_keyboard();

				//con enter no salimos. TODO: esto se hace porque el mouse esta enviando enter al pulsar boton izquierdo, y lo hace tambien al hacer dragging
				//lo ideal seria que mouse no enviase enter al pulsar boton izquierdo y entonces podemos hacer que se salga tambien con enter
				if (tecla==13) tecla=0;

        //} while (  (acumulado & MENU_PUERTO_TECLADO_NINGUNA) ==MENU_PUERTO_TECLADO_NINGUNA && tecla==0)  ;

		} while (tecla!=2 && tecla!=3);				



	//Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
	zxvision_set_window_overlay_from_current(ventana);

    //restauramos modo normal de texto de menu
    set_menu_overlay_function(normal_overlay_texto_menu);


    cls_menu_overlay();

    util_add_window_geometry_compact(ventana);

	if (tecla==3) {
        zxvision_message_put_window_background();
	}

	else {
		
		zxvision_destroy_window(ventana);			
	}


	//workaround_pentagon_clear_putpixel_cache();	

	menu_espera_no_tecla();

	/* Nota:
	Creo que este es de los pocos casos en que llamamos a menu_espera_no_tecla al salir, por dos razones:

	1) si no se hiciera, cuando hay text-to-speech+also send menu, la tecla ESC se suele escalar hacia abajo, probablemente porque activa
	variable menu_speech_tecla_pulsada=1
	Probablemente habria que llamar siempre a menu_espera_no_tecla(); al finalizar ventanas que no estan gestionadas por menu_dibuja_menu

	
	2) si no se hiciera, saldria con menu_speech_tecla_pulsada=1, y la tecla pulsada utilizada para salir de esta ventana (ESC),
	acaba pasando al menu anterior, cerrando el menu directamente. Esto solo pasa si no hay text-to-speech+also send menu
	No se muy bien porque solo sucede en este caso, quiza es porque estamos mostrando texto directamente en la funcion overlay y 
	de manera muy rapida. Esto es lo mismo que en el menu de Wave Piano
	

	*/			

}


zxvision_window *menu_beeper_pianokeyboard_overlay_window;


void menu_beeper_pianokeyboard_overlay(void)
{
    if (!zxvision_drawing_in_background) normal_overlay_texto_menu();

	//workaround_pentagon_clear_putpixel_cache();

	menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech

	//char volumen[16],textovolumen[32],textotono[32];

    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_beeper_pianokeyboard_overlay_window->is_minimized) return;   

    //printf("Overlay wave piano %d\n",contador_segundo);


	int linea=1;

	int canal=0;

    audiobuffer_stats audiostats;
    audio_get_audiobuffer_stats(&audiostats);


    int frecuencia=audiostats.frecuencia;

    //printf ("frecuencia %d\n",frecuencia);



    int freq_a=frecuencia;


    char nota_a[4];
    sprintf(nota_a,"%s",get_note_name(freq_a) );

    //Si no hay sonido, suele dar frecuencia 5 o menos
    if (frecuencia<=5) nota_a[0]=0;

    //Indicar que no hay que reducir el tamaño del piano segun el numero de chips (esto va bien en ay piano, pero no aqui)
    menu_ay_piano_drawing_wavepiano.v=1;
    menu_ay_pianokeyboard_draw_piano(menu_beeper_pianokeyboard_overlay_window,linea,canal,nota_a);
    //Restauramos comportamiento por defecto
    menu_ay_piano_drawing_wavepiano.v=0;

    //workaround_pentagon_clear_putpixel_cache();

    char buffer_texto[40];
    
    if (nota_a[0]!=0) {
        sprintf (buffer_texto,"%d Hz (%s) ",frecuencia,nota_a);
    }

    else strcpy (buffer_texto,"             ");

        
    
    //menu_escribe_linea_opcion(5,-1,1,buffer_texto);
    zxvision_print_string_defaults(menu_beeper_pianokeyboard_overlay_window,1,5,buffer_texto);
    //printf ("menu_speech_tecla_pulsada despues de enviar texto: %d\n",menu_speech_tecla_pulsada);


	zxvision_draw_window_contents(menu_beeper_pianokeyboard_overlay_window); 

}



zxvision_window zxvision_menu_beeper_pianokeyboard;

void menu_beeper_pianokeyboard(MENU_ITEM_PARAMETERS)
{
	menu_espera_no_tecla();



	if (!menu_multitarea) {
		menu_warn_message("This window needs multitask enabled");
		return;
	}

	zxvision_window *ventana;	
	ventana=&zxvision_menu_beeper_pianokeyboard;

    //IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
    //si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
    //la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
	zxvision_delete_window_if_exists(ventana);



	//Como si fuera 1 solo chip


	int xventana,yventana,ancho_ventana,alto_ventana,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;
	char *titulo_ventana="Wave Piano";
	if (!util_find_window_geometry("wavepiano",&xventana,&yventana,&ancho_ventana,&alto_ventana,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
        if (!si_mostrar_ay_piano_grafico()) {

            xventana=7;
            yventana=7;
            ancho_ventana=19;
            alto_ventana=11;

        }

        else {
            //Dibujar ay piano con grafico. Ajustar segun ancho de caracter (de ahi que use AY_PIANO_ANCHO_VENTANA en vez de valor fijo 14)
            xventana=PIANO_GRAPHIC_BASE_X-2;
            yventana=piano_graphic_base_y;
            ancho_ventana=AY_PIANO_ANCHO_VENTANA;
            alto_ventana=8;

        }

        ancho_antes_minimize=ancho_ventana;
        alto_antes_minimize=alto_ventana;


		int ancho_titulo=menu_da_ancho_titulo(titulo_ventana);
		
		//Para que se lea el titulo de la ventana cuando tamaño por defecto
		if (ancho_ventana<ancho_titulo) ancho_ventana=ancho_titulo;					



	}



	
	//int ancho_titulo=menu_da_ancho_titulo(titulo_ventana);
		
	//Para que siempre se lea el titulo de la ventana
	//No alteramos el ancho, que sea el que tenga por geometria
	//if (ancho_ventana<ancho_titulo) ancho_ventana=ancho_titulo;	

    zxvision_new_window_gn_cim(ventana,xventana,yventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,titulo_ventana,
                "wavepiano",is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);		


	//zxvision_new_window(ventana,xventana,yventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,titulo_ventana);
	ventana->can_be_backgrounded=1;
	//indicar nombre del grabado de geometria
	//strcpy(ventana->geometry_name,"wavepiano");
    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;    

	zxvision_draw_window(ventana);						



	//Cambiamos funcion overlay de texto de menu
	//Se establece a la de funcion de piano + texto
	set_menu_overlay_function(menu_beeper_pianokeyboard_overlay);

	menu_beeper_pianokeyboard_overlay_window=ventana; 


	int valor_contador_segundo_anterior;

	valor_contador_segundo_anterior=contador_segundo;


    //Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
    //Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
    if (zxvision_currently_restoring_windows_on_start) {
        //printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
        return;
    }


	z80_byte tecla=0;

    do {

        //esto hara ejecutar esto 2 veces por segundo
        //if ( (contador_segundo%500) == 0 || menu_multitarea==0) {
		if ( ((contador_segundo%500) == 0 && valor_contador_segundo_anterior!=contador_segundo) || menu_multitarea==0) {
            valor_contador_segundo_anterior=contador_segundo;

            //printf ("Refrescando. contador_segundo=%d\n",contador_segundo);
			if (menu_multitarea==0) menu_refresca_pantalla();

		}

		menu_cpu_core_loop();

		//si no hay multitarea, esperar tecla y salir
		if (menu_multitarea==0) {
            menu_espera_tecla();
		}

		
		tecla=zxvision_read_keyboard();

		//con enter no salimos. TODO: esto se hace porque el mouse esta enviando enter al pulsar boton izquierdo, y lo hace tambien al hacer dragging
		//lo ideal seria que mouse no enviase enter al pulsar boton izquierdo y entonces podemos hacer que se salga tambien con enter
		if (tecla==13) tecla=0;


	} while (tecla!=2 && tecla!=3);										

      
	//Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
	zxvision_set_window_overlay_from_current(ventana);

	//restauramos modo normal de texto de menu
	set_menu_overlay_function(normal_overlay_texto_menu);


	cls_menu_overlay();

	util_add_window_geometry_compact(ventana);		


	if (tecla==3) {
		zxvision_message_put_window_background();
	}

	else {
	
		zxvision_destroy_window(ventana);

	}

	menu_espera_no_tecla();


	/* Nota:
	Creo que este es de los pocos casos en que llamamos a menu_espera_no_tecla al salir,
	si no se hiciera, saldria con menu_speech_tecla_pulsada=1, y la tecla pulsada utilizada para salir de esta ventana (ESC),
	acaba pasando al menu anterior, cerrando el menu directamente. Esto solo pasa si no hay text-to-speech+also send menu
	No se muy bien porque solo sucede en este caso, quiza es porque estamos mostrando texto directamente en la funcion overlay y 
	de manera muy rapida
	*/	

}


void menu_debug_msx_memory_info_slot_segment(MENU_ITEM_PARAMETERS)
{
	//Le indicamos el valor de slot y segmento, codificandolo en valor hexadecimal: slot*16+segment

	int slot=(valor_opcion>>4) & 0xF;
	int segment=valor_opcion & 0xF;

	int tipo=msx_memory_slots[slot][segment];

	int inicio_bloque=segment*16384;
	int fin_bloque=((segment+1)*16384)-1;

	if (MACHINE_IS_SVI) {
		inicio_bloque=segment*32768;
		fin_bloque=((segment+1)*32768)-1;	
	}
	else {
	inicio_bloque=segment*16384;
	fin_bloque=((segment+1)*16384)-1;	
	}


	


	if (MACHINE_IS_SVI) {
		char buffer_mem_type[32];
		char long_buffer_mem_type[32];
		svi_get_string_memory_slot(buffer_mem_type,long_buffer_mem_type,slot,segment);

		menu_generic_message_format("Block info","Slot: %d Segment: %d Type: %s Uses: %04XH-%04XH"
			,slot,segment,long_buffer_mem_type,inicio_bloque,fin_bloque);		
	}
		
	else {
		//MSX
	
		menu_generic_message_format("Block info","Slot: %d Segment: %d Type: %s Uses: %04XH-%04XH"
			,slot,segment,msx_get_string_memory_type(tipo),inicio_bloque,fin_bloque);
	}


}


void menu_debug_msx_svi_memory_info(MENU_ITEM_PARAMETERS)
{

	int total_segmentos=4-1;

	if (MACHINE_IS_SVI) total_segmentos=2-1;	

	int ancho_ventana=32;
	int alto_ventana=7+(total_segmentos+1)*2;


	int xventana=menu_center_x()-ancho_ventana/2;
	int yventana=menu_center_y()-alto_ventana/2;

	zxvision_window ventana;

	zxvision_new_window(&ventana,xventana,yventana,ancho_ventana,alto_ventana,
                                                        ancho_ventana-1,alto_ventana-2,"Memory Info");

	//Dado que es una variable local, siempre podemos usar este nombre array_menu_common
	menu_item *array_menu_common;
	menu_item item_seleccionado;
	int retorno_menu;

	int comun_opcion_seleccionada=0;


	//Donde van los bloques

	int inicio_bloque_x=8;
	int inicio_bloque_y=2;
	int ancho_bloque=6;

	int linea=inicio_bloque_y;
	
	if (!MACHINE_IS_SVI) {
	zxvision_print_string_defaults(&ventana,1,linea,"C000H");
	linea+=2;
	}

	zxvision_print_string_defaults(&ventana,1,linea,"8000H");
	linea+=2;

	if (!MACHINE_IS_SVI) {
	zxvision_print_string_defaults(&ventana,1,linea,"4000H");
	linea+=2;
	}

	zxvision_print_string_defaults(&ventana,1,linea,"0000H");
	linea+=2;

	do {


		
		menu_add_item_menu_inicial_format(&array_menu_common,MENU_OPCION_NORMAL,NULL,NULL,"       Slot0 Slot1 Slot2 Slot3");
		menu_add_item_menu_tabulado(array_menu_common,1,0);

		int slot, segment;

		////slots asignados, y sus 4 segmentos
//tipos: rom, ram, vacio
//int msx_memory_slots[4][4];
/*
#define MSX_SLOT_MEMORY_TYPE_ROM 0
#define MSX_SLOT_MEMORY_TYPE_RAM 1
#define MSX_SLOT_MEMORY_TYPE_EMPTY 2
*/

		//SVI:
		//Siempre estan los slots fijos en svi
/*
  FFFF      BANK 02 RAM     |      BANK 12 CARTRIDGE ROM    |   BANK 22 RAM     |       BANK 32 RAM
  8000


  7FFF      BANK 01 ROM     |      BANK 11 CARTRIDGE ROM    |   BANK 21 RAM     |       BANK 31 RAM
  0000
*/
		


		for (segment=total_segmentos;segment>=0;segment--) {
			for (slot=0;slot<4;slot++) {
			

				char buffer_mem_type[32];


				if (MACHINE_IS_SVI) {
					svi_get_string_memory_slot(buffer_mem_type,NULL,slot,segment);
				}
				else {
					//MSX
				
				int tipo=msx_memory_slots[slot][segment];
		
				strcpy (buffer_mem_type,msx_get_string_memory_type(tipo));
			
				
				}

				menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_debug_msx_memory_info_slot_segment,NULL,buffer_mem_type);

				int coordenada_y;


				coordenada_y=inicio_bloque_y+(total_segmentos-segment)*2;
				

				menu_add_item_menu_tabulado(array_menu_common,inicio_bloque_x+slot*ancho_bloque,coordenada_y);

				//Le indicamos el valor de slot y segmento, codificandolo en valor hexadecimal: slot*16+segment

				int valor_opcion=slot*16+segment;
				menu_add_item_menu_valor_opcion(array_menu_common,valor_opcion);
			}
		}
		



		//if (!total_ventanas) menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,NULL,NULL,"(Empty)");

		//menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

		menu_add_ESC_item(array_menu_common);
		menu_add_item_menu_tabulado(array_menu_common,1,alto_ventana-4);

		retorno_menu=menu_dibuja_menu(&comun_opcion_seleccionada,&item_seleccionado,array_menu_common,"Window management");

			
			if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
					//llamamos por valor de funcion
					if (item_seleccionado.menu_funcion!=NULL) {
							//printf ("actuamos por funcion\n");
							item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
							
					}
			}

    } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);

    //En caso de menus tabulados, suele ser necesario esto. Si no, la ventana se quedaria visible
    cls_menu_overlay();

                                //En caso de menus tabulados, es responsabilidad de este de liberar ventana
                zxvision_destroy_window(&ventana);	

}


void menu_debug_tsconf_tbblue_msx_cpc_debug_borders(MENU_ITEM_PARAMETERS)
{
	cpc_debug_borders.v ^=1;
}   


void menu_debug_sprite_mangement_disable_change(MENU_ITEM_PARAMETERS)
{
    debug_tbblue_sprite_visibility[valor_opcion] ^=1;
}


void menu_debug_sprite_mangement_disable(MENU_ITEM_PARAMETERS)
{



	int ancho_ventana=34;
	int alto_ventana=24;

    //Nota: esta ventana es de 34 de ancho, para dar margen izquierda/derecha,
    //pues los 4 indices por linea ya ocupan 8x4=32
    //por tanto con border disabled, zx desktop disabled y menu char width=8, la ventana no caberia entera, saldra cortada parte por la derecha
    //pero no es lo habitual, al menos habra el border activado (en el caso de tbblue, se fuerza siempre border)


	int xventana=menu_center_x()-ancho_ventana/2;
	int yventana=menu_center_y()-alto_ventana/2;

	zxvision_window ventana;


    int total_height=TBBLUE_MAX_SPRITES/4;

	zxvision_new_window(&ventana,xventana,yventana,ancho_ventana,alto_ventana,
                                                        ancho_ventana-1,total_height,"Sprite disable");

	//Dado que es una variable local, siempre podemos usar este nombre array_menu_common
	menu_item *array_menu_common;
	menu_item item_seleccionado;
	int retorno_menu;

	int comun_opcion_seleccionada=0;




	do {


		
        menu_add_item_menu_inicial(&array_menu_common,"",MENU_OPCION_UNASSIGNED,NULL,NULL);        

		int sprite;


		for (sprite=0;sprite<TBBLUE_MAX_SPRITES;sprite++) {
			



            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_debug_sprite_mangement_disable_change,NULL,
                "[%c] %3d",(debug_tbblue_sprite_visibility[sprite] ? 'X' : ' '),sprite);

            menu_add_item_menu_tabulado(array_menu_common,1+(sprite %4)*8,sprite/4);

            menu_add_item_menu_valor_opcion(array_menu_common,sprite);
			
		}
		



		//menu_add_ESC_item(array_menu_common);
		//menu_add_item_menu_tabulado(array_menu_common,1,alto_ventana-4);

		retorno_menu=menu_dibuja_menu(&comun_opcion_seleccionada,&item_seleccionado,array_menu_common,"Sprite disable");

			
			if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
					//llamamos por valor de funcion
					if (item_seleccionado.menu_funcion!=NULL) {
							//printf ("actuamos por funcion\n");
							item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
							
					}
			}

    } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);

    //En caso de menus tabulados, suele ser necesario esto. Si no, la ventana se quedaria visible
    cls_menu_overlay();

    //En caso de menus tabulados, es responsabilidad de este de liberar ventana
    zxvision_destroy_window(&ventana);	

}

void menu_debug_tsconf_tbblue_msx_copper(MENU_ITEM_PARAMETERS)
{
    tbblue_force_disable_cooper.v ^=1;
}


void menu_debug_tsconf_tbblue_msx(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_debug_tsconf_tbblue_msx;
        menu_item item_seleccionado;
	int retorno_menu;
        do {



		menu_add_item_menu_inicial_format(&array_menu_debug_tsconf_tbblue_msx,MENU_OPCION_NORMAL,menu_debug_tsconf_tbblue_msx_videoregisters,NULL,"Video ~~Info");
		menu_add_item_menu_shortcut(array_menu_debug_tsconf_tbblue_msx,'i');

        if (MACHINE_IS_CPC && rainbow_enabled.v) {
            menu_add_item_menu(array_menu_debug_tsconf_tbblue_msx,"",MENU_OPCION_SEPARADOR,NULL,NULL);

            menu_add_item_menu_format(array_menu_debug_tsconf_tbblue_msx,MENU_OPCION_NORMAL,menu_debug_tsconf_tbblue_msx_cpc_debug_borders,NULL,"[%c] Debug borders",
                (cpc_debug_borders.v==1 ? 'X' : ' ') );

        }


        if (!MACHINE_IS_CPC) {
		menu_add_item_menu_format(array_menu_debug_tsconf_tbblue_msx,MENU_OPCION_NORMAL,menu_tsconf_layer_settings,NULL,"Video ~~Layers");
		menu_add_item_menu_shortcut(array_menu_debug_tsconf_tbblue_msx,'l');
        }

        if (!MACHINE_IS_CPC) {
		menu_add_item_menu_format(array_menu_debug_tsconf_tbblue_msx,MENU_OPCION_NORMAL,menu_debug_tsconf_tbblue_msx_spritenav,NULL,"~~Sprite navigator");
		menu_add_item_menu_shortcut(array_menu_debug_tsconf_tbblue_msx,'s');
        }

        if (MACHINE_IS_TBBLUE) {
		    menu_add_item_menu_format(array_menu_debug_tsconf_tbblue_msx,MENU_OPCION_NORMAL,menu_debug_sprite_mangement_disable,NULL,"Sprite ~~disabling");
		    menu_add_item_menu_shortcut(array_menu_debug_tsconf_tbblue_msx,'d');            
        }

		if (MACHINE_IS_TSCONF || MACHINE_IS_TBBLUE || MACHINE_HAS_VDP_9918A) {
			menu_add_item_menu_format(array_menu_debug_tsconf_tbblue_msx,MENU_OPCION_NORMAL,menu_debug_tsconf_tbblue_msx_tilenav,NULL,"~~Tile navigator");
			menu_add_item_menu_shortcut(array_menu_debug_tsconf_tbblue_msx,'t');
		}

        if (MACHINE_IS_TBBLUE) {
            menu_add_item_menu(array_menu_debug_tsconf_tbblue_msx,"",MENU_OPCION_SEPARADOR,NULL,NULL);
            menu_add_item_menu_format(array_menu_debug_tsconf_tbblue_msx,MENU_OPCION_NORMAL,menu_debug_tsconf_tbblue_msx_copper,NULL,"[%c] Copper enabled",
                            (tbblue_force_disable_cooper.v ? ' ' : 'X' ));
        }

		if (MACHINE_IS_MSX || MACHINE_IS_SVI) {
			menu_add_item_menu_format(array_menu_debug_tsconf_tbblue_msx,MENU_OPCION_NORMAL,menu_debug_msx_svi_memory_info,NULL,"~~Memory Info");
			menu_add_item_menu_shortcut(array_menu_debug_tsconf_tbblue_msx,'m');		
		}

                menu_add_item_menu(array_menu_debug_tsconf_tbblue_msx,"",MENU_OPCION_SEPARADOR,NULL,NULL);
                //menu_add_item_menu(array_menu_debug_tsconf_tbblue_msx,"ESC Back",MENU_OPCION_NORMAL|MENU_OPCION_ESC,NULL,NULL);
		menu_add_ESC_item(array_menu_debug_tsconf_tbblue_msx);

		char titulo_ventana[33];

		//por defecto
		strcpy(titulo_ventana,"Debug TSConf");

		if (MACHINE_IS_TBBLUE)  strcpy(titulo_ventana,"Debug TBBlue");
		if (MACHINE_IS_MSX)     strcpy(titulo_ventana,"Debug MSX");
		if (MACHINE_IS_COLECO)  strcpy(titulo_ventana,"Debug Colecovision");
		if (MACHINE_IS_SG1000)  strcpy(titulo_ventana,"Debug SG1000");
        if (MACHINE_IS_SMS)  strcpy(titulo_ventana,"Debug Master System");
		if (MACHINE_IS_SVI)     strcpy(titulo_ventana,"Debug Spectravideo");
        if (MACHINE_IS_CPC)     strcpy(titulo_ventana,"Debug CPC");

        retorno_menu=menu_dibuja_menu(&debug_tsconf_opcion_seleccionada,&item_seleccionado,array_menu_debug_tsconf_tbblue_msx,titulo_ventana);

                

		if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
				
                        }
                }

	} while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);

}


z80_byte *help_keyboard_bmp_file_mem=NULL;

//Ultima maquina activa cuando se cargo el teclado. Si cambia maquina, cargar teclado correspondiente
int help_keyboard_last_current_machine=-1;

void menu_help_keyboard_load_bmp(void)
{
	
    //Cargar el archivo bmp
    /*
    Deben ser, idealmente: 540x201.  (puede ser otro tamaño)
    bmp. 256 colour (indexed).  grabar con no-codificación run lenght,  y no sobreescribir la información de espacio de colores
    */

    char nombrebmp[PATH_MAX];


    if (MACHINE_IS_CHLOE) strcpy(nombrebmp,"keyboard_chloe.bmp");
    else if (MACHINE_IS_COLECO) strcpy(nombrebmp,"keyboard_coleco.bmp");
    else if (MACHINE_IS_CPC) strcpy(nombrebmp,"keyboard_cpc.bmp");
    else if (MACHINE_IS_INVES) strcpy(nombrebmp,"keyboard_inves.bmp");
    else if (MACHINE_IS_ACE) strcpy(nombrebmp,"keyboard_ace.bmp");
    else if (MACHINE_IS_MICRODIGITAL_TK90X || MACHINE_IS_MICRODIGITAL_TK90X_SPA) strcpy(nombrebmp,"keyboard_tk90x.bmp");
    else if (MACHINE_IS_MICRODIGITAL_TK95) strcpy(nombrebmp,"keyboard_tk95.bmp");
    else if (MACHINE_IS_MK14) strcpy(nombrebmp,"keyboard_mk14.bmp");
    else if (MACHINE_IS_MSX) strcpy(nombrebmp,"keyboard_msx.bmp");
    else if (MACHINE_IS_PENTAGON) strcpy(nombrebmp,"keyboard_pentagon.bmp");
    else if (MACHINE_IS_QL) strcpy(nombrebmp,"keyboard_ql.bmp");
    else if (MACHINE_IS_SAM) strcpy(nombrebmp,"keyboard_sam.bmp");
    else if (MACHINE_IS_SG1000) strcpy(nombrebmp,"keyboard_sg1000.bmp");
    else if (MACHINE_IS_SMS) strcpy(nombrebmp,"keyboard_sms.bmp");
    else if (MACHINE_IS_SVI) strcpy(nombrebmp,"keyboard_svi.bmp");
    else if (MACHINE_IS_TBBLUE) strcpy(nombrebmp,"keyboard_next.bmp");
    else if (MACHINE_IS_TIMEX_TS2068) strcpy(nombrebmp,"keyboard_ts2068.bmp");
    else if (MACHINE_IS_Z88) strcpy(nombrebmp,"keyboard_z88.bmp");
    else if (MACHINE_IS_SPECTRUM_P2) strcpy(nombrebmp,"keyboard_p2.bmp");
    else if (MACHINE_IS_SPECTRUM_P2A_P3) strcpy(nombrebmp,"keyboard_p3.bmp");
    else if (MACHINE_IS_SPECTRUM_16) strcpy(nombrebmp,"keyboard_16.bmp");
    else if (MACHINE_IS_SPECTRUM_48_SPA) strcpy(nombrebmp,"keyboard_48s.bmp");
    else if (MACHINE_IS_SPECTRUM_128) strcpy(nombrebmp,"keyboard_128.bmp");
    else if (MACHINE_IS_SPECTRUM_128_SPA) strcpy(nombrebmp,"keyboard_128s.bmp");		
    else if (MACHINE_IS_ZX80) strcpy(nombrebmp,"keyboard_zx80.bmp");
    else if (MACHINE_IS_ZX81) strcpy(nombrebmp,"keyboard_zx81.bmp");
    else if (MACHINE_IS_ZXEVO) strcpy(nombrebmp,"keyboard_zxevo.bmp");
    else if (MACHINE_IS_ZXUNO) strcpy(nombrebmp,"keyboard_zxuno.bmp");
    else strcpy(nombrebmp,"keyboard_48.bmp");

    //localizarlo
    char buffer_nombre[PATH_MAX];

    int existe=find_sharedfile(nombrebmp,buffer_nombre);
    if (!existe)  {
            debug_printf(VERBOSE_ERR,"Unable to find bmp file %s",nombrebmp);
            return;
    }

    help_keyboard_bmp_file_mem=util_load_bmp_file(buffer_nombre);


    //if (help_keyboard_bmp_file_mem==NULL) return;


		

}


int help_keyboard_valor_contador_segundo_anterior;

zxvision_window *menu_help_keyboard_overlay_window;




void menu_help_keyboard_overlay(void)
{
	if (!zxvision_drawing_in_background) normal_overlay_texto_menu();


    if (!si_complete_video_driver() ) return;


    //Cargar bmp si ha cambiado de maquina
    if (help_keyboard_last_current_machine!=current_machine_type) {
        help_keyboard_last_current_machine=current_machine_type;

        debug_printf(VERBOSE_DEBUG,"Loading help keyboard bmp");
        menu_help_keyboard_load_bmp();
    }

	//Si no hay archivo bmp cargado
	if (help_keyboard_bmp_file_mem==NULL) return;

	menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech

    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_help_keyboard_overlay_window->is_minimized) return;

    //printf("Overlay help heyboard %d\n",contador_segundo);


	zxvision_window *ventana;

	ventana=menu_help_keyboard_overlay_window;


    //esto hara ejecutar esto 5 veces por segundo (lo habitual en muchos de estos que no actualizan siempre es 2 veces por segundo)
    if ( ((contador_segundo%200) == 0 && help_keyboard_valor_contador_segundo_anterior!=contador_segundo) || menu_multitarea==0) {
                                    help_keyboard_valor_contador_segundo_anterior=contador_segundo;
        //printf ("Refrescando. contador_segundo=%d\n",contador_segundo);

        //zoom_x de offset para evitar parpadeo con la linea del recuadro por la izquierda
        screen_render_bmpfile(help_keyboard_bmp_file_mem,BMP_INDEX_FIRST_COLOR,ventana,zoom_x,0,0,-1,0);
                


    }

    //Siempre hará el dibujado de contenido para evitar que cuando esta en background, otra ventana por debajo escriba algo,
    //y entonces como esta no redibuja siempre, al no escribir encima, se sobreescribe este contenido con el de otra ventana
    //En ventanas que no escriben siempre su contenido, siempre deberia estar zxvision_draw_window_contents que lo haga siempre
    zxvision_draw_window_contents(ventana);



}


void menu_help_keyboard_create_window(zxvision_window *ventana,int x,int y,int ancho,int alto,int is_minimized,int is_maximized,
    int ancho_antes_minimize,int alto_antes_minimize)
{
    zxvision_new_window_gn_cim(ventana,x,y,ancho,alto,ancho-1,alto-2,"Keyboard Help","helpshowkeyboard",is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);

	ventana->can_be_backgrounded=1;

    //Metemos todo el contenido de la ventana con caracter transparente, para que no haya parpadeo
    //en caso de drivers xwindows por ejemplo, pues continuamente redibuja el texto (espacios) y encima el overlay
    //Al meter caracter transparente, el normal_overlay lo ignora y no dibuja ese caracter

    //ya no hace falta transparente debido al nuevo tratamiento de cache de putchar
    //zxvision_fill_window_transparent(ventana);

    zxvision_draw_window(ventana);
}



zxvision_window menu_help_show_keyboard_ventana;

void menu_help_show_keyboard(MENU_ITEM_PARAMETERS)
{

    

	menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();		

	if (!menu_multitarea) {
			menu_warn_message("This window needs multitask enabled");
			return;
	}	

	zxvision_window *ventana;
		
	ventana=&menu_help_show_keyboard_ventana;

    //IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
    //si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
    //la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
    zxvision_delete_window_if_exists(ventana);

		
	int x,y,ancho,alto,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;

	if (!util_find_window_geometry("helpshowkeyboard",&x,&y,&ancho,&alto,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
		//x=menu_origin_x();
		x=0;
		y=0;

		//540x201 es lo que ocupa el bmp de spectrum 48k

		ancho=1+1+540/menu_char_width/zoom_x;

		alto=1+2+201/8/zoom_y;

		//printf ("ancho %d alto %d\n",ancho,alto);

	}		



    menu_help_keyboard_create_window(ventana,x,y,ancho,alto,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);

    int ancho_anterior,alto_anterior;
    zxvision_window_save_size(ventana,&ancho_anterior,&alto_anterior);

	

    menu_help_keyboard_overlay_window=ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui


    help_keyboard_valor_contador_segundo_anterior=contador_segundo;

    //Cambiamos funcion overlay de texto de menu
    //Se establece a la de funcion de onda + texto
    set_menu_overlay_function(menu_help_keyboard_overlay);

    //Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
    //Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
    if (zxvision_currently_restoring_windows_on_start) {
        //printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
        return;
    }	

	//Al entrar siempre cargar bmp, esto especialmente es importante por si conmutamos a ventana about o cualquier otra que cargue bmp,
    //que luego al entrar aqui recargue la paleta asociada
    menu_help_keyboard_load_bmp();

	z80_byte tecla;

	do {
        tecla=zxvision_common_getkey_refresh();		
        zxvision_handle_cursors_pgupdn(ventana,tecla);
        //printf ("tecla: %d\n",tecla);

		if (ventana->visible_height!=alto_anterior || ventana->visible_width!=ancho_anterior) {

            zxvision_window_save_size(ventana,&ancho_anterior,&alto_anterior);
            
            //Esto evita el parpadeo al redimensionar para hacer mas grande. Llenamos toda la ventana con el transparente,
            //que se hace asi siempre al crearla por primera vez

            //ya no hace falta transparente debido al nuevo tratamiento de cache de putchar
            //zxvision_fill_window_transparent(ventana);

		}        
	} while (tecla!=2 && tecla!=3);				

	//Gestionar salir con tecla background
 
	menu_espera_no_tecla(); //Si no, se va al menu anterior.
	//En AY Piano por ejemplo esto no pasa aunque el estilo del menu es el mismo...

	//Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
	zxvision_set_window_overlay_from_current(ventana);	

    //restauramos modo normal de texto de menu
    set_menu_overlay_function(normal_overlay_texto_menu);


    cls_menu_overlay();	

	//Grabar geometria ventana
	util_add_window_geometry_compact(ventana);		


	if (tecla==3) {
		zxvision_message_put_window_background();
	}

	else {
		zxvision_destroy_window(ventana);	
		free(help_keyboard_bmp_file_mem);	
 	}


}

void menu_storage_zxpand_enable(MENU_ITEM_PARAMETERS)
{
	if (zxpand_enabled.v) zxpand_disable();
	else zxpand_enable();
}

void menu_storage_zxpand_root_dir(MENU_ITEM_PARAMETERS)
{

	int ret;
	ret=menu_storage_string_root_dir(zxpand_root_dir);

	//Si sale con ESC
	if (ret==0) {
       	//directorio zxpand vacio
        zxpand_cwd[0]=0;
	}		

} 


void menu_zxpand(MENU_ITEM_PARAMETERS)
{

	

        //Dado que es una variable local, siempre podemos usar este nombre array_menu_common
        menu_item *array_menu_common;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

                
				
			menu_add_item_menu_inicial_format(&array_menu_common,MENU_OPCION_NORMAL,menu_storage_zxpand_enable,NULL,"[%c] ZX~~pand emulation",(zxpand_enabled.v ? 'X' : ' ') );
                        menu_add_item_menu_shortcut(array_menu_common,'p');
			menu_add_item_menu_tooltip(array_menu_common,"Enable ZXpand emulation");
			menu_add_item_menu_ayuda(array_menu_common,"Enable ZXpand emulation");


			if (zxpand_enabled.v) {
				char string_zxpand_root_folder_shown[20];
				menu_tape_settings_trunc_name(zxpand_root_dir,string_zxpand_root_folder_shown,20);

				menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_storage_zxpand_root_dir,NULL,"~~Root dir: %s",string_zxpand_root_folder_shown);
                        	menu_add_item_menu_shortcut(array_menu_common,'r');
				menu_add_item_menu_tooltip(array_menu_common,"Sets the root directory for ZXpand filesystem");
				menu_add_item_menu_ayuda(array_menu_common,"Sets the root directory for ZXpand filesystem. "
					"Only file and folder names valid for zxpand will be shown:\n"
					"-Maximum 8 characters for name and 3 for extension\n"
					"-Files and folders will be shown always in uppercase. Folders which are not uppercase, are shown but can not be accessed\n"
					);

			}
		

						
			menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

            menu_add_ESC_item(array_menu_common);

            retorno_menu=menu_dibuja_menu(&zxpand_opcion_seleccionada,&item_seleccionado,array_menu_common,"ZXpand" );

                
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);


}

void menu_ql_microdrive_floppy(MENU_ITEM_PARAMETERS)
{
	ql_microdrive_floppy_emulation ^=1;
}



int menu_storage_ql_mdv_flp(char *string_root_dir)
{

        char *filtros[2];

        filtros[0]="";
        filtros[1]=0;


        //guardamos directorio actual
        char directorio_actual[PATH_MAX];
        getcwd(directorio_actual,PATH_MAX);

        int ret;


	char nada[PATH_MAX];

        //Obtenemos ultimo directorio visitado
	zvfs_chdir(string_root_dir);


        ret=menu_filesel("Enter dir & press ESC",filtros,nada);


	//Si sale con ESC
	if (ret==0) {
		//Directorio root
		sprintf (string_root_dir,"%s",menu_filesel_last_directory_seen);
		debug_printf (VERBOSE_DEBUG,"Selected directory: %s",string_root_dir);

	}

    //volvemos a directorio inicial
    zvfs_chdir(directorio_actual);

	return ret;


}


void menu_ql_mdv1(MENU_ITEM_PARAMETERS)
{
	menu_storage_ql_mdv_flp(ql_mdv1_root_dir);

	//Copiar misma ruta a flp1
	if (ql_flp1_follow_mdv1.v) strcpy(ql_flp1_root_dir,ql_mdv1_root_dir);
}

void menu_ql_mdv2(MENU_ITEM_PARAMETERS)
{
	menu_storage_ql_mdv_flp(ql_mdv2_root_dir);
}

void menu_ql_flp1(MENU_ITEM_PARAMETERS)
{
	menu_storage_ql_mdv_flp(ql_flp1_root_dir);
}


/*
void menu_ql_replace_underscore(MENU_ITEM_PARAMETERS)
{
	ql_replace_underscore_dot.v ^=1;
}


void menu_ql_replace_underscore_only_one(MENU_ITEM_PARAMETERS)
{
	ql_replace_underscore_dot_only_one.v ^=1;
}
*/


void menu_ql_flp1_follow_mdv1(MENU_ITEM_PARAMETERS)
{
	ql_flp1_follow_mdv1.v ^=1;
}

void menu_ql_data_size_headerless(MENU_ITEM_PARAMETERS)
{
    char string_data_size[7];


    sprintf (string_data_size,"%d",ql_task_default_data_size);



    int retorno=menu_ventana_scanf_numero("Data size",string_data_size,7,+4096,0,131072,1);
    if (retorno>=0) {
        int valor=parse_string_to_number(string_data_size);

        if (valor<0 || valor>131072) debug_printf(VERBOSE_ERR,"Invalid value. Must be in range (0-131072)");
        else ql_task_default_data_size=valor;
    }
}

void menu_ql_mdv1_readonly(MENU_ITEM_PARAMETERS)
{
    ql_device_mdv1_readonly ^= 1;
}

void menu_ql_mdv2_readonly(MENU_ITEM_PARAMETERS)
{
    ql_device_mdv2_readonly ^= 1;
}

void menu_ql_flp1_readonly(MENU_ITEM_PARAMETERS)
{
    ql_device_flp1_readonly ^= 1;
}


void menu_ql_mdv_flp(MENU_ITEM_PARAMETERS)
{

	

        //Dado que es una variable local, siempre podemos usar este nombre array_menu_common
        menu_item *array_menu_common;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

                
				

            menu_add_item_menu_inicial_format(&array_menu_common,MENU_OPCION_NORMAL,menu_ql_microdrive_floppy,NULL,"[%c] Microdrive&Floppy",
                    (ql_microdrive_floppy_emulation ? 'X' : ' ') );

                    if (ql_microdrive_floppy_emulation) {
                            menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);
                            
                            char string_ql_mdv1_root_dir_shown[28];
                            char string_ql_mdv2_root_dir_shown[28];
                            char string_ql_flp1_root_dir_shown[28];
                            menu_tape_settings_trunc_name(ql_mdv1_root_dir,string_ql_mdv1_root_dir_shown,28);
                            menu_tape_settings_trunc_name(ql_mdv2_root_dir,string_ql_mdv2_root_dir_shown,28);
                            menu_tape_settings_trunc_name(ql_flp1_root_dir,string_ql_flp1_root_dir_shown,28);

                            menu_add_item_menu_format(array_menu_common,MENU_OPCION_SEPARADOR,NULL,NULL,"Mdv1 root dir:");
                            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_ql_mdv1,NULL,"[%s]",string_ql_mdv1_root_dir_shown);
                            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_ql_mdv1_readonly,NULL,"[%c] Read only",
                                (ql_device_mdv1_readonly ? 'X' : ' ') );                            

                            menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);


                            menu_add_item_menu_format(array_menu_common,MENU_OPCION_SEPARADOR,NULL,NULL,"Mdv2 root dir:");
                            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_ql_mdv2,NULL,"[%s]",string_ql_mdv2_root_dir_shown);
                            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_ql_mdv2_readonly,NULL,"[%c] Read only",
                                (ql_device_mdv2_readonly ? 'X' : ' ') ); 
                            menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);
  

                            menu_add_item_menu_format(array_menu_common,MENU_OPCION_SEPARADOR,NULL,NULL,"Flp1 root dir:");
                            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_ql_flp1,NULL,"[%s]",string_ql_flp1_root_dir_shown);
                            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_ql_flp1_readonly,NULL,"[%c] Read only",
                                (ql_device_flp1_readonly ? 'X' : ' ') );   

							menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);


                            /*
							menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_ql_replace_underscore,NULL,"[%c] Replace _ to . in filename",
                    			(ql_replace_underscore_dot.v ? 'X' : ' ') );
 
							if (ql_replace_underscore_dot.v) {
								menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_ql_replace_underscore_only_one,NULL,"[%c] Replace only the extension",
                    				(ql_replace_underscore_dot_only_one.v ? 'X' : ' ') );
							}
                            */


							menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_ql_flp1_follow_mdv1,NULL,"[%c] FLP1 path follows MDV1",
                    (ql_flp1_follow_mdv1.v ? 'X' : ' ') );

                            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_ql_data_size_headerless,NULL,"[%6d] Data size for headerless exe",
                                ql_task_default_data_size);

                    }

						
			menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

            menu_add_ESC_item(array_menu_common);

            retorno_menu=menu_dibuja_menu(&ql_mdv_flp_opcion_seleccionada,&item_seleccionado,array_menu_common,"Microdrive & Floppy" );

                
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);


}


zxvision_window *menu_debug_unnamed_console_overlay_window;


int menu_debug_unnamed_console_indicador_actividad_contador=0;

int menu_debug_unnamed_console_indicador_actividad_visible=0;


void menu_debug_unnamed_console_show_legend(zxvision_window *ventana)
{
        //Forzar a mostrar atajos
        z80_bit antes_menu_writing_inverse_color;
        antes_menu_writing_inverse_color.v=menu_writing_inverse_color.v;
        menu_writing_inverse_color.v=1;		

        //Y linea leyenda
        char buffer_leyenda[32];
        sprintf(buffer_leyenda,"[%d] Verbose ~~level",verbose_level);
        zxvision_print_string_defaults_fillspc(ventana,1,0,buffer_leyenda);

        //Restaurar comportamiento atajos
        menu_writing_inverse_color.v=antes_menu_writing_inverse_color.v;     
}

void menu_debug_unnamed_console_overlay(void)
{

    if (!zxvision_drawing_in_background) normal_overlay_texto_menu();

    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_debug_unnamed_console_overlay_window->is_minimized) return; //Sustituir xxxx_overlay_window por lo que convenga
 
    //printf("Overlay verbose console %d\n",contador_segundo);


    zxvision_window *ventana;

    ventana=menu_debug_unnamed_console_overlay_window;   


    //Revisar aqui tambien si no esta inicializado el puntero,
    //por si esta la ventana en background y a alguien le da por desactivar el debug console
    if (debug_unnamed_console_memory_pointer==NULL || debug_unnamed_console_enabled.v==0) {
        zxvision_print_string_defaults_fillspc(ventana,1,0,"Debug console is not enabled. Enable it on Settings->Debug");
        zxvision_draw_window_contents(ventana);
        return;
    }   


    int refrescar_borrado_contador=0;

    //Ver si hay que borrar contador actividad
    if (menu_debug_unnamed_console_indicador_actividad_visible>0) {
        menu_debug_unnamed_console_indicador_actividad_visible--;
        if (menu_debug_unnamed_console_indicador_actividad_visible==0) {
            //Borrar contador actividad
            //printf("---------BORRAR contador actividad\n");
            zxvision_print_string_defaults_fillspc(ventana,1,1,"");

            refrescar_borrado_contador=1;
        }
    }

    if (!debug_unnamed_console_modified) {
        //Si no hay mensajes, ver si hay que refrescar porque se ha borrado el contador de actividad
        if (refrescar_borrado_contador) {
            //printf("---Refrescar antes de salir sin escribir\n");
            zxvision_draw_window_contents(ventana);
        }
        return;
    }


    int x,y;
    char *puntero;

    puntero=debug_unnamed_console_memory_pointer;

    //DEBUG_UNNAMED_CONSOLE_WIDTH*DEBUG_UNNAMED_CONSOLE_HEIGHT
    for (y=0;y<DEBUG_UNNAMED_CONSOLE_HEIGHT;y++) {
        char buffer_linea[DEBUG_UNNAMED_CONSOLE_WIDTH+1];
        for (x=0;x<DEBUG_UNNAMED_CONSOLE_WIDTH;x++) {
            //printf("%c",*puntero);

            //Empieza en x+1 para dejar 1 caracter margen izquierda
            //zxvision_print_char_defaults(ventana,x+1,y+2,*puntero);

            //Hay que guardarlo como string para poder visualizar caracteres utf-8 etc
            buffer_linea[x]=*puntero;


            puntero++;
        }
        buffer_linea[x]=0;
        //Empieza en x+1 para dejar 1 caracter margen izquierda
        zxvision_print_string_defaults(ventana,1,y+2,buffer_linea);
        //printf("\n");
    }

    //Mostrar indicador actividad. Para que diga que hay mensajes nuevos
    //mantener durante 50 frames (1 segundo visible) despues de ultimo mensaje
    menu_debug_unnamed_console_indicador_actividad_visible=50;
    char *mensaje="|/-\\";

    int max=strlen(mensaje);
    char mensaje_dest[32];

    int pos=menu_debug_unnamed_console_indicador_actividad_contador % max;
    menu_debug_unnamed_console_indicador_actividad_contador++;

    sprintf(mensaje_dest,"[New messages %c]",mensaje[pos]);

    zxvision_print_string_defaults_fillspc(ventana,1,1,mensaje_dest);

    //Mostar la leyenda tambien aqui, para cuando refresca en segundo plano,
    //porque a veces se redibujan las ventanas pero solo se llama al overlay, y no a la funcion principal 
    menu_debug_unnamed_console_show_legend(ventana);

    zxvision_draw_window_contents(ventana);

    //Decir que no se ha modificado 
    debug_unnamed_console_modified=0;
}


zxvision_window zxvision_window_unnamed_console;

void menu_debug_unnamed_console(MENU_ITEM_PARAMETERS)
{
    /*if (!menu_multitarea) {
            menu_warn_message("This window needs multitask enabled");
            return;
    }*/




    zxvision_window *ventana;
    ventana=&zxvision_window_unnamed_console;    

    //IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
    //si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
    //la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
    zxvision_delete_window_if_exists(ventana);    

    int x,y,ancho,alto,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;

    if (!util_find_window_geometry("debugconsole",&x,&y,&ancho,&alto,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
        x=menu_origin_x();
        y=0;
        ancho=32;
        alto=18;
    }    

    //DEBUG_UNNAMED_CONSOLE_HEIGHT+2 porque hay dos lineas de leyenda superior
    //DEBUG_UNNAMED_CONSOLE_WIDTH+1 porque damos 1 espacio con margen por la izquierda
    //zxvision_new_window(ventana,x,y,ancho,alto,DEBUG_UNNAMED_CONSOLE_WIDTH+1,DEBUG_UNNAMED_CONSOLE_HEIGHT+2,"Debug console");

    zxvision_new_window_gn_cim(ventana,x,y,ancho,alto,DEBUG_UNNAMED_CONSOLE_WIDTH+1,DEBUG_UNNAMED_CONSOLE_HEIGHT+2,"Debug console","debugconsole",
        is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);    
  
    //Ajustar el scroll al maximo, para entrar y mostrar las ultimas lineas

    //Con esto llegara mas alla del limite
    //dado que debug_unnamed_console_current_y, si esta al maximo, es mas de lo que se puede bajar

    int linea_scroll=debug_unnamed_console_current_y;

    //-4 para asegurarnos que siempre vaya por debajo
    linea_scroll -=(alto-4);
    if (linea_scroll<0) linea_scroll=0;
    zxvision_set_offset_y_or_maximum(ventana,linea_scroll);

    

    ventana->can_be_backgrounded=1;
    ventana->upper_margin=2;
    //Permitir hotkeys desde raton
    ventana->can_mouse_send_hotkeys=1;	

    //indicar nombre del grabado de geometria
    //strcpy(ventana->geometry_name,"debugconsole");
    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;    

    zxvision_draw_window(ventana);

    menu_debug_unnamed_console_overlay_window=ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui

                                                
    //Cambiamos funcion overlay de texto de menu
    //Se establece a la de funcion de onda + texto
    set_menu_overlay_function(menu_debug_unnamed_console_overlay);   

    //Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
    //Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
    if (zxvision_currently_restoring_windows_on_start) {
        //printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
        return;
    }

    menu_first_aid("debug_console");

    z80_byte tecla;
    do {

        
        menu_debug_unnamed_console_show_legend(ventana);


        tecla=zxvision_common_getkey_refresh();
        zxvision_handle_cursors_pgupdn(ventana,tecla);

        if (tecla=='l') {
            menu_debug_verbose(0);
            debug_unnamed_console_modified=1;
        }

        //printf ("tecla: %d\n",tecla);
    } while (tecla!=2 && tecla!=3);

	//Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
	//(siempre que esta funcion tenga overlay realmente)
	zxvision_set_window_overlay_from_current(ventana);    

    //restauramos modo normal de texto de menu
     set_menu_overlay_function(normal_overlay_texto_menu);

    
    cls_menu_overlay();

    //Grabar geometria ventana
    util_add_window_geometry_compact(ventana);    

	if (tecla==3) {
		//zxvision_ay_registers_overlay
		zxvision_message_put_window_background();
	}

	else {
		zxvision_destroy_window(ventana);		
 	}
}


zxvision_window *menu_audio_general_sound_overlay_window;

//Valores previos para vu meters dac
int menu_audio_general_sound_previos_dac[4];

//Valores previos para vu meters volumenes
int menu_audio_general_sound_previos_volumes[4];

//Valores previos para vu meters left right
int menu_audio_general_sound_previo_left;
int menu_audio_general_sound_previo_right;


int menu_audio_general_sound_contador_segundo_anterior;

void menu_audio_general_sound_overlay(void)
{

    if (!zxvision_drawing_in_background) normal_overlay_texto_menu();

 
    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_audio_general_sound_overlay_window->is_minimized) return;

    //printf("overlay general sound %d\n",contador_segundo);


    zxvision_window *ventana;

    ventana=menu_audio_general_sound_overlay_window;   


    if (gs_enabled.v==0) {
        zxvision_print_string_defaults_fillspc(ventana,1,0,"General sound is not enabled");
        zxvision_draw_window_contents(ventana);
        return;
    }   

    int decaer_volumenes=0;

    //esto hara ejecutar esto 2 veces por segundo
    if ( ((contador_segundo%500) == 0 && menu_audio_general_sound_contador_segundo_anterior!=contador_segundo) || menu_multitarea==0) {

        menu_audio_general_sound_contador_segundo_anterior=contador_segundo;

        decaer_volumenes=1;
    }
 


    int linea=0;
    char buffer_linea[64];

    //Forzar a mostrar atajos
    z80_bit antes_menu_writing_inverse_color;
    antes_menu_writing_inverse_color.v=menu_writing_inverse_color.v;
    menu_writing_inverse_color.v=1;		

 
    sprintf(buffer_linea,"~~Mode: %s",(gs_stereo_mode.v ? "Stereo" : "Mono") );
    zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);    

    //Restaurar comportamiento atajos
    menu_writing_inverse_color.v=antes_menu_writing_inverse_color.v; 

    sprintf(buffer_linea,"Command Register: %02XH",gs_command_register);
    zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);

    sprintf(buffer_linea,"Status Register:  %02XH",gs_state_register);
    zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);    

    sprintf(buffer_linea,"Data Register:    %02XH",gs_data_register);
    zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);

    sprintf(buffer_linea,"Output Register:  %02XH",gs_output_register);
    zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);    
   
    sprintf(buffer_linea,"MMU Register:     %02XH",gs_memory_mapping_value);
    zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);    

    zxvision_print_string_defaults_fillspc(ventana,1,linea++,"");  

    int i;    

    /*
    for (i=0;i<4;i++) {
        sprintf(buffer_linea,"Volume   #%d:      %02XH",i,gs_volumes[i]);
        zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);            
    }
    */

    /*
    for (i=0;i<4;i++) {
        sprintf(buffer_linea,"Last DAC #%d:      %02XH",i,gs_dac_channels[i]);
        zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);            
    }
    */

    //Controlar limites, dado que las variables entran sin inicializar
    for (i=0;i<4;i++) {
        if (menu_audio_general_sound_previos_dac[i]>15) menu_audio_general_sound_previos_dac[i]=15;
    }

    for (i=0;i<4;i++) {
        if (menu_audio_general_sound_previos_volumes[i]>15) menu_audio_general_sound_previos_volumes[i]=15;
    }    

    if (menu_audio_general_sound_previo_left>15) menu_audio_general_sound_previo_left=15;
    if (menu_audio_general_sound_previo_right>15) menu_audio_general_sound_previo_right=15;


    int nivel_actual;
    char buf_nivel[33];
    
    for (i=0;i<4;i++) {
        //VU meters para volumes

        nivel_actual=gs_volumes[i];


        //Y pasar de escala 0..3F a escala 0..15
        nivel_actual /=4;

        if (nivel_actual>=16) nivel_actual=15;

        menu_audio_general_sound_previos_volumes[i]=menu_decae_ajusta_valor_volumen(menu_audio_general_sound_previos_volumes[i],nivel_actual);
        

        
        menu_string_volumen(buf_nivel,nivel_actual,menu_audio_general_sound_previos_volumes[i]);
        sprintf (buffer_linea,"Volume #%d: %02XH %s",i,gs_volumes[i],buf_nivel);
        zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);

        if (decaer_volumenes) {
            menu_audio_general_sound_previos_volumes[i]=menu_decae_dec_valor_volumen(menu_audio_general_sound_previos_volumes[i],nivel_actual);
        }        
    



        //VU meters para DAC, para volumes
    

        //Valor unsigned con 0 en 128
        nivel_actual=gs_dac_channels[i];
        nivel_actual=nivel_actual-128;

        //Valor absoluto
        if (nivel_actual<0) nivel_actual=-nivel_actual;

        //Y pasar de escala 0..128 a escala 0..15
        nivel_actual /=8;

        if (nivel_actual>=16) nivel_actual=15;

        menu_audio_general_sound_previos_dac[i]=menu_decae_ajusta_valor_volumen(menu_audio_general_sound_previos_dac[i],nivel_actual);
        

        //char buf_nivel[33];

        
        menu_string_volumen(buf_nivel,nivel_actual,menu_audio_general_sound_previos_dac[i]);
        sprintf (buffer_linea,"DAC    #%d: %02XH %s",i,gs_dac_channels[i],buf_nivel);
        zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);

        if (decaer_volumenes) {
            //printf("Decaer volumen %d\n",i);
            //printf("decae actual %d\n",menu_audio_general_sound_previos_dac[i]);
            menu_audio_general_sound_previos_dac[i]=menu_decae_dec_valor_volumen(menu_audio_general_sound_previos_dac[i],nivel_actual);
        }        
    }



        //VU meters para Left
    

        //Valor unsigned con 0 en 128
        nivel_actual=gs_dac_valor_final_left;
        nivel_actual=nivel_actual-128;

        //Valor absoluto
        if (nivel_actual<0) nivel_actual=-nivel_actual;

        //Y pasar de escala 0..128 a escala 0..15
        nivel_actual /=8;

        if (nivel_actual>=16) nivel_actual=15;

        menu_audio_general_sound_previo_left=menu_decae_ajusta_valor_volumen(menu_audio_general_sound_previo_left,nivel_actual);
        

        //char buf_nivel[33];

        
        menu_string_volumen(buf_nivel,nivel_actual,menu_audio_general_sound_previo_left);
        sprintf (buffer_linea,"Left Out:  %02XH %s",gs_dac_valor_final_left,buf_nivel);
        zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);

        if (decaer_volumenes) {
            menu_audio_general_sound_previo_left=menu_decae_dec_valor_volumen(menu_audio_general_sound_previo_left,nivel_actual);
        }     

        //VU meters para Right
    

        //Valor unsigned con 0 en 128
        nivel_actual=gs_dac_valor_final_right;
        nivel_actual=nivel_actual-128;

        //Valor absoluto
        if (nivel_actual<0) nivel_actual=-nivel_actual;

        //Y pasar de escala 0..128 a escala 0..15
        nivel_actual /=8;

        if (nivel_actual>=16) nivel_actual=15;

        menu_audio_general_sound_previo_right=menu_decae_ajusta_valor_volumen(menu_audio_general_sound_previo_right,nivel_actual);
        

        //char buf_nivel[33];

        
        menu_string_volumen(buf_nivel,nivel_actual,menu_audio_general_sound_previo_right);
        sprintf (buffer_linea,"Right Out: %02XH %s",gs_dac_valor_final_right,buf_nivel);
        zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);

        if (decaer_volumenes) {
            menu_audio_general_sound_previo_right=menu_decae_dec_valor_volumen(menu_audio_general_sound_previo_right,nivel_actual);
        }             


    //Left & Right Channels
    /*
    sprintf(buffer_linea,"Left:    %02XH",gs_dac_valor_final_left);
    zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);

    sprintf(buffer_linea,"Right:    %02XH",gs_dac_valor_final_left);
    zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);    
    */

   zxvision_print_string_defaults_fillspc(ventana,1,linea++,"");

    sprintf(buffer_linea,"PC=%04X SP=%04X AF=%04X HL=%04X",
        general_sound_z80_cpu.r_pc,general_sound_z80_cpu.r_sp,general_sound_z80_cpu.r_af,general_sound_z80_cpu.r_hl);
    zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);

    sprintf(buffer_linea,"BC=%04X DE=%04X IX=%04X IY=%04X",
        general_sound_z80_cpu.r_bc,general_sound_z80_cpu.r_de,general_sound_z80_cpu.r_ix,general_sound_z80_cpu.r_iy);
    zxvision_print_string_defaults_fillspc(ventana,1,linea++,buffer_linea);

    



    zxvision_draw_window_contents(ventana);


}


zxvision_window zxvision_window_general_sound;

void menu_audio_general_sound(MENU_ITEM_PARAMETERS)
{
    /*if (!menu_multitarea) {
            menu_warn_message("This window needs multitask enabled");
            return;
    }*/




    zxvision_window *ventana;
    ventana=&zxvision_window_general_sound;    

    //IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
    //si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
    //la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
    zxvision_delete_window_if_exists(ventana);    

    int x,y,ancho,alto,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;

    if (!util_find_window_geometry("audiogensound",&x,&y,&ancho,&alto,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
        x=menu_origin_x();
        y=1;
        ancho=33;
        alto=22;   
    }    


    //Crear nueva ventana, asignando ademas geometry name y gestionando si se crea minimizada
    zxvision_new_window_gn_cim(ventana,x,y,ancho,alto,ancho-1,alto-2,"General sound","audiogensound",is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);


    //zxvision_new_window(ventana,x,y,ancho,alto,ancho-1,alto-2,"General sound");

    ventana->can_be_backgrounded=1;
    //ventana->upper_margin=2;
    //Permitir hotkeys desde raton
    ventana->can_mouse_send_hotkeys=1;	

    //indicar nombre del grabado de geometria
    //strcpy(ventana->geometry_name,"audiogensound");
    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;    

    zxvision_draw_window(ventana);

    menu_audio_general_sound_overlay_window=ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui

                                                
    //Cambiamos funcion overlay de texto de menu
    //Se establece a la de funcion de onda + texto
    set_menu_overlay_function(menu_audio_general_sound_overlay);   

    //Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
    //Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
    if (zxvision_currently_restoring_windows_on_start) {
        //printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
        return;
    }     

    z80_byte tecla;
    do {


        tecla=zxvision_common_getkey_refresh();
        zxvision_handle_cursors_pgupdn(ventana,tecla);

        if (tecla=='m') {
            gs_stereo_mode.v ^=1;
        }        


        //printf ("tecla: %d\n",tecla);
    } while (tecla!=2 && tecla!=3);

	//Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
	//(siempre que esta funcion tenga overlay realmente)
	zxvision_set_window_overlay_from_current(ventana);    

    //restauramos modo normal de texto de menu
     set_menu_overlay_function(normal_overlay_texto_menu);

    
    cls_menu_overlay();

    //Grabar geometria ventana
    util_add_window_geometry_compact(ventana);    

	if (tecla==3) {
		//zxvision_ay_registers_overlay
		zxvision_message_put_window_background();
	}

	else {
		zxvision_destroy_window(ventana);		
 	}
}






zxvision_window *menu_debug_ioports_overlay_window;

//Ultimo valor de lineas totales obtenido desde overlay
//Inicializado con algo por si acaso
int total_lineas_menu_debug_ioports=10;


//texto que contiene cada linea con ajuste de palabra. Al trocear las lineas aumentan
char debug_io_ports_buffer_lineas[MAX_LINEAS_TOTAL_GENERIC_MESSAGE][MAX_ANCHO_LINEAS_GENERIC_MESSAGE];

//Punteros a cada linea de esas
char *debug_ioports_punteros_lineas[MAX_LINEAS_TOTAL_GENERIC_MESSAGE];

//Obtener lineas de debug y separar cada linea
void menu_debug_ioports_overlay_get_lines(void)
{
  

    //Inicializar punteros a lineas
    int i;
    for (i=0;i<MAX_LINEAS_TOTAL_GENERIC_MESSAGE;i++) {
        debug_ioports_punteros_lineas[i]=&debug_io_ports_buffer_lineas[i][0];
    }

    char *io_buffer=util_malloc_max_texto_generic_message("Can not allocate memory for io buffer");


	debug_get_ioports(io_buffer);

    //printf("io ports: %s\n",io_buffer);


    total_lineas_menu_debug_ioports=zxvision_trocear_string_lineas(io_buffer,debug_ioports_punteros_lineas);

    free(io_buffer);
}


void menu_debug_ioports_overlay(void)
{

    if (!zxvision_drawing_in_background) normal_overlay_texto_menu();

 
    menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech

    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_debug_ioports_overlay_window->is_minimized) return;


    zxvision_window *ventana;

    ventana=menu_debug_ioports_overlay_window;   



    //Obtener lineas de debug y separar cada linea
    menu_debug_ioports_overlay_get_lines();
  
    int i;
  



    //Escribir cada linea
    //printf("total lineas: %d\n",total_lineas);

    for (i=0;i<total_lineas_menu_debug_ioports;i++) {
        zxvision_print_string_defaults_fillspc(ventana,1,i,debug_io_ports_buffer_lineas[i]);        
    }


    zxvision_draw_window_contents(ventana);


}


zxvision_window zxvision_window_debug_ioports;

void menu_debug_ioports(MENU_ITEM_PARAMETERS)
{
    /*if (!menu_multitarea) {
            menu_warn_message("This window needs multitask enabled");
            return;
    }*/




    zxvision_window *ventana;
    ventana=&zxvision_window_debug_ioports;    

    //IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
    //si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
    //la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
    zxvision_delete_window_if_exists(ventana);    

    int x,y,ancho,alto,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;

    if (!util_find_window_geometry("debugioports",&x,&y,&ancho,&alto,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
        x=menu_origin_x();
        y=1;
        ancho=33;
        alto=22;
    }    


    char titulo_ventana[64];

    if (CPU_IS_MOTOROLA) strcpy(titulo_ventana,"IO Addresses");
    else strcpy(titulo_ventana,"IO Ports");

    int total_alto=alto-2;

    //Calculo de minimo alto total, segun las lineas
    //Esta ventana tiene la particularidad que no sabemos a priori cuanto ocupara en alto total
    //dependera de la cantidad de lineas de i/o ports
    //Y o bien lo calculamos aqui al empezar, cosa que implicaria meter codigo redundante de la funcion de overlay,
    //o bien obtenemos el ultimo valor que muestra la funcion de overlay
    //Si lo obtenemos de overlay, implica que siempre habra que entrar una primera vez, con tamaño quiza menor,
    //y luego volver a entrar para que la ventana se recree
    //Mejor es reusar codigo para calcular ese alto

    //llamamos una primera vez para obtener total de lineas
    menu_debug_ioports_overlay_get_lines();

    if (total_alto<total_lineas_menu_debug_ioports) {
        total_alto=total_lineas_menu_debug_ioports;
        debug_printf(VERBOSE_DEBUG,"Increasing total Debug I/O window height to: %d",total_alto);
    }

    //zxvision_new_window(ventana,x,y,ancho,alto,ancho-1,total_alto,titulo_ventana);
  

    zxvision_new_window_gn_cim(ventana,x,y,ancho,alto,ancho-1,total_alto,titulo_ventana,"debugioports",is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);    

    ventana->can_be_backgrounded=1;


    //indicar nombre del grabado de geometria
    //strcpy(ventana->geometry_name,"debugioports");    

    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;

    zxvision_draw_window(ventana);

    menu_debug_ioports_overlay_window=ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui

                                                
    //Cambiamos funcion overlay de texto de menu
    //Se establece a la de funcion de onda + texto
    set_menu_overlay_function(menu_debug_ioports_overlay);   

    //Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
    //Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
    if (zxvision_currently_restoring_windows_on_start) {
        //printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
        return;
    }     

    z80_byte tecla;
    do {


        tecla=zxvision_common_getkey_refresh();
        zxvision_handle_cursors_pgupdn(ventana,tecla);


        //printf ("tecla: %d\n",tecla);
    } while (tecla!=2 && tecla!=3);

	//Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
	//(siempre que esta funcion tenga overlay realmente)
	zxvision_set_window_overlay_from_current(ventana);    

    //restauramos modo normal de texto de menu
     set_menu_overlay_function(normal_overlay_texto_menu);

    
    cls_menu_overlay();

    //Grabar geometria ventana
    util_add_window_geometry_compact(ventana);    

	if (tecla==3) {
		//zxvision_ay_registers_overlay
		zxvision_message_put_window_background();
	}

	else {
		zxvision_destroy_window(ventana);		
 	}
}



zxvision_window *menu_new_about_window_overlay_window;


//z80_byte *new_about_window_bmp_file_mem=NULL;

int new_about_window_ancho_mostrar=0;

void menu_new_about_window_overlay(void)
{
	if (!zxvision_drawing_in_background) normal_overlay_texto_menu();


    if (!si_complete_video_driver() ) return;



    menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech

	zxvision_window *ventana;

	ventana=menu_new_about_window_overlay_window;




    //Dibujar siempre la imagen, a 50 fps


    //zoom_x de offset para evitar parpadeo con la linea del recuadro por la izquierda
    //screen_render_bmpfile(new_about_window_bmp_file_mem,BMP_INDEX_FIRST_COLOR,ventana,zoom_x,1);

    //parametro x_ignore a 1 para evitar dibujar x=0 que sobreescribiria el marco izquierdo, produciendo parpadeo

    //aun asi, la imagen es de 63 pixeles de ancho, porque me producia parpadeo en la derecha, cosa que no entiendo,
    //podria tener una imagen de 64 pixeles de ancho y no caer la imagen 1 pixel sobre el texto de la derecha


    //mostrarla solo si hay archivo cargado. podria ser que alguien borrase el bmp
	//if (new_about_window_bmp_file_mem!=NULL) {
        screen_render_bmpfile(bitmap_salamanquesa,BMP_INDEX_FIRST_COLOR,ventana,1,1,new_about_window_ancho_mostrar,255,ESTILO_GUI_PAPEL_NORMAL);
    //}



    //Siempre hará el dibujado de contenido para evitar que cuando esta en background, otra ventana por debajo escriba algo,
    //y entonces como esta no redibuja siempre, al no escribir encima, se sobreescribe este contenido con el de otra ventana
    //En ventanas que no escriben siempre su contenido, siempre deberia estar zxvision_draw_window_contents que lo haga siempre
    zxvision_draw_window_contents(ventana);    

	

}




zxvision_window menu_about_new_ventana;

void menu_about_new(MENU_ITEM_PARAMETERS)
{

    

	menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();		


	zxvision_window *ventana;
		
	ventana=&menu_about_new_ventana;


		
	int x_ventana,y_ventana,ancho_ventana,alto_ventana;

    //hardcoded. la imagen bmp hace 64x64
    int ancho_imagen_salamanquesa=64;
    int alto_imagen_salamanquesa=64;
    

    int x_texto=ancho_imagen_salamanquesa/menu_char_width;
    //printf("x_texto: %d\n",x_texto);
    //con esto, son 8 caracteres cuando el menu_char_width=8 por defecto
    //pero si son menos de 7, pasaria que el texto se sobreescribe la primera columna por la imagen. ajustar

    //if (menu_char_width!=8) x_texto++;

    //printf("x_texto ajustado: %d\n",x_texto);
    //12345678901234567890123456789
    //(C) 2013 Cesar Hernandez Bano"
    // - Toi Acid Game edition - "
    
    //Lo siguiente es para que: con menu char width distinto de 8, quedaria un hueco vertical "transparente" entre el logo y el texto
    //esto seria casi imposible de evitar, pues ubico la zona del logo con transparente, y ese logo es multiple de 8 el ancho
    //la solucion es mostrar el logo siempre a multiplo del char width, por ejemplo si char width es 7,
    //mostrar 63 de ancho (que es multiple de 7). Y eso requiere la funcion de screen_render_bmpfile se le pueda
    //cambiar el ancho

    //Realmente lo que hago es cortar un poco el logo por la derecha pero como tiene margen en blanco, no pasa nada

    int ancho_mostrar_bmp=64/menu_char_width;

    int final_ancho_mostrar_bmp=ancho_mostrar_bmp*menu_char_width;

    //E indicamos a la funcion de render bmp, desde el overlay, el ancho final
    //printf("ancho bmp: %d\n",final_ancho_mostrar_bmp);

    new_about_window_ancho_mostrar=final_ancho_mostrar_bmp;

    //Textos. Creamos antes para ver el que tiene mas ancho
    char mensaje_about[3][200];
    //unsigned char letra_enye;

    //mensaje completo con enye en segundo apellido
    //letra_enye=129;       

    sprintf (mensaje_about[0],"ZEsarUX v." EMULATOR_VERSION " (" EMULATOR_SHORT_DATE ")");
    sprintf (mensaje_about[1]," - " EMULATOR_EDITION_NAME " - ");
    //sprintf (mensaje_about[2],"(C) 2013 Cesar Hernandez Ba%co",letra_enye);   
    sprintf (mensaje_about[2],"(C) 2013 César Hernández Bañó");   
    //sprintf (mensaje_about[2],"(C) 2013 Cesar Hernandez Bano");   

    int ancho_maximo=0; 
    int i;

    for (i=0;i<3;i++) {
        int ancho_texto=strlen(mensaje_about[i]);

        //TODO: dado que en mi nombre he puesto 3 acentos y una eñe, son 4 caracteres utf, que ocupan 2 bytes cada uno
        //por tanto strlen ve aparentemente 4 bytes de mas, los restamos para que se redimensione correctamente la ventana
        //lo ideal seria tener una funcion diferente a strlen que de la longitud real de un texto considerando utf
        if (i==2) ancho_texto -=4;

        if (ancho_texto>ancho_maximo) ancho_maximo=ancho_texto;
    }

    //+1 de margen derecho. el habitual izquierdo no lo contamos pues la parte izquierda ya la ocupa el logo
    ancho_ventana=ancho_maximo+x_texto+1;


    alto_ventana=10;

     

    //x_ventana=menu_center_x()-ancho_ventana/2;

    //Dado que si tenemos la opcion activada de situar ventanas en zx desktop por defecto,
    //si zx desktop es muy pequeño, no cabera ahi, y entonces la ventana se redimensiona al maximo como consecuencia del error
    //de que no cabe
    //por eso en vez de obtener menu_center_x() mejor usamos scr_get_menu_width que nos da el ancho total

    x_ventana=(scr_get_menu_width()-ancho_ventana)/2;

    y_ventana=menu_center_y()-alto_ventana/2;        

    //printf ("ancho %d alto %d\n",ancho,alto);

		

    int ancho_ventana_visible=ancho_ventana-1;
    int alto_ventana_visible=alto_ventana-2;


	zxvision_new_window(ventana,x_ventana,y_ventana,ancho_ventana,alto_ventana,
							ancho_ventana_visible,alto_ventana_visible,"About");

	
    //nota: la carga del juego de edicion y por tanto uno de los easter egg no sale con este about, logicamente pues no tenemos
    //opcion para buscar texto asi... hay que hacerlo desde el otro about, que se dispara si no hay zx desktop habilitado

    ventana->can_be_resized=0;

	zxvision_draw_window(ventana);

	
    //Cargar el archivo bmp
    /*
    bmp. 256 colour (indexed)
    */

/*
    char nombrebmp[PATH_MAX];

    strcpy(nombrebmp,"salamanquesa.bmp");


    //localizarlo
    char buffer_nombre[PATH_MAX];

    int existe=find_sharedfile(nombrebmp,buffer_nombre);
    if (!existe)  {
        debug_printf(VERBOSE_DEBUG,"Unable to find bmp file %s",nombrebmp);
        //no lanzamos error de esto, al menos mostrar ventana about
        //return;

        //decimos imagen a NULL para que no la muestre
        //en ese caso si que habra un recuadro transparente donde estaria la imagen
        //podria hacer que en este caso el recuadro no saliera, pero lo prefiero asi,
        //asi el usuario de alguna manera sabe que algo raro pasa... ;)
        new_about_window_bmp_file_mem=NULL;
    }

    else {
        new_about_window_bmp_file_mem=util_load_bmp_file(buffer_nombre);
    }


    //if (new_about_window_bmp_file_mem==NULL) return;
*/

    //La salamanquesa no se carga de disco sino que esta incrustada en el codigo. Es un BMP
    util_bmp_load_palette(bitmap_salamanquesa,BMP_INDEX_FIRST_COLOR);    

    //Metemos todo el contenido de la ventana con caracter transparente, para que no haya parpadeo
    //en caso de drivers xwindows por ejemplo, pues continuamente redibuja el texto (espacios) y encima el overlay
    //Al meter caracter transparente, el normal_overlay lo ignora y no dibuja ese caracter

    //ya no hace falta transparente debido al nuevo tratamiento de cache de putchar
    //zxvision_fill_window_transparent(ventana);



    //Y la zona que sera de texto, la quitamos como transparente (inicializamos con espacios)



    int x,y;
    for (y=0;y<alto_ventana_visible;y++) {
        //zxvision_print_string_defaults_fillspc(ventana,10,i,"");
        for (x=x_texto;x<ancho_ventana_visible;x++) {
            //zxvision_print_string_defaults(ventana,10,y,"         ");
            zxvision_print_char_defaults(ventana,x,y,' ');
        }
    }

      
    int linea;

    //considerar 3 lineas para centrar el texto (la de build number no la contamos pues solo es en los snapshots)
    //linea inicial para que quede centrado
    linea=(alto_ventana_visible-3)/2;
    //printf("linea: %d\n",linea);



    for (i=0;i<3;i++) {
        zxvision_print_string_defaults(ventana,x_texto,linea++,mensaje_about[i]);            
    }

#ifdef SNAPSHOT_VERSION
    char mensaje_about_build[200];
    sprintf (mensaje_about_build,"Build number: " BUILDNUMBER );
    zxvision_print_string_defaults(ventana,x_texto,linea++,mensaje_about_build);
#endif        

           
		

    menu_new_about_window_overlay_window=ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui



    //Cambiamos funcion overlay de texto de menu
    //Se establece a la de funcion de onda + texto
    set_menu_overlay_function(menu_new_about_window_overlay);



    //si no, el texto no apareceria a no ser que movieramos el raton o la ventana, cuando multitask esta off
	if (!menu_multitarea) zxvision_draw_window_contents(ventana);

	z80_byte tecla;

	do {
		tecla=zxvision_common_getkey_refresh();		
		zxvision_handle_cursors_pgupdn(ventana,tecla);
		//printf ("tecla: %d\n",tecla);
        if (mouse_is_clicking && mouse_is_double_clicking) {
            //printf("double click\n");
            if (si_menu_mouse_en_ventana() ) {
                //printf("Mouse en ventana\n");
                if (menu_mouse_x<x_texto) {
                    //printf("Coordenada mouse en columna salamanquesa\n");
                    int alto_imagen_salamanquesa_chars=alto_imagen_salamanquesa/8;
                    //printf("%d\n",menu_mouse_y);
                    //y=0 es el titulo
                    if (menu_mouse_y>0 && menu_mouse_y<alto_imagen_salamanquesa_chars+1) {
                        //printf("Clicked en salamanquesa\n");
                        menu_about_about_load_editionamegame();
                        //simular tecla esc
                        tecla=2;
                    }
                }

            }

        }
	} while (tecla!=2);				

 
	menu_espera_no_tecla(); //Si no, se va al menu anterior.
	//En AY Piano por ejemplo esto no pasa aunque el estilo del menu es el mismo...

	//Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
	zxvision_set_window_overlay_from_current(ventana);	

    //restauramos modo normal de texto de menu
     set_menu_overlay_function(normal_overlay_texto_menu);


    cls_menu_overlay();	



	zxvision_destroy_window(ventana);	
	//free(new_about_window_bmp_file_mem);	



}


void menu_setting_filesel_no_show_dirs(MENU_ITEM_PARAMETERS)
{
	menu_filesel_hide_dirs.v ^=1;
}

void menu_setting_filesel_no_show_size(MENU_ITEM_PARAMETERS)
{
	menu_filesel_hide_size.v ^=1;
}

void menu_setting_filesel_previews(MENU_ITEM_PARAMETERS)
{
	menu_filesel_show_previews.v ^=1;
}

void menu_setting_fileviewer_hex(MENU_ITEM_PARAMETERS)
{
    menu_file_viewer_always_hex.v ^=1;
}

void menu_setting_filesel_allow_delete_folders(MENU_ITEM_PARAMETERS)
{
    menu_filesel_utils_allow_folder_delete.v ^=1;
}

void menu_fileselector_settings(MENU_ITEM_PARAMETERS)
{
    menu_item *array_menu_common;
    menu_item item_seleccionado;
    int retorno_menu;
    do {



        menu_add_item_menu_inicial_format(&array_menu_common,MENU_OPCION_NORMAL,menu_setting_filesel_no_show_dirs,NULL,"[%c] Show ~~directories",
            (menu_filesel_hide_dirs.v==0 ? 'X' : ' ') );
        menu_add_item_menu_shortcut(array_menu_common,'d');	
        menu_add_item_menu_tooltip(array_menu_common,"Hide directories from file browser menus");
        menu_add_item_menu_ayuda(array_menu_common,"Hide directories from file browser menus. "
                                "Useful on demo environments and you don't want the user to be able to navigate the filesystem");

        menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_setting_filesel_no_show_size,NULL,"[%c] Show file ~~size",
            (menu_filesel_hide_size.v==0 ? 'X' : ' ') );
        menu_add_item_menu_shortcut(array_menu_common,'s');    
        menu_add_item_menu_tooltip(array_menu_common,"Hide file size from file selector menus");
        menu_add_item_menu_ayuda(array_menu_common,"Hide file size from file browser menus");      

        menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_setting_filesel_previews,NULL,"[%c] Show file ~~previews",
            (menu_filesel_show_previews.v ? 'X' : ' ') );
        menu_add_item_menu_shortcut(array_menu_common,'p');
        menu_add_item_menu_tooltip(array_menu_common,"Show file previews in the file selector");
        menu_add_item_menu_ayuda(array_menu_common,"Show file previews for .scr, .tap, .tzx, etc...\n"
                            "Note that the fileselector window must be big enough to hold that preview, if not, it will not be shown");


        menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_setting_fileviewer_hex,NULL,"[%c] ~~Hexadecimal file viewer",
            (menu_file_viewer_always_hex.v ? 'X' : ' ') );
        menu_add_item_menu_shortcut(array_menu_common,'h');
        menu_add_item_menu_tooltip(array_menu_common,"File viewer always shows file contents in hexadecimal+ascii");
        menu_add_item_menu_ayuda(array_menu_common,"File viewer always shows file contents in hexadecimal+ascii");


        menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_setting_filesel_allow_delete_folders,NULL,"[%c] Allow ~~folder delete",
            (menu_filesel_utils_allow_folder_delete.v ? 'X' : ' ') );
        menu_add_item_menu_shortcut(array_menu_common,'f');
        menu_add_item_menu_tooltip(array_menu_common,"Allows deleting folders on the file utilities browser. Enable it AT YOUR OWN RISK");
        menu_add_item_menu_ayuda(array_menu_common,"Allows deleting folders on the file utilities browser. Enable it AT YOUR OWN RISK");

                   

        menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

        menu_add_ESC_item(array_menu_common);

        retorno_menu=menu_dibuja_menu(&fileselector_settings_opcion_seleccionada,&item_seleccionado,array_menu_common,"File Browser Settings" );

                

        if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
            //llamamos por valor de funcion
            if (item_seleccionado.menu_funcion!=NULL) {
                //printf ("actuamos por funcion\n");
                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                
            }
        }

    } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);

}

void menu_debug_unload_source_code(MENU_ITEM_PARAMETERS)
{
    load_source_code_eject();

    menu_generic_message_splash("Unload Soure Code","OK File unloaded");
}


void menu_debug_load_source_code(MENU_ITEM_PARAMETERS)
{

    char source_load_file[PATH_MAX];

    char *filtros[3];

    filtros[0]="txt";
    filtros[1]="asm";
    filtros[2]=0;


    if (menu_filesel("Select Source File",filtros,source_load_file)==1) {
        int retorno=remote_load_source_code(source_load_file);

        if (!retorno) {
            menu_generic_message_splash("Load Soure Code","OK File loaded");
            //Y salimos de todos los menus
            salir_todos_menus=1;
        }

    }

}

void menu_snapshot_rewind_browse_select(MENU_ITEM_PARAMETERS)
{
    //Aplicar ese snapshot
    snapshot_in_ram_load(valor_opcion);

    menu_generic_message_splash("Load Snapshot","OK Snapshot loaded from RAM");
}

void menu_snapshot_rewind_browse(MENU_ITEM_PARAMETERS)
{

    if (snapshots_in_ram_total_elements==0) {
        menu_error_message("Snapshot list empty");
        return;
    }

    menu_item *array_menu_common;
    menu_item item_seleccionado;
    int retorno_menu;
    do {

        //Inicializar el ultimo a 0 siempre
        int snapshot_rewind_browse_opcion_seleccionada=0;

        menu_add_item_menu_inicial(&array_menu_common,"",MENU_OPCION_UNASSIGNED,NULL,NULL);


        int i;
        for (i=0;i<snapshots_in_ram_total_elements;i++) {

            //char buffer_entrada[100];
            int indice=snapshot_in_ram_get_element(i);

             

            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_snapshot_rewind_browse_select,NULL,"%4d: %02d:%02d:%02d",
                i,snapshots_in_ram[indice].hora,snapshots_in_ram[indice].minuto,snapshots_in_ram[indice].segundo);   
            
            menu_add_item_menu_valor_opcion(array_menu_common,i);
        }




        menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

        menu_add_ESC_item(array_menu_common);

        retorno_menu=menu_dibuja_menu(&snapshot_rewind_browse_opcion_seleccionada,&item_seleccionado,array_menu_common,"Browse Snapshots");



        if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
            //llamamos por valor de funcion
            if (item_seleccionado.menu_funcion!=NULL) {
                //printf ("actuamos por funcion\n");
                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);

            }
        }

    } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);   
}

void menu_snapshot_rewind_enable(MENU_ITEM_PARAMETERS)
{
    snapshot_in_ram_enabled.v ^=1;  
}

void menu_snapshot_rewind_interval(MENU_ITEM_PARAMETERS)
{
    menu_ventana_scanf_numero_enhanced("Snapshot interval",&snapshot_in_ram_interval_seconds,3,+1,1,99,0);
}


void menu_snapshot_rewind_maximum(MENU_ITEM_PARAMETERS)
{
    menu_ventana_scanf_numero_enhanced("Maximum snapshots",&snapshots_in_ram_maximum,5,+1,1,MAX_TOTAL_SNAPSHOTS_IN_RAM,0);

    snapshots_in_ram_reset();

    menu_warn_message("Snapshot list has been cleared due to list resize");
}

void menu_snapshot_rewind_timer_timeout(MENU_ITEM_PARAMETERS)
{
    menu_ventana_scanf_numero_enhanced("Rewind timeout",&snapshot_in_ram_enabled_timer_timeout,3,+1,1,99,0);
}


void menu_snapshot_rewind(MENU_ITEM_PARAMETERS)
{
    menu_item *array_menu_common;
    menu_item item_seleccionado;
    int retorno_menu;
    do {



        menu_add_item_menu_inicial_format(&array_menu_common,MENU_OPCION_NORMAL,menu_snapshot_rewind_enable,NULL,"[%c] Enabled",
        (snapshot_in_ram_enabled.v ? 'X' : ' ' ));


        menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_snapshot_rewind_interval,NULL,"[%d] Interval (seconds)",snapshot_in_ram_interval_seconds);

        menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_snapshot_rewind_maximum,NULL,"[%d] Maximum snapshots",snapshots_in_ram_maximum);
        menu_add_item_menu_tooltip(array_menu_common,"Maximum snapshots to keep in memory");
        menu_add_item_menu_ayuda(array_menu_common,"Maximum snapshots to keep in memory. When reached the maximum, the oldest will be deleted");


        menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_snapshot_rewind_timer_timeout,NULL,"[%d] Rewind timeout (seconds)",snapshot_in_ram_enabled_timer_timeout);
        menu_add_item_menu_tooltip(array_menu_common,"After this time pressed rewind action, the rewind position is reset to current");
        menu_add_item_menu_ayuda(array_menu_common,"After this time pressed rewind action, the rewind position is reset to current");
      

        if (snapshot_in_ram_enabled.v) {

            menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);
            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_snapshot_rewind_browse,NULL,"Browse");

        }


        menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

        menu_add_ESC_item(array_menu_common);

        retorno_menu=menu_dibuja_menu(&snapshot_rewind_opcion_seleccionada,&item_seleccionado,array_menu_common,"Snapshots to RAM");



        if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
            //llamamos por valor de funcion
            if (item_seleccionado.menu_funcion!=NULL) {
                //printf ("actuamos por funcion\n");
                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);

            }
        }

    } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);

}





int get_efectivo_tamanyo_find_buffer(void)
{
	if (MACHINE_IS_QL) return QL_MEM_LIMIT+1;
	return 65536;
}



//int menu_find_bytes_total_items=0;


//Indica si esta vacio o no; esto se usa para saber si la busqueda se hace sobre la busqueda anterior o no
int menu_find_bytes_empty=1;

unsigned char *menu_find_bytes_mem_pointer=NULL;
/* Estructura del array de busqueda:
65536 items del array. Cada item es un unsigned char
El valor indica:
0: en esa posicion de la memoria no se encuentra el byte
1: en esa posicion de la memoria si se encuentra el byte
otros valores de momento no tienen significado
*/


void menu_find_bytes_clear_results_process(void)
{
        //inicializamos array
        int i;

        for (i=0;i<get_efectivo_tamanyo_find_buffer();i++) menu_find_bytes_mem_pointer[i]=0;

        menu_find_bytes_empty=1;

}

void menu_find_bytes_clear_results(MENU_ITEM_PARAMETERS)
{
        menu_find_bytes_clear_results_process();

        menu_generic_message("Clear Results","OK. Results cleared");
}

/*
void old_delete_menu_find_bytes_view_results(MENU_ITEM_PARAMETERS)
{

        int index_find,index_buffer;

        char results_buffer[MAX_TEXTO_GENERIC_MESSAGE];

        //margen suficiente para que quepa una linea
        //direccion+salto linea+codigo 0
        char buf_linea[9];

        index_buffer=0;

        int encontrados=0;

        int salir=0;

        for (index_find=0;index_find<get_efectivo_tamanyo_find_buffer() && salir==0;index_find++) {
                if (menu_find_bytes_mem_pointer[index_find]) {
                        sprintf (buf_linea,"%d\n",index_find);
                        sprintf (&results_buffer[index_buffer],"%s\n",buf_linea);
                        index_buffer +=strlen(buf_linea);
                        encontrados++;
                }

                //controlar maximo
                //20 bytes de margen
                if (index_buffer>MAX_TEXTO_GENERIC_MESSAGE-20) {
                        debug_printf (VERBOSE_ERR,"Too many results to show. Showing only the first %d",encontrados);
                        //forzar salir
                        salir=1;
                }

        }

        results_buffer[index_buffer]=0;

        menu_generic_message("View Results",results_buffer);
}
*/

void menu_find_bytes_open_hexviewer(MENU_ITEM_PARAMETERS)
{
    menu_debug_hexdump_direccion=valor_opcion;
    menu_debug_hexdump(0);
}

void menu_find_bytes_view_results(MENU_ITEM_PARAMETERS)
{

    menu_item *array_menu_common;
    menu_item item_seleccionado;
    int retorno_menu;

    int opcion_seleccionada_common=0;
    do {

        menu_add_item_menu_inicial(&array_menu_common,"",MENU_OPCION_UNASSIGNED,NULL,NULL);



        int index_find;

        

        //margen suficiente para que quepa una linea
        //direccion+salto linea+codigo 0
        //char buf_linea[9];

        //index_buffer=0;

        //int encontrados=0;

        int salir=0;

        int total_items=0;

        for (index_find=0;index_find<get_efectivo_tamanyo_find_buffer() && salir==0;index_find++) {
                if (menu_find_bytes_mem_pointer[index_find]) {
                        //sprintf (buf_linea,"%d\n",index_find);
                        //sprintf (&results_buffer[index_buffer],"%s\n",buf_linea);
                        //index_buffer +=strlen(buf_linea);

                        menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_find_bytes_open_hexviewer,NULL,"%d",index_find);
                        menu_add_item_menu_valor_opcion(array_menu_common,index_find);
                        menu_add_item_menu_tooltip(array_menu_common,"Press Enter to open Hexadecimal Editor on this address");
                        menu_add_item_menu_ayuda(array_menu_common,"Press Enter to open Hexadecimal Editor on this address");

                        total_items++;
                        
                }


        }

        if (total_items==0) {
            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,NULL,NULL,"Empty list");
        }

        menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

        menu_add_ESC_item(array_menu_common);

        retorno_menu=menu_dibuja_menu(&opcion_seleccionada_common,&item_seleccionado,array_menu_common,"View results");



        if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
            //llamamos por valor de funcion
            if (item_seleccionado.menu_funcion!=NULL) {
                //printf ("actuamos por funcion\n");
                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);

            }
        }

    } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);
}

//Busqueda desde direccion indicada
int menu_find_bytes_process_from(z80_byte byte_to_find,int inicio)
{
	int dir;
	int total_items_found=0;
	int final_find=get_efectivo_tamanyo_find_buffer();

	//Busqueda con array no inicializado
	if (menu_find_bytes_empty) {

					debug_printf (VERBOSE_INFO,"Starting Search with no previous results");


					//asumimos que no va a encontrar nada
					menu_find_bytes_empty=1;

					for (dir=inicio;dir<final_find;dir++) {
									if (peek_byte_z80_moto(dir)==byte_to_find) {
													menu_find_bytes_mem_pointer[dir]=1;

													//al menos hay un resultado
													menu_find_bytes_empty=0;

													//incrementamos contador de resultados para mostrar al final
													total_items_found++;
									}
					}

	}

	else {
					//Busqueda con array ya con contenido
					//examinar solo las direcciones que indique el array

					debug_printf (VERBOSE_INFO,"Starting Search using previous results");

					//asumimos que no va a encontrar nada
					menu_find_bytes_empty=1;

					int i;
					for (i=0;i<final_find;i++) {
									if (menu_find_bytes_mem_pointer[i]) {
													//Ver el contenido de esa direccion
													if (peek_byte_z80_moto(i)==byte_to_find) {
																	//al menos hay un resultado
																	menu_find_bytes_empty=0;
																	//incrementamos contador de resultados para mostrar al final
																	total_items_found++;
													}
													else {
																	//el byte ya no esta en esa direccion
																	menu_find_bytes_mem_pointer[i]=0;
													}
									}
					}
	}

	return total_items_found;

}

//Busqueda desde direccion 0
int menu_find_bytes_process(z80_byte byte_to_find)
{
	return menu_find_bytes_process_from(byte_to_find,0);
}

//Busqueda desde direccion indicada una lista de bytes
//menu_z80_moto_int dir,int *lista,int total_items
int menu_find_bytes_list_from(int *lista,int total_items,int inicio)
{
	int dir;
	int total_items_found=0;
	int final_find=get_efectivo_tamanyo_find_buffer();

	//Busqueda con array no inicializado
	if (menu_find_bytes_empty) {

					debug_printf (VERBOSE_INFO,"Starting Search with no previous results");


					//asumimos que no va a encontrar nada
					menu_find_bytes_empty=1;

					for (dir=inicio;dir<final_find;dir++) {
                                    if (util_compare_bytes_address(dir,lista,total_items)) {
									//if (peek_byte_z80_moto(dir)==byte_to_find) {
													menu_find_bytes_mem_pointer[dir]=1;

													//al menos hay un resultado
													menu_find_bytes_empty=0;

													//incrementamos contador de resultados para mostrar al final
													total_items_found++;
									}
					}

	}

	else {
					//Busqueda con array ya con contenido
					//examinar solo las direcciones que indique el array

					debug_printf (VERBOSE_INFO,"Starting Search using previous results");

					//asumimos que no va a encontrar nada
					menu_find_bytes_empty=1;

					int i;
					for (i=0;i<final_find;i++) {
									if (menu_find_bytes_mem_pointer[i]) {
													//Ver el contenido de esa direccion
                                                    if (util_compare_bytes_address(i,lista,total_items)) {
													//if (peek_byte_z80_moto(i)==byte_to_find) {
																	//al menos hay un resultado
																	menu_find_bytes_empty=0;
																	//incrementamos contador de resultados para mostrar al final
																	total_items_found++;
													}
													else {
																	//el byte ya no esta en esa direccion
																	menu_find_bytes_mem_pointer[i]=0;
													}
									}
					}
	}

	return total_items_found;

}

//Antiguo para buscar 1 solo byte
void old_delete_menu_find_bytes_find(MENU_ITEM_PARAMETERS)
{

        //Buscar en la memoria direccionable (0...65535) si se encuentra el byte
        z80_byte byte_to_find;


        char string_find[4];

        sprintf (string_find,"0");

        menu_ventana_scanf("Find byte",string_find,4);

        int valor_find=parse_string_to_number(string_find);

        if (valor_find<0 || valor_find>255) {
                debug_printf (VERBOSE_ERR,"Invalid value %d",valor_find);
                return;
        }


        byte_to_find=valor_find;


        int total_items_found;

				total_items_found=menu_find_bytes_process(byte_to_find);

        menu_generic_message_format("Find","Total addresses found: %d",total_items_found);


}

//Para buscar mas de 1 byte separado por espacio
void menu_find_bytes_find(MENU_ITEM_PARAMETERS)
{

    //maximos bytes a buscar
    #define MAX_BYTES_FIND 30

    #define MAX_STRING_FIND_BUFFER (MAX_BYTES_FIND*4)
    
    int lista[MAX_BYTES_FIND];

    //Buscar en la memoria direccionable (0...65535) si se encuentran los bytes indicados
    //z80_byte byte_to_find;


    char string_find[MAX_STRING_FIND_BUFFER];

    string_find[0]=0;

    menu_ventana_scanf("Values space separated",string_find,MAX_STRING_FIND_BUFFER);

    //Si cadena vacia, no hacer nada
    if (string_find[0]==0) return;

    //ir procesando cada valor
    int i;

    //int longitud=strlen(string_find);

    //indice al string 
    int indice_numero=0;

    int total_numeros=0;

    int salir=0;

    i=0;

    //for (i=0;i<longitud;i++) {
    while (!salir) {
        if (string_find[i]==0) salir=1;

        if (string_find[i]==' ' || string_find[i]==0) {

            if (total_numeros==MAX_BYTES_FIND) {
                menu_error_message("Maximum bytes in list reached");
                return;
            }

            string_find[i]=0;
            int valor_find=parse_string_to_number(&string_find[indice_numero]);

            lista[total_numeros]=valor_find;
            //printf("numero: %d\n",valor_find);

            indice_numero=i+1;
            total_numeros++;

        }

        i++;
    }



    int total_items_found;

    //total_items_found=menu_find_bytes_process(byte_to_find);

    total_items_found=menu_find_bytes_list_from(lista,total_numeros,0);

    menu_generic_message_format("Find","Total addresses found: %d",total_items_found);


}
//int total_tamanyo_find_buffer=0;

void menu_find_bytes_alloc_if_needed(void)
{
	//Si puntero memoria no esta asignado, asignarlo, o si hemos cambiado de tipo de maquina
	if (menu_find_bytes_mem_pointer==NULL) {

					//65536 elementos del array, cada uno de tamanyo unsigned char
					//total_tamanyo_find_buffer=get_total_tamanyo_find_buffer();

					menu_find_bytes_mem_pointer=malloc(QL_MEM_LIMIT+1); //Asignamos el maximo (maquina QL)
					if (menu_find_bytes_mem_pointer==NULL) cpu_panic("Error allocating find array");

					//inicializamos array
					int i;
					for (i=0;i<get_efectivo_tamanyo_find_buffer();i++) menu_find_bytes_mem_pointer[i]=0;
	}
}

void menu_find_bytes(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_find_bytes;
        menu_item item_seleccionado;
        int retorno_menu;

        //Si puntero memoria no esta asignado, asignarlo, o si hemos cambiado de tipo de maquina
        menu_find_bytes_alloc_if_needed();


        do {

                menu_add_item_menu_inicial_format(&array_menu_find_bytes,MENU_OPCION_NORMAL,menu_find_bytes_find,NULL,"Find bytes");
                menu_add_item_menu_tooltip(array_menu_find_bytes,"Find several byte on memory");
                menu_add_item_menu_ayuda(array_menu_find_bytes,"Find some bytes on the 64 KB of mapped memory, considering the last address found (if any).\n"
                        "It can also be used to find POKEs, it's very easy: \n"
                        "I first recommend to disable Multitasking menu, to avoid losing lives where in the menu.\n"
                        "As an example, you are in a game with 4 lives. Enter find byte "
                        "with value 4. It will find a lot of addresses, don't panic.\n"
                        "Then, you must lose one live, you have now 3. Then you must search for byte with value 3; "
                        "the search will be made considering the last search results. Normally here you will find only "
                        "one address with value 3. At this moment you know the address where the lives are stored.\n"
                        "The following to find, for example, infinite lives, is to search where this life value is decremented. "
                        "You can find it by making a MRA breakpoint to the address where the lives are stored, or a condition breakpoint "
			"(NN)=value, setting NN to the address where lives are stored, and value to the desired number of lives, for example: (51308)=2.\n"
                        "When the breakpoint is caught, you will probably have the section of code where the lives are decremented ;) ");

                menu_add_item_menu_format(array_menu_find_bytes,MENU_OPCION_NORMAL,menu_find_bytes_view_results,NULL,"View results");
                menu_add_item_menu_tooltip(array_menu_find_bytes,"View results");
                menu_add_item_menu_ayuda(array_menu_find_bytes,"View results");

                menu_add_item_menu_format(array_menu_find_bytes,MENU_OPCION_NORMAL,menu_find_bytes_clear_results,NULL,"Clear results");
                menu_add_item_menu_tooltip(array_menu_find_bytes,"Clear results");
                menu_add_item_menu_ayuda(array_menu_find_bytes,"Clear results");




                menu_add_item_menu(array_menu_find_bytes,"",MENU_OPCION_SEPARADOR,NULL,NULL);


                menu_add_ESC_item(array_menu_find_bytes);

                retorno_menu=menu_dibuja_menu(&find_bytes_opcion_seleccionada,&item_seleccionado,array_menu_find_bytes,"Find bytes" );

                

                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);
}





/*
Busqueda de contador de vidas.
Estados: 0. Inicial. Se indica vidas actuales. Se realiza busqueda en toda memoria con ese valor
Estados: 1. Ya se ha indicado vidas iniciales. Se puede indicar vidas actuales. Se realiza busqueda en toda memoria. Si se encuentra 1 solo valor, se pasa a estado 2.
Se puede pasar a estado 0 con "Restart"

Estados: 2. Ya se ha encontrado contador vidas. Se muestra direccion. Se puede pasar a estado 0 con "Restart"

*/

int menu_find_lives_state=0;

//Puntero a memoria de spectrum que dice donde esta el contador de vidas
z80_int menu_find_lives_pointer=0;

//Ultimo valor buscado
int lives_to_find=3;


void menu_find_lives_restart(MENU_ITEM_PARAMETERS)
{
	menu_find_lives_state=0;
}

void menu_find_lives_initial(MENU_ITEM_PARAMETERS)
{
	//Limpiar resultados
	menu_find_bytes_alloc_if_needed();
	if (menu_find_lives_state==0) menu_find_bytes_clear_results_process();

	//Suponemos que la segunda vez habra perdido al menos 1 vida
	if (menu_find_lives_state==1 && lives_to_find>0) lives_to_find--;

	//Pedir vidas actuales
	//Buscar en la memoria direccionable (0...65535) si se encuentra el byte


	char string_find[4];

	sprintf (string_find,"%d",lives_to_find);

	menu_ventana_scanf("Current lives",string_find,4);

	int valor_find=parse_string_to_number(string_find);

	if (valor_find<0 || valor_find>255) {
					debug_printf (VERBOSE_ERR,"Invalid value %d",valor_find);
					return;
	}


	lives_to_find=valor_find;


	int total_items_found;

	//Empezar a buscar desde la 16384. No tiene sentido buscar desde la rom
	total_items_found=menu_find_bytes_process_from(lives_to_find,16384);

	//menu_generic_message_format("Find","Total addresses found: %d",total_items_found);

	//Si estamos en estado 0
	if (menu_find_lives_state==0) {
		if (total_items_found==0) {
			 menu_generic_message("Find lives","Sorry, no lives counter found");
		}
		else {
			menu_generic_message("Find lives","Ok. Continue playing game and come back when you lose a life");
			menu_find_lives_state=1;
		}
	}

	//Si estamos en estado 1
	else if (menu_find_lives_state==1) {
		if (total_items_found==0) {
			menu_generic_message("Find lives","Sorry, I haven't found any addresses. The process has been restarted");
			menu_find_lives_state=0;
		}
		else if (total_items_found!=1) {
			 menu_generic_message("Find lives","Sorry, no unique address found. You may want to try again losing another live or maybe manually find it on the Find bytes menu");
		}
		else {

			//Buscar la direccion
			int index_find;

			int salir=0;

			for (index_find=0;index_find<get_efectivo_tamanyo_find_buffer() && salir==0;index_find++) {
							if (menu_find_bytes_mem_pointer[index_find]) {
											menu_find_lives_pointer=index_find;
											salir=0;
							}
			}


			menu_find_lives_state=2;

			menu_generic_message("Find lives","Great. Memory pointer found");
		}
	}



	//Buscar bytes

}


//Ultimo valor de vidas seleccionadas
z80_byte ultimo_menu_find_lives_set=9;

void menu_find_lives_set(MENU_ITEM_PARAMETERS)
{


	char string_lives[4];

	sprintf (string_lives,"%d",ultimo_menu_find_lives_set);

	menu_ventana_scanf("Lives?",string_lives,4);

	int valor_lives=parse_string_to_number(string_lives);

	if (valor_lives<0 || valor_lives>255) {
					debug_printf (VERBOSE_ERR,"Invalid value %d",valor_lives);
					return;
	}

	ultimo_menu_find_lives_set=valor_lives;

	poke_byte_z80_moto(menu_find_lives_pointer,valor_lives);

}

void menu_find_lives(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_find_lives;
        menu_item item_seleccionado;
        int retorno_menu;




        do {

								if (menu_find_lives_state==0) {
                	menu_add_item_menu_inicial_format(&array_menu_find_lives,MENU_OPCION_NORMAL,menu_find_lives_initial,NULL,"Tell current lives (initial)");
								}

								if (menu_find_lives_state==1) {
									menu_add_item_menu_inicial_format(&array_menu_find_lives,MENU_OPCION_NORMAL,menu_find_lives_initial,NULL,"Tell current lives (decr.)");
								}

								if (menu_find_lives_state==2) {
									menu_add_item_menu_inicial_format(&array_menu_find_lives,MENU_OPCION_NORMAL,NULL,NULL,"Lives pointer: %d",menu_find_lives_pointer);
									menu_add_item_menu_format(array_menu_find_lives,MENU_OPCION_NORMAL,NULL,NULL,"Lives: %d",peek_byte_z80_moto(menu_find_lives_pointer) );
									menu_add_item_menu_format(array_menu_find_lives,MENU_OPCION_NORMAL,menu_find_lives_set,NULL,"Set lives");
								}

								if (menu_find_lives_state==1 || menu_find_lives_state==2) {
									menu_add_item_menu_format(array_menu_find_lives,MENU_OPCION_NORMAL,menu_find_lives_restart,NULL,"Restart process");
								}

                menu_add_item_menu(array_menu_find_lives,"",MENU_OPCION_SEPARADOR,NULL,NULL);


                menu_add_ESC_item(array_menu_find_lives);

                retorno_menu=menu_dibuja_menu(&find_lives_opcion_seleccionada,&item_seleccionado,array_menu_find_lives,"Find lives" );

                

                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);
}


void menu_find(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_find;
        menu_item item_seleccionado;
        int retorno_menu;




        do {

                menu_add_item_menu_inicial_format(&array_menu_find,MENU_OPCION_NORMAL,menu_find_bytes,NULL,"Find bytes");
                menu_add_item_menu_tooltip(array_menu_find,"Find several bytes on memory");
                menu_add_item_menu_ayuda(array_menu_find,"Find several bytes on the 64 KB of mapped memory, considering the last address found (if any)");

								menu_add_item_menu_format(array_menu_find,MENU_OPCION_NORMAL,menu_find_lives,NULL,"Find lives address");
                menu_add_item_menu_tooltip(array_menu_find,"Find memory pointer where lives are located");
                menu_add_item_menu_ayuda(array_menu_find,"Find memory pointer where lives are located)");


                menu_add_item_menu(array_menu_find,"",MENU_OPCION_SEPARADOR,NULL,NULL);


                menu_add_ESC_item(array_menu_find);

                retorno_menu=menu_dibuja_menu(&find_opcion_seleccionada,&item_seleccionado,array_menu_find,"Find" );

                

                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);
}


void menu_debug_view_basic_variables(MENU_ITEM_PARAMETERS)
{

    menu_first_aid("debug_variables");

    char *results_buffer=util_malloc_max_texto_generic_message("Can not allocate memory for showing variables");

	debug_view_basic_variables(results_buffer,MAX_TEXTO_GENERIC_MESSAGE);

    menu_generic_message_format("Basic Variables","%s",results_buffer);

    free(results_buffer);
}

//Indica a la funcion de overlay cual es la ventana
zxvision_window *menu_debug_view_sensors_overlay_window;

//Contador de segundo para hacer que el overlay solo se redibuje un numero de veces por segundo y no siempre
int menu_debug_view_sensors_contador_segundo_anterior;



//TODO esto para hacer una prueba rapida. finalmente esto se hara guardando el short_name de cada sensor
int temporal_current_view_sensors_actual=0;

//Usado para el meter de tipo volumen
//int menu_debug_view_sensors_valor_anterior=0;

int menu_debug_view_sensors_tipo=0;

#define MENU_VIEW_SENSORS_START_X 1
#define MENU_VIEW_SENSORS_START_Y 3

//array de sensores en pantalla

#define MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS 16
#define MENU_SENSORS_SEPARACION_ENTRE_FILAS 10

menu_debug_view_sensors_list menu_debug_view_sensors_list_sensors[MENU_VIEW_SENSORS_TOTAL_ELEMENTS]={
    {"",MENU_SENSORS_SEPARACION_ENTRE_FILAS*0,MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS*0,0,0},
    {"",MENU_SENSORS_SEPARACION_ENTRE_FILAS*0,MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS*1,0,0},
    {"",MENU_SENSORS_SEPARACION_ENTRE_FILAS*0,MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS*2,0,0},
    {"",MENU_SENSORS_SEPARACION_ENTRE_FILAS*0,MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS*3,0,0},
    {"",MENU_SENSORS_SEPARACION_ENTRE_FILAS*0,MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS*4,0,0},

    {"",MENU_SENSORS_SEPARACION_ENTRE_FILAS*1,MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS*0,0,0},
    {"",MENU_SENSORS_SEPARACION_ENTRE_FILAS*1,MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS*1,0,0},
    {"",MENU_SENSORS_SEPARACION_ENTRE_FILAS*1,MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS*2,0,0},
    {"",MENU_SENSORS_SEPARACION_ENTRE_FILAS*1,MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS*3,0,0},
    {"",MENU_SENSORS_SEPARACION_ENTRE_FILAS*1,MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS*4,0,0},

    {"",MENU_SENSORS_SEPARACION_ENTRE_FILAS*2,MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS*0,0,0},
    {"",MENU_SENSORS_SEPARACION_ENTRE_FILAS*2,MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS*1,0,0},
    {"",MENU_SENSORS_SEPARACION_ENTRE_FILAS*2,MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS*2,0,0},
    {"",MENU_SENSORS_SEPARACION_ENTRE_FILAS*2,MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS*3,0,0},
    {"",MENU_SENSORS_SEPARACION_ENTRE_FILAS*2,MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS*4,0,0},        

};

int menu_view_sensors_cursor_fila=0;
int menu_view_sensors_cursor_columna=0;
int menu_view_sensors_cursor_visible=0;

void menu_debug_view_sensors_print_cursor(zxvision_window *ventana)
{
    
    int fila=menu_view_sensors_cursor_fila;
    int columna=menu_view_sensors_cursor_columna;

    /*
    puntos del cuadrado:

      x1,y1      x2,y1
       -----------
       |         |
       |         |
       -----------
      x1,y2      x2,y2
    */

    int x1=(MENU_VIEW_SENSORS_START_X+columna* MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS)*menu_char_width-1; //-1 para que no roce por la izquierda con el texto
    int y1=(MENU_VIEW_SENSORS_START_Y-1+fila * MENU_SENSORS_SEPARACION_ENTRE_FILAS)   *8;

    int x2=(MENU_VIEW_SENSORS_START_X+(columna+1)* MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS)*menu_char_width-1; //-1 para que no toque el pixel siguiente
    int y2=(MENU_VIEW_SENSORS_START_Y-2+(fila+1) * MENU_SENSORS_SEPARACION_ENTRE_FILAS)   *8-1; //-1 para que no toque el pixel siguiente

    //arriba
    zxvision_draw_line(ventana,x1,y1,x2,y1,ESTILO_GUI_TINTA_NORMAL,zxvision_putpixel);
    //abajo
    zxvision_draw_line(ventana,x1,y2,x2,y2,ESTILO_GUI_TINTA_NORMAL,zxvision_putpixel);
    //izquierda
    zxvision_draw_line(ventana,x1,y1,x1,y2,ESTILO_GUI_TINTA_NORMAL,zxvision_putpixel);
    //derecha
    zxvision_draw_line(ventana,x2,y1,x2,y2,ESTILO_GUI_TINTA_NORMAL,zxvision_putpixel);



/*
    //Rellenar cuadrado de color del cursor
    //Nota: no puedo rellenar todo el texto simplemente con lineas porque esto ocultaria el texto del sensor,
    //pues al hacer render de pantalla siempre primero se escribe el texto y luego la rutina de overlay (o sea esta)
    //Parte de arriba hasta texto. 8 pixeles de alto
    franja_color_y_inicio=y1+1;
    for (i=franja_color_y_inicio;i<=franja_color_y_inicio+6;i++) {        
        zxvision_draw_line(ventana,x1+1,i,x2-1,i,ESTILO_GUI_PAPEL_SELECCIONADO,zxvision_putpixel);
    }      

    //Parte desde abajo del texto incluyendo sensor
    franja_color_y_inicio=y1+16;
    for (i=franja_color_y_inicio;i<=y2-1;i++) {        
        zxvision_draw_line(ventana,x1+1,i,x2-1,i,ESTILO_GUI_PAPEL_SELECCIONADO,zxvision_putpixel);
    }    

    //Si sensor vacio, si que dibujamos esa franja
    int offset_array=menu_view_sensors_cursor_fila*MENU_VIEW_SENSORS_TOTAL_COLUMNS+menu_view_sensors_cursor_columna;

    if (menu_debug_view_sensors_list_sensors[offset_array].short_name[0]==0) {
        franja_color_y_inicio=y1+8;
        for (i=franja_color_y_inicio;i<=franja_color_y_inicio+7;i++) {        
            zxvision_draw_line(ventana,x1+1,i,x2-1,i,ESTILO_GUI_PAPEL_SELECCIONADO,zxvision_putpixel);
        }            
    }   
    */  

}



//La funcion de overlay
void menu_debug_view_sensors_overlay_window_overlay(void)
{
    if (!zxvision_drawing_in_background) normal_overlay_texto_menu();

    menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech

    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_debug_view_sensors_overlay_window->is_minimized) return; //Sustituir xxxx_overlay_window por lo que convenga  

    //printf("overlay view sensors %d\n",contador_segundo);  

    zxvision_window *ventana;

    ventana=menu_debug_view_sensors_overlay_window;    



    //esto hara ejecutar esto 2 veces por segundo
    if ( ((contador_segundo%500) == 0 && menu_debug_view_sensors_contador_segundo_anterior!=contador_segundo) ) {

        menu_debug_view_sensors_contador_segundo_anterior=contador_segundo;
        //printf ("Refrescando. contador_segundo=%d\n",contador_segundo);

              

    }

    if (menu_view_sensors_cursor_visible) menu_debug_view_sensors_print_cursor(ventana);    


    int fila_texto;
    int columna_texto;


    int fila,columna;

    for (fila=0;fila<MENU_VIEW_SENSORS_TOTAL_ROWS;fila++) {
        for (columna=0;columna<MENU_VIEW_SENSORS_TOTAL_COLUMNS;columna++) {
            int offset_array=fila*MENU_VIEW_SENSORS_TOTAL_COLUMNS+columna;

            fila_texto=MENU_VIEW_SENSORS_START_Y+menu_debug_view_sensors_list_sensors[offset_array].fila;
            columna_texto=MENU_VIEW_SENSORS_START_X+menu_debug_view_sensors_list_sensors[offset_array].columna;

            char *short_name;
            //temporal esto hacerlo luego mejor
            short_name=menu_debug_view_sensors_list_sensors[offset_array].short_name; 
            int tipo=menu_debug_view_sensors_list_sensors[offset_array].tipo;   
            int valor_en_vez_de_perc=menu_debug_view_sensors_list_sensors[offset_array].valor_en_vez_de_perc;

            
            int tinta_texto=ESTILO_GUI_TINTA_NORMAL;
            int papel_texto=ESTILO_GUI_PAPEL_NORMAL;         

            //Cambio color si cursor ahi
            if (fila==menu_view_sensors_cursor_fila && columna==menu_view_sensors_cursor_columna && menu_view_sensors_cursor_visible) {
                //texto en color inverso si esta el cursor ahi
                tinta_texto=ESTILO_GUI_TINTA_SELECCIONADO;
                papel_texto=ESTILO_GUI_PAPEL_SELECCIONADO;

                /*int i,j;
                for (j=0;j<MENU_SENSORS_SEPARACION_ENTRE_FILAS-1;j++) {
                    for (i=0;i<MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS;i++) {
                        zxvision_print_char_simple(ventana,columna_texto+i,fila_texto+j-1,tinta_texto,papel_texto,0,'X');
                    }                
                }
                */
            }               

            if (short_name[0]) {

                zxvision_widgets_draw_metter_common_by_shortname
                    (ventana,columna_texto,fila_texto,short_name,tipo,valor_en_vez_de_perc,tinta_texto,papel_texto,
                    MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS);            
            }


        }
    }


    



    //Siempre hará el dibujado de contenido para evitar que cuando esta en background, otra ventana por debajo escriba algo,
    //y entonces como esta no redibuja siempre, al no escribir encima, se sobreescribe este contenido con el de otra ventana
    //En ventanas que no escriben siempre su contenido, siempre deberia estar zxvision_draw_window_contents que lo haga siempre
    zxvision_draw_window_contents(ventana);
}

//La ventana tal cual que creamos. Es la estructura, no un puntero
zxvision_window zxvision_window_view_sensors;




int menu_debug_view_sensors_get_sensor_tipo(int tipo)
{
    int opcion_seleccionada=tipo;

    menu_item *array_menu_common;
    menu_item item_seleccionado;
    int retorno_menu;
    

    menu_add_item_menu_inicial(&array_menu_common,"",MENU_OPCION_UNASSIGNED,NULL,NULL);

    int i;

    for (i=0;i<ZXVISION_TOTAL_WIDGET_TYPES;i++) {
        menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,NULL,NULL,zxvision_widget_types_names[i]);
    }



    menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);
    
    menu_add_ESC_item(array_menu_common);

    retorno_menu=menu_dibuja_menu(&opcion_seleccionada,&item_seleccionado,array_menu_common,"Meter Type" );



    if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
        //Si se pulsa Enter
        return opcion_seleccionada;
    }

    return -1;   
}

//Retorna:
//0 si selecciona vacio
//1... si selecciona un sensor
//-1 si sale con ESC
int menu_debug_view_sensors_get_sensor_item(int sensor_id)
{
        

    int opcion_seleccionada=sensor_id;

    menu_item *array_menu_common;
    menu_item item_seleccionado;
    int retorno_menu;
    

    menu_add_item_menu_inicial_format(&array_menu_common,MENU_OPCION_NORMAL,NULL,NULL,"(Empty)");    

    int i;
    for (i=0;i<TOTAL_SENSORS;i++) {

        menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,NULL,NULL,sensors_array[i].long_name);
        //menu_add_item_menu_tooltip(array_menu_common,"Sensors that return times, they are expressed in microseconds");
        menu_add_item_menu_ayuda(array_menu_common,
            "Sensors may be type:\n"
            "- A natural value, like FPS, Render time, or Volume of an Audio Chip Channel\n"
            "- A percentage value, like %CPU usage\n"
            "\n"
            "Sensors that return times, they are expressed in microseconds\n"
            "Some sensors will change its colour to a warning colour (usually red) when they are beyond normal values\n"
            "\n"
            "Sensors can be shown on the window by the sensor value or a calculated percentage, for example:\n"
            "If a sensor returns time in microseconds, and the sensor is 10000, the calculated percentage of a total 20000, will be 50%\n"
            "These sensors which are naturally a percentage value (like %CPU usage) showing the absolute value or a calculated percentage, "
            "will show exactly the same value (which is totally logic by the way)"   
            );

    }


    menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);
    
    menu_add_ESC_item(array_menu_common);

    retorno_menu=menu_dibuja_menu(&opcion_seleccionada,&item_seleccionado,array_menu_common,"Sensors" );



    if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
        //Si se pulsa Enter
        return opcion_seleccionada;
    }

    return -1;

}


void menu_view_sensors_fondo_cursor(zxvision_window *ventana,int tinta,int papel)
{

    int offset_array=menu_view_sensors_cursor_fila*MENU_VIEW_SENSORS_TOTAL_COLUMNS+menu_view_sensors_cursor_columna;

    int fila_texto_cursor,columna_texto_cursor;
    //Rellenar color fondo donde esta cursor
    fila_texto_cursor=MENU_VIEW_SENSORS_START_Y+menu_debug_view_sensors_list_sensors[offset_array].fila;
    columna_texto_cursor=MENU_VIEW_SENSORS_START_X+menu_debug_view_sensors_list_sensors[offset_array].columna;


    int i,j;
    for (j=0;j<MENU_SENSORS_SEPARACION_ENTRE_FILAS-1;j++) {
        for (i=0;i<MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS;i++) {
            zxvision_print_char_simple(ventana,columna_texto_cursor+i,fila_texto_cursor+j-1,
                    tinta,papel,0,' ');
        }                
    }
}

int menu_view_sensors_mouse_in_zone_widgets(int *columna,int *fila)
{
    int cursor_mouse_y=menu_mouse_y;
    //empieza dentro de ventana en la 1
    cursor_mouse_y--;

    int cursor_mouse_x=menu_mouse_x;

    cursor_mouse_x -=MENU_VIEW_SENSORS_START_X;
    cursor_mouse_y -=(MENU_VIEW_SENSORS_START_Y-1); //-1 porque el cursor esta 1 fila por encima

    if (cursor_mouse_x>=0 && cursor_mouse_y>=0) {

        //Ajustar a que widget apuntamos
        cursor_mouse_x /=MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS;
        cursor_mouse_y /=MENU_SENSORS_SEPARACION_ENTRE_FILAS;

        //printf("widget %d %d\n",cursor_mouse_x,cursor_mouse_y);

        if (cursor_mouse_x>=0 && cursor_mouse_x<MENU_VIEW_SENSORS_TOTAL_COLUMNS &&
            cursor_mouse_y>=0 && cursor_mouse_y<MENU_VIEW_SENSORS_TOTAL_ROWS) {
                //printf("en rango\n");

                //movemos cursor
                if (columna!=NULL) *columna=cursor_mouse_x;
                if (fila!=NULL) *fila=cursor_mouse_y;

                return 1;
            }
    }   

    return 0; 
}

void menu_debug_view_sensors(MENU_ITEM_PARAMETERS)
{

    menu_espera_no_tecla();
	menu_reset_counters_tecla_repeticion();

    if (!menu_multitarea) {
        menu_warn_message("This window needs multitask enabled");
        return;
    }

    //Nuestro puntero apunta a la estructura que hay fuera, por comodidad de usar el nombre de puntero "ventana"
    zxvision_window *ventana;
    ventana=&zxvision_window_view_sensors;    

    //IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
    //si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
    //la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
    zxvision_delete_window_if_exists(ventana);    

    int x_ventana,y_ventana,ancho_ventana,alto_ventana,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;

    //Recuperar geometria
    if (!util_find_window_geometry("viewsensors",&x_ventana,&y_ventana,&ancho_ventana,&alto_ventana,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
        alto_ventana=MENU_VIEW_SENSORS_TOTAL_ROWS*MENU_SENSORS_SEPARACION_ENTRE_FILAS+MENU_VIEW_SENSORS_START_Y;
        ancho_ventana=MENU_VIEW_SENSORS_TOTAL_COLUMNS*MENU_SENSORS_SEPARACION_ENTRE_COLUMNAS+MENU_VIEW_SENSORS_START_X+1;
        
        x_ventana=scr_get_menu_width()-ancho_ventana; //Al ser tan ancho no cabe centrado. Hacemos que quede pegado a la derecha 
        y_ventana=menu_center_y()-alto_ventana/2; 

        
    }   

    //printf("%d %d %d %d\n",x_ventana,y_ventana,ancho_ventana,alto_ventana); 

    //Crear ventana
	//zxvision_new_window(ventana,x_ventana,y_ventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,"View Sensors");

    zxvision_new_window_gn_cim(ventana,x_ventana,y_ventana,ancho_ventana,alto_ventana,ancho_ventana-1,alto_ventana-2,"View Sensors","viewsensors",
        is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);                            

    //Se puede ir a background
    ventana->can_be_backgrounded=1;
    //indicar nombre del grabado de geometria
    //strcpy(ventana->geometry_name,"viewsensors");
    //Permitir hotkeys desde raton. Parece que incompatible con pulsar boton y simular enter
    //ventana->can_mouse_send_hotkeys=1;    
    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;    

    //decimos que tiene que borrar fondo cada vez al redibujar
    //por tanto es como decirle que no use cache de putchar
    //dado que el fondo de texto es casi todo texto con caracter " " eso borra los pixeles que metemos con overlay del frame anterior
    ventana->must_clear_cache_on_draw=1;    

    //Y dibujar la ventana
    zxvision_draw_window(ventana);


    menu_debug_view_sensors_overlay_window=ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui

    //Cambiamos funcion overlay de texto de menu
    set_menu_overlay_function(menu_debug_view_sensors_overlay_window_overlay);

    //Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
    //Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
    if (zxvision_currently_restoring_windows_on_start) {
        //printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
        return;
    }    


    menu_view_sensors_cursor_visible=1;

    z80_byte tecla;

    //int antes_mouse_left=0;

    int antes_menu_mouse_x=menu_mouse_x;
    int antes_menu_mouse_y=menu_mouse_y;

    //Y esperar escape (2) o tecla background (3)
    do {

                //borrar rastros de textos anteriores
        zxvision_cls(ventana);

        //Forzar a mostrar atajos
		z80_bit antes_menu_writing_inverse_color;
		antes_menu_writing_inverse_color.v=menu_writing_inverse_color.v;
		menu_writing_inverse_color.v=1;

        zxvision_print_string_defaults(ventana,1,0,"Move: Cursors. ~~E~~n~~t~~e~~r: Select Sensor. ~~Type. ~~Abs/Perc");

        //Restaurar comportamiento atajos
		menu_writing_inverse_color.v=antes_menu_writing_inverse_color.v;        

        char *short_name;
        int menu_debug_view_sensors_tipo;

        //menu_debug_view_sensors_print_cursor(ventana,menu_view_sensors_cursor_fila,menu_view_sensors_cursor_columna);

        
            int offset_array=menu_view_sensors_cursor_fila*MENU_VIEW_SENSORS_TOTAL_COLUMNS+menu_view_sensors_cursor_columna;

            menu_view_sensors_fondo_cursor(ventana,ESTILO_GUI_TINTA_SELECCIONADO,ESTILO_GUI_PAPEL_SELECCIONADO);
            
       
            tecla=zxvision_common_getkey_refresh();
            zxvision_handle_cursors_pgupdn(ventana,tecla);

            //printf("mouse_left: %d tecla: %d\n",mouse_left,tecla);
         

            //Si se pulsa boton y esta en rango
            if (mouse_left && tecla==0 && menu_view_sensors_mouse_in_zone_widgets(NULL,NULL) ) {
                //printf("pulsado left\n");
                //menu_espera_no_tecla();
                tecla=13;
            }

            //printf("mouse %d %d\n",menu_mouse_x,menu_mouse_y);

            //antes_mouse_left=mouse_left;

            //gestionar movimiento cursor
            //Solo si se ha movido
            if (antes_menu_mouse_x!=menu_mouse_x || antes_menu_mouse_y!=menu_mouse_y) {
                //printf("mouse movido\n");

                int cursor_mouse_x,cursor_mouse_y;

                if (menu_view_sensors_mouse_in_zone_widgets(&cursor_mouse_x,&cursor_mouse_y)) {
                    //movemos cursor
                    menu_view_sensors_cursor_columna=cursor_mouse_x;
                    menu_view_sensors_cursor_fila=cursor_mouse_y;
                }

               
            }

            antes_menu_mouse_x=menu_mouse_x;
            antes_menu_mouse_y=menu_mouse_y;

            switch(tecla) {
                case 8:
                    if (menu_view_sensors_cursor_columna>0) menu_view_sensors_cursor_columna--;
                break;

                case 9:
                    if (menu_view_sensors_cursor_columna<MENU_VIEW_SENSORS_TOTAL_COLUMNS-1) menu_view_sensors_cursor_columna++;
                break;

                case 11:
                    if (menu_view_sensors_cursor_fila>0) menu_view_sensors_cursor_fila--;
                break;

                case 10:
                    if (menu_view_sensors_cursor_fila<MENU_VIEW_SENSORS_TOTAL_ROWS-1) menu_view_sensors_cursor_fila++;
                break;        

                case 13:
                    
                    //necesario cuando viene de pulsar boton izquierdo con raton
                    menu_espera_no_tecla();

                    //buscar el id para ese nombre de sensor
                    short_name=menu_debug_view_sensors_list_sensors[offset_array].short_name;
                    int sensor_id;

                    

                    //estaba vacio. asignar
                    if (short_name[0]==0) {
                        sensor_id=0;
                    }
                    else {
                        sensor_id=sensor_find(short_name);
                        sensor_id++;
                        //invalido
                        if (sensor_id<0) sensor_id=0;                        
                    }

                    sensor_id=menu_debug_view_sensors_get_sensor_item(sensor_id);

                    if (sensor_id>=0) {
                        if (sensor_id==0) {
                            //vacio
                            strcpy(menu_debug_view_sensors_list_sensors[offset_array].short_name,"");
                        }
                        else {
                            //indice-1
                            sensor_id--;
                            short_name=sensors_array[sensor_id].short_name;
                            strcpy(menu_debug_view_sensors_list_sensors[offset_array].short_name,short_name);                            
                        }
                    }

                break;

                case 't':
                    menu_debug_view_sensors_tipo=menu_debug_view_sensors_list_sensors[offset_array].tipo;

                    menu_debug_view_sensors_tipo=menu_debug_view_sensors_get_sensor_tipo(menu_debug_view_sensors_tipo);

                    //menu_debug_view_sensors_tipo++;
                    //if (menu_debug_view_sensors_tipo>=ZXVISION_TOTAL_WIDGET_TYPES) menu_debug_view_sensors_tipo=0;

                    if (menu_debug_view_sensors_tipo>=0) menu_debug_view_sensors_list_sensors[offset_array].tipo=menu_debug_view_sensors_tipo;
                break;

                case 'a':
                    menu_debug_view_sensors_list_sensors[offset_array].valor_en_vez_de_perc ^=1;
                    if (menu_debug_view_sensors_list_sensors[offset_array].valor_en_vez_de_perc) {
                        menu_generic_message_splash("Display value","OK Showing absolute value instead of percentage");
                    }
                    else {
                        menu_generic_message_splash("Display percentage","OK Showing percentage instead of absolute value");
                    }

                break;


            }
            //printf ("tecla: %d\n",tecla);
    } while (tecla!=2 && tecla!=3);


    
    //menu_debug_view_sensors_clear_cursor(ventana,menu_view_sensors_cursor_fila,menu_view_sensors_cursor_columna);
    menu_view_sensors_cursor_visible=0;

    //borrar fondo cursor
    menu_view_sensors_fondo_cursor(ventana,ESTILO_GUI_TINTA_NORMAL,ESTILO_GUI_PAPEL_NORMAL);


    //Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
    zxvision_set_window_overlay_from_current(ventana);

    //restauramos modo normal de texto de menu
    set_menu_overlay_function(normal_overlay_texto_menu);


    cls_menu_overlay();
    util_add_window_geometry_compact(ventana);

    if (tecla==3) {
    //if (retorno_menu==MENU_RETORNO_BACKGROUND) {
            zxvision_message_put_window_background();
    }

    else {
            zxvision_destroy_window(ventana);
    }


}

















#define VISUALREALTAPE_X (menu_origin_x())
#define VISUALREALTAPE_Y 2
#define VISUALREALTAPE_ANCHO 32
#define VISUALREALTAPE_ALTO 20





//Usado dentro del overlay de waveform, para mostrar dos veces por segundo el texto que average, etc
int menu_visual_realtape_valor_contador_segundo_anterior;


zxvision_window *menu_audio_visual_realtape_window;

//offsets donde empieza y acaba bloque actual
long int menu_visual_realtape_bloque_posicion_inicio=-1;
long int menu_visual_realtape_bloque_posicion_final=-1;

void menu_visual_realtape_overlay(void)
{

	if (!zxvision_drawing_in_background) normal_overlay_texto_menu();

	char buffer_texto_medio[40]; 

	menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech

    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_audio_visual_realtape_window->is_minimized) return; 

    //printf ("contador_segundo=%d\n",contador_segundo);


    int dibujar=0;

    //esto hara ejecutar esto 5 veces por segundo
    if ( ((contador_segundo%200) == 0 && menu_visual_realtape_valor_contador_segundo_anterior!=contador_segundo) || menu_multitarea==0) {
        dibujar=1;
    }

    //Con top speed, solo se dibuja 1 frame por segundo. En ese caso, hacemos que siempre dibuje cuando hay ese frame
    if (timer_condicion_top_speed()) {
        //printf("top speed\n");
        dibujar=1;
    }
	
	if (dibujar) {

        menu_visual_realtape_valor_contador_segundo_anterior=contador_segundo;
        //printf ("Refrescando. contador_segundo=%d\n",contador_segundo);

        //menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech

        //borrar lo que haya
        zxvision_print_string_defaults_fillspc(menu_audio_visual_realtape_window,1,0,"");
        if (realtape_name!=NULL) {
            char nombre[PATH_MAX];
            util_get_file_no_directory(realtape_name,nombre);

            char string_realtape_shown[50];
            menu_tape_settings_trunc_name(nombre,string_realtape_shown,50);

            char buffer_linea[100];
            sprintf(buffer_linea,"Name: %s",string_realtape_shown);
            zxvision_print_string_defaults_fillspc(menu_audio_visual_realtape_window,1,0,buffer_linea);
        }

        char *tipos_cinta[]={
            "Type: Unknown",
            "Type: ZX Spectrum",
            "Type: ZX80",
            "Type: ZX81"
        };

        //por si acaso
        if (realtape_visual_detected_tape_type>3) {
            zxvision_print_string_defaults_fillspc(menu_audio_visual_realtape_window,1,1,"Error geting file type");
        }

        else {
            zxvision_print_string_defaults_fillspc(menu_audio_visual_realtape_window,1,1,tipos_cinta[realtape_visual_detected_tape_type]);
        }


        //Average, min, max
        int elapsed_seconds=realtape_get_elapsed_seconds();
        int total_seconds=realtape_get_total_seconds();

        char buffer_elapsed[10];
        char buffer_total[10];

        util_print_minutes_seconds(elapsed_seconds,buffer_elapsed);
        util_print_minutes_seconds(total_seconds,buffer_total);

        sprintf (buffer_texto_medio,"Elapsed: %s Total: %s",buffer_elapsed,buffer_total);

        zxvision_print_string_defaults_fillspc(menu_audio_visual_realtape_window,1,2,buffer_texto_medio);


        //de momento borrar esas lineas
        zxvision_print_string_defaults_fillspc(menu_audio_visual_realtape_window,1,3,"");
        zxvision_print_string_defaults_fillspc(menu_audio_visual_realtape_window,1,4,"");
        zxvision_print_string_defaults_fillspc(menu_audio_visual_realtape_window,1,5,"");

        //Ver el bloque que corresponde a esta posicion

        int i;

        for (i=0;visual_realtape_array_positions[i]!=-1;i++) {

            //en cuanto nuestra posicion es menor que la leida del array, retornamos la anterior 
            //printf("posicion actual: %ld array: %ld\n",realtape_file_size_counter,visual_realtape_array_positions[i]);

            if (visual_realtape_array_positions[i]>realtape_file_size_counter || visual_realtape_array_positions[i]==-1) break;
        }

        //printf("posicion real tape: %d\n",i);


        if (i>0) {
            i--;
   
            int posicion_buscar=i;
            //printf("Bloque %i position marker: %ld\n",posicion_buscar,visual_realtape_array_positions[posicion_buscar]);

            menu_visual_realtape_bloque_posicion_inicio=visual_realtape_array_positions[posicion_buscar];
            menu_visual_realtape_bloque_posicion_final=visual_realtape_array_positions[posicion_buscar+1];

            //Ahora localizar ese bloque dentro del texto. Cada texto empieza con dos saltos de linea seguidos
            int conteo_bloque=-1;
            int encontrado=0;
            for (i=0;visual_realtape_textbrowse[i] && !encontrado;i++) {
                if (visual_realtape_textbrowse[i]=='\n' && visual_realtape_textbrowse[i+1]=='\n') {
                    conteo_bloque++;
                    if (conteo_bloque==posicion_buscar) encontrado=1;
                }
            }
            if (encontrado) {
                //ahora pasar ese texto a otro string
                char buf_texto_bloque[1024];
                int indice_destino=0;
                int encontrado_final=0;
                //saltar primer salto de linea
                i++;
                for (;visual_realtape_textbrowse[i] && !encontrado_final;i++) {
                    buf_texto_bloque[indice_destino++]=visual_realtape_textbrowse[i];
                    if (visual_realtape_textbrowse[i]=='\n' && visual_realtape_textbrowse[i+1]=='\n') {
                        encontrado_final=1;
                    }
                }

                buf_texto_bloque[indice_destino]=0;

                //Y escribirlo. Al menos en dos lineas
                char buffer_linea[1024];
                int linea=0;
                int i;
                indice_destino=0;
                for (i=0;buf_texto_bloque[i];i++) {

                    buffer_linea[indice_destino]=buf_texto_bloque[i];
                    if (buf_texto_bloque[i]=='\n') {
                        buffer_linea[indice_destino]=0;
                        zxvision_print_string_defaults_fillspc(menu_audio_visual_realtape_window,1,3+linea,buffer_linea);

                        indice_destino=0;

                        linea++;
                        if (linea==3) break;
                    }
                    else {
                        indice_destino++;
                    }
                }
                
            }
     
        }

	}


//printf("refrescando\n");
	//Ancho variable segun el tamanyo de ventana
	int ancho=menu_audio_visual_realtape_window->visible_width-2;

	//Por si acaso, no vayamos a provocar alguna division por cero
	if (ancho<1) ancho=1;

	int alto;

    //lineas de separacion por encima de la onda de audio
	int lineas_cabecera=9;

	alto=menu_audio_visual_realtape_window->visible_height-lineas_cabecera-2;

	//Por si acaso, no vayamos a provocar alguna division por cero
	if (alto<1) alto=1;



	int xorigen=1;
	int yorigen;



	yorigen=lineas_cabecera;


	if (si_complete_video_driver() ) {
        ancho *=menu_char_width;
        alto *=8;
        xorigen *=menu_char_width;
        yorigen *=8;
	}



    int tamanyo_trozo=realtape_visual_total_used/ancho;

    //compensar. Para que quepa toda la forma de onda en ventana. Si no, seguramente siempre habria un trozo al final que no se veria
    int tamanyo_trozo_compensado=tamanyo_trozo+1;

    //posicion en la cinta real tape
    long int total=realtape_file_size;
    long int transcurrido=realtape_file_size_counter;

    int maximo_x_dibujar=realtape_visual_total_used/tamanyo_trozo_compensado;


    //evitar divisiones por cero
    if (total==0) total=1;
    long int posicion_cinta_x=(transcurrido*maximo_x_dibujar)/total;

    int x=0;

    int minimo,maximo;

    minimo=maximo=128;

    int indice;

    //printf("bloque posicion inicio %ld final %ld\n",menu_visual_realtape_bloque_posicion_inicio,menu_visual_realtape_bloque_posicion_final);
    //printf("ajustado bloque posicion inicio %ld final %ld\n",
    //    (menu_visual_realtape_bloque_posicion_inicio*maximo_x_dibujar)/total,
    //    (menu_visual_realtape_bloque_posicion_final*maximo_x_dibujar)/total);

    for (indice=0;indice<realtape_visual_total_used;indice++) {

        z80_byte valor_leido_maximo,valor_leido_minimo;

        valor_leido_minimo=realtape_visual_data[indice][0];
        valor_leido_maximo=realtape_visual_data[indice][1];

        //acumulado=acumulado+byte_leido;
        if (valor_leido_minimo<minimo) minimo=valor_leido_minimo;
        if (valor_leido_maximo>maximo) maximo=valor_leido_maximo;


        if ((indice%tamanyo_trozo_compensado)==0) {
            //siguiente trozo

            //por si acaso controlar maximo
            if (x<ancho) {
                //escalar el alto total a lo que corresponda
                int ymin=(minimo*alto)/256;
                int ymax=(maximo*alto)/256;

                int color_fondo=ESTILO_GUI_PAPEL_NORMAL;

                //Ver si estamos dibujando zona que esta entre los margenes del bloque actual
                //menu_visual_realtape_bloque_posicion_inicio, menu_visual_realtape_bloque_posicion_final
                //Convertir umbrales a posicion x

                //importante que sean long it igual que menu_visual_realtape_bloque_posicion_inicio,
                //sino, luego al multiplicar mas abajo podemos salirnos de rango facilmente
                long int umbral_min=menu_visual_realtape_bloque_posicion_inicio;
                long int umbral_max=menu_visual_realtape_bloque_posicion_final;

                if (umbral_min!=-1) {
                    umbral_min=(umbral_min*maximo_x_dibujar)/total;
                }

                if (umbral_max!=-1) {
                    umbral_max=(umbral_max*maximo_x_dibujar)/total;
                }


                //printf("cursor %d umbrales %d %d\n",x,umbral_min,umbral_max);
                //printf("xxx %ld\n",realtape_visual_total_used*tamanyo_trozo_compensado);

                if (umbral_min!=-1) {
                    if (x>=umbral_min) {
                        if (umbral_max==-1 ||  //Esto indica que no hay siguiente bloque
                                x < umbral_max) {

                            //printf("cambio color x: %d min %ld max %ld\n",x,umbral_min,umbral_max);

                            color_fondo=ESTILO_GUI_COLOR_BLOCK_VISUALTAPE;
                        }
                    }
                }
                

                int y;

                //0,0 es arriba del todo
                //dado que empezamos dibujando hasta ymin y luego hasta ymax, queremos que nuestro ymin se vea abajo del todo
                //por eso restamos siempre alto-

                for (y=0;y<ymin;y++) {
                    zxvision_putpixel(menu_audio_visual_realtape_window,x+xorigen,(alto-1-y)+yorigen,color_fondo);
                }

                //condicion <= porque hay que llegar hasta el valor maximo
                for (;y<=ymax;y++) {
                    zxvision_putpixel(menu_audio_visual_realtape_window,x+xorigen,(alto-1-y)+yorigen,ESTILO_GUI_COLOR_WAVEFORM);
                }

                for (;y<alto;y++) {
                    zxvision_putpixel(menu_audio_visual_realtape_window,x+xorigen,(alto-1-y)+yorigen,color_fondo);
                }

                //Si esta el cursor de cinta aqui, dibujar linea vertical
                if (x==posicion_cinta_x) {
                    for (y=0;y<alto;y++) {
                        zxvision_putpixel(menu_audio_visual_realtape_window,x+xorigen,y+yorigen,ESTILO_GUI_COLOR_AVISO);
                    }
                }

                x++;
            }
            else {
                //printf("Trying to write pixel beyond realtape visual: %d\n",x);
                return;
            }

            minimo=maximo=128;

        }
    }


	zxvision_draw_window_contents(menu_audio_visual_realtape_window);

}






zxvision_window zxvision_window_visual_realtape;

void menu_visual_realtape_rewind(MENU_ITEM_PARAMETERS)
{
    realtape_rewind_five();
}

void menu_visual_realtape_ffwd(MENU_ITEM_PARAMETERS)
{
    realtape_ffwd_five();
}

void menu_visual_realtape_rewind_one(MENU_ITEM_PARAMETERS)
{
    realtape_rewind_one();
}

void menu_visual_realtape_ffwd_one(MENU_ITEM_PARAMETERS)
{
    realtape_ffwd_one();
}

void menu_visual_realtape_reinsert(MENU_ITEM_PARAMETERS)
{
    if (!menu_realtape_cond() ) {
        debug_printf(VERBOSE_ERR,"There is no real tape selected");
        return;
    }
    menu_reinsert_real_tape();
}



void menu_realtape_open(MENU_ITEM_PARAMETERS)
{

        char *filtros[10];

        filtros[0]="smp";
        filtros[1]="rwa";
        filtros[2]="wav";
        filtros[3]="tzx";
        filtros[4]="p";
        filtros[5]="o";
        filtros[6]="tap";
        filtros[7]="cdt";
		filtros[8]="pzx";
        filtros[9]=0;


        //guardamos directorio actual
        char directorio_actual[PATH_MAX];
        getcwd(directorio_actual,PATH_MAX);

        //Obtenemos directorio de cinta
        //si no hay directorio, vamos a rutas predefinidas
        if (realtape_name==NULL) menu_chdir_sharedfiles();

        else {
                char directorio[PATH_MAX];
                util_get_dir(realtape_name,directorio);
                //printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

     		//cambiamos a ese directorio, siempre que no sea nulo
                if (directorio[0]!=0) {
                        debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
                        zvfs_chdir(directorio);
                }
        }



        int ret;

        ret=menu_filesel("Select Input Tape",filtros,menu_realtape_name);
        //volvemos a directorio inicial
        zvfs_chdir(directorio_actual);


        if (ret==1) {
                realtape_name=menu_realtape_name;
        	realtape_insert();
	}


}




void menu_visual_realtape_insert(MENU_ITEM_PARAMETERS)
{
    menu_realtape_open(0);

    //reestablecer overlay por que al llamar a menu_realtape_open, en el filesel, se resetea funcion overlay
    set_menu_overlay_function(menu_visual_realtape_overlay);
}

void menu_visual_realtape_stopbegin(MENU_ITEM_PARAMETERS)
{

    realtape_rewind_begin();
    realtape_stop_playing();
}


void menu_visual_realtape(MENU_ITEM_PARAMETERS)
{

    menu_espera_no_tecla();
    menu_reset_counters_tecla_repeticion();


    zxvision_window *ventana;
    ventana=&zxvision_window_visual_realtape;


	//IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
	//si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
	//la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
	zxvision_delete_window_if_exists(ventana);

	int x,y,ancho,alto,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;

	if (!util_find_window_geometry("visualrealtape",&x,&y,&ancho,&alto,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
        x=VISUALREALTAPE_X;
        y=VISUALREALTAPE_Y-2;
        ancho=VISUALREALTAPE_ANCHO;
        alto=VISUALREALTAPE_ALTO+4;      
	}


	//zxvision_new_window_nocheck_staticsize(ventana,x,y,ancho,alto,ancho-1,alto-2,"Visual Real Tape");
    zxvision_new_window_gn_cim(ventana,x,y,ancho,alto,ancho-1,alto-2,"Visual Real Tape","visualrealtape",is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);

	ventana->can_be_backgrounded=1;
	//indicar nombre del grabado de geometria
	//strcpy(ventana->geometry_name,"visualrealtape");
    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;    

	//printf("despues zxvision_new_window_nocheck_staticsize\n");
	zxvision_draw_window(ventana);


    //Cambiamos funcion overlay de texto de menu
    //Se establece a la de funcion de audio waveform
	set_menu_overlay_function(menu_visual_realtape_overlay);

	menu_audio_visual_realtape_window=ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui

	//Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
	//Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
	if (zxvision_currently_restoring_windows_on_start) {
		//printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
		return;
	}

	menu_item *array_menu_common;
	menu_item item_seleccionado;
	int retorno_menu;
	do {

        //borrar linea de menu por si hay restos de insertar
        zxvision_print_string_defaults_fillspc(ventana,1,6,"");
        zxvision_print_string_defaults_fillspc(ventana,1,7,"");



        menu_add_item_menu_inicial(&array_menu_common,"",MENU_OPCION_UNASSIGNED,NULL,NULL);

        if (realtape_inserted.v) {

            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_visual_realtape_rewind,NULL,"~~Rew");
            menu_add_item_menu_shortcut(array_menu_common,'r');
            menu_add_item_menu_tabulado(array_menu_common,1,6);

            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_visual_realtape_rewind_one,NULL,"Rew 1%%");
            menu_add_item_menu_tabulado(array_menu_common,5,6);


            char string_playpause[32];
            if (realtape_playing.v) strcpy(string_playpause,"~~Pause");
            else strcpy(string_playpause,"~~Play ");
            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_realtape_pause_unpause,NULL,string_playpause);
            menu_add_item_menu_shortcut(array_menu_common,'p');
            menu_add_item_menu_tabulado(array_menu_common,12,6);

            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_visual_realtape_ffwd_one,NULL,"FF 1%%");
            menu_add_item_menu_tabulado(array_menu_common,18,6);

            menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_visual_realtape_ffwd,NULL,"~~FF");
            menu_add_item_menu_shortcut(array_menu_common,'f');
            menu_add_item_menu_tabulado(array_menu_common,24,6);

         

        }

        if (menu_realtape_cond() ) {
		    menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_visual_realtape_reinsert,NULL,"R~~einsert");
		    menu_add_item_menu_shortcut(array_menu_common,'e');
		    menu_add_item_menu_tabulado(array_menu_common,1,7);
        }

		menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_visual_realtape_insert,NULL,"~~Insert");
		menu_add_item_menu_shortcut(array_menu_common,'i');
		menu_add_item_menu_tabulado(array_menu_common,10,7);

        if (menu_realtape_cond() && realtape_playing.v) {
		    menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_visual_realtape_stopbegin,NULL,"StopBegin");
		    //menu_add_item_menu_shortcut(array_menu_common,'s');
		    menu_add_item_menu_tabulado(array_menu_common,17,7);
        }


		//Nombre de ventana solo aparece en el caso de stdout
		retorno_menu=menu_dibuja_menu(&audio_visual_realtape_opcion_seleccionada,&item_seleccionado,array_menu_common,"Visual Real Tape" );

		if (retorno_menu!=MENU_RETORNO_BACKGROUND) {

			//En caso de menus tabulados, es responsabilidad de este de borrar la ventana
			cls_menu_overlay();
			if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
				//llamamos por valor de funcion
				if (item_seleccionado.menu_funcion!=NULL) {
					//printf ("actuamos por funcion\n");
					item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
					//En caso de menus tabulados, es responsabilidad de este de borrar la ventana
				}
			}
		}

	} while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus && retorno_menu!=MENU_RETORNO_BACKGROUND);

    //Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
    zxvision_set_window_overlay_from_current(ventana);

    //restauramos modo normal de texto de menu
    set_menu_overlay_function(normal_overlay_texto_menu);

    //En caso de menus tabulados, suele ser necesario esto. Si no, la ventana se quedaria visible
    cls_menu_overlay();

    //Grabar geometria ventana
    util_add_window_geometry_compact(ventana);


    if (retorno_menu==MENU_RETORNO_BACKGROUND) {
        zxvision_message_put_window_background();
    }

    else {
        //En caso de menus tabulados, es responsabilidad de este de liberar ventana
        zxvision_destroy_window(ventana);
    }

}


void hotswap_zxuno_to_p2as_set_pages(void)
{

                int i;
                //Punteros a paginas de la ROM
                for (i=0;i<4;i++) {
                        rom_mem_table[i]=zxuno_sram_mem_table_new[i+8];
                }

                //Punteros a paginas de la RAM
                for (i=0;i<8;i++) {
                        ram_mem_table[i]=zxuno_sram_mem_table_new[i];
                }


                //Paginas mapeadas actuales
                for (i=0;i<4;i++) {
                        memory_paged[i]=zxuno_memory_paged_brandnew[i*2];
                }
}


//Hace hotswap de cualquier maquina a spectrum 48. simplemente hace copia de los 64kb
/*NOTA: no uso esta funcion pues al pasar de zxuno a spectrum
la pantalla refresca "de otro sitio", y solo se puede ver si se habilita interfaz spectra...
es raro, es un error pero no tiene que ver con spectra, tiene que ver con divmmc:
-si hago hotswap de zxuno a 48k con divmmc, luego la pantalla no se refresca
-si hago hotswap de zxuno a 48k sin divmmc, si se ve bien
No se exactamente porque ocurre, seguramente algo que ver con peek_byte_no_time y paginas de divmmc
Uso la otra funcion de hotswap_any_machine_to_spec48 que hay mas abajo
*/
void to_delete_hotswap_any_machine_to_spec48(void)
{

	//Asignamos 64kb RAM
	z80_byte *memoria_spectrum_final;
	memoria_spectrum_final=malloc(65536);

	if (memoria_spectrum_final==NULL) {
		cpu_panic ("Error. Cannot allocate Machine memory");
	}

        //Copiamos ROM y RAM a destino
        int i;
        //ROM y RAM
        for (i=0;i<65536;i++) memoria_spectrum_final[i]=peek_byte_no_time(i);

	free(memoria_spectrum);
        memoria_spectrum=memoria_spectrum_final;

	current_machine_type=1;

        set_machine_params();
        post_set_machine(NULL);

}

void hotswap_any_machine_to_spec48(void)
{

        //Asignamos 64kb RAM
        z80_byte *memoria_buffer;
        memoria_buffer=malloc(65536);

        if (memoria_buffer==NULL) {
                cpu_panic ("Error. Cannot allocate Machine memory");
        }

        //Copiamos ROM y RAM en buffer
        int i;
        for (i=0;i<65536;i++) memoria_buffer[i]=peek_byte_no_time(i);

        //Spectrum 48k
        current_machine_type=1;

        set_machine(NULL);

        //Copiar contenido de buffer en ROM y RAM
	//Por tanto la rom de destino sera la que habia antes del hotswap
	memcpy(memoria_spectrum,memoria_buffer,65536);

        free(memoria_buffer);
}

void hotswap_p2a_to_128(void)
{
	//Copiamos ROM0 y ROM3 en ROM 0 y 1 de spectrum 128k
	//La ram la copiamos tal cual
	z80_byte old_puerto_32765=puerto_32765;

	//Asignamos 32+128k de memoria
	z80_byte *memoria_buffer;
	memoria_buffer=malloc((32+128)*1024);

	if (memoria_buffer==NULL) {
					cpu_panic ("Error. Cannot allocate Machine memory");
	}

	//Copiamos rom 0 en buffer
	int i;
	z80_byte *puntero;
	puntero=rom_mem_table[0];
	for (i=0;i<16384;i++) {
		memoria_buffer[i]=*puntero;
		puntero++;
	}

	//Copiamos rom 3 en buffer
	puntero=rom_mem_table[3];
	for (i=0;i<16384;i++) {
		memoria_buffer[16384+i]=*puntero;
		puntero++;
	}

	//Copiamos paginas de ram
	int pagina;
	for (pagina=0;pagina<8;pagina++) {
		puntero=ram_mem_table[pagina];
		for (i=0;i<16384;i++) {
			memoria_buffer[32768+pagina*16384+i]=*puntero;
			puntero++;
		}
	}

	//Spectrum 128k
        current_machine_type=6;

        set_machine(NULL);

 //Mapear como estaba
 puerto_32765=old_puerto_32765;

	//asignar ram
	mem_page_ram_128k();

	//asignar rom
	mem_page_rom_128k();

	//Copiar contenido de buffer en ROM y RAM
	//No nos complicamos la vida, como sabemos que viene lineal las dos roms y la ram, volcamos

	for (i=0;i<(32+128)*1024;i++) memoria_spectrum[i]=memoria_buffer[i];

  free(memoria_buffer);



}



void hotswap_128_to_p2a(void)
{
	//Copiamos ROM0 en ROM0, ROM1 en ROM1, ROM0 en ROM2 y ROM1 en ROM3 de +2a
	//La ram la copiamos tal cual
	z80_byte old_puerto_32765=puerto_32765;

	//Asignamos 64+128k de memoria
	z80_byte *memoria_buffer;
	memoria_buffer=malloc((64+128)*1024);

	if (memoria_buffer==NULL) {
					cpu_panic ("Error. Cannot allocate Machine memory");
	}

	//Copiamos rom 0 y en buffer
	int i;
	z80_byte *puntero;
	puntero=rom_mem_table[0];
	for (i=0;i<16384;i++) {
		memoria_buffer[i]=*puntero;
		memoria_buffer[32768+i]=*puntero;
		puntero++;
	}

	//Copiamos rom 3 en buffer
	puntero=rom_mem_table[1];
	for (i=0;i<16384;i++) {
		memoria_buffer[16384+i]=*puntero;
		memoria_buffer[49152+i]=*puntero;
		puntero++;
	}

	//Copiamos paginas de ram
	int pagina;
	for (pagina=0;pagina<8;pagina++) {
		puntero=ram_mem_table[pagina];
		for (i=0;i<16384;i++) {
			memoria_buffer[65536+pagina*16384+i]=*puntero;
			puntero++;
		}
	}

	//Spectrum +2A
        current_machine_type=11;

        set_machine(NULL);

 //Mapear como estaba
 puerto_32765=old_puerto_32765;

 puerto_8189=0;

	//asignar ram
	mem_page_ram_p2a();

	//asignar rom
	mem_page_rom_p2a();

	//Copiar contenido de buffer en ROM y RAM
	//No nos complicamos la vida, como sabemos que viene lineal las  roms y la ram, volcamos

	for (i=0;i<(64+128)*1024;i++) memoria_spectrum[i]=memoria_buffer[i];

  free(memoria_buffer);



}


//Hace hotswap de cualquier maquina 48 a spectrum 128. Se guarda los 48kb de ram en un buffer, cambia maquina, y vuelca contenido ram
void hotswap_any_machine_to_spec128(void)
{

        //Asignamos 48kb RAM
        z80_byte *memoria_buffer;
        memoria_buffer=malloc(49152);

        if (memoria_buffer==NULL) {
                cpu_panic ("Error. Cannot allocate Machine memory");
        }

        //Copiamos RAM en buffer
        int i;
        for (i=0;i<49152;i++) memoria_buffer[i]=peek_byte_no_time(16384+i);

	//Spectrum 128k
        current_machine_type=6;

        set_machine(NULL);

	//Paginar ROM 1 y RAM 0
	puerto_32765=16;

	//asignar ram
	mem_page_ram_128k();

	//asignar rom
	mem_page_rom_128k();

	//Copiar contenido de buffer en RAM
	for (i=0;i<49152;i++) poke_byte_no_time(16384+i,memoria_buffer[i]);

        free(memoria_buffer);
}



void menu_hotswap_machine(MENU_ITEM_PARAMETERS)
{

                menu_item *array_menu_machine_selection;
                menu_item item_seleccionado;
                int retorno_menu;

                do {

			//casos maquinas 16k, 48k
			if (MACHINE_IS_SPECTRUM_16_48) {
				hotswap_machine_opcion_seleccionada=current_machine_type;
        	                menu_add_item_menu_inicial(&array_menu_machine_selection,"ZX Spectrum 16k",MENU_OPCION_NORMAL,NULL,NULL);
                	        menu_add_item_menu(array_menu_machine_selection,"ZX Spectrum 48k",MENU_OPCION_NORMAL,NULL,NULL);
                        	menu_add_item_menu(array_menu_machine_selection,"Inves Spectrum +",MENU_OPCION_NORMAL,NULL,NULL);
	                        menu_add_item_menu(array_menu_machine_selection,"Microdigital TK90X",MENU_OPCION_NORMAL,NULL,NULL);
        	                menu_add_item_menu(array_menu_machine_selection,"Microdigital TK90X (Spanish)",MENU_OPCION_NORMAL,NULL,NULL);
                	        menu_add_item_menu(array_menu_machine_selection,"Microdigital TK95",MENU_OPCION_NORMAL,NULL,NULL);
				menu_add_item_menu(array_menu_machine_selection,"ZX Spectrum+ 128",MENU_OPCION_NORMAL,NULL,NULL);
			}

			//casos maquinas 128k,+2 (y no +2a)
			if (MACHINE_IS_SPECTRUM_128_P2) {
				hotswap_machine_opcion_seleccionada=current_machine_type-6;
	                        menu_add_item_menu_inicial(&array_menu_machine_selection,"ZX Spectrum+ 128k",MENU_OPCION_NORMAL,NULL,NULL);
        	                menu_add_item_menu(array_menu_machine_selection,"ZX Spectrum+ 128k (Spanish)",MENU_OPCION_NORMAL,NULL,NULL);
                	        menu_add_item_menu(array_menu_machine_selection,"ZX Spectrum +2",MENU_OPCION_NORMAL,NULL,NULL);
                        	menu_add_item_menu(array_menu_machine_selection,"ZX Spectrum +2 (French)",MENU_OPCION_NORMAL,NULL,NULL);
	                        menu_add_item_menu(array_menu_machine_selection,"ZX Spectrum +2 (Spanish)",MENU_OPCION_NORMAL,NULL,NULL);
													menu_add_item_menu(array_menu_machine_selection,"ZX Spectrum +2A (ROM v4.0)",MENU_OPCION_NORMAL,NULL,NULL);
				menu_add_item_menu(array_menu_machine_selection,"ZX Spectrum 48k",MENU_OPCION_NORMAL,NULL,NULL);
			}

			//maquinas p2a
			if (MACHINE_IS_SPECTRUM_P2A_P3) {
				hotswap_machine_opcion_seleccionada=current_machine_type-11;
	                        menu_add_item_menu_inicial(&array_menu_machine_selection,"ZX Spectrum +2A (ROM v4.0)",MENU_OPCION_NORMAL,NULL,NULL);
        	                menu_add_item_menu(array_menu_machine_selection,"ZX Spectrum +2A (ROM v4.1)",MENU_OPCION_NORMAL,NULL,NULL);
                	        menu_add_item_menu(array_menu_machine_selection,"ZX Spectrum +2A (Spanish)",MENU_OPCION_NORMAL,NULL,NULL);
													menu_add_item_menu(array_menu_machine_selection,"Spectrum 128k",MENU_OPCION_NORMAL,NULL,NULL);
				menu_add_item_menu(array_menu_machine_selection,"ZX Spectrum 48k",MENU_OPCION_NORMAL,NULL,NULL);
			}

			//maquinas cpc
			if (MACHINE_IS_CPC) {
				hotswap_machine_opcion_seleccionada=current_machine_type-MACHINE_ID_CPC_464;
	                        menu_add_item_menu_inicial(&array_menu_machine_selection,"Amstrad CPC 464",MENU_OPCION_NORMAL,NULL,NULL);
        	                menu_add_item_menu(array_menu_machine_selection,"Amstrad CPC 4128",MENU_OPCION_NORMAL,NULL,NULL);
			}			

                        //maquinas zxuno
                        if (MACHINE_IS_ZXUNO) {
                                hotswap_machine_opcion_seleccionada=current_machine_type-14;
                                menu_add_item_menu_inicial(&array_menu_machine_selection,"ZX Spectrum +2A (ROM v4.0)",MENU_OPCION_NORMAL,NULL,NULL);

	                        menu_add_item_menu_tooltip(array_menu_machine_selection,"The final machine type is "
							"Spectrum +2A (ROM v4.0) but the data ROM really comes from ZX-Uno");
	                        menu_add_item_menu_ayuda(array_menu_machine_selection,"The final machine type is "
							"Spectrum +2A (ROM v4.0) but the data ROM really comes from ZX-Uno");


				menu_add_item_menu(array_menu_machine_selection,"Spectrum 48k",MENU_OPCION_NORMAL,NULL,NULL);


                        }


			//maquinas zx80, zx81
			if (MACHINE_IS_ZX8081) {
				hotswap_machine_opcion_seleccionada=current_machine_type-120;
				menu_add_item_menu_inicial(&array_menu_machine_selection,"ZX80",MENU_OPCION_NORMAL,NULL,NULL);
	            menu_add_item_menu(array_menu_machine_selection,"ZX81",MENU_OPCION_NORMAL,NULL,NULL);
			}

                 

			//maquinas chloe
			if (MACHINE_IS_CHLOE) {
				if (MACHINE_IS_CHLOE_140SE) hotswap_machine_opcion_seleccionada=0;
				if (MACHINE_IS_CHLOE_280SE) hotswap_machine_opcion_seleccionada=1;

				menu_add_item_menu_inicial(&array_menu_machine_selection,"Chloe 140SE",MENU_OPCION_NORMAL,NULL,NULL);
				menu_add_item_menu(array_menu_machine_selection,"Chloe 280SE",MENU_OPCION_NORMAL,NULL,NULL);
				menu_add_item_menu(array_menu_machine_selection,"ZX Spectrum 48k",MENU_OPCION_NORMAL,NULL,NULL);


			}

			//Diferentes maquinas que solo pueden saltar a spectrum 48k
			if (MACHINE_IS_PRISM || MACHINE_IS_TIMEX_TS2068 || MACHINE_IS_TBBLUE || MACHINE_IS_CHROME || MACHINE_IS_ZXEVO) {
								hotswap_machine_opcion_seleccionada=0;
								menu_add_item_menu_inicial(&array_menu_machine_selection,"ZX Spectrum 48k",MENU_OPCION_NORMAL,NULL,NULL);
			}

			


                        menu_add_item_menu(array_menu_machine_selection,"",MENU_OPCION_SEPARADOR,NULL,NULL);
                        //menu_add_item_menu(array_menu_machine_selection,"ESC Back",MENU_OPCION_NORMAL|MENU_OPCION_ESC,NULL,NULL);
			menu_add_ESC_item(array_menu_machine_selection);

			retorno_menu=menu_dibuja_menu(&hotswap_machine_opcion_seleccionada,&item_seleccionado,array_menu_machine_selection,"Hotswap Machine" );

	                


                        if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
				//casos maquinas 16k, 48k
	                        if (MACHINE_IS_SPECTRUM_16_48) {
					//Caso especial cuando se cambia entre maquina Inves, porque la asignacion de memoria es diferente
					if (MACHINE_IS_INVES || hotswap_machine_opcion_seleccionada==2) {
						//si misma maquina inves origen o destino, no hacer nada

						//Cambiamos de Inves a otra
						if (MACHINE_IS_INVES && hotswap_machine_opcion_seleccionada!=2) {
							//Asignamos 64kb RAM
							z80_byte *memoria_spectrum_final;
						        memoria_spectrum_final=malloc(65536);

						        if (memoria_spectrum_final==NULL) {
						                cpu_panic ("Error. Cannot allocate Machine memory");
						        }

							//Copiamos ROM y RAM a destino
							int i;
							//ROM
							for (i=0;i<16384;i++) memoria_spectrum_final[i]=memoria_spectrum[65536+i];

							//RAM
							for (i=16384;i<65536;i++) memoria_spectrum_final[i]=memoria_spectrum[i];

							free(memoria_spectrum);
							memoria_spectrum=memoria_spectrum_final;

						}
						if (!(MACHINE_IS_INVES) && hotswap_machine_opcion_seleccionada==2) {
							//Asignamos 80 kb RAM
                                                        z80_byte *memoria_spectrum_final;
                                                        memoria_spectrum_final=malloc(65536+16384);

                                                        if (memoria_spectrum_final==NULL) {
                                                                cpu_panic ("Error. Cannot allocate Machine memory");
                                                        }

							//Copiamos ROM y RAM a destino
							int i;
							//ROM
                                                        for (i=0;i<16384;i++) memoria_spectrum_final[65536+i]=memoria_spectrum[i];

                                                        //RAM
                                                        for (i=16384;i<65536;i++) memoria_spectrum_final[i]=memoria_spectrum[i];

                                                        free(memoria_spectrum);
                                                        memoria_spectrum=memoria_spectrum_final;

							//Establecemos valores de low ram inves
							random_ram_inves(memoria_spectrum,16384);


						}
					}

					//Hotswap a 128
          if (hotswap_machine_opcion_seleccionada==6) {
						debug_printf (VERBOSE_INFO,"Hotswapping to Spectrum 128");
                                                hotswap_any_machine_to_spec128();
                                        }

					else {
						current_machine_type=hotswap_machine_opcion_seleccionada;
				        	set_machine_params();
				        	post_set_machine(NULL);
					}
                                        //Y salimos de todos los menus
                                        salir_todos_menus=1;
					return; //Para evitar saltar a otro if
				}

				if (MACHINE_IS_SPECTRUM_128_P2) {
					if (hotswap_machine_opcion_seleccionada==6) {
						hotswap_any_machine_to_spec48();
					}

					else if (hotswap_machine_opcion_seleccionada==5) {
						hotswap_128_to_p2a();
						menu_warn_message("Note that ROM data are the previous data coming from 128K");
					}

					else {
						current_machine_type=hotswap_machine_opcion_seleccionada+6;
        	                                set_machine_params();
                	                        post_set_machine(NULL);
					}
                        	        //Y salimos de todos los menus
                                	salir_todos_menus=1;
					return; //Para evitar saltar a otro if
                                }

				if (MACHINE_IS_SPECTRUM_P2A_P3) {
                                        if (hotswap_machine_opcion_seleccionada==4) {
                                                hotswap_any_machine_to_spec48();
                                        }
					else if (hotswap_machine_opcion_seleccionada==3) {
						//De +2A a 128k
						hotswap_p2a_to_128();
						menu_warn_message("Note that ROM data are the previous data coming from +2A");
					}
					else {
	                                        current_machine_type=hotswap_machine_opcion_seleccionada+11;
        	                                set_machine_params();
                	                        post_set_machine(NULL);
					}
                                        //Y salimos de todos los menus
                                        salir_todos_menus=1;
					return; //Para evitar saltar a otro if
                                }

				if (MACHINE_IS_CPC) {
					current_machine_type=MACHINE_ID_CPC_464+hotswap_machine_opcion_seleccionada;
					set_machine_params();
                	post_set_machine(NULL);
                    //Y salimos de todos los menus
                    salir_todos_menus=1;
					return; //Para evitar saltar a otro if

				}

				if (MACHINE_IS_ZX8081) {
					current_machine_type=hotswap_machine_opcion_seleccionada+120;
					set_machine_params();
                                        post_set_machine(NULL);

					//ajustar algunos registros
					if (MACHINE_IS_ZX80) reg_i=0x0E;

					if (MACHINE_IS_ZX81) {
						reg_i=0x1E;
						nmi_generator_active.v=0;
					}

                                        //Y salimos de todos los menus
                                        salir_todos_menus=1;
					return; //Para evitar saltar a otro if
                                }

				if (MACHINE_IS_ZXUNO) {
                                        if (hotswap_machine_opcion_seleccionada==1) {
                                                hotswap_any_machine_to_spec48();
                                        }

					else {
						current_machine_type=hotswap_machine_opcion_seleccionada+11;
						set_machine_params();

						//no cargar rom, la rom sera la que haya activa en las paginas del zxuno
						post_set_machine_no_rom_load();

						//dejamos toda la memoria que hay asignada del zx-uno, solo que
						//reasignamos los punteros de paginacion del +2a

						hotswap_zxuno_to_p2as_set_pages();


						//Si teniamos el divmmc activo. Llamar a esto manualmente, no a todo divmmc_enable(),
						//pues cargaria por ejemplo el firmware esxdos de disco, y mejor conservamos el mismo firmware
						//que haya cargado el ZX-Uno
						if (diviface_enabled.v) {
							diviface_set_peek_poke_functions();
							//diviface_paginacion_manual_activa.v=0;
							diviface_control_register&=(255-128);
							diviface_paginacion_automatica_activa.v=0;
						}

						menu_warn_message("Note that ROM data are the previous data coming from ZX-Uno");

					}

					salir_todos_menus=1;
					return; //Para evitar saltar a otro if
				}



				if (MACHINE_IS_CHLOE) {
                                        if (hotswap_machine_opcion_seleccionada==2) {
                                                hotswap_any_machine_to_spec48();
                                        }

					else {
						current_machine_type=hotswap_machine_opcion_seleccionada+15;
        	                                set_machine_params();
                	                        post_set_machine(NULL);

					}
                    //Y salimos de todos los menus
                    salir_todos_menus=1;
					return; //Para evitar saltar a otro if
				}

				if (MACHINE_IS_PRISM || MACHINE_IS_TIMEX_TS2068 || MACHINE_IS_TBBLUE || MACHINE_IS_CHROME || MACHINE_IS_ZXEVO) {
					hotswap_any_machine_to_spec48();
                    salir_todos_menus=1;
					return; //Para evitar saltar a otro if
                }

				


            }

		} while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);
}

int custom_machine_type=0;
char custom_romfile[PATH_MAX]="";

static char *custom_machine_names[]={
                "Spectrum 16k",
                "Spectrum 48k",

		"TK90X/95",

                "Spectrum 128k/+2",
                "Spectrum +2A",
                "Spectrum +3",
		"ZX-Uno",

		"Chloe 140 SE",
		"Chloe 280 SE",
		"Timex TS 2068",
		"Prism 512",

                "ZX80",
                "ZX81",
		"Jupiter Ace",
		"Z88",
		"Amstrad CPC 464",
		"Sam Coupe",
		"QL"
};


void menu_custom_machine_romfile(MENU_ITEM_PARAMETERS)
{

        char *filtros[2];

        filtros[0]="rom";
        filtros[1]=0;


        if (menu_filesel("Select ROM File",filtros,custom_romfile)==1) {
                //

        }

        else {
                custom_romfile[0]=0;
        }
}




void menu_custom_machine_change(MENU_ITEM_PARAMETERS)
{
	custom_machine_type++;
	if (custom_machine_type==18) custom_machine_type=0;
}

void menu_custom_machine_run(MENU_ITEM_PARAMETERS)
{

	int minimum_size=0;
	int next_machine_type;

	switch (custom_machine_type) {

  
        //Spectrum 16k
		case 0:
			next_machine_type=0;
		break;

        //Spectrum 48k
		case 1:
			next_machine_type=1;
		break;

        //TK90X/95
		case 2:
			next_machine_type=3;
		break;

        //Spectrum 128k/+2
		case 3:
			next_machine_type=6;
		break;

        //Spectrum +2A
		case 4:
			next_machine_type=11;
		break;

        //Spectrum +3
		case 5:
			next_machine_type=MACHINE_ID_SPECTRUM_P3_40;
		break;        

		case 6:
			//ZX-Uno
			next_machine_type=14;
		break;





		case 7:
			//Chloe 140SE
			next_machine_type=15;
		break;

		case 8:
			//Chloe 280SE
			next_machine_type=16;
		break;

		case 9:
			//Timex TS2068
			next_machine_type=17;
		break;

		case 10:
			//Prism
			next_machine_type=18;
		break;



		case 11:
			//ZX-80
			next_machine_type=120;
		break;

		case 12:
			//ZX-81
			next_machine_type=121;
		break;

		case 13:
			//ACE
			next_machine_type=122;
		break;

		case 14:
			//Z88
			next_machine_type=130;
		break;

		case 15:
			//Amstrad CPC 464
			next_machine_type=140;
		break;

		case 16:
			//Sam Coupe
			next_machine_type=150;
		break;

		case 17:
			//QL
			next_machine_type=MACHINE_ID_QL_STANDARD;
		break;

		default:
			cpu_panic("Custom machine type unknown");
			//este return no hace falta, solo es para silenciar los warning de variable next_machine_type no inicializada
			return;
		break;

	}

	//Ver tamanyo archivo rom
	minimum_size=get_rom_size(next_machine_type);

	struct stat buf_stat;


                if (stat(custom_romfile, &buf_stat)!=0) {
                        debug_printf(VERBOSE_ERR,"Unable to find rom file %s",custom_romfile);
			return;
                }

                else {
                        //Tamaño del archivo es >=minimum_size
                        if (buf_stat.st_size<minimum_size) {
				debug_printf(VERBOSE_ERR,"ROM file must be at least %d bytes length",minimum_size);
                                return;
                        }
                }

	current_machine_type=next_machine_type;
	set_machine(custom_romfile);
	cold_start_cpu_registers();
	reset_cpu();

	//Y salimos de todos los menus
	salir_todos_menus=1;

}

void menu_custom_machine(MENU_ITEM_PARAMETERS)
{
   menu_item *array_menu_custom_machine;
        menu_item item_seleccionado;
        int retorno_menu;

	//Tipo de maquina: 16k,48k,128k/+2,+2a,zx80,zx81,ace,z88
	//Archivo ROM

	//sprintf(custom_romfile,"%s","alternaterom_plus2b.rom");

        do {
                menu_add_item_menu_inicial_format(&array_menu_custom_machine,MENU_OPCION_NORMAL,menu_custom_machine_change,NULL,"Machine Type: %s",custom_machine_names[custom_machine_type] );

		char string_romfile_shown[16];
                menu_tape_settings_trunc_name(custom_romfile,string_romfile_shown,16);

                menu_add_item_menu_format(array_menu_custom_machine,MENU_OPCION_NORMAL,menu_custom_machine_romfile,NULL,"Rom File: %s",string_romfile_shown);

		menu_add_item_menu_format(array_menu_custom_machine,MENU_OPCION_NORMAL,menu_custom_machine_run,NULL,"Run machine");



                menu_add_item_menu(array_menu_custom_machine,"",MENU_OPCION_SEPARADOR,NULL,NULL);

                menu_add_ESC_item(array_menu_custom_machine);

                retorno_menu=menu_dibuja_menu(&custom_machine_opcion_seleccionada,&item_seleccionado,array_menu_custom_machine,"Custom Machine" );

                

                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);

}

int menu_hotswap_machine_cond(void) {

	//Retornar ok solo para determinadas maquinas
	if (MACHINE_IS_SPECTRUM_16_48)  return 1;
	if (MACHINE_IS_SPECTRUM_128_P2)  return 1;
	if (MACHINE_IS_SPECTRUM_P2A_P3)  return 1;
    if (MACHINE_IS_ZXUNO)  return 1;
	if (MACHINE_IS_ZX8081)  return 1;
	if (MACHINE_IS_CHLOE)  return 1;
	if (MACHINE_IS_PRISM)  return 1;
	if (MACHINE_IS_TIMEX_TS2068)  return 1;
	if (MACHINE_IS_TBBLUE)  return 1;
	if (MACHINE_IS_CHROME)  return 1;
	if (MACHINE_IS_ZXEVO)  return 1;
	if (MACHINE_IS_CPC)  return 1;


	return 0;
}


void menu_machine_set_machine_by_id(int id_maquina)
{
current_machine_type=id_maquina;

				     set_machine(NULL);
                                        cold_start_cpu_registers();
                                        reset_cpu();

                                        //desactivar autoload
                                        //noautoload.v=1;
                                        //initial_tap_load.v=0;


                                        //expulsamos cintas
                                        eject_tape_load();
                                        eject_tape_save();

                                        //Y salimos de todos los menus
                                        salir_todos_menus=1;


										
										if (MACHINE_IS_TBBLUE) {
												//Si se pregunta si se quiere autoconfigurar SD, solo si esta el grabado de configuracion, e interfaz permite menu (no stdout ni simpletext ni null)
												if (save_configuration_file_on_exit.v && tbblue_autoconfigure_sd_asked.v==0 && si_normal_menu_video_driver()) {
													if (menu_confirm_yesno_texto("Autoconfigure Initial SD","Sure?")) {
														menu_storage_mmc_autoconfigure_tbblue(0);
													}

													tbblue_autoconfigure_sd_asked.v=1;
												}

										}

										if (MACHINE_IS_SG1000) {
											menu_first_aid("sg1000_boot");
										}
											
}

void menu_machine_selection_manufacturer_machines(int fabricante)
{
	int i;
	int *maquinas;

	maquinas=return_maquinas_fabricante(fabricante);

	//cambiar linea seleccionada a maquina en cuestion
	int indice_maquina=return_machine_position(maquinas,current_machine_type);
	if (indice_maquina!=255) machine_selection_por_fabricante_opcion_seleccionada=indice_maquina;
	else {
		//Maquina no es de este menu. Resetear linea a 0
		machine_selection_por_fabricante_opcion_seleccionada=0;
	}

	char *nombre_maquina;

	int total_maquinas;

	int m;

        //Seleccion por fabricante
                menu_item *array_menu_machine_selection_por_fabricante;
                menu_item item_seleccionado;
                int retorno_menu;
	do {

		for (i=0;maquinas[i]!=255;i++) {
			m=maquinas[i];
			//printf ("%d\n",m);
			nombre_maquina=get_machine_name(m);
			//printf ("%d %s\n",m,nombre_maquina);


			if (i==0) {
				//Primera maquina
	                        menu_add_item_menu_inicial_format(&array_menu_machine_selection_por_fabricante,MENU_OPCION_NORMAL,NULL,NULL,"%s",nombre_maquina);

			}

			else {
				menu_add_item_menu_format(array_menu_machine_selection_por_fabricante,MENU_OPCION_NORMAL,NULL,NULL,"%s",nombre_maquina);
			}


		}

		total_maquinas=i;




      menu_add_item_menu(array_menu_machine_selection_por_fabricante,"",MENU_OPCION_SEPARADOR,NULL,NULL);


                        //menu_add_item_menu(array_menu_machine_selection_por_fabricante,"ESC Back",MENU_OPCION_NORMAL|MENU_OPCION_ESC,NULL,NULL);
                        menu_add_ESC_item(array_menu_machine_selection_por_fabricante);



                        retorno_menu=menu_dibuja_menu(&machine_selection_por_fabricante_opcion_seleccionada,&item_seleccionado,array_menu_machine_selection_por_fabricante,"Select machine" );

                        //printf ("Opcion seleccionada: %d\n",machine_selection_por_fabricante_opcion_seleccionada);

                        

                        if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {

                                if (machine_selection_por_fabricante_opcion_seleccionada>=0 && machine_selection_por_fabricante_opcion_seleccionada<=total_maquinas) {



								//printf ("Seleccion opcion=%d\n",machine_selection_por_fabricante_opcion_seleccionada);
								int id_maquina=maquinas[machine_selection_por_fabricante_opcion_seleccionada];
								//printf ("Maquina= %d %s\n",id_maquina, get_machine_name(id_maquina) );




								menu_machine_set_machine_by_id(id_maquina);

					
										

                              }



                                //llamamos por valor de funcion
                                if (item_seleccionado.menu_funcion!=NULL) {
                                        //printf ("actuamos por funcion\n");
                                        item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                }


         
                        }

                
                } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);






}

//Seleccion de maquina por fabricante
void menu_machine_selection_manufacturer(MENU_ITEM_PARAMETERS)
{

	//Seleccion por fabricante
                menu_item *array_menu_machine_selection;
                menu_item item_seleccionado;
                int retorno_menu;

//return_fabricante_maquina
		//Establecemos linea menu segun fabricante activo
		machine_selection_opcion_seleccionada=return_fabricante_maquina(current_machine_type);

                do {

			//Primer fabricante
                        menu_add_item_menu_inicial_format(&array_menu_machine_selection,MENU_OPCION_NORMAL,NULL,NULL,"%s",array_fabricantes_hotkey[0]);
			menu_add_item_menu_shortcut(array_menu_machine_selection,array_fabricantes_hotkey_letra[0]);

		//Siguientes fabricantes
			int i;
			for (i=1;i<TOTAL_FABRICANTES;i++) {
				menu_add_item_menu_format(array_menu_machine_selection,MENU_OPCION_NORMAL,NULL,NULL,"%s",array_fabricantes_hotkey[i]);
				z80_byte letra=array_fabricantes_hotkey_letra[i];
				if (letra!=' ') menu_add_item_menu_shortcut(array_menu_machine_selection,letra);
			}


                       menu_add_item_menu(array_menu_machine_selection,"",MENU_OPCION_SEPARADOR,NULL,NULL);

                        //Hotswap de Z88 o Jupiter Ace o CHLOE no existe
                        menu_add_item_menu(array_menu_machine_selection,"~~Hotswap machine",MENU_OPCION_NORMAL,menu_hotswap_machine,menu_hotswap_machine_cond);
                        menu_add_item_menu_shortcut(array_menu_machine_selection,'h');
                        menu_add_item_menu_tooltip(array_menu_machine_selection,"Change machine type without resetting");
                        menu_add_item_menu_ayuda(array_menu_machine_selection,"Change machine type without resetting.");
                        menu_add_item_menu_tiene_submenu(array_menu_machine_selection);

                        menu_add_item_menu_en_es_ca(array_menu_machine_selection,MENU_OPCION_NORMAL,menu_custom_machine,NULL,
                            "Custom machine","Maquina personalizada","Maquina personalitzada");
                        menu_add_item_menu_tooltip(array_menu_machine_selection,"Specify custom machine type & ROM");
                        menu_add_item_menu_ayuda(array_menu_machine_selection,"Specify custom machine type & ROM");
                        menu_add_item_menu_tiene_submenu(array_menu_machine_selection);

                        menu_add_item_menu(array_menu_machine_selection,"",MENU_OPCION_SEPARADOR,NULL,NULL);


                        //menu_add_item_menu(array_menu_machine_selection,"ESC Back",MENU_OPCION_NORMAL|MENU_OPCION_ESC,NULL,NULL);
                        menu_add_ESC_item(array_menu_machine_selection);



                        retorno_menu=menu_dibuja_menu(&machine_selection_opcion_seleccionada,&item_seleccionado,array_menu_machine_selection,menu_get_string_language("Select manufacturer") );

                        //printf ("Opcion seleccionada: %d\n",machine_selection_opcion_seleccionada);

                        

                        if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {

                                if (machine_selection_opcion_seleccionada>=0 && machine_selection_opcion_seleccionada<=TOTAL_FABRICANTES) {

					//printf ("Seleccionado fabricante %s\n",array_fabricantes[machine_selection_opcion_seleccionada]);

                                        //int last_machine_type=machine_type;


					menu_machine_selection_manufacturer_machines(machine_selection_opcion_seleccionada);



			      }
                                //llamamos por valor de funcion
                                if (item_seleccionado.menu_funcion!=NULL) {
                                        //printf ("actuamos por funcion\n");
                                        item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                        
                                }


                             
                        }

              
                } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);


}



int menu_machine_selection_by_name_alphasort(const struct s_machine_names **d1, const struct s_machine_names **d2)
{

        //printf ("menu_filesel_alphasort %s %s\n",(*d1)->d_name,(*d2)->d_name );

        //compara nombre
        return (strcasecmp((*d1)->nombre_maquina,(*d2)->nombre_maquina));
}

void menu_machine_selection_by_name_set(MENU_ITEM_PARAMETERS)
{
	menu_machine_set_machine_by_id(valor_opcion);
}

//Seleccion de maquina por nombre
void menu_machine_selection_by_name(MENU_ITEM_PARAMETERS)
{

	
	int total_maquinas;


	total_maquinas=0;

	int i;

	for (i=0;i<99999 && machine_names[i].nombre_maquina[0]!=0;i++) {
		//printf ("id: %03d nombre: %s\n",machine_names[i].id,machine_names[i].nombre_maquina);
		total_maquinas++;
	}
	
	//printf ("total maquinas: %d\n",total_maquinas);


	//Meterlas en array, para poderlas ordenar

	struct s_machine_names *sorted_machine_names;

	int tamanyo_struct=sizeof(struct s_machine_names);

	int tamanyo_total=tamanyo_struct*total_maquinas;

	//printf ("Allocating memory for %d\n",tamanyo_total);

	sorted_machine_names=malloc(tamanyo_total);

	if (sorted_machine_names==NULL) cpu_panic ("Cannot allocate memory for machine list");

	//Insertar listado en memoria
	for (i=0;i<total_maquinas;i++) {
		//printf ("id: %03d nombre: %s\n",machine_names[i].id,machine_names[i].nombre_maquina);

		strcpy(sorted_machine_names[i].nombre_maquina,machine_names[i].nombre_maquina);
		sorted_machine_names[i].id=machine_names[i].id;
	}

	//Array de punteros para poderlos ordenar
	struct s_machine_names **memoria_punteros;

        
	//Asignamos memoria
    memoria_punteros=malloc(sizeof(struct dirent *)*total_maquinas);


    if (memoria_punteros==NULL) {
                cpu_panic("Error allocating memory when sorting machine list");
    }	

	//Meter en esa lista de punteros cada item de la estructura
	for (i=0;i<total_maquinas;i++) {
		memoria_punteros[i]=&sorted_machine_names[i];
	}

	//Ordenar ese listado de punteros

	//lanzar qsort
	int (*funcion_compar)(const void *, const void *);

	funcion_compar=( int (*)(const void *, const void *)  ) menu_machine_selection_by_name_alphasort;

	qsort(memoria_punteros,total_maquinas,sizeof(struct s_machine_names *), funcion_compar);	

	//Imprimir listado de memoria
	/*for (i=0;i<total_maquinas;i++) {
		printf ("sorted id: %03d nombre: %s\n",memoria_punteros[i]->id,memoria_punteros[i]->nombre_maquina);

	}
	*/	


	//Meter cada uno en menu. Asignar id maquina como valor_opcion

	//Dado que es una variable local, siempre podemos usar este nombre array_menu_common
	menu_item *array_menu_common;
	menu_item item_seleccionado;
	int retorno_menu;

	
	do {


		//Como no sabemos cual sera el item inicial, metemos este sin asignar, que se sobreescribe en el siguiente menu_add_item_menu
		menu_add_item_menu_inicial(&array_menu_common,"",MENU_OPCION_UNASSIGNED,NULL,NULL);

		for (i=0;i<total_maquinas;i++) {
			//printf ("sorted id: %03d nombre: %s\n",memoria_punteros[i]->id,memoria_punteros[i]->nombre_maquina);
			menu_add_item_menu_format(array_menu_common,MENU_OPCION_NORMAL,menu_machine_selection_by_name_set,NULL,memoria_punteros[i]->nombre_maquina);

			menu_add_item_menu_valor_opcion(array_menu_common,memoria_punteros[i]->id);

			//Si coincide id con la maquina actual, cambiar menu_machine_selection_by_name_opcion_seleccionada
			if (current_machine_type==memoria_punteros[i]->id) {
				menu_machine_selection_by_name_opcion_seleccionada=i;
				//printf ("Match current machine %d with list entry %d. Changing last selected\n",current_machine_type,i);
			}

		}	
			
        menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

        //Hotswap de Z88 o Jupiter Ace o CHLOE no existe
        menu_add_item_menu(array_menu_common,"~~Hotswap machine",MENU_OPCION_NORMAL,menu_hotswap_machine,menu_hotswap_machine_cond);
        menu_add_item_menu_shortcut(array_menu_common,'h');
        menu_add_item_menu_tooltip(array_menu_common,"Change machine type without resetting");
        menu_add_item_menu_ayuda(array_menu_common,"Change machine type without resetting.");
        menu_add_item_menu_tiene_submenu(array_menu_common);

        menu_add_item_menu(array_menu_common,"Custom machine",MENU_OPCION_NORMAL,menu_custom_machine,NULL);
        menu_add_item_menu_spanish(array_menu_common,"Maquina personalizada");
        menu_add_item_menu_tooltip(array_menu_common,"Specify custom machine type & ROM");
        menu_add_item_menu_ayuda(array_menu_common,"Specify custom machine type & ROM");
        menu_add_item_menu_tiene_submenu(array_menu_common);		
					
		menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

		menu_add_ESC_item(array_menu_common);

		retorno_menu=menu_dibuja_menu(&menu_machine_selection_by_name_opcion_seleccionada,&item_seleccionado,array_menu_common,"Select Machine" );

			
			if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
					//llamamos por valor de funcion
					if (item_seleccionado.menu_funcion!=NULL) {
							//printf ("actuamos por funcion\n");
							item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
							
					}
			}

	} while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);	


	free(sorted_machine_names);
	free(memoria_punteros);
			

 

}

void menu_machine_selection(MENU_ITEM_PARAMETERS)
{
	if (setting_machine_selection_by_name.v==0) {
		menu_machine_selection_manufacturer(0);
	}
	else {
		menu_machine_selection_by_name(0);
	}
}


void menu_about_read_file(char *title,char *aboutfile,int show_err_if_big)
{

    char *about_file=util_malloc(MAX_TEXTO_GENERIC_MESSAGE,"Can not allocate memory for reading the file");

	debug_printf (VERBOSE_INFO,"Loading %s File",aboutfile);
	FILE *ptr_aboutfile;
	//ptr_aboutfile=fopen(aboutfile,"rb");
	open_sharedfile(aboutfile,&ptr_aboutfile);

	if (!ptr_aboutfile)
	{
		debug_printf (VERBOSE_ERR,"Unable to open %s file",aboutfile);
	}
	else {

		int leidos=fread(about_file,1,MAX_TEXTO_GENERIC_MESSAGE,ptr_aboutfile);
		debug_printf (VERBOSE_INFO,"Read %d bytes of file: %s",leidos,aboutfile);

        int message_verbose=VERBOSE_DEBUG;

		if (leidos==MAX_TEXTO_GENERIC_MESSAGE) {
            if (show_err_if_big) {
			    message_verbose=VERBOSE_ERR;
            }

            debug_printf (message_verbose,"Reached maximum text buffer: %d bytes. Showing only the first %d bytes",leidos,leidos);
			leidos--;
		}

		about_file[leidos]=0;


		fclose(ptr_aboutfile);

		menu_generic_message(title,about_file);

	}

    free(about_file);

}

void menu_about_changelog(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("Changelog","Changelog",1);
}


void menu_about_history(MENU_ITEM_PARAMETERS)
{
	menu_about_read_file("History","HISTORY",1);
}

void menu_about_features(MENU_ITEM_PARAMETERS)
{
    if (gui_language==GUI_LANGUAGE_SPANISH) {
        menu_about_read_file("Caracteristicas","FEATURES_es",1);
    }
    else menu_about_read_file("Features","FEATURES",1);
}

void menu_about_exclusivefeatures(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("Exclusive Features","EXCLUSIVEFEATURES",1);
}

void menu_about_readme(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("Readme","README",1);
}


void menu_about_install(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("Install","INSTALL",1);
}

void menu_about_installwindows(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("Install on Windows","INSTALLWINDOWS",1);
}

void menu_about_alternate_roms(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("Alternate ROMS","ALTERNATEROMS",1);
}

void menu_about_included_tapes(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("Included Tapes","INCLUDEDTAPES",1);
}



void menu_about_acknowledgements(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("Acknowledgements","ACKNOWLEDGEMENTS",1);
}

void menu_about_donate(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("Donate","DONATE",1);
}

void menu_about_faq(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("FAQ","FAQ",1);
}

void menu_about_license(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("ZEsarUX License","LICENSE",1);
}

void menu_about_licenses_info(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("Licenses information","LICENSES_info",1);
}

void menu_about_license_motorola_core(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("Motorola Core License","licenses/LICENSE_MOTOROLA_CORE",1);
}

void menu_about_license_scmp_core(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("SCMP Core License","licenses/LICENSE_SCMP_CORE",1);
}

void menu_about_license_scl2trd(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("scl2trd License","licenses/LICENSE_scl2trd",1);
}

void menu_about_license_fuse(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("Fuse License","licenses/LICENSE_fuse",1);
}

void menu_about_license_atomlite(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("SimCoupe License","licenses/LICENSE_simcoupe",1);
}

void menu_about_license_dosfont(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("DOS font License","licenses/LICENSE_DOS_font",1);
}

void menu_about_license_unrealspeccy(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("UnrealSpeccy License","licenses/LICENSE_unrealspeccy",1);
}

void menu_about_license_mdvtool(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("mdvtool License","licenses/LICENSE_mdvtool",1);
}

void menu_about_license_zip(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("zip License","licenses/LICENSE_zip",1);
}

void menu_about_license_unpaws(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("unpaws/unquill License","licenses/LICENSE_unpaws",1);
}

void menu_about_license_undaad(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("undaad License","licenses/LICENSE_undaad",1);
}

void menu_about_license_grackle(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("grackle License","licenses/LICENSE_grackle",1);
}

void menu_about_license_ungac(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("ungac License","licenses/LICENSE_ungac",1);
}

void menu_about_license_qemu(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("Qemu License","licenses/LICENSE_qemu",1);
}

void menu_about_license_hilow(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("Hilow License","licenses/LICENSE_hilow",1);
}

void menu_about_license_fatfs(MENU_ITEM_PARAMETERS)
{
        menu_about_read_file("FatFs License","licenses/LICENSE_FatFs",1);
}


void menu_about_statistics(MENU_ITEM_PARAMETERS)
{

 int tiempo_trabajado_en_zesarux=timer_get_worked_time();

	menu_generic_message_format("Statistics",
		"Source code lines: %d\n"
        "Approximate TODOs: %d\n"
		"Total time used on coding ZEsarUX: ^^%d^^ hours (and growing)\n"
		"ZEsarUX yesterday users: %s\n"

		"\n"
		"Edited with Visual Studio Code and vim\n"
		"Developed on macOS Catalina, Debian 10, Raspbian, FreeBSD 12, and MinGW environment on Windows\n"
		,
        LINES_SOURCE,
        TOTAL_TODO_ITEMS,
        tiempo_trabajado_en_zesarux,
		(stats_last_yesterday_users[0]==0 ? "Unknown" : stats_last_yesterday_users)
        
		);

}


void menu_about_running_info(MENU_ITEM_PARAMETERS)
{

	char string_video_drivers[1024];
	char string_audio_drivers[1024];
	int driver;

	int i;

	i=0;
        for (driver=0;driver<num_scr_driver_array;driver++) {
		sprintf(&string_video_drivers[i],"%s ",scr_driver_array[driver].driver_name);
		i=i+strlen(scr_driver_array[driver].driver_name)+1;
	}
	string_video_drivers[i]=0;


	i=0;
        for (driver=0;driver<num_audio_driver_array;driver++) {
                sprintf(&string_audio_drivers[i],"%s ",audio_driver_array[driver].driver_name);
                i=i+strlen(audio_driver_array[driver].driver_name)+1;
        }
        string_audio_drivers[i]=0;

				char configfile[PATH_MAX];

				if (util_get_configfile_name(configfile)==0)  {
					sprintf(configfile,"Unknown");
				}

				int uptime_seconds=timer_get_uptime_seconds();

				char hora_inicio[100];
				timer_get_texto_time(&zesarux_start_time,hora_inicio);


	//int cpu_use_total_acumulado=0;
	//int cpu_use_total_acumulado_medidas=0;

	/*int media_cpu=0;

	if (cpu_use_total_acumulado_medidas>0) {
		media_cpu=cpu_use_total_acumulado/cpu_use_total_acumulado_medidas;
	}*/

    int media_cpu=sensor_get_percentaje_value("total_avg_cpu");

	char mensaje_cpu_usage[100];

    //por defecto
    mensaje_cpu_usage[0]=0;

    //Uso cpu no se ve en windows
#ifndef MINGW
	if (screen_show_cpu_usage.v && menu_footer) {
		sprintf(mensaje_cpu_usage,"Total Average CPU Use: %d%%\n",media_cpu);
	}
#endif
	
	char mensaje_total_uptime[100];

	//tiempo total de uso del emulador solo si esta guardado de config
	if (save_configuration_file_on_exit.v) {
		sprintf (mensaje_total_uptime,"Total minutes use %d mins\n",
  		stats_get_current_total_minutes_use() );
	}
	else {
		mensaje_total_uptime[0]=0;
	}

	//guardamos directorio actual
	char directorio_actual[PATH_MAX];
	getcwd(directorio_actual,PATH_MAX);	

	menu_generic_message_format("Running info",
		"Video Driver: %s\nAvailable video drivers: %s\n\nAudio Driver: %s\nAvailable audio drivers: %s\n\n"
		"Current directory: %s\n\n"

#if defined(__APPLE__)
		"Executable path: %s\n\n"
#endif

		"Configuration file: %s\n\n"
		"Start time: %s\n"
		"Uptime %d secs (%d mins)\n"
		"%s"
		"%s"
		,
		scr_new_driver_name,string_video_drivers,audio_new_driver_name,string_audio_drivers,
		directorio_actual,

#if defined(__APPLE__)
		macos_path_to_executable,
#endif

		configfile,hora_inicio,
		uptime_seconds,uptime_seconds/60,mensaje_total_uptime,mensaje_cpu_usage);

	//Average CPU use solo sale si screen_show_cpu_usage.v




}

void menu_about_about_load_editionamegame(void)
{
    if (si_existe_editionnamegame(NULL)) {
        util_load_editionnamegame();
        salir_todos_menus=1;
    }
    else {
        //Se ha seleccionado texto edition name pero el juego no esta disponible
        debug_printf(VERBOSE_INFO,"Edition name game %s is not available",EMULATOR_GAME_EDITION);
    }
}

void menu_about_about(MENU_ITEM_PARAMETERS)
{

	char mensaje_about[1024];
	unsigned char letra_enye,letra_e_acentuada,letra_a_acentuada,letra_o_acentuada;


	if (si_complete_video_driver() ) {
		//mensaje completo con enye en segundo apellido y acentos
        //TODO: arreglar los charset para que los acentos sean letras igual en cada charset con acento
        //TODO: hacer lo mismo cuando zx desktop activo (menu_about_new)
		letra_enye=129;
        letra_e_acentuada=143;
        letra_a_acentuada=142;
        letra_o_acentuada=145;
	}

	else {
		//mensaje con n en vez de enye, y acentos
		letra_enye='n';
        letra_e_acentuada='e';
        letra_a_acentuada='a';
        letra_o_acentuada='o';        
	} 

	sprintf (mensaje_about,"ZEsarUX v." EMULATOR_VERSION " (" EMULATOR_SHORT_DATE ")\n"
        " - " EMULATOR_EDITION_NAME " - \n"
        "(C) 2013 Cesar Hernandez Ba%co\n"
        //"(C) 2013 C%csar Hern%cndez Ba%c%c\n"

#ifdef SNAPSHOT_VERSION
        "Build number: " BUILDNUMBER "\n"
#endif

                        
        ,letra_enye);
        //,letra_e_acentuada,letra_a_acentuada,letra_enye,letra_o_acentuada);
                                        

	


	generic_message_tooltip_return retorno_ventana;
	
	zxvision_generic_message_tooltip("About" , 0 ,0,0,0,&retorno_ventana,0,mensaje_about);

	

	//Si se sale con ESC
    if (retorno_ventana.estado_retorno==0) return;

	//Linea seleccionada es 1? quiere decir que se selecciona texto "--- edition"
/*
	Por defecto, linea seleccionada es 0, incluso aunque no se haya habilitado linea de cursor, por ejemplo
	al buscar texto con f y n
	Como la que buscamos es la 1, no hay problema de falso positivo
*/
	int linea=retorno_ventana.linea_seleccionada;

	//printf ("retorno ventana linea: %d\n",retorno_ventana.linea_seleccionada);

	debug_printf(VERBOSE_INFO,"Closing window with Enter and selected line=%d",linea);
	if (linea==1) {
		menu_about_about_load_editionamegame();
	}

}


void menu_about_compile_info(MENU_ITEM_PARAMETERS)
{
        char buffer[MAX_COMPILE_INFO_LENGTH];
        get_compile_info(buffer);

	menu_generic_message("Compile info",
		buffer
	);
}


void menu_about_help(MENU_ITEM_PARAMETERS)
{

	if (!menu_cond_stdout() ) {
		menu_generic_message("Help",
			"Use cursor keys to move\n"
			"Press F1 (or h on some video drivers) on an option to see its help\n"
			"Press Enter to select a menu item\n"
			"Press Space on some menu items to enable/disable\n"
			"Press a key between a and z to select an entry with shortcuts; shortcut clues appear when you wait some seconds or press a key "
			"not associated with any shortcut.\n"
			"Unavailable options may be hidden, or disabled, which are shown with red colour or with x cursor on some video drivers\n"
            "Character > on the right of a menu item means the menu has submenus\n"
			"ESC Key gives you to the previous menu, except in the case with aalib driver and pure text console, which is changed to another key (shown on the menu). On curses driver, ESC key is a bit slow, you have to wait one second after pressing it; you can also use key @ to simulate ESC on menu on curses driver. "
			"\n\n"
			"On File Browser:\n"
			"- Use cursors and PgDn/Up\n"
			"- Use Enter or left mouse click to select item. Compressed files will be opened like folders\n"
			"- Use Space to expand files, currently supported:\n"
            "dsk, epr, eprom, flash, hdf, mdv, o, p, pzx, scl, tap, trd, tzx and also all the compressed supported files.\n"
            "- When moving the cursor, a small preview of the screen in the file is shown, currently supported files for preview:\n"
            "dsk, p, pzx, scr, sna, sp, tap, trd, tzx, z80, zsf\n"
			"- Use TAB to change section\n"
			"- Use Space/cursor on filter to change filter\n"
			"- Press the initial letter \n"
			"for faster searching\n"
            "\n"
			"When using fileselector from file utilities menu:\n"
			"- Press shift+key to select functions, like shift+v to view files or shift+d to select Drive\n"
            "- Currently supported files on Viewer:\n"
            "b, bas, basz88, baszx80, baszx81, cas, cdt, col, dsk, epr, eprom, flash, "
            "ide, mmc, mmcide, nex, o, p, pzx, sna, snx, sp, spg, tap, trd, tzx, z80, zsf, zx and text files.\n"
			"\n"
			"On message windows:\n"
			"- Use cursors and PgDn/Up\n"
			"- Use f and n to find text\n"
			"- Use c to copy to ZEsarUX clipboard\n"
			"\n"
            "On input fields, press cursor down to delete all input text.\n"
			"On numeric input fields, numbers can be written on decimal, hexadecimal (with suffix H), binary (with suffix %) or as a character (with quotes '' or \"\")\n\n"
			"Symbols on menu must be written according to the Spectrum keyboard mapping, so for example, to write the symbol minus (<), you have to press "
			"ctrl(symbol shift)+r. You should use ctrl/alt (no need to Spectrum extended mode) to write any of the following: ~|\\{}[], located on letters asdfgyu\n\n"
			"\n"
			"On ZX-Vision windows:\n"
			"- Use mouse to move windows dragging from the title bar\n"
			"- Drag mouse from the bottom-right part of the window to resize it\n"
            "- Click on the minimize button (-) to minimize the window\n"
			"- Click on the maximize button (+) or double click on the title bar to maximize the window\n"
            "- Click on the recover button (=) to recover previous size after a minimize or maximize action\n"
			"- Click out of the window to put the focus on the emulated machine and send there keyboard presses\n"
			"- Can also be moved with the keyboard: Shift+QAOP\n"
			"- Can also be resized with the keyboard: Shift+WSKL\n"
			"Note: non ZX-Vision windows are marked with a small pixel in the right of the title bar\n"

			"\n"

			"Inside a machine, the keys are mapped this way:\n"
			"ESC: If text to speech is not enabled, sends Shift+Space (break) on Spectrum. If enabled, stops playing text to speech\n"
			"CTRL/ALT: Symbol shift\n"
			"TAB: Extended mode (symbol shift + caps shift)\n"
			"\n"
			"F4: When menu is closed, send Spectrum display content to speech program, including only known characters (unknown characters are shown as a space). "
			"When menu is opened, it will read the window contents and send it to speech program, even if it has already been read again\n"
			"F5: Open menu\n"
			"F8: Open On Screen Keyboard (only on Spectrum & ZX80/81)\n"
			"F9: Open Smart Load window\n"
			"\n"
			"On Z88, the following keys have special meaning:\n"
			"F1: Help\n"
			"F2: Index\n"
			"F3: Menu\n"
			"CTRL: Diamond\n"
			"ALT: Square\n"
			"\n"
			"Note: Drivers curses, aa, caca do not read CTRL or ALT. Instead, you can use F6 for CTRL and F7 for ALT on these drivers.\n"
	);
	}

	else {
		menu_generic_message("Help","Press h<num> to see help for <num> option, for example: h3\n"
				"Press t<num> to see tooltip for <num> option\n"
				"Unavailable options may be hidden, or disabled, which are shown with x cursor\n"
				"ESC text gives you to the previous menu\n"
				"On fileselector, write the file without spaces\n"
				"On input fields, numbers can be written on decimal or hexadecimal (with suffix H)\n"
	);
	}

}


void menu_help_background_windows(MENU_ITEM_PARAMETERS)
{

	
		menu_generic_message("Background Windows Help",
			"When you enable Background Windows (from Settings-> ZX Vision), "
			"some features are added to the ZX Desktop and some behaviour is modified. \n"
			"\n"
			"First, we will refer to 'menu' to all the menu windows and all the windows in background. "
			"When we say that the 'menu is open' or the 'menu is closed', we refer to all the menu windows and all the windows "
			"in background, that they are visible and can be interacted with them or not "
            "(enabling setting background windows+even when menu closed, shows windows in background but you can't interact with them). \n"
			"\n"
			"We will refer to 'main menu' to the main ZEsarUX menu window (the one with Smartload, Machine, etc). \n"
			"\n"
			"Windows that can be sent to background, have a button (exclamation mark !, or a shaded button) in the window title. \n"
			"Pressing that button (or F6 key) will send the window to the background and then, "
            "if background windows setting is enabled even when menu closed, the menu will be closed; otherwise, it will go back to the previous window. \n"
			"\n"
			"A window in the background is open, doesn't have the focus, and usually is refreshing its contents "
			"(we will talk about it later). \n"
			"If you click to another window, the current window will be sent to background, if it allows to do it. "
			"If it's not allowed, the current window will be closed. \n"
			"Some background windows don't refresh their contents when they are in background, like Debug CPU. \n"
			"\n"
			"Pressing F5 when on menu or pressing the ZEsarUX logo button (on the top left of ZX Desktop) will send you back to the main menu.\n"
            "Pressing Shift+Cursor Right will switch to another background window.\n"
			"\n"
			
			"Pressing window close button, ESC or right click on the mouse it always closes the current window (same behaviour with background windows disabled). \n" 
			"\n"
			"When menu is open, pressing on the emulated machine section (usually on the left), the keyboard focus is lost from the menu "
			"and goes to the emulated machine. To return the keyboard focus to the menu, press on any of the background windows, "
			"or in the ZEsarUX logo, or press F5. \n"
			"\n"
			"Pressing ESC on the main menu, makes disappear all windows. But pressing F5 again will restore all windows. \n"
			"Keep in mind that F-keys are only read when menu is closed (except F4, F5 and F6, which are also read with menu open). "
			"\n"
			"You can enable a setting to restore windows when ZEsarUX is opened (from Settings-> ZX Vision-> "
			"Reopen windows on start). \n"
			"\n"
            "You can enable a setting to view windows in background even when menu closed (but you can't interact with them), "
            "from Settings-> ZX Vision-> Background Windows-Even when menu closed\n"
			"You can have background windows enabled but multitasking disabled (not recommended, but allowed). "

			
	);


}


void menu_licenses(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_common;
        menu_item item_seleccionado;
        int retorno_menu;
        do {
        
            menu_add_item_menu_inicial(&array_menu_common,"~~Information",MENU_OPCION_NORMAL,menu_about_licenses_info,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'i');

            menu_add_item_menu(array_menu_common,"~~ZEsarUX",MENU_OPCION_NORMAL,menu_about_license,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'z');

			menu_add_item_menu(array_menu_common,"~~Atomlite (from simcoupe)",MENU_OPCION_NORMAL,menu_about_license_atomlite,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'a');	

			menu_add_item_menu(array_menu_common,"D~~OS font",MENU_OPCION_NORMAL,menu_about_license_dosfont,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'o');

			menu_add_item_menu(array_menu_common,"Fa~~tFs",MENU_OPCION_NORMAL,menu_about_license_fatfs,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'t');	
            
			menu_add_item_menu(array_menu_common,"~~Fuse disassembler",MENU_OPCION_NORMAL,menu_about_license_fuse,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'f');	

			menu_add_item_menu(array_menu_common,"~~grackle",MENU_OPCION_NORMAL,menu_about_license_grackle,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'g');

			menu_add_item_menu(array_menu_common,"~~Hilow",MENU_OPCION_NORMAL,menu_about_license_hilow,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'h');

			menu_add_item_menu(array_menu_common,"m~~dvtool",MENU_OPCION_NORMAL,menu_about_license_mdvtool,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'d');	

			menu_add_item_menu(array_menu_common,"~~Motorola Core",MENU_OPCION_NORMAL,menu_about_license_motorola_core,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'m');

			menu_add_item_menu(array_menu_common,"~~Qemu Mac OS video driver",MENU_OPCION_NORMAL,menu_about_license_qemu,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'q');				

			menu_add_item_menu(array_menu_common,"s~~cl2trd",MENU_OPCION_NORMAL,menu_about_license_scl2trd,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'c');			

			menu_add_item_menu(array_menu_common,"~~SCMP Core",MENU_OPCION_NORMAL,menu_about_license_scmp_core,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'s');

			menu_add_item_menu(array_menu_common,"SPG ~~loader (from unrealspeccy)",MENU_OPCION_NORMAL,menu_about_license_unrealspeccy,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'l');				

			menu_add_item_menu(array_menu_common,"~~undaad",MENU_OPCION_NORMAL,menu_about_license_undaad,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'u');		
			
			menu_add_item_menu(array_menu_common,"u~~ngac",MENU_OPCION_NORMAL,menu_about_license_ungac,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'n');

			menu_add_item_menu(array_menu_common,"unpa~~ws/unquill",MENU_OPCION_NORMAL,menu_about_license_unpaws,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'w');						

			menu_add_item_menu(array_menu_common,"zi~~p",MENU_OPCION_NORMAL,menu_about_license_zip,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'p');
					

            menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

            menu_add_ESC_item(array_menu_common);

            retorno_menu=menu_dibuja_menu(&licenses_opcion_seleccionada,&item_seleccionado,array_menu_common,"Licenses" );

			

            if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
            	//llamamos por valor de funcion
                if (item_seleccionado.menu_funcion!=NULL) {
                	//printf ("actuamos por funcion\n");
                    item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                    
                }
            }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);

}

int if_menu_new_about_is_available(void)
{
    //No hacer si no hay driver grafico completo
    if (!si_complete_video_driver()) return 0;

    //Solo cuando zx desktop activado y soportado por el driver
    if (!if_zxdesktop_enabled_and_driver_allows()) return 0;

    return 1;
}

void menu_about_about_which(MENU_ITEM_PARAMETERS)
{
    if (if_menu_new_about_is_available()) menu_about_new(0);
    else menu_about_about(0);
}


void menu_help(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_common;
        menu_item item_seleccionado;
        int retorno_menu;
        do {
            menu_add_item_menu_inicial(&array_menu_common,"~~About",MENU_OPCION_NORMAL,menu_about_about_which,NULL);
            menu_add_item_menu_spanish_catalan(array_menu_common,"~~Acerca de","Quant ~~a");
			menu_add_item_menu_shortcut(array_menu_common,'a');

			menu_add_item_menu(array_menu_common,"~~Help",MENU_OPCION_NORMAL,menu_about_help,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'h');

			menu_add_item_menu(array_menu_common,"~~Background Windows Help",MENU_OPCION_NORMAL,menu_help_background_windows,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'b');

			menu_add_item_menu(array_menu_common,"~~Keyboard Help",MENU_OPCION_NORMAL,menu_help_show_keyboard,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'k');			

			menu_add_item_menu(array_menu_common,"~~Readme",MENU_OPCION_NORMAL,menu_about_readme,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'r');

			menu_add_item_menu(array_menu_common,"~~Features",MENU_OPCION_NORMAL,menu_about_features,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'f');

			menu_add_item_menu_en_es_ca(array_menu_common,MENU_OPCION_NORMAL,menu_about_exclusivefeatures,NULL,
                "E~~xclusive features","Caracteristicas e~~xclusivas","Caracteristiques e~~xclusives");
			menu_add_item_menu_shortcut(array_menu_common,'x');            

            menu_add_item_menu(array_menu_common,"H~~istory",MENU_OPCION_NORMAL,menu_about_history,NULL);
            menu_add_item_menu_spanish(array_menu_common,"H~~istoria");
			menu_add_item_menu_shortcut(array_menu_common,'i');

            menu_add_item_menu_en_es_ca(array_menu_common,MENU_OPCION_NORMAL,menu_about_acknowledgements,NULL,
                "A~~cknowledgements","Agrade~~cimientos","Re~~coneixements");
			menu_add_item_menu_shortcut(array_menu_common,'c');

			menu_add_item_menu(array_menu_common,"~~Donate",MENU_OPCION_NORMAL,menu_about_donate,NULL);
            menu_add_item_menu_spanish(array_menu_common,"~~Donar");
			menu_add_item_menu_shortcut(array_menu_common,'d');

			menu_add_item_menu(array_menu_common,"FA~~Q",MENU_OPCION_NORMAL,menu_about_faq,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'q');

			menu_add_item_menu(array_menu_common,"Cha~~ngelog",MENU_OPCION_NORMAL,menu_about_changelog,NULL);
			menu_add_item_menu_shortcut(array_menu_common,'n');

			menu_add_item_menu_en_es_ca(array_menu_common,MENU_OPCION_NORMAL,menu_about_alternate_roms,NULL,
                "Alternate RO~~MS","RO~~MS alternativas","RO~~MS alternatives");
			menu_add_item_menu_shortcut(array_menu_common,'m');

			menu_add_item_menu_en_es_ca(array_menu_common,MENU_OPCION_NORMAL,menu_about_included_tapes,NULL,
                "Included ~~tapes","Cin~~tas incluidas","Cin~~tes incloses");
			menu_add_item_menu_shortcut(array_menu_common,'t');

			menu_add_item_menu(array_menu_common,"Insta~~ll",MENU_OPCION_NORMAL,menu_about_install,NULL);
            menu_add_item_menu_spanish(array_menu_common,"Insta~~lar");
			menu_add_item_menu_shortcut(array_menu_common,'l');

			menu_add_item_menu_en_es_ca(array_menu_common,MENU_OPCION_NORMAL,menu_about_installwindows,NULL,
                "Install on ~~Windows","Instalar en ~~Windows","Instalar a ~~Windows");
			menu_add_item_menu_shortcut(array_menu_common,'w');

            menu_add_item_menu_en_es_ca(array_menu_common,MENU_OPCION_NORMAL,menu_about_compile_info,NULL,
                "C~~ompile info","Informacion de c~~ompilacion","Informacio de c~~ompilacio");
			menu_add_item_menu_shortcut(array_menu_common,'o');			

            menu_add_item_menu_en_es_ca(array_menu_common,MENU_OPCION_NORMAL,menu_about_statistics,NULL,
                "~~Statistics","E~~stadisticas","E~~stadistiques");
			menu_add_item_menu_shortcut(array_menu_common,'s');

            menu_add_item_menu_en_es_ca(array_menu_common,MENU_OPCION_NORMAL,menu_about_core_statistics,NULL,
                "Core Statistics","Estadisticas del nucleo","Estadistiques del nucli");
			//menu_add_item_menu_shortcut(array_menu_common,'r');

			menu_add_item_menu_en_es_ca(array_menu_common,MENU_OPCION_NORMAL,menu_about_running_info,NULL,
                "R~~unning info","Informacion de ejec~~ucion","Informacio d'exec~~ucio");
			menu_add_item_menu_shortcut(array_menu_common,'u');

			menu_add_item_menu_en_es_ca(array_menu_common,MENU_OPCION_NORMAL,menu_licenses,NULL,
                "Lic~~enses","Lic~~encias","Llic~~encies");
			menu_add_item_menu_shortcut(array_menu_common,'e');
            menu_add_item_menu_tiene_submenu(array_menu_common);



            menu_add_item_menu(array_menu_common,"",MENU_OPCION_SEPARADOR,NULL,NULL);

            menu_add_ESC_item(array_menu_common);

            retorno_menu=menu_dibuja_menu(&about_opcion_seleccionada,&item_seleccionado,array_menu_common,"Help" );

			

            if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
            	//llamamos por valor de funcion
                if (item_seleccionado.menu_funcion!=NULL) {
                	//printf ("actuamos por funcion\n");
                    item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                    
                }
            }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);

}




void menu_input_file_keyboard_insert(MENU_ITEM_PARAMETERS)
{

        if (input_file_keyboard_inserted.v==0) {
                input_file_keyboard_init();
        }

        else if (input_file_keyboard_inserted.v==1) {
                input_file_keyboard_close();
        }

}



int menu_input_file_keyboard_cond(void)
{
        if (input_file_keyboard_name!=NULL) return 1;
        else return 0;
}

void menu_input_file_keyboard_delay(MENU_ITEM_PARAMETERS)
{

    //Final valor =>  input_file_keyboard_delay=((Valor en ms)*50)/1000
    int valor_ms=util_get_input_file_keyboard_ms();

    menu_ventana_scanf_numero_enhanced("Key length",&valor_ms,5,+20,20,2000,1);


    input_file_keyboard_delay=(valor_ms*50)/1000;

    //Por si acaso controlar los limites despues de hacer este calculo
    //1->20 ms. 100->2000 ms
    if (input_file_keyboard_delay<1 || input_file_keyboard_delay>100) input_file_keyboard_delay=1;
    

}

void menu_input_file_keyboard(MENU_ITEM_PARAMETERS)
{

        input_file_keyboard_inserted.v=0;
		input_file_keyboard_playing.v=0;


        char *filtros[2];

        filtros[0]="txt";
        filtros[1]=0;


        if (menu_filesel("Select Spool File",filtros,input_file_keyboard_name_buffer)==1) {
		input_file_keyboard_name=input_file_keyboard_name_buffer;

        }

        else {
		input_file_keyboard_name=NULL;
		eject_input_file_keyboard();
        }
}


void menu_input_file_keyboard_send_pause(MENU_ITEM_PARAMETERS)
{
	input_file_keyboard_send_pause.v ^=1;
}


void menu_input_file_keyboard_turbo(MENU_ITEM_PARAMETERS)
{

	if (input_file_keyboard_turbo.v) {
		reset_peek_byte_function_spoolturbo();
		input_file_keyboard_turbo.v=0;
	}

	else {
		set_peek_byte_function_spoolturbo();
		input_file_keyboard_turbo.v=1;
	}
}


int menu_input_file_keyboard_turbo_cond(void)
{
	if (MACHINE_IS_SPECTRUM) return 1;
    //if (MACHINE_IS_ACE) return 1;
	return 0;
}


void menu_input_file_keyboard_play(MENU_ITEM_PARAMETERS)
{
	input_file_keyboard_playing.v ^=1;
}

void menu_debug_input_file_keyboard(MENU_ITEM_PARAMETERS)
{
    menu_item *array_menu_input_file_keyboard;
    menu_item item_seleccionado;
    int retorno_menu;

    do {

        char string_input_file_keyboard_shown[16];
        menu_tape_settings_trunc_name(input_file_keyboard_name,string_input_file_keyboard_shown,16);
        menu_add_item_menu_inicial_format(&array_menu_input_file_keyboard,MENU_OPCION_NORMAL,menu_input_file_keyboard,NULL,"Spool file [%s]",string_input_file_keyboard_shown);


        menu_add_item_menu_format(array_menu_input_file_keyboard,MENU_OPCION_NORMAL,menu_input_file_keyboard_insert,menu_input_file_keyboard_cond,"[%c] Spool file inserted",(input_file_keyboard_inserted.v ? 'X' : ' ' ));
        if (input_file_keyboard_inserted.v) {

            menu_add_item_menu_format(array_menu_input_file_keyboard,MENU_OPCION_NORMAL,menu_input_file_keyboard_play,NULL,"[%c] Spool file playing",(input_file_keyboard_playing.v ? 'X' : ' ' ));	

            //en tbblue no va bien la opcion de turbo
            if (!MACHINE_IS_TBBLUE) {
                menu_add_item_menu_format(array_menu_input_file_keyboard,MENU_OPCION_NORMAL,menu_input_file_keyboard_turbo,menu_input_file_keyboard_turbo_cond,"[%c] Turbo mode",(input_file_keyboard_turbo.v ? 'X' : ' ') );
                menu_add_item_menu_tooltip(array_menu_input_file_keyboard,"Allow turbo mode on Spectrum models");
                menu_add_item_menu_ayuda(array_menu_input_file_keyboard,"Allow turbo mode on Spectrum models. It traps calls to ROM when keyboard is read.\n"
                                    "Works well with Spectrum Basic but also with Text Adventures made with Daad, Paws and GAC");
            }


            if (input_file_keyboard_turbo.v==0) {

                            menu_add_item_menu_format(array_menu_input_file_keyboard,MENU_OPCION_NORMAL,menu_input_file_keyboard_delay,NULL,"[%d ms] Key length",util_get_input_file_keyboard_ms() );
                            menu_add_item_menu_tooltip(array_menu_input_file_keyboard,"Length of every key pressed");
                            menu_add_item_menu_ayuda(array_menu_input_file_keyboard,"I recommend 100 ms for entering lines on Spectrum BASIC. I also suggest to send some manual delays, using unhandled character, like \\, to assure entering lines is correct ");

                            menu_add_item_menu_format(array_menu_input_file_keyboard,MENU_OPCION_NORMAL,menu_input_file_keyboard_send_pause,NULL,"[%c] Delay after every key",(input_file_keyboard_send_pause.v==1 ? 'X' : ' ') );
                            menu_add_item_menu_tooltip(array_menu_input_file_keyboard,"Send or not a delay of the same duration after every key");
                            menu_add_item_menu_ayuda(array_menu_input_file_keyboard,"I recommend enabling this for entering lines on Spectrum BASIC");

            }
        }


        menu_add_item_menu(array_menu_input_file_keyboard,"",MENU_OPCION_SEPARADOR,NULL,NULL);
        
        menu_add_ESC_item(array_menu_input_file_keyboard);

        retorno_menu=menu_dibuja_menu(&input_file_keyboard_opcion_seleccionada,&item_seleccionado,array_menu_input_file_keyboard,"Input File Spooling" );
    

        if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                //llamamos por valor de funcion
                if (item_seleccionado.menu_funcion!=NULL) {
                        //printf ("actuamos por funcion\n");
                        item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                        
                }
        }

    } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);
}






//menu audio 
void menu_audio(MENU_ITEM_PARAMETERS)
{
    menu_item *array_menu_audio;
    menu_item item_seleccionado;
    int retorno_menu;

    do {

				

        menu_add_item_menu_inicial(&array_menu_audio,"Audio Chip ~~Registers",MENU_OPCION_NORMAL,menu_ay_registers,menu_cond_ay_or_sn_chip);
        menu_add_item_menu_spanish_catalan(array_menu_audio,"~~Registros del Chip de Audio","~~Registres del Xip d'Audio");
        menu_add_item_menu_shortcut(array_menu_audio,'r');


        menu_add_item_menu_en_es_ca(array_menu_audio,MENU_OPCION_NORMAL,menu_ay_pianokeyboard,menu_cond_ay_or_sn_chip,
            "Audio Chip P~~iano","P~~iano del Chip de Audio","P~~iano del Xip d'Audio");
        menu_add_item_menu_shortcut(array_menu_audio,'i');
        menu_add_item_menu_tooltip(array_menu_audio,"Shows a piano keyboard with the notes being played on the AY Chip");
        menu_add_item_menu_ayuda(array_menu_audio,"Shows a piano keyboard with the notes being played on the AY Chip");


		if (si_complete_video_driver() ) {
                menu_add_item_menu_en_es_ca(array_menu_audio,MENU_OPCION_NORMAL,menu_ay_partitura,menu_cond_ay_or_sn_chip,
                    "Audio Chip ~~Sheet","Partitura~~s del Chip de Audio","Partiture~~s del Xip d'Audio");
                menu_add_item_menu_shortcut(array_menu_audio,'s');
		}

        menu_add_item_menu_en_es_ca(array_menu_audio,MENU_OPCION_NORMAL,menu_audio_chip_info,menu_cond_ay_or_sn_chip,
            "Audio Chip Info","Info del Chip de Audio","Info del Xip d'Audio");

        if (MACHINE_IS_SPECTRUM && gs_enabled.v) {
            menu_add_item_menu_en_es_ca(array_menu_audio,MENU_OPCION_NORMAL,menu_audio_general_sound,NULL,
                "General Sound Info","General Sound Info","General Sound Info");
        }
					



        menu_add_item_menu_en_es_ca(array_menu_audio,MENU_OPCION_NORMAL,menu_beeper_pianokeyboard,NULL,
            "W~~ave Piano","Pi~~ano de onda","Pi~~ano d'ona");
        menu_add_item_menu_shortcut(array_menu_audio,'a');		
        menu_add_item_menu_tooltip(array_menu_audio,"Shows a piano keyboard with the note being played through the output speakers");
        menu_add_item_menu_ayuda(array_menu_audio,"Shows a piano keyboard with the note being played through the output speakers. "
            "In case you don't have AY sound or DAC audio, that note is the one that is played through the beeper. "
            "It can be inaccurate with short notes");


        

        menu_add_item_menu_en_es_ca(array_menu_audio,MENU_OPCION_NORMAL,menu_audio_new_waveform,NULL,
            "~~Waveform","Forma de onda","Forma d'ona");
        menu_add_item_menu_tooltip(array_menu_audio,"Shows the waveform being played through the output speakers");
        menu_add_item_menu_ayuda(array_menu_audio,"Shows the waveform being played through the output speakers");
        menu_add_item_menu_shortcut(array_menu_audio,'w');

        menu_add_item_menu(array_menu_audio,"",MENU_OPCION_SEPARADOR,NULL,NULL);

        if (MACHINE_IS_QL) {
            menu_add_item_menu_format(array_menu_audio,MENU_OPCION_NORMAL,menu_i8049_mixer,menu_cond_i8049_chip,"i8049 Mi~~xer");
            menu_add_item_menu_shortcut(array_menu_audio,'x');		
        }
        else {
            menu_add_item_menu_format(array_menu_audio,MENU_OPCION_NORMAL,menu_ay_mixer,menu_cond_ay_chip,"AY Mi~~xer");
            menu_add_item_menu_shortcut(array_menu_audio,'x');					
        }
        menu_add_item_menu_tiene_submenu(array_menu_audio);

        menu_add_item_menu_format(array_menu_audio,MENU_OPCION_NORMAL,menu_audio_new_ayplayer,NULL,"AY ~~Player");
        menu_add_item_menu_tooltip(array_menu_audio,"Opens the .ay file player menu");
        menu_add_item_menu_ayuda(array_menu_audio,"Opens the .ay file player menu");
        menu_add_item_menu_shortcut(array_menu_audio,'p');                    


        menu_add_item_menu_en_es_ca(array_menu_audio,MENU_OPCION_NORMAL,menu_record_mid,menu_cond_ay_or_sn_chip,
            "Audio Chip to .~~mid","Audio Chip a .~~mid","Audio Xip a .~~mid");
        menu_add_item_menu_tooltip(array_menu_audio,"Saves music from the AY Chip to a .mid file");
        menu_add_item_menu_ayuda(array_menu_audio,"Saves music from the AY Chip to a .mid file");
        menu_add_item_menu_shortcut(array_menu_audio,'m');
        menu_add_item_menu_tiene_submenu(array_menu_audio);



        menu_add_item_menu(array_menu_audio,"",MENU_OPCION_SEPARADOR,NULL,NULL);


		menu_add_ESC_item(array_menu_audio);

        retorno_menu=menu_dibuja_menu(&audio_opcion_seleccionada,&item_seleccionado,array_menu_audio,"Audio" );

                

		if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
            //llamamos por valor de funcion
            if (item_seleccionado.menu_funcion!=NULL) {
                //printf ("actuamos por funcion\n");
                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                    
            }
		}

	} while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);
}


void menu_debug_reset(MENU_ITEM_PARAMETERS)
{
	if (menu_confirm_yesno("Reset CPU")==1) {
		reset_cpu();
                //Y salimos de todos los menus
                salir_todos_menus=1;
	}

}




void menu_debug_prism_failsafe(MENU_ITEM_PARAMETERS)
{
	if (menu_confirm_yesno("Reset to failsafe?")==1) {
                reset_cpu();

		prism_failsafe_mode.v=1;
		//Para aplicar cambio de pagina rom
		prism_set_memory_pages();

                //Y salimos de todos los menus
                salir_todos_menus=1;
	}
}

void menu_debug_hard_reset(MENU_ITEM_PARAMETERS)
{
        if (menu_confirm_yesno("Hard Reset CPU")==1) {
                hard_reset_cpu();
                //Y salimos de todos los menus
                salir_todos_menus=1;
        }

}


void menu_debug_nmi(MENU_ITEM_PARAMETERS)
{
        if (menu_confirm_yesno("Generate NMI")==1) {

		generate_nmi();

                //Y salimos de todos los menus
                salir_todos_menus=1;
        }

}

void menu_debug_nmi_multiface_tbblue(MENU_ITEM_PARAMETERS)
{
        if (menu_confirm_yesno("Generate Multiface NMI")==1) {

		generate_nmi_multiface_tbblue();

                //Y salimos de todos los menus
                salir_todos_menus=1;
        }

}

void menu_debug_special_nmi(MENU_ITEM_PARAMETERS)
{
        if (menu_confirm_yesno("Generate Special NMI")==1) {

		char string_nmi[4];
		int valor_nmi;

		sprintf (string_nmi,"0");

		//Pedir valor de NMIEVENT
	        menu_ventana_scanf("NMIEVENT value (0-255)",string_nmi,4);

        	valor_nmi=parse_string_to_number(string_nmi);

	        if (valor_nmi<0 || valor_nmi>255) {
        	        debug_printf (VERBOSE_ERR,"Invalid value %d",valor_nmi);
                	return;
	        }


		generate_nmi();

		//meter BOOTM a 1 (bit 0)
		zxuno_ports[0] |=1;

		zxuno_set_memory_pages();

		//Mapear sram 13
		//zxuno_memory_paged_new(13);
		zxuno_memory_paged_brandnew[3*2]=zxuno_sram_mem_table_new[13];
		zxuno_memory_paged_brandnew[3*2+1]=zxuno_sram_mem_table_new[13]+8192;

		//Valor nmievent
		zxuno_ports[8]=valor_nmi;

                //Y salimos de todos los menus
                salir_todos_menus=1;
        }

}



menu_z80_moto_int load_binary_last_address=0;
menu_z80_moto_int load_binary_last_length=0;
menu_z80_moto_int save_binary_last_address=0;
menu_z80_moto_int save_binary_last_length=1;




void menu_debug_load_binary(MENU_ITEM_PARAMETERS)
{

	char *filtros[2];

	filtros[0]="";
	filtros[1]=0;


	//guardamos directorio actual
	char directorio_actual[PATH_MAX];
	getcwd(directorio_actual,PATH_MAX);

	int ret;

	//Obtenemos ultimo directorio visitado
	if (binary_file_load[0]!=0) {
		char directorio[PATH_MAX];
		util_get_dir(binary_file_load,directorio);
		//printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

		//cambiamos a ese directorio, siempre que no sea nulo
		if (directorio[0]!=0) {
				debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
				zvfs_chdir(directorio);
		}
	}

	ret=menu_filesel("Select File to Load",filtros,binary_file_load);

	//volvemos a directorio inicial
	zvfs_chdir(directorio_actual);

	if (ret==1) {

		cls_menu_overlay();

		menu_debug_change_memory_zone();


		char string_direccion[10];
		sprintf (string_direccion,"%XH",load_binary_last_address);
		menu_ventana_scanf("Address: ",string_direccion,10);
		int valor_leido_direccion=parse_string_to_number(string_direccion);
		load_binary_last_address=valor_leido_direccion;

		cls_menu_overlay();

		char string_longitud[8];
		sprintf (string_longitud,"%d",load_binary_last_length);
		menu_ventana_scanf("Length: 0 - all",string_longitud,8);
		int valor_leido_longitud=parse_string_to_number(string_longitud);
		load_binary_last_length=valor_leido_longitud;

		load_binary_file(binary_file_load,valor_leido_direccion,valor_leido_longitud);

		//Y salimos de todos los menus
		salir_todos_menus=1;


    }



}




void menu_debug_view_basic(MENU_ITEM_PARAMETERS)
{

    char *results_buffer=util_malloc_max_texto_generic_message("Can not allocate memory for showing basic");
	debug_view_basic(results_buffer);

    menu_generic_message_format("View Basic","%s",results_buffer);

    free(results_buffer);
}

void menu_debug_lost_vsync(MENU_ITEM_PARAMETERS)
{
	simulate_lost_vsync.v ^=1;
}



void menu_run_mantransfer(MENU_ITEM_PARAMETERS)
{
	//Cargar mantransfer.bin
	char *mantransfefilename="mantransfev3.bin";
                FILE *ptr_mantransfebin;
                int leidos;

                open_sharedfile(mantransfefilename,&ptr_mantransfebin);
                if (!ptr_mantransfebin)
                {
                        debug_printf(VERBOSE_ERR,"Unable to open mantransfer binary file %s",mantransfefilename);
                        return;
                }

	#define MAX_MANTRANSFE_BIN 1024
	z80_byte buffer[MAX_MANTRANSFE_BIN];

	leidos=fread(buffer,1,MAX_MANTRANSFE_BIN,ptr_mantransfebin);

	//pasarlo a memoria
	int i;

	for (i=0;i<leidos;i++) {
		poke_byte_no_time(16384+i,buffer[i]);
	}

	fclose(ptr_mantransfebin);

	//Establecer modo im1 o im2
	//Al inicio hay
	//regsp defw 0
	//im 1  (0xed,0x56)

	//im2 seria 0xed, 0x5e

	int offset_im_opcode=16384+2+1;
	z80_byte opcode;

	if (im_mode==1 || im_mode==0) opcode=0x56;
	//im2
	else opcode=0x5e;

	poke_byte_no_time(offset_im_opcode,opcode);

	debug_printf (VERBOSE_INFO,"Running mantransfer saving routine");

	//y saltar a la rutina de grabacion de mantransfe
	//Si se cambia la rutina, hay que cambiar este salto tambien
        push_valor(reg_pc,PUSH_VALUE_TYPE_CALL);
        reg_pc=16384+0x32;

        //Y salimos de todos los menus
        salir_todos_menus=1;

}




void menu_debug_save_binary(MENU_ITEM_PARAMETERS)
{

	char *filtros[2];

	filtros[0]="";
	filtros[1]=0;


	//guardamos directorio actual
	char directorio_actual[PATH_MAX];
	getcwd(directorio_actual,PATH_MAX);

	int ret;

	//Obtenemos ultimo directorio visitado
	if (binary_file_save[0]!=0) {
		char directorio[PATH_MAX];
		util_get_dir(binary_file_save,directorio);
		//printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

		//cambiamos a ese directorio, siempre que no sea nulo
		if (directorio[0]!=0) {
				debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
				zvfs_chdir(directorio);
		}
	}

	ret=menu_filesel("Select File to Save",filtros,binary_file_save);

	//volvemos a directorio inicial
	zvfs_chdir(directorio_actual);


    if (ret==1) {

		//Ver si archivo existe y preguntar

      	if (si_existe_archivo(binary_file_save)) {

			if (menu_confirm_yesno_texto("File exists","Overwrite?")==0) return;

		}

		cls_menu_overlay();

		menu_debug_change_memory_zone();

		char string_direccion[10];
		sprintf (string_direccion,"%XH",save_binary_last_address);
		menu_ventana_scanf("Address: ",string_direccion,10);
		int valor_leido_direccion=parse_string_to_number(string_direccion);
		save_binary_last_address=valor_leido_direccion;

		cls_menu_overlay();
		char string_longitud[8];
		sprintf (string_longitud,"%d",save_binary_last_length);
		menu_ventana_scanf("Length: 0 - all",string_longitud,8);
		int valor_leido_longitud=parse_string_to_number(string_longitud);
		save_binary_last_length=valor_leido_longitud;						


		save_binary_file(binary_file_save,valor_leido_direccion,valor_leido_longitud);
		
		
		//Y salimos de todos los menus
        salir_todos_menus=1;

    }


}




void menu_debug_file_utils(MENU_ITEM_PARAMETERS)
{


	int ret=1;

	while (ret!=0) {
			char *filtros[2];

			filtros[0]="";
			filtros[1]=0;


        //guardamos directorio actual
        char directorio_actual[PATH_MAX];
        getcwd(directorio_actual,PATH_MAX);


        //Obtenemos ultimo directorio visitado
        if (file_utils_file_name[0]!=0) {
                char directorio[PATH_MAX];
                util_get_dir(file_utils_file_name,directorio);
                //printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

                //cambiamos a ese directorio, siempre que no sea nulo
                if (directorio[0]!=0) {
                        debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
                        zvfs_chdir(directorio);
                }
        }

        menu_filesel_show_utils.v=1;
        ret=menu_filesel("File utilities",filtros,file_utils_file_name);
        menu_filesel_show_utils.v=0;

        //volvemos a directorio inicial
        zvfs_chdir(directorio_actual);

        if (ret==1) {

						cls_menu_overlay();
						//menu_file_utils_read_file("File view",file_utils_file_name);
				}

    }



}



int menu_debug_view_basic_cond(void)
{
	
	if (MACHINE_IS_ACE) return 0;
    if (MACHINE_IS_COLECO) return 0;
	if (MACHINE_IS_CPC) return 0;
    if (MACHINE_IS_MK14) return 0;
    if (MACHINE_IS_MSX) return 0;
    if (MACHINE_IS_QL) return 0;
	if (MACHINE_IS_SAM) return 0;
    if (MACHINE_IS_SG1000) return 0;
    if (MACHINE_IS_SMS) return 0;
    if (MACHINE_IS_SVI) return 0;
    if (MACHINE_IS_Z88) return 0;
	return 1;
}

void menu_debug_spritefinder(MENU_ITEM_PARAMETERS)
{
	if (spritefinder_enabled.v) spritefinder_disable();
	else spritefinder_enable();
}




void menu_write_message(MENU_ITEM_PARAMETERS)
{
	char buffer_texto[256];

	buffer_texto[0]=0;
    menu_ventana_scanf("Just write...",buffer_texto,256);

	menu_generic_message("Your message",buffer_texto);


}


#ifdef TIMESENSORS_ENABLED

void menu_debug_timesensors(MENU_ITEM_PARAMETERS)
{
	int i;  


    char *timesensors_buffer=util_malloc_max_texto_generic_message("Can not allocate memory for debug timesensors");

	char buf_linea[64];

    int index_buffer=0;

    for (i=0;i<10;i++) {
		long media=TIMESENSOR_ENTRY_MEDIATIME(i);
        sprintf (buf_linea,"ID: %02d average: %ld us (%ld ms)\n",i,media,media/1000);
        sprintf (&timesensors_buffer[index_buffer],"%s",buf_linea); index_buffer +=strlen(buf_linea);

		long max=TIMESENSOR_ENTRY_MAXTIME(i);
        sprintf (buf_linea,"ID: %02d max: %ld us (%ld ms)\n",i,max,max/1000);
        sprintf (&timesensors_buffer[index_buffer],"%s",buf_linea); index_buffer +=strlen(buf_linea);		
	}

	menu_generic_message("Sensors",timesensors_buffer);

    free(timesensors_buffer);


}

void menu_debug_timesensors_enable(MENU_ITEM_PARAMETERS)
{
	timesensors_started ^=1;

}

void menu_debug_timesensors_init(MENU_ITEM_PARAMETERS)
{
	TIMESENSOR_INIT();
}

#endif

void menu_debug_set_pc_zero(MENU_ITEM_PARAMETERS)
{
	if (menu_confirm_yesno("Set PC=0")==1) {
		reg_pc=0;
        //Y salimos de todos los menus
        salir_todos_menus=1;
	}    
    
}


#define SHORTCUTS_HELPER_ANCHO 32
#define SHORTCUTS_HELPER_ALTO 3
#define SHORTCUTS_HELPER_X (menu_center_x()-SHORTCUTS_HELPER_ANCHO/2)

//ponerlo arriba para que inicialmente sea el sitio mejor para verse
#define SHORTCUTS_HELPER_Y 0


//Usado dentro del overlay de menu_shortcuts_helper_overlay, para mostrar dos veces por segundo el texto que average, etc
int menu_shortcuts_helper_valor_contador_segundo_anterior;


zxvision_window *menu_audio_shortcuts_helper_window;



void menu_shortcuts_helper_overlay(void)
{

	if (!zxvision_drawing_in_background) normal_overlay_texto_menu();


	menu_speech_tecla_pulsada=1; //Si no, envia continuamente todo ese texto a speech

    //si ventana minimizada, no ejecutar todo el codigo de overlay
    if (menu_audio_shortcuts_helper_window->is_minimized) return; 

    //printf ("contador_segundo=%d\n",contador_segundo);


    //esto hara ejecutar esto 5 veces por segundo
    if ( ((contador_segundo%200) == 0 && menu_shortcuts_helper_valor_contador_segundo_anterior!=contador_segundo) || menu_multitarea==0) {
        menu_shortcuts_helper_valor_contador_segundo_anterior=contador_segundo;

        zxvision_print_string_defaults_fillspc(menu_audio_shortcuts_helper_window,1,0,zxvision_helper_shorcuts_accumulated);     
	}


	zxvision_draw_window_contents(menu_audio_shortcuts_helper_window);

}



zxvision_window zxvision_window_shortcuts_helper;


void menu_shortcuts_window(MENU_ITEM_PARAMETERS)
{

    menu_espera_no_tecla();
    menu_reset_counters_tecla_repeticion();


    zxvision_window *ventana;
    ventana=&zxvision_window_shortcuts_helper;


	//IMPORTANTE! no crear ventana si ya existe. Esto hay que hacerlo en todas las ventanas que permiten background.
	//si no se hiciera, se crearia la misma ventana, y en la lista de ventanas activas , al redibujarse,
	//la primera ventana repetida apuntaria a la segunda, que es el mismo puntero, y redibujaria la misma, y se quedaria en bucle colgado
	zxvision_delete_window_if_exists(ventana);

	int x,y,ancho,alto,is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;

	if (!util_find_window_geometry("shortcutshelper",&x,&y,&ancho,&alto,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
        x=SHORTCUTS_HELPER_X;
        y=SHORTCUTS_HELPER_Y;
        ancho=SHORTCUTS_HELPER_ANCHO;
        alto=SHORTCUTS_HELPER_ALTO;      
	}


    zxvision_new_window_gn_cim(ventana,x,y,ancho,alto,ancho-1,alto-2,"Shortcuts helper","shortcutshelper",is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize);

	ventana->can_be_backgrounded=1;
	//indicar nombre del grabado de geometria
	//strcpy(ventana->geometry_name,"shortcutshelper");
    //restaurar estado minimizado de ventana
    //ventana->is_minimized=is_minimized;    

	//printf("despues zxvision_new_window_nocheck_staticsize\n");
	zxvision_draw_window(ventana);


    //Cambiamos funcion overlay de texto de menu
    //Se establece a la de funcion de audio waveform
	set_menu_overlay_function(menu_shortcuts_helper_overlay);

	menu_audio_shortcuts_helper_window=ventana; //Decimos que el overlay lo hace sobre la ventana que tenemos aqui

	//Toda ventana que este listada en zxvision_known_window_names_array debe permitir poder salir desde aqui
	//Se sale despues de haber inicializado overlay y de cualquier otra variable que necesite el overlay
	if (zxvision_currently_restoring_windows_on_start) {
		//printf ("Saliendo de ventana ya que la estamos restaurando en startup\n");
		return;
	}

    int tecla=zxvision_wait_until_esc(ventana);


    //Antes de restaurar funcion overlay, guardarla en estructura ventana, por si nos vamos a background
    zxvision_set_window_overlay_from_current(ventana);

    //restauramos modo normal de texto de menu
    set_menu_overlay_function(normal_overlay_texto_menu);

    //En caso de menus tabulados, suele ser necesario esto. Si no, la ventana se quedaria visible
    cls_menu_overlay();

    //Grabar geometria ventana
    util_add_window_geometry_compact(ventana);


    if (tecla==3) {
        zxvision_message_put_window_background();
    }

    else {
        //En caso de menus tabulados, es responsabilidad de este de liberar ventana
        zxvision_destroy_window(ventana);
    }

}





//menu debug
void menu_debug_main(MENU_ITEM_PARAMETERS)
{
    menu_item *array_menu_debug;
    menu_item item_seleccionado;
	int retorno_menu;

    //letras usadas: rhndmictxbsvfpoaug
    do {
        menu_add_item_menu_inicial(&array_menu_debug,"~~Reset",MENU_OPCION_NORMAL,menu_debug_reset,NULL);
		menu_add_item_menu_shortcut(array_menu_debug,'r');

        //Agregar una acción de solo hacer PC=0 en casos, por ejemplo, en que hay divide en modo mapram y no queremos
        //que se reinicialice toda la maquina y perder ese mapeo
        //Dejamos que la acción siempre esté visible
        if (CPU_IS_Z80) {
            menu_add_item_menu_en_es_ca(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_set_pc_zero,NULL,
                "Set PC=0","Establecer PC=0","Establir PC=0");
            menu_add_item_menu_tooltip(array_menu_debug,"It only resets cpu by setting PC register to zero");
            menu_add_item_menu_ayuda(array_menu_debug,"It only resets cpu by setting PC register to zero.\n"
                "Useful for example using DivIDE firmwares in MAPRAM mode and you need to restart it but without "
                "losing the mapping");                    
        }
                

		if (MACHINE_IS_PRISM) {
			//Reset to failsafe
			menu_add_item_menu(array_menu_debug,"Reset to Failsafe mode",MENU_OPCION_NORMAL,menu_debug_prism_failsafe,NULL);

		}

		if (MACHINE_IS_Z88 || MACHINE_IS_ZXUNO || MACHINE_IS_PRISM || MACHINE_IS_TBBLUE || superupgrade_enabled.v || MACHINE_IS_TSCONF || MACHINE_IS_BASECONF) {
            menu_add_item_menu(array_menu_debug,"~~Hard Reset",MENU_OPCION_NORMAL,menu_debug_hard_reset,NULL);
			menu_add_item_menu_shortcut(array_menu_debug,'h');
            menu_add_item_menu_tooltip(array_menu_debug,"Hard resets the machine");
            menu_add_item_menu_ayuda(array_menu_debug,"Hard resets the machine.\n"
				"On Z88, it's the same as opening flap and pressing reset button.\n"
				"On ZX-Uno, it's the same as pressing Ctrl-Alt-Backspace or powering off and on the machine"
				);
		}

		if (!CPU_IS_MOTOROLA) {
    		menu_add_item_menu(array_menu_debug,"Generate ~~NMI",MENU_OPCION_NORMAL,menu_debug_nmi,NULL);
            menu_add_item_menu_spanish(array_menu_debug,"Generar ~~NMI");
			menu_add_item_menu_shortcut(array_menu_debug,'n');

			if (MACHINE_IS_TBBLUE && multiface_enabled.v && (tbblue_registers[6]&8) ) {
                menu_add_item_menu(array_menu_debug,"Generate Multiface NMI",MENU_OPCION_NORMAL,menu_debug_nmi_multiface_tbblue,NULL);
            }
		}

		if (MACHINE_IS_ZXUNO_BOOTM_DISABLED) {
            menu_add_item_menu_en_es_ca(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_special_nmi,NULL,
                "Generate Special NMI","Generar NMI Especial","Generar NMI Especial");
		}

		menu_add_item_menu(array_menu_debug,"~~Debug CPU",MENU_OPCION_NORMAL,menu_debug_registers,NULL);
		menu_add_item_menu_shortcut(array_menu_debug,'d');
		menu_add_item_menu_tooltip(array_menu_debug,"Open debug window");
		menu_add_item_menu_ayuda(array_menu_debug,"This window opens the debugger. You can see there some Z80 registers "
					"easily recognizable. Some other variables and entries need further explanation:\n"
					"TSTATES: T-states total in a frame\n"
					"TSTATL: T-states total in a scanline\n"
					"TSTATP: T-states partial. This is a counter that you can reset with key P"



					);


        if (MACHINE_IS_SPECTRUM || MACHINE_IS_CPC) {
            if (util_textadventure_is_daad_quill_paws() ) {
                menu_add_item_menu(array_menu_debug,"Debug Adventure",MENU_OPCION_NORMAL,menu_debug_registers_view_adventure,NULL);

		        menu_add_item_menu_tooltip(array_menu_debug,"Open debug window on the adventure view (view number 8)");
                menu_add_item_menu_ayuda(array_menu_debug,"Open debug window on the adventure view (view number 8)");
            }
        }
                            

        menu_add_item_menu(array_menu_debug,"",MENU_OPCION_SEPARADOR,NULL,NULL);                    

        menu_add_item_menu_en_es_ca(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_load_source_code,NULL,
            "Load Source Code","Cargar Codigo Fuente","Carregar Codi Font");
        menu_add_item_menu_tooltip(array_menu_debug,"Load source code");                
        menu_add_item_menu_ayuda(array_menu_debug,"Load source code. It is shown on the Debug CPU window. "
            "Source code must have labels in format LXXXX or XXXX where XXXX is an address in hexadecimal. \n"
            "If you compile with sjasmplus, you can generate an assembler output file with addresses on every line "
            "so it can be loaded in ZEsarUX. Run it the following way:\n"
            "sjasmplus inputfile.asm --lst=output_extended.asm\n"
            "That output_extended.asm will have labels/addresses on every line. Then go to Debug settings, and uncheck "
            "'Source code L Prefix'. You need also to adjust 'Source code skip cols' to discard X characters from the beginning "
            "of the line until the label/address is located, typically 6 or 7 characters");   

        if (remote_tamanyo_archivo_raw_source_code) {
            menu_add_item_menu_en_es_ca(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_unload_source_code,NULL,
                "Unload Source Code","Descartar Codigo Fuente","Descartar Codi Font");
        }     

		if (MACHINE_IS_TSCONF || MACHINE_IS_ZXUNO || datagear_dma_emulation.v) {
			menu_add_item_menu_format(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_dma_tsconf_zxuno,NULL,"Debug D~~MA");
			menu_add_item_menu_shortcut(array_menu_debug,'m');
		}					

		if (CPU_IS_Z80) {
			menu_add_item_menu_format(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_ioports,NULL,"Debug ~~I/O Ports");
			menu_add_item_menu_shortcut(array_menu_debug,'i');

			menu_add_item_menu_en_es_ca(array_menu_debug,MENU_OPCION_NORMAL,menu_cpu_transaction_log,NULL,
                "~~CPU Transaction Log","Registro transacciones ~~CPU","Registre transaccions ~~CPU");
			menu_add_item_menu_shortcut(array_menu_debug,'c');
            menu_add_item_menu_tiene_submenu(array_menu_debug);
		}

		if (CPU_IS_MOTOROLA) {
			menu_add_item_menu_format(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_ioports,NULL,"Debug ~~I/O Addresses");
			menu_add_item_menu_shortcut(array_menu_debug,'i');        
        }

		if (MACHINE_IS_TSCONF || MACHINE_IS_TBBLUE || MACHINE_IS_CPC) {
			if (MACHINE_IS_TSCONF) {
                menu_add_item_menu_format(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_tsconf_tbblue_msx,NULL,"~~TSConf");
                menu_add_item_menu_shortcut(array_menu_debug,'t');
                menu_add_item_menu_tiene_submenu(array_menu_debug);
            }
			if (MACHINE_IS_TBBLUE) {
                menu_add_item_menu_format(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_tsconf_tbblue_msx,NULL,"~~TBBlue");
                menu_add_item_menu_shortcut(array_menu_debug,'t');
                menu_add_item_menu_tiene_submenu(array_menu_debug);
            }
            if (MACHINE_IS_CPC) {
                menu_add_item_menu_format(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_tsconf_tbblue_msx,NULL,"CPC");
                menu_add_item_menu_tiene_submenu(array_menu_debug);
            }
			
		}

		if (MACHINE_HAS_VDP_9918A) {
			char buffer_item[32];
			
			strcpy(buffer_item,"~~MSX");
			// por defecto


			if (MACHINE_IS_COLECO) {
				strcpy(buffer_item,"Colecovision");
			}

			if (MACHINE_IS_SG1000) {
				strcpy(buffer_item,"SG-1000");
			}		

			if (MACHINE_IS_SMS) {
				strcpy(buffer_item,"Master System");
			}	            

			if (MACHINE_IS_SVI) {
				strcpy(buffer_item,"Spectravideo");
			}	


			menu_add_item_menu_format(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_tsconf_tbblue_msx,NULL,buffer_item);

			if (MACHINE_IS_MSX) {
				//Letra M tambien se usa en DMA, pero como no hay DMA en MSX, pues no estaran nunca las dos opciones a la vez
				menu_add_item_menu_shortcut(array_menu_debug,'m');
			}

            menu_add_item_menu_tiene_submenu(array_menu_debug);
		}		

        menu_add_item_menu_en_es_ca(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_unnamed_console,NULL,
            "Debug console","Consola Depuracion","Consola Depuracio");

        menu_add_item_menu(array_menu_debug,"",MENU_OPCION_SEPARADOR,NULL,NULL);

        


		menu_add_item_menu(array_menu_debug,"He~~xadecimal Editor",MENU_OPCION_NORMAL,menu_debug_hexdump,NULL);
        menu_add_item_menu_spanish(array_menu_debug,"Editor He~~xadecimal");
		menu_add_item_menu_shortcut(array_menu_debug,'x');

		menu_add_item_menu_en_es_ca(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_view_basic,menu_debug_view_basic_cond,
            "View ~~Basic","Ver ~~Basic","Veure ~~Basic");
		menu_add_item_menu_shortcut(array_menu_debug,'b');

        if (MACHINE_IS_SPECTRUM || MACHINE_IS_ZX8081) {
		    menu_add_item_menu_en_es_ca(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_view_basic_variables,NULL,
                "View Basic variab~~les","Ver variab~~les Basic","Veure variab~~les Basic");
            menu_add_item_menu_shortcut(array_menu_debug,'l');
        }

#ifdef EMULATE_CPU_STATS
		if (CPU_IS_Z80) {
			menu_add_item_menu_en_es_ca(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_cpu_stats,NULL,
                "View CPU Statistics","Ver estadísticas CPU","Veure estadístiques CPU");
            menu_add_item_menu_tiene_submenu(array_menu_debug);
		}

#endif        

        menu_add_item_menu_en_es_ca(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_view_sensors,NULL,
            "View Sensors","Ver Sensores","Veure Sensors");

		if (si_complete_video_driver() ) {
			menu_add_item_menu_en_es_ca(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_view_sprites,NULL,
                "View ~~Sprites","Ver ~~Sprites","Veure ~~Sprites");
			menu_add_item_menu_shortcut(array_menu_debug,'s');
		}



#ifdef EMULATE_VISUALMEM
			//if (!CPU_IS_MOTOROLA) {
			//menu_add_item_menu(array_menu_debug,"Old visual memory",MENU_OPCION_NORMAL,menu_debug_visualmem,NULL);
	                //menu_add_item_menu_tooltip(array_menu_debug,"Show which memory zones are changed or which memory address with opcodes have been executed");
	                //menu_add_item_menu_ayuda(array_menu_debug,"Show which memory zones are changed or which memory address with opcodes have been executed");

			menu_add_item_menu(array_menu_debug,"~~Visual memory",MENU_OPCION_NORMAL,menu_debug_new_visualmem,NULL);
            menu_add_item_menu_spanish(array_menu_debug,"Memoria ~~Visual");
			menu_add_item_menu_shortcut(array_menu_debug,'v');
	                menu_add_item_menu_tooltip(array_menu_debug,"Show which memory zones are changed or which memory address with opcodes have been executed");
	                menu_add_item_menu_ayuda(array_menu_debug,"Show which memory zones are changed or which memory address with opcodes have been executed");			
			//}
#endif

    



    menu_add_item_menu(array_menu_debug,"",MENU_OPCION_SEPARADOR,NULL,NULL);

    menu_add_item_menu_format(array_menu_debug,MENU_OPCION_NORMAL,menu_find,NULL,"~~Find");
		menu_add_item_menu_shortcut(array_menu_debug,'f');
    menu_add_item_menu_tooltip(array_menu_debug,"Find bytes on memory");
    menu_add_item_menu_ayuda(array_menu_debug,"Find bytes on the 64 KB of mapped memory");
    menu_add_item_menu_tiene_submenu(array_menu_debug);


		menu_add_item_menu(array_menu_debug,"~~Poke",MENU_OPCION_NORMAL,menu_poke,NULL);
		menu_add_item_menu_shortcut(array_menu_debug,'p');
		menu_add_item_menu_tooltip(array_menu_debug,"Poke address manually or from .POK file");
		menu_add_item_menu_ayuda(array_menu_debug,"Poke address for infinite lives, etc...");
        menu_add_item_menu_tiene_submenu(array_menu_debug);



		if (menu_cond_zx8081() ) {

			menu_add_item_menu_format(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_lost_vsync,NULL,
				"Simulate lost VSYNC: %s",(simulate_lost_vsync.v==1 ? "On" : "Off"));
		}




		menu_add_item_menu_en_es_ca(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_load_binary,NULL,
            "L~~oad binary block","Cargar bl~~oque binario","Carregar bl~~oc binari");
		menu_add_item_menu_shortcut(array_menu_debug,'o');

		menu_add_item_menu_en_es_ca(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_save_binary,NULL,
            "S~~ave binary block","S~~alvar bloque binario","S~~alvar bloc binari");
		menu_add_item_menu_shortcut(array_menu_debug,'a');


		if (menu_desactivado_file_utilities.v==0) {

			menu_add_item_menu_en_es_ca(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_file_utils,NULL,
                "File ~~utilities","~~Utilidades de archivos","~~Utilidats d'arxius");
			menu_add_item_menu_shortcut(array_menu_debug,'u');
			menu_add_item_menu_tooltip(array_menu_debug,"Some file utilities. NOTE: Shortcuts must be chosen pressing Shift+Key");
			menu_add_item_menu_ayuda(array_menu_debug,"Some file utilities.\nNOTE: Shortcuts in file utilities must be chosen by pressing Shift+Key, "
								"I mean, shortcuts are in capital letters to differentiate from quick selecting a file, so for example, "
								"to view a file you must press Shift+v");

		}
		


		if (!CPU_IS_MOTOROLA) {
		menu_add_item_menu_format(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_input_file_keyboard,NULL,"Input File Spoolin~~g");
		menu_add_item_menu_shortcut(array_menu_debug,'g');
                menu_add_item_menu_tooltip(array_menu_debug,"Sends every character from a text file as keyboard presses");
                menu_add_item_menu_ayuda(array_menu_debug,"Every character from a text file is sent as keyboard presses. Only Ascii characters, not UFT, Unicode or others. "
                                                                   "Symbols that require extended mode on Spectrum are not sent: [ ] (c) ~ \\ { }. These can be used "
                                                                   "as a delay.\n"
								"Note: symbol | means Shift+1 (Edit)");
                                menu_add_item_menu_tiene_submenu(array_menu_debug);
		}


		/*
		if (menu_allow_background_windows) {
			menu_add_item_menu_format(array_menu_debug,MENU_OPCION_NORMAL,menu_draw_background_windows,NULL,"ZXVision background windows");
		}
		*/


		menu_add_item_menu_en_es_ca(array_menu_debug,MENU_OPCION_NORMAL,menu_write_message,NULL,
            "Write message","Escribir mensaje","Escriure missatge");
		menu_add_item_menu_tooltip(array_menu_debug,"Just lets you write text in a window, useful if you want to record the display and you want to say something");
		menu_add_item_menu_ayuda(array_menu_debug,"Just lets you write text in a window, useful if you want to record the display and you want to say something");

		menu_add_item_menu_en_es_ca(array_menu_debug,MENU_OPCION_NORMAL,menu_shortcuts_window,NULL,
            "Shortcuts helper","Ayudante de atajos","Ajudant de dreceres");
		menu_add_item_menu_tooltip(array_menu_debug,"Window to see all shortcuts (hotkeys) pressed");
        menu_add_item_menu_ayuda(array_menu_debug,"Window to see all shortcuts (hotkeys) pressed");


#ifdef TIMESENSORS_ENABLED

		menu_add_item_menu_format(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_timesensors_enable,NULL,"[%c] Timesensors",
		(timesensors_started ? 'X' : ' ' ));

		if (timesensors_started) {
			menu_add_item_menu_format(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_timesensors,NULL,"    List Timesensors");

			menu_add_item_menu_format(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_timesensors_init,NULL,"    Init Timesensors");
		}

#endif



	if (MACHINE_IS_SPECTRUM_16_48) {
		menu_add_item_menu_en_es_ca(array_menu_debug,MENU_OPCION_NORMAL,menu_run_mantransfer,NULL,
            "Run mantransfer","Ejecutar mantransfer","Executar mantransfer");
		menu_add_item_menu_tooltip(array_menu_debug,"Run mantransfer, which dumps ram memory contents (snapshot) to Spectrum Tape\n"
					"Only Spectrum 48k/16k models supported");
		menu_add_item_menu_ayuda(array_menu_debug,"The difference between this option and the Save snapshot option is that "
					"this option runs a Spectrum machine program (mantransfev3.bin) which dumps the ram contents to tape, "
					"so you can use a .tap file to save it or even a real tape connected to line out of your soundcard.\n"
					"It uses a small amount of RAM on memory display and some bytes on the stack, so it is not a perfect "
					"routine and sometimes may fail.\n"
					"The source code can be found on mantransfev3.tap\n"
					"Note: Although mantransfe is a Spectrum program and it could run on a real spectrum or another emulator, "
					"the saving routine needs that ZEsarUX emulator tells which im mode the cpu is (IM1 or IM2), "
					"so, a saved program can be run on a real spectrum or another emulator, "
					"but the saving routine sees im1 by default, so, saving from a real spectrum or another emulator "
					"instead ZEsarUX will only work if the cpu is in IM1 mode (and not IM2)");
	}

	//testeo
	//menu_add_item_menu_format(array_menu_debug,MENU_OPCION_NORMAL,menu_testeo_scanf_numero,NULL,"Test scanf number");

		/* De momento desactivado
		if (MACHINE_IS_SPECTRUM) {
			menu_add_item_menu_format(array_menu_debug,MENU_OPCION_NORMAL,menu_debug_spritefinder,NULL,"Spritefinder: %s",
					(spritefinder_enabled.v ? "Yes" : "No") );
		}
		*/

	


        menu_add_item_menu(array_menu_debug,"",MENU_OPCION_SEPARADOR,NULL,NULL);
                //menu_add_item_menu(array_menu_debug,"ESC Back",MENU_OPCION_NORMAL|MENU_OPCION_ESC,NULL,NULL);
		menu_add_ESC_item(array_menu_debug);

        retorno_menu=menu_dibuja_menu(&debug_opcion_seleccionada,&item_seleccionado,array_menu_debug,"Debug" );

                

		if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
				
                        }
                }

	} while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);

}


void menu_snapshot_load(MENU_ITEM_PARAMETERS)
{

        char *filtros[16];

        filtros[0]="zx";
        filtros[1]="sp";
        filtros[2]="z80";
        filtros[3]="sna";
        filtros[4]="o";
        filtros[5]="p";

        filtros[6]="80";
        filtros[7]="81";
        filtros[8]="z81";
        filtros[9]="ace";
		filtros[10]="rzx";
		filtros[11]="zsf";
		filtros[12]="spg";
		filtros[13]="nex";
        filtros[14]="snx";
        filtros[15]=0;



        //guardamos directorio actual
        char directorio_actual[PATH_MAX];
        getcwd(directorio_actual,PATH_MAX);

        //Obtenemos directorio de snap
        //si no hay directorio, vamos a rutas predefinidas
        if (snapfile==NULL) menu_chdir_sharedfiles();

	else {
	        char directorio[PATH_MAX];
	        util_get_dir(snapfile,directorio);
	        //printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

	        //cambiamos a ese directorio, siempre que no sea nulo
	        if (directorio[0]!=0) {
	                debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
	                zvfs_chdir(directorio);
        	}
	}


	int ret;

	ret=menu_filesel("Select Snapshot",filtros,snapshot_load_file);
        //volvemos a directorio inicial
        zvfs_chdir(directorio_actual);


        if (ret==1) {
		snapfile=snapshot_load_file;

		//sin overlay de texto, que queremos ver las franjas de carga con el color normal (no apagado)
		reset_menu_overlay_function();


			snapshot_load();

		//restauramos modo normal de texto de menu
		set_menu_overlay_function(normal_overlay_texto_menu);

		//Y salimos de todos los menus
		salir_todos_menus=1;
        }


}

void menu_snapshot_save(MENU_ITEM_PARAMETERS)
{

    menu_first_aid("snapshot_save_zsf");

    char *filtros[6];

  	if (MACHINE_IS_ZX8081) {
		filtros[0]="zx";

		if (MACHINE_IS_ZX80) filtros[1]="o";
		else filtros[1]="p";

		filtros[2]="zsf";
		filtros[3]=0;
}

	else if (MACHINE_IS_Z88) {
		filtros[0]="zx";
		filtros[1]="zsf";
		filtros[2]=0;
	}

	else if (MACHINE_IS_SPECTRUM_16_48) {
		filtros[0]="zsf";
		filtros[1]="zx";
		filtros[2]="z80";
		filtros[3]="sp";
		filtros[4]="sna";
		filtros[5]=0;
	}

	else if (MACHINE_IS_ACE) {
		filtros[0]="zx";
		filtros[1]="ace";
		filtros[2]="zsf";
		filtros[3]=0;
	}

	else if (MACHINE_IS_CPC) {
		filtros[0]="zx";
		filtros[1]="zsf";
		filtros[2]=0;
    }


	else {
		filtros[0]="zsf";
		filtros[1]="zx";
		filtros[2]="z80";
		filtros[3]="sna";
		filtros[4]=0;
	}


        //guardamos directorio actual
        char directorio_actual[PATH_MAX];
        getcwd(directorio_actual,PATH_MAX);


 		//Obtenemos directorio de snap save
        //si no hay directorio, vamos a rutas predefinidas
        if (snapshot_save_file[0]==0) menu_chdir_sharedfiles();

		else {
			char directorio[PATH_MAX];
			util_get_dir(snapshot_save_file,directorio);
			//printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

			//cambiamos a ese directorio, siempre que no sea nulo
			if (directorio[0]!=0) {
					debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
					zvfs_chdir(directorio);
			}
		}



		int ret;

		ret=menu_filesel("Snapshot file",filtros,snapshot_save_file);
        //volvemos a directorio inicial
        zvfs_chdir(directorio_actual);

        if (ret==1) {

			//Ver si archivo existe y preguntar
			struct stat buf_stat;

			if (stat(snapshot_save_file, &buf_stat)==0) {

			if (menu_confirm_yesno_texto("File exists","Overwrite?")==0) return;

		}


		snapshot_save(snapshot_save_file);

		//Si ha ido bien la grabacion
		if (!if_pending_error_message) menu_generic_message_splash("Save Snapshot","OK. Snapshot saved");

			//Y salimos de todos los menus
			salir_todos_menus=1;

        }




}




void menu_snapshot_stop_rzx_play(MENU_ITEM_PARAMETERS)
{
	eject_rzx_file();
}

void menu_snapshot_quicksave(MENU_ITEM_PARAMETERS)
{
	char final_name[PATH_MAX];
	snapshot_quick_save(final_name);


	menu_generic_message_format("Quicksave","OK. Snapshot name: %s",final_name);

}


void menu_snapshot_quickload(MENU_ITEM_PARAMETERS)
{

	char *filtros[2];

	filtros[0]="autosnap";
	filtros[1]=0;



	//guardamos directorio actual
	char directorio_actual[PATH_MAX];
	getcwd(directorio_actual,PATH_MAX);

	//Vamos a directorio de autosnap
	zvfs_chdir(snapshot_autosave_interval_quicksave_directory);


	int ret;

	ret=menu_filesel("Select Snapshot",filtros,snapshot_load_file);
	//volvemos a directorio inicial
	zvfs_chdir(directorio_actual);


	if (ret==1) {
		snapfile=snapshot_load_file;

		//sin overlay de texto, que queremos ver las franjas de carga con el color normal (no apagado)
		//reset_menu_overlay_function();


		snapshot_load();

		//restauramos modo normal de texto de menu
		//set_menu_overlay_function(normal_overlay_texto_menu);

		//Y salimos de todos los menus
		salir_todos_menus=1;
	}


}


void menu_snapshot_save_game_config(MENU_ITEM_PARAMETERS)
{

        char *filtros[29];

        filtros[0]="zx";
        filtros[1]="sp";
        filtros[2]="z80";
        filtros[3]="sna";

        filtros[4]="o";
        filtros[5]="p";
        filtros[6]="80";
        filtros[7]="81";
        filtros[8]="z81";

        filtros[9]="tzx";
        filtros[10]="tap";

        filtros[11]="rwa";
        filtros[12]="smp";
        filtros[13]="wav";

        filtros[14]="epr";
        filtros[15]="63";
        filtros[16]="eprom";
        filtros[17]="flash";

        filtros[18]="ace";

        filtros[19]="dck";

        filtros[20]="cdt";

        filtros[21]="ay";

        filtros[22]="scr";

        filtros[23]="rzx";

        filtros[24]="zsf";

        filtros[25]="spg";

        filtros[26]="trd";

        filtros[27]="config";

        filtros[28]=0;

	char source_file[PATH_MAX];
	char game_config_file[PATH_MAX];


	//por defecto
	source_file[0]=0;

        //guardamos directorio actual
        char directorio_actual[PATH_MAX];
        getcwd(directorio_actual,PATH_MAX);

	int ret;

        //Obtenemos directorio de quickload, para generar el .config en la ultima ruta que se haya hecho smartload
        //si no hay directorio, vamos a rutas predefinidas
        if (quickfile!=NULL)  {
			debug_printf (VERBOSE_INFO,"Last smartload file: %s",quickfile);

			char nombre[PATH_MAX];
			util_get_file_no_directory(quickfile,nombre);


			int usar_nombre_autodetectado;
		
     

			//Si nombre vacio, no usar nombre autodetectado
			if (nombre[0]==0) {
				usar_nombre_autodetectado=0;
			}

			else {
				//Nombre previo. El usuario quiere usarlo?
				char nombre_shown[25];
				menu_tape_settings_trunc_name(nombre,nombre_shown,25);
				usar_nombre_autodetectado=menu_confirm_yesno_texto("Generate config for",nombre_shown);

			}

			if (usar_nombre_autodetectado) {
				strcpy(source_file,quickfile);
				ret=1;
			}


			else {
				//No seleccionamos ultimo quickfile como source. Cambiar a directorio quickfile
	              char directorio[PATH_MAX];
        	        util_get_dir(quickfile,directorio);
                	//printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

	                //cambiamos a ese directorio, siempre que no sea nulo
        	        if (directorio[0]!=0) {
                	        debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
                        	zvfs_chdir(directorio);
	        }


		}

    }

	//Si no se selecciona source_file como ultimo archivo cargado
	if (source_file[0]==0) {

			ret=menu_filesel("Source or dest file",filtros,source_file);
			//volvemos a directorio inicial
			zvfs_chdir(directorio_actual);

	}

	debug_printf (VERBOSE_INFO,"Source file: %s",source_file);

    if (ret) {

		//Archivo final agregar .config, si es que no es ya el .config el que hemos seleccionado
		if (!util_compare_file_extension(source_file,"config")) strcpy(game_config_file,source_file);
		else sprintf (game_config_file,"%s.config",source_file);


		debug_printf (VERBOSE_INFO,"Destination file will be %s",game_config_file);

		 //Ver si archivo existe y preguntar
                if (si_existe_archivo(game_config_file) ) {

                        if (menu_confirm_yesno_texto("File exists","Overwrite?")==0) return;

                }



		util_save_game_config(game_config_file);
		menu_generic_message_splash("Save autoconfig","OK. File saved");


    }
                
}




void menu_snapshot(MENU_ITEM_PARAMETERS)
{

    menu_item *array_menu_snapshot;
    menu_item item_seleccionado;
    int retorno_menu;

    do {


        menu_add_item_menu_inicial(&array_menu_snapshot,"~~Load snapshot",MENU_OPCION_NORMAL,menu_snapshot_load,NULL);
        menu_add_item_menu_spanish_catalan(array_menu_snapshot,"~~Load instantanea","~~Load instantania");

        menu_add_item_menu_shortcut(array_menu_snapshot,'l');
        menu_add_item_menu_tooltip(array_menu_snapshot,"Load snapshot");
        menu_add_item_menu_ayuda(array_menu_snapshot,"Supported snapshot formats on load:\n"
                "Z80, ZX, SP, SNA, O, 80, P, 81, Z81");

        menu_add_item_menu_en_es_ca(array_menu_snapshot,MENU_OPCION_NORMAL,menu_snapshot_save,NULL,
            "~~Save snapshot","~~Salvar instantanea","~~Salvar instantania");
        menu_add_item_menu_shortcut(array_menu_snapshot,'s');
        menu_add_item_menu_tooltip(array_menu_snapshot,"Save snapshot of the current machine state");
        menu_add_item_menu_ayuda(array_menu_snapshot,"Supported snapshot formats on save:\n"
                "Z80, ZX, SP, P, O\n"
                "You must write the file name with the extension");

        menu_add_item_menu(array_menu_snapshot,"",MENU_OPCION_SEPARADOR,NULL,NULL);

        if (rzx_reproduciendo) {
            menu_add_item_menu_en_es_ca(array_menu_snapshot,MENU_OPCION_NORMAL,menu_snapshot_stop_rzx_play,NULL,
                "Stop RZX Play","Detener RZX Play","Aturar RZX Play");
            menu_add_item_menu(array_menu_snapshot,"",MENU_OPCION_SEPARADOR,NULL,NULL);
        }


        menu_add_item_menu_en_es_ca(array_menu_snapshot,MENU_OPCION_NORMAL,menu_snapshot_quickload,NULL,
            "Quickl~~oad","L~~oad rapido","L~~oad rapid");
        menu_add_item_menu_shortcut(array_menu_snapshot,'o');
        menu_add_item_menu_tooltip(array_menu_snapshot,"Load a snapshot quickly");
        menu_add_item_menu_ayuda(array_menu_snapshot,"Browses on the quicksave directory");

        menu_add_item_menu_en_es_ca(array_menu_snapshot,MENU_OPCION_NORMAL,menu_snapshot_quicksave,NULL,
            "Quicks~~ave","S~~alvado rapido","S~~alvat rapid");
        menu_add_item_menu_shortcut(array_menu_snapshot,'a');
        menu_add_item_menu_tooltip(array_menu_snapshot,"Save a snapshot quickly");
        menu_add_item_menu_ayuda(array_menu_snapshot,"Save a snapshot quickly. Name prefix and directory to save are configured on settings->Snapshot");

        menu_add_item_menu(array_menu_snapshot,"",MENU_OPCION_SEPARADOR,NULL,NULL);

        menu_add_item_menu_en_es_ca(array_menu_snapshot,MENU_OPCION_NORMAL,menu_snapshot_rewind,NULL,
            "Snapshots to ~~RAM","Instantaneas a ~~RAM","Instantanies a ~~RAM");
        menu_add_item_menu_shortcut(array_menu_snapshot,'r');
        menu_add_item_menu_tooltip(array_menu_snapshot,"Options to keep last snapshots in RAM");
        menu_add_item_menu_ayuda(array_menu_snapshot,"Options to keep last snapshots in RAM");
        menu_add_item_menu_tiene_submenu(array_menu_snapshot);


        menu_add_item_menu(array_menu_snapshot,"",MENU_OPCION_SEPARADOR,NULL,NULL);


        menu_add_item_menu_en_es_ca(array_menu_snapshot,MENU_OPCION_NORMAL,menu_snapshot_save_game_config,NULL,
            "Save a~~utoconfig file","Salvar archivo a~~utoconfig","Salvar arxiu a~~utoconfig");
        menu_add_item_menu_shortcut(array_menu_snapshot,'u');
        menu_add_item_menu_tooltip(array_menu_snapshot,"Generate .config file with common settings");
        menu_add_item_menu_ayuda(array_menu_snapshot,"Generate .config file with common settings. Used to define custom settings for games, "
            "by default it asks to generate a .config file for the last smartloaded game");




        menu_add_item_menu(array_menu_snapshot,"",MENU_OPCION_SEPARADOR,NULL,NULL);
        menu_add_ESC_item(array_menu_snapshot);

        retorno_menu=menu_dibuja_menu(&snapshot_opcion_seleccionada,&item_seleccionado,array_menu_snapshot,"Snapshot" );

            

        if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
            //llamamos por valor de funcion
            if (item_seleccionado.menu_funcion!=NULL) {
                //printf ("actuamos por funcion\n");
                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
    
            }
        }

    } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




}




//Funcion para seleccionar un directorio con filesel
//Solo cambia string_root_dir si se sale de filesel con ESC
//Devuelve mismo valor que retorna menu_filesel
int menu_storage_string_root_dir(char *string_root_dir)
{

        char *filtros[2];

        filtros[0]="nofiles";
        filtros[1]=0;


        //guardamos directorio actual
        char directorio_actual[PATH_MAX];
        getcwd(directorio_actual,PATH_MAX);

        int ret;


	char nada[PATH_MAX];

        //Obtenemos ultimo directorio visitado
	zvfs_chdir(string_root_dir);


        ret=menu_filesel("Enter dir & press ESC",filtros,nada);


	//Si sale con ESC
	if (ret==0) {
		//Directorio root
		sprintf (string_root_dir,"%s",menu_filesel_last_directory_seen);
		debug_printf (VERBOSE_DEBUG,"Selected directory: %s",string_root_dir);

	}

    //volvemos a directorio inicial
    zvfs_chdir(directorio_actual);

	return ret;


}





void menu_storage_esxdos_traps_emulation(MENU_ITEM_PARAMETERS)
{



	if (esxdos_handler_enabled.v) esxdos_handler_disable();
	else {
		//Si no hay paging, avisar
		if (diviface_enabled.v==0) {
			if (menu_confirm_yesno_texto("No divide/mmc paging","Sure enable?")==0) return;
		}
		esxdos_handler_enable();
	}
}

void menu_esxdos_traps_root_dir(MENU_ITEM_PARAMETERS)
{


	int ret;
	ret=menu_storage_string_root_dir(esxdos_handler_root_dir);

	//Si sale con ESC
	if (ret==0) {
        //directorio esxdos vacio
	    esxdos_handler_cwd[0]=0;
	}		

}

void menu_esxdos_traps_readonly(MENU_ITEM_PARAMETERS)
{
    esxdos_handler_readonly.v ^=1;
}


void menu_esxdos_traps(MENU_ITEM_PARAMETERS)
{
    menu_item *array_menu_esxdos_traps;
    menu_item item_seleccionado;
    int retorno_menu;
    do {

        char string_esxdos_traps_root_dir_shown[18];


        menu_add_item_menu_inicial_format(&array_menu_esxdos_traps,MENU_OPCION_NORMAL,menu_storage_esxdos_traps_emulation,NULL,"[%c] ~~Enabled", (esxdos_handler_enabled.v ? 'X' : ' ' ));
        menu_add_item_menu_shortcut(array_menu_esxdos_traps,'e');
        menu_add_item_menu_tooltip(array_menu_esxdos_traps,"Enable ESXDOS handler");
        menu_add_item_menu_ayuda(array_menu_esxdos_traps,"Enable ESXDOS handler");

        if (esxdos_handler_enabled.v) {
            menu_tape_settings_trunc_name(esxdos_handler_root_dir,string_esxdos_traps_root_dir_shown,18);
            menu_add_item_menu_format(array_menu_esxdos_traps,MENU_OPCION_NORMAL,menu_esxdos_traps_root_dir,NULL,"~~Root dir: %s",string_esxdos_traps_root_dir_shown);
            menu_add_item_menu_shortcut(array_menu_esxdos_traps,'r');

            menu_add_item_menu_tooltip(array_menu_esxdos_traps,"Sets the root directory for ESXDOS filesystem");
            menu_add_item_menu_ayuda(array_menu_esxdos_traps,"Sets the root directory for ESXDOS filesystem. "
                "Only file and folder names valid for ESXDOS will be shown:\n"
                "-Maximum 8 characters for name and 3 for extension\n"
                "-Files and folders will be shown always in uppercase. Folders which are not uppercase, are shown but can not be accessed\n"
                );

            menu_add_item_menu_format(array_menu_esxdos_traps,MENU_OPCION_NORMAL,menu_esxdos_traps_readonly,NULL,"[%c] Read only",
                (esxdos_handler_readonly.v ? 'X' : ' ' ) );

        }






        menu_add_item_menu(array_menu_esxdos_traps,"",MENU_OPCION_SEPARADOR,NULL,NULL);

        menu_add_ESC_item(array_menu_esxdos_traps);

        retorno_menu=menu_dibuja_menu(&esxdos_traps_opcion_seleccionada,&item_seleccionado,array_menu_esxdos_traps,"ESXDOS handler" );


        if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
            //llamamos por valor de funcion
            if (item_seleccionado.menu_funcion!=NULL) {
                    //printf ("actuamos por funcion\n");
                    item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                    
            }
        }

    } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




}


void menu_storage_dskplusthree_file(MENU_ITEM_PARAMETERS)
{

	dskplusthree_disable();

        char *filtros[2];

        filtros[0]="dsk";
        filtros[1]=0;

        //guardamos directorio actual
        char directorio_actual[PATH_MAX];
        getcwd(directorio_actual,PATH_MAX);

              //Obtenemos directorio de dskplusthree
        //si no hay directorio, vamos a rutas predefinidas
        if (dskplusthree_file_name[0]==0) menu_chdir_sharedfiles();

        else {
                char directorio[PATH_MAX];
                util_get_dir(dskplusthree_file_name,directorio);
                //printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

                //cambiamos a ese directorio, siempre que no sea nulo
                if (directorio[0]!=0) {
                        debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
                        zvfs_chdir(directorio);
                }
        }

	char dskfile[PATH_MAX];
	dskfile[0]=0;

        int ret=menu_filesel("Select DSK File",filtros,dskfile);
        //volvemos a directorio inicial
        zvfs_chdir(directorio_actual);

        if (ret==1) {

		if (!si_existe_archivo(dskfile)) {

			menu_warn_message("File does not exist");
			return;


			//Crear archivo vacio
			/*
		        FILE *ptr_dskplusthreefile;
			ptr_dskplusthreefile=fopen(dskplusthree_file_name,"wb");

		        long int totalsize=640*1024;
			
			z80_byte valor_grabar=0;

		        if (ptr_dskplusthreefile!=NULL) {
				while (totalsize) {
					fwrite(&valor_grabar,1,1,ptr_dskplusthreefile);
					totalsize--;
				}
		                fclose(ptr_dskplusthreefile);
		        }
				*/

		}
		dsk_insert_disk(dskfile);

		dskplusthree_enable();
		pd765_enable();
		plus3dos_traps.v=1;


        }
        //Sale con ESC
        else {
                //Quitar nombre
                dskplusthree_file_name[0]=0;


        }
}

void menu_storage_plusthreedisk_traps(MENU_ITEM_PARAMETERS)
{
	plus3dos_traps.v ^=1;
}


void menu_plusthreedisk_pd765(MENU_ITEM_PARAMETERS)
{
        if (pd765_enabled.v) pd765_disable();
	else pd765_enable();
}

int menu_storage_dskplusthree_emulation_cond(void)
{
        if (dskplusthree_file_name[0]==0) return 0;
        else return 1;
}


void menu_storage_dskplusthree_emulation(MENU_ITEM_PARAMETERS)
{
	if (dskplusthree_emulation.v==0) {
		dskplusthree_enable();
		pd765_enable();
		plus3dos_traps.v=1;
	}

	else dskplusthree_disable();
}


void menu_storage_dskplusthree_browser(MENU_ITEM_PARAMETERS)
{
	menu_file_dsk_browser_show(dskplusthree_file_name);
}

void menu_storage_dsk_write_protect(MENU_ITEM_PARAMETERS)
{	
	dskplusthree_write_protection.v ^=1;
}	


void menu_storage_dskplusthree_persistent_writes(MENU_ITEM_PARAMETERS)
{
	dskplusthree_persistent_writes.v ^=1;
}

void menu_plusthreedisk(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_plusthreedisk;
        menu_item item_seleccionado;
        int retorno_menu;
        do {




        	char string_dskplusthree_file_shown[17];
						

			menu_tape_settings_trunc_name(dskplusthree_file_name,string_dskplusthree_file_shown,17);
                        menu_add_item_menu_inicial_format(&array_menu_plusthreedisk,MENU_OPCION_NORMAL,menu_storage_dskplusthree_file,NULL,"~~DSK File: %s",string_dskplusthree_file_shown);
                        menu_add_item_menu_shortcut(array_menu_plusthreedisk,'d');
                        menu_add_item_menu_tooltip(array_menu_plusthreedisk,"DSK Emulation file");
                        menu_add_item_menu_ayuda(array_menu_plusthreedisk,"DSK Emulation file");


                        menu_add_item_menu_format(array_menu_plusthreedisk,MENU_OPCION_NORMAL,menu_storage_dskplusthree_emulation,
                        	menu_storage_dskplusthree_emulation_cond,"DSK ~~Emulation: %s", (dskplusthree_emulation.v ? "Yes" : "No"));
                        menu_add_item_menu_shortcut(array_menu_plusthreedisk,'e');
                        menu_add_item_menu_tooltip(array_menu_plusthreedisk,"DSK Emulation");
                        menu_add_item_menu_ayuda(array_menu_plusthreedisk,"DSK Emulation");


			menu_add_item_menu_format(array_menu_plusthreedisk,MENU_OPCION_NORMAL,menu_storage_dsk_write_protect,NULL,"~~Write protect: %s", (dskplusthree_write_protection.v ? "Yes" : "No"));
                        menu_add_item_menu_shortcut(array_menu_plusthreedisk,'w');
                        menu_add_item_menu_tooltip(array_menu_plusthreedisk,"If DSK disk is write protected");
                        menu_add_item_menu_ayuda(array_menu_plusthreedisk,"If DSK disk is write protected");


			menu_add_item_menu_format(array_menu_plusthreedisk,MENU_OPCION_NORMAL,menu_storage_dskplusthree_persistent_writes,NULL,"Persistent Writes: %s",(dskplusthree_persistent_writes.v ? "Yes" : "No") );
                        menu_add_item_menu_tooltip(array_menu_plusthreedisk,"Tells if DSK writes are saved to disk");
                        menu_add_item_menu_ayuda(array_menu_plusthreedisk,"Tells if DSK writes are saved to disk. "
                        "Note: all writing operations to TRD are always saved to internal memory (unless you disable write permission), but this setting "
                        "tells if these changes are written to disk or not."
                        );


                        menu_add_item_menu_format(array_menu_plusthreedisk,MENU_OPCION_NORMAL,menu_storage_dskplusthree_browser,menu_storage_dskplusthree_emulation_cond,"DSK ~~Browser");
                        menu_add_item_menu_shortcut(array_menu_plusthreedisk,'b');
                        menu_add_item_menu_tooltip(array_menu_plusthreedisk,"DSK Browser");
                        menu_add_item_menu_ayuda(array_menu_plusthreedisk,"DSK Browser");

                               
			menu_add_item_menu(array_menu_plusthreedisk,"",MENU_OPCION_SEPARADOR,NULL,NULL);


                        menu_add_item_menu_format(array_menu_plusthreedisk,MENU_OPCION_NORMAL,menu_storage_plusthreedisk_traps,NULL,"~~PLUS3DOS Traps: %s", (plus3dos_traps.v ? "Yes" : "No"));
                        menu_add_item_menu_shortcut(array_menu_plusthreedisk,'k');
                        menu_add_item_menu_tooltip(array_menu_plusthreedisk,"Enable plusthreedisk");
                        menu_add_item_menu_ayuda(array_menu_plusthreedisk,"Enable plusthreedisk");


                        menu_add_item_menu_format(array_menu_plusthreedisk,MENU_OPCION_NORMAL,menu_plusthreedisk_pd765,NULL,"PD765 enabled: %s",(pd765_enabled.v ? "Yes" : "No") );


                        
                                menu_add_item_menu(array_menu_plusthreedisk,"",MENU_OPCION_SEPARADOR,NULL,NULL);

                menu_add_ESC_item(array_menu_plusthreedisk);

                retorno_menu=menu_dibuja_menu(&plusthreedisk_opcion_seleccionada,&item_seleccionado,array_menu_plusthreedisk,"+3 Disk" );

                
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




}

//Comun para coleco y msx y sg1000 y sms
void menu_msxcart_load(MENU_ITEM_PARAMETERS)
{

        char *filtros[5];

		if (MACHINE_IS_COLECO) {
        	filtros[0]="col";
			filtros[1]=0;
		}

		else if (MACHINE_IS_SG1000) {
        	filtros[0]="sg";
			//Aunque extensión SC es de la sega sc3000, algunos cartuchos medio funcionan
			filtros[1]="sc";
			filtros[2]=0;
		}		

		else if (MACHINE_IS_SMS) {
            filtros[0]="sms";
        	filtros[1]="sg";
			//Aunque extensión SC es de la sega sc3000, algunos cartuchos medio funcionan
			filtros[2]="sc";
            filtros[3]="bin";
			filtros[4]=0;
		}	        

		else {
			filtros[0]="rom";
			filtros[1]=0;
		}

        



        //guardamos directorio actual
        char directorio_actual[PATH_MAX];
        getcwd(directorio_actual,PATH_MAX);

        //Obtenemos directorio de ultimo archivo
        //si no hay directorio, vamos a rutas predefinidas
        if (last_msx_cart[0]==0) menu_chdir_sharedfiles();

        else {
                char directorio[PATH_MAX];
                util_get_dir(last_msx_cart,directorio);
                //printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

                //cambiamos a ese directorio, siempre que no sea nulo
                if (directorio[0]!=0) {
                        debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
                        zvfs_chdir(directorio);
                }
        }


        int ret;

        ret=menu_filesel("Select Cartridge",filtros,last_msx_cart);
        //volvemos a directorio inicial
		zvfs_chdir(directorio_actual);


        if (ret==1) {
		//                sprintf (last_msx_cart,"%s",msxcart_load_file);

                //sin overlay de texto, que queremos ver las franjas de carga con el color normal (no apagado)
                reset_menu_overlay_function();


				if (MACHINE_IS_MSX) {
                        msx_insert_rom_cartridge(last_msx_cart);
				}
				else if (MACHINE_IS_SG1000) {
					sg1000_insert_rom_cartridge(last_msx_cart);
				}

				else if (MACHINE_IS_SMS) {
					sms_insert_rom_cartridge(last_msx_cart);
				}                

				else if (MACHINE_IS_SVI) {
					svi_insert_rom_cartridge(last_msx_cart);
				}

				else {
					coleco_insert_rom_cartridge(last_msx_cart);
				}

                //restauramos modo normal de texto de menu
                set_menu_overlay_function(normal_overlay_texto_menu);

                //Y salimos de todos los menus
                salir_todos_menus=1;
        }


}


void menu_msxcart_eject(MENU_ITEM_PARAMETERS)
{

	if (MACHINE_IS_COLECO) coleco_empty_romcartridge_space();
	else if (MACHINE_IS_SG1000) sg1000_empty_romcartridge_space();
    else if (MACHINE_IS_SMS) sms_empty_romcartridge_space();
	else if (MACHINE_IS_SVI) svi_empty_romcartridge_space();
	else msx_empty_romcartridge_space();
	menu_generic_message("Eject Cartridge","OK. Cartridge ejected");
}

void menu_sms_mapper_type(MENU_ITEM_PARAMETERS)
{
    sms_mapper_type++;

    //Si es mayor que el ultimo, resetear
    if (sms_mapper_type>SMS_MAPPER_TYPE_CODEMASTERS) sms_mapper_type=SMS_MAPPER_TYPE_NONE; 
}

void menu_sms_mapper_cartridge_size(MENU_ITEM_PARAMETERS)
{
    sms_cartridge_size *=2;

    if (sms_cartridge_size>SMS_MAX_ROM_SIZE) sms_cartridge_size=8192;

    sms_set_mapper_mask_bits();

}

void menu_msxcart(MENU_ITEM_PARAMETERS)
{

        menu_item *array_menu_msxcart;
        menu_item item_seleccionado;
        int retorno_menu;

        do {


                menu_add_item_menu_inicial(&array_menu_msxcart,"~~Load Cartridge",MENU_OPCION_NORMAL,menu_msxcart_load,NULL);
                menu_add_item_menu_shortcut(array_menu_msxcart,'l');
                menu_add_item_menu_tooltip(array_menu_msxcart,"Load msx Cartridge");
                menu_add_item_menu_ayuda(array_menu_msxcart,"Supported msx cartridge formats on load:\n"
                                        "DCK");

                if (MACHINE_IS_SMS && sms_cartridge_inserted.v) {


                    char buf_mapper_type[33];

                    //Por defecto
                    strcpy(buf_mapper_type,"None");

                    if (sms_mapper_type==SMS_MAPPER_TYPE_SEGA) strcpy(buf_mapper_type,"Sega");
                    if (sms_mapper_type==SMS_MAPPER_TYPE_CODEMASTERS) strcpy(buf_mapper_type,"CodeMasters");

                    menu_add_item_menu_format(array_menu_msxcart,MENU_OPCION_NORMAL,menu_sms_mapper_type,NULL,"[%s] Mapper type",buf_mapper_type);

                    //Esto no tiene mucho sentido cambiarlo a no ser que quieras hacer debug o ver que sucede....
                    menu_add_item_menu_format(array_menu_msxcart,MENU_OPCION_NORMAL,menu_sms_mapper_cartridge_size,NULL,"[%d KB] Cartridge Size",sms_cartridge_size/1024);

                    menu_add_item_menu(array_menu_msxcart,"",MENU_OPCION_SEPARADOR,NULL,NULL);

                }

                //en SMS , solo deja eject si hay algo insertado
                //TODO: hacerlo igual en el resto de maquinas?
                if (MACHINE_IS_SMS) {
                    if (sms_cartridge_inserted.v) menu_add_item_menu(array_menu_msxcart,"~~Eject Cartridge",MENU_OPCION_NORMAL,menu_msxcart_eject,NULL);
                }

                else {
                    menu_add_item_menu(array_menu_msxcart,"~~Eject Cartridge",MENU_OPCION_NORMAL,menu_msxcart_eject,NULL);
                }


                menu_add_item_menu_shortcut(array_menu_msxcart,'e');
                menu_add_item_menu_tooltip(array_menu_msxcart,"Eject Cartridge");
                menu_add_item_menu_ayuda(array_menu_msxcart,"Eject Cartridge");


     				menu_add_item_menu(array_menu_msxcart,"",MENU_OPCION_SEPARADOR,NULL,NULL);
                menu_add_ESC_item(array_menu_msxcart);

				char window_title[64];

				if (MACHINE_IS_COLECO) strcpy(window_title,"Coleco Cartridge");
				else if (MACHINE_IS_SG1000) strcpy(window_title,"SG1000 Cartridge");
                else if (MACHINE_IS_SMS) strcpy(window_title,"SMS Cartridge");
				else if (MACHINE_IS_SVI) strcpy(window_title,"SVI Cartridge");
				else strcpy(window_title,"MSX Cartridge");

                retorno_menu=menu_dibuja_menu(&msxcart_opcion_seleccionada,&item_seleccionado,array_menu_msxcart,window_title);

                

                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);

}




int menu_insert_slot_number;
int menu_insert_slot_ram_size;
int menu_insert_slot_type;
//char menu_insert_slot_rom_name[PATH_MAX];
char menu_insert_slot_eprom_name[PATH_MAX];
char menu_insert_slot_flash_intel_name[PATH_MAX];

void menu_z88_slot_insert_internal_ram(MENU_ITEM_PARAMETERS)
{

	//RAM interna. Siempre entre 32 y 512 K
        if (menu_insert_slot_ram_size==512*1024) menu_insert_slot_ram_size=32*1024;
        else menu_insert_slot_ram_size *=2;
}


void menu_z88_slot_insert_ram(MENU_ITEM_PARAMETERS)
{

	//RAM siempre entre 32 y 1024 K
	if (menu_insert_slot_ram_size==0) menu_insert_slot_ram_size=32768;
	else if (menu_insert_slot_ram_size==1024*1024) menu_insert_slot_ram_size=0;
	else menu_insert_slot_ram_size *=2;
}





int menu_z88_eprom_size(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_z88_eprom_size;
        menu_item item_seleccionado;
        int retorno_menu;

        do {
               //32, 128, 256

                menu_add_item_menu_inicial_format(&array_menu_z88_eprom_size,MENU_OPCION_NORMAL,NULL,NULL,"32 Kb");

                menu_add_item_menu_format(array_menu_z88_eprom_size,MENU_OPCION_NORMAL,NULL,NULL,"128 Kb");

		menu_add_item_menu_format(array_menu_z88_eprom_size,MENU_OPCION_NORMAL,NULL,NULL,"256 Kb");


                menu_add_item_menu(array_menu_z88_eprom_size,"",MENU_OPCION_SEPARADOR,NULL,NULL);
                menu_add_ESC_item(array_menu_z88_eprom_size);

                retorno_menu=menu_dibuja_menu(&z88_eprom_size_opcion_seleccionada,&item_seleccionado,array_menu_z88_eprom_size,"Eprom Size" );

                

                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }

			//Devolver tamanyo eprom
			if (z88_eprom_size_opcion_seleccionada==0) return 32*1024;
			if (z88_eprom_size_opcion_seleccionada==1) return 128*1024;
			if (z88_eprom_size_opcion_seleccionada==2) return 256*1024;
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);

	//Salimos con ESC, devolver 0
	return 0;
}


void menu_z88_slot_insert_eprom(MENU_ITEM_PARAMETERS)
{
        char *filtros[4];

        filtros[0]="eprom";
        filtros[1]="epr";
        filtros[2]="63";
        filtros[3]=0;

	//guardamos directorio actual
        char directorio_actual[PATH_MAX];
        getcwd(directorio_actual,PATH_MAX);

        //Obtenemos directorio de rom
        //si no hay directorio, vamos a rutas predefinidas
        if (menu_insert_slot_eprom_name[0]==0) menu_chdir_sharedfiles();
        else {
                char directorio[PATH_MAX];
                util_get_dir(menu_insert_slot_eprom_name,directorio);
                //printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

                //cambiamos a ese directorio, siempre que no sea nulo
                if (directorio[0]!=0) {
                        debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
                        zvfs_chdir(directorio);
                }
        }



        int ret;

        ret=menu_filesel("Select existing or new",filtros,menu_insert_slot_eprom_name);
        //volvemos a directorio inicial
        zvfs_chdir(directorio_actual);

        if (ret==1) {

       		//Ver si archivo existe y preguntar si inicializar o no
                struct stat buf_stat;

                if (stat(menu_insert_slot_eprom_name, &buf_stat)!=0) {

			if (menu_confirm_yesno_texto("File does not exist","Create?")==0) {
				menu_insert_slot_eprom_name[0]=0;
				return;
			}

			//Preguntar tamanyo EPROM
			int size=menu_z88_eprom_size(0);

			if (size==0) {
				//ha salido con ESC
				menu_insert_slot_eprom_name[0]=0;
				return;
			}


			if (z88_create_blank_eprom_flash_file(menu_insert_slot_eprom_name,size)) {
				menu_insert_slot_eprom_name[0]=0;
			}

			return;
                }
        }

        else menu_insert_slot_eprom_name[0]=0;
}


void menu_z88_slot_insert_hybrid_eprom(MENU_ITEM_PARAMETERS)
{
        char *filtros[4];

        filtros[0]="eprom";
        filtros[1]="epr";
        //filtros[2]="63"; .63 extensions no admitidas para eprom que son hybridas
        filtros[2]=0;

        //guardamos directorio actual
        char directorio_actual[PATH_MAX];
        getcwd(directorio_actual,PATH_MAX);

        //Obtenemos directorio de rom
        //si no hay directorio, vamos a rutas predefinidas
        if (menu_insert_slot_eprom_name[0]==0) menu_chdir_sharedfiles();
        else {
                char directorio[PATH_MAX];
                util_get_dir(menu_insert_slot_eprom_name,directorio);
                //printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

                //cambiamos a ese directorio, siempre que no sea nulo
                if (directorio[0]!=0) {
                        debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
                        zvfs_chdir(directorio);
                }
        }



        int ret;

        ret=menu_filesel("Select existing or new",filtros,menu_insert_slot_eprom_name);
        //volvemos a directorio inicial
        zvfs_chdir(directorio_actual);

  if (ret==1) {

                //Ver si archivo existe y preguntar si inicializar o no
                struct stat buf_stat;

                if (stat(menu_insert_slot_eprom_name, &buf_stat)!=0) {

                        if (menu_confirm_yesno_texto("File does not exist","Create?")==0) {
                                menu_insert_slot_eprom_name[0]=0;
                                return;
                        }

                        //Tamanyo de la parte EPROM es de 512kb
                        int size=512*1024;


                        if (z88_create_blank_eprom_flash_file(menu_insert_slot_eprom_name,size)) {
                                menu_insert_slot_eprom_name[0]=0;
                        }

                        return;
                }
        }

        else menu_insert_slot_eprom_name[0]=0;
}



int menu_z88_flash_intel_size(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_z88_flash_intel_size;
        menu_item item_seleccionado;
        int retorno_menu;

        do {
               //512,1024

                menu_add_item_menu_inicial_format(&array_menu_z88_flash_intel_size,MENU_OPCION_NORMAL,NULL,NULL,"512 Kb");

                menu_add_item_menu_format(array_menu_z88_flash_intel_size,MENU_OPCION_NORMAL,NULL,NULL,"1 Mb");


                menu_add_item_menu(array_menu_z88_flash_intel_size,"",MENU_OPCION_SEPARADOR,NULL,NULL);
                menu_add_ESC_item(array_menu_z88_flash_intel_size);

                retorno_menu=menu_dibuja_menu(&z88_flash_intel_size_opcion_seleccionada,&item_seleccionado,array_menu_z88_flash_intel_size,"Flash Size" );

                

                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }

                        //Devolver tamanyo flash_intel
                        if (z88_flash_intel_size_opcion_seleccionada==0) return 512*1024;
                        if (z88_flash_intel_size_opcion_seleccionada==1) return 1024*1024;
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);

        //Salimos con ESC, devolver 0
        return 0;
}


void menu_z88_slot_insert_flash_intel(MENU_ITEM_PARAMETERS)
{
        char *filtros[2];

        filtros[0]="flash";
        filtros[1]=0;

        int ret;

        ret=menu_filesel("Select existing or new",filtros,menu_insert_slot_flash_intel_name);

        if (ret==1) {

                //Ver si archivo existe y preguntar si inicializar o no
                struct stat buf_stat;

                if (stat(menu_insert_slot_flash_intel_name, &buf_stat)!=0) {

                        if (menu_confirm_yesno_texto("File does not exist","Create?")==0) {
                                menu_insert_slot_flash_intel_name[0]=0;
                                return;
                        }

                        //Preguntar tamanyo Flash
                        int size=menu_z88_flash_intel_size(0);

                        if (size==0) {
                                //ha salido con ESC
                                menu_insert_slot_flash_intel_name[0]=0;
                                return;
                        }


                        if (z88_create_blank_eprom_flash_file(menu_insert_slot_flash_intel_name,size)) {
				menu_insert_slot_flash_intel_name[0]=0;
			}

                        return;
                }
        }

        else menu_insert_slot_flash_intel_name[0]=0;
}




//extern void z88_insert_ram_card(int size,int slot);

//Si se han aplicado cambios (insertar tarjeta memoria) para volver a menu anterior
z80_bit menu_z88_slot_insert_applied_changes={0};

void menu_z88_slot_insert_apply(MENU_ITEM_PARAMETERS)
{

	if (menu_insert_slot_number==0) {
		//Memoria interna

		if (menu_confirm_yesno("Need Hard Reset")==1) {
			z88_change_internal_ram(menu_insert_slot_ram_size);
			menu_z88_slot_insert_applied_changes.v=1;
		}
		return;
	}


	if (menu_insert_slot_type==0) {
		//RAM
		z88_insert_ram_card(menu_insert_slot_ram_size,menu_insert_slot_number);
		menu_z88_slot_insert_applied_changes.v=1;
	}


	/*
	if (menu_insert_slot_type==1) {
                //ROM
		if (menu_insert_slot_rom_name[0]==0) debug_printf (VERBOSE_ERR,"Empty ROM name");

		else {
			z88_load_rom_card(menu_insert_slot_rom_name,menu_insert_slot_number);
			menu_z88_slot_insert_applied_changes.v=1;
		}
	}
	*/

        if (menu_insert_slot_type==2) {
                //EPROM
                if (menu_insert_slot_eprom_name[0]==0) debug_printf (VERBOSE_ERR,"Empty EPROM name");

                else {
			z88_load_eprom_card(menu_insert_slot_eprom_name,menu_insert_slot_number);
			menu_z88_slot_insert_applied_changes.v=1;
		}
        }

        if (menu_insert_slot_type==3) {
                //Intel Flash
                if (menu_insert_slot_flash_intel_name[0]==0) debug_printf (VERBOSE_ERR,"Empty Flash name");

                else {
			z88_load_flash_intel_card(menu_insert_slot_flash_intel_name,menu_insert_slot_number);
			menu_z88_slot_insert_applied_changes.v=1;
		}
        }


        if (menu_insert_slot_type==4) {
                //Hybrida RAM+EPROM
                if (menu_insert_slot_eprom_name[0]==0) debug_printf (VERBOSE_ERR,"Empty EPROM name");

                else {
                        z88_load_hybrid_eprom_card(menu_insert_slot_eprom_name,menu_insert_slot_number);
                        menu_z88_slot_insert_applied_changes.v=1;
                }
        }





}

void menu_z88_slot_insert_change_type(MENU_ITEM_PARAMETERS)
{
	if (menu_insert_slot_ram_size==0) {
		//si no habia, activamos ram con 32kb
		menu_insert_slot_type=0;
		menu_insert_slot_ram_size=32768;
	}

	else if (menu_insert_slot_type==0) {
		//de ram pasamos a eprom
		menu_insert_slot_type=2;
	}

/*	else if (menu_insert_slot_type==1) {
		//de rom pasamos a eprom
		menu_insert_slot_type=2;
	}
*/

        else if (menu_insert_slot_type==2) {
                //de eprom pasamos a flash
                menu_insert_slot_type=3;
        }

        else if (menu_insert_slot_type==3) {
                //de flash pasamos a hybrida ram+eprom
                menu_insert_slot_type=4;
        }




	else {
		//y de flash pasamos a vacio - ram con 0 kb
                menu_insert_slot_type=0;
                menu_insert_slot_ram_size=0;
	}
}


//valor_opcion le viene dado desde la propia funcion de gestion de menu
void menu_z88_slot_insert(MENU_ITEM_PARAMETERS)
{
	//menu_insert_slot_number=z88_slots_opcion_seleccionada;


	menu_insert_slot_number=valor_opcion;

	debug_printf (VERBOSE_DEBUG,"Slot selected on menu: %d",menu_insert_slot_number);

	if (menu_insert_slot_number<0 || menu_insert_slot_number>3) cpu_panic ("Invalid slot number");

	menu_z88_slot_insert_applied_changes.v=0;


	if (menu_insert_slot_number>0) {
		//Memoria externa
		//guardamos tamanyo +1
		menu_insert_slot_ram_size=z88_memory_slots[menu_insert_slot_number].size+1;

		if (menu_insert_slot_ram_size==1) menu_insert_slot_ram_size=0;

		menu_insert_slot_type=z88_memory_slots[menu_insert_slot_number].type;
	}

	else {
		//Memoria interna
		//guardamos tamanyo +1

		menu_insert_slot_ram_size=z88_internal_ram_size+1;
	}



	//reseteamos nombre rom
	//menu_insert_slot_rom_name[0]=0;

	//copiamos nombre eprom/flash a las dos variables
	strcpy(menu_insert_slot_eprom_name,z88_memory_slots[menu_insert_slot_number].eprom_flash_nombre_archivo);

	strcpy(menu_insert_slot_flash_intel_name,z88_memory_slots[menu_insert_slot_number].eprom_flash_nombre_archivo);




        menu_item *array_menu_z88_slot_insert;
        menu_item item_seleccionado;
        int retorno_menu;
        //char string_slot_name_shown[20];
	char string_slot_eprom_name_shown[20],string_slot_flash_intel_name_shown[20];
	char string_memory_type[20];

        do {

		//menu_tape_settings_trunc_name(menu_insert_slot_rom_name,string_slot_name_shown,20);

		menu_tape_settings_trunc_name(menu_insert_slot_eprom_name,string_slot_eprom_name_shown,20);
		menu_tape_settings_trunc_name(menu_insert_slot_flash_intel_name,string_slot_flash_intel_name_shown,20);


                //int slot;


		if (menu_insert_slot_ram_size==0) sprintf (string_memory_type,"%s","Empty");
		else sprintf (string_memory_type,"%s",z88_memory_types[menu_insert_slot_type]);

		//Memorias externas

		if (menu_insert_slot_number>0) {

			menu_add_item_menu_inicial_format(&array_menu_z88_slot_insert,MENU_OPCION_NORMAL,menu_z88_slot_insert_change_type,NULL,"Memory type: %s",string_memory_type);
        	        menu_add_item_menu_tooltip(array_menu_z88_slot_insert,"Type of memory card if present");
                	menu_add_item_menu_ayuda(array_menu_z88_slot_insert,"Type of memory card if present");

			if (menu_insert_slot_type==0) {
				//RAM
				menu_add_item_menu_format(array_menu_z88_slot_insert,MENU_OPCION_NORMAL,menu_z88_slot_insert_ram,NULL,"Size: %d Kb",(menu_insert_slot_ram_size)/1024);
		                menu_add_item_menu_tooltip(array_menu_z88_slot_insert,"Size of RAM card");
        		        menu_add_item_menu_ayuda(array_menu_z88_slot_insert,"Size of RAM card");

			}

			if (menu_insert_slot_type==1) {
				cpu_panic("ROM cards do not exist on Z88");
				
			}

			if (menu_insert_slot_type==2) {
                	        //EPROM
                        	menu_add_item_menu_format(array_menu_z88_slot_insert,MENU_OPCION_NORMAL,menu_z88_slot_insert_eprom,NULL,"Name: %s",string_slot_eprom_name_shown);
		                menu_add_item_menu_tooltip(array_menu_z88_slot_insert,"EPROM file to use");
        		        menu_add_item_menu_ayuda(array_menu_z88_slot_insert,"EPROM file to use. Valid formats are .eprom. Select existing or new");

                	}

                        if (menu_insert_slot_type==3) {
                                //Intel Flash
                                menu_add_item_menu_format(array_menu_z88_slot_insert,MENU_OPCION_NORMAL,menu_z88_slot_insert_flash_intel,NULL,"Name: %s",string_slot_flash_intel_name_shown);
                                menu_add_item_menu_tooltip(array_menu_z88_slot_insert,"Intel Flash file to use");
                                menu_add_item_menu_ayuda(array_menu_z88_slot_insert,"Intel Flash file to use. Valid formats are .flash. Select existing or new");

                        }

			if (menu_insert_slot_type==4) {
                                //Hybrida RAM+EPROM
                                menu_add_item_menu_format(array_menu_z88_slot_insert,MENU_OPCION_NORMAL,menu_z88_slot_insert_hybrid_eprom,NULL,"Name: %s",string_slot_eprom_name_shown);
                                menu_add_item_menu_tooltip(array_menu_z88_slot_insert,"Hybrid RAM+EPROM file to use");
                                menu_add_item_menu_ayuda(array_menu_z88_slot_insert,"Hybrid RAM+EPROM file to use. Valid formats are .eprom. Select existing or new");

                        }



		}

		else {
			//Memoria interna
			menu_add_item_menu_inicial_format(&array_menu_z88_slot_insert,MENU_OPCION_NORMAL,menu_z88_slot_insert_internal_ram,NULL,"RAM Size: %d Kb",(menu_insert_slot_ram_size)/1024);
			menu_add_item_menu_tooltip(array_menu_z88_slot_insert,"Size of RAM card");
                        menu_add_item_menu_ayuda(array_menu_z88_slot_insert,"Size of RAM card");
		}




		menu_add_item_menu_format(array_menu_z88_slot_insert,MENU_OPCION_NORMAL,menu_z88_slot_insert_apply,NULL,"Apply changes");
                menu_add_item_menu_tooltip(array_menu_z88_slot_insert,"Apply slot changes");
                menu_add_item_menu_ayuda(array_menu_z88_slot_insert,"Apply slot changes");





                menu_add_item_menu(array_menu_z88_slot_insert,"",MENU_OPCION_SEPARADOR,NULL,NULL);


                menu_add_ESC_item(array_menu_z88_slot_insert);

                //retorno_menu=menu_dibuja_menu(&z88_slot_insert_opcion_seleccionada,&item_seleccionado,array_menu_z88_slot_insert,"Z88 Memory Slots" );

		//Titulo de la ventana variable segun el nombre del slot
		char texto_titulo[32];
		sprintf (texto_titulo,"Z88 Memory Slot %d",menu_insert_slot_number);

                retorno_menu=menu_dibuja_menu(&z88_slot_insert_opcion_seleccionada,&item_seleccionado,array_menu_z88_slot_insert,texto_titulo);

                

                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus && !menu_z88_slot_insert_applied_changes.v );


}

void menu_z88_slot_erase_eprom_flash(MENU_ITEM_PARAMETERS)
{
        if (menu_confirm_yesno("Erase Card")==1) {
		z88_erase_eprom_flash();
		menu_generic_message("Erase Card","OK. Card erased");
        }
}

void menu_z88_eprom_flash_reclaim_free_space(MENU_ITEM_PARAMETERS)
{
       if (menu_confirm_yesno("Reclaim Free Space")==1) {
                z80_long_int liberados=z88_eprom_flash_reclaim_free_space();
                menu_generic_message_format("Reclaim Free Space","OK. %d bytes reclaimed",liberados);
        }

}

void menu_z88_eprom_flash_undelete_files(MENU_ITEM_PARAMETERS)
{
       if (menu_confirm_yesno("Undelete Files")==1) {
                z80_long_int undeleted=z88_eprom_flash_recover_deleted();
                menu_generic_message_format("Undelete Files","OK. %d files undeleted",undeleted);
        }

}

char copy_to_eprom_nombrearchivo[PATH_MAX]="";

void menu_z88_slot_copy_to_eprom_flash(MENU_ITEM_PARAMETERS)
{

	//printf ("%d\n",sizeof(copy_to_eprom_nombrearchivo));

        char *filtros[2];

        filtros[0]="";
        filtros[1]=0;


        //guardamos directorio actual
        char directorio_actual[PATH_MAX];
        getcwd(directorio_actual,PATH_MAX);

        int ret;


        //Obtenemos ultimo directorio visitado
        if (copy_to_eprom_nombrearchivo[0]!=0) {
                char directorio[PATH_MAX];
                util_get_dir(copy_to_eprom_nombrearchivo,directorio);
                //printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

                //cambiamos a ese directorio, siempre que no sea nulo
                if (directorio[0]!=0) {
                        debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
                        zvfs_chdir(directorio);
                }
        }




        ret=menu_filesel("Select file to copy",filtros,copy_to_eprom_nombrearchivo);

        //volvemos a directorio inicial
        zvfs_chdir(directorio_actual);

        if (ret==1) {
		//Cargamos archivo en memoria. Maximo 128 KB
		z80_byte *datos;
		const z80_long_int max_load=131072;
		datos=malloc(max_load);

		FILE *ptr_load;
		ptr_load=fopen(copy_to_eprom_nombrearchivo,"rb");

		if (!ptr_load) {
			debug_printf (VERBOSE_ERR,"Unable to open file %s",copy_to_eprom_nombrearchivo);
			return;
		}


		z80_long_int leidos=fread(datos,1,max_load,ptr_load);
		if (leidos==max_load) {
			debug_printf (VERBOSE_ERR,"Can not load more than %d bytes",max_load);
			return;
		}


		if (leidos<1) {
			debug_printf (VERBOSE_ERR,"No bytes read");
			return;
		}


		//esto puede retornar algun error mediante debug_printf
		//nombre en eprom, quitando carpetas
		char nombre_eprom[256];
		util_get_file_no_directory(copy_to_eprom_nombrearchivo,nombre_eprom);


		//Preguntar nombre en destino. Truncar a maximo de nombre en tarjeta memoria
		nombre_eprom[Z88_MAX_CARD_FILENAME]=0;
		menu_ventana_scanf("Target file name?",nombre_eprom,Z88_MAX_CARD_FILENAME+1);


		if (z88_eprom_flash_fwrite(nombre_eprom,datos,leidos)==0) {
			menu_generic_message("Copy File","OK. File copied to Card");
		}

		free(datos);

	}

}

void menu_z88_slot_card_browser_aux(int slot,char *texto_buffer,int max_texto)
{
        z88_dir dir;
        z88_eprom_flash_file file;

        z88_eprom_flash_find_init(&dir,slot);

        char buffer_nombre[Z88_MAX_CARD_FILENAME+1];

        int retorno;
        int longitud;


        int indice_buffer=0;

        do {
                retorno=z88_eprom_flash_find_next(&dir,&file);
                if (retorno) {
                        z88_eprom_flash_get_file_name(&file,buffer_nombre);

			if (buffer_nombre[0]=='.') buffer_nombre[0]='D'; //archivo borrado

			//printf ("nombre: %s c1: %d\n",buffer_nombre,buffer_nombre[0]);
                        longitud=strlen(buffer_nombre)+1; //Agregar salto de linea
                        if (indice_buffer+longitud>max_texto-1) retorno=0;
                        else {
                                sprintf (&texto_buffer[indice_buffer],"%s\n",buffer_nombre);
                                indice_buffer +=longitud;
                        }

                }
        } while (retorno!=0);

        texto_buffer[indice_buffer]=0;

}

void menu_z88_slot_card_browser(MENU_ITEM_PARAMETERS)
{
#define MAX_TEXTO 4096
        char texto_buffer[MAX_TEXTO];

        int slot=valor_opcion;

        menu_z88_slot_card_browser_aux(slot,texto_buffer,MAX_TEXTO);


	//Si esta vacio
        if (texto_buffer[0]==0) {
                debug_printf(VERBOSE_ERR,"Card is empty");
                return;
        }

        //menu_generic_message_tooltip("Card browser", 0, 0, 1, NULL, "%s", texto_buffer);

	zxvision_generic_message_tooltip("Card Browser" , 0 , 0, 0, 1, NULL, 1, "%s", texto_buffer);		

}


void menu_z88_slot_copy_from_eprom(MENU_ITEM_PARAMETERS)
{
#define MAX_TEXTO 4096
	char texto_buffer[MAX_TEXTO];

	int slot=valor_opcion;

	menu_z88_slot_card_browser_aux(slot,texto_buffer,MAX_TEXTO);

	//Si esta vacio
	if (texto_buffer[0]==0) {
		debug_printf(VERBOSE_ERR,"Card is empty");
                return;
        }



	//printf ("archivos: %s\n",texto_buffer);
	generic_message_tooltip_return retorno_archivo;
	//menu_generic_message_tooltip("Select file", 0, 0, 1, &retorno_archivo, "%s", texto_buffer);
	zxvision_generic_message_tooltip("Select file" , 0 , 0, 0, 1, &retorno_archivo, 1,"%s", texto_buffer);

	//Si se sale con ESC
	if (retorno_archivo.estado_retorno==0) return;

       //        strcpy(retorno->texto_seleccionado,buffer_lineas[linea_final];
       //         retorno->linea_seleccionada=linea_final;
	//printf ("Seleccionado: (%s) linea: %d\n",retorno_archivo.texto_seleccionado,retorno_archivo.linea_seleccionada);
	//nombre archivo viene con espacio al final


	int longitud_nombre=strlen(retorno_archivo.texto_seleccionado);
	if (longitud_nombre) {
		if (retorno_archivo.texto_seleccionado[longitud_nombre-1] == ' ') {
			retorno_archivo.texto_seleccionado[longitud_nombre-1]=0;
		}
	}



        z88_dir dir;
        z88_eprom_flash_file file;


	z88_find_eprom_flash_file (&dir,&file,retorno_archivo.texto_seleccionado, slot);


	//con el puntero a dir, retornamos file

	//printf ("dir: %x bank: %x\n",dir.dir,dir.bank);

	//z88_return_eprom_flash_file (&dir,&file);

	//Si no es archivo valido
	if (file.namelength==0 || file.namelength==255) {
		debug_printf (VERBOSE_ERR,"File not found");
		return;
	}


	//Grabar archivo en disco. Supuestamente le damos el mismo nombre evitando la / inicial

	//Con selector de archivos
	char nombredestino[PATH_MAX];

	char *filtros[2];

        filtros[0]="";
        filtros[1]=0;


        if (menu_filesel("Select Target File",filtros,nombredestino)==0) return;


	//Ver si archivo existe
	if (si_existe_archivo(nombredestino)) {
		if (menu_confirm_yesno_texto("File exists","Overwrite?")==0) return;
	}




	//Hacer que dir apunte a los datos
	dir.bank=file.datos.bank;
	dir.dir=file.datos.dir;

	z80_byte byte_leido;

                                FILE *ptr_file_save;
                                  ptr_file_save=fopen(nombredestino,"wb");
                                  if (!ptr_file_save)
                                {
                                      debug_printf (VERBOSE_ERR,"Unable to open Binary file %s",nombredestino);

                                  }
                                else {
					unsigned int i;
					z80_long_int size=file.size[0]+(file.size[1]*256)+(file.size[2]*65536)+(file.size[3]*16777216);

					for (i=0;i<size;i++) {
						byte_leido=peek_byte_no_time_z88_bank_no_check_low(dir.dir,dir.bank);
						z88_increment_pointer(&dir);
						fwrite(&byte_leido,1,1,ptr_file_save);
					}


                                  fclose(ptr_file_save);
				}
	menu_generic_message("Copy File","OK. File copied from Card to Disk");




}


//menu z88 slots
void menu_z88_slots(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_z88_slots;
        menu_item item_seleccionado;
        int retorno_menu;

        do {

		menu_add_item_menu_inicial_format(&array_menu_z88_slots,MENU_OPCION_NORMAL,menu_z88_slot_insert,NULL,"ROM: %d Kb RAM: %d Kb",(z88_internal_rom_size+1)/1024,(z88_internal_ram_size+1)/1024);
                menu_add_item_menu_tooltip(array_menu_z88_slots,"Internal ROM and RAM");
                menu_add_item_menu_ayuda(array_menu_z88_slots,"Internal RAM can be maximum 512 KB. Internal ROM can be changed from \n"
					"Machine Menu->Custom Machine, and can also be maximum 512 KB");

                //establecemos numero slot como opcion de ese item de menu
                menu_add_item_menu_valor_opcion(array_menu_z88_slots,0);



		int slot;

		//int eprom_flash_invalida_en_slot_3=0;

		for (slot=1;slot<=3;slot++) {

			int eprom_flash_valida=0;
			int tipo_tarjeta=-1;
			char *tipos_tarjeta[]={"APP","FIL","MIX"};
			int type;

			//Si no hay slot insertado
			if (z88_memory_slots[slot].size==0) {
				menu_add_item_menu_format(array_menu_z88_slots,MENU_OPCION_NORMAL,menu_z88_slot_insert,NULL,"Empty");
			}

			else {
				type=z88_memory_slots[slot].type;

				//Si es flash/eprom en slot de escritura(3), indicar a que archivo hace referencia
				if (slot==3 && (type==2 || type==3 || type==4) ) {
					char string_writable_card_shown[18];
					menu_tape_settings_trunc_name(z88_memory_slots[slot].eprom_flash_nombre_archivo,string_writable_card_shown,18);
					menu_add_item_menu_format(array_menu_z88_slots,MENU_OPCION_NORMAL,menu_z88_slot_insert,NULL,"%s: %s",z88_memory_types[type],string_writable_card_shown);
				}
				else {
					menu_add_item_menu_format(array_menu_z88_slots,MENU_OPCION_NORMAL,menu_z88_slot_insert,NULL,"%s",z88_memory_types[type]);
				}
			}

			//establecemos numero slot como opcion de ese item de menu
			menu_add_item_menu_valor_opcion(array_menu_z88_slots,slot);
	                menu_add_item_menu_tooltip(array_menu_z88_slots,"Type of memory card if present and file name in case of slot 3 and EPROM/Flash cards");
        	        menu_add_item_menu_ayuda(array_menu_z88_slots,"Type of memory card if present and file name in case of slot 3 and EPROM/Flash cards.\n"
						"Slot 1, 2 or 3 can contain "
						"EPROM or Intel Flash cards. But EPROMS and Flash cards can only be written on slot 3\n"
						"EPROM/Flash cards files on slots 1,2 are only used at insert time and loaded on Z88 memory\n"
						"EPROM/Flash cards files on slot 3 are loaded on Z88 memory at insert time but are written everytime \n"
						"a change is made on this Z88 memory, so, they are always used when they are inserted\n"
						"\n"
						"Flash card files and eprom files are internally compatible, but eprom size maximum is 256 Kb "
						"and flash minimum size is 512 Kb, so you can not load an eprom file as a flash or viceversa\n"
						);
						//"Note: if you use OZ rom 4.3.1 or higher, flash cards are recognized well; if you use a lower "
						//"version, flash cards are recognized as eprom cards");

			if (z88_memory_slots[slot].size!=0) {

				int size=(z88_memory_slots[slot].size+1)/1024;

				//Si es EPROM o Flash, decir espacio libre, detectando si hay una tarjeta con filesystem
				char string_info_tarjeta[40];
				if (type==2 || type==3 || type==4) {
					z80_long_int total_eprom,used_eprom, free_eprom;
					tipo_tarjeta=z88_return_card_type(slot);
					debug_printf (VERBOSE_DEBUG,"Card type: %d",tipo_tarjeta);

					if (tipo_tarjeta>0) {

						//No buscar filesystem en caso de tarjeta hibrida
						if (type==4) {
							sprintf (string_info_tarjeta," (%s) %d kb Free Unkn",tipos_tarjeta[tipo_tarjeta],size);
                                                }

						else {

							z88_eprom_flash_free(&total_eprom,&used_eprom, &free_eprom,slot);

							//Controlar si eprom corrupta, tamanyos logicos
							if (free_eprom>1024*1024) {
								sprintf (string_info_tarjeta," (%s) %d kb Free Unkn",tipos_tarjeta[tipo_tarjeta],size);
							}

							else {
								sprintf (string_info_tarjeta," (%s) %d K Free %d K",tipos_tarjeta[tipo_tarjeta],size,free_eprom/1024);
								eprom_flash_valida=1;
							}
						}
					}

					else {
						//0 o -1
						if (tipo_tarjeta==0) {
							sprintf (string_info_tarjeta," (%s) %d kb",tipos_tarjeta[tipo_tarjeta],size);
						}
						else {
							sprintf (string_info_tarjeta," (Unk) %d kb",size);
						}
					}
				}

				else {
					sprintf (string_info_tarjeta," %d K",size);
				}

				menu_add_item_menu_format(array_menu_z88_slots,MENU_OPCION_NORMAL,NULL,NULL,"%s",string_info_tarjeta);
				menu_add_item_menu_tooltip(array_menu_z88_slots,"Card Information");
				menu_add_item_menu_ayuda(array_menu_z88_slots,"Size of Card, and in case of EPROM/Flash cards: \n"
							"-Type of Card: Applications, Files or Unknown type\n"
							"-Space Available, in case of Files Card\n");


			}

			//Si hay una eprom en slot 3, dar opcion de borrar
			if (slot==3 && z88_memory_slots[3].size!=0 && (z88_memory_slots[3].type==2 || z88_memory_slots[3].type==3) ) {
				menu_add_item_menu_format(array_menu_z88_slots,MENU_OPCION_NORMAL,menu_z88_slot_erase_eprom_flash,NULL," Erase Card");
	                        menu_add_item_menu_tooltip(array_menu_z88_slots,"Card can only be erased on slot 3");
        	                menu_add_item_menu_ayuda(array_menu_z88_slots,"Card can only be erased on slot 3");
			}



			if (eprom_flash_valida && tipo_tarjeta>0) {

				if (slot==3) {

					menu_add_item_menu_format(array_menu_z88_slots,MENU_OPCION_NORMAL,menu_z88_eprom_flash_reclaim_free_space,NULL," Reclaim Free Space");
					menu_add_item_menu_tooltip(array_menu_z88_slots,"It reclaims the space used by deleted files");
					menu_add_item_menu_ayuda(array_menu_z88_slots,"It reclaims the space used by deleted files");

					menu_add_item_menu_format(array_menu_z88_slots,MENU_OPCION_NORMAL,menu_z88_eprom_flash_undelete_files,NULL," Undelete Files");
					menu_add_item_menu_tooltip(array_menu_z88_slots,"Undelete deleted files");
					menu_add_item_menu_ayuda(array_menu_z88_slots,"Undelete deleted files");


					menu_add_item_menu_format(array_menu_z88_slots,MENU_OPCION_NORMAL,menu_z88_slot_copy_to_eprom_flash,NULL," Copy to Card");
					menu_add_item_menu_tooltip(array_menu_z88_slots,"Copy files from your hard drive to Card");
					menu_add_item_menu_ayuda(array_menu_z88_slots,"Copy files from your hard drive to Card. "
						"Card card must be initialized before you can copy files to it, "
						"I mean, if it's a new card, it must be erased and Z88 Filer must know it; usually it is needed to copy "
						"at least one file from Filer");
				}




				menu_add_item_menu_format(array_menu_z88_slots,MENU_OPCION_NORMAL,menu_z88_slot_card_browser,NULL," Card browser");
				menu_add_item_menu_tooltip(array_menu_z88_slots,"Browse card");
				menu_add_item_menu_ayuda(array_menu_z88_slots,"Browse card");
	                        //establecemos numero slot como opcion de ese item de menu
        	                menu_add_item_menu_valor_opcion(array_menu_z88_slots,slot);

				menu_add_item_menu_format(array_menu_z88_slots,MENU_OPCION_NORMAL,menu_z88_slot_copy_from_eprom,NULL," Copy from Card");
				menu_add_item_menu_tooltip(array_menu_z88_slots,"Copy files from Card to your hard drive");
				menu_add_item_menu_ayuda(array_menu_z88_slots,"Copy files from Card to your hard drive");
	                        //establecemos numero slot como opcion de ese item de menu
        	                menu_add_item_menu_valor_opcion(array_menu_z88_slots,slot);


			}

		}


                menu_add_item_menu(array_menu_z88_slots,"",MENU_OPCION_SEPARADOR,NULL,NULL);


		menu_add_ESC_item(array_menu_z88_slots);

                retorno_menu=menu_dibuja_menu(&z88_slots_opcion_seleccionada,&item_seleccionado,array_menu_z88_slots,"Z88 Memory Slots" );

                

                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);


}




void menu_tape_browser(MENU_ITEM_PARAMETERS)
{
	menu_tape_browser_show(tapefile);
}

void menu_tape_browser_output(MENU_ITEM_PARAMETERS)
{
	menu_tape_browser_show(tape_out_file);
}

void menu_tape_browser_real(MENU_ITEM_PARAMETERS)
{
	menu_tape_browser_show(realtape_name);
}


void menu_tape_input_insert(MENU_ITEM_PARAMETERS)
{

	if (tapefile==NULL) return;

	if ((tape_loadsave_inserted & TAPE_LOAD_INSERTED)==0) {
		tap_open();
	}

	else {
		tap_close();
	}
}


//Retorna 0=Cancel, 1=Append, 2=Truncate, 3=Rotate
int menu_ask_no_append_truncate_texto(char *texto_ventana,char *texto_interior)
{

	

        cls_menu_overlay();

        menu_espera_no_tecla();


	menu_item *array_menu_ask_no_append_truncate;
        menu_item item_seleccionado;
        int retorno_menu;

	//Siempre indicamos el Cancel
	int ask_no_append_truncate_opcion_seleccionada=1;
	do {

		menu_add_item_menu_inicial_format(&array_menu_ask_no_append_truncate,MENU_OPCION_SEPARADOR,NULL,NULL,texto_interior);

		menu_add_item_menu_format(array_menu_ask_no_append_truncate,MENU_OPCION_NORMAL,NULL,NULL,"~~Cancel");
		menu_add_item_menu_shortcut(array_menu_ask_no_append_truncate,'c');
		menu_add_item_menu_tooltip(array_menu_ask_no_append_truncate,"Cancel operation and don't set file");
		menu_add_item_menu_ayuda(array_menu_ask_no_append_truncate,"Cancel operation and don't set file");		

		menu_add_item_menu_format(array_menu_ask_no_append_truncate,MENU_OPCION_NORMAL,NULL,NULL,"~~Append");
		menu_add_item_menu_shortcut(array_menu_ask_no_append_truncate,'a');
		menu_add_item_menu_tooltip(array_menu_ask_no_append_truncate,"Open the selected file in append mode");
		menu_add_item_menu_ayuda(array_menu_ask_no_append_truncate,"Open the selected file in append mode");			

		menu_add_item_menu_format(array_menu_ask_no_append_truncate,MENU_OPCION_NORMAL,NULL,NULL,"~~Truncate");
		menu_add_item_menu_shortcut(array_menu_ask_no_append_truncate,'t');
		menu_add_item_menu_tooltip(array_menu_ask_no_append_truncate,"Truncates selected file to 0 size");
		menu_add_item_menu_ayuda(array_menu_ask_no_append_truncate,"Truncates selected file to 0 size");			

		menu_add_item_menu_format(array_menu_ask_no_append_truncate,MENU_OPCION_NORMAL,NULL,NULL,"~~Rotate");
		menu_add_item_menu_shortcut(array_menu_ask_no_append_truncate,'r');	
		menu_add_item_menu_tooltip(array_menu_ask_no_append_truncate,"Rotate selected file to keep history files");
		menu_add_item_menu_ayuda(array_menu_ask_no_append_truncate,"Rename selected file adding extension suffix .1. \n"
			"If that file also exists, the extension suffix is renamed to .2. \n"
			"If that file also exists, the extension suffix is renamed to .3, and so on... \n"
			"You can set the maximum file rotations, by default 10."
		
			);							

		//separador adicional para que quede mas grande la ventana y mas mono
		menu_add_item_menu_format(array_menu_ask_no_append_truncate,MENU_OPCION_SEPARADOR,NULL,NULL," ");



		retorno_menu=menu_dibuja_menu(&ask_no_append_truncate_opcion_seleccionada,&item_seleccionado,array_menu_ask_no_append_truncate,texto_ventana);

		

		if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
				//llamamos por valor de funcion
	//if (ask_no_append_truncate_opcion_seleccionada==1) return 1;
	//else return 0;
				return ask_no_append_truncate_opcion_seleccionada-1; //0=Cancel, 1=Append, 2=Truncate, 3=Rotate
		}

	} while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);

	return 0;


}



int menu_tape_out_open_last_rotated=10;

void menu_tape_out_open(MENU_ITEM_PARAMETERS)
{

	char *filtros[5];
	char mensaje_existe[20];

	if (MACHINE_IS_ZX8081) {

		if (MACHINE_IS_ZX80) filtros[0]="o";
		else filtros[0]="p";

		filtros[1]=0;

		strcpy(mensaje_existe,"Overwrite?");
	}

	else {
		filtros[0]="tzx";
		filtros[1]="tap";
		filtros[2]="pzx";
		filtros[3]=0;
		strcpy(mensaje_existe,"Append?");
	}


	if (menu_filesel("Select Output Tape",filtros,tape_out_open_file)==1) {

		//Ver si archivo existe y preguntar
		struct stat buf_stat;

		if (stat(tape_out_open_file, &buf_stat)==0) {

			if (MACHINE_IS_ZX8081) {
					if (menu_confirm_yesno_texto("File exists",mensaje_existe)==0) {
						tape_out_file=NULL;
						tap_out_close();
						return;
				}
			}

			else {
				int opcion=menu_ask_no_append_truncate_texto("File exists","What do you want?");
				//printf ("opcion: %d\n",opcion);

				//Cancel
				if (opcion==0) {
					tape_out_file=NULL;
					tap_out_close();
					return;
				}

				//Truncate
				if (opcion==2) {
					util_truncate_file(tape_out_open_file);
				}

				//Rotate
				if (opcion==3) {
					//Rotar
					char string_rotaciones[3];


					int valor_leido;
					sprintf (string_rotaciones,"%d",menu_tape_out_open_last_rotated);

					menu_ventana_scanf("Number of files",string_rotaciones,3);

					valor_leido=parse_string_to_number(string_rotaciones);

					if (valor_leido<1 || valor_leido>99) {
							debug_printf (VERBOSE_ERR,"Invalid value %d",valor_leido);
							tape_out_file=NULL;
							tap_out_close();
							return;
					}

					menu_tape_out_open_last_rotated=valor_leido;


					util_rotate_file(tape_out_open_file,menu_tape_out_open_last_rotated);
					//El actual ya se creará cuando se escriba la primera vez
				}				

			}

		}

		tape_out_file=tape_out_open_file;
		tape_out_init();
	}


	else {
		tape_out_file=NULL;
		tap_out_close();
	}



}


void menu_tape_open(MENU_ITEM_PARAMETERS)
{

        char *filtros[7];

	if (MACHINE_IS_ZX80) {
		filtros[0]="80";
        	filtros[1]="o";
        	filtros[2]="rwa";
        	filtros[3]="smp";
        	filtros[4]="wav";
        	filtros[5]="z81";
        	filtros[6]=0;
	}

	else if (MACHINE_IS_ZX81) {
                filtros[0]="p";
                filtros[1]="81";
                filtros[2]="rwa";
                filtros[3]="smp";
                filtros[4]="z81";
                filtros[5]="wav";
                filtros[6]=0;
        }

	else if (MACHINE_IS_MSX) {
                filtros[0]="cas";
                filtros[1]=0;
        }		

	else if (MACHINE_IS_SVI) {
                filtros[0]="cas";
                filtros[1]=0;
        }				

	else {
        filtros[0]="tzx";
        filtros[1]="tap";
        filtros[2]="rwa";
        filtros[3]="smp";
        filtros[4]="wav";
        filtros[5]=0;
	}


	//guardamos directorio actual
	char directorio_actual[PATH_MAX];
	getcwd(directorio_actual,PATH_MAX);

	//Obtenemos directorio de cinta
	//si no hay directorio, vamos a rutas predefinidas
	if (tapefile==NULL) menu_chdir_sharedfiles();

	else {
	        char directorio[PATH_MAX];
	        util_get_dir(tapefile,directorio);
	        //printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

		//cambiamos a ese directorio, siempre que no sea nulo
		if (directorio[0]!=0) {
			debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
			zvfs_chdir(directorio);
		}
	}



        int ret;

        ret=menu_filesel("Select Input Tape",filtros,tape_open_file);
        //volvemos a directorio inicial
        zvfs_chdir(directorio_actual);


	if (ret==1) {
		tapefile=tape_open_file;
		tape_init();
	}


}

int menu_tape_input_insert_cond(void)
{
	if (tapefile==NULL) return 0;
	else return 1;
}

int menu_tape_output_insert_cond(void)
{
        if (tape_out_file==NULL) return 0;
        else return 1;
}

void menu_tape_output_insert(MENU_ITEM_PARAMETERS)
{

        if (tape_out_file==NULL) return;

	if ((tape_loadsave_inserted & TAPE_SAVE_INSERTED)==0) {
                tap_out_open();
        }

        else {
                tap_out_close();
        }
}


void menu_realtape_insert(MENU_ITEM_PARAMETERS)
{
	if (realtape_inserted.v==0) realtape_insert();
	else realtape_eject();
}

int menu_realtape_cond(void)
{
	if (realtape_name==NULL) return 0;
	else return 1;
}

int menu_realtape_inserted_cond(void)
{
	if (menu_realtape_cond()==0) return 0;
	return realtape_inserted.v;
}

void menu_realtape_pause_unpause(MENU_ITEM_PARAMETERS)
{
	//Este if solo es util cuando se llama desde una tecla F
	if (!menu_realtape_inserted_cond()) return;

	realtape_pause_unpause();
}

//Esto de momento solo se llama desde una tecla F. Lo pongo aqui para que este cerca de las condiciones y acciones de insert
void menu_reinsert_real_tape(void)
{

	debug_printf(VERBOSE_DEBUG,"Running reinsert real tape");

	if (!menu_realtape_cond() ) {
		debug_printf(VERBOSE_DEBUG,"No real inserted to reinsert");
		return;
	}

	//Si esta insertada, expulsar
	if (realtape_inserted.v) {
		debug_printf(VERBOSE_DEBUG,"Ejecting tape");
		realtape_eject();
	}

	//E insertar
	debug_printf(VERBOSE_DEBUG,"Inserting tape");
	realtape_insert();
}



//menu storage tape 
void menu_storage_tape(MENU_ITEM_PARAMETERS)
{
    menu_item *array_menu_tape_settings;
	menu_item item_seleccionado;
	int retorno_menu;

    do {
        char string_tape_load_shown[20],string_tape_save_shown[20];
        //char string_tape_load_inserted[50],string_tape_save_inserted[50];
		char string_realtape_shown[23];

		menu_add_item_menu_inicial_format(&array_menu_tape_settings,MENU_OPCION_NORMAL,NULL,NULL,"--Standard Tape--");
        menu_add_item_menu_spanish_catalan(array_menu_tape_settings,"--Cinta Estandar--","--Cinta Estandard--");
		menu_add_item_menu_tooltip(array_menu_tape_settings,"Select Standard tape for Input and Output");
		menu_add_item_menu_ayuda(array_menu_tape_settings,"Standard tapes are those handled by ROM routines and "
					"have normal speed (no turbo). These tapes are handled by the emulator and loaded or saved "
					"very quickly. The input formats supported are: o, p, tap, tzx (binary only), rwa, wav and smp; "
					"output formats are: o, p, tap and tzx. Those input audio formats (rwa, wav or smp) "
					"are converted by the emulator to bytes and loaded on the machine memory. For every other non standard "
					"tapes (turbo or handled by non-ROM routines like loading stripes on different colours) you must use "
					"Real Input tape for load, and Audio output to file for saving");


		menu_tape_settings_trunc_name(tapefile,string_tape_load_shown,20);
		menu_add_item_menu_format(array_menu_tape_settings,MENU_OPCION_NORMAL,menu_tape_open,NULL,"~~Input [%s]",string_tape_load_shown);
		menu_add_item_menu_shortcut(array_menu_tape_settings,'i');


		//sprintf (string_tape_load_inserted,"[%c] Input tape inserted",((tape_loadsave_inserted & TAPE_LOAD_INSERTED)!=0 ? 'X' : ' '));
		//menu_add_item_menu(array_menu_tape_settings,string_tape_load_inserted,MENU_OPCION_NORMAL,menu_tape_input_insert,menu_tape_input_insert_cond);

        menu_add_item_menu_format(array_menu_tape_settings,MENU_OPCION_NORMAL,menu_tape_input_insert,menu_tape_input_insert_cond,
            "[%c] Input tape inserted",(is_tape_inserted() ? 'X' : ' '));

		menu_add_item_menu_format(array_menu_tape_settings,MENU_OPCION_NORMAL,menu_tape_browser,menu_tape_input_insert_cond,"Tape ~~Browser");
		menu_add_item_menu_shortcut(array_menu_tape_settings,'b');
		menu_add_item_menu_tooltip(array_menu_tape_settings,"Browse Input tape");
		menu_add_item_menu_ayuda(array_menu_tape_settings,"Browse Input tape");


		menu_add_item_menu(array_menu_tape_settings,"",MENU_OPCION_SEPARADOR,NULL,NULL);


        menu_tape_settings_trunc_name(tape_out_file,string_tape_save_shown,20);
		menu_add_item_menu_format(array_menu_tape_settings,MENU_OPCION_NORMAL,menu_tape_out_open,NULL,"~~Output [%s]",string_tape_save_shown);
		menu_add_item_menu_shortcut(array_menu_tape_settings,'o');

        //sprintf (string_tape_save_inserted,"[%c] Output tape inserted",((tape_loadsave_inserted & TAPE_SAVE_INSERTED)!=0 ? 'X' : ' '));
        //menu_add_item_menu(array_menu_tape_settings,string_tape_save_inserted,MENU_OPCION_NORMAL,menu_tape_output_insert,menu_tape_output_insert_cond);

        menu_add_item_menu_format(array_menu_tape_settings,MENU_OPCION_NORMAL,menu_tape_output_insert,menu_tape_output_insert_cond,
            "[%c] Output tape inserted",((tape_loadsave_inserted & TAPE_SAVE_INSERTED)!=0 ? 'X' : ' '));

		menu_add_item_menu_format(array_menu_tape_settings,MENU_OPCION_NORMAL,menu_tape_browser_output,menu_tape_output_insert_cond,"Tape B~~rowser");
		menu_add_item_menu_shortcut(array_menu_tape_settings,'r');
		menu_add_item_menu_tooltip(array_menu_tape_settings,"Browse Output tape");
		menu_add_item_menu_ayuda(array_menu_tape_settings,"Browse Output tape");				


        menu_add_item_menu(array_menu_tape_settings,"",MENU_OPCION_SEPARADOR,NULL,NULL);


		menu_add_item_menu_en_es_ca(array_menu_tape_settings,MENU_OPCION_NORMAL,NULL,NULL,
            "--Input Real Tape--","--Cinta Real de Entrada--","--Cinta Real d'Entrada--");
		menu_add_item_menu_tooltip(array_menu_tape_settings,"Input Real Tape at normal loading Speed");
		menu_add_item_menu_ayuda(array_menu_tape_settings,"You may select any input valid tape: o, p, tap, tzx, rwa, wav, smp. "
					"This tape is handled the same way as the real machine does, at normal loading speed, and may "
					"select tapes with different loading methods instead of the ROM: turbo loading, alkatraz, etc...\n"
					"When inserted real tape, realvideo is enabled, only to show real loading stripes on screen, but it is "
					"not necessary, you may disable realvideo if you want");


        menu_tape_settings_trunc_name(realtape_name,string_realtape_shown,23);
        menu_add_item_menu_en_es_ca(array_menu_tape_settings,MENU_OPCION_NORMAL,menu_realtape_open,NULL,
            "~~File","~~Fichero","~~Fitxer");
        menu_add_item_menu_sufijo_format(array_menu_tape_settings," [%s]",string_realtape_shown);
		menu_add_item_menu_shortcut(array_menu_tape_settings,'f');
		menu_add_item_menu_tooltip(array_menu_tape_settings,"Audio file to use as the input audio");
		menu_add_item_menu_ayuda(array_menu_tape_settings,"Audio file to use as the input audio");


		menu_add_item_menu_en_es_ca(array_menu_tape_settings,MENU_OPCION_NORMAL,menu_realtape_insert,menu_realtape_cond,
            "Inserted","Insertado","Insertat");
        menu_add_item_menu_prefijo_format(array_menu_tape_settings,"[%c] ", (realtape_inserted.v==1 ? 'X' : ' '));
		menu_add_item_menu_tooltip(array_menu_tape_settings,"Insert the audio file");
		menu_add_item_menu_ayuda(array_menu_tape_settings,"Insert the audio file");



		menu_add_item_menu_en_es_ca(array_menu_tape_settings,MENU_OPCION_NORMAL,menu_realtape_pause_unpause,menu_realtape_inserted_cond,
            "~~Playing","Re~~produciendose","Re~~produint-se");
        menu_add_item_menu_prefijo_format(array_menu_tape_settings,"[%c] ", (realtape_playing.v==1 ? 'X' : ' '));
		menu_add_item_menu_shortcut(array_menu_tape_settings,'p');
		menu_add_item_menu_tooltip(array_menu_tape_settings,"Start playing the audio tape");
		menu_add_item_menu_ayuda(array_menu_tape_settings,"Start playing the audio tape");

		menu_add_item_menu_format(array_menu_tape_settings,MENU_OPCION_NORMAL,menu_tape_browser_real,menu_realtape_cond,"Tape Bro~~wser");
		menu_add_item_menu_shortcut(array_menu_tape_settings,'w');
		menu_add_item_menu_tooltip(array_menu_tape_settings,"Browse Real tape");
		menu_add_item_menu_ayuda(array_menu_tape_settings,"Browse Real tape");				

        menu_add_item_menu_en_es_ca(array_menu_tape_settings,MENU_OPCION_NORMAL,menu_visual_realtape,NULL,
            "~~Visual Real Tape","Cinta Real ~~Visual","Cinta Real ~~Visual");
        menu_add_item_menu_shortcut(array_menu_tape_settings,'v');
        menu_add_item_menu_tooltip(array_menu_tape_settings,"See an audio render of your tape, see tape blocks and rewind or move forward the cassette player");
        menu_add_item_menu_ayuda(array_menu_tape_settings,"See an audio render of your tape, see tape blocks and rewind or move forward the cassette player");

        menu_add_item_menu(array_menu_tape_settings,"",MENU_OPCION_SEPARADOR,NULL,NULL);


		menu_add_ESC_item(array_menu_tape_settings);

        retorno_menu=menu_dibuja_menu(&storage_tape_opcion_seleccionada,&item_seleccionado,array_menu_tape_settings,"Tape" );

                

		if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
			//llamamos por valor de funcion
            if (item_seleccionado.menu_funcion!=NULL) {
                    //printf ("actuamos por funcion\n");
                    item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
        
            }
		}

	} while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);


}



int menu_tape_settings_cond(void)
{
	return !(MACHINE_IS_Z88);
}




void menu_timexcart_load(MENU_ITEM_PARAMETERS)
{

        char *filtros[2];

        filtros[0]="dck";

        filtros[1]=0;



        //guardamos directorio actual
        char directorio_actual[PATH_MAX];
        getcwd(directorio_actual,PATH_MAX);

        //Obtenemos directorio de ultimo archivo
        //si no hay directorio, vamos a rutas predefinidas
        if (last_timex_cart[0]==0) menu_chdir_sharedfiles();

        else {
                char directorio[PATH_MAX];
                util_get_dir(last_timex_cart,directorio);
                //printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

                //cambiamos a ese directorio, siempre que no sea nulo
                if (directorio[0]!=0) {
                        debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
                        zvfs_chdir(directorio);
                }
        }


        int ret;

        ret=menu_filesel("Select Cartridge",filtros,last_timex_cart);
        //volvemos a directorio inicial
		zvfs_chdir(directorio_actual);


        if (ret==1) {
		//                sprintf (last_timex_cart,"%s",timexcart_load_file);

                //sin overlay de texto, que queremos ver las franjas de carga con el color normal (no apagado)
                reset_menu_overlay_function();


                        timex_insert_dck_cartridge(last_timex_cart);

                //restauramos modo normal de texto de menu
                set_menu_overlay_function(normal_overlay_texto_menu);

                //Y salimos de todos los menus
                salir_todos_menus=1;
        }


}


void menu_timexcart_eject(MENU_ITEM_PARAMETERS)
{
	timex_empty_dock_space();
	menu_generic_message("Eject Cartridge","OK. Cartridge ejected");
}

void menu_dandanator_rom_file(MENU_ITEM_PARAMETERS)
{
	dandanator_disable();

    char *filtros[2];

    filtros[0]="rom";
    filtros[1]=0;

    //guardamos directorio actual
    char directorio_actual[PATH_MAX];
    getcwd(directorio_actual,PATH_MAX);	

	//Obtenemos ultimo directorio visitado
	if (dandanator_rom_file_name[0]!=0) {
		char directorio[PATH_MAX];
		util_get_dir(dandanator_rom_file_name,directorio);
		//printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

		//cambiamos a ese directorio, siempre que no sea nulo
		if (directorio[0]!=0) {
				debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
				zvfs_chdir(directorio);
		}
	}    

    int ret;

    ret=menu_filesel("Select dandanator File",filtros,dandanator_rom_file_name);

    //volvemos a directorio inicial
    zvfs_chdir(directorio_actual);	    


    if (ret==1) {
        if (!si_existe_archivo(dandanator_rom_file_name)) {
            menu_error_message("File does not exist");
            dandanator_rom_file_name[0]=0;
            return;
        }

        else {
            //Comprobar aqui tambien el tamanyo
            long int size=get_file_size(dandanator_rom_file_name);
            if (size!=DANDANATOR_SIZE) {
                menu_error_message("ROM file must be 512 KB length");
                dandanator_rom_file_name[0]=0;
                return;
            }
        }


    }
    //Sale con ESC
    else {
        //Quitar nombre
        dandanator_rom_file_name[0]=0;


    }

}

int menu_storage_dandanator_emulation_cond(void)
{
	if (dandanator_rom_file_name[0]==0) return 0;
        return 1;
}

int menu_storage_dandanator_press_button_cond(void)
{
	return dandanator_enabled.v;
}


void menu_storage_dandanator_emulation(MENU_ITEM_PARAMETERS)
{
	if (dandanator_enabled.v) dandanator_disable();
	else dandanator_enable();
}

void menu_storage_dandanator_press_button(MENU_ITEM_PARAMETERS)
{
	dandanator_press_button();
	//Y salimos de todos los menus
	salir_todos_menus=1;

}

void menu_dandanator(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_dandanator;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

                char string_dandanator_file_shown[13];


                        menu_tape_settings_trunc_name(dandanator_rom_file_name,string_dandanator_file_shown,13);
                        menu_add_item_menu_inicial_format(&array_menu_dandanator,MENU_OPCION_NORMAL,menu_dandanator_rom_file,NULL,"~~ROM File [%s]",string_dandanator_file_shown);
                        menu_add_item_menu_shortcut(array_menu_dandanator,'r');
                        menu_add_item_menu_tooltip(array_menu_dandanator,"ROM Emulation file");
                        menu_add_item_menu_ayuda(array_menu_dandanator,"ROM Emulation file");


                        menu_add_item_menu_format(array_menu_dandanator,MENU_OPCION_NORMAL,menu_storage_dandanator_emulation,menu_storage_dandanator_emulation_cond,"[%c] Dandanator ~~Enabled", (dandanator_enabled.v ? 'X' : ' '));
                        menu_add_item_menu_shortcut(array_menu_dandanator,'e');
                        menu_add_item_menu_tooltip(array_menu_dandanator,"Enable dandanator");
                        menu_add_item_menu_ayuda(array_menu_dandanator,"Enable dandanator");


			menu_add_item_menu_format(array_menu_dandanator,MENU_OPCION_NORMAL,menu_storage_dandanator_press_button,menu_storage_dandanator_press_button_cond,"~~Press button");
			menu_add_item_menu_shortcut(array_menu_dandanator,'p');
                        menu_add_item_menu_tooltip(array_menu_dandanator,"Press button");
                        menu_add_item_menu_ayuda(array_menu_dandanator,"Press button");


                                menu_add_item_menu(array_menu_dandanator,"",MENU_OPCION_SEPARADOR,NULL,NULL);

                menu_add_ESC_item(array_menu_dandanator);

				char titulo_menu[32];
				if (MACHINE_IS_SPECTRUM) strcpy(titulo_menu,"ZX Dandanator");
				else strcpy(titulo_menu,"CPC Dandanator");

                retorno_menu=menu_dibuja_menu(&dandanator_opcion_seleccionada,&item_seleccionado,array_menu_dandanator,titulo_menu);

                
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




}



void menu_kartusho_rom_file(MENU_ITEM_PARAMETERS)
{
	kartusho_disable();

        char *filtros[2];

        filtros[0]="rom";
        filtros[1]=0;


        if (menu_filesel("Select kartusho File",filtros,kartusho_rom_file_name)==1) {
                if (!si_existe_archivo(kartusho_rom_file_name)) {
                        menu_error_message("File does not exist");
                        kartusho_rom_file_name[0]=0;
                        return;



                }

                else {
                        //Comprobar aqui tambien el tamanyo
                        long int size=get_file_size(kartusho_rom_file_name);
                        if (size!=KARTUSHO_SIZE) {
                                menu_error_message("ROM file must be 512 KB length");
                                kartusho_rom_file_name[0]=0;
                                return;
                        }
                }


        }
        //Sale con ESC
        else {
                //Quitar nombre
                kartusho_rom_file_name[0]=0;


        }

}

int menu_storage_kartusho_emulation_cond(void)
{
	if (kartusho_rom_file_name[0]==0) return 0;
        return 1;
}

int menu_storage_kartusho_press_button_cond(void)
{
	return kartusho_enabled.v;
}


void menu_storage_kartusho_emulation(MENU_ITEM_PARAMETERS)
{
	if (kartusho_enabled.v) kartusho_disable();
	else kartusho_enable();
}

void menu_storage_kartusho_press_button(MENU_ITEM_PARAMETERS)
{
	kartusho_press_button();
	//Y salimos de todos los menus
	salir_todos_menus=1;

}

void menu_kartusho(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_kartusho;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

                char string_kartusho_file_shown[13];


                        menu_tape_settings_trunc_name(kartusho_rom_file_name,string_kartusho_file_shown,13);
                        menu_add_item_menu_inicial_format(&array_menu_kartusho,MENU_OPCION_NORMAL,menu_kartusho_rom_file,NULL,"~~ROM File [%s]",string_kartusho_file_shown);
                        menu_add_item_menu_shortcut(array_menu_kartusho,'r');
                        menu_add_item_menu_tooltip(array_menu_kartusho,"ROM Emulation file");
                        menu_add_item_menu_ayuda(array_menu_kartusho,"ROM Emulation file");


                        			menu_add_item_menu_format(array_menu_kartusho,MENU_OPCION_NORMAL,menu_storage_kartusho_emulation,menu_storage_kartusho_emulation_cond,"[%c] ~~Kartusho Enabled", (kartusho_enabled.v ? 'X' : ' '));
                        menu_add_item_menu_shortcut(array_menu_kartusho,'k');
                        menu_add_item_menu_tooltip(array_menu_kartusho,"Enable kartusho");
                        menu_add_item_menu_ayuda(array_menu_kartusho,"Enable kartusho");


			menu_add_item_menu_format(array_menu_kartusho,MENU_OPCION_NORMAL,menu_storage_kartusho_press_button,menu_storage_kartusho_press_button_cond,"~~Press button");
			menu_add_item_menu_shortcut(array_menu_kartusho,'p');
                        menu_add_item_menu_tooltip(array_menu_kartusho,"Press button");
                        menu_add_item_menu_ayuda(array_menu_kartusho,"Press button");


                                menu_add_item_menu(array_menu_kartusho,"",MENU_OPCION_SEPARADOR,NULL,NULL);

                menu_add_ESC_item(array_menu_kartusho);

                retorno_menu=menu_dibuja_menu(&kartusho_opcion_seleccionada,&item_seleccionado,array_menu_kartusho,"Kartusho" );

                
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




}

void menu_samram_rom_file(MENU_ITEM_PARAMETERS)
{
	samram_disable();

        char *filtros[2];

        filtros[0]="rom";
        filtros[1]=0;


        if (menu_filesel("Select ROM File",filtros,samram_rom_file_name)==1) {
                if (!si_existe_archivo(samram_rom_file_name)) {
                        menu_error_message("File does not exist");
                        samram_rom_file_name[0]=0;
                        return;



                }

                else {
                        //Comprobar aqui tambien el tamanyo
                        long int size=get_file_size(samram_rom_file_name);
                        if (size!=32768)  {
                                menu_error_message("ROM file must be 32 KB length");
                                samram_rom_file_name[0]=0;
                                return;
                        }
                }


        }
        //Sale con ESC
        else {
                //Quitar nombre
                samram_rom_file_name[0]=0;


        }

}

int menu_storage_samram_emulation_cond(void)
{
	if (samram_rom_file_name[0]==0) return 0;
        return 1;
}

/*
int menu_storage_samram_press_button_cond(void)
{
	return samram_enabled.v;
}
*/


void menu_storage_samram_emulation(MENU_ITEM_PARAMETERS)
{
	if (samram_enabled.v) samram_disable();
	else samram_enable();
}

/*
void menu_storage_samram_press_button(MENU_ITEM_PARAMETERS)
{
	samram_press_button();
	//Y salimos de todos los menus
	salir_todos_menus=1;

}
*/

void menu_samram(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_samram;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

                char string_samram_file_shown[13];


                        menu_tape_settings_trunc_name(samram_rom_file_name,string_samram_file_shown,13);
                        menu_add_item_menu_inicial_format(&array_menu_samram,MENU_OPCION_NORMAL,menu_samram_rom_file,NULL,"~~ROM File [%s]",string_samram_file_shown);
                        menu_add_item_menu_shortcut(array_menu_samram,'r');
                        menu_add_item_menu_tooltip(array_menu_samram,"ROM Emulation file");
                        menu_add_item_menu_ayuda(array_menu_samram,"ROM Emulation file");


                        			menu_add_item_menu_format(array_menu_samram,MENU_OPCION_NORMAL,menu_storage_samram_emulation,menu_storage_samram_emulation_cond,"[%c] ~~Samram Enabled", (samram_enabled.v ? 'X' : ' '));
                        menu_add_item_menu_shortcut(array_menu_samram,'s');
                        menu_add_item_menu_tooltip(array_menu_samram,"Enable samram");
                        menu_add_item_menu_ayuda(array_menu_samram,"Enable samram");


            /*
			menu_add_item_menu_format(array_menu_samram,MENU_OPCION_NORMAL,menu_storage_samram_press_button,menu_storage_samram_press_button_cond,"~~Press button");
			menu_add_item_menu_shortcut(array_menu_samram,'p');
                        menu_add_item_menu_tooltip(array_menu_samram,"Press button");
                        menu_add_item_menu_ayuda(array_menu_samram,"Press button");
            */

                                menu_add_item_menu(array_menu_samram,"",MENU_OPCION_SEPARADOR,NULL,NULL);

                menu_add_ESC_item(array_menu_samram);

                retorno_menu=menu_dibuja_menu(&samram_opcion_seleccionada,&item_seleccionado,array_menu_samram,"Samram" );

                
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




}


void menu_ifrom_rom_file(MENU_ITEM_PARAMETERS)
{
	ifrom_disable();

        char *filtros[2];

        filtros[0]="rom";
        filtros[1]=0;


        if (menu_filesel("Select ifrom File",filtros,ifrom_rom_file_name)==1) {
                if (!si_existe_archivo(ifrom_rom_file_name)) {
                        menu_error_message("File does not exist");
                        ifrom_rom_file_name[0]=0;
                        return;



                }

                else {
                        //Comprobar aqui tambien el tamanyo
                        long int size=get_file_size(ifrom_rom_file_name);
                        if (size!=IFROM_SIZE) {
                                menu_error_message("ROM file must be 512 KB length");
                                ifrom_rom_file_name[0]=0;
                                return;
                        }
                }


        }
        //Sale con ESC
        else {
                //Quitar nombre
                ifrom_rom_file_name[0]=0;


        }

}

int menu_storage_ifrom_emulation_cond(void)
{
	if (ifrom_rom_file_name[0]==0) return 0;
        return 1;
}

int menu_storage_ifrom_press_button_cond(void)
{
	return ifrom_enabled.v;
}


void menu_storage_ifrom_emulation(MENU_ITEM_PARAMETERS)
{
	if (ifrom_enabled.v) ifrom_disable();
	else ifrom_enable();
}

void menu_storage_ifrom_press_button(MENU_ITEM_PARAMETERS)
{
	ifrom_press_button();
	//Y salimos de todos los menus
	salir_todos_menus=1;

}

void menu_ifrom(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_ifrom;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

                char string_ifrom_file_shown[13];


                        menu_tape_settings_trunc_name(ifrom_rom_file_name,string_ifrom_file_shown,13);
                        menu_add_item_menu_inicial_format(&array_menu_ifrom,MENU_OPCION_NORMAL,menu_ifrom_rom_file,NULL,"~~ROM File [%s]",string_ifrom_file_shown);
                        menu_add_item_menu_shortcut(array_menu_ifrom,'r');
                        menu_add_item_menu_tooltip(array_menu_ifrom,"ROM Emulation file");
                        menu_add_item_menu_ayuda(array_menu_ifrom,"ROM Emulation file");


                        			menu_add_item_menu_format(array_menu_ifrom,MENU_OPCION_NORMAL,menu_storage_ifrom_emulation,menu_storage_ifrom_emulation_cond,"[%c] ~~iFrom Enabled", (ifrom_enabled.v ? 'X' : ' '));
                        menu_add_item_menu_shortcut(array_menu_ifrom,'i');
                        menu_add_item_menu_tooltip(array_menu_ifrom,"Enable ifrom");
                        menu_add_item_menu_ayuda(array_menu_ifrom,"Enable ifrom");


			menu_add_item_menu_format(array_menu_ifrom,MENU_OPCION_NORMAL,menu_storage_ifrom_press_button,menu_storage_ifrom_press_button_cond,"~~Press button");
			menu_add_item_menu_shortcut(array_menu_ifrom,'p');
                        menu_add_item_menu_tooltip(array_menu_ifrom,"Press button");
                        menu_add_item_menu_ayuda(array_menu_ifrom,"Press button");


                                menu_add_item_menu(array_menu_ifrom,"",MENU_OPCION_SEPARADOR,NULL,NULL);

                menu_add_ESC_item(array_menu_ifrom);

                retorno_menu=menu_dibuja_menu(&ifrom_opcion_seleccionada,&item_seleccionado,array_menu_ifrom,"iFrom" );


                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);

                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




}


/*
void menu_storage_hilow_press_button(MENU_ITEM_PARAMETERS)
{
	hilow_press_button();
	//Y salimos de todos los menus
	salir_todos_menus=1;

}*/

int menu_storage_hilow_press_button_cond(void)
{
	return hilow_enabled.v;
}


void menu_storage_hilow_emulation(MENU_ITEM_PARAMETERS)
{
	if (hilow_enabled.v) hilow_disable();
	else hilow_enable();
}

void menu_storage_hilow_insert(MENU_ITEM_PARAMETERS)
{
    hilow_cinta_insertada.v ^=1;
}

void menu_storage_hilow_cover(MENU_ITEM_PARAMETERS)
{
    hilow_tapa_abierta.v ^=1;
}

void menu_hilow(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_hilow;
        menu_item item_seleccionado;
        int retorno_menu;
        do {


            menu_add_item_menu_inicial_format(&array_menu_hilow,MENU_OPCION_NORMAL,menu_storage_hilow_emulation,NULL,"[%c] ~~Hilow Enabled", (hilow_enabled.v ? 'X' : ' '));
            menu_add_item_menu_shortcut(array_menu_hilow,'h');
            menu_add_item_menu_tooltip(array_menu_hilow,"Enable hilow");
            menu_add_item_menu_ayuda(array_menu_hilow,"Enable hilow");

            menu_add_item_menu_format(array_menu_hilow,MENU_OPCION_NORMAL,menu_storage_hilow_insert,NULL,"[%c] Tape ~~inserted", (hilow_cinta_insertada.v ? 'X' : ' '));
            menu_add_item_menu_shortcut(array_menu_hilow,'i');

            menu_add_item_menu_format(array_menu_hilow,MENU_OPCION_NORMAL,menu_storage_hilow_cover,NULL,"[%c] Cover ~~open", (hilow_tapa_abierta.v ? 'X' : ' '));
            menu_add_item_menu_shortcut(array_menu_hilow,'o');            

/*
			menu_add_item_menu_format(array_menu_hilow,MENU_OPCION_NORMAL,menu_storage_hilow_press_button,menu_storage_hilow_press_button_cond,"~~Press button");
			menu_add_item_menu_shortcut(array_menu_hilow,'p');
                        menu_add_item_menu_tooltip(array_menu_hilow,"Press button");
                        menu_add_item_menu_ayuda(array_menu_hilow,"Press button");
*/


                                menu_add_item_menu(array_menu_hilow,"",MENU_OPCION_SEPARADOR,NULL,NULL);

                menu_add_ESC_item(array_menu_hilow);

                retorno_menu=menu_dibuja_menu(&hilow_opcion_seleccionada,&item_seleccionado,array_menu_hilow,"Hilow" );


                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);

                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




}


void menu_storage_betadisk_emulation(MENU_ITEM_PARAMETERS)
{
	if (betadisk_enabled.v) betadisk_disable();
	else betadisk_enable();
}

void menu_storage_betadisk_allow_boot(MENU_ITEM_PARAMETERS)
{
	betadisk_allow_boot_48k.v ^=1;
}


void menu_storage_trd_emulation(MENU_ITEM_PARAMETERS)
{
	if (trd_enabled.v) trd_disable();
	else trd_enable();
}

void menu_storage_trd_write_protect(MENU_ITEM_PARAMETERS)
{
	trd_write_protection.v ^=1;
}

int menu_storage_trd_emulation_cond(void)
{
        if (trd_file_name[0]==0) return 0;
        else return 1;
}


void menu_storage_trd_file(MENU_ITEM_PARAMETERS)
{

	trd_disable();

        char *filtros[2];

        filtros[0]="trd";
        filtros[1]=0;

        //guardamos directorio actual
        char directorio_actual[PATH_MAX];
        getcwd(directorio_actual,PATH_MAX);

              //Obtenemos directorio de trd
        //si no hay directorio, vamos a rutas predefinidas
        if (trd_file_name[0]==0) menu_chdir_sharedfiles();

        else {
                char directorio[PATH_MAX];
                util_get_dir(trd_file_name,directorio);
                //printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

                //cambiamos a ese directorio, siempre que no sea nulo
                if (directorio[0]!=0) {
                        debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
                        zvfs_chdir(directorio);
                }
        }


        int ret=menu_filesel("Select TRD File",filtros,trd_file_name);
        //volvemos a directorio inicial
        zvfs_chdir(directorio_actual);

        if (ret==1) {
		if (!si_existe_archivo(trd_file_name)) {
			if (menu_confirm_yesno_texto("File does not exist","Create?")==0) {
                                trd_file_name[0]=0;
                                return;
                        }


			//Crear archivo vacio
		        FILE *ptr_trdfile;
			ptr_trdfile=fopen(trd_file_name,"wb");

		        long int totalsize=640*1024;
			
			z80_byte valor_grabar=0;

		        if (ptr_trdfile!=NULL) {
				while (totalsize) {
					fwrite(&valor_grabar,1,1,ptr_trdfile);
					totalsize--;
				}
		                fclose(ptr_trdfile);
		        }

		}

		trd_enable();
		


        }
        //Sale con ESC
        else {
                //Quitar nombre
                trd_file_name[0]=0;


        }
}


void menu_storage_trd_browser(MENU_ITEM_PARAMETERS)
{
	//menu_file_trd_browser_show(trd_file_name,"TRD");
	menu_file_viewer_read_file("TRD file viewer",trd_file_name);
}


void menu_storage_trd_persistent_writes(MENU_ITEM_PARAMETERS)
{
	trd_persistent_writes.v ^=1;
}


void menu_betadisk(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_betadisk;
        menu_item item_seleccionado;
        int retorno_menu;
        do {




        	char string_trd_file_shown[17];
						

menu_tape_settings_trunc_name(trd_file_name,string_trd_file_shown,17);
                        menu_add_item_menu_inicial_format(&array_menu_betadisk,MENU_OPCION_NORMAL,menu_storage_trd_file,NULL,"~~TRD File [%s]",string_trd_file_shown);
                        menu_add_item_menu_shortcut(array_menu_betadisk,'t');
                        menu_add_item_menu_tooltip(array_menu_betadisk,"TRD Emulation file");
                        menu_add_item_menu_ayuda(array_menu_betadisk,"TRD Emulation file");


                        menu_add_item_menu_format(array_menu_betadisk,MENU_OPCION_NORMAL,menu_storage_trd_emulation,menu_storage_trd_emulation_cond,"[%c] TRD ~~Emulation", (trd_enabled.v ? 'X' : ' '));
                        menu_add_item_menu_shortcut(array_menu_betadisk,'e');
                        menu_add_item_menu_tooltip(array_menu_betadisk,"TRD Emulation");
                        menu_add_item_menu_ayuda(array_menu_betadisk,"TRD Emulation");


			menu_add_item_menu_format(array_menu_betadisk,MENU_OPCION_NORMAL,menu_storage_trd_write_protect,NULL,"[%c] ~~Write protect", (trd_write_protection.v ? 'X' : ' '));
			menu_add_item_menu_shortcut(array_menu_betadisk,'w');
                        menu_add_item_menu_tooltip(array_menu_betadisk,"If TRD disk is write protected");
                        menu_add_item_menu_ayuda(array_menu_betadisk,"If TRD disk is write protected");


                        menu_add_item_menu_format(array_menu_betadisk,MENU_OPCION_NORMAL,menu_storage_trd_persistent_writes,NULL,"[%c] Persistent Writes",(trd_persistent_writes.v ? 'X' : ' ') );
			menu_add_item_menu_tooltip(array_menu_betadisk,"Tells if TRD writes are saved to disk");
			menu_add_item_menu_ayuda(array_menu_betadisk,"Tells if TRD writes are saved to disk. "
			"Note: all writing operations to TRD are always saved to internal memory (unless you disable write permission), but this setting "
			"tells if these changes are written to disk or not."
			);



                        menu_add_item_menu_format(array_menu_betadisk,MENU_OPCION_NORMAL,menu_storage_trd_browser,menu_storage_trd_emulation_cond,"TRD ~~Viewer");
                        menu_add_item_menu_shortcut(array_menu_betadisk,'v');
                        menu_add_item_menu_tooltip(array_menu_betadisk,"TRD Viewer");
                        menu_add_item_menu_ayuda(array_menu_betadisk,"TRD Viewer");



                        menu_add_item_menu(array_menu_betadisk,"",MENU_OPCION_SEPARADOR,NULL,NULL);


                        menu_add_item_menu_format(array_menu_betadisk,MENU_OPCION_NORMAL,menu_storage_betadisk_emulation,NULL,"[%c] Betadis~~k Enabled", (betadisk_enabled.v ? 'X' : ' '));
                        menu_add_item_menu_shortcut(array_menu_betadisk,'k');
                        menu_add_item_menu_tooltip(array_menu_betadisk,"Enable betadisk");
                        menu_add_item_menu_ayuda(array_menu_betadisk,"Enable betadisk");


			menu_add_item_menu_format(array_menu_betadisk,MENU_OPCION_NORMAL,menu_storage_betadisk_allow_boot,NULL,"[%c] ~~Allow Boot", (betadisk_allow_boot_48k.v ? 'X' : ' '));
			menu_add_item_menu_shortcut(array_menu_betadisk,'a');
                        menu_add_item_menu_tooltip(array_menu_betadisk,"Allow autoboot on 48k machines");
                        menu_add_item_menu_ayuda(array_menu_betadisk,"Allow autoboot on 48k machines");

                        


                        
                                menu_add_item_menu(array_menu_betadisk,"",MENU_OPCION_SEPARADOR,NULL,NULL);

                menu_add_ESC_item(array_menu_betadisk);

                retorno_menu=menu_dibuja_menu(&betadisk_opcion_seleccionada,&item_seleccionado,array_menu_betadisk,"Betadisk" );

                
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




}


void menu_superupgrade_rom_file(MENU_ITEM_PARAMETERS)
{
        superupgrade_disable();

        char *filtros[2];

        filtros[0]="flash";
        filtros[1]=0;


        if (menu_filesel("Select Superupgrade File",filtros,superupgrade_rom_file_name)==1) {
                if (!si_existe_archivo(superupgrade_rom_file_name)) {
                        menu_error_message("File does not exist");
                        superupgrade_rom_file_name[0]=0;
                        return;



                }

                else {
                        //Comprobar aqui tambien el tamanyo
                        long int size=get_file_size(superupgrade_rom_file_name);
                        if (size!=SUPERUPGRADE_ROM_SIZE) {
                                menu_error_message("Flash file must be 512 KB length");
                                superupgrade_rom_file_name[0]=0;
                                return;
                        }
                }


        }
        //Sale con ESC
        else {
                //Quitar nombre
                superupgrade_rom_file_name[0]=0;

        }

}

int menu_storage_superupgrade_emulation_cond(void)
{
        if (superupgrade_rom_file_name[0]==0) return 0;
        return 1;
}


void menu_storage_superupgrade_emulation(MENU_ITEM_PARAMETERS)
{
        if (superupgrade_enabled.v) superupgrade_disable();
        else superupgrade_enable(1);
}

void menu_storage_superupgrade_internal_rom(MENU_ITEM_PARAMETERS)
{
		//superupgrade_puerto_43b ^=0x20;
		//if ( (superupgrade_puerto_43b & (32+64))==32) return 1;

		superupgrade_puerto_43b &=(255-32-64);
		superupgrade_puerto_43b |=32;
}



void menu_superupgrade(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_superupgrade;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

                char string_superupgrade_file_shown[13];


                        menu_tape_settings_trunc_name(superupgrade_rom_file_name,string_superupgrade_file_shown,13);
                        menu_add_item_menu_inicial_format(&array_menu_superupgrade,MENU_OPCION_NORMAL,menu_superupgrade_rom_file,NULL,"~~Flash File [%s]",string_superupgrade_file_shown);
                        menu_add_item_menu_shortcut(array_menu_superupgrade,'f');
                        menu_add_item_menu_tooltip(array_menu_superupgrade,"Flash Emulation file");
                        menu_add_item_menu_ayuda(array_menu_superupgrade,"Flash Emulation file");


                        menu_add_item_menu_format(array_menu_superupgrade,MENU_OPCION_NORMAL,menu_storage_superupgrade_emulation,menu_storage_superupgrade_emulation_cond,"[%c] ~~Superupgrade Enabled", (superupgrade_enabled.v ? 'X' : ' '));
                        menu_add_item_menu_shortcut(array_menu_superupgrade,'s');
                        menu_add_item_menu_tooltip(array_menu_superupgrade,"Enable superupgrade");
                        menu_add_item_menu_ayuda(array_menu_superupgrade,"Enable superupgrade");


												menu_add_item_menu_format(array_menu_superupgrade,MENU_OPCION_NORMAL,menu_storage_superupgrade_internal_rom,menu_storage_superupgrade_emulation_cond,"[%c] Show ~~internal ROM", (si_superupgrade_muestra_rom_interna() ? 'X' : ' '));
												menu_add_item_menu_shortcut(array_menu_superupgrade,'i');
												menu_add_item_menu_tooltip(array_menu_superupgrade,"Show internal ROM instead of Superupgrade flash");
												menu_add_item_menu_ayuda(array_menu_superupgrade,"Show internal ROM instead of Superupgrade flash");



                                menu_add_item_menu(array_menu_superupgrade,"",MENU_OPCION_SEPARADOR,NULL,NULL);

                menu_add_ESC_item(array_menu_superupgrade);


retorno_menu=menu_dibuja_menu(&superupgrade_opcion_seleccionada,&item_seleccionado,array_menu_superupgrade,"Superupgrade" );

                
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




}




void menu_if1_settings(MENU_ITEM_PARAMETERS)
{
	if (if1_enabled.v==0) enable_if1();
	else disable_if1();
}




void menu_timexcart(MENU_ITEM_PARAMETERS)
{

        menu_item *array_menu_timexcart;
        menu_item item_seleccionado;
        int retorno_menu;

        do {


                menu_add_item_menu_inicial(&array_menu_timexcart,"~~Load Cartridge",MENU_OPCION_NORMAL,menu_timexcart_load,NULL);
                menu_add_item_menu_shortcut(array_menu_timexcart,'l');
                menu_add_item_menu_tooltip(array_menu_timexcart,"Load Timex Cartridge");
                menu_add_item_menu_ayuda(array_menu_timexcart,"Supported timex cartridge formats on load:\n"
                                        "DCK");

                menu_add_item_menu(array_menu_timexcart,"~~Eject Cartridge",MENU_OPCION_NORMAL,menu_timexcart_eject,NULL);
                menu_add_item_menu_shortcut(array_menu_timexcart,'e');
                menu_add_item_menu_tooltip(array_menu_timexcart,"Eject Cartridge");
                menu_add_item_menu_ayuda(array_menu_timexcart,"Eject Cartridge");


     				menu_add_item_menu(array_menu_timexcart,"",MENU_OPCION_SEPARADOR,NULL,NULL);
                menu_add_ESC_item(array_menu_timexcart);

                retorno_menu=menu_dibuja_menu(&timexcart_opcion_seleccionada,&item_seleccionado,array_menu_timexcart,"Timex Cartridge" );

                

                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);

}


void menu_zxuno_spi_persistent_writes(MENU_ITEM_PARAMETERS)
{
	if (zxuno_flash_persistent_writes.v==0) {
           if (menu_confirm_yesno_texto("Will flush prev. changes","Enable?")==1) zxuno_flash_persistent_writes.v=1;

	}

	else zxuno_flash_persistent_writes.v=0;
}

void menu_zxuno_spi_flash_file(MENU_ITEM_PARAMETERS)
{
	char *filtros[2];

        filtros[0]="flash";
        filtros[1]=0;


        if (menu_filesel("Select Flash File",filtros,zxuno_flash_spi_name)==1) {

                //Ver si archivo existe y preguntar
                /*if (si_existe_archivo(zxuno_flash_spi_name) ) {

                        if (menu_confirm_yesno_texto("File exists","Overwrite?")==0) return;

                }
		*/

		if (si_existe_archivo(zxuno_flash_spi_name) ) {

			if (menu_confirm_yesno_texto("File exists","Reload SPI Flash from file?")) {

				//Decir que no hay que hacer flush anteriores
				zxuno_flash_must_flush_to_disk=0;

				//Y sobreescribir ram spi flash con lo que tiene el archivo de disco
				zxuno_load_spi_flash();
			}

		}

		else {

			//Si archivo nuevo,
			//volcar contenido de la memoria flash en ram aqui
			//Suponemos que permisos de escritura estan activos
			zxuno_flash_must_flush_to_disk=1;
		}

        }

	//Sale con ESC
        else {
		//dejar archivo por defecto
		zxuno_flash_spi_name[0]=0;

		//Y por defecto solo lectura
		zxuno_flash_persistent_writes.v=0;

		if (menu_confirm_yesno_texto("Default SPI Flash file","Reload SPI Flash from file?")) {
			zxuno_load_spi_flash();
                }

        }
}



void menu_zxuno_spi_write_protect(MENU_ITEM_PARAMETERS)
{
	zxuno_flash_write_protection.v ^=1;
}



void menu_zxuno_spi_flash(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_zxuno_spi_flash;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

                     char string_spi_flash_file_shown[12]; //,string_mmc_file_shown[13];            
			if (zxuno_flash_spi_name[0]==0) sprintf (string_spi_flash_file_shown,"Default");
			else menu_tape_settings_trunc_name(zxuno_flash_spi_name,string_spi_flash_file_shown,12);

			menu_add_item_menu_inicial_format(&array_menu_zxuno_spi_flash,MENU_OPCION_NORMAL,menu_zxuno_spi_flash_file,NULL,"~~Flash File: [%s]",string_spi_flash_file_shown);
			menu_add_item_menu_shortcut(array_menu_zxuno_spi_flash,'f');
			menu_add_item_menu_tooltip(array_menu_zxuno_spi_flash,"File used for the ZX-Uno SPI Flash");
			menu_add_item_menu_ayuda(array_menu_zxuno_spi_flash,"File used for the ZX-Uno SPI Flash");

			menu_add_item_menu_format(array_menu_zxuno_spi_flash,MENU_OPCION_NORMAL,menu_zxuno_spi_write_protect,NULL,"[%c] ~~Write protect",(zxuno_flash_write_protection.v ? 'X' : ' '));
			menu_add_item_menu_shortcut(array_menu_zxuno_spi_flash,'w');
                        menu_add_item_menu_tooltip(array_menu_zxuno_spi_flash,"If ZX-Uno SPI Flash is write protected");
                        menu_add_item_menu_ayuda(array_menu_zxuno_spi_flash,"If ZX-Uno SPI Flash is write protected");



			menu_add_item_menu_format(array_menu_zxuno_spi_flash,MENU_OPCION_NORMAL,menu_zxuno_spi_persistent_writes,NULL,"[%c] Persistent Writes",(zxuno_flash_persistent_writes.v ? 'X' : ' '));
			menu_add_item_menu_tooltip(array_menu_zxuno_spi_flash,"Tells if ZX-Uno SPI Flash writes are saved to disk");
			menu_add_item_menu_ayuda(array_menu_zxuno_spi_flash,"Tells if ZX-Uno SPI Flash writes are saved to disk. "
			"When you enable it, all previous changes (before enable it and since machine boot) and "
			"future changes made to spi flash will be saved to disk.\n"
			"Note: all writing operations to SPI Flash are always saved to internal memory (unless you disable write permission), but this setting "
			"tells if these changes are written to disk or not.");
							



				menu_add_item_menu(array_menu_zxuno_spi_flash,"",MENU_OPCION_SEPARADOR,NULL,NULL);
                //menu_add_item_menu(array_menu_zxuno_spi_flash,"ESC Back",MENU_OPCION_NORMAL|MENU_OPCION_ESC,NULL,NULL);
                menu_add_ESC_item(array_menu_zxuno_spi_flash);

                retorno_menu=menu_dibuja_menu(&zxuno_spi_flash_opcion_seleccionada,&item_seleccionado,array_menu_zxuno_spi_flash,"ZX-Uno Flash" );

                
                if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                        //llamamos por valor de funcion
                        if (item_seleccionado.menu_funcion!=NULL) {
                                //printf ("actuamos por funcion\n");
                                item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                                
                        }
                }

        } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);




}




//menu storage 
void menu_storage(MENU_ITEM_PARAMETERS)
{
        menu_item *array_menu_storage;
        menu_item item_seleccionado;
        int retorno_menu;
        do {

                //char string_spi_flash_file_shown[13]; //,string_mmc_file_shown[13];

		 menu_add_item_menu_inicial(&array_menu_storage,"",MENU_OPCION_UNASSIGNED,NULL,NULL);


		if (MACHINE_IS_Z88) {
			menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_z88_slots,NULL,"Z88 Memory ~~Slots");
            menu_add_item_menu_shortcut(array_menu_storage,'s');

            menu_add_item_menu_tooltip(array_menu_storage,"Z88 Memory Slots");
            menu_add_item_menu_ayuda(array_menu_storage,"Selects Memory Slots to use on Z88");
            menu_add_item_menu_tiene_submenu(array_menu_storage);

		}

		else if (MACHINE_IS_QL) {
			menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_ql_mdv_flp,NULL,"Microdrive & Floppy");
            menu_add_item_menu_tiene_submenu(array_menu_storage);
			


		}


		else if (!MACHINE_IS_CHLOE && !MACHINE_IS_COLECO && !MACHINE_IS_SG1000 && !MACHINE_IS_SMS) {
            menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_storage_tape,menu_tape_settings_cond,"~~Tape");
            menu_add_item_menu_shortcut(array_menu_storage,'t');
            menu_add_item_menu_tooltip(array_menu_storage,"Select tape and options");
            menu_add_item_menu_ayuda(array_menu_storage,"Select tape for input (read) or output (write). \n"
                                                        "You use them as real tapes, with BASIC functions like LOAD and SAVE\n"
                                                        "Also select different options to change tape behaviour");
            menu_add_item_menu_tiene_submenu(array_menu_storage);
		}


		if (MACHINE_IS_SPECTRUM_P2A_P3) {
			menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_plusthreedisk,NULL,"+3 ~~Disk");
			menu_add_item_menu_shortcut(array_menu_storage,'d');
			menu_add_item_menu_tooltip(array_menu_storage,"+3 Disk emulation");
			menu_add_item_menu_ayuda(array_menu_storage,"+3 Disk emulation");
            menu_add_item_menu_tiene_submenu(array_menu_storage);
		}


		if (MACHINE_IS_TIMEX_TS2068) {
			menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_timexcart,NULL,"Timex ~~Cartridge");
			menu_add_item_menu_shortcut(array_menu_storage,'c');
			menu_add_item_menu_tooltip(array_menu_storage,"Timex Cartridge Settings");
			menu_add_item_menu_ayuda(array_menu_storage,"Timex Cartridge Settings");
            menu_add_item_menu_tiene_submenu(array_menu_storage);
		}



		if (MACHINE_IS_MSX) {
			menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_msxcart,NULL,"MSX ~~Cartridge");
			menu_add_item_menu_shortcut(array_menu_storage,'c');
			menu_add_item_menu_tooltip(array_menu_storage,"MSX Cartridge Settings");
			menu_add_item_menu_ayuda(array_menu_storage,"MSX Cartridge Settings");
            menu_add_item_menu_tiene_submenu(array_menu_storage);
		}

		if (MACHINE_IS_COLECO) {
			menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_msxcart,NULL,"Coleco ~~Cartridge");
			menu_add_item_menu_shortcut(array_menu_storage,'c');
			menu_add_item_menu_tooltip(array_menu_storage,"Coleco Cartridge Settings");
			menu_add_item_menu_ayuda(array_menu_storage,"Coleco Cartridge Settings");
            menu_add_item_menu_tiene_submenu(array_menu_storage);
		}


		if (MACHINE_IS_SG1000) {
			menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_msxcart,NULL,"SG1000 ~~Cartridge");
			menu_add_item_menu_shortcut(array_menu_storage,'c');
			menu_add_item_menu_tooltip(array_menu_storage,"SG1000 Cartridge Settings");
			menu_add_item_menu_ayuda(array_menu_storage,"SG1000 Cartridge Settings");
            menu_add_item_menu_tiene_submenu(array_menu_storage);
		}

		if (MACHINE_IS_SMS) {
			menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_msxcart,NULL,"SMS ~~Cartridge");
			menu_add_item_menu_shortcut(array_menu_storage,'c');
			menu_add_item_menu_tooltip(array_menu_storage,"SMS Cartridge Settings");
			menu_add_item_menu_ayuda(array_menu_storage,"SMS Cartridge Settings");
            menu_add_item_menu_tiene_submenu(array_menu_storage);
		}        

		if (MACHINE_IS_SVI) {
			menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_msxcart,NULL,"SVI ~~Cartridge");
			menu_add_item_menu_shortcut(array_menu_storage,'c');
			menu_add_item_menu_tooltip(array_menu_storage,"SVI Cartridge Settings");
			menu_add_item_menu_ayuda(array_menu_storage,"SVI Cartridge Settings");
            menu_add_item_menu_tiene_submenu(array_menu_storage);
		}		


		if (MACHINE_IS_SPECTRUM) {
            menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_betadisk,NULL,"~~Betadisk");
            menu_add_item_menu_shortcut(array_menu_storage,'b');
            menu_add_item_menu_tooltip(array_menu_storage,"Betadisk settings");
            menu_add_item_menu_ayuda(array_menu_storage,"Betadisk settings");
            menu_add_item_menu_tiene_submenu(array_menu_storage);
		}

		if (MACHINE_IS_SPECTRUM) {
			menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_esxdos_traps,NULL,"~~ESXDOS Handler");
			menu_add_item_menu_shortcut(array_menu_storage,'e');
			menu_add_item_menu_tooltip(array_menu_storage,"Enables emulator to handle ESXDOS calls");
			menu_add_item_menu_ayuda(array_menu_storage,"Enables emulator to handle ESXDOS calls and "
				"use local files from your computer instead of using from inside the mmc/ide virtual file.\n"
				"You can choose to have also "
				"enabled mmc/ide virtual file or not, you can use one of the settings or both. In case of using both, supported esxdos handler "
				"functions are managed with it; if not, they will be handled by the usual mmc/ide virtual file firmware (usually esxdos).\n"
				"Use with caution, "
				"only some ESXDOS calls are handled, the rest are handled from the mmc/ide virtual file firmware.\n"
				"The list of supported calls are: \n"
				"DISK_INFO, DISK_STATUS, F_CHDIR, F_CLOSE, F_FSTAT, F_GETCWD, F_MKDIR, F_MOUNT, F_OPEN, F_OPENDIR, F_READ, F_READDIR, F_RENAME, F_REWINDDIR, F_SEEK, F_SEEKDIR, F_STAT, F_SYNC, F_TELLDIR, F_UNLINK, F_WRITE, M_DRIVEINFO, M_GETSETDRV"
				"\n"
				"Note: you can also enable and disable ESXDOS handler whenever you want, for example in programs that use unsupported functions for handler."


			);
            menu_add_item_menu_tiene_submenu(array_menu_storage);
		}        

		if (MACHINE_IS_SPECTRUM) {
            menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_hilow,NULL,"~~HiLow");
            menu_add_item_menu_shortcut(array_menu_storage,'h');
            menu_add_item_menu_tooltip(array_menu_storage,"HiLow settings");
            menu_add_item_menu_ayuda(array_menu_storage,"HiLow settings");
            menu_add_item_menu_tiene_submenu(array_menu_storage);
		} 
        

		if (MACHINE_IS_SPECTRUM || MACHINE_IS_SAM) {

            menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_ide_divide,NULL,"~~IDE");
            menu_add_item_menu_shortcut(array_menu_storage,'i');
            menu_add_item_menu_tooltip(array_menu_storage,"IDE, DivIDE and 8-bit simple settings");
            menu_add_item_menu_ayuda(array_menu_storage,"IDE, DivIDE and 8-bit simple settings");
            menu_add_item_menu_tiene_submenu(array_menu_storage);


		}

  

		if (MACHINE_IS_SPECTRUM || MACHINE_IS_CPC) {
            menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_ifrom,NULL,"i~~From");
            menu_add_item_menu_shortcut(array_menu_storage,'f');
            menu_add_item_menu_tooltip(array_menu_storage,"iFrom settings");
            menu_add_item_menu_ayuda(array_menu_storage,"iFrom settings");
            menu_add_item_menu_tiene_submenu(array_menu_storage);
		}        

		if (MACHINE_IS_SPECTRUM || MACHINE_IS_CPC) {
            menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_kartusho,NULL,"~~Kartusho");
            menu_add_item_menu_shortcut(array_menu_storage,'k');
            menu_add_item_menu_tooltip(array_menu_storage,"Kartusho settings");
            menu_add_item_menu_ayuda(array_menu_storage,"Kartusho settings");
            menu_add_item_menu_tiene_submenu(array_menu_storage);
		}        



		if (MACHINE_IS_SPECTRUM) {
			//menu_tape_settings_trunc_name(mmc_file_name,string_mmc_file_shown,13);
			menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_mmc_divmmc,NULL,"~~MMC");
			menu_add_item_menu_shortcut(array_menu_storage,'m');
			menu_add_item_menu_tooltip(array_menu_storage,"MMC, DivMMC and ZXMMC settings");
			menu_add_item_menu_ayuda(array_menu_storage,"MMC, DivMMC and ZXMMC settings");
            menu_add_item_menu_tiene_submenu(array_menu_storage);
		}


	    if (MACHINE_IS_SPECTRUM_48) {
            menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_samram,NULL,"~~Samram");
            menu_add_item_menu_shortcut(array_menu_storage,'s');

            menu_add_item_menu_tooltip(array_menu_storage,"Samram settings");
            menu_add_item_menu_ayuda(array_menu_storage,"Settings for Gerton Lunter Samram emulation.\n"
                    "It's a device that Gerton Lunter created and also was emulated in his own emulator\n"
                    "The original interface has a 32kb of static RAM and also uses 32 kb of the extra shadow unused faulty "
                    "ram of all Spectrum 48kb; in ZEsarUX I emulate it as a 64kb interface"
                    );     
            menu_add_item_menu_tiene_submenu(array_menu_storage);                  
        }


		if (superupgrade_supported_machine() ) {
            menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_superupgrade,NULL,"Speccy Superup~~grade");
            menu_add_item_menu_shortcut(array_menu_storage,'g');
            menu_add_item_menu_tooltip(array_menu_storage,"Superupgrade settings");
            menu_add_item_menu_ayuda(array_menu_storage,"Superupgrade settings");
            menu_add_item_menu_tiene_submenu(array_menu_storage);

		}




        if ( (MACHINE_IS_SPECTRUM || MACHINE_IS_CPC) && !MACHINE_IS_ZXUNO) {

            menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_dandanator,NULL,
                "%s D~~andanator",(MACHINE_IS_SPECTRUM ? "ZX" : "CPC")  );
            menu_add_item_menu_shortcut(array_menu_storage,'a');
            menu_add_item_menu_tooltip(array_menu_storage,"Dandanator settings");
            menu_add_item_menu_ayuda(array_menu_storage,"Dandanator settings");
            menu_add_item_menu_tiene_submenu(array_menu_storage);

        }




		if (MACHINE_IS_ZX8081) {
			menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_zxpand,NULL,"ZX~~pand emulation");
            menu_add_item_menu_shortcut(array_menu_storage,'p');
			menu_add_item_menu_tooltip(array_menu_storage,"ZXpand emulation");
			menu_add_item_menu_ayuda(array_menu_storage,"ZXpand emulation");
            menu_add_item_menu_tiene_submenu(array_menu_storage);

		}


		if (MACHINE_IS_ZXUNO) {
			menu_add_item_menu_format(array_menu_storage,MENU_OPCION_NORMAL,menu_zxuno_spi_flash,NULL,"~~ZX-Uno Flash");
			menu_add_item_menu_shortcut(array_menu_storage,'z');
            menu_add_item_menu_tiene_submenu(array_menu_storage);
		}                  



        menu_add_item_menu(array_menu_storage,"",MENU_OPCION_SEPARADOR,NULL,NULL);
        //menu_add_item_menu(array_menu_storage,"ESC Back",MENU_OPCION_NORMAL|MENU_OPCION_ESC,NULL,NULL);
        menu_add_ESC_item(array_menu_storage);

        retorno_menu=menu_dibuja_menu(&storage_opcion_seleccionada,&item_seleccionado,array_menu_storage,"Storage" );

        
        if ((item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu>=0) {
                //llamamos por valor de funcion
                if (item_seleccionado.menu_funcion!=NULL) {
                        //printf ("actuamos por funcion\n");
                        item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
                        
                }
        }

    } while ( (item_seleccionado.tipo_opcion&MENU_OPCION_ESC)==0 && retorno_menu!=MENU_RETORNO_ESC && !salir_todos_menus);


}




void menu_smartload(MENU_ITEM_PARAMETERS)
{

	menu_first_aid("smartload");

        char *filtros[38];

        filtros[0]="zx";
        filtros[1]="sp";
        filtros[2]="z80";
        filtros[3]="sna";

        filtros[4]="o";
        filtros[5]="p";
        filtros[6]="80";
        filtros[7]="81";
	filtros[8]="z81";

        filtros[9]="tzx";
        filtros[10]="tap";

	filtros[11]="rwa";
	filtros[12]="smp";
	filtros[13]="wav";

	filtros[14]="epr";
	filtros[15]="63";
	filtros[16]="eprom";
	filtros[17]="flash";

	filtros[18]="ace";

	filtros[19]="dck";

	filtros[20]="cdt";

	filtros[21]="ay";

	filtros[22]="scr";

	filtros[23]="rzx";

	filtros[24]="zsf";

	filtros[25]="spg";

	filtros[26]="trd";

	filtros[27]="nex";
	
	filtros[28]="dsk";

	filtros[29]="pzx";

	filtros[30]="rom";

	filtros[31]="col";

	filtros[32]="sg";

	filtros[33]="cas";

    filtros[34]="snx";

    filtros[35]="sms";

    filtros[36]="bin";

	filtros[37]=0;


        //guardamos directorio actual
        char directorio_actual[PATH_MAX];
        getcwd(directorio_actual,PATH_MAX);

        //Obtenemos directorio de snap
        //si no hay directorio, vamos a rutas predefinidas
        if (quickfile==NULL) menu_chdir_sharedfiles();
		else {
                char directorio[PATH_MAX];
                util_get_dir(quickfile,directorio);
                //printf ("strlen directorio: %d directorio: %s\n",strlen(directorio),directorio);

                //cambiamos a ese directorio, siempre que no sea nulo
                if (directorio[0]!=0) {
                        debug_printf (VERBOSE_INFO,"Changing to last directory: %s",directorio);
						//printf ("antes zvfs_chdir\n");
                        zvfs_chdir(directorio);
						//printf ("despues zvfs_chdir\n");
                }

				util_get_file_no_directory(quickfile,menu_filesel_posicionar_archivo_nombre);

				menu_filesel_posicionar_archivo.v=1;

        }






        int ret;

		//printf ("antes menu_filesel\n");

        ret=menu_filesel("Smart load",filtros,quickload_file);

		//printf ("despues menu_filesel\n");

        //volvemos a directorio inicial
		
        zvfs_chdir(directorio_actual);

        if (ret==1) {

			quickfile=quickload_file;

            //sin overlay de texto, que queremos ver las franjas de carga con el color normal (no apagado)
            reset_menu_overlay_function();


			if (quickload(quickload_file)) {
				debug_printf (VERBOSE_ERR,"Unknown file format");
			}

                //restauramos modo normal de texto de menu
                set_menu_overlay_function(normal_overlay_texto_menu);

                //Y salimos de todos los menus si conviene
                if (no_close_menu_after_smartload.v==0) salir_todos_menus=1;
        }

	//printf ("tapefile: %p %s\n",tapefile,tapefile);

}





#define OSD_KEYBOARD_ANCHO_VENTANA 27
#define OSD_KEYBOARD_ALTO_VENTANA 12
#define OSD_KEYBOARD_X_VENTANA (menu_center_x()-OSD_KEYBOARD_ANCHO_VENTANA/2)
#define OSD_KEYBOARD_Y_VENTANA (menu_center_y()-OSD_KEYBOARD_ALTO_VENTANA/2)

struct s_osd_teclas {
    char tecla[5]; //4 de longitud mas 0 final
    int x; //posicion X en pantalla. Normalmente todos van separados dos caracteres excepto Symbol Shift, Enter etc que ocupan mas
    int ancho_tecla; //1 para todas, excepto enter, cap shift, etc
};



typedef struct s_osd_teclas osd_teclas;
/*

01234567890123456789012345

1 2 3 4 5 6 7 8 9 0
 Q W E R T Y U I O P
 A S D F G H J K L ENT
CS Z X C V B N M SS SP
*/

//Primeras 10 teclas son de la primera linea, siguientes 10, siguiente linea, etc
osd_teclas teclas_osd[40]={
    {"1",0,1}, {"2",2,1}, {"3",4,1}, {"4",6,1}, {"5",8,1}, {"6",10,1}, {"7",12,1}, {"8",14,1}, {"9",16,1}, {"0",18,1},
    {"Q",1,1}, {"W",3,1}, {"E",5,1}, {"R",7,1}, {"T",9,1}, {"Y",11,1}, {"U",13,1}, {"I",15,1}, {"O",17,1}, {"P",19,1},
    {"A",1,1}, {"S",3,1}, {"D",5,1}, {"F",7,1}, {"G",9,1}, {"H",11,1}, {"J",13,1}, {"K",15,1}, {"L",17,1}, {"ENT",19,3},
    {"CS",0,2}, {"Z",3,1}, {"X",5,1}, {"C",7,1}, {"V",9,1}, {"B",11,1}, {"N",13,1}, {"M",15,1}, {"SS",17,2}, {"SP",20,2}
};


int osd_keyboard_cursor_x=0; //Vale 0..9
int osd_keyboard_cursor_y=0; //Vale 0..3

int menu_onscreen_keyboard_return_index_cursor(void)
{
	return osd_keyboard_cursor_y*10+osd_keyboard_cursor_x;
}


//Comun para dibujar cursor y senyalar teclas activas
void menu_onscreen_keyboard_dibuja_cursor_aux(zxvision_window *ventana,char *s,int x,int y,int escursor)
{
	char *textocursor;
	char textospeech[32];
	textocursor=s;

        //Parchecillo para ZX80/81
        if (MACHINE_IS_ZX8081) {
		if (!strcmp(s,"SS")) textocursor=".";
		if (!strcmp(s,"ENT")) textocursor="NL";
        }


        //Si es teclas activas, texto inverso. Si es cursor, texto papel de color seleccion no disponible (rojo por defecto)
        if (escursor) {
		//menu_escribe_texto_ventana(x,y,ESTILO_GUI_TINTA_SELECCIONADO,ESTILO_GUI_PAPEL_SELECCIONADO,textocursor);	
		//void zxvision_print_string(zxvision_window *w,int x,int y,int tinta,int papel,int parpadeo,char *texto)
		zxvision_print_string(ventana,x,y,ESTILO_GUI_TINTA_SELECCIONADO,ESTILO_GUI_PAPEL_SELECCIONADO,0,textocursor);
	}

	else {
		//menu_escribe_texto_ventana(x,y,ESTILO_GUI_TINTA_OPCION_MARCADA,ESTILO_GUI_PAPEL_OPCION_MARCADA,textocursor);	
		zxvision_print_string(ventana,x,y,ESTILO_GUI_TINTA_OPCION_MARCADA,ESTILO_GUI_PAPEL_OPCION_MARCADA,0,textocursor);
	}

	

	//Enviar a speech
	string_a_minusculas(textocursor,textospeech);

	//Casos especiales para speech
	if (!strcmp(textospeech,".")) strcpy (textospeech,"dot");
	else if (!strcmp(textospeech,"cs")) strcpy (textospeech,"caps shift");
	else if (!strcmp(textospeech,"ss")) strcpy (textospeech,"symbol shift");
	else if (!strcmp(textospeech,"ent")) strcpy (textospeech,"enter");
	else if (!strcmp(textospeech,"sp")) strcpy (textospeech,"space");

	//Forzar que siempre suene en speech
	menu_speech_tecla_pulsada=0;


	menu_textspeech_send_text(textospeech);
}

void menu_onscreen_keyboard_dibuja_cursor(zxvision_window *ventana)
{


	int offset_x=1;
	int offset_y=1;

	//Calcular posicion del cursor
	int x,y;
	y=osd_keyboard_cursor_y*2;
	//la x hay que buscarla en el array



	int indice=menu_onscreen_keyboard_return_index_cursor();

	//Si en stick
	if (osd_keyboard_cursor_y==4) {
		if (indice==40) menu_onscreen_keyboard_dibuja_cursor_aux(ventana,"Stick",offset_x,offset_y+y,1);
		else menu_onscreen_keyboard_dibuja_cursor_aux(ventana,"Send",offset_x+6,offset_y+y,1);
		return;
	}

	x=teclas_osd[indice].x;

	menu_onscreen_keyboard_dibuja_cursor_aux(ventana,teclas_osd[indice].tecla,offset_x+x,offset_y+y,1);

	



}


//Que teclas se estan pulsando. A 0 no tecla, a 1 tecla
z80_byte menu_osd_teclas_pulsadas[40];

int menu_onscreen_keyboard_sticky=0;


void menu_onscreen_keyboard_dibuja_teclas_activas(zxvision_window *ventana)
{
	int i,x,y;

	int offset_x=1;
	int offset_y=1;


	for (i=0;i<40;i++) {
		y=(i/10)*2;
		if (menu_osd_teclas_pulsadas[i]) {
			x=teclas_osd[i].x;
			menu_onscreen_keyboard_dibuja_cursor_aux(ventana,teclas_osd[i].tecla,offset_x+x,offset_y+y,0);
		}
	}

	if (menu_onscreen_keyboard_sticky) menu_onscreen_keyboard_dibuja_cursor_aux(ventana,"Stick",offset_x,offset_y+(40/10)*2,0);
}

void menu_onscreen_keyboard_reset_pressed_keys(void)
{
	int i;
	for (i=0;i<40;i++) menu_osd_teclas_pulsadas[i]=0;
}

void menu_osd_send_key_text(char *texto_tecla)
{
	//Enviar tecla ascii tal cual, excepto Enter, CS, SS, SP
		if (strlen(texto_tecla)==1) {
			z80_byte tecla=letra_minuscula(texto_tecla[0]);
			debug_printf (VERBOSE_DEBUG,"Sending Ascii key: %c",tecla);
			convert_numeros_letras_puerto_teclado_continue(tecla,1);
		}
		else {
/*
 A S D F G H J K L ENT
CS Z X C V B N M SS SP
*/
			if (!strcmp(texto_tecla,"ENT")) util_set_reset_key(UTIL_KEY_ENTER,1);

			//CS y SS los enviamos asi porque en algunos teclados, util_set_reset_key los gestiona diferente y no queremos

			else if (!strcmp(texto_tecla,"SS")) {
				if (MACHINE_IS_ZX8081) {
					puerto_32766 &=255-2;
				}
				else util_set_reset_key(UTIL_KEY_ALT_L,1);
			}


			else if (!strcmp(texto_tecla,"SP")) util_set_reset_key(UTIL_KEY_SPACE,1);


			//Si estan los flags de CS o SS, activarlos
			else if (!strcmp(texto_tecla,"CS")) util_set_reset_key(UTIL_KEY_SHIFT_L,1);
		//if (menu_button_osdkeyboard_caps.v) puerto_65278  &=255-1;
		//if (menu_button_osdkeyboard_symbol.v) puerto_32766 &=255-2;



		}
}

int menu_onscreen_send_enter_check_exit(z80_byte tecla)
{


	if (tecla==2) {
		//printf ("exit with ESC\n");

		return 1; //Salir con ESC
	}

	int indice;
	int salir=0;

	indice=menu_onscreen_keyboard_return_index_cursor();
	if (indice==40) {
        //En sticky
        menu_onscreen_keyboard_sticky ^=1;

        if (!menu_onscreen_keyboard_sticky) menu_onscreen_keyboard_reset_pressed_keys();
	}

	else {


		//Si esta en modo sticky, agregar tecla a la lista y enviar todas
		//Si no, solo enviar una tecla
		if (!menu_onscreen_keyboard_sticky) {
			menu_onscreen_keyboard_reset_pressed_keys();
		}

		//Agregar esa tecla al array, siempre que no sea orden "send"
	        indice=menu_onscreen_keyboard_return_index_cursor();

	        if (indice!=41) {
			menu_osd_teclas_pulsadas[indice] ^=1;
			if (menu_osd_teclas_pulsadas[indice]) debug_printf (VERBOSE_DEBUG,"Adding key %s",teclas_osd[indice].tecla);
			else debug_printf (VERBOSE_DEBUG,"Clearing key %s",teclas_osd[indice].tecla);
		}

		//Si es modo stick, solo enviar cuando pulsar "Send"
		//Si no modo stick, enviar la que haya
		//int enviar=1;
		salir=1;
		if (menu_onscreen_keyboard_sticky && indice!=41) {
			salir=0;
			//enviar=0;
		}

	}


	return salir;

}

void menu_onscreen_keyboard(MENU_ITEM_PARAMETERS)
{
	//Si maquina no es Spectrum o zx80/81, volver
	if (!MACHINE_IS_SPECTRUM && !MACHINE_IS_ZX8081) return;

	
	//Evitar que se pueda llamar al mismo osd desde aqui dentro
	int antes_osd_kb_no_mostrar_desde_menu=osd_kb_no_mostrar_desde_menu;
	osd_kb_no_mostrar_desde_menu=1;


	if (!menu_onscreen_keyboard_sticky) menu_onscreen_keyboard_reset_pressed_keys();


	zxvision_window ventana;

	
    int ancho_ventana;
    int alto_ventana;
    int xventana;
    int yventana;

    int is_minimized,is_maximized,ancho_antes_minimize,alto_antes_minimize;

    if (!util_find_window_geometry("osdkeyboard",&xventana,&yventana,&ancho_ventana,&alto_ventana,&is_minimized,&is_maximized,&ancho_antes_minimize,&alto_antes_minimize)) {
        ancho_ventana=OSD_KEYBOARD_ANCHO_VENTANA;
        alto_ventana=OSD_KEYBOARD_ALTO_VENTANA;
        xventana=OSD_KEYBOARD_X_VENTANA;
        yventana=OSD_KEYBOARD_Y_VENTANA;   
    }    

 
    zxvision_new_window(&ventana,xventana,yventana,ancho_ventana,alto_ventana,
                        ancho_ventana-1,alto_ventana-2,"On Screen Keyboard");

    strcpy(ventana.geometry_name,"osdkeyboard");

    zxvision_draw_window(&ventana);

	z80_byte tecla;

	int salir=0;

	

	do {

        int linea=1;

            //01234567890123456789012345678901
        char textoventana[32];

		int fila_tecla;
		int pos_tecla_en_fila;

		int indice_tecla=0;

		for (fila_tecla=0;fila_tecla<4;fila_tecla++) {
		//Inicializar texto linea con 31 espacios
					                  //1234567890123456789012345678901
			sprintf (textoventana,"%s","                               ");
			for (pos_tecla_en_fila=0;pos_tecla_en_fila<10;pos_tecla_en_fila++) {
				//Copiar texto tecla a buffer linea
				int len=teclas_osd[indice_tecla].ancho_tecla;
				int tecla_x=teclas_osd[indice_tecla].x;
				int i;

				//parchecillo para ZX80/81. Si es Symbol Shift, Realmente es el .
				if (MACHINE_IS_ZX8081 && !strcmp(teclas_osd[indice_tecla].tecla,"SS")) {
					textoventana[tecla_x+0]='.';
					textoventana[tecla_x+1]=' ';  //Como ancho de tecla realmente es dos, meter un espacio
				}

				//parchecillo para ZX80/81. Si es ENT, Realmente es NL
				else if (MACHINE_IS_ZX8081 && !strcmp(teclas_osd[indice_tecla].tecla,"ENT")) {
					textoventana[tecla_x+0]='N';
					textoventana[tecla_x+1]='L';
					textoventana[tecla_x+2]=' ';  //Como ancho de tecla realmente es tres, meter un espacio
				}

				else for (i=0;i<len;i++) {
					textoventana[tecla_x+i+0]=teclas_osd[indice_tecla].tecla[i];
				}

				indice_tecla++;
			}

			//Meter final de cadena
			textoventana[OSD_KEYBOARD_ANCHO_VENTANA-2]=0;


			//No queremos que se envie cada linea a speech
			z80_bit old_textspeech_also_send_menu;
			old_textspeech_also_send_menu.v=textspeech_also_send_menu.v;
			textspeech_also_send_menu.v=0;

	        	
			zxvision_print_string_defaults_fillspc(&ventana,1,linea++,textoventana);


			//Restaurar parametro speech
			textspeech_also_send_menu.v=old_textspeech_also_send_menu.v;

			linea++;
		}

		//No quiero que envie ni "Stick" ni "Send" a speech
		z80_bit old_textspeech_also_send_menu;
		old_textspeech_also_send_menu.v=textspeech_also_send_menu.v;
		textspeech_also_send_menu.v=0;

		
		zxvision_print_string_defaults_fillspc(&ventana,1,linea++,"Stick Send");

		//Restaurar parametro speech
		textspeech_also_send_menu.v=old_textspeech_also_send_menu.v;


		menu_onscreen_keyboard_dibuja_teclas_activas(&ventana);

		menu_onscreen_keyboard_dibuja_cursor(&ventana);


		zxvision_draw_window_contents(&ventana);



		tecla=zxvision_common_getkey_refresh();

        //Si movido raton
        if (tecla==0) {
            if (si_menu_mouse_activado() && si_menu_mouse_en_ventana() ) {
                //printf("despues\n");
                //printf("mouse_x %d mouse_y %d\n",menu_mouse_x,menu_mouse_y);
                int posicion_mouse_x=menu_mouse_x-1;
                int posicion_mouse_y=menu_mouse_y-2;

                int mouse_selecciona_tecla=0;

                //Si raton en ventana

                if (posicion_mouse_y<8) {
                    int i;
                    for (i=0;i<40 && !mouse_selecciona_tecla;i++) {
                        int y=(i/10)*2;
                        int xtecla=teclas_osd[i].x;
                        int anchotecla=teclas_osd[i].ancho_tecla;
                        if (posicion_mouse_x>=xtecla && posicion_mouse_x<xtecla+anchotecla &&
                            y==posicion_mouse_y) {

                            //printf("mouse sobre tecla: %s\n",teclas_osd[i].tecla);
                            osd_keyboard_cursor_y=i / 10;
                            osd_keyboard_cursor_x=i % 10;
                            mouse_selecciona_tecla=1;
                        }
                    }
                }

                else if (posicion_mouse_y==8) {
                    mouse_selecciona_tecla=1;
                    //posicion en sticky o send
                    osd_keyboard_cursor_x=0;
                    osd_keyboard_cursor_y=4;

                    if (posicion_mouse_x>=6) osd_keyboard_cursor_x++;
                }

                
                //Enviar enter si se pulsa el raton, pero solo si se hace click en tecla valida
                if (mouse_left && mouse_selecciona_tecla) {
                    //printf("PULSADA ENTER\n");
                    tecla=13;
                    menu_espera_no_tecla();
                }

            }
        }

		//tambien permitir mover con joystick aunque no este mapeado a cursor key
		switch (tecla) {
			case 11:
				//arriba
				if (osd_keyboard_cursor_y>0) osd_keyboard_cursor_y--;
			break;

			case 10:
				//abajo
				if (osd_keyboard_cursor_y<4) osd_keyboard_cursor_y++;
				if (osd_keyboard_cursor_y==4) osd_keyboard_cursor_x=0;  //Cursor en sticky
			break;

			case 8:
				//izquierda
				if (osd_keyboard_cursor_x>0) osd_keyboard_cursor_x--;
			break;

			case 9:
				//derecha
				if (osd_keyboard_cursor_y==4) {  //Si en linea inferior
					if (osd_keyboard_cursor_x<1) osd_keyboard_cursor_x++;
				}
				else if (osd_keyboard_cursor_x<9) osd_keyboard_cursor_x++;
			break;

			case 2: //ESC
			case 13: //Enter
				salir=menu_onscreen_send_enter_check_exit(tecla);
				
			break;
		}

	} while (salir==0);

	menu_espera_no_tecla();

	//Si salido con Enter o Fire joystick
	if (tecla==13) {
	
        //Liberar otras teclas, por si acaso
        reset_keyboard_ports();
        int i;
        for (i=0;i<40;i++) {
            if (menu_osd_teclas_pulsadas[i]) {
                //printf ("Sending key %s\n",teclas_osd[i].tecla);
                menu_osd_send_key_text(teclas_osd[i].tecla);
            }
        }


        //printf ("Exiting and sending\n");

        salir_todos_menus=1;
        timer_on_screen_key=25; //durante medio segundo
		

	}

	cls_menu_overlay();

    //Grabar geometria ventana
    util_add_window_geometry_compact(&ventana);

    zxvision_destroy_window(&ventana);

	//Si no se ha salido con escape, hacer que vuelva y quitar pulsaciones de caps y symbol
	if (tecla!=2) {
		menu_button_osdkeyboard_return.v=1;
	}
	else {
		//se sale con esc, quitar pulsaciones de caps y symbol
		menu_onscreen_keyboard_reset_pressed_keys();
		menu_onscreen_keyboard_sticky=0;

	}

	osd_kb_no_mostrar_desde_menu=antes_osd_kb_no_mostrar_desde_menu;

}







void menu_exit_emulator(MENU_ITEM_PARAMETERS)
{

	menu_reset_counters_tecla_repeticion();

	int salir=0;

	//Si quickexit, no preguntar
	if (quickexit.v) salir=1;

	else salir=menu_confirm_yesno("Exit ZEsarUX");

                        if (salir) {

				//menu_footer=0;

                                cls_menu_overlay();

                                reset_menu_overlay_function();
                                menu_abierto=0;

                                //if (autosave_snapshot_on_exit.v) autosave_snapshot();

                                //end_emulator();

                                end_emulator_autosave_snapshot();

                        }
                        cls_menu_overlay();
}




void menu_principal_salir_emulador(MENU_ITEM_PARAMETERS)
{
	menu_exit_emulator(0);	
}


void menu_inicio_bucle_main(void)
{
    //printf("menu_inicio_bucle_main: menu_pressed_zxdesktop_button_which %d menu_pressed_zxdesktop_lower_icon_which %d pulsado_alguna_ventana_con_menu_cerrado %d\n",
    //            menu_pressed_zxdesktop_button_which,menu_pressed_zxdesktop_lower_icon_which,pulsado_alguna_ventana_con_menu_cerrado);


    //Primera ayuda siempre que no se haya pulsado en botones de menu diferentes del menu principal o dispositivos
    int mostrar_first_aid_menu=1;
    if (menu_pressed_zxdesktop_lower_icon_which>=0) mostrar_first_aid_menu=0;

    //boton de menu distinto del boton de menu principal
    if (menu_pressed_zxdesktop_button_which>0) mostrar_first_aid_menu=0;
	
    if (mostrar_first_aid_menu) menu_first_aid("initial_menu");

	//Si descargar stats
	//Si se pregunta si se quiere enviar estadisticas, solo si esta el grabado de configuracion, e interfaz permite menu (no stdout ni simpletext ni null)
	if (save_configuration_file_on_exit.v && stats_asked.v==0 && si_normal_menu_video_driver()) {
		stats_ask_if_enable();
	}
	
	int retorno_menu;

	menu_item *array_menu_principal;
	menu_item item_seleccionado;

	int salir_menu=0;


	do {

        //printf("antes del if\n");
		if (menu_pressed_zxdesktop_button_which>=0 || menu_pressed_zxdesktop_lower_icon_which>=0 || pulsado_alguna_ventana_con_menu_cerrado) {
            //printf("se cumple if: menu_pressed_zxdesktop_button_which %d menu_pressed_zxdesktop_lower_icon_which %d pulsado_alguna_ventana_con_menu_cerrado %d\n",
            //    menu_pressed_zxdesktop_button_which,menu_pressed_zxdesktop_lower_icon_which,pulsado_alguna_ventana_con_menu_cerrado);

			cls_menu_overlay();
		//Si se habia pulsado boton de zx desktop y boton no es el 0
		//con boton 0 lo que hacemos es abrir el menu solamente			
			if (menu_pressed_zxdesktop_button_which>0) {
							menu_inicio_handle_button_presses();
			}

			//Si era 0 es el menu inicio y liberamos el boton
			else if (menu_pressed_zxdesktop_button_which==0) {
				menu_pressed_zxdesktop_button_which=-1;
			}

			else if (menu_pressed_zxdesktop_lower_icon_which>=0) {
				menu_inicio_handle_lower_icon_presses();
			}
			//printf ("despues menu_inicio_handle_button_presses\n");

            else if (pulsado_alguna_ventana_con_menu_cerrado) {
                //printf("menu_inicio_bucle_main. pulsado en alguna ventana con menu cerrado\n");
                pulsado_alguna_ventana_con_menu_cerrado=0;
                salir_menu=1;
            }
		}

		else {		
            //printf("else if\n");
            zxvision_helper_menu_shortcut_init();

            if (strcmp(scr_new_driver_name,"xwindows")==0 || strcmp(scr_new_driver_name,"sdl")==0 || strcmp(scr_new_driver_name,"caca")==0 || strcmp(scr_new_driver_name,"fbdev")==0 || strcmp(scr_new_driver_name,"cocoa")==0 || strcmp(scr_new_driver_name,"curses")==0) f_functions=1;
            else f_functions=0;


            menu_add_item_menu_inicial(&array_menu_principal,"~~Smart load",MENU_OPCION_NORMAL,menu_smartload,NULL);
            menu_add_item_menu_spanish(array_menu_principal,"Carga ingenio~~sa");
            menu_add_item_menu_catalan(array_menu_principal,"Carrega enginyo~~sa");
            menu_add_item_menu_shortcut(array_menu_principal,'s');
                    menu_add_item_menu_tooltip(array_menu_principal,"Smart load tape, snapshot, Z88 memory card or Timex Cartridge");
                    menu_add_item_menu_ayuda(array_menu_principal,"This option loads the file depending on its type: \n"
                        "-Binary tapes are inserted as standard tapes and loaded quickly\n"
                        "-Audio tapes are loaded as real tapes\n"
                        "-Snapshots are loaded at once\n"
                        "-Timex Cartridges are inserted on the machine and you should do a reset to run the cartridge\n"
                        "-Memory cards on Z88 are inserted on the machine\n\n"
                        "Note: Tapes will be autoloaded if the autoload setting is on (by default)"

                        );


            menu_add_item_menu_en_es_ca(array_menu_principal,MENU_OPCION_NORMAL,menu_snapshot,NULL,
                "S~~napshot","I~~nstantánea","I~~nstantània");
            menu_add_item_menu_shortcut(array_menu_principal,'n');
            menu_add_item_menu_tooltip(array_menu_principal,"Load or save snapshots");
            menu_add_item_menu_ayuda(array_menu_principal,"Load or save different snapshot images. Snapshot images are loaded or saved at once");
            menu_add_item_menu_tiene_submenu(array_menu_principal);


            menu_add_item_menu_en_es_ca(array_menu_principal,MENU_OPCION_NORMAL,menu_machine_selection,NULL,
                "~~Machine","~~Máquina","~~Màquina");
            menu_add_item_menu_shortcut(array_menu_principal,'m');
            menu_add_item_menu_tooltip(array_menu_principal,"Change active machine");
            menu_add_item_menu_ayuda(array_menu_principal,"You can switch to another machine. It also resets the machine");
            menu_add_item_menu_tiene_submenu(array_menu_principal);


            menu_add_item_menu(array_menu_principal,"~~Audio",MENU_OPCION_NORMAL,menu_audio,NULL);
            menu_add_item_menu_shortcut(array_menu_principal,'a');
            menu_add_item_menu_tooltip(array_menu_principal,"Audio related actions");
            menu_add_item_menu_ayuda(array_menu_principal,"Audio related actions");
            menu_add_item_menu_tiene_submenu(array_menu_principal);


            menu_add_item_menu(array_menu_principal,"~~Display",MENU_OPCION_NORMAL,menu_display_settings,NULL);
            menu_add_item_menu_shortcut(array_menu_principal,'d');
            menu_add_item_menu_tooltip(array_menu_principal,"Display related actions");
            menu_add_item_menu_ayuda(array_menu_principal,"Display related actions");		
            menu_add_item_menu_tiene_submenu(array_menu_principal);


            menu_add_item_menu_en_es_ca(array_menu_principal,MENU_OPCION_NORMAL,menu_storage,NULL,
                "S~~torage","Almacenamien~~to","Emmagatzema~~tge");
            menu_add_item_menu_shortcut(array_menu_principal,'t');
            menu_add_item_menu_tooltip(array_menu_principal,"Select storage mediums, like tape, MMC, IDE, etc");
            menu_add_item_menu_ayuda(array_menu_principal,"Select storage mediums, like tape, MMC, IDE, etc");
            menu_add_item_menu_tiene_submenu(array_menu_principal);


            menu_add_item_menu(array_menu_principal,"D~~ebug",MENU_OPCION_NORMAL,menu_debug_main,NULL);
            menu_add_item_menu_shortcut(array_menu_principal,'e');
            menu_add_item_menu_tooltip(array_menu_principal,"Debug tools");
            menu_add_item_menu_ayuda(array_menu_principal,"Tools to debug the machine");
            menu_add_item_menu_tiene_submenu(array_menu_principal);


            menu_add_item_menu(array_menu_principal,"Netw~~ork",MENU_OPCION_NORMAL,menu_network,NULL);
            menu_add_item_menu_shortcut(array_menu_principal,'o');
            menu_add_item_menu_tooltip(array_menu_principal,"Network related actions");
            menu_add_item_menu_ayuda(array_menu_principal,"Network related actions");
            menu_add_item_menu_tiene_submenu(array_menu_principal);


            if (menu_allow_background_windows) {
                menu_add_item_menu(array_menu_principal,"~~Windows",MENU_OPCION_NORMAL,menu_windows,NULL);
                menu_add_item_menu_shortcut(array_menu_principal,'w');
                menu_add_item_menu_tooltip(array_menu_principal,"Window management");
                menu_add_item_menu_ayuda(array_menu_principal,"Window management");
                menu_add_item_menu_tiene_submenu(array_menu_principal);
            }


            menu_add_item_menu(array_menu_principal,"",MENU_OPCION_SEPARADOR,NULL,NULL);		


            menu_add_item_menu_en_es_ca(array_menu_principal,MENU_OPCION_NORMAL,menu_settings,NULL,
                "Sett~~ings","Opc~~iones","Opc~~ions");
            menu_add_item_menu_shortcut(array_menu_principal,'i');
            menu_add_item_menu_tooltip(array_menu_principal,"General Settings");
            menu_add_item_menu_ayuda(array_menu_principal,"General Settings");
            menu_add_item_menu_tiene_submenu(array_menu_principal);


            menu_add_item_menu(array_menu_principal,"He~~lp",MENU_OPCION_NORMAL,menu_help,NULL);
            menu_add_item_menu_shortcut(array_menu_principal,'l');
            menu_add_item_menu_tooltip(array_menu_principal,"Help menu");
            menu_add_item_menu_ayuda(array_menu_principal,"Some help and related files");
            menu_add_item_menu_tiene_submenu(array_menu_principal);


            menu_add_item_menu_en_es_ca(array_menu_principal,MENU_OPCION_NORMAL|MENU_OPCION_ESC,NULL,NULL,
                "Close menu","Cerrar menu","Tancar menu");
            menu_add_item_menu_prefijo_format(array_menu_principal,"%s ",esc_key_message);
            menu_add_item_menu_tooltip(array_menu_principal,string_esc_go_back);
            menu_add_item_menu_ayuda(array_menu_principal,string_esc_go_back);

            menu_add_item_menu_en_es_ca(array_menu_principal,MENU_OPCION_NORMAL,menu_principal_salir_emulador,NULL,
                "Exit ZEsarUX","Salir de ZEsarUX","Sortir de ZEsarUX");
            menu_add_item_menu_prefijo_format(array_menu_principal,"%s",(f_functions==1 ? "F10 ": "") );
            menu_add_item_menu_tooltip(array_menu_principal,"Exit ZEsarUX");
            menu_add_item_menu_ayuda(array_menu_principal,"Exit ZEsarUX");


            retorno_menu=menu_dibuja_menu(&menu_inicio_opcion_seleccionada,&item_seleccionado,array_menu_principal,"ZEsarUX v." EMULATOR_VERSION );

            //printf ("Opcion seleccionada: %d\n",menu_inicio_opcion_seleccionada);
            //printf ("Tipo opcion: %d\n",item_seleccionado.tipo_opcion);
            //printf ("Retorno menu: %d\n",retorno_menu);
            

            if ( (retorno_menu!=MENU_RETORNO_ESC) &&  (retorno_menu==MENU_RETORNO_F10)  ) {

                //menu_exit_emulator(0);
                menu_principal_salir_emulador(0);

            }


            else if (retorno_menu>=0) {
                //llamamos por valor de funcion
                if (item_seleccionado.menu_funcion!=NULL) {
                    //printf ("actuamos por funcion\n");
        
                    item_seleccionado.menu_funcion(item_seleccionado.valor_opcion);
        

                    //si ha generado error, no salir
                    if (if_pending_error_message) salir_todos_menus=0;
                }

                
            }



            if (retorno_menu==MENU_RETORNO_ESC || (item_seleccionado.tipo_opcion & MENU_OPCION_ESC) == MENU_OPCION_ESC) {
                //printf ("opcion ESC o pulsado ESC\n");
                salir_menu=1;
            }

		}

	} while (!salir_menu && !salir_todos_menus);



}


