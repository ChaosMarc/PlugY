library PlugYLocal;
//Created by L'Autour

{ Important note about DLL memory management: ShareMem must be the
  first unit in your library's USES clause AND your project's (select
  Project-View Source) USES clause if your DLL exports any procedures or
  functions that pass strings as parameters or function results. This
  applies to all strings passed to and from your DLL--even those that
  are nested in records and classes. ShareMem is the interface unit to
  the BORLNDMM.DLL shared memory manager, which must be deployed along
  with your DLL. To avoid using BORLNDMM.DLL, pass string information
  using PChar or ShortString parameters. }

uses
  KOL;
  //SysUtils,
  //Classes;

{$R *.res}

type
  TLocalStr = record
    name: AnsiString;
    value: WideString;
  end;  

  TStrType = record
    k: AnsiString;
    s: WideString;
    case Byte of
      0: (dw: Cardinal);
      1: (c: array[0..3] of AnsiChar);
  end;

const
  NamePlugyLocal = 'Plugy\PlugYLocal.ini';
  MaxStr = 52;
  MaxLng = 11;
  MaxType = 97;
  MaxIdxType = 41;

  sLng: array[0..MaxLng] of AnsiString =
    ('ENG','ESP','DEU','FRA','POR','ITA','JPN','KOR','SIN','CHI','POL','RUS');

