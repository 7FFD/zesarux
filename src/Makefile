EMULATOR_VERSION=X
CFLAGS= -fsigned-char -g
LDFLAGS= -lncurses -lX11 -L/usr/X11R6/lib -L/opt/X11/lib -lXext -lXxf86vm -lpthread -framework CoreAudio -framework AudioUnit -framework CoreServices -framework CoreMIDI -framework IOKit -framework Foundation -framework AppKit -framework OpenGL
CC=gcc
INSTALLPREFIX=/usr/local


all: zesarux


zesarux:  charset.o scrstdout.o scrsimpletext.o scrcurses.o    scrxwindows.o   autoselectoptions.o chardetect.o textspeech.o scrnull.o     audiocoreaudio.o  audionull.o ay38912.o sn76489an.o vdp_9918a.o vdp_9918a_sms.o msx.o svi.o coleco.o sg1000.o sms.o saa_simul.o cpu.o start.o codsinpr.o codprddfd.o codpred.o operaciones.o debug.o tape.o tape_tap.o tape_tzx.o tape_pzx.o tape_smp.o audio.o audio_sine_table.o screen.o mem128.o chloe.o prism.o tbblue.o timex.o zx8081.o jupiterace.o z88.o cpc.o pcw.o sam.o atomlite.o zxuno.o snap.o snap_zsf.o snap_ram.o snap_z81.o snap_zx8081.o snap_rzx.o snap_spg.o spg_depack.o zxvision.o menu_items.o menu_filesel.o menu_file_viewer_browser.o menu_zeng_online.o menu_items_settings.o menu_debug_cpu.o menu_bitmaps.o salamanquesa.o settings.o core_spectrum.o core_reduced_spectrum.o core_zx8081.o core_z88.o core_cpc.o core_pcw.o core_ace.o core_sam.o core_ql.o core_mk14.o core_msx.o core_svi.o core_coleco.o core_sg1000.o core_sms.o mk14.o scmp.o timer.o contend.o disassemble.o utils.o utils_text_adventure.o playtzx.o mdvtool.o joystick.o ula.o mmc.o ide.o pd765.o dsk.o plus3dos_handler.o divmmc.o divide.o diviface.o zxpand.o superupgrade.o dandanator.o gs.o betadisk.o codetests.o kartusho.o samram.o ifrom.o hilow_datadrive.o hilow_barbanegra.o transtape.o mhpokeador.o specmate.o interface007.o dinamid3.o phoenix.o defcon.o ramjet.o datagear.o spritefinder.o multiface.o spectra.o spritechip.o printers.o realjoystick.o ulaplus.o if1.o ds1307.o ql.o ql_qdos_handler.o ql_i8049.o ql_zx8302.o m68kcpu.o m68kdasm.o m68kops.o  m68kopac.o m68kopdm.o m68kopnz.o chrome.o zxevo.o tsconf.o baseconf.o remote.o esxdos_handler.o assemble.o expression_parser.o chardevice.o uartbridge.o network.o zeng.o zeng_online.o zeng_online_client.o zvfs.o atomic.o stats.o sensors.o hilow_datadrive_audio.o scl2trd.o zip.o diskio.o ff.o ffsystem.o ffunicode.o sdcard.o rtc.o scrcocoa.o 
	$(CC) $(CFLAGS) -ggdb cpu.o scrcocoa.o start.o charset.o scrstdout.o scrsimpletext.o scrcurses.o    scrxwindows.o   autoselectoptions.o chardetect.o textspeech.o scrnull.o screen.o mem128.o chloe.o prism.o tbblue.o timex.o     audiocoreaudio.o  audionull.o ay38912.o sn76489an.o vdp_9918a.o vdp_9918a_sms.o msx.o svi.o coleco.o sg1000.o sms.o saa_simul.o codsinpr.o codprddfd.o codpred.o operaciones.o debug.o tape.o tape_tap.o tape_tzx.o tape_pzx.o tape_smp.o audio.o audio_sine_table.o zx8081.o jupiterace.o z88.o cpc.o pcw.o sam.o atomlite.o zxuno.o snap.o snap_zsf.o snap_ram.o snap_z81.o snap_spg.o spg_depack.o snap_zx8081.o snap_rzx.o zxvision.o menu_items.o menu_filesel.o menu_file_viewer_browser.o menu_zeng_online.o menu_items_settings.o menu_debug_cpu.o menu_bitmaps.o salamanquesa.o settings.o core_spectrum.o core_reduced_spectrum.o core_zx8081.o core_z88.o core_cpc.o core_pcw.o core_ace.o core_sam.o core_ql.o core_mk14.o core_msx.o core_svi.o core_coleco.o core_sg1000.o core_sms.o mk14.o scmp.o timer.o contend.o disassemble.o utils.o utils_text_adventure.o playtzx.o mdvtool.o joystick.o ula.o mmc.o ide.o pd765.o dsk.o plus3dos_handler.o divmmc.o divide.o diviface.o zxpand.o superupgrade.o dandanator.o gs.o betadisk.o codetests.o kartusho.o samram.o ifrom.o hilow_datadrive.o hilow_barbanegra.o transtape.o mhpokeador.o specmate.o interface007.o dinamid3.o phoenix.o defcon.o ramjet.o datagear.o spritefinder.o multiface.o spectra.o spritechip.o printers.o realjoystick.o ulaplus.o ds1307.o if1.o ql.o ql_qdos_handler.o ql_i8049.o ql_zx8302.o m68kcpu.o m68kdasm.o m68kops.o  m68kopac.o m68kopdm.o m68kopnz.o chrome.o zxevo.o tsconf.o baseconf.o remote.o esxdos_handler.o assemble.o expression_parser.o chardevice.o uartbridge.o network.o zeng.o zeng_online.o zeng_online_client.o zvfs.o atomic.o stats.o sensors.o hilow_datadrive_audio.o scl2trd.o zip.o diskio.o ff.o ffsystem.o ffunicode.o sdcard.o rtc.o -o zesarux $(LDFLAGS)
	@echo
	@echo "Compilation finished"
	@echo "You can run it without installing by typing ./zesarux (or just zesarux on Windows)"
	@echo

rtc.o: rtc.c rtc.h cpu.h
	$(CC) $(CFLAGS) -c rtc.c

sdcard.o: sdcard.c sdcard.h cpu.h
	$(CC) $(CFLAGS) -c sdcard.c

charset.o: charset.c charset.h zxvision.h
	$(CC) $(CFLAGS) -c charset.c

scrnull.o: scrnull.c scrnull.h debug.h screen.h cpu.h settings.h
	$(CC) $(CFLAGS) -c scrnull.c

codprddfd.o: codprddfd.c cpu.h operaciones.h debug.h contend.h utils.h compileoptions.h settings.h
	$(CC) $(CFLAGS) -c codprddfd.c

codpred.o: codpred.c cpu.h operaciones.h debug.h contend.h zxuno.h tbblue.h screen.h settings.h samram.h
	$(CC) $(CFLAGS) -c codpred.c

codsinpr.o: codsinpr.c cpu.h operaciones.h debug.h contend.h utils.h compileoptions.h z88.h snap_rzx.h esxdos_handler.h settings.h
	$(CC) $(CFLAGS) -c codsinpr.c

operaciones.o: operaciones.c cpu.h operaciones.h debug.h audio.h tape.h ay38912.h mem128.h chloe.h prism.h tbblue.h timex.h zx8081.h zxvision.h screen.h compileoptions.h contend.h joystick.h ula.h utils.h printers.h disassemble.h z88.h ulaplus.h zxuno.h chardetect.h mmc.h ide.h divmmc.h divide.h diviface.h zxpand.h spectra.h spritechip.h jupiterace.h cpc.h sam.h if1.h timer.h pd765.h superupgrade.h snap_rzx.h multiface.h chrome.h zxevo.h tsconf.h baseconf.h ds1307.h mk14.h settings.h saa_simul.h datagear.h hilow_datadrive.h msx.h coleco.h sg1000.h sms.h svi.h vdp_9918a.h gs.h samram.h vdp_9918a_sms.h hilow_barbanegra.h transtape.h phoenix.h defcon.h ramjet.h plus3dos_handler.h pcw.h dsk.h utils_text_adventure.h
	$(CC) $(CFLAGS) -c operaciones.c

