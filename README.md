# ASCIIDisplay
A quick lightweight ascii display engine for GUI-type console interactions

Very straight forward
Sample main.cpp included for reference.

ASCIIDisplay.h

#defined width and height will change the size of the display buffer

for use initialize an ASCIIDisplay object, e.g. ASCIIDisplay ad;

ad.Clear will clear the buffer, but not the screen. You'll need to call Draw to clear the screen after this.

ad.charSet will place a single character at a given coordinate in the buffer.

ad.Print will print an entire string at a given coordinate in the buffer.

ad.draw will redraw the entire screen, refreshing all changes to the buffer. If you're making a game, this should be called at
  the end of each gameloop iteration.
  
NOTE: Spaces do not overwrite characters already placed on the screen, you will need to clear and redraw the buffer. Functions
will be added that will write spaces in the future.
