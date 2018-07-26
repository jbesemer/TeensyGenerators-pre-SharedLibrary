#! env python

import os, os.path, re
import datetime


def Parse( filename ):
	fd = open( filename )

	for line in fd:
		if line:
			if line.startswith( "Timestamp" ):
				break
		else:
			return

	for line in fd:
		s = line.strip()
		if not s:
			return

		fields = line.split(",")
		print "\t", fields[1].strip(), ","

	
def Main( args ):
	if len( args ) > 0:
		for arg in args:
			Parse( arg )
	else:
		Parse( "LM3 lpem.csv" )

if __name__ == "__main__":
	import sys

	Main( sys.argv[ 1: ] )