cpu.o: cpu.c cpu.h start.h scrnull.h scrstdout.h scrsimpletext.h operaciones.h debug.h compileoptions.h tape.h tape_tap.h tape_tzx.h audio.h screen.h ay38912.h chloe.h prism.h tbblue.h mem128.h timex.h scrcurses.h scraa.h scrxwindows.h scrsdl.h scrnull.h scrfbdev.h audiodsp.h audioonebitspeaker.h audiosdl.h audionull.h audioalsa.h audiopulse.h zx8081.h snap.h zxvision.h core_spectrum.h core_zx8081.h core_z88.h tape_smp.h contend.h utils.h utils_text_adventure.h ula.h printers.h joystick.h realjoystick.h z88.h ulaplus.h autoselectoptions.h zxuno.h chardetect.h textspeech.h mmc.h ide.h divmmc.h divide.h diviface.h zxpand.h spectra.h spritechip.h jupiterace.h cpc.h sam.h if1.h atomlite.h dandanator.h kartusho.h ifrom.h spritefinder.h superupgrade.h ql.h remote.h snap_rzx.h multiface.h chrome.h zxevo.h tsconf.h baseconf.h scmp.h mk14.h esxdos_handler.h betadisk.h pd765.h settings.h datagear.h network.h stats.h hilow_datadrive.h msx.h svi.h coleco.h sn76489an.h sg1000.h sms.h ql_qdos_handler.h ql_i8049.h snap_ram.h menu_items.h charset.h menu_filesel.h menu_debug_cpu.h hilow_barbanegra.h transtape.h mhpokeador.h specmate.h phoenix.h defcon.h ramjet.h interface007.h dinamid3.h dsk.h plus3dos_handler.h pcw.h 
	$(CC) $(CFLAGS) -c cpu.c

start.o: start.c start.h cpu.h scrnull.h scrstdout.h scrsimpletext.h operaciones.h debug.h compileoptions.h tape.h tape_tap.h tape_tzx.h audio.h screen.h ay38912.h chloe.h prism.h tbblue.h mem128.h timex.h scrcurses.h scraa.h scrxwindows.h scrsdl.h scrnull.h scrfbdev.h audiodsp.h audioonebitspeaker.h audiosdl.h audionull.h audioalsa.h audiopulse.h zx8081.h snap.h zxvision.h core_spectrum.h core_zx8081.h core_z88.h tape_smp.h contend.h utils.h utils_text_adventure.h ula.h printers.h joystick.h realjoystick.h z88.h ulaplus.h autoselectoptions.h zxuno.h chardetect.h textspeech.h mmc.h ide.h divmmc.h divide.h diviface.h zxpand.h spectra.h spritechip.h jupiterace.h cpc.h sam.h if1.h atomlite.h dandanator.h kartusho.h ifrom.h spritefinder.h superupgrade.h ql.h remote.h snap_rzx.h multiface.h chrome.h zxevo.h tsconf.h baseconf.h scmp.h mk14.h esxdos_handler.h betadisk.h codetests.h pd765.h settings.h datagear.h network.h stats.h hilow_datadrive.h msx.h svi.h coleco.h sn76489an.h sg1000.h sms.h ql_qdos_handler.h ql_i8049.h snap_ram.h menu_items.h charset.h menu_filesel.h menu_debug_cpu.h hilow_barbanegra.h transtape.h mhpokeador.h specmate.h phoenix.h defcon.h ramjet.h interface007.h dinamid3.h dsk.h plus3dos_handler.h pcw.h zeng_online.h zeng_online_client.h
	$(CC) $(CFLAGS) -c start.c

core_reduced_spectrum.o: core_reduced_spectrum.c core_reduced_spectrum.h core_spectrum.h cpu.h debug.h tape.h audio.h screen.h ay38912.h operaciones.h snap.h timer.h zxvision.h chardetect.h compileoptions.h contend.h ula.h utils.h realjoystick.h divmmc.h divide.h diviface.h timex.h zxuno.h prism.h snap_rzx.h superupgrade.h pd765.h zxevo.h tsconf.h baseconf.h settings.h snap_zsf.h zeng.h zeng_online.h snap_ram.h pd765.h
	$(CC) $(CFLAGS) -c core_reduced_spectrum.c 

core_spectrum.o: core_spectrum.c core_spectrum.h cpu.h debug.h tape.h audio.h screen.h ay38912.h operaciones.h snap.h timer.h zxvision.h chardetect.h compileoptions.h contend.h ula.h utils.h realjoystick.h divmmc.h divide.h diviface.h timex.h zxuno.h prism.h snap_rzx.h superupgrade.h pd765.h zxevo.h tsconf.h baseconf.h tbblue.h settings.h datagear.h snap_zsf.h zeng.h zeng_online.h ds1307.h gs.h snap_ram.h codsinpr.h menu_items.h plus3dos_handler.h pd765.h zeng_online_client.h
	$(CC) $(CFLAGS) -c core_spectrum.c 

core_zx8081.o: core_zx8081.c core_zx8081.h cpu.h debug.h tape.h audio.h screen.h ay38912.h operaciones.h snap.h zx8081.h timer.h zxvision.h chardetect.h compileoptions.h contend.h snap_zx8081.h utils.h realjoystick.h ula.h settings.h snap_zsf.h zeng.h zeng_online.h snap_ram.h
	$(CC) $(CFLAGS) -c core_zx8081.c

core_ace.o: core_ace.c core_ace.h cpu.h debug.h tape.h audio.h screen.h ay38912.h operaciones.h snap.h jupiterace.h timer.h zxvision.h chardetect.h compileoptions.h contend.h snap_zx8081.h utils.h realjoystick.h ula.h settings.h zeng.h zeng_online.h snap_zsf.h
	$(CC) $(CFLAGS) -c core_ace.c

core_ql.o: core_ql.c core_ql.h cpu.h debug.h tape.h audio.h screen.h ay38912.h operaciones.h snap.h timer.h zxvision.h chardetect.h compileoptions.h contend.h snap_zx8081.h utils.h realjoystick.h ula.h settings.h ql_i8049.h ql_qdos_handler.h ql_zx8302.h zeng.h zeng_online.h snap_zsf.h snap_ram.h
	$(CC) $(CFLAGS) -c core_ql.c

core_mk14.o: core_mk14.c core_mk14.h scmp.h cpu.h debug.h tape.h audio.h screen.h ay38912.h operaciones.h snap.h timer.h zxvision.h chardetect.h compileoptions.h contend.h snap_zx8081.h utils.h realjoystick.h ula.h settings.h
	$(CC) $(CFLAGS) -c core_mk14.c

core_msx.o: core_msx.c core_msx.h cpu.h debug.h tape.h audio.h screen.h ay38912.h operaciones.h snap.h timer.h zxvision.h chardetect.h compileoptions.h contend.h snap_zx8081.h utils.h realjoystick.h  settings.h msx.h snap_ram.h codsinpr.h
	$(CC) $(CFLAGS) -c core_msx.c

core_svi.o: core_svi.c core_svi.h cpu.h debug.h tape.h audio.h screen.h ay38912.h operaciones.h snap.h timer.h zxvision.h chardetect.h compileoptions.h contend.h snap_zx8081.h utils.h realjoystick.h  settings.h svi.h snap_ram.h codsinpr.h
	$(CC) $(CFLAGS) -c core_svi.c

core_coleco.o: core_coleco.c core_coleco.h cpu.h debug.h tape.h audio.h screen.h ay38912.h operaciones.h snap.h timer.h zxvision.h chardetect.h compileoptions.h contend.h snap_zx8081.h utils.h realjoystick.h  settings.h coleco.h vdp_9918a.h sn76489an.h vdp_9918a_sms.h snap_ram.h codsinpr.h
	$(CC) $(CFLAGS) -c core_coleco.c

core_sg1000.o: core_sg1000.c core_sg1000.h cpu.h debug.h tape.h audio.h screen.h ay38912.h operaciones.h snap.h timer.h zxvision.h chardetect.h compileoptions.h contend.h snap_zx8081.h utils.h realjoystick.h  settings.h sg1000.h vdp_9918a.h sn76489an.h vdp_9918a_sms.h snap_ram.h codsinpr.h
	$(CC) $(CFLAGS) -c core_sg1000.c

core_sms.o: core_sms.c core_sms.h cpu.h debug.h tape.h audio.h screen.h ay38912.h operaciones.h snap.h timer.h zxvision.h chardetect.h compileoptions.h contend.h snap_zx8081.h utils.h realjoystick.h  settings.h sms.h vdp_9918a.h sn76489an.h vdp_9918a_sms.h snap_ram.h codsinpr.h
	$(CC) $(CFLAGS) -c core_sms.c

mk14.o: mk14.c mk14.h cpu.h debug.h scmp.h utils.h zxvision.h
	$(CC) $(CFLAGS) -c mk14.c

core_z88.o: core_z88.c core_z88.h cpu.h debug.h tape.h audio.h screen.h operaciones.h snap.h timer.h zxvision.h chardetect.h compileoptions.h contend.h ula.h utils.h z88.h audio.h utils.h settings.h
	$(CC) $(CFLAGS) -c core_z88.c

core_cpc.o: core_cpc.c core_cpc.h cpu.h debug.h tape.h audio.h screen.h operaciones.h snap.h timer.h zxvision.h chardetect.h compileoptions.h contend.h ula.h utils.h audio.h utils.h tape.h cpc.h realjoystick.h settings.h snap_zsf.h zeng.h zeng_online.h snap_ram.h pd765.h
	$(CC) $(CFLAGS) -c core_cpc.c

core_pcw.o: core_pcw.c core_pcw.h cpu.h debug.h tape.h audio.h screen.h operaciones.h snap.h timer.h zxvision.h chardetect.h compileoptions.h contend.h ula.h utils.h audio.h utils.h tape.h pcw.h realjoystick.h settings.h snap_zsf.h zeng.h zeng_online.h snap_ram.h pd765.h
	$(CC) $(CFLAGS) -c core_pcw.c


