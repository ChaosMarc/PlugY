import os
import json
import codecs
import shutil

files = ["ENG.json", "ESP.json", "DEU.json", "FRA.json", "POR.json", "ITA.json", "JPN.json", "KOR.json", "SIN.json", "CHI.json", "POL.json", "RUS.json"]
translations = {}

for file in files:
    lang = os.path.splitext(file)[0]
    with open(file) as json_file:
        data = json.load(json_file)
        for key, value in data.items():
            if (key in translations):
                t = translations[key]
            else:
                t = {}
            t[lang] = value
            translations[key] = t
    json_file.close()

with codecs.open("../LocalizedStrings.ini", "w", encoding="utf16") as ini_file:
    ini_file.write(';UTF16\r\n')
    ini_file.write(';--------------------------------------------------------------------------------------;\r\n')
    ini_file.write(';                                                                                      ;\r\n')
    ini_file.write(';                              "PlugY, The Survival Kit"                               ;\r\n')
    ini_file.write(';                                Localized String File                                 ;\r\n')
    ini_file.write(';                                                                                      ;\r\n')
    ini_file.write(';                                  by Yohann Nicolas                                   ;\r\n')
    ini_file.write(';                                                                                      ;\r\n')
    ini_file.write(';                                    version 11.02                                     ;\r\n')
    ini_file.write(';                                                                                      ;\r\n')
    ini_file.write(';--------------------------------------------------------------------------------------;\r\n')
    ini_file.write('\r\n')

    for key, langs in translations.items():
        ini_file.write("[{}]\r\n".format(key))
        for lang, value in langs.items():
            ini_file.write("{}={}\r\n".format(lang, value))
        ini_file.write("\r\n")

    ini_file.close()
