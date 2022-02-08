
# SDF Parser for Unreal Engine

![SDFParser banner image](https://user-images.githubusercontent.com/891532/153074435-e27e1305-6c58-4428-8480-cc048d20e1f4.png)

SDFParser is a plugin that is designed to open and parse SDF and MOL chemical table files into custom molecule structures, for use with any Blueprints or C++ based project.

## Features

 - *SDFParserComponent* actor component, the primary component for performing all primary functions. Attach to any actor.
 - Blueprint nodes for listing folders, with optional file extension filters, plus opening files into a string array and parsing.
 - *SDFConfig* data asset which can be instanced and used to provide rendering defaults including scale, molecule and bond colours.
 - Multiple structs and enums for definitions of molecules, atoms, bonds, charges and isotopes.
 - Full C++ source included.

## Example Project

- After installing the plugin, download the example project below and try it for yourself.

[Download](https://github.com/darbycostello/SDFParser/files/8027430/SDFExample.zip)

## Limitations and Future Work

 - The parser has been tested against a number of SDF / MOL files and it holds up reasonably well and will attempt to at least get the main atom and bond information out of the file, even if there are some errors. But it would need more testing to be fully resilient to the breadth of modifications that are often made to these kinds of file.
 - The entire SDF / MOL specification is not covered by the plugin, as I understand this to be pretty vast once one goes beyond the more standard use cases. I would welcome any updates or changes to the parser covering these additional attributes. This was an exploratory project and it is unlikely I will return to add any new features, but I'll happily accept any PRs.