core_sam.o: core_sam.c core_sam.h cpu.h debug.h tape.h audio.h screen.h operaciones.h snap.h timer.h zxvision.h chardetect.h compileoptions.h contend.h ula.h utils.h audio.h utils.h tape.h cpc.h realjoystick.h settings.h ay38912.h
	$(CC) $(CFLAGS) -c core_sam.c

scmp.o: scmp.c scmp.h cpu.h operaciones.h
	$(CC) $(CFLAGS) -c scmp.c


timer.o: timer.c timer.h cpu.h start.h audio.h debug.h zxvision.h tape.h screen.h compileoptions.h zx8081.h joystick.h utils.h printers.h z88.h autoselectoptions.h zxuno.h textspeech.h mmc.h ide.h zxpand.h superupgrade.h snap.h snap_rzx.h ql.h esxdos_handler.h betadisk.h pd765.h settings.h ql_i8049.h cpc.h snap_ram.h hilow_datadrive.h dsk.h menu_items.h pcw.h
	$(CC) $(CFLAGS) -c timer.c


debug.o: debug.c cpu.h debug.h mem128.h timex.h screen.h zxvision.h zx8081.h operaciones.h core_spectrum.h core_reduced_spectrum.h core_zx8081.h core_z88.h core_ace.h core_cpc.h core_pcw.h core_msx.h core_svi.h core_coleco.h core_sg1000.h core_sms.h disassemble.h utils.h prism.h core_sam.h core_ql.h spectra.h tbblue.h zxuno.h ulaplus.h timex.h ay38912.h ula.h ql.h m68k.h superupgrade.h core_mk14.h scmp.h dandanator.h kartusho.h ifrom.h spritefinder.h multiface.h chloe.h cpc.h sam.h snap.h diviface.h betadisk.h zxevo.h tsconf.h baseconf.h remote.h charset.h settings.h datagear.h expression_parser.h atomic.h msx.h coleco.h sn76489an.h svi.h vdp_9918a.h ql_zx8302.h ide.h mmc.h esxdos_handler.h vdp_9918a_sms.h menu_debug_cpu.h transtape.h hilow_barbanegra.h pd765.h pcw.h
	$(CC) $(CFLAGS) -c debug.c

tape.o: tape.c tape.h cpu.h operaciones.h debug.h tape_tap.h tape_tzx.h tape_pzx.h tape_smp.h chloe.h prism.h mem128.h timex.h snap.h compileoptions.h screen.h zx8081.h zxvision.h snap_z81.h utils.h audio.h screen.h autoselectoptions.h zxuno.h timer.h superupgrade.h multiface.h chrome.h zxevo.h tsconf.h baseconf.h snap_spg.h tbblue.h settings.h msx.h samram.h menu_items.h zvfs.h hilow_barbanegra.h transtape.h dsk.h
	$(CC) $(CFLAGS) -c tape.c

tape_tap.o: tape_tap.c tape_tap.h tape.h cpu.h operaciones.h debug.h
	$(CC) $(CFLAGS) -c tape_tap.c

tape_smp.o: tape_smp.c tape_smp.h tape.h cpu.h operaciones.h debug.h zx8081.h snap.h zxvision.h snap_zx8081.h utils.h settings.h
	$(CC) $(CFLAGS) -c tape_smp.c

tape_tzx.o: tape_tzx.c tape_tzx.h tape.h cpu.h operaciones.h debug.h utils.h zvfs.h settings.h
	$(CC) $(CFLAGS) -c tape_tzx.c

tape_pzx.o: tape_pzx.c tape_pzx.h tape.h cpu.h operaciones.h debug.h utils.h zvfs.h settings.h snap.h
	$(CC) $(CFLAGS) -c tape_pzx.c

audio.o: audio.c audio.h cpu.h start.h debug.h screen.h utils.h zx8081.h audionull.h jupiterace.h autoselectoptions.h operaciones.h cpc.h settings.h audio_sine_table.h msx.h svi.h coleco.h sg1000.h sms.h sn76489an.h ql_i8049.h compileoptions.h zvfs.h menu_filesel.h
	$(CC) $(CFLAGS) -c audio.c

audio_sine_table.o: audio_sine_table.c audio_sine_table.h audio.h
	$(CC) $(CFLAGS) -c audio_sine_table.c

audionull.o: audionull.c audionull.h cpu.h debug.h audio.h settings.h
	$(CC) $(CFLAGS) -c audionull.c

ay38912.o: ay38912.c ay38912.h cpu.h audio.h joystick.h debug.h
	$(CC) $(CFLAGS) -c ay38912.c

sn76489an.o: sn76489an.c sn76489an.h cpu.h audio.h joystick.h debug.h
	$(CC) $(CFLAGS) -c sn76489an.c

vdp_9918a.o: vdp_9918a.c vdp_9918a.h cpu.h debug.h screen.h settings.h vdp_9918a_sms.h
	$(CC) $(CFLAGS) -c vdp_9918a.c

vdp_9918a_sms.o: vdp_9918a_sms.c vdp_9918a_sms.h vdp_9918a.h cpu.h debug.h screen.h settings.h 
	$(CC) $(CFLAGS) -c vdp_9918a_sms.c

msx.o: msx.c msx.h cpu.h debug.h vdp_9918a.h tape.h screen.h audio.h operaciones.h joystick.h settings.h
	$(CC) $(CFLAGS) -c msx.c

svi.o: svi.c svi.h cpu.h debug.h vdp_9918a.h tape.h screen.h audio.h operaciones.h joystick.h 
	$(CC) $(CFLAGS) -c svi.c  

coleco.o: coleco.c coleco.h cpu.h debug.h vdp_9918a.h tape.h screen.h audio.h sn76489an.h joystick.h vdp_9918a_sms.h
	$(CC) $(CFLAGS) -c coleco.c

sg1000.o: sg1000.c sg1000.h cpu.h debug.h vdp_9918a.h tape.h screen.h audio.h sn76489an.h joystick.h vdp_9918a_sms.h
	$(CC) $(CFLAGS) -c sg1000.c

sms.o: sms.c sms.h cpu.h debug.h vdp_9918a.h tape.h screen.h audio.h sn76489an.h joystick.h vdp_9918a_sms.h
	$(CC) $(CFLAGS) -c sms.c

saa_simul.o: saa_simul.c saa_simul.h ay38912.h cpu.h audio.h debug.h
	$(CC) $(CFLAGS) -c saa_simul.c

screen.o: screen.c screen.h cpu.h debug.h mem128.h chloe.h prism.h timex.h cpc.h prism.h operaciones.h zx8081.h charset.h zxvision.h menu_bitmaps.h audio.h contend.h ula.h tape_smp.h z88.h ulaplus.h zxuno.h spectra.h spritechip.h timer.h sam.h ql.h chrome.h zxevo.h tsconf.h baseconf.h mk14.h vdp_9918a.h msx.h coleco.h ql_zx8302.h stats.h vdp_9918a_sms.h menu_items.h chardetect.h pcw.h textspeech.h
	$(CC) $(CFLAGS) -c screen.c

mem128.o: mem128.c cpu.h mem128.h debug.h contend.h zxuno.h chloe.h prism.h timex.h sam.h ula.h tbblue.h superupgrade.h chrome.h zxevo.h tsconf.h baseconf.h msx.h coleco.h sg1000.h sms.h svi.h
	$(CC) $(CFLAGS) -c mem128.c

timex.o: timex.c timex.h cpu.h debug.h contend.h tape.h mem128.h zxvision.h chloe.h prism.h zxuno.h tbblue.h
	$(CC) $(CFLAGS) -c timex.c

chloe.o: chloe.c chloe.h cpu.h timex.h mem128.h debug.h contend.h zxuno.h timex.h prism.h 
	$(CC) $(CFLAGS) -c chloe.c

chrome.o: chrome.c chrome.h cpu.h mem128.h debug.h contend.h  
	$(CC) $(CFLAGS) -c chrome.c

zxevo.o: zxevo.c zxevo.h cpu.h mem128.h debug.h contend.h zxvision.h screen.h ula.h operaciones.h
	$(CC) $(CFLAGS) -c zxevo.c

tsconf.o: tsconf.c tsconf.h cpu.h mem128.h debug.h contend.h zxvision.h screen.h ula.h operaciones.h zxevo.h chardevice.h uartbridge.h
	$(CC) $(CFLAGS) -c tsconf.c

baseconf.o: baseconf.c baseconf.h cpu.h mem128.h debug.h contend.h zxvision.h screen.h ula.h operaciones.h zxevo.h
	$(CC) $(CFLAGS) -c baseconf.c

prism.o: prism.c prism.h cpu.h timex.h mem128.h debug.h contend.h zxuno.h timex.h utils.h zxvision.h
	$(CC) $(CFLAGS) -c prism.c

