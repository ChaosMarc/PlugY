# PlugY
PlugY, The Survival Kit - Plug-in for Diablo II Lord of Destruction (1.09b - 1.13d + 1.14d)

Extends Diablo II - Lord of Destruction by a number of useful features

## FEATURES
Each features can be turned on/off via PlugY.ini (see "COMMENTS ON THE CONFIGURATION FILE")
* Disable access to Battle.net.
* Infinite storage space in the stash.
* Shared storage space in the stash.
* Enable the ladder only runewords for singleplayer and TCP/IP game.
* World Event and Uber Quest for singleplayer and TCP/IP game.
* Can open Cow Level Portal even when player have kill the Cow King in that difficulty.
* Prevent Nihlathak's portal from closing.
* Move Deckard Cain near the waypoint in Harrogath.
* Unassign assigned skills and stats points.
* Auto backup save files before saving.
* Change the selected language.
* Always regenerate maps in SinglePlayer like in MultiPlayer.
* Automatically execute /players X when you launch a new game.
* Added some pages for display more characters stats.
* Display item level in its popup.
* Launch any number of Diablo II games on the same computer.
* Increase the stash to 10x10 squares.
* Change the save path directory.
* Always display Mana and Life values above the globes.
* D2 can load all files, even those opened with Microsoft Excel (disabled by default).
* Display the current stats value (without magical bonus).
* Can launch game in windowed mode.
* Add following commands (see "COMMENTS ON THE CONFIGURATION FILE") :
	* /lockmouse : Lock mouse cursor in the window.
	* /lock : Same as /lockmouse.
	* /unlockmouse : Unlock mouse cursor in the window.
	* /unlock : Same as /unlockmouse.
	* /renamepage name : Rename current page stash (use # for page number).
	* /rp name : See /renamepage.
	* /setindex : Set current stash page as index.
	* /setmainindex : Set current stash page as main index.
	* /resetindex : Remove index flag on the current stash page.
	* /insertpage : Insert a new page after the current page.
	* /ip : See /insertpage.
	* /deletepage : Delete current page if empty.
	* /dp : See /deletepage.
	* /swappage page : Swap the content of current stash page with the content of another page.
	* /sp page : See /swappage.
	* /togglepage page : Swap the content of current stash page with the content of another page in opposing stash shared/personal.
	* /tp page : See /togglepage.
	* /dlm : Toggle always display mana and life mode.
	* /dml : See /dlm.
	* /dl : See /dlm.
	* /dm : See /dlm.
	* /page 1 : Show normal stats page (stats page must be opened).
	* /page 2 : Show extra stats page (stats page must be opened).
	* /page 3 : Show resistance stats page (stats page must be opened).
	* /page 4 : Show player breakpoints (stats page must be opened).
	* /page 5 : Show mercenaries breakpoints (stats page must be opened).
	* /page 6 : (beta) Show available runewords (stats page must be opened).
	* /save : (beta) Save game without exit.
	* /listcube : (beta) Create a "cube.txt" file in save directory containing all cube's receipts.
	* /renamechar newname : (beta) Rename your character and save it.
	
## Contribute
If you want to update the translations please use the [POEditor project](https://poeditor.com/join/project/VnO1SKslPV) and create a bug-ticket nofifying me that you have done so. Please do not edit the LocalizedStrings.ini directly. If you absolutely don't want to use POEditor, edit the json files found at [PlugYInstaller/PlugY/translations](https://github.com/ChaosMarc/PlugY/tree/master/PlugYInstaller/PlugY/translations)
