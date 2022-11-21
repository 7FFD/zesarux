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

DSK emulation

*/


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>


#include "dsk.h"
#include "cpu.h"
#include "debug.h"
#include "utils.h"
#include "tape.h"
#include "menu_items.h"
#include "screen.h"


char dskplusthree_file_name[PATH_MAX]="";

z80_bit dskplusthree_write_protection={0};

int dskplusthree_must_flush_to_disk=0;


//Si cambios en escritura se hace flush a disco
z80_bit dskplusthree_persistent_writes={1};


z80_byte p3dsk_buffer_disco[DSK_MAX_BUFFER_DISCO];
int p3dsk_buffer_disco_size=DSK_MAX_BUFFER_DISCO; //Tamanyo del dsk leido. De momento establecemos en maximo

void dsk_insert_disk(char *nombre)
{
                strcpy(dskplusthree_file_name,nombre);
                
    if (noautoload.v==0) {
		reset_cpu();
	}
}


z80_bit dskplusthree_emulation={0};


void dskplusthree_flush_contents_to_disk(void)
{

        if (dskplusthree_emulation.v==0) return;

        if (dskplusthree_must_flush_to_disk==0) {
                debug_printf (VERBOSE_DEBUG,"Trying to flush DSK to disk but no changes made");
                return;
        }


        if (dskplusthree_persistent_writes.v==0) {
                debug_printf (VERBOSE_DEBUG,"Trying to flush DSK to disk but persistent writes disabled");
                return;
        }



        debug_printf (VERBOSE_INFO,"Flushing DSK to disk");


        FILE *ptr_dskplusthreefile;

        debug_printf (VERBOSE_INFO,"Opening DSK File %s",dskplusthree_file_name);
        ptr_dskplusthreefile=fopen(dskplusthree_file_name,"wb");



        int escritos=0;
        long long int size;
        size=p3dsk_buffer_disco_size;


        if (ptr_dskplusthreefile!=NULL) {
                z80_byte *puntero;
                puntero=p3dsk_buffer_disco; 

                //Justo antes del fwrite se pone flush a 0, porque si mientras esta el fwrite entra alguna operacion de escritura,
                //metera flush a 1
                dskplusthree_must_flush_to_disk=0;

                escritos=fwrite(puntero,1,size,ptr_dskplusthreefile);

                fclose(ptr_dskplusthreefile);


        }

        //debug_printf(VERBOSE_DEBUG,"ptr_dskplusthreefile: %d",ptr_dskplusthreefile);
        //debug_printf(VERBOSE_DEBUG,"escritos: %d",escritos);

        if (escritos!=size || ptr_dskplusthreefile==NULL) {
                debug_printf (VERBOSE_ERR,"Error writing to DSK file");
        }

}




void dskplusthree_disable(void)
{

	if (dskplusthree_emulation.v==0) return;

	debug_printf (VERBOSE_INFO,"Disabling DSK emulation");

	dskplusthree_emulation.v=0;
}

                                
const char *dsk_signature_basic=   "MV - CPC";
//Usada en captain blood: "MV - CPC format Disk Image (DU54)\r\nDisk-Info"

const char *dsk_signature_extended="EXTENDED";

int dsk_file_type_extended=0;

void dsk_get_string_protected(int offset,char *buffer_signature,int total_bytes)
{
    int i;
    for (i=0;i<total_bytes;i++) {
        z80_byte c=p3dsk_buffer_disco[i+offset];
        if (c<32 || c>126) c='.';

        buffer_signature[i]=c;
    }

    buffer_signature[i]=0;    
}



void dsk_get_signature(char *buffer)
{
    //Mostrar firma ocultando caracteres no validos
    dsk_get_string_protected(0,buffer,DSK_SIGNATURE_LENGTH);
}

void dsk_get_creator(char *buffer)
{
    dsk_get_string_protected(0x22,buffer,DSK_CREATOR_LENGTH);
}