remote.o: remote.c remote.h cpu.h start.h debug.h utils.h compileoptions.h network.h ql.h disassemble.h zxvision.h menu_items.h audio.h timer.h screen.h ay38912.h charset.h diviface.h ula.h superupgrade.h tbblue.h zxevo.h tsconf.h baseconf.h operaciones.h snap.h kartusho.h ifrom.h settings.h datagear.h esxdos_handler.h assemble.h expression_parser.h joystick.h snap_zsf.h autoselectoptions.h zeng.h zeng_online.h ql_qdos_handler.h tape.h snap_ram.h mmc.h menu_debug_cpu.h atomic.h
	$(CC) $(CFLAGS) -c remote.c

network.o: network.c network.h cpu.h debug.h utils.h compileoptions.h chardevice.h atomic.h
	$(CC) $(CFLAGS) -c network.c

zeng.o: zeng.c zeng.h cpu.h debug.h utils.h network.h compileoptions.h remote.h snap_zsf.h autoselectoptions.h zeng_online_client.h
	$(CC) $(CFLAGS) -c zeng.c

zeng_online.o: zeng_online.c zeng_online.h cpu.h debug.h utils.h network.h compileoptions.h remote.h snap_zsf.h autoselectoptions.h ay38912.h atomic.h stats.h textspeech.h settings.h
	$(CC) $(CFLAGS) -c zeng_online.c

zeng_online_client.o: zeng_online_client.c zeng_online_client.h cpu.h debug.h utils.h network.h compileoptions.h remote.h snap_zsf.h zeng_online.h zeng.h stats.h screen.h timer.h autoselectoptions.h textspeech.h
	$(CC) $(CFLAGS) -c zeng_online_client.c

zvfs.o: zvfs.c zvfs.h cpu.h debug.h utils.h ff.h compileoptions.h
	$(CC) $(CFLAGS) -c zvfs.c

atomic.o: atomic.c atomic.h compileoptions.h
	$(CC) $(CFLAGS) -c atomic.c

scl2trd.o: scl2trd.c scl2trd.h debug.h utils.h zvfs.h
	$(CC) $(CFLAGS) -c scl2trd.c

zip.o: zip.c zip.h miniz.h debug.h 
	$(CC) $(CFLAGS) -c zip.c

diskio.o: diskio.c diskio.h ff.h ffconf.h utils.h
	$(CC) $(CFLAGS) -c diskio.c

ff.o: ff.c ff.h ffconf.h diskio.h 
	$(CC) $(CFLAGS) -c ff.c

ffsystem.o: ffsystem.c ffconf.h ff.h 
	$(CC) $(CFLAGS) -c ffsystem.c

ffunicode.o: ffunicode.c ffconf.h ff.h 
	$(CC) $(CFLAGS) -c ffunicode.c

stats.o: stats.c stats.h cpu.h zxvision.h compileoptions.h debug.h network.h screen.h timer.h
	$(CC) $(CFLAGS) -c stats.c

sensors.o: sensors.c sensors.h cpu.h debug.h ay38912.h screen.h zxvision.h timer.h stats.h audio.h sn76489an.h
	$(CC) $(CFLAGS) -c sensors.c

esxdos_handler.o: esxdos_handler.c esxdos_handler.h cpu.h operaciones.h debug.h utils.h diviface.h screen.h menu_filesel.h
	$(CC) $(CFLAGS) -c esxdos_handler.c

tbblue.o: tbblue.c tbblue.h cpu.h mem128.h debug.h contend.h utils.h zxvision.h divmmc.h diviface.h screen.h timex.h audio.h datagear.h ay38912.h multiface.h uartbridge.h settings.h joystick.h
	$(CC) $(CFLAGS) -c tbblue.c

zx8081.o: zx8081.c zx8081.h cpu.h screen.h debug.h audio.h core_zx8081.h operaciones.h zxvision.h ula.h
	$(CC) $(CFLAGS) -c zx8081.c

jupiterace.o: jupiterace.c jupiterace.h cpu.h screen.h debug.h audio.h core_ace.h operaciones.h zxvision.h
	$(CC) $(CFLAGS) -c jupiterace.c

z88.o: z88.c z88.h cpu.h screen.h debug.h core_z88.h contend.h joystick.h zxvision.h operaciones.h utils.h timer.h compileoptions.h
	$(CC) $(CFLAGS) -c z88.c

cpc.o: cpc.c cpc.h cpu.h screen.h debug.h core_cpc.h contend.h joystick.h zxvision.h operaciones.h utils.h ay38912.h tape.h dsk.h pd765.h
	$(CC) $(CFLAGS) -c cpc.c

pcw.o: pcw.c pcw.h cpu.h screen.h debug.h core_pcw.h contend.h joystick.h zxvision.h operaciones.h utils.h audio.h dsk.h pd765.h ula.h tape.h ay38912.h
	$(CC) $(CFLAGS) -c pcw.c

sam.o: sam.c sam.h cpu.h screen.h debug.h core_sam.h contend.h joystick.h zxvision.h operaciones.h utils.h
	$(CC) $(CFLAGS) -c sam.c

atomlite.o: atomlite.c atomlite.h cpu.h screen.h debug.h zxvision.h operaciones.h utils.h ide.h
	$(CC) $(CFLAGS) -c atomlite.c

zxuno.o: zxuno.c zxuno.h cpu.h debug.h contend.h mem128.h utils.h ula.h screen.h zxvision.h divmmc.h diviface.h ay38912.h ulaplus.h operaciones.h chloe.h chardevice.h uartbridge.h menu_items.h
	$(CC) $(CFLAGS) -c zxuno.c

#ql.o: 68000.c 68000_debug.c op68kadd.c op68karith.c op68ksub.c op68klogop.c op68kmisc.c op68kmove.c op68kshift.c 68000_additional.c ql.c
#	$(CC) $(CFLAGS) -c 68000.c 68000_debug.c op68kadd.c op68karith.c op68ksub.c op68klogop.c op68kmisc.c op68kmove.c op68kshift.c 68000_additional.c ql.c

ql.o: ql.c ql.h debug.h m68k.h utils.h zxvision.h operaciones.h settings.h ql_i8049.h ql_zx8302.h compileoptions.h
	$(CC) $(CFLAGS) -c ql.c

ql_qdos_handler.o: ql_qdos_handler.c ql_qdos_handler.h ql.h debug.h m68k.h utils.h zxvision.h operaciones.h settings.h ql_i8049.h ql_zx8302.h menu_items.h
	$(CC) $(CFLAGS) -c ql_qdos_handler.c

ql_i8049.o: ql_i8049.c ql_i8049.h debug.h utils.h ql.h audio.h
	$(CC) $(CFLAGS) -c ql_i8049.c

ql_zx8302.o: ql_zx8302.c ql_zx8302.h debug.h utils.h ql.h ql_i8049.h timer.h
	$(CC) $(CFLAGS) -c ql_zx8302.c


m68kcpu.o: m68kcpu.c
	$(CC) $(CFLAGS) -c m68kcpu.c

m68kdasm.o: m68kdasm.c
	$(CC) $(CFLAGS) -c m68kdasm.c

m68kops.o: m68kops.c
	$(CC) $(CFLAGS) -c m68kops.c

m68kopac.o: m68kopac.c
	$(CC) $(CFLAGS) -c m68kopac.c

m68kopdm.o: m68kopdm.c
	$(CC) $(CFLAGS) -c m68kopdm.c

m68kopnz.o: m68kopnz.c
	$(CC) $(CFLAGS) -c m68kopnz.c



snap.o: snap.c snap.h cpu.h debug.h operaciones.h zx8081.h mem128.h ay38912.h compileoptions.h autoselectoptions.h ay38912.h tape_smp.h audio.h screen.h zxvision.h tape.h snap_z81.h snap_zx8081.h snap_rzx.h utils.h ula.h joystick.h realjoystick.h z88.h chardetect.h jupiterace.h cpc.h timex.h zxuno.h ulaplus.h chloe.h prism.h diviface.h snap_rzx.h chrome.h zxevo.h tsconf.h baseconf.h snap_spg.h settings.h tbblue.h esxdos_handler.h
	$(CC) $(CFLAGS) -c snap.c

snap_zsf.o: snap_zsf.c snap_zsf.h cpu.h debug.h operaciones.h zx8081.h mem128.h ay38912.h compileoptions.h autoselectoptions.h ay38912.h tape_smp.h audio.h screen.h zxvision.h tape.h snap_z81.h snap_zx8081.h snap_rzx.h utils.h ula.h joystick.h realjoystick.h z88.h chardetect.h jupiterace.h cpc.h timex.h zxuno.h ulaplus.h chloe.h prism.h diviface.h snap_rzx.h chrome.h zxevo.h tsconf.h baseconf.h divmmc.h divide.h tbblue.h msx.h vdp_9918a.h coleco.h sg1000.h sms.h sn76489an.h m68k.h ql_zx8302.h ql_i8049.h vdp_9918a_sms.h settings.h scmp.h mk14.h chrome.h sam.h pcw.h zeng_online_client.h
	$(CC) $(CFLAGS) -c snap_zsf.c

snap_ram.o: snap_ram.c snap_ram.h cpu.h debug.h operaciones.h snap_zsf.h zxvision.h autoselectoptions.h
	$(CC) $(CFLAGS) -c snap_ram.c

