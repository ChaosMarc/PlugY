;--------------------------------------------------------------------------------------;
;                                                                                      ;
;                               "PlugY, The Survival Kit"                              ;
;                                                                                      ;
;                                  by Yohann Nicolas                                   ;
;                                                                                      ;
;                                     version 14.02                                    ;
;                                                                                      ;
;--------------------------------------------------------------------------------------;

Official website : http://plugy.free.fr
You can make a donation if you want.


******** WARNING ********
- This plug-in works with LoD version 1.09 to 1.13d and 1.14d and mods based on.
- This plug-in doesn't work on Battle.net and others realms.
- All files have changed since previous version. Please don't use old files.
- LOD 1.14 change the save directory, so you must move PlugY save files manually.


******** FEATURES ********
Each features can be turn on/off via PlugY.ini (see "COMMENTS ON THE CONFIGURATION FILE")
- Disable access to Battle.net.
- Infinite storage space in the stash.
- Shared storage space in the stash.
- Enable the ladder only runewords for singleplayer and TCP/IP game.
- World Event and Uber Quest for singleplayer and TCP/IP game.
- Can open Cow Level Portal even when player have kill the Cow King in that difficulty.
- Prevent Nihlathak's portal from closing.
- Move Deckar Cain near the waypoint in Harrogath.
- Unassign assigned skills and stats points.
- Auto backup save files before saving.
- Change the selected language.
- Always regenerate maps in SinglePlayer like in MultiPlayer.
- Automatically execute /players X when you launch a new game.
- Added some pages for display more characters stats.
- Display item level in its popup.
- Launch any number of Diablo II games on the same computer.
- Increase the stash to 10x10 squares.
- Change the save path directory.
- Always display Mana and Life values above the globes.
- D2 can load all files, even those opened with Microsoft Excel (disabled by default).
- Display the current stats value (without magical bonus).
- Can launch game in windowed mode.
- Add following commands (see "COMMENTS ON THE CONFIGURATION FILE") :
	/lockmouse : Lock mouse cursor in the window.
	/lock : Same as /lockmouse.
	/unlockmouse : Unlock mouse cursor in the window.
	/unlock : Same as /unlockmouse.
	/renamepage name : Rename current page stash (use # for page number).
	/rp name : See /renamepage.
	/setindex : Set current stash page as index.
	/setmainindex : Set current stash page as main index.
	/resetindex : Remove index flag on the current stash page.
	/insertpage : Insert a new page after the current page.
	/ip : See /insertpage.
	/deletepage : Delete current page if empty.
	/dp : See /deletepage.
	/swappage page : Swap the content of current stash page with the content of another page.
	/sp page : See /swappage.
	/togglepage page : Swap the content of current stash page with the content of another page in opposing stash shared/personal.
	/tp page : See /togglepage.
	/dlm : Toggle always display mana and life mode.
	/dml : See /dlm.
	/dl : See /dlm.
	/dm : See /dlm.
	/page 1 : Show normal stats page (stats page must be opened).
	/page 2 : Show extra stats page (stats page must be opened).
	/page 3 : Show resistance stats page (stats page must be opened).
	/page 4 : Show player breakpoints (stats page must be opened).
	/page 5 : Show mercenaries breakpoints (stats page must be opened).
	/page 6 : (beta) Show available runewords (stats page must be opened).
	/save : (beta) Save game without exit.
	/listcube : (beta) Create a "cube.txt" file in save directory containing all cube's receipts.
	/renamechar newname : (beta) Rename your character and save it.

v14.02 changes :
- Fix a bug allowing multiple identical unique charms to be in inventory.

v14.01 changes :
- Fix stash items lost on loading a character for the first time.

v14.00 changes :
- Add compatibility with LOD 1.14d. (Thanks to Haxifix)
- Add auto backup save files before saving.
- Prevent Nihlathak's portal from closing.
- Move Deckar Cain near the waypoint in Harrogath.
- Change UberDiablo, UberBaal and UberMephisto starting positions in Uber Tristram.
- UberDiablo, UberBaal and UberMephisto can spawn monsters (Need LOD 1.13c or higher). (Thanks to SnapChip)
- Update UberDiablo, UberBaal and UberMephisto AI (Need LOD 1.13c or higher). (Thanks to SnapChip)
- Add player and mercenaries breakpoints in stats page 4 and 5.
- Disable shared stash in multiplayer by default.
- Change stash page color dependings of indexes flags.
- Increase the maximum length of stash page name from 15 to 20 characters.
- Enable automatic stash page naming.
- Click on page stash name to change index type.
- Shift + click on page stash name to rename it.
- Rename /swap command to /swappage.
- Rename /toggle command to /togglepage.
- Add /rp command as shortcut for /renamepage.
- Add /ip command as shortcut for /insertpage.
- Add /dp command as shortcut for /deletepage.
- Add /sp command as shortcut for /swappage.
- Add /tp command as shortcut for /togglepage.
- The relative folder for SavePath is now the D2 save folder instead of D2 install path.
- Now, the PlugY folder must be in the same directory as PlugY.ini (so in the mod folder).
- Optimize PlugY time loading and infinite stash time loading.
- Fix minimum SOJ sold value for the World Event.
- Fix crash of /swappage command when the target page wasn't created.
- Fix possible crash with stash name allocation. (Thanks to SnapChip)
- Fix NBPlayersByDefault when MultiStash was disabled.
- Fix crash when SkillsUnassignment, StatsUnassignment, NewStatsInterface, BigStash and MultiPageStash was disabled.
- Fix ActiveSkillsUnassignmentOneForOne Feature (option for mods).
- Fix crash in Polish version language.
- Fix the /players anormal message au startup.
- Fix the abnormal message that sometimes appears when starting a game with the NBPlayersByDefault option.
- Fix compatibility issue between NBPlayersByDefault option and D2MultiRes mod.
- More stash buttons parameters in PlugY (option for mods).
- Update Chinese transalation. (Thanks to Nagahaku)
- Fix some translations in different languages.

v12.00 changes : 
- Unofficial version supporting LOD 1.14d

v11.02 changes :
- Add command /setmainindex : Set the current stash page as main index (shift + prev/next index button go to an main index if exists)
- Current number of simulated players use with /players command is save with the player and set on game loading. NBPlayersByDefault must be different to 0 in PlugY.ini.

v11.01 changes :
- Compatibily with 1.13d (thanks to L'Autour)
- Add command /unlockmouse : Unlock the mouse
- Add command /unlock : same as /unlockmouse
- Add command /renamepage : stash page name are succefully saved.
- Add command /setindex : Set the current stash page as index (prev/next index button go to an index if exists)
- Add command /resetindex : Remove index flag on the current stash page (prev/next index button go to this index if exists).
- Add command /insertpage : Insert a new page after the current page.
- Add command /deletepage : Delete current page if empty.
- Add localizion in Russian and google traduction for not translated language. (thanks to L'Autour)
- Add an option in PlugY.ini to select shared stash (instead of personal one) on character loading.
- Rename command /rename to /renamechar.
- Remove unfinished command /reload.

v11.00 changes : 
- Unofficial version supporting LOD 1.13d

v10.01 changes :
- Add windowed mode.
- Can lock mouse cursor in the window (windowed mode).
- Can remove border (windowed mode).
- Can resize or maximize window (windowed mode).
- Can fix window above any others windows including taskbar (windowed mode).
- Can lock mouse cursor in the windows on startup and with command "/lockmouse" or "/lock" (windowed mode).
- Add command "/swap page" to swap the content of current stash page with the content of another page.
- Add command "/toggle page" to swap the content of current stash page with the content of another page in opposing stash shared/personal.
- Add command "/rename newname" to rename your character. This feature is still in beta and you must exit the game to update the stats page.

v10.00 changes :
- Disable access to Battle.net via main menu button.
- PlugY works for 1.13c version of LoD too.
- Fix shortcut in start menu

v9.00 changes :
- PlugY works for 1.12 version of LoD too.
- Fix somes bugs.
- Add option for unassign skill for mods.

v8.00 changes :
- Easier installation : New installer.
- Can open Cow Level Portal even when player have kill the Cow King in that difficulty.
- Display the real version of LoD in the main screen. (v 1.09d or v 1.11b instead of v 1.09 or v 1.11)
- Add the possibility to move the unassign skills button like stash buttons. (for modders)
- Fix crash when meeting a superunique monsters in Lod v1.11.
- Fix skills points lost when unasssign them in mods with special skills.
- Multiplayer : Save stash files (with client's data like version before 5.00) when a deconnection or error happend during saving process.
- Remove the "check load memory failed" message when D2gfx.dll was patched.

v7.01b changes :
- Fix the ladder only runewords features in versions 1.11 and 1.10 of LoD.
- Fix wierd characters in some text.

v7.01 changes :
- Enabled the ladder only runewords out of realms.
- Fixed Uber Baal AI.
- Remove all param options set by default in PlugY.ini (like windowed mode).
- Display the stats current value (without magical bonus) even when stats unasisgnment are disabled.
- Add an executable to launch PlugY (no more LoD's files modified) (RECALL)
- Translation into spanish and polish.

v7.00 changes :
- PlugY works for 1.11b version of LoD too.
- Add an executable to launch PlugY (no more LoD's files modified)
- Add base value for each stat on assign buttons overtext.
- Fix infinity stat bugs during unassignation.
- Fix features which stayed enabled on Battle.net.
- Translation into italian.

v6.01b changes :
- Bug fix with the display of popup on stat assignment buttons.

v6.01 changes :
- Major fix : unique carry1 items don't disappear when they are cubbed in LoD 1.10
- Keys and Uber organs aren't destroyed when we try to open a Red Porpal out of Harrogath.
- Fix conflict with D2Mod for the version display.

v6.00 changes :
- PlugY works for 1.11 version of LoD too !
- Enabled Uber Quest off realm (LoD 1.11 only).
- Fixed crash on PlugY launch if LoD install isn't clean
- Fixed some minor bugs and added some minor improvements.
- Added command "/save" to save the game without exit (LoD 1.11 only).

v5.06 changes :
- Added buttons for shared gold.
- Enabled shared gold in multiplayer.
- Command "/DisplayLifeMana" is replaced by "/dlm".
- Fixed some bugs.

v5.05 changes :
- Fixed bad default color in interface stats.
- Added Shared gold via commands.
- Command "/DisplayLifeAndMana" is now "/DisplayLifeMana".
- Display green set item name in popup when it's in the shared stash.
- Fixed multiplayer bugs by redoing multiplayer procedure.

v5.04 changes :
- Fixed : Stat/Skill points per level-up bug.
- Fixed : Multiplayer bugs.
- PlugY/PlugYDefault.ini completed.

v5.03 changes :
- Fixed : Bug which sometimes swaps Hardcore and Softcore shared stash.
- Added color on extra stats page.
- Changed default values on extra stats page.
- Set EnabledTXTFilesWhenMSExcelOpenIt=1 in PlugY.ini file.

v5.02 changes :
- Fixed : Previous bug fix which caused items to disappear.

v5.01 changes :
- Fixed : Major bugs in stash management.
- Fixed : Set back PlugY.ini with ActiveLogFile=0 by default.
- Fixed : bug when shared stash is disabled.

v5.00 changes :
- PlugY works for 1.09, 1.09b, 1.09d versions of LoD, including mods based on these releases !
- PlugY can load D2Mod.dll.
- D2 can load all files, even those openned with Microsoft Excel.
- World Event monster can be changed.
- Some stuff for modders.
- Fixed : major bugs in Multiplayer : fingerprints reset, unidentified bugged items, etc.
- Fixed : Typo error in PlugY.ini (Commands).
- Fixed : No more case sensitive commands in game.
- Fixed : Select Main Stat page bug on opening
- Fixed : Replaced the display "Critical Strike/Deadly Strike" with Deadly Strike only.
- Fixed : The spawn of DiabloClone at starting of a new game
- Fixed : Some other small bugs.

v4.04 changes :
- Fixed : Display bug when statPerLevelUp enabled.
- Fixed : Bug in saving procedure when the disk is full.
- New configuration system for modders.
- Always display Mana and Life values above the globes.

v4.03 changes :
- Fixed : "carry 1" unique item (unique charm) when we drop the cube.
- Can go directly to first or last page of stash (shift + click on next/previous).
- Second index added (shift + click on index buttons)
- Added data to extra stats pages (2 pages now).
- Added previous page button in main stats page (only in 800x600).
- Moved buttons in extra stats pages to same place as in main stats page (only in 800x600).
- Can choose whether the main (first) page or the last selected page is displayed on opening the stats page.

v4.02b changes :
- Fixed : Features stay enabled in open Battle.net


v4.02 changes :
- Fixed : No more conflict with Battle.net (BigStash disabled on realms)
- Fixed : Missing "d" in "SeparateHardcoreStash=1" from PlugY.ini
- Fixed : By default in PlugY.ini, the language isn't changed.
- Fixed : Item level display enabled correctly for all configurations of PlugY.
- Added data in the extra stats page.

v4.01 changes :
- Fixed : NbPlayers always set to 8 when active. 
- Added data in the extra stats page.

v4.00b changes :
- Fixed : MSVCR70.dll not found bug.

v4.00 changes :
- Better optimization of the code.
- Added some pages for displaying more characters stats like %MF.
- Change the selected language (and for mod, default and available language).
- Always regenerate maps in SinglePlayer like in MultiPlayer.
- Automatically execute /players X when you launch a new game.
- Display item level in its popup.
- Separate hardcore and softcore shared stash.
- Change installation method (can be installed directly on linux now)
- The item which triggers the World Event can be changed.
- Any number of "carry 1 item" (like annihilus) can be put in the stash.
- Fixed : Cannot put more than one "carry 1 item"  in others page than stash.
- Fixed : display bug of socketed items in the stash.
- Fixed : removed space bug in PlugY.ini.
- Fixed : Diablo Clone can't spawn in normal and nightmare difficulty.
- Fixed : Destruction of extra minions after unassignment if you have +x bonus to the skill.

v3.02 changes :
- Fixed : Change the number of stats points gained when player gains a level.
- Fixed : When the shared stash is disabled, you can load a game with your character.
- Fixed : You can change parameters of World Event without activating skill per level up.

v3.01 changes :
- Change the number of stats points gained when player gains a level.
- Fixed bugs which give extra points when skills points are unassigned.
- Added parameters for the WorldEvent in configuration file.
- By default, World Event only SHOWS "X SOJ Sold" in hell difficulty.

v3.00 changes :
- Local World Event for singleplayer and multiplayer off-realm !
- Unassign assigned skills points.
- New background for the stash.
- Can change the filename of the shared savefile.
- Shared stash page number display are in red now.

v2.05 changes :
- major fix : bugs which cause D2 not to start are finally removed.

v2.04 changes :
- Unassign stats points, skills on level up are disabled when you connect to realm (like stash).
- Open a error message box instead of crash when PlugY.dll isn't found by D2.
- Fixed some bugs in installation method.
- Fixed bug display of buttons.
- Fixed win95/98/Me saving.

v2.03b changes :
- Show PlugY version only in main screen.

v2.03 changes :
- Major fix : Correct and secure the saving procedure.
- No more crash of the host game when a character is unable to enter the game.
- Unassign stats points button greyed when base stat is above 255 fixed. 
- Change version printing on main screen (change color & PlugY version in right corner)
- Character without PlugY can join game host with PlugY enabled.

v2.02 changes :
- PlugY doesn't use D2win.dll to launch PlugY anymore.
- PlugY includes a patcher/unpatcher for editing D2gfx.dll to launch PlugY.
- PlugY can be launched by D2Mod system of SVR.
- The infinite storage sytem is automatically disabled on a realm game.
- Fixed index button bugs.

v2.01 changes :
- Fixed skill per level up bug
- Fixed bug display of text in the main menu

v2.00 changes :
- Localized in German.
- Change the number of Skills points gained when player gains a level.
- Launch any number of Diablo II game on the same computers.
- You can unassign Stats points.
- Added 2 buttons for jumping to index page.
- Print the current stash instead of Gold max. (Gold max value is a current Gold field popup)
- Complety re-done the configuration file.
- Configuration file can be put in mpq (like other PlugY images files)
- Increased compatibility with mods.
- Removed the TCP/IP crash.
- Removed page number bug when you switch between characters.
- Removed set item's bug display.
- Removed the bug of "carry 1"
- Add other small improvements... :)

v1.03 changes :
- Added French readme and ini files.
- Removed bugs in D2Classic game (there is no multipage, it's not a bug)
- Removed the bug when loading character from previous version.
 (like ShadowMaster character or 1.09 or D2Classic character)
- Removed the bugged line in the text when you click on delete character.
* must read : You can start any mods without moving SAVES files
     (you need to move dll files with classic script).

v1.02 changes :
- Re-changed name files due to an IE bug with colon in zip file.
- Ability to change the version text print in the main menu (see ini file).

v1.01 changes : 
- Localized for french version (wait for an french readme.txt) 
- Changed filename from "PlugY, The Survival Kit.ini" to "PlugY,The_Survival_Kit". 
- Added example for installation in the readme. 
- Detection of bad installation on starting plugY. 
- Removed from the ini default file the [GENERAL]PlugYDirectory=PlugY\ 
(you can add it if you want but need to know what are you doing...) 
- Released in .zip file instead of .rar 

v1.00 features (can all be easily enabled or disabled) :
- You can change the save path directory.
- You can start any mods without moving saves files.
- You can increase the stash to 10x10 squares.
- Up to 4,294,967,296 pages in the stash (e.g. infinite storage space) !
  note : for LOD1.10 character only.
- Any of these pages can be shared by all of your characters!



******** CONTENTS ********
20 files, 1 folder :
- PlugY_The_Survival_Kit_-_Readme.txt
- PlugY_The_Survival_Kit_-_LisezMoi.txt
- PlugY_The_Survival_Kit_-_Liesmich.txt
- PlugY_The_Survival_Kit_-_讀我檔案.txt
- PlugY.exe
- PlugY.dll (in Diablo II directory)
- PlugY.ini
- PlugY\PlugYFixed.ini
- PlugY\PlugYDefault.ini
- PlugY\LocalizedStrings.ini
- PlugY\EmptyPage.dc6
- PlugY\SharedGoldBtns.dc6
- PlugY\StashBtns.dc6
- PlugY\TradeStash.dc6
- PlugY\StatsBackground.dc6
- PlugY\UnassignSkillsBtns.dc6
- PlugY\UnassignStatsBtns.dc6
- PlugY\statsinterface.txt
- PatchD2File.exe (in Diablo II directory with PatchFile option)
- RestoreD2File.exe (in Diablo II directory with PatchFile option)



******** INSTALLATION ********
Normal Installation :
- Follow directive installer.

note : You can choice "Diablo II" directory as install directory.

Installation in another mod:
- Copy PlugY.ini, PlugY.exe and PlugY folder (+its contents) in the targeted mod folder.
- Edit PlugY.ini to configure some features (see section below).
- Run PlugY.exe.


Example :
You have installed Lord of Destruction in :  C:\Games\Diablo II\
And the target mod is in : D:\D2Mod\MyMod\
And the second mod is in : D:\D2Mod\MyMod2\
So the new installation is :
   C:\Games\Diablo II\PlugY.dll
   D:\D2Mod\MyMod\PlugY\SharedGoldBtns.dc6
   D:\D2Mod\MyMod\PlugY\PlugYFixed.ini
   D:\D2Mod\MyMod\PlugY\PlugYDefault.ini
   D:\D2Mod\MyMod\PlugY\EmptyPage.dc6
   D:\D2Mod\MyMod\PlugY\SharedGoldBtns.dc6
   D:\D2Mod\MyMod\PlugY\StashBtns.dc6
   D:\D2Mod\MyMod\PlugY\TradeStash.dc6
   D:\D2Mod\MyMod\PlugY\StatsBackground.dc6
   D:\D2Mod\MyMod\PlugY\UnassignSkillsBtns.dc6
   D:\D2Mod\MyMod\PlugY\UnassignStatsBtns.dc6
   D:\D2Mod\MyMod\PlugY\statsinterface.txt
   D:\D2Mod\MyMod\PlugY\LocalizedStrings.ini
   D:\D2Mod\MyMod\PlugY.ini
   D:\D2Mod\MyMod\PlugY.exe
   D:\D2Mod\MyMod2\PlugY\SharedGoldBtns.dc6
   D:\D2Mod\MyMod2\PlugY\PlugYFixed.ini
   D:\D2Mod\MyMod2\PlugY\PlugYDefault.ini
   D:\D2Mod\MyMod2\PlugY\EmptyPage.dc6
   D:\D2Mod\MyMod2\PlugY\SharedGoldBtns.dc6
   D:\D2Mod\MyMod2\PlugY\StashBtns.dc6
   D:\D2Mod\MyMod2\PlugY\TradeStash.dc6
   D:\D2Mod\MyMod2\PlugY\StatsBackground.dc6
   D:\D2Mod\MyMod2\PlugY\UnassignSkillsBtns.dc6
   D:\D2Mod\MyMod2\PlugY\UnassignStatsBtns.dc6
   D:\D2Mod\MyMod2\PlugY\statsinterface.txt
   D:\D2Mod\MyMod2\PlugY\LocalizedStrings.ini
   D:\D2Mod\MyMod2\PlugY.ini
   D:\D2Mod\MyMod2\PlugY.exe


Uninstallation : Use the uninstaller or simply remove all PlugY files.
Note : You can also move PlugY.dll in the mod folder but you must remove any on in D2 folder.
Note : PlugY directory and its contents can be put in a mpq. 

------- D2File Patcher

If you have problem when you run PlugY.exe then use PatchD2File.exe. (It happend sometimes with Windows 2000)
- Do a backup of D2gfx.dll or game.exe.
- Run PatchD2File.exe which modify D2gfx.dll or Game.exe.
- Create a shortcut : Enter target mod directory in "start in" field of properties->shortcut. (unless you install PlugY in Diablo II directory)
- Launch with the shorcut !


******************** FAQ ******************

=> I can't find PlugY.ini file, where is it ? 
In Windows Explorer, selecting Tools->Folder Options->View.
Mark "Show Hidden files and Folders".
Unmark "Hide extensions for know file types".
Then you will for sure see the ini file. 


=> How do I Play sometimes on Battle.net when PlugY is installed ?
PlugY disable the connection to Battle.net.

=> What do I do if I have an error like "Bad Generic File" on loading a new Character ? 
This can appear when you have bad item in the shared stash file. 
A possible cause is to use same save folder for different mod.
In this case, just change the save folder in PlugY.ini. 
You can also move the _LOD_SharedStashSave.sss and _LOD_HC_SharedStashSave.sss to another directory.

=> I get "sUnitItemInsertItemInvGridBase failed at 1046 in C:\projects\D2\head\Diablo2\Source\D2Client\UNIT\Item.cpp" in D2YYMMDD.txt, what I should do ? 
It's just a warning, it causes no problem in game. 


******** CONFIGURATION ********

Configuration of this kit for a specified mod :
- Copy PlugY.ini, PlugY.exe and PlugY folder in the target mod directory.
- Change the save directory in PlugY.ini.

D2Mod configuration :
Just add the dll name in PlugY.ini, for example : "DllToLoad=D2Mod.dll"

Warning :
- Items stored in the Cube are always saved on the player, if you want to shared them, you must remove them from the Cube.
- Be careful about compatibility if you edit PlugY.inin between 2 games.
- In multiplayer game, verify that all player have the same configurations in PlugY.ini.



*** Configuration for modders ***
There are 3 files with same structure to configure PlugY :
- "PlugY/PlugYFixed.ini" in mpq or via the switch -direct
This file override parameters set by users in PlugY.ini.
Use it to enabled(disabled) wanted(unwanted) features.
Warning 1: ActivePlugin=0 doesn't work here (but ActivePlugin=1 works)
Warning 2: SavePath management is ignore in this file.
Warning 3: Don't abuse it, a lot of field should be set by users. (see note below)

- "PlugY/PlugYDefault.ini" in mpq or via the switch -direct
Use it to change default values of PlugY.
Works like PlugY.ini in an mpq in version 4.03 and before.
All fields should be here.

- "PlugY.ini" in current directory only.
For users' configuration (like previous version).
Fields which are in PlugYFixed.ini shouldn't be found here.


******** COMMENTS ON THE CONFIGURATION FILE ********

The configuration in PlugY.ini are not the default configuration.

[LAUNCHING]
This section store info for PlugY.exe and don't work in PlugYDefault.ini and PlugYFixed.ini files.

Add params to transmit to LoD on his command line.
Params give to PlugY.exe are also transmitted to LoD on his command line.
By default no param are transited.
Most common switch are (without quote) :
"-w" open LoD in windowed form. (See WINDOWED section instead)
"-direct" use files in directory instead of those in mpq.
"-txt" recompile txt files before launch a game.
Following are default values, between {} are some examples values with descriptions :
Param=				{-direct -txt -w: these 3 commands are passed on the command line}


Select the library to load.
The current directory are the one used by D2 (like set the "start in" field of a shorcut).
If no library specify, it load LoD without PlugY.
Following are default values, between {} are some examples values with descriptions :
Library=			{PlugY.dll: Load PlugY.dll}


[GENERAL]
Enable or disable all selected features.
Dlls from field "DllToLoad" aren't loaded anymore when ActivePlugin=0.
Following are default values, between {} are some examples values with descriptions :
- ActivePlugin=0		{0:Don't load any features; 1:Plugin enabled}

Enable or disable BattleNet Access.
- DisableBattleNet=1		{0:Battle.net access enable; 1:Battle.net access disable}

Create a log file "PlugY.log" in the current directory.
This feature can slow down your game.
- ActiveLogFile=0 		{0:No information is written while playing; 1:Always enabled}

Load dll of a specific mod for used PlugY in same time.
Separate each dll file name by the character pipe (|)
- DllToLoad=			{(empty): load nothing; D2extra.dll|myDll.dll: Load both D2extra.dll and myDll.dll}
- DllToLoad2=			{(empty): Same as DlltoLoad}

Activate some new commands in PlugY. In parenthesis is the condition to be able to use the command.
	/lockmouse : Lock mouse cursor in the window.
	/lock : Same as /lockmouse.
	/unlockmouse : Unlock mouse cursor in the window.
	/unlock : Same as /unlockmouse.
	/renamepage name : Rename current page stash (use # for page nuymber).
	/rp name : Rename current page stash (use # for page nuymber).
	/setindex : Set current stash page as index.
	/setmainindex : Set current stash page as main index.
	/resetindex : Remove index flag on the current stash page.
	/insertpage : Insert a new page after the current page.
	/ip : Insert a new page after the current page.
	/deletepage : Delete current page if empty.
	/dp : Delete current page if empty.
	/swappage page : Swap the content of current stash page with the content of another page.
	/sp page : Swap the content of current stash page with the content of another page.
	/togglepage page : Swap the content of current stash page with the content of another page in opposing stash shared/personal.
	/tp page : Swap the content of current stash page with the content of another page in opposing stash shared/personal.
	/dlm : Toggle always display mana and life mode.
	/dml : Same as /dlm.
	/dl : Toggle always display life mode.
	/dm : Toggle always display mana mode.
	/page 1 : Show normal stats page (stats page must be opened).
	/page 2 : Show extra stats page (stats page must be opened).
	/page 3 : Show resistance stats page (stats page must be opened).
	/page 4 : Show player breakpoints (stats page must be opened).
	/page 5 : Show mercenaries breakpoints (stats page must be opened).
	/page 6 : (beta) Show available runewords (stats page must be opened).
	/save : (beta) Save game without exit.
	/listcube : (beta) Create a "cube.txt" file in save directory containing all cube's receipts.
	/renamechar newname : (beta) Rename your character and save it.
- ActiveCommands=0 		{0:Disabled; 1:Enabled}

Quit D2, if PlugY failed to install all features.
Disable it only if you know what you do.
- ActiveCheckMemory=1

Activate hidden or unfinished feature. (don't use it)
- ActiveAllOthersFeatures=0 	{0:Disabled; 1:Enabled}


[WINDOWED]
Launch in windowed mode.
- ActiveWindowed=0 		{0:Disabled; 1:Enabled}

Remove border in windowed mode.
- RemoveBorder=0 		{0:Disabled; 1:Enabled}

Set window at most top (above taskbar) in windowed mode.
- WindowOnTop=0 		{0:Disabled; 1:Enabled}

Maximized and center window (keep ratio 4/3) in windowed mode (if SetWindowPos=0).
- Maximized=0 			{0:Disabled; 1:Enabled}

Set position and size of the window in windowed mode.
- SetWindowPos=0 		{0:Disabled; 1:Enabled}
- X=0 					{0:Window Position X}
- Y=0 					{0:Window Position Y}
- Width=0 				{0:Window Width}
- Height=0 				{0:Window Height}

Lock cursor mouse in the window in windowed mode.
- LockMouseOnStartup=0	{0:Disabled; 1:Enabled}


[LANGUAGE]
Change the selected language.
You must have files of the selected language.
All D2/LoD versions contain the english language (except voices).
All possibles languages: ENG|ESP|DEU|FRA|POR|ITA|JPN|KOR|SIN|CHI|POL|RUS
- ActiveChangeLanguage=0	{0:Disabled; 1:Enabled}
- SelectedLanguage=ENG		{FRA: Select French as language}

For modders who want to restrict the available languages and the default language :
- ActiveLanguageManagement=0	{0:Disabled; 1:Enabled}
- DefaultLanguage=ENG		{empty:D2 default language; FRA:French is the default language}
- AvailableLanguages=ENG|ESP|DEU|FRA|POR|ITA|JPN|KOR|SIN|CHI|POL|RUS	{ENG|FRA}


[SAVEPATH]
This is where all of your characters and the shared stash is saved.
You can use absolute or relative paths.
It don't work in PlugYFixed.ini.
Following are default values, between {} are some examples values with descriptions :
- ActiveSavePathChange=0	{0:Disabled; 1:Enabled, you must set "SavePath"}
- SavePath=				{MyMod\  or D:\Save Games\diablo II\Current Mod\}

Active autobackup save file just before the save.
The backup will be store in a folder name "backup" in the save folder.
- ActiveAutoBackup=0		{0:Disabled; 1:Enabled}
- MaxBackupPerCharacter=20	{20: Number of backup to keep before delete; 0:No backup purge}


[MAIN SCREEN]
Change the version text in the main menu (first menu)(instead of "v 1.10")
Color is an integer which refers to defined D2 colors.
Following are default values, between {} are some examples values with descriptions :
- ActiveVersionTextChange=0 	{0:Disabled; 1:Enabled}
- VersionText=       			{Empty: Display the current version of LoD with the subversion letter (1.11b, 1.09d) ; Mod Name:Text with maximum length of 23 characters (ex : v 1.11b)}
- ColorOfVersionText=0      	{0:see * for color list}
- ActivePrintPlugYVersion=1 	{0:Disabled; 1:Enabled)
- ColorOfPlugYVersion=4     	{0:see * for color list}


[STASH]
Increase the stash to 10x10 squares.
Use PlugY\TradeStash.dc6 to change the background image.
When bigStash is enabled, you must restart D2 for play in single/multi/open when you have started a game in closed Bnet previously (and vice versa).
Following are default values, between {} are some examples values with descriptions :
- ActiveBigStash=0	{0:Default stash size is used; 1: Enabled, Stash uses 10x10 squared}

Use this for sharing and keep all of your items. :)
There are 2 multipage stashes :
- one Personal, only seen by the Player;
- one Shared between your Players in this mod.
Use the Toggle Button to switch between stash.
Use arrow buttons on bottom the stash (and shift key) for switching between the pages.
Definition : The last page is the last page with an item in it.
The multipage stashes are inactive for Diablo II Classic Character and on realm.
You can change the name of the shared filename.
Following are default values, between {} are some examples values with descriptions :
- ActiveMultiPageStash=0		{0:Disabled; 1:Enabled}
- NbPagesPerIndex=10			{10: Index page is 1,10,20,30,...,max}
- NbPagesPerIndex2=100			{100: Index page (+shift) is 1,50,100,150,...,max}
- MaxPersonnalPages=0 			{0:Infinite number of personnal pages; 1000: Maximum of 1000 shared pages}
- AutoRenameStashPage=0			{0:Disabled; 1:Enabled automatic renaming page}
- PersonalNormalPageColor=0		{0:Color of the personal stash name without index (see * for color list)}
- PersonalIndexPageColor=12		{0:Color of the personal stash name with index (see * for color list)}
- PersonalMainIndexPageColor=9	{0:Color of the personal stash name with main index (see * for color list)}
- SharedNormalPageColor=4		{0:Color of the shared stash name without index (see * for color list)}
- SharedIndexPageColor=8		{0:Color of the shared stash name with index (see * for color list)
- SharedMainIndexPageColor=1	{0:Color of the shared stash name with main index (see * for color list)}

- ActiveSharedStash=0			{0:Disabled; 1:Enabled if ActiveMultiPageStash=1}
- ActiveSharedStashInMultiPlayer=0	{0:Disabled; 1:Enabled shared stash in multiplayer. Use only with different save folders.}
- SeparateHardcoreStash=1		{0:Same shared stash for HC and SC; 1:Use 2 differents stashes}
- OpenSharedStashOnLoading=0	{0:Disabled; 1:Select shared stash (instead of personal one) on character loading}
- SharedStashFilename=SharedStashSave	{xxx: The filename will be "_LOD_xxx.sss"}
- displaySharedSetItemNameInGreen=1 	{0:Disabled; 1:Enabled, set items in stash are their name displayed in green on other sets items.}
- MaxSharedPages=0 		{0:Infinite number of shared pages; 5000: Maximum of 5000 shared pages}
- ActiveSharedGold=1		{0:Disabled; 1:Use command to put and take gold (see command section)}
- PosXPreviousBtn=-1		{-1: Default position, 50: Put the button at the position 50 in absiss}
Same for PosYPreviousBtn, PosXNextBtn, PosYNextBtn, PosXSharedBtn, PosYSharedBtn, PosXPreviousIndexBtn, PosYPreviousIndexBtn, PosXNextIndexBtn, PosYNextIndexBtn, PosXPutGoldBtn, PosYPutGoldBtn, PosXTakeGoldBtn, PosYTakeGoldBtn, PosXStashNameField, PosYStashNameField, PosXStashGoldField, PosYStashGoldField.
- PosWPreviousBtn=32		{32: Width of the button}
Same for PosHPreviousBtn, PosWNextBtn, PosHNextBtn, PosWSharedBtn, PosHSharedBtn, PosWPreviousIndexBtn, PosHPreviousIndexBtn, PosWNextIndexBtn, PosHNextIndexBtn, PosWPutGoldBtn, PosHPutGoldBtn, PosWTakeGoldBtn, PosHTakeGoldBtn, PosWStashNameField, PosHStashNameField, PosWStashGoldField, PosHStashGoldField.


[STATS POINTS]
Use for repairing a bad stat point assignment.
For example, 30 points in energy for a barbarian!
On the character stat page, press selected key and click on minus button.
Select a key by setting KeyUsed (should choose 17 or 18).
Following are default values, between {} are some examples values with descriptions :
- ActiveStatsUnassignment=0		{0:Disabled 1:Enabled, press selected key when clicking}
- KeyUsed=18				{17:Control key selected; 18:Alt key selected}

Use the shift buton for assigning/unassigning all possible points in one click.
You can define a limit value for points assigned/unassigned with shift.
Following are default values, between {} are some examples values with descriptions :
- ActiveShiftClickLimit=0		{0:Disabled; 1:Enabled}
- LimitValueToShiftClick=5		(10:Assign or unassign stats points, 10 by 10}
- PosXUnassignSkillBtn=-1		{-1: Default position, 50: X position of the button set to 50.}
- PosYUnassignSkillBtn=-1		{-1: Default position, 50: Y position of the button set to 50.}


[STAT ON LEVEL UP]
WARNING : CHEAT, DON'T USE IN NORMAL GAME.
Change the number of Stats Points you receive when your character gains a level.
Following are default values, between {} are some examples values with descriptions :
- ActiveStatPerLevelUp=0		{0:Disabled; 1:Enabled}
- StatPerLevelUp=5			{0:no points win;  11:eleven points win}


[SKILLS POINTS]
Use for repairing a bad skill point assignment.
Click on the button on skill page for unassigning all assigned skills points.
Note : It verifies the real cost of each skill (can be greater than 1 in mod)
Warning : There are few place where you can put this button without bugs.
Following are default values, between {} are some examples values with descriptions :
- ActiveSkillsUnassignment=0	{0:Disabled; 1:Enabled}
- ActiveSkillsUnassignmentOneForOne=0	{0:Normal; 1:Force the skill unassign 1 for 1 (for mods).}
- PosXUnassignSkillBtn=-1 	{-1: Default position, 50: Put the button at the position 50 in X}
- PosYUnassignSkillBtn=-1 	{-1: Default position, 50: Put the button at the position 50 in Y}


[SKILL ON LEVEL UP]
WARNING : CHEAT, DON'T USE IN NORMAL GAME.
Change the number of Skills Points you receive when your character gains a level.
Following are default values, between {} are some examples values with descriptions :
- ActiveSkillPerLevelUp=0		{0:Disabled; 1:Enabled}
- SkillPerLevelUp=1			{0:no point gained;  3:three points gained)


[WORLD EVENT]
Activate the World Event in local game.
World Event only triggers in hell difficulty and only one time per game.
If the WE triggers when you aren't in the game, you lose it.
From the moment you launch D2, the next WE will trigger between few seconds to 41:40 hours after.
Keep in mind before editing it, World Event should be triggered rarely.
The item to sell can be changed, the value expected is same as the cube input field.
Following are default values, between {} are some examples values with descriptions :
- ActiveWorldEvent=0			{0:Disabled; 1:Enabled}
- ShowCounterInAllDifficulty=0		{0:Show it "SOJ Sold" message only in Hell; 1:Show it in all difficulties}
- ItemsToSell=The Stone of Jordan	{r01: rune EL;      cap,rar,upg: Any cap/war hat/shako rare}
- MonsterID=333				{333: DiabloClone spawned}
- OwnSOJSoldChargeFor=100		{100:When you sell a SOJ, the SOJ counter is incremented by 100}
- InititalSOJSoldMin=200		{200:The SOJ counter is set at least to 20 when you launch D2}
- InititalSOJSoldMax=3000		{3000:The SOJ counter is set at most to 300 when you launch D2}
- TriggerAtEachSOJSoldMin=75		{75:Need to have at least 75 SOJ sold between 2 World Event}
- TriggerAtEachSOJSoldMax=125		{125:Need to have at most 125 SOJ sold between 2 World Event}
- ActiveAutoSell=1			{0:Disabled; 1:SOJ counter is automatically incremented by 1}
- TimeBeforeAutoSellMin=0		{50:Need at least 50 seconds between 2 auto-increments}
- TimeBeforeAutoSellMin=1200		{1200:Need at most 20 minutes (1200 seconds) between 2 auto-increments}


[UBER QUEST]
Activate the Uber Quest in local.
It works only in Hell.
You must cube the 3 keys then the 3 organs in Harrogath.
ActiveUberQuest=0					{0:Disabled; 1:Enabled}
UberMephistoX=25130					{25130:X position of Uber Mephisto}
UberMephistoY=5143					{5143:Y position of Uber Mephisto}
UberDiabloX=25139					{25139:X position of Uber Diablo}
UberDiabloY=5139					{5139:Y position of Uber Diablo}
UberBaalX=25139						{25139:X position of Uber Baal}
UberBaalY=5135						{5135:Y position of Uber Baal}
ActiveUberMinions=1					{0:Disabled; 1:Enabled Uber minions in Tristram}
UberMephistoSpawnPercent=80			{80:Percent chance of Uber Mephisto to spawn a minion}
UberMephistoSpawnRadius=30			{30:Radius of Uber Mephisto to spawn a minion}
UberBaalSpawnPercent=30				{30:Percent chance of Uber Baal to spawn a minion}
UberBaalSpawnRadius=30				{30:Radius of Uber Baal to spawn a minion}
UberDiabloSpawnPercent=30			{30:Percent chance of Uber Diablo to spawn a minion}
UberDiabloSpawnRadius=30			{30:Radius of Uber Diablo to spawn a minion}
ActiveUberDiabloRushTweekAI=1		{0:Disabled; 1:Enabled Uber Diablo Rush tweek}
ActiveUberBaalTeleportTweekAI=1		{0:Disabled; 1:Enabled Uber Baal Teleport tweek}
ActiveUberBaalChillingArmorTweekAI=1	{0:Disabled; 1:Enabled Uber Baal Chilling Armor tweek}
UberBaalChillingArmorTimer=6000		{6000:Timer between Uber Baal casting Chilling Armor}


[INTERFACE]
Add extra page for displaying some stats.
Can choose if the main (first) page or the last selected page is displayed on opening the stats page.
You can change the the stats displayed via the PlugY\statsinterface.txt file (open it with MS Excel).
There is no max page limit.
Can choose whether to display the background of buttons (Use when a mod already changes background).
- ActiveNewStatsInterface=0			{0:Disabled; 1:Enabled}
- SelectMainPageOnOpenning=1			{0:Last selected page displayed; 1:Main page displayed}
- PrintButtonsBackgroundOnMainStatsPage=1	{0:Don't display the background; 1:display it}


[EXTRA]
You can run any number of Diablo II games on one computer.
For example, modder can test multiplayer game for their mod.
To start the second game, you must start it with "game.exe" and not "Diablo II.exe".
Warning : Don't start games with the same savepath when you use the Shared Stash.
	  Don't use the same character in same time.
Following are default values, between {} are some examples values with descriptions :
- ActiveLaunchAnyNumberOfLOD=0		{0:Disabled; 1:Enabled}

Regenerate the map each time you re-start a game (like in multiplayer).
- AlwaysRegenMapInSP=0			{0:Disabled; 1:Enabled}

Set the number of players (like /players x) each time you start a game.
- NBPlayersByDefault=0			{0:Disabled; 1:Set the game to 1 player (normal); 8:Set the game to emulate 8 players (maximum)}

Show the level of each item in their popup.
- ActiveDisplayItemLevel=0		{0:Disabled; 1:Enabled}

Always display Mana and Life values above the globes.
- AlwaysDisplayLifeAndManaValues=0	{0:Disabled; 1:Enabled; 2:Disabled but can be enabled by command}

Fix the bug which blocks the opening of txt files when they are opened by Miscrosoft Excel.
- EnabledTXTFilesWhenMSExcelOpenIt=0	{0:Disabled; 1:Enabled}

Display the stats current value (without magical bonus) when mouse pass over assignment buttons.
- ActiveDisplayBaseStatsValue=0		{0:Disabled; 1:Enabled}

Enabled the ladder only runewords out of realms.
This is done by setting to 0 the column "server" in runes.txt file.
So don't use this column in your mod with this funcion enabled !
- ActiveLadderRunewords=0		{0:Disabled; 1:Enabled}

Enabled the ability to open the Cow Portal in a difficulty where the player have already killed the Cow King.
- ActiveCowPortalWhenCowKingWasKilled=0 {0:Disabled; 1:Enabled}

Prevent Nihlathak's portal from closing.
- ActiveDoNotCloseNihlathakPortal=0 {0:Disabled; 1:Enabled}

Move Cain near Harrogath waypoint.
- MoveCainNearHarrogathWaypoint=0 {0:Disabled; 1:Enabled}


* Color list values (color code greater than 12 is black in 1.14d fullscreen):
- Invisible: 6
- Dark gray: 5
- Gray: 16
- Light gray: 15
- White: 0,
- Bright white: 18
- Gold: 4
- Dark yellow: 7
- Yellow: 9
- Orange: 8
- Darkest green: 10
- Dark green: 12
- Green: 2
- Blue: 3
- Purple: 11
- Red: 1
- Crystal red: 19


******** THANKS TO ********
- Blizzard for making Diablo2 and Lord of Destruction.
- Kingpin, Afj666, Joel, SVR, Myrdinn for their great help.
- Pralinor for his help in the convertion to 1.12.
- L'Autour for his help in the convertion to 1.13d.
- Haxifix for his help in the convertion to 1.14d.
- SnapChip for Uber AI in Tristram.
- ChaosEnergy for his testing.
- Char & Darque in the correction of my english.
- Shaitane, K&V, themastercaster, raspa and onyx for testing.
- Golvmopp, Dark Spot in the Corner, Megalixir and Athara for their help.
- All members of ProzenKeep chat and forums for their information and feedback.
- PhrozenKeep team.
- Translation :
	* English: Yohann, Jurica.
	* French: Yohann
	* German: ChaosEnergy, TheMasterCaster, ChaosMarc.
	* Italian: ItalianPlayer
	* Spanish: Acrerune
	* Polish: Serdel
	* Russian: L'Autour
	* Chinese (Traditional): Nagahaku
	* Japanase : CaiMiao

;--------------------------------------------------------------------------------------;