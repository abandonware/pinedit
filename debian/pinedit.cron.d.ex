#
# Regular cron jobs for the pinedit package
#
0 4	* * *	root	[ -x /usr/bin/pinedit_maintenance ] && /usr/bin/pinedit_maintenance