snap_z81.o: snap_z81.c snap_z81.h cpu.h debug.h operaciones.h snap.h
	$(CC) $(CFLAGS) -c snap_z81.c

snap_spg.o: snap_spg.c snap_spg.h cpu.h debug.h operaciones.h snap.h mem128.h tsconf.h
	$(CC) $(CFLAGS) -c snap_spg.c

spg_depack.o: spg_depack.c
	$(CC) $(CFLAGS) -c spg_depack.c

snap_zx8081.o: snap_zx8081.c snap_zx8081.h cpu.h debug.h operaciones.h zx8081.h audio.h screen.h tape.h tape_smp.h snap_z81.h zxvision.h snap.h utils.h
	$(CC) $(CFLAGS) -c snap_zx8081.c

snap_rzx.o: snap_rzx.c snap_rzx.h snap.h cpu.h debug.h operaciones.h utils.h zxvision.h screen.h
	$(CC) $(CFLAGS) -c snap_rzx.c

zxvision.o: zxvision.c zxvision.h menu_items.h menu_items_settings.h menu_bitmaps.h menu_debug_cpu.h menu_file_viewer_browser.h screen.h cpu.h start.h debug.h ay38912.h tape.h audio.h timer.h operaciones.h utils.h joystick.h ula.h realjoystick.h scrstdout.h autoselectoptions.h charset.h chardetect.h textspeech.h prism.h cpc.h sam.h tbblue.h remote.h tsconf.h settings.h stats.h network.h ql.h zvfs.h menu_filesel.h pd765.h dsk.h zeng_online_client.h
	$(CC) $(CFLAGS) -c zxvision.c

menu_filesel.o: menu_filesel.c menu_filesel.h zxvision.h menu_file_viewer_browser.h screen.h cpu.h debug.h timer.h utils.h compileoptions.h ff.h diskio.h zvfs.h snap.h joystick.h textspeech.h network.h ula.h
	$(CC) $(CFLAGS) -c menu_filesel.c

menu_items.o: menu_items.c menu_items.h zxvision.h menu_items_settings.h menu_debug_cpu.h menu_zeng_online.h menu_file_viewer_browser.h screen.h cpu.h start.h debug.h zx8081.h ay38912.h compileoptions.h tape.h audio.h timer.h snap.h operaciones.h disassemble.h utils.h contend.h joystick.h ula.h printers.h realjoystick.h scrstdout.h z88.h ulaplus.h autoselectoptions.h zxuno.h charset.h chardetect.h textspeech.h  mmc.h ide.h divmmc.h divide.h diviface.h zxpand.h spectra.h spritechip.h jupiterace.h timex.h chloe.h cpc.h prism.h sam.h if1.h pd765.h atomlite.h tbblue.h dandanator.h kartusho.h ifrom.h spritefinder.h multiface.h superupgrade.h m68k.h remote.h snap_rzx.h multiface.h scmp.h esxdos_handler.h zxevo.h tsconf.h baseconf.h snap_spg.h betadisk.h tape_tzx.h snap_zsf.h settings.h datagear.h assemble.h expression_parser.h uartbridge.h zeng.h zeng_online.h network.h stats.h vdp_9918a.h msx.h coleco.h sg1000.h sms.h svi.h sn76489an.h ql_qdos_handler.h ql_i8049.h gs.h zvfs.h vdp_9918a_sms.h snap_ram.h sensors.h samram.h hilow_datadrive.h menu_filesel.h menu_bitmaps.h utils_text_adventure.h salamanquesa.h hilow_datadrive_audio.h hilow_barbanegra.h transtape.h mhpokeador.h specmate.h phoenix.h defcon.h ramjet.h interface007.h dinamid3.h dsk.h plus3dos_handler.h pcw.h 
	$(CC) $(CFLAGS) -c menu_items.c

menu_file_viewer_browser.o: menu_file_viewer_browser.c zxvision.h compileoptions.h screen.h cpu.h debug.h settings.h zvfs.h snap.h tape_tzx.h msx.h snap_spg.h snap_zsf.h hilow_datadrive.h menu_items.h
	$(CC) $(CFLAGS) -c menu_file_viewer_browser.c

menu_zeng_online.o: menu_zeng_online.c zxvision.h menu_items.h compileoptions.h screen.h cpu.h debug.h network.h zeng_online_client.h zeng_online.h
	$(CC) $(CFLAGS) -c menu_zeng_online.c

menu_items_settings.o: menu_items_settings.c menu_items_settings.h zxvision.h menu_file_viewer_browser.h screen.h cpu.h start.h debug.h zx8081.h ay38912.h compileoptions.h tape.h audio.h timer.h snap.h operaciones.h disassemble.h utils.h contend.h joystick.h ula.h printers.h realjoystick.h scrstdout.h z88.h ulaplus.h autoselectoptions.h zxuno.h charset.h chardetect.h textspeech.h  mmc.h ide.h divmmc.h divide.h diviface.h zxpand.h spectra.h spritechip.h jupiterace.h timex.h chloe.h cpc.h prism.h sam.h if1.h pd765.h atomlite.h tbblue.h dandanator.h kartusho.h ifrom.h spritefinder.h superupgrade.h m68k.h remote.h snap_rzx.h multiface.h scmp.h esxdos_handler.h zxevo.h tsconf.h baseconf.h snap_spg.h betadisk.h tape_tzx.h snap_zsf.h settings.h datagear.h assemble.h expression_parser.h uartbridge.h zeng.h zeng_online.h network.h stats.h vdp_9918a.h msx.h coleco.h sg1000.h sms.h svi.h sn76489an.h ql_qdos_handler.h ql_i8049.h gs.h zvfs.h vdp_9918a_sms.h snap_ram.h sensors.h samram.h snap_zx8081.h menu_bitmaps.h menu_filesel.h menu_debug_cpu.h pcw.h utils_text_adventure.h
	$(CC) $(CFLAGS) -c menu_items_settings.c

menu_debug_cpu.o: menu_debug_cpu.c menu_debug_cpu.h zxvision.h cpu.h debug.h scmp.h m68k.h zx8081.h z88.h settings.h operaciones.h screen.h joystick.h tbblue.h ula.h timer.h audio.h prism.h menu_items.h menu_filesel.h disassemble.h ay38912.h realjoystick.h utils_text_adventure.h
	$(CC) $(CFLAGS) -c menu_debug_cpu.c

menu_bitmaps.o: menu_bitmaps.c menu_bitmaps.h settings.h
	$(CC) $(CFLAGS) -c menu_bitmaps.c 

salamanquesa.o: salamanquesa.c salamanquesa.h
	$(CC) $(CFLAGS) -c salamanquesa.c 

settings.o: settings.c settings.h menu_items.h zxvision.h screen.h cpu.h debug.h zx8081.h ay38912.h compileoptions.h tape.h audio.h timer.h snap.h operaciones.h disassemble.h utils.h contend.h joystick.h ula.h printers.h realjoystick.h scrstdout.h z88.h ulaplus.h autoselectoptions.h zxuno.h charset.h chardetect.h textspeech.h  mmc.h ide.h divmmc.h divide.h diviface.h zxpand.h spectra.h spritechip.h jupiterace.h timex.h chloe.h cpc.h prism.h sam.h if1.h pd765.h atomlite.h tbblue.h dandanator.h kartusho.h ifrom.h spritefinder.h multiface.h superupgrade.h m68k.h remote.h snap_rzx.h multiface.h scmp.h esxdos_handler.h zxevo.h tsconf.h baseconf.h snap_spg.h betadisk.h tape_tzx.h snap_zsf.h datagear.h
	$(CC) $(CFLAGS) -c settings.c

disassemble.o: disassemble.c disassemble.h cpu.h operaciones.h debug.h ql.h utils.h scmp.h zxvision.h tbblue.h utils_text_adventure.h menu_debug_cpu.h
	$(CC) $(CFLAGS) -c disassemble.c

utils.o: utils.c utils.h cpu.h start.h debug.h joystick.h compileoptions.h tape.h snap.h screen.h realjoystick.h zxvision.h z88.h playtzx.h tape_tzx.h tape_pzx.h operaciones.h zx8081.h autoselectoptions.h ulaplus.h ay38912.h textspeech.h spectra.h zxuno.h spritechip.h timex.h cpc.h sam.h divmmc.h divide.h superupgrade.h chardetect.h zx8081.h jupiterace.h mmc.h ide.h zxpand.h diviface.h divmmc.h divide.h dandanator.h kartusho.h ifrom.h spritefinder.h ql.h m68k.h remote.h ula.h snap_rzx.h scmp.h mk14.h esxdos_handler.h tbblue.h zxevo.h tsconf.h baseconf.h mdvtool.h betadisk.h pd765.h settings.h datagear.h zeng.h zeng_online.h network.h stats.h scl2trd.h zip.h msx.h coleco.h sg1000.h sms.h svi.h charset.h snap_zsf.h ql_qdos_handler.h ql_i8049.h samram.h ff.h diskio.h ffconf.h zvfs.h snap_ram.h menu_items.h tape_smp.h menu_file_viewer_browser.h menu_filesel.h utils_text_adventure.h menu_debug_cpu.h hilow_datadrive.h hilow_datadrive_audio.h transtape.h mhpokeador.h specmate.h phoenix.h defcon.h ramjet.h interface007.h dinamid3.h dsk.h plus3dos_handler.h pcw.h menu_bitmaps.h zeng_online_client.h zeng_online.h
	$(CC) $(CFLAGS) -c utils.c