var
  Gender: WideString = '';

  StrTypes: array[0..MaxType + 1] of TStrType = (
    (k: '';     s: 'Shield (Not Class Specific)';  c: ('s','h','i','e')),
    (k: '';     s: 'Body Armor';                   c: ('t','o','r','s')),
    (k: 'Gold'; s: 'Gold';                         c: ('g','o','l','d')),
    (k: 'aqv';  s: 'Arrows';                       c: ('b','o','w','q')),
    (k: 'cqv';  s: 'Bolts';                        c: ('x','b','o','q')),
    (k: 'ear';  s: 'Ear';                          c: ('p','l','a','y')),
    (k: 'hrb';  s: 'Herb';                         c: ('h','e','r','b')),
    (k: '';     s: 'Potion';                       c: ('p','o','t','i')),
    (k: 'rin';  s: 'Ring';                         c: ('r','i','n','g')),
    (k: 'elx';  s: 'Elixir';                       c: ('e','l','i','x')),
    (k: 'amu';  s: 'Amulet';                       c: ('a','m','u','l')),
    (k: '';     s: 'Charm';                        c: ('c','h','a','r')),
    (k: 'lbt';  s: 'Boots';                        c: ('b','o','o','t')),
    (k: '';     s: 'Gloves';                       c: ('g','l','o','v')),
    (k: '';     s: 'Book';                         c: ('b','o','o','k')),
    (k: 'mbl';  s: 'Belt';                         c: ('b','e','l','t')),
    (k: '';     s: 'Gem';                          c: ('g','e','m',' ')),
    (k: 'tch';  s: 'Torch';                        c: ('t','o','r','c')),
    (k: '';     s: 'Scroll';                       c: ('s','c','r','o')),
    (k: 'scp';  s: 'Scepter';                      c: ('s','c','e','p')),
    (k: 'wnd';  s: 'Wand';                         c: ('w','a','n','d')),
    (k: '';     s: 'Staff';                        c: ('s','t','a','f')),
    (k: '';     s: 'Bow';                          c: ('b','o','w',' ')),
    (k: 'axe';  s: 'Axe';                          c: ('a','x','e',' ')),
    (k: 'clb';  s: 'Club';                         c: ('c','l','u','b')),
    (k: '';     s: 'Sword';                        c: ('s','w','o','r')),
    (k: '';     s: 'Hammer';                       c: ('h','a','m','m')),
    (k: '';     s: 'Knife';                        c: ('k','n','i','f')),
    (k: 'spr';  s: 'Spear';                        c: ('s','p','e','a')),
    (k: '';     s: 'Polearm';                      c: ('p','o','l','e')),
    (k: 'mxb';  s: 'Crossbow';                     c: ('x','b','o','w')),
    (k: 'mac';  s: 'Mace';                         c: ('m','a','c','e')),
    (k: 'hlm';  s: 'Helm';                         c: ('h','e','l','m')),
    (k: '';     s: 'Missile Potion';               c: ('t','p','o','t')),
    (k: '';     s: 'Quest Item';                   c: ('q','u','e','s')),
    (k: '';     s: 'Body Part';                    c: ('b','o','d','y')),
    (k: 'key';  s: 'Key';                          c: ('k','e','y',' ')),
    (k: 'tkf';  s: 'Throwing Knife';               c: ('t','k','n','i')),
    (k: 'tax';  s: 'Throwing Axe';                 c: ('t','a','x','e')),
    (k: 'jav';  s: 'Javelin';                      c: ('j','a','v','e')),
    (k: '';     s: 'Weapon';                       c: ('w','e','a','p')),
    (k: '';     s: 'Melee Weapon';                 c: ('m','e','l','e')),
    (k: '';     s: 'Missile Weapon';               c: ('m','i','s','s')),
    (k: '';     s: 'Throwing Weapon';              c: ('t','h','r','o')),
    (k: '';     s: 'Combo Weapon';                 c: ('c','o','m','b')),
    (k: '';     s: 'Armor';                        c: ('a','r','m','o')),
    (k: '';     s: 'Any Shield';                   c: ('s','h','l','d')),
    (k: '';     s: 'Miscellaneous';                c: ('m','i','s','c')),
    (k: '';     s: 'Socket Filler';                c: ('s','o','c','k')),
    (k: '';     s: 'Second Hand Item';             c: ('s','e','c','o')),
    (k: '';     s: 'Staves And Rods';              c: ('r','o','d',' ')),
    (k: '';     s: 'Missile';                      c: ('m','i','s','l')),
    (k: '';     s: 'Blunt';                        c: ('b','l','u','n')),
    (k: 'jew'; s: 'Jewel';                         c: ('j','e','w','l')),
    (k: '';     s: 'Class Specific';               c: ('c','l','a','s')),
    (k: '';     s: 'Amazon Item';                  c: ('a','m','a','z')),
    (k: '';     s: 'Barbarian Item';               c: ('b','a','r','b')),
    (k: '';     s: 'Necromancer Item';             c: ('n','e','c','r')),
    (k: '';     s: 'Paladin Item';                 c: ('p','a','l','a')),
    (k: '';     s: 'Sorceress Item';               c: ('s','o','r','c')),
    (k: '';     s: 'Assassin Item';                c: ('a','s','s','n')),
    (k: '';     s: 'Druid Item';                   c: ('d','r','u','i')),
    (k: '';     s: 'Claw';                         c: ('h','2','h',' ')),
    (k: '';     s: 'Assassin Claw';                c: ('h','2','h','2')),
    (k: '';     s: 'Orb';                          c: ('o','r','b',' ')),
    (k: '';     s: 'Voodoo Heads';                 c: ('h','e','a','d')),
    (k: '';     s: 'Paladin Shield';               c: ('a','s','h','d')),
    (k: '';     s: 'Barbarian Helm';               c: ('p','h','l','m')),
    (k: '';     s: 'Druid Helm';                   c: ('p','e','l','t')),
    (k: 'cloak';   s: 'Cloak';                     c: ('c','l','o','a')),
    (k: '';     s: 'Rune';                         c: ('r','u','n','e')),
    (k: 'circlet'; s: 'Circlet';                   c: ('c','i','r','c')),
    (k: 'hp3';  s: 'Healing Potion';               c: ('h','p','o','t')),
    (k: 'mp3';  s: 'Mana Potion';                  c: ('m','p','o','t')),
    (k: 'rvs';  s: 'Rejuvenation potion';          c: ('r','p','o','t')),
    (k: 'vps';  s: 'Stamina Potion';               c: ('s','p','o','t')),
    (k: 'yps';  s: 'Antidote Potion';              c: ('a','p','o','t')),
    (k: 'wms';  s: 'Thawing Potion';               c: ('w','p','o','t')),
    (k: 'cm1';  s: 'Small Charm';                  c: ('s','c','h','a')),
    (k: 'cm2';  s: 'Large Charm';                  c: ('m','c','h','a')),
    (k: 'cm3';  s: 'Grand Charm';                  c: ('l','c','h','a')),
    (k: '';     s: 'Amazon Bow';                   c: ('a','b','o','w')),
    (k: '';     s: 'Amazon Spear';                 c: ('a','s','p','e')),
    (k: '';     s: 'Amazon Javelin';               c: ('a','j','a','v')),
    (k: '';     s: 'Magic Arrows';                 c: ('m','b','o','q')),
    (k: '';     s: 'Magic Bolts';                  c: ('m','x','b','q')),
    (k: '';     s: 'Chipped Gem';                  c: ('g','e','m','0')),
    (k: '';     s: 'Flawed Gem';                   c: ('g','e','m','1')),
    (k: '';     s: 'Normal Gem';                   c: ('g','e','m','2')),
    (k: '';     s: 'Flawless Gem';                 c: ('g','e','m','3')),
    (k: '';     s: 'Perfect Gem';                  c: ('g','e','m','4')),
    (k: 'gsv';  s: 'Amethyst';                     c: ('g','e','m','a')),
    (k: 'gsw';  s: 'Diamond';                      c: ('g','e','m','d')),
    (k: 'gsg';  s: 'Emerald';                      c: ('g','e','m','e')),
    (k: 'gsr';  s: 'Ruby';                         c: ('g','e','m','r')),
    (k: 'gsb';  s: 'Sapphire';                     c: ('g','e','m','s')),
    (k: 'gsy';  s: 'Topaz';                        c: ('g','e','m','t')),
    (k: 'sku';  s: 'Skull';                        c: ('g','e','m','z')),
    (k: ''; s: '???'; dw: 0));


  LocalStrings: array[0..MaxStr + 1] of TLocalStr = (
    (name: 'STR_STATS_UNASSIGN_WITH_LIMIT'; value: '+Alt: Unassign, +Shift: by %d points'),
    (name: 'STR_STATS_UNASSIGN_WITHOUT_LIMIT'; value: '+Alt: Unassign, +Shift: all remaining points'),
    (name: 'STR_STATS_BASE_MIN'; value: 'Base: %d (Min: %d)'),
    (name: 'STR_SKILLS_UNASSIGN'; value: 'Un-allocate all skills points'),
    (name: 'STR_STASH_PREVIOUS_PAGE'; value: 'Previous Page (+shift: First Page)'),
    (name: 'STR_STASH_NEXT_PAGE'; value: 'Next Page (+shift: Last not empty Page'),
    (name: 'STR_TOGGLE_TO_PERSONAL'; value: 'Toggle to Personal Stash'),
    (name: 'STR_TOGGLE_TO_SHARED'; value: 'Toggle to Shared Stash'),
    (name: 'STR_STASH_PREVIOUS_INDEX'; value: 'Previous Index : by %d Pages (+Shift: %d)'),
    (name: 'STR_STASH_NEXT_INDEX'; value: 'Next Index : by %d Pages (+shift: %d)'),
    (name: 'STR_PERSONAL_PAGE_NUMBER'; value: 'Personal Page n°%u'),
    (name: 'STR_SHARED_PAGE_NUMBER'; value: 'Shared Page n°%u'),
    (name: 'STR_NO_SELECTED_PAGE'; value: 'No selected page'),
    (name: 'STR_PUT_GOLD'; value: 'Put Gold'),
    (name: 'STR_TAKE_GOLD'; value: 'Take Gold'),
    (name: 'STR_SHARED_GOLD_QUANTITY'; value: 'Shared Gold : %u'),
    (name: 'STR_PREVIOUS_PAGE'; value: 'Previous Page'),
    (name: 'STR_NEXT_PAGE'; value: 'Next Page'),
    (name: 'STR_ITEM_LEVEL'; value: 'Item Level: %u'),
    (name: 'STR_COW_PORTAL'; value: 'Cow Portal'),
    (name: 'STR_PANDEMONIUM_PORTAL'; value: 'Pandemonium Portal'),
    (name: 'STR_PANDEMONIUM_FINAL_PORTAL'; value: 'Pandemonium Final Portal'),
    (name: 'STR_FULL'; value: 'Fully '),
    (name: 'STR_REPAIR'; value: 'Repair '),
    (name: 'STR_AND'; value: 'and '),
    (name: 'STR_RECHARGE'; value: 'Recharge '),
    (name: 'STR_DESTROY_FILLERS'; value: 'Destroys Fillers '),
    (name: 'STR_REMOVE_FILLERS'; value: 'Remove Fillers '),
    (name: 'STR_REGENERATE'; value: 'Regenerate '),
    (name: 'STR_WITH_N_SOCKETS'; value: ' with %u Sockets'),
    (name: 'STR_ETHERAL'; value: 'Ethereal '),
    (name: 'STR_NOT_ETHERAL'; value: 'Not Ethereal '),
    (name: 'STR_NOT_RUNEWORD'; value: 'Not Runeword '),
    (name: 'STR_BASIC'; value: 'Basic '),
    (name: 'STR_EXCEPTIONAL'; value: 'Exceptional '),
    (name: 'STR_ELITE'; value: 'Elite '),
    (name: 'STR_CRACKED'; value: 'Cracked '),
    (name: 'STR_NORMAL'; value: 'Normal '),
    (name: 'STR_SUPERIOR'; value: 'Superior '),
    (name: 'STR_MAGIC'; value: 'Magic '),
    (name: 'STR_SET'; value: 'Set '),
    (name: 'STR_RARE'; value: 'Rare '),
    (name: 'STR_UNIQUE'; value: 'Unique '),
    (name: 'STR_CRAFTED'; value: 'Crafted '),
    (name: 'STR_TEMPERED'; value: 'Tempered '),
    (name: 'STR_ITEM'; value: 'Item'),
    (name: 'STR_ITEM_SAME_TYPE'; value: 'Item of the same type'),
    (name: 'STR_OR_UPGRADED'; value: ' (or upgraded)'),
    (name: 'STR_WITHOUT_SOCKET'; value: ' without Sockets'),
    (name: 'STR_WITH_SOCKET'; value: ' with Sockets'),
    (name: 'STR_ONLY_N_H'; value: ' (Nightmare and Hell only)'),
    (name: 'STR_ONLY_HELL'; value: ' (Hell only)'),
    (name: 'STR_ONLY_CLASS'; value: ' (%s only)'),
    (name: ''; value: '<unknown string>')
    );

  IniName: AnsiString;

