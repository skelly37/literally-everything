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


## Normie-friendly and useful aliases [(raw text to copy-paste)](https://raw.githubusercontent.com/skelly37/literally-everything/main/raw-aliases)

Simply paste it into your shell config, e.g. ~/.bashrc

Keep in mind that ones containing 'paru' require paru and an AUR-friendly distro. Feel free to replace it with your own package manager

`alias update='checkhosts; paru -Syyuu; clean'`

`alias chax='chmod a+x'`

`alias l='ls --group-directories-first'`

`alias lq='ls --quote-name --group-directories-first'`

`alias la='ls --quote-name --group-directories-first -a'`

`alias ins='paru -S --skipreview'`

`alias rem='paru -Rns'`

`alias comp='makepkg -si'`

`alias pkgs='paru -Q'`

`alias aurpkgs='paru -Qm'`

`alias clean='paru -Rns $(paru -Qdtq)'`

`alias wgetq='wget -q'`

`alias pyins='pyinstaller --onefile'`

`alias exrar='unrar x'`

`alias extar='tar -xvf'`

`alias remdir='rm -r'`

`alias remprtscr='cd ~/Pictures && rm Screenshot*; cd'`

`alias tojpg='c2jpg $(l)'`

### Dependencies
* Package manager:
	* pacman 
* 'Classic' tools:
	* `wget`, `unrar`, `tar`
* Other content:
	* https://github.com/Morganamilo/paru
	* https://github.com/skelly37/literally-everything#update-checker-for-the-stevenblacks-unified--gambling--porn-hosts-file-bash--python 
	* https://github.com/pyinstaller/pyinstaller
	* https://github.com/eon01/c2jpg   	


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

Since getch() works only on Windows (Windows.h), there's some crossplatform solution that returns the uppercase key from buffer

# Things not to forget
## Configuring USB printer Brother MFC 7860DW on Artix Linux with runit
### Prerequisites
* `$ paru -S brother-mfc-7860dw brscan4`

Replace *paru* with your preferred AUR helper prefix or simply build the AUR packages manually

* `# pacman -S cups-runit simple-scan`

The latter may be any other scanning software

* `# cp /etc/runit/sv/cupsd /run/runit/service/`
* `# sv up cupsd && sv status cupsd`

### Setting up the printer
* `# lpadmin -p BROTHER-MFC-7860DW -E -v [PORT-USB] -m MFC7860DW.ppd`

example:

* `# lpadmin -p BROTHER-MFC-7860DW -E -v "usb://Brother/MFC-7860DW?serial=E6343844N360681"-m MFC7860DW.ppd`

### Setting up the scanner
* `# brsaneconfig4 -a name=Brother_MFC-7860DW model=MFC-7860DW ip=192.000.000.192`

Only the IP modification is required. You have to set up a static IP for your printer. Either via your router or via the settings of the printer.

### Resources
* https://wiki.archlinux.org/index.php/CUPS#CLI_tools
* https://juancjuarez.wordpress.com/2014/02/17/archlinux-brother-mfc-7860dw/
* https://forum.artixlinux.org/index.php/topic,767.0.html

