example fapolicyd blocking shell
===

Demonstrates an application installed to a directory in `/usr/local/boo` that has `bin`, `lib`, and `config` subdirs.  

The binary under `bin` loads the conf under `config` and calls into a shared library under `lib`.

Two library functions are demonstrated:
1. function with no external calls
2. function that attempts to start a shell with a `system` call

The included `fapolicyd.rules` file demonstrate that fapolicyd can be configured to allow the library and config to be accessed while blocking the shell execution.

The demonstration is packaged into a RPM and has been tested on FC34. 

## warning: this demo will overwrite your fapolicyd.rules file

## setup 
1. build the rpm
- `cmake && cpack -G RPM`
2. install the rpm
- `rpm -i --replacefiles fapolicyd-deny-shell-0.1.1-Linux.rpm`
3. create group with 10001 
- `groupadd -g 10001 blocked`
5. **start** fapolicyd
6. call boo with systemctl
- `systemctl start boo`
7. tail syslog
- `tail -n25 /var/log/messages`

   ```
    2022-04-09T00:49:59.636625+00:00 fedora systemd[1]: Starting Boo!...
    2022-04-09T00:49:59.638672+00:00 fedora fapolicyd[31398]: rule=1 dec=allow_syslog perm=execute uid=0 gid=10001 pid=31406 exe=/usr/lib/systemd/systemd : path=/usr/local/boo/bin/boo ftype=application/x-executable trust=1
    2022-04-09T00:49:59.638983+00:00 fedora fapolicyd[31398]: rule=1 dec=allow_syslog perm=open uid=0 gid=10001 pid=31406 exe=/usr/lib/systemd/systemd : path=/usr/local/boo/bin/boo ftype=application/x-executable trust=1
    2022-04-09T00:49:59.639097+00:00 fedora fapolicyd[31398]: rule=5 dec=allow_syslog perm=execute uid=0 gid=10001 pid=31406 exe=/usr/lib/systemd/systemd : path=/usr/lib64/ld-2.33.so ftype=application/x-sharedlib trust=1
    2022-04-09T00:49:59.639180+00:00 fedora fapolicyd[31398]: rule=4 dec=allow_syslog perm=open uid=0 gid=10001 pid=31406 exe=/usr/lib/systemd/systemd : path=/usr/lib64/ld-2.33.so ftype=application/x-sharedlib trust=1
    2022-04-09T00:49:59.639706+00:00 fedora fapolicyd[31398]: rule=2 dec=allow_syslog perm=open uid=0 gid=10001 pid=31406 exe=/usr/local/boo/bin/boo : path=/usr/local/boo/lib/libboo.so ftype=application/x-sharedlib trust=1
    2022-04-09T00:49:59.640650+00:00 fedora fapolicyd[31398]: rule=6 dec=allow_syslog perm=open uid=0 gid=10001 pid=31406 exe=/usr/local/boo/bin/boo : path=/etc/ld.so.cache ftype=application/octet-stream trust=0
    2022-04-09T00:49:59.640838+00:00 fedora fapolicyd[31398]: rule=4 dec=allow_syslog perm=open uid=0 gid=10001 pid=31406 exe=/usr/local/boo/bin/boo : path=/usr/lib64/libstdc++.so.6.0.29 ftype=application/x-sharedlib trust=1
    2022-04-09T00:49:59.640993+00:00 fedora fapolicyd[31398]: rule=4 dec=allow_syslog perm=open uid=0 gid=10001 pid=31406 exe=/usr/local/boo/bin/boo : path=/usr/lib64/libgcc_s-11-20210324.so.1 ftype=application/x-sharedlib trust=1
    2022-04-09T00:49:59.641140+00:00 fedora fapolicyd[31398]: rule=4 dec=allow_syslog perm=open uid=0 gid=10001 pid=31406 exe=/usr/local/boo/bin/boo : path=/usr/lib64/libc-2.33.so ftype=application/x-sharedlib trust=1
    2022-04-09T00:49:59.641298+00:00 fedora fapolicyd[31398]: rule=4 dec=allow_syslog perm=open uid=0 gid=10001 pid=31406 exe=/usr/local/boo/bin/boo : path=/usr/lib64/libm-2.33.so ftype=application/x-sharedlib trust=1
    2022-04-09T00:49:59.644459+00:00 fedora fapolicyd[31398]: rule=3 dec=allow_syslog perm=open uid=0 gid=10001 pid=31406 exe=/usr/local/boo/bin/boo : path=/usr/local/boo/config/boo.conf ftype=text/plain trust=1
    2022-04-09T00:49:59.645719+00:00 fedora boo[31406]: [no_shell]   calling into the lib is ok
    2022-04-09T00:49:59.646271+00:00 fedora fapolicyd[31398]: rule=7 dec=deny_syslog perm=execute uid=0 gid=10001 pid=31407 exe=/usr/local/boo/bin/boo : path=/usr/bin/bash ftype=application/x-executable trust=1
    2022-04-09T00:49:59.646387+00:00 fedora boo[31406]: [with_shell] summoning a shell is not ok
    2022-04-09T00:49:59.646956+00:00 fedora systemd[1]: boo.service: Deactivated successfully.
    2022-04-09T00:49:59.647328+00:00 fedora systemd[1]: Finished Boo!.
   ```


8. **stop** fapolicyd
9. call boo with systemctl
- `systemctl start boo`
10. tail syslog again

    ```
     2022-04-09T00:51:24.967844+00:00 fedora systemd[1]: Starting Boo!...
     2022-04-09T00:51:24.970787+00:00 fedora boo[31428]: [no_shell]   calling into the lib is ok
     2022-04-09T00:51:24.976165+00:00 fedora boo[31428]: [with_shell] summoning a shell is ok
     2022-04-09T00:51:24.976609+00:00 fedora systemd[1]: boo.service: Deactivated successfully.
     2022-04-09T00:51:24.976922+00:00 fedora systemd[1]: Finished Boo!.
    ```