utils_text_adventure.o: utils_text_adventure.c utils_text_adventure.h utils.h cpu.h debug.h compileoptions.h operaciones.h cpc.h screen.h menu_items.h
	$(CC) $(CFLAGS) -c utils_text_adventure.c

playtzx.o: playtzx.c playtzx.h debug.h audio.h utils.h
	$(CC) $(CFLAGS) -c playtzx.c

mdvtool.o: mdvtool.c mdvtool.h debug.h utils.h ay38912.h
	$(CC) $(CFLAGS) -c mdvtool.c

contend.o: contend.c contend.h cpu.h debug.h screen.h compileoptions.h ulaplus.h zxuno.h ula.h tbblue.h
	$(CC) $(CFLAGS) -c contend.c

joystick.o: joystick.c joystick.h cpu.h debug.h screen.h zxvision.h zeng.h zeng_online.h
	$(CC) $(CFLAGS) -c joystick.c

ula.o: ula.c ula.h cpu.h start.h debug.h screen.h contend.h zxvision.h multiface.h betadisk.h settings.h divmmc.c hilow_datadrive.h samram.h hilow_barbanegra.h transtape.h mhpokeador.h specmate.h phoenix.h defcon.h ramjet.h interface007.h dinamid3.h
	$(CC) $(CFLAGS) -c ula.c

mmc.o: mmc.c mmc.h cpu.h debug.h utils.h zxvision.h screen.h divmmc.h compileoptions.h operaciones.h menu_items.h
	$(CC) $(CFLAGS) -c mmc.c

ide.o: ide.c ide.h cpu.h debug.h utils.h zxvision.h screen.h divide.h menu_items.h
	$(CC) $(CFLAGS) -c ide.c

pd765.o: pd765.c pd765.h cpu.h debug.h utils.h dsk.h menu_items.h screen.h settings.h pcw.h
	$(CC) $(CFLAGS) -c pd765.c

dsk.o: dsk.c dsk.h cpu.h debug.h utils.h tape.h menu_items.h screen.h pd765.h settings.h timer.h
	$(CC) $(CFLAGS) -c dsk.c

plus3dos_handler.o: plus3dos_handler.c plus3dos_handler.h cpu.h debug.h utils.h operaciones.h mem128.h dsk.h
	$(CC) $(CFLAGS) -c plus3dos_handler.c

zxpand.o: zxpand.c zxpand.h mmc.h cpu.h debug.h utils.h zxvision.h screen.h zx8081.h joystick.h menu_items.h
	$(CC) $(CFLAGS) -c zxpand.c

dandanator.o: dandanator.c dandanator.h cpu.h debug.h utils.h operaciones.h ula.h audio.h screen.h menu_items.h
	$(CC) $(CFLAGS) -c dandanator.c

gs.o: gs.c gs.h cpu.h debug.h utils.h operaciones.h contend.h audio.h
	$(CC) $(CFLAGS) -c gs.c

betadisk.o: betadisk.c betadisk.h cpu.h debug.h utils.h operaciones.h ula.h mem128.h screen.h tsconf.h tape.h menu_items.h
	$(CC) $(CFLAGS) -c betadisk.c

codetests.o: codetests.c codetests.h cpu.h debug.h utils.h operaciones.h ula.h mem128.h screen.h tbblue.h assemble.h expression_parser.h audio.h zeng.h zeng_online.h network.h settings.h atomic.h
	$(CC) $(CFLAGS) -c codetests.c

assemble.o: assemble.c assemble.h cpu.h debug.h utils.h
	$(CC) $(CFLAGS) -c assemble.c

chardevice.o: chardevice.c chardevice.h cpu.h debug.h 
	$(CC) $(CFLAGS) -c chardevice.c

uartbridge.o: uartbridge.c uartbridge.h cpu.h debug.h utils.h chardevice.h screen.h
	$(CC) $(CFLAGS) -c uartbridge.c

expression_parser.o: expression_parser.c expression_parser.h cpu.h debug.h utils.h operaciones.h screen.h mem128.h scmp.h m68k.h prism.h tbblue.h hilow_datadrive.h pd765.h superupgrade.h
	$(CC) $(CFLAGS) -c expression_parser.c

kartusho.o: kartusho.c kartusho.h cpu.h debug.h utils.h operaciones.h ula.h
	$(CC) $(CFLAGS) -c kartusho.c

samram.o: samram.c samram.h cpu.h debug.h utils.h operaciones.h ula.h joystick.h
	$(CC) $(CFLAGS) -c samram.c

ifrom.o: ifrom.c ifrom.h cpu.h debug.h utils.h operaciones.h ula.h
	$(CC) $(CFLAGS) -c ifrom.c

hilow_datadrive.o: hilow_datadrive.c hilow_datadrive.h cpu.h debug.h utils.h operaciones.h ula.h screen.h menu_items.h mem128.h compileoptions.h
	$(CC) $(CFLAGS) -c hilow_datadrive.c

hilow_barbanegra.o: hilow_barbanegra.c hilow_barbanegra.h cpu.h debug.h utils.h operaciones.h mem128.h
	$(CC) $(CFLAGS) -c hilow_barbanegra.c

transtape.o: transtape.c transtape.h cpu.h debug.h utils.h operaciones.h mem128.h
	$(CC) $(CFLAGS) -c transtape.c

mhpokeador.o: mhpokeador.c mhpokeador.h cpu.h debug.h utils.h operaciones.h
	$(CC) $(CFLAGS) -c mhpokeador.c

specmate.o: specmate.c specmate.h cpu.h debug.h utils.h operaciones.h
	$(CC) $(CFLAGS) -c specmate.c

interface007.o: interface007.c interface007.h cpu.h debug.h utils.h operaciones.h
	$(CC) $(CFLAGS) -c interface007.c

dinamid3.o: dinamid3.c dinamid3.h cpu.h debug.h utils.h operaciones.h
	$(CC) $(CFLAGS) -c dinamid3.c

phoenix.o: phoenix.c phoenix.h cpu.h debug.h utils.h operaciones.h
	$(CC) $(CFLAGS) -c phoenix.c

defcon.o: defcon.c defcon.h cpu.h debug.h utils.h operaciones.h
	$(CC) $(CFLAGS) -c defcon.c

ramjet.o: ramjet.c ramjet.h cpu.h debug.h utils.h operaciones.h
	$(CC) $(CFLAGS) -c ramjet.c

datagear.o: datagear.c datagear.h cpu.h debug.h utils.h operaciones.h ula.h
	$(CC) $(CFLAGS) -c datagear.c

spritefinder.o: spritefinder.c spritefinder.h cpu.h debug.h utils.h operaciones.h ula.h screen.h
	$(CC) $(CFLAGS) -c spritefinder.c

multiface.o: multiface.c multiface.h cpu.h debug.h utils.h operaciones.h
	$(CC) $(CFLAGS) -c multiface.c

superupgrade.o: superupgrade.c superupgrade.h cpu.h debug.h utils.h operaciones.h mem128.h zxvision.h screen.h
	$(CC) $(CFLAGS) -c superupgrade.c

spectra.o: spectra.c spectra.h cpu.h debug.h utils.h zxvision.h screen.h operaciones.h mem128.h ulaplus.h
	$(CC) $(CFLAGS) -c spectra.c

spritechip.o: spritechip.c spritechip.h cpu.h debug.h utils.h screen.h ula.h ulaplus.h mem128.h
	$(CC) $(CFLAGS) -c spritechip.c

divmmc.o: divmmc.c divmmc.h divide.h diviface.h cpu.h debug.h utils.h
	$(CC) $(CFLAGS) -c divmmc.c

divide.o: divide.c divide.h divmmc.h diviface.h cpu.h debug.h utils.h
	$(CC) $(CFLAGS) -c divide.c

diviface.o: diviface.c diviface.h cpu.h debug.h utils.h zxvision.h screen.h operaciones.h zxuno.h contend.h prism.h tbblue.h tsconf.h
	$(CC) $(CFLAGS) -c diviface.c

if1.o: if1.c if1.h cpu.h debug.h utils.h operaciones.h zxvision.h
	$(CC) $(CFLAGS) -c if1.c

ds1307.o: ds1307.c ds1307.h cpu.h debug.h utils.h operaciones.h zxvision.h
	$(CC) $(CFLAGS) -c ds1307.c

printers.o: printers.c printers.h cpu.h debug.h utils.h screen.h zxvision.h
	$(CC) $(CFLAGS) -c printers.c

realjoystick.o: realjoystick.c realjoystick.h cpu.h debug.h joystick.h zxvision.h utils.h  screen.h compileoptions.h snap_ram.h
	$(CC) $(CFLAGS) -c realjoystick.c

