# My Linux scripts & configs

## Update checker for the StevenBlack's unified + gambling + porn hosts file ([bash](https://github.com/skelly37/literally-everything/blob/main/checkhosts/checkhosts) + [Python](https://github.com/skelly37/literally-everything/blob/main/checkhosts/checkhosts.py))

This Python3 script checks whether there was an update of the StevenBlack's unified + gambling + porn hosts file.
If there was, the user may agree to replace the older file from /etc/hosts with the newest one

### Prerequisites
* **wget** 
* `$ chmod a+x checkhosts checkhosts-py`

To use different set, just copy the link from the StevenBlack's repo and assign it to the LINK in the bash script `checkhosts`.

Premade Python binary was compiled for Artix Linux but the source code does not depent on the OS.

Whitelist/Blacklist support

### How to use whitelist?
* Paste links/domains into WHITELIST in `checkhosts` script. Correct formatting: WHITELIST = ("domain1" "domain2" "domain3") *you can use ' instead of ", though*
* Enter either full lines from /etc/hosts like '0.0.0.0 www-google-analytics.l.google.com' to whitelist specific domain or just keywords like 'google' to whitelist all of the Google domains (don't do it).
* Paste the links the same way there are in the /etc/hosts — no tabulating, no spacing, no commas etc.

### How to use blacklist?
* Same thing as with the whitelist

### How to force the script to update the file even though there was no update at all?
* Use `--force` flag, i.e. `checkhosts --force`

**[StevenBlack's hosts repo](https://github.com/StevenBlack/hosts)**


## [Fix polish subtitles from NapiProjekt (Python)](https://github.com/skelly37/literally-everything/blob/main/fix-subtitles.py)

Something breaks when using NapiProjekt on Linux with Winetricks and you get some weird characters like œ in your subtitles. It simply does its job.

### Usage
Without replacing the old file:

* `$ python3 fix-subtitles.py my_subtitles.srt`

To replace the old file with the fixed one simply add the _-o_ or _--overwrite_ flag before the filename, e.g.:

* `$ python3 fix-subtitles.py --overwrite my_subtitles.srt`

**Actually just use [this one](https://github.com/emericg/OpenSubtitlesDownload)**

# Nice things
## [Python3](https://github.com/skelly37/literally-everything/blob/main/nice-things/python3)
### [Displaying a progressbar in terminal](https://github.com/skelly37/literally-everything/blob/main/nice-things/python3/functions/my_progressbar.py)

Display script's progress in a pacman-like prograssbar with a loop. Usage documented in the source code.

Example:

```
from time import sleep
from my_progressbar import show_progressbar
	      
        max = 153
        show_progressbar(0, max)
        
        for count in range(max):
            sleep(0.05) 
            #some code
            show_progressbar(count+1, max)
  ```

## [C++](https://github.com/skelly37/literally-everything/blob/main/nice-things/cpp)
### [Crossplatform getch()](https://github.com/skelly37/literally-everything/blob/main/nice-things/cpp/functions/crossplatform-getch.cpp)

Here's some crossplatform solution that returns the uppercase key from buffer
