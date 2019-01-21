# mysigsegv
A dummy project to reproduce SIGSEGV in libmysqlclient when reconnecting with QMYSQL

To reproduce:

```
# start the containers
docker-compose run app bash

# build the example code (in main.cpp)
mkdir -p /code/build
cd /code/build
qmake "CONFIG+=debug" ..
make

# run the result with gdb (in order to see the trace)
# the run command is expected to crash with error message "Program received signal SIGSEGV, Segmentation fault."
gdb mysigsegv
run
bt
```

When I run this on my Ubuntu workstation, I get this output:

```
❯ docker-compose run app bash
Creating network "mysigsegv_default" with the default driver
Creating mysigsegv_mysql_1 ... done
root@613f6e670e74:/# mkdir -p /code/build
root@613f6e670e74:/# cd /code/build
root@613f6e670e74:/code/build# qmake "CONFIG+=debug" ..
Info: creating stash file /code/build/.qmake.stash
root@613f6e670e74:/code/build# make
g++ -c -pipe -g -std=gnu++11 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_SQL_LIB -DQT_CORE_LIB -I/code -I. -isystem /usr/include/x86_64-linux-gnu/qt5 -isystem /usr/include/x86_64-linux-gnu/qt5/QtSql -isystem /usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -o main.o ../main.cpp
g++  -o mysigsegv main.o   -lQt5Sql -lQt5Core -lpthread
root@613f6e670e74:/code/build# gdb mysigsegv
GNU gdb (Ubuntu 8.1-0ubuntu3) 8.1.0.20180409-git
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from mysigsegv...done.
(gdb) run
Starting program: /code/build/mysigsegv
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".
"innodb_version"  =  "5.7.24"
"protocol_version"  =  "10"
"slave_type_conversions"  =  ""
"tls_version"  =  "TLSv1,TLSv1.1"
"version"  =  "5.7.24"
"version_comment"  =  "MySQL Community Server (GPL)"
"version_compile_machine"  =  "x86_64"
"version_compile_os"  =  "Linux"

Program received signal SIGSEGV, Segmentation fault.
__GI___pthread_mutex_lock (mutex=0x20) at ../nptl/pthread_mutex_lock.c:65
65	../nptl/pthread_mutex_lock.c: No such file or directory.
(gdb) bt
#0  __GI___pthread_mutex_lock (mutex=0x20) at ../nptl/pthread_mutex_lock.c:65
#1  0x00007ffff2d9926a in ?? () from /usr/lib/x86_64-linux-gnu/libmysqlclient.so.20
#2  0x00007ffff2d70ad1 in ?? () from /usr/lib/x86_64-linux-gnu/libmysqlclient.so.20
#3  0x00007ffff2d44abb in mysql_real_connect () from /usr/lib/x86_64-linux-gnu/libmysqlclient.so.20
#4  0x00007ffff332d1b9 in ?? () from /usr/lib/x86_64-linux-gnu/qt5/plugins/sqldrivers/libqsqlmysql.so
#5  0x00007ffff7ba1f50 in QSqlDatabase::open() () from /usr/lib/x86_64-linux-gnu/libQt5Sql.so.5
#6  0x000055555555553b in connect (connectionName=...) at ../main.cpp:17
#7  0x0000555555555964 in main (argc=1, argv=0x7fffffffe768) at ../main.cpp:34

```
