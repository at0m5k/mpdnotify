mpdnotify
====

This is a simple notification app for MPD. When the MPD state is changed (playing \ paused \ stopped), it will display a visual notification displaying the artist, title, and album art (if available) of the current song.

**Requirements:**
* `libmpdclient`
* `libnotify`

**Notes on album art:**  
Album art is currently managed by looking for an image named "cover.jpg" in the directory that the current song is stored in **(This is likely to change in future builds)**. If the image is not found, or upon errors, a default icon is used instead. You will need to change the *mpdroot* string to match your mpd music directory in order for album art to work.

Note that the "cover.jpg" images only need to be as large as the notification icon (30x30 by default in notify-osd) as converting larger images to a GdkPixbuf consumes an unnecessary amount of system resources. Using large images may cause a noticable delay before the notification is shown, among other issues. You can use the mogrify command from "Extra/imagemagick" to resize images. You can also run a simple one-liner if you would rather resize all of the covers in your mpd music directory at once.

zsh users can simply run:  

	$ for a in /path/to/mpd/music/dir/**/*.jpg; do mv $a $a.orig && convert -resize 40x40 $a.orig cover.jpg

while bash users can run:  

	$ find /path/to/mpd/music/dir -type f -name \*.jpg | while read a; do mv "$a" "$a".orig && convert -resize 40x40 "$a".orig cover.jpg

For best results, change the "40x40" to match the icon size your notification daemon is using.  
For other image types just change the \*.jpg to whichever extension you prefer to store the covers as. If you change this, be sure to also change the *albumart* string in mpdnotify.c.

**Installation:**  
Arch Linux users can simply use the PKGBUILD to build and install.

Other Linux users can simply clone this repository and run:

	$ make
	# make install

**Todo:**
* Add error checking.
* Implement better method of handling album art.
* Clean up code -> memory \ speed optimizations.