//MS C++__fastcall(ecx,edx) vs Delphi register(eax,edx,ecx) - :(
function InitTranslatedString(_EAX: Integer;_EDX: Integer; iLng: Integer): Boolean; register;
var
  IniFile: PIniFile;
  CurLng: AnsiString;
  S: UTF8String;
  i: Integer;
begin
  Result := False;
  if not FileExists(IniName) then Exit;

  if (iLng < 0)or(iLng > MaxLng) then iLng := 0;
  CurLng := sLng[iLng];

  IniFile := OpenIniFile(IniName);
  IniFile.Mode := ifmRead;
  for i := 0 to MaxStr do
  begin
    IniFile.Section := LocalStrings[i].name;
    S := IniFile.ValueString(CurLng, '');
    if S <> '' then LocalStrings[i].value := UTF8Decode(S);
  end;
  for i := 0 to MaxType do
  begin
    IniFile.Section := StrTypes[i].c;
    S := IniFile.ValueString(CurLng, '');
    if S <> '' then
    begin
      StrTypes[i].s := UTF8Decode(S);
      StrTypes[i].k := '';
    end;
  end;
  Result := True;
end;

//MS C++__fastcall(ecx,edx) vs Delphi register(eax,edx,ecx) - :(
function GetTranslatedString(_EAX: Integer;_EDX: Integer; Idx: Integer): PWideChar; register;
begin
  if (Idx < 0)or(Idx > MaxStr) then Idx := MaxStr + 1;
  Result := @LocalStrings[Idx].Value[1];