void dskplusthree_enable(void)
{

	if (dskplusthree_emulation.v) return;

	debug_printf (VERBOSE_INFO,"Enabling DSK emulation");
	debug_printf (VERBOSE_INFO,"Opening DSK File %s",dskplusthree_file_name);

	long long int tamanyo=get_file_size(dskplusthree_file_name);

	if (tamanyo>DSK_MAX_BUFFER_DISCO) {
		debug_printf(VERBOSE_ERR,"DSK size too big");
		return;
	}

        FILE *ptr_dskfile;
        ptr_dskfile=fopen(dskplusthree_file_name,"rb");

        if (!ptr_dskfile) {
                debug_printf(VERBOSE_ERR,"Unable to open disk %s",dskplusthree_file_name);
                return;
        }

        //int leidos=fread(p3dsk_buffer_disco,1,200000,ptr_configfile);
        fread(p3dsk_buffer_disco,1,DSK_MAX_BUFFER_DISCO,ptr_dskfile);


        fclose(ptr_dskfile);

    //Detect signature
    const int signature_check_length=8;

    if (!memcmp(dsk_signature_basic,p3dsk_buffer_disco,signature_check_length)) {
        printf("Detected Basic DSK\n");
        dsk_file_type_extended=0;
    }

    else if (!memcmp(dsk_signature_extended,p3dsk_buffer_disco,signature_check_length)) {
        printf("Detected Extended DSK\n");
        dsk_file_type_extended=1;
    }

    else {
        debug_printf(VERBOSE_ERR,"Unknown DSK file format");
        return;
    }

    //Mostrar firma ocultando caracteres no validos
    char buffer_signature[DSK_SIGNATURE_LENGTH+1];
    dsk_get_signature(buffer_signature);
    printf("DSK signature: %s\n",buffer_signature);

    char buffer_creator[DSK_CREATOR_LENGTH+1];
    dsk_get_creator(buffer_creator);
    printf("DSK creator: %s\n",buffer_creator);    

    printf("DSK total tracks: %d total sides: %d\n",dsk_get_total_tracks(),dsk_get_total_sides());

	p3dsk_buffer_disco_size=tamanyo;

        dskplusthree_emulation.v=1;

}


z80_byte plus3dsk_get_byte_disk(int offset)
{

        if (dskplusthree_emulation.v==0) return 0;

        if (offset>=p3dsk_buffer_disco_size) {
                debug_printf (VERBOSE_ERR,"Error. Trying to read beyond dsk. Size: %d Asked: %d. Disabling DSK",p3dsk_buffer_disco_size,offset);
                dskplusthree_disable();
                return 0;
        }


        return p3dsk_buffer_disco[offset];
}

void plus3dsk_put_byte_disk(int offset,z80_byte value)
{
        if (dskplusthree_emulation.v==0) return;

        if (offset>=p3dsk_buffer_disco_size) {
                debug_printf (VERBOSE_ERR,"Error. Trying to read beyond dsk. Size: %d Asked: %d. Disabling DSK",p3dsk_buffer_disco_size,offset);
                dskplusthree_disable();
                return;
        }


	if (dskplusthree_write_protection.v) return;

        p3dsk_buffer_disco[offset]=value;

	dskplusthree_must_flush_to_disk=1;
}

int dsk_get_total_tracks(void)
{
    return p3dsk_buffer_disco[0x30];
}

int dsk_get_total_sides(void)
{
    return p3dsk_buffer_disco[0x31];
}

void dsk_show_activity(void)
{
	generic_footertext_print_operating("DISK");

	//Y poner icono en inverso
	if (!zxdesktop_icon_plus3_inverse) {
			zxdesktop_icon_plus3_inverse=1;
			menu_draw_ext_desktop();
	}	
}

const int dsk_sector_sizes_numbers[]={
    0,    //0: no usado, puesto aqui por comodidad al hacer lookup de tabla
    256,  //1
    512,  //2
    1024, //3
    2048, //4
    4096, //5
    8192, //6
};


//entrada: offset a track information block
int dsk_get_gap_length_track_from_offset(int offset)
{
    z80_byte gap=plus3dsk_get_byte_disk(offset+0x16);

    return gap;
}



int dsk_get_gap_length_track(int pista,int cara)
{
    int offset=dsk_get_start_track(pista,cara);
    return dsk_get_gap_length_track_from_offset(offset);

}


//entrada: offset a track information block
int dsk_get_filler_byte_track_from_offset(int offset)
{
    z80_byte filler=plus3dsk_get_byte_disk(offset+0x17);

    return filler;
}

int dsk_get_filler_byte_track(int pista,int cara)
{
    int offset=dsk_get_start_track(pista,cara);
    return dsk_get_filler_byte_track_from_offset(offset);

}


//entrada: offset a track information block
int dsk_get_total_sectors_track_from_offset(int offset)
{
    int total_sectors=plus3dsk_get_byte_disk(offset+0x15);

    return total_sectors;
}


int dsk_get_total_sectors_track(int pista,int cara)
{
    int offset=dsk_get_start_track(pista,cara);
    return dsk_get_total_sectors_track_from_offset(offset);

}


