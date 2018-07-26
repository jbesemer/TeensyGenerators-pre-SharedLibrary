import sys
import os
import win32com.client

# http://stackoverflow.com/questions/6011115/doc-to-pdf-using-python

class Word( object ):
    FormatPDF = 17

    def __init__( self ): self.Word = win32com.client.Dispatch('Word.Application')

    def Quit( self ): self.Word.Quit()

    def Open( self, filename ): return self.Word.Documents.Open( filename )

    def ConvertToPdf( self, filename ):
        in_file = os.path.abspath( filename )
        base, ext = os.path.splitext( filename )
        out_file = os.path.abspath( base + ".pdf" )

        doc = self.Open( in_file )
        doc.SaveAs( out_file, self.FormatPDF )
        doc.Close()

def Main( args ):

    word = Word()

    if len( args ) > 0:
        for arg in args:
            if arg.endswith( ".docx" ):
                word.ConvertToPdf( arg )
    else:
        word.ConvertToPdf( "Test.docx" )

    word.Quit();

if __name__ == "__main__":
	import sys

	Main( sys.argv[ 1: ] )