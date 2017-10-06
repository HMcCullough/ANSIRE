# ASCIIDisplay
A quick lightweight ascii display engine for GUI-type console interactions

Very straight forward
Sample main.cpp included for reference.

ASCIIDisplay.h

#defined width and height will change the size of the display buffer

for use initialize an ASCIIDisplay object, e.g. ASCIIDisplay ad;

ad.Clear will clear the buffer, but not the screen. You'll need to call Draw to clear the screen after this.

ad.charSet will place a single character at a given coordinate in the buffer. If you want to overwrite spaces, pass in a 4th
argument determining spaces or not.

ad.Print will print an entire string at a given coordinate in the buffer. If you want to overwrite spaces, pass in a 4th
argument determining spaces or not.

ad.CreateDialogue will create a box of a given width and height at a given point, primarily intended for dialogues

ad.draw will redraw the entire screen, refreshing all changes to the buffer. If you're making a game, this should be called at
  the end of each gameloop iteration.
