all:
	$(MAKE) -C source
	install -m 755 ./source/bin/smbd $(INSTALL_DIR)/bin/smbd
	install -m 755 ./source/bin/smbpasswd $(INSTALL_DIR)/bin/smbpasswd
	cp ./source/conf/smb.conf $(INSTALL_DIR)/etc
	install -m 755 ./source/bin/CP850.so $(INSTALL_DIR)/lib/CP850.so	#casper
	install -m 755 ./source/bin/CP437.so $(INSTALL_DIR)/lib/CP437.so	#casper
	install -m 755 ./source/bin/libbigballofmud.so $(INSTALL_DIR)/lib/libbigballofmud.so	#casper
	ln -snf libbigballofmud.so $(INSTALL_DIR)/lib/libbigballofmud.so.0	#casper

romfs: all
	$(ROMFSINST) source/bin/CP850.so /lib/CP850.so
	$(ROMFSINST) source/bin/CP437.so /lib/CP437.so
	$(ROMFSINST) source/bin/libbigballofmud.so /lib/libbigballofmud.so
	ln -snf libbigballofmud.so $(ROOTDIR)/romfs/lib/libbigballofmud.so.0
	$(ROMFSINST) source/bin/nmbd /sbin/nmbd
	$(ROMFSINST) source/bin/smbd /sbin/smbd
	$(ROMFSINST) source/bin/smbpasswd /sbin/smbpasswd
	$(ROMFSINST) /bin/samba.sh
	$(ROMFSINST) /bin/samba_add_dir.sh

clean:
#	$(MAKE) -C source clean
	if [ -f ./source/Makefile ];then $(MAKE) -C ./source clean;fi;
