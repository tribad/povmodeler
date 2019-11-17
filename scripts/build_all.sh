#!/bin/bash
ssh root@debian-10.vm.home /usr/src/povmodeler/scripts/build_povmodeler.sh >& povmodeler.debian-10.log&
ssh root@mint191.vm.home /usr/src/povmodeler/scripts/build_povmodeler.sh >& povmodeler.mint-19.1.log&
ssh root@mint192.vm.home /usr/src/povmodeler/scripts/build_povmodeler.sh >& povmodeler.mint-19.2.log&
ssh root@suse151.vm.home /usr/src/povmodeler/scripts/build_povmodeler.sh >& povmodeler.suse-15.1.log&

wait

scp root@debian-10.vm.home:/usr/src/povmodeler/povmodeler-0.1-debian-10.deb .
scp root@mint191.vm.home:/usr/src/povmodeler/povmodeler-0.1-linuxmint-19.1.deb .
scp root@mint192.vm.home:/usr/src/povmodeler/povmodeler-0.1-linuxmint-19.2.deb .
scp root@suse151.vm.home:/usr/src/povmodeler/povmodeler-0.1-opensuse-leap-15.1.rpm .

scp -P 50735 povmodeler-0.1-debian-10.deb hjl@prbrowsergame.de:/var/www/html/simulated-universe/product
scp -P 50735 povmodeler-0.1-linuxmint-19.1.deb hjl@prbrowsergame.de:/var/www/html/simulated-universe/product
scp -P 50735 povmodeler-0.1-linuxmint-19.2.deb hjl@prbrowsergame.de:/var/www/html/simulated-universe/product
scp -P 50735 povmodeler-0.1-opensuse-leap-15.1.rpm hjl@prbrowsergame.de:/var/www/html/simulated-universe/product