//entrada: offset a track information block
int dsk_get_sector_size_track_from_offset(int offset)
{
    int sector_size=plus3dsk_get_byte_disk(offset+0x14);
    if (sector_size<1 || sector_size>6) {
        debug_printf(VERBOSE_ERR,"Sector size %d unsupported",sector_size);
        return -1;
    }

    sector_size=dsk_sector_sizes_numbers[sector_size];

    return sector_size;
}

int dsk_get_sector_size_track(int pista,int cara)
{
    int offset=dsk_get_start_track(pista,cara);
    return dsk_get_sector_size_track_from_offset(offset);
}



const char *dsk_track_info_signature="Track-Info\r\n";

int dsk_check_track_signature(int offset)
{
    int i;
    for (i=0;i<12;i++) {
        int leido_firma=dsk_track_info_signature[i];
        int leido_pista=plus3dsk_get_byte_disk(offset+i);
        if (leido_firma!=leido_pista) return -1;
    }
    return 0;    
}

int dsk_basic_get_start_track(int pista_encontrar,int cara_encontrar)
{
    int pista;
    int offset=0x100;

    for (pista=0;pista<dsk_get_total_tracks();pista++) {
        //Validar que estemos en informacion de pista realmente mirando la firma
        //TODO: quiza esta validacion se pueda quitar y/o hacerla al abrir el dsk 
        if (dsk_check_track_signature(offset)) {
            debug_printf(VERBOSE_ERR,"DSK: Track signature not found on track %XH offset %XH",pista,offset);
        }    

        z80_byte track_number=plus3dsk_get_byte_disk(offset+0x10);
        z80_byte side_number=plus3dsk_get_byte_disk(offset+0x11);

        if (track_number==pista_encontrar && side_number==cara_encontrar) {
            return offset;
        }

        int sector_size=dsk_get_sector_size_track_from_offset(offset);
        if (sector_size<0) {
            return -1;
        }

        int total_sectors=dsk_get_total_sectors_track_from_offset(offset);

        int saltar=total_sectors*sector_size+256; //256 ocupa el sector block

        offset +=saltar;
    }

    return -1;

}

//Retorna numero de pista. 
//Entrada: offset: offset a track-info
int dsk_get_track_number_from_offset(int offset)
{
    z80_byte track_number=plus3dsk_get_byte_disk(offset+0x10);
    return track_number;
}


int dsk_get_track_number(int pista,int cara)
{
    int offset=dsk_get_start_track(pista,cara);
    return dsk_get_track_number_from_offset(offset);
}


//Retorna numero de cata. 
//Entrada: offset: offset a track-info
int dsk_get_track_side_from_offset(int offset)
{
    z80_byte side_number=plus3dsk_get_byte_disk(offset+0x11);
    return side_number;
}

int dsk_get_track_side(int pista,int cara)
{
    int offset=dsk_get_start_track(pista,cara);
    return dsk_get_track_side_from_offset(offset);
}


int dsk_extended_get_start_track(int pista_encontrar,int cara_encontrar)
{
    int pista;
    int offset=0x100;
    int offset_track_table=0x34;

    for (pista=0;pista<dsk_get_total_tracks();pista++) {
        //Validar que estemos en informacion de pista realmente mirando la firma
        //TODO: quiza esta validacion se pueda quitar y/o hacerla al abrir el dsk 
        if (dsk_check_track_signature(offset)) {
            debug_printf(VERBOSE_ERR,"DSK: Track signature not found on track %XH offset %XH",pista,offset);
        } 

        z80_byte track_number=dsk_get_track_number_from_offset(offset);
        z80_byte side_number=dsk_get_track_side_from_offset(offset);

        //printf("dsk_extended_get_start_track: pista: %d current_track: %d offset: %XH buscar pista: %d\n",
        //    pista,track_number,offset,pista_encontrar);        

        if (track_number==pista_encontrar && side_number==cara_encontrar) {
            printf("dsk_extended_get_start_track: return %X\n",offset);
            return offset;
        }

        int sector_size=dsk_get_sector_size_track_from_offset(offset);
        if (sector_size<0) {
            return -1;
        }

        
        int saltar=plus3dsk_get_byte_disk(offset_track_table)*256;
        offset +=saltar;

        //TODO: este incremento sobre la tabla (creo) que es el doble cuando el disco tiene dos caras
        offset_track_table++;
    }

    return -1;

}