end;

//MS C++__fastcall(ecx,edx) vs Delphi register(eax,edx,ecx) - :(
function GetTypeString(_EAX: Integer;out IdxStr: PAnsiChar; Code: Cardinal): PWideChar; register;
var
  i: Integer;
begin
  i := 0;
  while i <= MaxType do
  begin
    if Code = StrTypes[i].dw then Break;
    Inc(i);
  end;
  if StrTypes[i].k = '' then
    IdxStr := nil
  else
    IdxStr := PAnsiChar(StrTypes[i].k);
  Result := PWideChar(StrTypes[i].s);
end;

function WSprintStringLastGender(buf: PWideChar; lenbuf: Integer; Idx: Integer): Integer; stdcall;
var
  i, p, L: Integer;
  S: WideString;
begin
  S := GetTranslatedString(0,0,Idx);

  if Gender <> '' then
  begin
    p := Pos(Gender, S);
    if p <> 0 then
    begin
      L := Length(S);
      p := p + Length(Gender);
      for i := p to L do
        if S[i] = '[' then Break;
      S := Copy(S, p, i - p);
    end;
  end;

  Result := Min(lenbuf - 1, Length(S));
  for i := 1 to Result do
    buf[i-1] := S[i];
  buf[Result + 1] := #$0000;  
end;

//MS C++__fastcall(ecx,edx) vs Delphi register(eax,edx,ecx) - :(
function SetMonoString(_EAX: Integer;_EDX: Integer; InStr: PWideChar): PWideChar; register;
var
  StrList: PWStrList;
  i: Integer;
  S: WideString;