ulaplus.o: ulaplus.c ulaplus.h cpu.h debug.h screen.h spectra.h zxvision.h
	$(CC) $(CFLAGS) -c ulaplus.c

autoselectoptions.o: autoselectoptions.c autoselectoptions.h debug.h zx8081.h cpu.h screen.h joystick.h tape.h realjoystick.h ulaplus.h zxvision.h utils.h chardetect.h
	$(CC) $(CFLAGS) -c autoselectoptions.c

chardetect.o: chardetect.c chardetect.h cpu.h operaciones.h debug.h screen.h textspeech.h disassemble.h zxvision.h settings.h utils_text_adventure.h 
	$(CC) $(CFLAGS) -c chardetect.c

textspeech.o: textspeech.c textspeech.h cpu.h operaciones.h debug.h screen.h chardetect.h zxvision.h utils.h sam.h
	$(CC) $(CFLAGS) -c textspeech.c


hilow_datadrive_audio.o: hilow_datadrive_audio.c
	$(CC) $(CFLAGS) -c hilow_datadrive_audio.c


clean:
	rm -f *.o zesarux zesarux.exe smpatap sp_z80 tapabin bin_sprite_to_c leezx81 lee_hilow_datadrive_audio file_to_eprom bmp_to_prism_4_planar bmp_to_sprite spedtotxt install.sh 
	rm -fR bintargztemp/ sourcetargztemp/ ZEsarUX_win-$(EMULATOR_VERSION)/
	rm -fR macos/zesarux.app
	rm -f macos/zesarux-noncompressed.dmg
	rm -f macos/zesarux-noncompressed.dmg.gz
	rm -f macos/ZEsarUX_macos-$(EMULATOR_VERSION).dmg
	rm -f ZEsarUX_Darwin-$(EMULATOR_VERSION)_arm64.tar.gz
	rm -f ZEsarUX_src-$(EMULATOR_VERSION).tar.gz
	rm -f ZEsarUX_win-$(EMULATOR_VERSION).zip
	rm -f ZEsarUX_extras-$(EMULATOR_VERSION).zip

COMMONFILES=ACKNOWLEDGEMENTS LICENSE LICENSES_info Changelog Cambios TODO* README HISTORY FEATURES FEATURES_es EXCLUSIVEFEATURES INSTALL INSTALLWINDOWS ALTERNATEROMS INCLUDEDTAPES DONATE DONORS FAQ *.odt mantransfev3.bin *.rom zxuno.flash tbblue.mmc pcw_8x_boot*dsk zesarux.mp3 zesarux.xcf editionnamegame.* bin_sprite_to_c.sh keyboard_*.bmp z88_shortcuts.bmp zesarux.pdf docs licenses my_soft speech_filters text_image_filters

ONLYSOURCEFILES=icons_buttons macos patches tests *.c *.m *.h *.tpl DEVELOPMENT CHECKLIST configure *.sh *.asm benchmark_*.txt current_checklist.txt prism_change_boot.txt Dockerfile*



ONLYUNIXBINARIES=install.sh zesarux
ONLYWINBINARIES=zesarux.exe SDL.dll pthreadGC2.dll pthreadGC-3.dll libgcc_s_dw2-1.dll libcrypto-1_1.dll libssl-1_1.dll

sourcetargz:
	rm -fR sourcetargztemp
	mkdir -p sourcetargztemp/ZEsarUX-$(EMULATOR_VERSION)
	cp -a $(COMMONFILES) $(ONLYSOURCEFILES) sourcetargztemp/ZEsarUX-$(EMULATOR_VERSION)/
	tar -C sourcetargztemp -cvzf ZEsarUX_src-$(EMULATOR_VERSION).tar.gz ZEsarUX-$(EMULATOR_VERSION)
	echo
	echo "Generated file is : ZEsarUX_src-$(EMULATOR_VERSION).tar.gz"

backupsrc:
	rm -fR backupsrctemp
	mkdir -p backupsrctemp/ZEsarUX-$(EMULATOR_VERSION)
	cp -a $(ONLYSOURCEFILES) backupsrctemp/ZEsarUX-$(EMULATOR_VERSION)/
	tar -C backupsrctemp -cvzf ZEsarUX_backupsrc-$(EMULATOR_VERSION).tar.gz ZEsarUX-$(EMULATOR_VERSION)
	echo
	echo "Generated file is : ZEsarUX_backupsrc-$(EMULATOR_VERSION).tar.gz"

bintargz: all
	./generate_install_sh.sh
	rm -fR bintargztemp
	mkdir -p bintargztemp/ZEsarUX-$(EMULATOR_VERSION)
	cp -a $(COMMONFILES) $(ONLYUNIXBINARIES) bintargztemp/ZEsarUX-$(EMULATOR_VERSION)/
	tar -C bintargztemp -cvzf ZEsarUX_Darwin-$(EMULATOR_VERSION)_arm64.tar.gz ZEsarUX-$(EMULATOR_VERSION)
	echo
	echo "Generated file is : ZEsarUX_Darwin-$(EMULATOR_VERSION)_arm64.tar.gz"


rpi: all
	./generate_install_sh.sh
	rm -fR bintargztemp
	mkdir -p bintargztemp/ZEsarUX-$(EMULATOR_VERSION)
	cp -a $(COMMONFILES) $(ONLYUNIXBINARIES) bintargztemp/ZEsarUX-$(EMULATOR_VERSION)/
	tar -C bintargztemp -cvzf ZEsarUX_raspberrypios-framebuffer-$(EMULATOR_VERSION)_arm64.tar.gz ZEsarUX-$(EMULATOR_VERSION)
	echo
	echo "Generated file is : ZEsarUX_raspberrypios-framebuffer-$(EMULATOR_VERSION)_arm64.tar.gz"


debian32: all
	./generate_install_sh.sh
	rm -fR bintargztemp
	mkdir -p bintargztemp/ZEsarUX-$(EMULATOR_VERSION)
	cp -a $(COMMONFILES) $(ONLYUNIXBINARIES) bintargztemp/ZEsarUX-$(EMULATOR_VERSION)/
	tar -C bintargztemp -cvzf ZEsarUX_linux-$(EMULATOR_VERSION)-debian11_i686.tar.gz ZEsarUX-$(EMULATOR_VERSION)
	echo
	echo "Generated file is : ZEsarUX_linux-$(EMULATOR_VERSION)-debian11_i686.tar.gz"


debian64: all
	./generate_install_sh.sh
	rm -fR bintargztemp
	mkdir -p bintargztemp/ZEsarUX-$(EMULATOR_VERSION)
	cp -a $(COMMONFILES) $(ONLYUNIXBINARIES) bintargztemp/ZEsarUX-$(EMULATOR_VERSION)/
	tar -C bintargztemp -cvzf ZEsarUX_linux-$(EMULATOR_VERSION)-debian11_x86_64.tar.gz ZEsarUX-$(EMULATOR_VERSION)
	echo
	echo "Generated file is : ZEsarUX_linux-$(EMULATOR_VERSION)-debian11_x86_64.tar.gz"


freebsd: all
	./generate_install_sh.sh
	rm -fR bintargztemp
	mkdir -p bintargztemp/ZEsarUX-$(EMULATOR_VERSION)
	cp -a $(COMMONFILES) $(ONLYUNIXBINARIES) bintargztemp/ZEsarUX-$(EMULATOR_VERSION)/
	tar -C bintargztemp -cvzf ZEsarUX_freebsd-$(EMULATOR_VERSION)-freebsd12_amd64.tar.gz ZEsarUX-$(EMULATOR_VERSION)
	echo
	echo "Generated file is : ZEsarUX_freebsd-$(EMULATOR_VERSION)-freebsd12_amd64.tar.gz"


ubuntu: 
	./docker-zesarux.sh build-version-and-get-binary ubuntu
	mv zesarux.ubuntu zesarux
	mv install.sh.ubuntu install.sh
	rm -fR bintargztemp
	mkdir -p bintargztemp/ZEsarUX-$(EMULATOR_VERSION)
	cp -a $(COMMONFILES) $(ONLYUNIXBINARIES) bintargztemp/ZEsarUX-$(EMULATOR_VERSION)/
	tar -C bintargztemp -cvzf ZEsarUX_linux-$(EMULATOR_VERSION)-ubuntu22_x86_64.tar.gz ZEsarUX-$(EMULATOR_VERSION)
	rm zesarux install.sh
	echo
	echo "Generated file is : ZEsarUX_linux-$(EMULATOR_VERSION)-ubuntu22_x86_64.tar.gz"


fedora: 
	./docker-zesarux.sh build-version-and-get-binary fedora
	mv zesarux.fedora zesarux
	mv install.sh.fedora install.sh
	rm -fR bintargztemp
	mkdir -p bintargztemp/ZEsarUX-$(EMULATOR_VERSION)
	cp -a $(COMMONFILES) $(ONLYUNIXBINARIES) bintargztemp/ZEsarUX-$(EMULATOR_VERSION)/
	tar -C bintargztemp -cvzf ZEsarUX_linux-$(EMULATOR_VERSION)-fedora38_x86_64.tar.gz ZEsarUX-$(EMULATOR_VERSION)
	rm zesarux install.sh
	echo
	echo "Generated file is : ZEsarUX_linux-$(EMULATOR_VERSION)-fedora38_x86_64.tar.gz"