//Retorna -1 si pista no encontrada
//Retorna offset al Track information block
int dsk_get_start_track(int pista,int cara)
{
    //Hacerlo diferente si dsk basico o extendido
    if (dsk_file_type_extended) return dsk_extended_get_start_track(pista,cara);
    else return dsk_basic_get_start_track(pista,cara);
}


//Retorna el offset al dsk segun la pista y sector id dados 
//Retorna tambien el sector fisico: 0,1,2,3....
int dsk_get_sector(int pista,int parametro_r,z80_byte *sector_fisico)
{

    int iniciopista=dsk_get_start_track(pista,0); //TODO: de momento solo cara 0

    printf("Inicio pista %d: %XH\n",pista,iniciopista);

    int total_sectors=dsk_get_total_sectors_track_from_offset(iniciopista);   

    printf("Total sectors: %d\n",total_sectors); 


    int sector_information_list=iniciopista+0x18;

    int sector;

    for (sector=0;sector<total_sectors;sector++) {

        printf("Buscando sector ID %02XH on track %d estamos en pos sector %d\n",parametro_r,pista,sector);


        z80_byte sector_id=plus3dsk_get_byte_disk(sector_information_list+2); 


        if (sector_id==parametro_r) {
            //debug_printf(VERBOSE_DEBUG,"Found sector  ID track %d/sector %d at  pos track %d/sector %d",pista_buscar,sector_buscar,pista,sector);
            printf("Found sector ID %02XH on track %d at pos sector %d\n",parametro_r,pista,sector);


            int offset=iniciopista+0x100;

            int sector_size=dsk_get_sector_size_track_from_offset(iniciopista);
            if (sector_size<0) {
                return -1;
            }                        

            //int iniciopista=traps_plus3dos_getoff_start_track(pista);
            int offset_retorno=offset+sector_size*sector;
            //printf("Offset sector: %XH\n",offset_retorno);

            *sector_fisico=sector;
            printf("Found sector ID %02XH on track %d at offset in DSK: %XH\n",parametro_r,pista,offset_retorno);
            return offset_retorno;
        }

        sector_information_list +=8;

    }



    printf("NOT Found sector ID %02XH on track %d (max sectors: %d)\n",parametro_r,pista,total_sectors);
	return -1;

}



//Devolver CHRN de una pista y sector concreto
void dsk_get_chrn(int pista,int cara,int sector_fisico,z80_byte *parametro_c,z80_byte *parametro_h,z80_byte *parametro_r,z80_byte *parametro_n)
{


    int iniciopista=dsk_get_start_track(pista,cara); 

    printf("En dsk_get_chrn Inicio pista %d: %XH\n",pista,iniciopista);

    //saltar 0x18
    iniciopista +=0x18;


    int offset_tabla_sector=sector_fisico*8; 
    //z80_byte pista_id=plus3dsk_get_byte_disk(iniciopista+offset_tabla_sector); //Leemos pista id
    //z80_byte sector_id=plus3dsk_get_byte_disk(iniciopista+offset_tabla_sector+2); //Leemos c1, c2, etc

    //debug_printf(VERBOSE_DEBUG,"%02X ",sector_id);

    *parametro_c=plus3dsk_get_byte_disk(iniciopista+offset_tabla_sector); 
    *parametro_h=plus3dsk_get_byte_disk(iniciopista+offset_tabla_sector+1); 
    *parametro_r=plus3dsk_get_byte_disk(iniciopista+offset_tabla_sector+2); 
    *parametro_n=plus3dsk_get_byte_disk(iniciopista+offset_tabla_sector+3);             
            



}




//Devolver st1,2 de una pista y sector concreto

void dsk_get_st12(int pista,int cara,int sector_fisico,z80_byte *parametro_st1,z80_byte *parametro_st2)
{

    int iniciopista=dsk_get_start_track(pista,cara); 

    printf("En dsk_get_st12 Inicio pista %d: %XH\n",pista,iniciopista);

    //saltar 0x18
    iniciopista +=0x18;


    int offset_tabla_sector=sector_fisico*8; 
    //z80_byte pista_id=plus3dsk_get_byte_disk(iniciopista+offset_tabla_sector); //Leemos pista id
    //z80_byte sector_id=plus3dsk_get_byte_disk(iniciopista+offset_tabla_sector+2); //Leemos c1, c2, etc

    //debug_printf(VERBOSE_DEBUG,"%02X ",sector_id);


    *parametro_st1=plus3dsk_get_byte_disk(iniciopista+offset_tabla_sector+4); 
    *parametro_st2=plus3dsk_get_byte_disk(iniciopista+offset_tabla_sector+5);             
            


}