begin
  Result := InStr;
  if Result = nil then Exit;
  StrList := NewWStrList;
  StrList.Text := InStr;
  i := Strlist.Count - 1;
  if i = 0 then Exit;
  S := StrList.Items[i];
  while i > 0 do
  begin
    Dec(i);
    S := S + '. ' + StrList.Items[i];
  end;
  Move(S[1], InStr[0], Length(S) shl 1);
end;

//MS C++__fastcall(ecx,edx) vs Delphi register(eax,edx,ecx) - :(
function CutStringGender(_EAX: Integer;_EDX: Integer; InStr: PWideChar): PWideChar; register;
var
  i, j: Integer;
begin
  Result := InStr;
  Gender := '';
  if (InStr = nil)or(InStr[0] <> '[') then Exit;
  i := 1;
  while (InStr[i] <> #$0000) do
  begin
    if InStr[i] = ']' then
    begin
      if (i < 2)or(InStr[i+1] = #$0000) then Exit;
      SetLength(Gender, i + 1);
      for j := 0 to i do
        Gender[j+1] := InStr[j];
      Result := @InStr[i+1];
      Exit;   
    end;
    Inc(i);
  end;
end;

{
const
  NcColor = 14;
  LenCode = 9;

type
  TTextColor = array[0..LenCode - 1] of AnsiChar;

const
  cColor: array[0..NcColor - 1] of TTextColor = (
    ('\','w','h','i','t','e',';',#00,#00),
    ('\','g','r','e','y',';',#00,#00,#00),
    ('\','r','e','d',';',#00,#00,#00,#00),
    ('\','g','r','e','e','n',';',#00,#00),
    ('\','b','l','u','e',';',#00,#00,#00),
    ('\','g','o','l','d',';',#00,#00,#00),
    ('\','d','g','r','e','y',';',#00,#00),
    ('\','b','l','a','c','k',';',#00,#00),
    ('\','t','a','n',';',#00,#00,#00,#00),
    ('\','o','r','a','n','g','e',';',#00),
    ('\','y','e','l','l','o','w',';',#00),
    ('\','d','g','r','e','e','n',';',#00),
    ('\','p','u','r','p','l','e',';',#00),
    ('\','c','o','l','o','r',';',#00,#00));
  //lengths of strings in cColor table, without '\'
  cColLength:  array[0..NcColor-1] of Byte = (6,5,4,6,5,5,6,6,4,7,7,7,7,6);
  pColor: PAnsiChar = @cColor[NcColor-1][1];
var
  SaveToTbl: Byte = 0;

//ANSI convert ColorApi to ColorCode
//optional UCS2 convert '\n' to  $0A
function ColorApi2ColorCode(Src: PAnsiChar; Dst: PAnsiChar;
  SourceChars: Integer): Integer;
//EAX: Src
//EDX: Dst
//ECX: Length Src
//Result: OutLength -> EAX
asm
  //backup
  PUSHF
  CLD //инкремент для строковых команд
  PUSH ESI
  PUSH EDI
  PUSH EBX
  PUSH EBP

  PUSH EDX //сохраняем начальный адрес приемника
  MOV EDI, Dst
  TEST Src, Src //проверка на пустую строку
  JZ @Exit
  MOV ESI, Src
// в ECX хранится количество оставшихся символов из Src
@NextChar:
  //загрузка очередного символа в EAX
  XOR EAX, EAX
  LODSB //MOV AL, [ESI]+
  //проверка на нулевой символ (конец строки)
  TEST AL, AL
  JZ @Exit
  //проверка на символ '\'
  CMP AL, '\'
  JE @Slash

@CopyChar:
  //normal chars
  STOSB //MOV [EDI]+, AL

//уменьшение счетчика необработанных байтов и перед в начало цикла
@Loop:
  LOOP @NextChar

@Exit:
  MOV BYTE PTR [EDI], $00 //нулевой символ в конце выходной строки
  POP EAX //восстанавливаем начальный адрес приемника
  XCHG EAX, EDI
  //get length of Dst
  SUB EAX, EDI
  //restore
  POP EBP
  POP EBX
  POP EDI
  POP ESI
  POPF
  RET

@Slash:
  //проверка на наличие следующего символа
  CMP ECX, 1
  JB @CopyChar // if ECX < 1
  //загрузка следующего символа
  LODSB //MOV AL, [ESI]+
  //проверка символа на код перевода строки
  CMP AL, 'n'
  JNZ @TestColor
  //поправка ECX
  DEC ECX

  //test Save2Tbl
  CMP SaveToTbl, 0
  JNZ @UnixReturn
  //save '\n'
  MOV AL, '\'
  STOSB //MOV [EDI]+, AL
  MOV AL, 'n'
  JMP @CopyChar

@UnixReturn:
  //save UnixNewLine
  MOV AL, $0A
  JMP @CopyChar

//проверка на строки установки цвета шрифта:
@TestColor:
  //проверка на использование макро определений цвета шрифта
  //CMP MacroColorView, $00
  //JE @StoreSlash

  //backup
  PUSH ECX
  PUSH EDI
  //восстановление ESI
  DEC ESI
  //сохранение источнка
  MOV EBX, ESI
  //загрузка количества сравниваемых строк
  MOV EAX, NcColor
  //загрузка адреса последней строки из массива строк
  //установки цвета шрифта (без '')
  MOV EBP, pColor
  //загрузка адреса массива длин строк без '\' и
  //(-1, т.к. будет прибавлятся EAX)
  LEA EDX, [cColLength - 1]

@CmpStr:
  //загрузка адреса строки приемника
  MOV EDI, EBP
  //загрузка счетчика символов строки
  MOVZX ECX, BYTE PTR [EDX + EAX]
  //сравнение строк
  //(прерывание, если не равны, т.е. длину Src можно не проверять)
  REPE CMPSB
  //проверка результата сравнения строк
  JZ @ColorCode
  //восстановление адреса строки источника
  MOV ESI, EBX
  //сдвиг адреса строки приемника на следующую строку
  SUB EBP, LenCode
  //декремент счетчика строк
  DEC EAX
  //проверка на повтор цикла сравнения строк
  JA @CmpStr //if EAX > 0
//символ '\' был просто символом
  //restore
  POP EDI
  POP ECX
@StoreSlash:
  //запись кода символа '\'
  MOV AL, '\'
  JMP @CopyChar

//запись кода смены известного цвета шрифта
//в AL номер строки из cColor
@ColorCode:
  //restore
  POP EDI
  //добавка кода цвета к ColorCode
  MOVZX EDX, BYTE PTR [EDX + EAX]//загрузка счетчика символов строки
  ADD AL, $2E //1..14 + $2E = $2F..$3C
  //backup EAX
  MOV ECX, EAX
  //save ColorCode
  MOV AX, $63FF
  STOSW //MOVD [EDI]+, AX
  //restore EAX
  MOV EAX, ECX
  //test \color;
  CMP AL, $3C
  JE @FullColorCode
  //add number to ColorCode
  STOSB //MOVD [EDI]+, AL

@FullColorCode:
  //restore ECX
  POP ECX
  SUB ECX, EDX //коррекция ECX на длину строки
  JZ @Exit //конец строки источника
  //ESI после сравнения уже указывает на следующий символ
  JMP @NextChar //ECX >= 1
end;

//MS C++__fastcall(ecx,edx) vs Delphi register(eax,edx,ecx) - :(
procedure ReplaceColorCode(_EAX: Integer;_EDX: Integer; Str: PAnsiChar); register;
var
  i, L, n: Integer;
begin
  L := Length(Str);
  n := ColorApi2ColorCode(Str, Str, L);
  Dec(L);
  for i := n to L do
  begin
    //Str[i] := ' ';
  end;
  //MsgOK(Str);
end;
}

//Decode string from UCS2 to UTF8
//WideCharToMultiByte not support CP_UTF8 in Windows 95
function UCS2ToUTF8(Dest: PAnsiChar; MaxDestBytes: Integer;
  Source: PWideChar; SourceChars: Integer): Integer;
//EAX: @Dest
//EDX: MaxDestBytes
//ECX: @Source
//(ESP): SourceChars;
//Result: DestChars of @Dest -> EAX
asm
  //backup
  PUSHF
  CLD //set (ESI)+
  PUSH EBX
  PUSH ESI
  PUSH EDI

  PUSH Dest //backup @Dst
  MOV EDI, Dest
  TEST Source, Source //test NULL string
  JZ @Exit
  MOV ESI, Source
  MOV ECX, SourceChars

@NextChar:
  //test length of Dst
  DEC EDX
  JLE @Exit
  //get next char to EAX
  XOR EAX, EAX
  LODSW //MOV AX, [ESI]+
  //test NULL char (end of string)
  TEST EAX, EAX
  JZ @Exit
//decode UCS2 to UTF8
@Ucs2ToUtf8:
  //test UCS2-char in $0000..$007F
  CMP AX, $007F
  JA @11xxxxxx //if AX > $7F
//UTF8-char: 0xxxxxxx
  //AH = 00000000; AL = 0xxxxxxx
@0xxxxxxx:
  //save UTF8-char
  STOSB //MOVB [EDI]+, AL
//end Loop
@Loop:
  LOOP @NextChar
  JMP @Exit

@11xxxxxx:
  //test length of Dst
  DEC EDX
  JLE @Exit
  //test UCS2-char in $0080..$07FF
  CMP AX, $07FF
  JA @1110xxxx //if AX > $07FF
//UTF8-char: 110xxxxx 10xxxxxx
  //AH = 00000xxx; AL = xxxxxxxx
  //get first byte UTF8-char to AL
  ROR AX, 6     //AH = xxxxxx00; AL = 000xxxxx
  //get second byte UTF8-char to AH
  SHR AH, 2     //AH = 00xxxxxx
  OR  AX, $80C0 //AH = 10xxxxxx; AL = 110xxxxx
  //save UTF8-char
  STOSW //MOVW [EDI]+, AX
  JMP @Loop

//UTF8-char: 1110xxxx 10xxxxxx 10xxxxxx
@1110xxxx:
  //test length of Dst
  DEC EDX
  JLE @Exit
  //save lobyte of UCS2-char
  MOV BL, AL
  //AH = xxxxxxxx; AL = xxxxxxxx
  //get first byte UTF8-char UTF8 to AL
  ROL AX, 4    //AL = ????xxxx; AH = xxxxxx??
  AND AL, $0F  //AL = 0000xxxx
  //get second byte UTF8-char to AH
  SHR AH, 2    //AH = 00xxxxxx
  OR AX, $80E0 //AH = 10xxxxxx; AL = 1110xxxx
  //save first bytes UTF8-char
  STOSW //MOVW [EDI]+, AX
  //get second byte UTF8-char to AL
  XCHG EAX, EBX //??xxxxxx
  AND AL, $3F   //00xxxxxx
  OR  AL, $80   //10xxxxxx
  //save third byte UTF8-char
  JMP @0xxxxxxx

@Exit:
  MOV BYTE PTR [EDI], $00 //set end-char of Dst
  POP EAX //restore @Dst
  XCHG EAX, EDI
  //get length of Dst to Result
  SUB EAX, EDI
  //restore
  POP EDI
  POP ESI
  POP EBX
  POPF
end;

function _UCS2ToUTF8(Dest: PAnsiChar; MaxDestBytes: Integer;
  Source: PWideChar; SourceChars: Integer): Integer; stdcall;
begin
  Result := UCS2ToUTF8(Dest, MaxDestBytes, Source, SourceChars);
end;

//Decode string from UTF8 to UCS2
function UTF8ToUCS2(Dest: PWideChar; MaxDestBytes: Integer;
  Source: PAnsiChar; SourceChars: Integer): Integer;
//EAX: @Dest
//EDX: MaxDestBytes
//ECX: @Source
//(ESP): SourceChars;
//Result: DestChars of @Dest -> EAX
//if errors then
//Result: -(DestChars of @Dest) -> EAX
asm
  //backup
  PUSHF
  CLD //set (ESI)+
  PUSH EBX
  PUSH ESI
  PUSH EDI

  PUSH Dest //backup @Dst
  MOV EDI, Dest
  TEST Source, Source //test NULL string
  JZ @Exit
  MOV ESI, Source
  MOV ECX, SourceChars

@NextChar:
  //test length of Dst
  SUB EDX, 2
  JLE @Exit
  //get next char to EAX
  XOR EAX, EAX
  LODSB //MOV AL, [ESI]+
  //test NULL char (end of string)
  TEST AL, AL
  JZ @Exit
//decode UTF8 to UCS2
@Utf8ToUcs2:
  //test first byte UTF8 = 0xxxxxxx
  TEST AL, $80
  JNZ @1xxxxxxx
//UTF8: 0xxxxxxx (AH = 0)
@SaveU16:
  STOSW //MOVW [EDI]+, EAX
@Loop:
  LOOP @NextChar
  JMP @Exit

@1xxxxxxx:
  //test first byte UTF8 = 10xxxxxx
  TEST AL, $40 //01000000
  JZ @Exit  //Error UTF8: 10xxxxxx
  //test first byte UTF8 = 1111xxxx
  CMP AL, $F0 //11110000
  JAE @Exit  //Error UTF8 to UCS2: 1111xxxx ( if AL >= $F0)
  //test exist second byte UTF8
  JECXZ @Exit // DEC ECX; if ECX = 0
  //backup first byte UTF8
  MOV AH, AL //11xxxxxx
  //load second byte UTF8
  LODSB //MOV AL, [ESI]+
  //test second byte UTF8 = 10xxxxxx
  TEST AL, $40 //01000000
  JNE @Exit  //Error UTF8: 10xxxxxx
  //test second byte UTF8 = 110xxxxx
  TEST AH, $20 //00100000
  JNZ @1110xxxx //third byte UTF8
//UTF8: 110xxxxx 10xxxxxx
  //backup first byte UTF8
  MOV BL, AH //110xxxxx
  //get high byte UCS2
  SHR AH, 2  //00110xxx
  AND AX, $073F //AH: 00000xxx; AL: 00xxxxxx
  //get low byte USC2
  SHL BL, 6  //xx000000
  OR AL, BL   //xxxxxxxx
  //AX: 00000xxx:xxxxxxxx
  JMP @SaveU16

@1110xxxx:
  //test exist third byte UTF8
  JeCXZ @Exit // DEC ECX; if ECX = 0
  //backup second byte UTF8
  MOV BL, AL //10xxxxxx
  //load third byte UTF8
  LODSB //MOV AL, [ESI]+
  //test third byte UTF8 = 10xxxxxx
  CMP AL, $C0 //11000000
  JAE @Exit  //Error UTF8: 11xxxxxx ( if AL >= $C0)
//UTF8: 1110xxxx 10xxxxxx 10xxxxxx
  //get bytes UCS2 на: xx00000:0000xxxx
  AND BX, $003F //DX := 00000000:00xxxxxx
  ROR BX, 2 //BL := 0000xxxx; BH := xx000000
  //get low byte UTF8
  AND AL, $3F //00xxxxxx
  OR AL, BH   //xxxxxxxx
  //get high byte UCS2
  SHL AH, 4   //xxxx0000
  OR AH, BL   //xxxxxxxx
  JMP @SaveU16

@Exit:
  XOR EAX, EAX
  MOV [EDI],AX //set end-char of Dst
  POP EAX //restore @Dst
  XCHG EAX, EDI
  //get length of Dst to Result
  SUB EAX, EDI
  SHR EAX, 1
  //restore
  POP EDI
  POP ESI
  POP EBX
  POPF
end ; //asm


function _UTF8ToUCS2(Dest: PWideChar; MaxDestBytes: Integer;
  Source: PAnsiChar; SourceChars: Integer): Integer; stdcall;
begin
  Result := UTF8ToUCS2(Dest, MaxDestBytes, Source, SourceChars);
end;

exports
  _UCS2ToUTF8 name '__stdcall UCS2toUTF8',
  _UTF8ToUCS2 name '__stdcall UTF8toUCS2',
  //ReplaceColorCode name 'replaceColorCode',
  SetMonoString name '__fastcall setMonoString',
  WSprintStringLastGender name '__stdcall wSprintStringLastGender',
  CutStringGender name '__fastcall cutStringGender',
  GetTypeString name '__fastcall getTypeString',
  GetTranslatedString name '__fastcall getTranslatedString',
  InitTranslatedString name '__fastcall initTranslatedString';

var
  i, j: Integer;
  S: UTF8String;
  b: Boolean;
begin
  IniName := GetStartDir + NamePlugyLocal;
  if FileExists(IniName) then Exit;
  S := #$EF#$BB#$BF';UTF8';
  for i := 0 to MaxStr do
  begin
    S := S + #$0D#$0A'[' + LocalStrings[i].name + ']'#$0D#$0A + sLng[0] + '="'
      + LocalStrings[i].value + '"'#$0D#$0A;
    for j := 1 to MaxLng do
      S := S + sLng[j] + '='#$0D#$0A;
  end;
  for i := 0 to MaxType do
  begin
    S := S + #$0D#$0A;
    b := (StrTypes[i].k <> '');
    if b then
      S := S + ';';
    S := S + '[' + StrTypes[i].c + ']'#$0D#$0A;

    if b then
      S := S + ';';
    S := S + sLng[0] + '="' + StrTypes[i].s + '"'#$0D#$0A;
    if not b then
    begin
      for j := 1 to MaxLng do
        S := S + sLng[j] + '='#$0D#$0A;
    end;
  end;
  StrSaveToFile(IniName, S);
end.