#just for testing right now
debiandocker:
	./docker-zesarux.sh build-version-and-get-binary debian
	mv zesarux.debian zesarux
	mv install.sh.debian install.sh
	rm -fR bintargztemp
	mkdir -p bintargztemp/ZEsarUX-$(EMULATOR_VERSION)
	cp -a $(COMMONFILES) $(ONLYUNIXBINARIES) bintargztemp/ZEsarUX-$(EMULATOR_VERSION)/
	tar -C bintargztemp -cvzf ZEsarUX_linux-$(EMULATOR_VERSION)-debian11_x86_64.tar.gz ZEsarUX-$(EMULATOR_VERSION)
	echo
	echo "Generated file is : ZEsarUX_linux-$(EMULATOR_VERSION)-debian11_x86_64.tar.gz"


extra_files:
	echo "Run the following: cd ../../zesarux-extras/ && zip -r /tmp/ZEsarUX_extras-$(EMULATOR_VERSION).zip *"
	echo "Generated file will be: /tmp/ZEsarUX_extras-$(EMULATOR_VERSION).zip"

windows:
	mkdir -p ZEsarUX_win-$(EMULATOR_VERSION)
	cp -a $(COMMONFILES) $(ONLYWINBINARIES) ZEsarUX_win-$(EMULATOR_VERSION)/
	zip -r ZEsarUX_win-$(EMULATOR_VERSION).zip ZEsarUX_win-$(EMULATOR_VERSION)/
	echo
	echo "Generated file is: ZEsarUX_win-$(EMULATOR_VERSION).zip"

macapp: all
	mkdir -p macos/zesarux.app
	cp -r macos/apptemplate/* macos/zesarux.app/
	cp zesarux macos/zesarux.app/Contents/MacOS/zesarux
	cp -a $(COMMONFILES) macos/zesarux.app/Contents/Resources/
	rm -f macos/zesarux-noncompressed.dmg
	rm -f macos/zesarux-noncompressed.dmg.gz
	rm -f macos/ZEsarUX_macos-$(EMULATOR_VERSION).dmg
	hdiutil create -megabytes 128 -fs HFS+ -volname ZEsarUX macos/zesarux-noncompressed.dmg
	hdiutil attach -mountpoint macos/tempmount macos/zesarux-noncompressed.dmg
	cp -R macos/zesarux.app macos/tempmount
	ln -s /Applications/ macos/tempmount/Applications
	sleep 5
	hdiutil detach macos/tempmount
	#gzip macos/zesarux-noncompressed.dmg
	#UDBZ - UDIF bzip2-compressed image (Mac OS X 10.4+ only)
	hdiutil convert macos/zesarux-noncompressed.dmg -format UDBZ -o macos/ZEsarUX_macos-$(EMULATOR_VERSION).dmg
	rm -f macos/zesarux-noncompressed.dmg
	echo "Generated file is: macos/ZEsarUX_macos-$(EMULATOR_VERSION).dmg"


#CC32=gcc $(CFLAGS) -m32
#CC64=gcc $(CFLAGS) -m64

#UTILS32=smpatap_x32 sp_z80_x32 tapabin_x32 leezx81_x32
#UTILS64=smpatap_x64 sp_z80_x64 tapabin_x64 leezx81_x64

#utilities32: $(UTILS32)

#utilities64: $(UTILS64)


#smpatap_x32: smpatap_unix.c
#	$(CC32) $(CFLAGS) smpatap_unix.c -o smpatap_x32

#smpatap_x64: smpatap_unix.c
#	$(CC64) $(CFLAGS) smpatap_unix.c -o smpatap_x64

#leezx81_x32: leezx81_unix.c
#	$(CC32) $(CFLAGS) leezx81_unix.c -o leezx81_x32

#leezx81_x64: leezx81_unix.c
#	$(CC64) $(CFLAGS) leezx81_unix.c -o leezx81_x64

#sp_z80_x32: sp_z80_unix.c
#	$(CC32) $(CFLAGS) sp_z80_unix.c -o sp_z80_x32

#sp_z80_x64: sp_z80_unix.c
#	$(CC64) $(CFLAGS) sp_z80_unix.c -o sp_z80_x64

#tapabin_x32: tapabin_unix.c
#	$(CC32) $(CFLAGS) tapabin_unix.c -o tapabin_x32

#tapabin_x64: tapabin_unix.c
#	$(CC64) $(CFLAGS) tapabin_unix.c -o tapabin_x64


#UTILITIES=smpatap sp_z80 tapabin leezx81


install: all
	./generate_install_sh.sh
	./install.sh

#utilities: $(UTILITIES)
utilities: smpatap sp_z80 tapabin leezx81 file_to_eprom bmp_to_prism_4_planar bmp_to_sprite spedtotxt bin_sprite_to_c lee_hilow_datadrive_audio


main_lee_hilow_datadrive_audio.o: main_lee_hilow_datadrive_audio.c hilow_datadrive_audio.h
	$(CC) $(CFLAGS) -c main_lee_hilow_datadrive_audio.c

lee_hilow_datadrive_audio: main_lee_hilow_datadrive_audio.o hilow_datadrive_audio.o
	$(CC) $(CFLAGS) main_lee_hilow_datadrive_audio.o hilow_datadrive_audio.o -o lee_hilow_datadrive_audio


spedtotxt: spedtotxt.c
	$(CC) $(CFLAGS) spedtotxt.c -o spedtotxt

smpatap: smpatap_unix.c
	$(CC) $(CFLAGS) smpatap_unix.c -o smpatap

leezx81: leezx81_unix.c
	$(CC) $(CFLAGS) leezx81_unix.c -o leezx81

sp_z80: sp_z80_unix.c
	$(CC) $(CFLAGS) sp_z80_unix.c -o sp_z80

tapabin: tapabin_unix.c
	$(CC) $(CFLAGS) tapabin_unix.c -o tapabin

file_to_eprom: file_to_eprom.c
	$(CC) $(CFLAGS) file_to_eprom.c -o file_to_eprom

bmp_to_prism_4_planar: bmp_to_prism_4_planar.c
	$(CC) $(CFLAGS) bmp_to_prism_4_planar.c -o bmp_to_prism_4_planar

bmp_to_sprite: bmp_to_sprite.c
	$(CC) $(CFLAGS) bmp_to_sprite.c -o bmp_to_sprite

bin_sprite_to_c: bin_sprite_to_c.c
	$(CC) $(CFLAGS) bin_sprite_to_c.c -o bin_sprite_to_c

scrcocoa.o: scrcocoa.m joystick.h compileoptions.h cpu.h start.h screen.h charset.h debug.h utils.h timer.h zxvision.h cpc.h prism.h sam.h ql.h settings.h msx.h svi.h coleco.h sg1000.h sms.h realjoystick.h pcw.h
	clang scrcocoa.m -c -o scrcocoa.o

scrstdout.o: scrstdout.c scrstdout.h debug.h screen.h mem128.h zx8081.h operaciones.h cpu.h utils.h zxvision.h joystick.h ula.h disassemble.h z88.h timer.h chardetect.h textspeech.h tsconf.h baseconf.h settings.h msx.h svi.h coleco.h sg1000.h sms.h zeng_online_client.h
	$(CC) $(CFLAGS) -c scrstdout.c

scrsimpletext.o: scrsimpletext.c scrsimpletext.h debug.h screen.h mem128.h zx8081.h operaciones.h cpu.h utils.h zxvision.h joystick.h ula.h disassemble.h z88.h timer.h tsconf.h baseconf.h settings.h textspeech.h msx.h svi.h coleco.h sg1000.h sms.h
	$(CC) $(CFLAGS) -c scrsimpletext.c

scrcurses.o: scrcurses.c cpu.h scrcurses.h compileoptions.h operaciones.h mem128.h charset.h debug.h zx8081.h screen.h audio.h zxvision.h utils.h joystick.h ula.h z88.h sam.h charset.h tsconf.h baseconf.h settings.h chloe.h timex.h msx.h svi.h coleco.h sg1000.h sms.h zeng.h zeng_online.h zeng_online_client.h
	$(CC) $(CFLAGS) -c scrcurses.c

scrxwindows.o: scrxwindows.c cpu.h scrxwindows.h debug.h screen.h mem128.h compileoptions.h zx8081.h audio.h charset.h zxvision.h timer.h utils.h joystick.h cpc.h prism.h z88.h sam.h ql.h settings.h msx.h svi.h coleco.h sg1000.h sms.h pcw.h
	$(CC) $(CFLAGS) -I/usr/X11R6/include -I/opt/X11/include -c scrxwindows.c

audiocoreaudio.o: audiocoreaudio.c audiocoreaudio.h cpu.h audio.h compileoptions.h debug.h settings.h
	$(CC) $(CFLAGS) -c audiocoreaudio.c

