example fapolicyd blocking shell
===

## warning: this demo will overwrite your fapolicyd.rules file

## setup 
1. build the rpm
- `cmake && cpack -G RPM`
2. install the rpm
- `rpm -i --replacefiles fapolicyd-deny-shell-0.1.1-Linux.rpm`
3. create group with 10001 
- `groupadd -g 10001 blocked`
5. start fapolicyd
6. call with systemd
- `systemctl start boo`
7. tail syslog
- `tail -n25 /var/log/messages`

   ```
   2022-04-08T23:16:56.355764+00:00 fedora systemd[1]: Starting Boo!...
   2022-04-08T23:16:56.357635+00:00 fedora fapolicyd[30268]: rule=1 dec=allow_syslog perm=execute uid=0 gid=10001 pid=30356 exe=/usr/lib/systemd/systemd : path=/usr/local/boo/bin/boo ftype=application/x-executable trust=1
   2022-04-08T23:16:56.358097+00:00 fedora fapolicyd[30268]: rule=1 dec=allow_syslog perm=open uid=0 gid=10001 pid=30356 exe=/usr/lib/systemd/systemd : path=/usr/local/boo/bin/boo ftype=application/x-executable trust=1
   2022-04-08T23:16:56.358207+00:00 fedora fapolicyd[30268]: rule=4 dec=allow_syslog perm=execute uid=0 gid=10001 pid=30356 exe=/usr/lib/systemd/systemd : path=/usr/lib64/ld-2.33.so ftype=application/x-sharedlib trust=1
   2022-04-08T23:16:56.358289+00:00 fedora fapolicyd[30268]: rule=4 dec=allow_syslog perm=open uid=0 gid=10001 pid=30356 exe=/usr/lib/systemd/systemd : path=/usr/lib64/ld-2.33.so ftype=application/x-sharedlib trust=1
   2022-04-08T23:16:56.358839+00:00 fedora fapolicyd[30268]: rule=2 dec=allow_syslog perm=open uid=0 gid=10001 pid=30356 exe=/usr/local/boo/bin/boo : path=/usr/local/boo/lib/libboo.so ftype=application/x-sharedlib trust=1
   2022-04-08T23:16:56.358982+00:00 fedora fapolicyd[30268]: rule=5 dec=allow_syslog perm=open uid=0 gid=10001 pid=30356 exe=/usr/local/boo/bin/boo : path=/etc/ld.so.cache ftype=application/octet-stream trust=0
   2022-04-08T23:16:56.359969+00:00 fedora fapolicyd[30268]: rule=3 dec=allow_syslog perm=open uid=0 gid=10001 pid=30356 exe=/usr/local/boo/bin/boo : path=/usr/local/boo/config/boo.conf ftype=text/plain trust=1
   2022-04-08T23:16:56.360065+00:00 fedora boo[30356]: calling into the lib is ok
   2022-04-08T23:16:56.360635+00:00 fedora fapolicyd[30268]: rule=7 dec=deny_syslog perm=execute uid=0 gid=10001 pid=30357 exe=/usr/local/boo/bin/boo : path=/usr/bin/bash ftype=application/x-executable trust=1
   2022-04-08T23:16:56.360843+00:00 fedora boo[30356]: calling a shell is not ok
   2022-04-08T23:16:56.361418+00:00 fedora systemd[1]: boo.service: Deactivated successfully.
   2022-04-08T23:16:56.362005+00:00 fedora systemd[1]: Finished Boo!.
   ```


8. stop fapolicyd
9. tail syslog again

   ```
   2022-04-08T23:18:14.047373+00:00 fedora systemd[1]: Starting Boo!...
   2022-04-08T23:18:14.050716+00:00 fedora boo[30374]: calling into the lib is ok
   2022-04-08T23:18:14.056997+00:00 fedora boo[30374]: calling a shell is ok
   2022-04-08T23:18:14.057402+00:00 fedora systemd[1]: boo.service: Deactivated successfully.
   2022-04-08T23:18:14.057816+00:00 fedora systemd[1]: Finished Boo!.
   ```
